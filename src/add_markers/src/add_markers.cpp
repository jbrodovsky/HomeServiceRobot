#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include "nav_msgs/Odometry.h"
#include <math.h>
#include <ros/console.h>

float odomX = 0.0, odomY = 0.0;

void odomCallback(const nav_msgs::Odometry::ConstPtr& msg){
    //odomX = msg->pose.pose.linear.x;
    //odomY = msg->pose.pose.linear.y;
    ::odomX = msg->pose.pose.position.x;
    ::odomY = msg->pose.pose.position.y;
}

int main(int argc, char** argv){
    ros::init(argc, argv, "add_markers");
    ros::NodeHandle n;
    ros::Rate r(1);
    ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("marker", 1);
    ros::Subscriber odom_sub = n.subscribe("/odom", 1000, odomCallback);

    uint32_t shape = visualization_msgs::Marker::CUBE;
    bool hide = false;
    int i = 0;
    int num = 2;
    double points[num][3] = {{ 2.0, 2.0,   1.5707/2.0}, 
                             {-2.0, 2.0,   3.14}};
    visualization_msgs::Marker marker;
    marker.header.frame_id = "map";
    marker.header.stamp = ros::Time::now();
    marker.ns = "marker";
    marker.id = 0;
    marker.type = shape;
    marker.action = visualization_msgs::Marker::ADD;
    
    marker.pose.position.z = 0.0;
    marker.pose.orientation.z = points[i][2];

    marker.color.r = 0.0;
    marker.color.g = 0.0;
    marker.color.b = 1.0;
    marker.color.a = 1.0;

    marker.scale.x = 0.25;
    marker.scale.y = 0.25;
    marker.scale.z = 0.25;
    
    marker.lifetime = ros::Duration();

    while(ros::ok()){
        marker.pose.position.x = points[i][0];
        marker.pose.position.y = points[i][1];
        while(marker_pub.getNumSubscribers() < 1){
            if(!ros::ok()){return 0;}
            ROS_WARN_ONCE("No marker subscriber!");
            sleep(1);
        }
        ROS_WARN_ONCE("Recieved subscriber!");
        /*
        if(!hide and i < num){
            ROS_INFO("Publishing marker.");
            marker.color.a = 1.0;
            marker_pub.publish(marker);
            i++;
        }
        else{
            ROS_INFO("Hiding marker.");
            //visualization_msgs::Marker blank;
            marker.color.a = 0.0;
            marker_pub.publish(marker);
            ros::Duration(5).sleep();
            hide = false;
        }
        */
        //ros::Duration(5).sleep();
        //hide = !hide;
        float dx = marker.pose.position.x - odomX;
        float dy = marker.pose.position.y - odomY;
        float dist = std::sqrt(pow(dx, 2) + pow(dy, 2));
        ROS_INFO("POSE: (%f, %f) --- Dist: %f | dx: %f | dy: %f", odomX, odomY, dist, dx, dy);
        if(fabs(dist) > 0.5){
            marker.color.a = 1.0;
            marker_pub.publish(marker);
        }
        else if(i<num) { 
            hide = true;
            ROS_INFO("Target reached, picking up package...");
            marker.color.a = 0.0;
            marker_pub.publish(marker);
            ros::Duration(5).sleep();
            i++;
        }
        ros::spinOnce();
        r.sleep();
    }

    return 0;
}
