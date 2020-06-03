#include <ros/ros.h>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2_ros/transform_broadcaster.h>
#include <nav_msgs/Odometry.h>

void odomCallback(const nav_msgs::Odometry::ConstPtr& msg){
  static tf2_ros::TransformBroadcaster br;
  geometry_msgs::TransformStamped transformStamped;
  
  transformStamped.header.stamp = ros::Time::now();
  transformStamped.header.frame_id = "robot_odom";
  transformStamped.child_frame_id = "robot_base_footprint";
  transformStamped.transform.translation.x = msg->pose.pose.position.x;
  transformStamped.transform.translation.y = msg->pose.pose.position.y;
  transformStamped.transform.translation.z = 0.0;
  //tf2::Quaternion q;
  //q.setRPY(0, 0, msg->pose.pose.theta);
//   transformStamped.transform.rotation.x = q.x();
//   transformStamped.transform.rotation.y = q.y();
//   transformStamped.transform.rotation.z = q.z();
//   transformStamped.transform.rotation.w = q.w();
  transformStamped.transform.rotation.x = msg->pose.pose.orientation.x;
  transformStamped.transform.rotation.y = msg->pose.pose.orientation.y;
  transformStamped.transform.rotation.z = msg->pose.pose.orientation.z;
  transformStamped.transform.rotation.w = msg->pose.pose.orientation.w;

  br.sendTransform(transformStamped);
}

int main(int argc, char** argv){
  ros::init(argc, argv, "odom_frame_broadcaster");

//   ros::NodeHandle private_node("~");
//   if (! private_node.hasParam("turtle"))
//   {
//     if (argc != 2){ROS_ERROR("need turtle name as argument"); return -1;};
//     turtle_name = argv[1];
//   }
//   else
//   {
//     private_node.getParam("turtle", turtle_name);
//   }
    
  ros::NodeHandle node;
  ros::Subscriber sub = node.subscribe("/robot/robotnik_base_control/odom", 10, &odomCallback);

  ros::spin();
  return 0;
};