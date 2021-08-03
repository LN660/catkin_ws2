#include <serial/serial.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include "cmath"
#include "ros/ros.h"
#include "sensor/radius_msgs.h"  //定义的消息类型记得修改
using namespace std;
const double Pi = 3.14159265358979;

int main(int argc, char** argv) {
  ros::init(argc, argv, "radius_driver");  //解析参数，命名节点
  ros::NodeHandle nh;                      //创建句柄，实例化node
  ros::NodeHandle private_nh("~");
  sensor::radius_msgs msg;  //创建消息
  serial::Serial sp;
  string _port;
  int _baud;
  private_nh.param("port", _port, std::string("/dev/ttyUSB2"));  //设置参数
  private_nh.param("baud", _baud, 9600);
  ros::Publisher pub =
      nh.advertise<sensor::radius_msgs>("raw_radius_data", 1);  //创建publisher
  ros::Rate loop_rate(10.0);  //定义循环发布的频率

  try {
    //设置要打开的串口名称
    sp.setPort(_port);
    //设置串口通信的波特率
    sp.setBaudrate(_baud);
    //窗口设置timeout
    serial::Timeout to = serial::Timeout::simpleTimeout(1000);
    sp.setTimeout(to);
    //打开串口
    sp.open();
  } catch (serial::IOException& e) {
    ROS_ERROR_STREAM("Unable to open port.");
    return -1;
  }
  //判断串口是否打开成功
  if (sp.isOpen()) {
    ROS_INFO_STREAM("radius sensor is opened.");

  } else {
    return -1;
  }

  string serial_buffer;

  while (ros::ok()) {
    if (sp.available()) {
      ROS_INFO_STREAM("Reading from serial port for radius_sensor");
      string t_serial_buffer("radius error");
      t_serial_buffer = sp.readline(60);
      //$RLS,ÀAAA.AA,ÀBBB.BB,S1,XXX.XXX,S2,HHHH*CC<CR><LF>
      size_t pos = t_serial_buffer.find("$RLS");
      if (pos != string::npos) {
        serial_buffer = t_serial_buffer.substr(pos);
        sscanf(serial_buffer.c_str(), "$RLS,%lf,%lf,%*c,%lf,%*c,%*u", &(msg.y),
               &(msg.x),  //
               &(msg.deg));
      }
      ROS_INFO(
          "publish radius_info:radius_x:%lf m  radius_y:%lf m  radius_deg:%lf",
          msg.x, msg.y, msg.deg);
      // double target_x = 10, target_y = 10, sensor_x = 20, sensor_y = 20;
      // msg.kp_x = sensor_x * cos(msg.deg / 180 * Pi) +
      //            sensor_y * sin(msg.deg / 180 * Pi) + msg.x + target_x;
      // msg.kp_y = sensor_y * cos(msg.deg / 180 * Pi) -
      //            sensor_x * sin(msg.deg / 180 * Pi) + msg.y + target_y;
      // msg.kp_deg = msg.deg;
      // ROS_INFO("trans radius_info:radius_x:%lf  radius_y:%lf  radius_deg:%lf
      // ",
      //          msg.kp_x, msg.kp_y, msg.kp_deg);

      pub.publish(msg);

    }
    ros::spinOnce();
    loop_rate.sleep();
     }
    return 0;
  }