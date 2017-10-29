#include <ros/ros.h>
#include <motion_decoder/image_converter.hpp>
#include <apriltags_ros/AprilTagDetectionArray.h>
#include <apriltags_ros/AprilTagDetection.h>
#include <tf/transform_broadcaster.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/Quaternion.h>


ImageConverter* ic;

void apriltag_detection_callback(const apriltags_ros::AprilTagDetectionArray msg)
{
  
  //TODO: Parse message and publish transforms as apriltag_tf and camera
  if(msg.detections.size()>0){
    geometry_msgs::PoseStamped POSE = msg.detections[0].pose;
    ROS_INFO("In subscribe\n");
    static tf::TransformBroadcaster br;
    tf::Transform transform;
//call up fn from iamge converter
ic->setTagLocations(POSE.pose.position.x, POSE.pose.position.y, POSE.pose.position.z);

transform.setOrigin(tf::Vector3(POSE.pose.position.x, POSE.pose.position.y, POSE.pose.position.z));
transform.setRotation(tf::Quaternion(POSE.pose.orientation.x, POSE.pose.orientation.y, POSE.pose.orientation.z, POSE.pose.orientation.z));

    br.sendTransform(tf::StampedTransform(transform,ros::Time::now(), "camera", "april_tf"));

  }

  
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "image_converter");
  
  ros::NodeHandle n;
  //TODO: Add a subscriber to get the AprilTag detections The callback function skeleton is given.
  ros::Subscriber sub = n.subscribe("tag_detections",10,&apriltag_detection_callback);//check why 10 and not 1000
  ImageConverter converter;
  ic = &converter;
  ros::Rate loop_rate(50);
  ROS_INFO("In main\n");
  while(ros::ok()) {
    ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
}
