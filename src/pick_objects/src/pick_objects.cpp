#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <tf/tf.h>

// Define a client for to send goal requests to the move_base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){
  // Initialize the simple_navigation_goals node
  //ros::init(argc, argv, "simple_navigation_goals");
  ros::init(argc, argv, "pick_objects");  
  
  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);
  
  // Wait 5 sec for move_base action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }
  ROS_INFO("Waiting for everything to spin up.");
  ac.waitForServer(ros::Duration(10.0));
  ROS_INFO("Executing!");
  move_base_msgs::MoveBaseGoal goal;

  // set up the frame parameters
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();
  
  int num = 2;
  double points[num][3] = {{ 2.0, 2.0,   1.5707/2.0}, 
                           {-2.0, 2.0,   3.14}};

  for (int i=0; i < num; i++){
      goal.target_pose.pose.position.x = points[i][0];
      goal.target_pose.pose.position.y = points[i][1];
      goal.target_pose.pose.orientation = tf::createQuaternionMsgFromYaw(points[i][2]);
      // Send the goal position and orientation for the robot to reach
      ROS_INFO("Sending goal");
      ac.sendGoal(goal);
      // Wait an infinite time for the results
      ac.waitForResult();
      // Check if the robot reached its goal
      if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
        ROS_INFO("Goal reached!");
      else
        ROS_INFO("Failed to reach goal for some reason");
      ros::Duration(5.0).sleep();
  }  
  return 0;
}