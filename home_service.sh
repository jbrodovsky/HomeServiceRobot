#!/bin/sh
echo "Add Markers Shell Script"
echo "Initializing and booting up ROS"
xterm -e "source /opt/ros/kinetic/setup.bash" &
xterm -e "source ./devel/setup.bash; roslaunch turtlebot_gazebo turtlebot_world.launch" &
sleep 10
echo "Booting up simulation environment"
xterm -e "source ./devel/setup.bash; roslaunch turtlebot_gazebo amcl_demo.launch" &
xterm -e "source ./devel/setup.bash; roslaunch add_markers moddedRviz.launch" &
sleep 15
echo "Booting up home service functions"
xterm -e "source ./devel/setup.bash; rosrun add_markers add_markers"&
xterm -e "source ./devel/setup.bash; rosrun pick_objects pick_objects"&