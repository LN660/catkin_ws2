
#include <sensor_msgs/NavSatFix.h>
#include <serial/serial.h>
#include <std_msgs/Float64.h>
#include <std_msgs/Float64MultiArray.h>
#include <std_msgs/String.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include "ros/ros.h"
#include "sensor/gps_msgs.h"  //定义的消息类型记得修改
using namespace std;

int main(int argc, char** argv) {
  ros::init(argc, argv, "gpsout_driver");  //解析参数，命名节点
  ros::NodeHandle nh;                      //创建句柄，实例化node
  ros::NodeHandle private_nh("~");
  std_msgs::Float64MultiArray gps_msg;  //创建消息
  gps_msg.data.push_back(0);
  gps_msg.data.push_back(0);
  serial::Serial gps_buffer;
  string _port;
  int _baud;
  private_nh.param("port", _port, std::string("/dev/ttyUSB0"));  //设置参数
  private_nh.param("baud", _baud, 57600);
  ros::Publisher pub = nh.advertise<std_msgs::Float64MultiArray>(
      "gps_out_data", 10);  //创建publisher
  ros::Publisher pub_timestamp =
      nh.advertise<std_msgs::Float64>("gps_timestamp", 10);
  ros::Rate loop_rate(50.0);  //定义循环发布的频率

  try {
    //设置要打开的串口名称
    gps_buffer.setPort(_port);
    //设置串口通信的波特率
    gps_buffer.setBaudrate(_baud);
    //窗口设置timeout
    serial::Timeout to = serial::Timeout::simpleTimeout(1000);
    gps_buffer.setTimeout(to);
    //打开串口
    gps_buffer.open();
  } catch (serial::IOException& e) {
    ROS_ERROR_STREAM("Unable to open gps_driver.");
    return -1;
  }
  //判断串口是否打开成功
  if (gps_buffer.isOpen()) {
    ROS_INFO_STREAM("gps_driver sensor is opened.");

  } else {
    return -1;
  }

  string serial_buffer;
  std_msgs::Float64 gps_timestamp;

  while (ros::ok()) {
    if (gps_buffer.available()) {
      // ROS_INFO_STREAM("Reading from serial port for gps_sensor");
      string t_serial_buffer("gps error");
      t_serial_buffer = gps_buffer.readline(100);
      //$GPGGA,134658.00,5106.9792,N,11402.3003,W,2,09,1.0,1048.47,M,-16.27,M,08,AAAA*60
      size_t pos = t_serial_buffer.find("$GPGGA");
      if (pos != string::npos) {
        serial_buffer = t_serial_buffer.substr(pos);
        // sscanf(serial_buffer.c_str(),
        //        "$GPGGA,%*f,%lf,%*c,%lf,%*c,%*d,%*d,%*f,%*f,%*c",
        //        &(gps_msg.data[0]), &(gps_msg.data[1]));
        sscanf(serial_buffer.c_str(),
               "$GPGGA,%lf,%lf,%*c,%lf,%*c,%*d,%*d,%*f,%*f,%*c",
               &gps_timestamp.data, &(gps_msg.data[0]), &(gps_msg.data[1]));
      }
      //转换成度分秒
      int dd;
      double mm;
      dd = floor(gps_msg.data[0] / 100);
      mm = gps_msg.data[0] - 100 * dd;
      gps_msg.data[0] = dd + mm / 60;
      dd = floor(gps_msg.data[1] / 100);
      mm = gps_msg.data[1] - 100 * dd;
      gps_msg.data[1] = dd + mm / 60;
      std::cout << "gps status" << gps_timestamp.data << std::endl;
      ROS_INFO("publish gps_info:gps_latitude:%lf  gps_longitude:%lf ",
               gps_msg.data[0], gps_msg.data[1]);
      pub.publish(gps_msg);
      pub_timestamp.publish(gps_timestamp);

    }
    ros::spinOnce();
    loop_rate.sleep();
     }
    return 0;
  }
