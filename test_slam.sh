#!/bin/sh
echo "ROS Testing setup"
xterm -e "source /opt/ros/kinetic/setup.bash" &
xterm -e "source ./devel/setup.bash; roslaunch turtlebot_gazebo turtlebot_world.launch" &
sleep 3
xterm -e "source ./devel/setup.bash; rosrun gmapping slam_gmapping" &
xterm -e "source ./devel/setup.bash; roslaunch turtlebot_teleop keyboard_teleop.launch" &
xterm -e "source ./devel/setup.bash; roslaunch turtlebot_rviz_launchers view_navigation.launch" &