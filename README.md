# Motion-Decoder
Tracks the movement of an april tag in image and plots small circles in its path. PLots the trajectory hector on RVIZ.

1. Install ROS Indigo
2. Install and make a catkin workspace
3. Clone this repo inside src folder in catkin workspace
4. At root of catkin workspace run:

catkin_make
source devel/setup.bash
roslaunch motion_decoder motion_decoder.launch 

This will run the motion encoder from fixed camera frame. Alternately, to run motion encoder from moivng camera frame, run:

roslaunch motion_decoder motion_decoder_camera.launch 

5. In another terminal run 
roscore
6. To run RVIZ, open a third terminal and type 
rviz 
7. Create a new path, and while the launch file is running, select topic 'trajectory' under path and fixed frame as the required frame ('april_tf'/'camera')

