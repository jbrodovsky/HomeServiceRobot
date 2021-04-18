#!/bin/sh
echo "Add Markers Shell Script"
xterm -e "source /opt/ros/kinetic/setup.bash" &
xterm -e "source ./devel/setup.bash; roslaunch turtlebot_gazebo turtlebot_world.launch" &
sleep 10
xterm -e "source ./devel/setup.bash; roslaunch turtlebot_gazebo amcl_demo.launch" &
xterm -e "source ./devel/setup.bash; roslaunch add_markers moddedRviz.launch" &
sleep 5
xterm -e "source ./devel/setup.bash; rosrun add_markers add_markers"&