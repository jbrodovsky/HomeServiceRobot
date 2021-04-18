#!/bin/sh
echo "Test Navigation Shell Script"
xterm -e "source /opt/ros/kinetic/setup.bash" &
xterm -e "source ./devel/setup.bash; roslaunch turtlebot_gazebo turtlebot_world.launch" &
sleep 3
xterm -e "source ./devel/setup.bash; roslaunch turtlebot_gazebo amcl_demo.launch" &
xterm -e "source ./devel/setup.bash; roslaunch turtlebot_rviz_launchers view_navigation.launch" &