#include <ros/ros.h>
// #include <sensor/conversions.h>
#include <sensor/gps_msgs.h>
#include <std_msgs/Float64MultiArray.h>
#include <iostream>
#include "sensor/gps.h"

ros::Publisher pub_gps;
std_msgs::Float64MultiArray raw_gps_data;
sensor::gps_msgs gps_data;
// raw_gps_data.data.push_back(0);
// raw_gps_data.data.push_back(0);
// raw_gps_data.data.push_back(0);
// raw_gps_data.data.push_back(0);
UTMalt tm(6378388, 1 / 297.0, 51, true);

void gps_callback(const std_msgs::Float64MultiArray& msg)
{
  // ROS_INFO_STREAM("ROS_GET_INFO2");
  // raw_gps_data.stamp = ros::Time::now();
  if (std::isnormal(msg.data[0]) && std::isnormal(msg.data[1]))
  {
    raw_gps_data.data[0] = msg.data[0];
    raw_gps_data.data[1] = msg.data[1];

    // gps_common::UTM(raw_gps_data.data[0], raw_gps_data.data[1],
    // &raw_gps_data.data[2], &raw_gps_data.data[3]);
    tm.Forward(raw_gps_data.data[0], raw_gps_data.data[1], raw_gps_data.data[2], raw_gps_data.data[3]);
  }
  else
  {
    raw_gps_data.data[0] = 0;
    raw_gps_data.data[1] = 0;

    raw_gps_data.data[2] = 0;
    raw_gps_data.data[3] = 0;
  }

  gps_data.latitude = raw_gps_data.data[0];
  gps_data.longitude = raw_gps_data.data[1];
  gps_data.UTMx = raw_gps_data.data[2];
  gps_data.UTMy = raw_gps_data.data[3];

  // std::cout << "altitude: \n" << gps_data.latitude << std::endl;

  ROS_INFO("publish gps_info:gps_latitude:%lf  gps_longitude:%lf utmx:%lf  "
           "utmy:%lf ",
           gps_data.latitude, gps_data.longitude, gps_data.UTMx, gps_data.UTMy);
  pub_gps.publish(gps_data);
}

int main(int argv, char** argc)
{
  ros::init(argv, argc, "gps_driver");
  ros::NodeHandle n;
  ros::NodeHandle private_nh("~");
  std::string topic_name_sub;
  private_nh.param("topic_name_sub", topic_name_sub, std::string("gps_out_data"));
  // ROS_INFO_STREAM("ROS_GET_INFO1");
  ros::Subscriber sub_gps1 = n.subscribe(topic_name_sub, 1, gps_callback);
  raw_gps_data.data.push_back(0);
  raw_gps_data.data.push_back(0);
  raw_gps_data.data.push_back(0);
  raw_gps_data.data.push_back(0);
  pub_gps = n.advertise<sensor::gps_msgs>("raw_gps_data", 10);
  ros::spin();
  return 0;
}
