# HomeServiceRobot

## Project Description

This project is the capstone to the Robotics Software Engineering nanodegree and puts together all or
the previous projects in the form of a simulated “home service” robot. This is a type of domestic robot
that could be tasked with simple tasks in a two dimensional three degree of freedom configuration
space. Such tasks could be cleaning (vacuuming or mopping) floors, mowing grass, or simple cargo
transport (like taking grocery bags from the front door to the kitchen). This project tasks the student
with putting together several pre-made packages from ROS with two custom packages written by the
student to conduct SLAM and navigation. The task it to have a robot drive to a pick up location, simulate
loading or picking up an object, and transporting it to a drop off zone.

## Package Descriptions

This project includes six total packages: `gmapping`, `turtlebot_teleop`, `turtlebot_rviz_launchers`, `turtlebot_gazebo`, `pick_objects`, and `add_markers`. The first four are pre-built packages and the final two are built by the student.

### `gmapping`
`gmapping` is a simultaneous localization and mapping package for a robot equipped with a laser range finder or an RGB-D camera(s). This package creates the `slam_gmapping` node. This node takes a laser scan as input and builds a two dimensional occupancy grid map.

### `turtlebot_teleop`
`turtlebot_teleop` allows for the user to manually control the robot’s motion using the keyboard. It is used in this project to test and debug the SLAM and navigation packages.

### `turtlebot_rviz_launchers`
`turtlebot_rviz_launchers` provides preconfigured Rviz settings. Specifically, this project makes use of the `view_navigation.launch` file which displays the robot as well as tracks its planned path and global and local map.

### `turtlebot_gazebo`
`turtlebot_gazebo` contains several premade Gazebo based world environments for testing and
simulation. This project makes use of the `turtlebot_world.launch` Gazebo world.

### `pick_objects`
The `pick_objects` package implements the `pick_objects` node. This node is used to direct the object to a predetermined point, in this case the pickup and drop off locations in the environment. This node uses the `MoveBaseAction` message to publish goal locations for the robot to drive towards. When the robot first reaches the pickup zone, it then pauses for five seconds to simulate a cargo pickup. After the pause, it then drives to the drop off zone by publishing a second `MoveBaseAction` message containing the new coordinates.

### `add_markers`
The `add_markers` package implements the `add_markers` node that simulates both waypoint markers for the robot to follow, and a “virtual object” for the robot to pick up and drop off. This node makes use of the visualization messages `Marker` class in ROS to publish a virtual object visible in Rviz. Similarly to the `pick_objects` node, this marker is displayed in the pick up zone while the robot is not within it (representing both a navigational waypoint and simulated cargo). Once reached, the marker is hidden while the simulated loading occurs. After being “loaded,” the marker is published with new coordinates representing a navigational waypoint in the drop off zone. Once the drop off zone is
reached the marker is removed as the mission is complete.

## Conclusion

This project tied together all the topics learned throughout this course. ROS was successfully used to
build a comprehensive package to navigate robot through a planar three degree of freedom
environment. The custom nodes for programming robot behavior were successfully incorporated
alongside the prebuilt nodes for SLAM and navigation.
