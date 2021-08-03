// #include <sensor/conversions.h>
#include <std_msgs/Float64.h>
#include <cmath>
// #include <iostream>
// #include <string>
#include "ros/ros.h"
#include "sensor/gps.h"
// using namespace std;

double kputmx = 0, kputmy = 0, kpdeg = 0;
// int sample_num = 10;
std::vector<double> gpstime_array;
void kputmx_callback(const std_msgs::Float64 &msg) {
  kputmx = msg.data;
  // std::cout << "kputmx   " << kputmx << std::endl;
}
void kputmy_callback(const std_msgs::Float64 &msg) {
  kputmy = msg.data;
  // std::cout << "kputmy   " << kputmy << std::endl;
}
void kpdeg_callback(const std_msgs::Float64 &msg) {
  kpdeg = msg.data / M_PI * 180;
  // std::cout << "kpdeg   " << kpdeg << std::endl;
}

// void gpstime_callback(const std_msgs::Float64 &msg) {
//   gpstime = msg.data;
//   for (int i = 0; i < sample_num - 1; i++) {  // update the data of imu1
//   pitch
//     gpstime_array[sample_num - i - 1] = gpstime_array[sample_num - i - 2];
//   }
//   if (std::isnormal(gpstime))
//     gpstime_array[0] = gpstime;
//   else
//     gpstime_array[0] = gpstime_array[1];
// }
UTMalt tm(6378388, 1 / 297.0, 51, true);

int main(int argc, char **argv) {
  ros::init(argc, argv, "utm_tf");  //
  ros::NodeHandle n;
  ros::NodeHandle private_nh;  //
  ros::Publisher local_x_pub = n.advertise<std_msgs::Float64>("local_x", 1);
  ros::Publisher local_y_pub = n.advertise<std_msgs::Float64>("local_y", 1);
  ros::Publisher local_deg_pub = n.advertise<std_msgs::Float64>("local_deg", 1);

  // for (int i = 0; i < sample_num; i++)  //初始化
  // {
  //   gpstime_array.push_back(0);
  // }

  ros::Subscriber sub_utmx =
      n.subscribe("UTMx", 10, kputmx_callback);  //创建subscriber
  ros::Subscriber sub_utmy =
      n.subscribe("UTMy", 10, kputmy_callback);  //创建subscriber
  ros::Subscriber sub_deg =
      n.subscribe("imu_head", 2, kpdeg_callback);  //创建subscriber
  // ros::Subscriber sub_timestamp =
  // n.subscribe("gps_timestamp", 5, gpstime_callback);  //创建subscriber

  double topside_utmx = 0, topside_utmy = 0, topside_lat, topside_lon,
         topside_head, local_x = 0, local_y = 0, local_deg = 0;
  private_nh.getParam("topside_lat", topside_lat);
  private_nh.getParam("topside_lon", topside_lon);
  private_nh.getParam("topside_head", topside_head);
  int dd;
  double mm;
  dd = floor(topside_lat / 100);
  mm = topside_lat - 100 * dd;
  topside_lat = dd + mm / 60;
  dd = floor(topside_lon / 100);
  mm = topside_lon - 100 * dd;
  topside_lon = dd + mm / 60;
  std::cout << "topside_lat   " << topside_lat << std::endl;
  std::cout << "topside_lon   " << topside_lon << std::endl;
  std::cout << "topside_head   " << topside_head << std::endl;
  // gps_common::UTM(topside_lat, topside_lon, &topside_utmx, &topside_utmy);
  tm.Forward(topside_lat, topside_lon, topside_utmx, topside_utmy);
  ros::Rate loop_rate(1);
  while (ros::ok()) {
    std_msgs::Float64 msg1, msg2, msg3;
    std::cout << "kputmx   " << kputmx << std::endl;
    std::cout << "kputmy   " << kputmy << std::endl;
    // if (gpstime_array[0] == gpstime_array[sample_num - 1])
    //   ROS_INFO("GPS is disconnected");
    // std::cout << "topside_utmx   " << topside_utmx << std::endl;
    // std::cout << "topside_utmy   " << topside_utmy << std::endl;
    double topside_utmx_temp = 0, topside_utmy_temp = 0, objutmx = 0,
           objutmy = 0;
    topside_utmx_temp = topside_utmx, topside_utmy_temp = topside_utmy;
    objutmx = kputmx - topside_utmx_temp;
    objutmy = kputmy - topside_utmy_temp;
    std::cout << "objutmx   " << objutmx << std::endl;
    std::cout << "objutmy   " << objutmy << std::endl;
    std::cout << "topside_head   " << topside_head << std::endl;
    //得到utm坐标系的相对位置坐标，还差一步转换到导管架局部坐标系
    local_x = objutmx * cos(topside_head / 180 * M_PI) -
              objutmy * sin(topside_head / 180 * M_PI);
    local_y = objutmy * cos(topside_head / 180 * M_PI) +
              objutmx * sin(topside_head / 180 * M_PI);
    if (kpdeg >= topside_head) {
      local_deg = kpdeg - topside_head;
    } else
      local_deg = 360 - (topside_head - kpdeg);
    msg1.data = local_x;
    msg2.data = local_y;
    msg3.data = local_deg;
    local_x_pub.publish(msg1);
    local_y_pub.publish(msg2);
    local_deg_pub.publish(msg3);
    std::cout << "local_x   " << local_x << std::endl;
    std::cout << "local_y   " << local_y << std::endl;
    std::cout << "local_deg   " << local_deg << std::endl;
    ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
  }
