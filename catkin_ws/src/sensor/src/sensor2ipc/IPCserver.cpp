/*
***********************************************************************
* OSsever.cpp: 订阅对应的话题消息并转发给其他的船舶
* This header file can be read by C++ compilers
* 主函数包括三大部分:一、实例化数据结构，对话题数据进行回调订阅，
* 三、创建OSserver对象,并调用函数senddata2others将数据打包成一个string
*by SJTU LN
***********************************************************************
*/

#include "sensor/IPCserver.h"
#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <std_msgs/Float64MultiArray.h>
#include <stdio.h>
#include <string.h>
#include <cmath>
#include <sstream>
#include "std_msgs/String.h"
// 初始化结构体
//发送出去的
// 列表中1-6的数据
cyscanRTdata _cyscanRTdata_1{
    22.11,  // cyscan_x;    // m
    11.22,  // cyscan_y;    // m
    50,     // cyscan_deg;  // deg
    0.5,    // cyscan_weight;
    1,      // cyscan_ready;  // 0,1
    0,      // cyscan_alarm;  // 0,1
};
// 列表中7-12的数据
cyscanRTdata _cyscanRTdata_2{
    22.13,  // cyscan_x;    // m
    11.25,  // cyscan_y;    // m
    50,     // cyscan_deg;  // deg
    0.5,    // cyscan_weight;
    1,      // cyscan_ready;  // 0,1
    0,      // cyscan_alarm;  // 0,1
};
// 列表中13-18的数据
radiusRTdata _radiusRTdata_1{
    22.17,  // cyscan_x;    // m
    11.29,  // cyscan_y;    // m
    51,     // cyscan_deg;  // deg
    0.3,    // cyscan_weight;
    1,      // cyscan_ready;  // 0,1
    0,      // cyscan_alarm;  // 0,1
};
// 列表中19-24的数据
radiusRTdata _radiusRTdata_2{
    22.19,  // cyscan_x;    // m
    11.39,  // cyscan_y;    // m
    51,     // cyscan_deg;  // deg
    0.3,    // cyscan_weight;
    1,      // cyscan_ready;  // 0,1
    0,      // cyscan_alarm;  // 0,1
};
// 列表中25-34的数据
gpsRTdata _gpsRTdata_1{
    3100.1111,   // latitude
    'N',         // latitude_hemisphere,N,S
    12100.1111,  // longgitude
    'E',         // longitude_hemisphereE,W
    1,           // status
    9,           // num_NVS
    0,           // altitude
    0.3,         // weight_GPS
    1,           // ready_GPS
    0,           // Alarm_GPS
};

//列表中35-44号数据
gpsRTdata _gpsRTdata_2{
    3100.2222,   // latitude
    'N',         // latitude_hemisphere,N,S
    12100.2222,  // longgitude
    'E',         // longitude_hemisphereE,W
    1,           // status
    8,           // num_NVS
    0,           // altitude
    0.3,         // weight_GPS
    1,           // ready_GPS
    0,           // Alarm_GPS
};

//列表中45-54号数据
gpsRTdata _gpsRTdata_3{
    3100.3333,   // latitude
    'N',         // latitude_hemisphere,N,S
    12100.3333,  // longgitude
    'E',         // longitude_hemisphereE,W
    1,           // status
    7,           // num_NVS
    0,           // altitude
    0.4,         // weight_GPS
    1,           // ready_GPS
    0,           // Alarm_GPS
};

//列表中55-58号数据
gyroRTdata _gyroRTdata_1{
    0,    // double heading;
    0.5,  // double weight_Gyro;
    1,    // int ready_Gyro;
    0,    // int Alarm_Gyro;
};
//列表中59-62号数据
gyroRTdata _gyroRTdata_2{
    0,    // double heading;
    0.5,  // double weight_gyro;
    1,    // int ready_gyro;
    0,    // int Alarm_gyro;
};
//列表中63-66号数据
gyroRTdata _gyroRTdata_3{
    0,  // double heading;
    0,  // double weight_gyro;
    1,  // int ready_gyro;
    0,  // int Alarm_gyro;

};
// 列表中67-71号数据
VRURTdata _VRURTdata_1{
    4,     //  double roll; //+-
    5,     // double pitch;
    0.35,  // double weight_VRU;
    1,     // double ready_VRU;
    0,     // double Alarm_VRU;
};
//列表中70-75号数据
VRURTdata _VRURTdata_2{
    6,     //  double roll; //+-
    7,     // double pitch;
    0.65,  // double weight_VRU;
    1,     // double ready_VRU;
    0,     // double Alarm_VRU;
};
//列表中76-81号数据
VRURTdata _VRURTdata_3{
    3,  //  double roll; //+-
    5,  // double pitch;
    0,  // double weight_VRU;
    1,  // double ready_VRU;
    0,  // double Alarm_VRU;
};

//列表中82-88数据
fusiondata _fusiondata{
    0,  // roll_fusion
    0,  // pitch_fusion
    0,  // kpoint_x_fusion
    0,  // kpoint_y_fusion
    0,  // kpoint_deg_fusion
    0,  // NEkpoint_x_fusion
    0,  // NEkpoint_y_fusion

};
// 列表中89-91的数据
vesselState _vesselState{
    5,    //   double vessel_velocity; // Knot
    0,    //  double vessel_heading;
    0.3,  // vessel_speed_heading;
};
// 系统的信息最后不一定在这里传递
// systemInfo _systemInfo{
//     1,  // wlan
//     0,  //   double time;
//     1,  //   int all_ready;
// };
// double getNowTime() {
//   double timestring;
//   double tmp;
//   time_t tt;
//   time(&tt);
//   tt = tt + 8 * 3600;  // transform the time zone
//   tm *t = gmtime(&tt);
//   // std::cout << tt << std::endl;
//   // printf("%d-%02d-%02d %02d:%02d:%02d\n",
//   //        t->tm_year + 1900,
//   //        t->tm_mon + 1,
//   //        t->tm_mday,
//   //        t->tm_hour,
//   //        t->tm_min,
//   //        t->tm_sec);

//   timestring = t->tm_sec + t->tm_min * 100 + t->tm_hour * 10000 +
//                t->tm_mday * 1000000 + (t->tm_mon + 1) * 100000000 +
//                (t->tm_year + 1900) * 10000000000;
//   return timestring;
// }
//怎么去掉timestring后面的小数

////////////回调
// 回调1-6号的数据 cyscanRTdata
void cyscan_1_x_Callback(const std_msgs::Float64::ConstPtr &msg) {
  _cyscanRTdata_1.cyscan_x = msg->data;
}
void cyscan_1_y_Callback(const std_msgs::Float64::ConstPtr &msg) {
  _cyscanRTdata_1.cyscan_x = msg->data;
}
void cyscan_1_deg_Callback(const std_msgs::Float64::ConstPtr &msg) {
  _cyscanRTdata_1.cyscan_x = msg->data;
}
void cyscan_1_weight_Callback(const std_msgs::Float64::ConstPtr &msg) {
  _cyscanRTdata_1.cyscan_x = msg->data;
}
void cyscan_1_ready_Callback(const std_msgs::Float64::ConstPtr &msg) {
  _cyscanRTdata_1.cyscan_x = msg->data;
}
void cyscan_1_alarm_Callback(const std_msgs::Float64::ConstPtr &msg) {
  _cyscanRTdata_1.cyscan_x = msg->data;
}
// 回调7-12的数据
void cyscan_2_x_Callback(const std_msgs::Float64::ConstPtr &msg) {
  _cyscanRTdata_2.cyscan_x = msg->data;
}
void cyscan_2_y_Callback(const std_msgs::Float64::ConstPtr &msg) {
  _cyscanRTdata_2.cyscan_x = msg->data;
}
void cyscan_2_deg_Callback(const std_msgs::Float64::ConstPtr &msg) {
  _cyscanRTdata_2.cyscan_x = msg->data;
}
void cyscan_2_weight_Callback(const std_msgs::Float64::ConstPtr &msg) {
  _cyscanRTdata_2.cyscan_x = msg->data;
}
void cyscan_2_ready_Callback(const std_msgs::Float64::ConstPtr &msg) {
  _cyscanRTdata_2.cyscan_x = msg->data;
}
void cyscan_2_alarm_Callback(const std_msgs::Float64::ConstPtr &msg) {
  _cyscanRTdata_2.cyscan_x = msg->data;
}
// 回调13-18号的数据 cyscanRTdata
void radius_1_x_Callback(const std_msgs::Float64::ConstPtr &msg) {
  _radiusRTdata_1.radius_x = msg->data;
}
void radius_1_y_Callback(const std_msgs::Float64::ConstPtr &msg) {
  _radiusRTdata_1.radius_x = msg->data;
}
void radius_1_deg_Callback(const std_msgs::Float64::ConstPtr &msg) {
  _radiusRTdata_1.radius_x = msg->data;
}
void radius_1_weight_Callback(const std_msgs::Float64::ConstPtr &msg) {
  _radiusRTdata_1.radius_x = msg->data;
}
void radius_1_ready_Callback(const std_msgs::Float64::ConstPtr &msg) {
  _radiusRTdata_1.radius_x = msg->data;
}
void radius_1_alarm_Callback(const std_msgs::Float64::ConstPtr &msg) {
  _radiusRTdata_1.radius_x = msg->data;
}
// 回调19-24的数据
void radius_2_x_Callback(const std_msgs::Float64::ConstPtr &msg) {
  _radiusRTdata_2.radius_x = msg->data;
}
void radius_2_y_Callback(const std_msgs::Float64::ConstPtr &msg) {
  _radiusRTdata_2.radius_x = msg->data;
}
void radius_2_deg_Callback(const std_msgs::Float64::ConstPtr &msg) {
  _radiusRTdata_2.radius_x = msg->data;
}
void radius_2_weight_Callback(const std_msgs::Float64::ConstPtr &msg) {
  _radiusRTdata_2.radius_x = msg->data;
}
void radius_2_ready_Callback(const std_msgs::Float64::ConstPtr &msg) {
  _radiusRTdata_2.radius_x = msg->data;
}
void radius_2_alarm_Callback(const std_msgs::Float64::ConstPtr &msg) {
  _radiusRTdata_2.radius_x = msg->data;
}

// 回调25-34的数据
void gps_1_latitude_Callback(const std_msgs::Float64::ConstPtr &msg) {
  _gpsRTdata_1.latitude = msg->data;
}
void gps_1_longitude_Callback(const std_msgs::Float64::ConstPtr &msg) {
  _gpsRTdata_1.longitude = msg->data;
}
void gps_1_status_Callback(const std_msgs::Float64::ConstPtr &msg) {
  _gpsRTdata_1.status = msg->data;
}
void gps_1_num_NVS_Callback(const std_msgs::Float64::ConstPtr &msg) {
  _gpsRTdata_1.num_NVS = msg->data;
}
void gps_1_altitude_Callback(const std_msgs::Float64::ConstPtr &msg) {
  _gpsRTdata_1.altitude = msg->data;
}
void gps_1_weight_GPS_Callback(const std_msgs::Float64::ConstPtr &msg) {
  _gpsRTdata_1.weight_GPS = msg->data;
}
void gps_1_ready_GPS_Callback(const std_msgs::Float64::ConstPtr &msg) {
  _gpsRTdata_1.ready_GPS = msg->data;
}
void gps_1_Alarm_GPS_Callback(const std_msgs::Float64::ConstPtr &msg) {
  _gpsRTdata_1.Alarm_GPS = msg->data;
}

// 回调35-44的数据

void gps_2_latitude_Callback(const std_msgs::Float64::ConstPtr &msg) {
  _gpsRTdata_2.latitude = msg->data;
}
void gps_2_longitude_Callback(const std_msgs::Float64::ConstPtr &msg) {
  _gpsRTdata_2.longitude = msg->data;
}
void gps_2_status_Callback(const std_msgs::Float64::ConstPtr &msg) {
  _gpsRTdata_2.status = msg->data;
}
void gps_2_num_NVS_Callback(const std_msgs::Float64::ConstPtr &msg) {
  _gpsRTdata_2.num_NVS = msg->data;
}
void gps_2_altitude_Callback(const std_msgs::Float64::ConstPtr &msg) {
  _gpsRTdata_2.altitude = msg->data;
}
void gps_2_weight_GPS_Callback(const std_msgs::Float64::ConstPtr &msg) {
  _gpsRTdata_2.weight_GPS = msg->data;
}
void gps_2_ready_GPS_Callback(const std_msgs::Float64::ConstPtr &msg) {
  _gpsRTdata_2.ready_GPS = msg->data;
}
void gps_2_Alarm_GPS_Callback(const std_msgs::Float64::ConstPtr &msg) {
  _gpsRTdata_2.Alarm_GPS = msg->data;
}

// 回调45-54的数据

void gps_3_latitude_Callback(const std_msgs::Float64::ConstPtr &msg) {
  _gpsRTdata_3.latitude = msg->data;
}
void gps_3_longitude_Callback(const std_msgs::Float64::ConstPtr &msg) {
  _gpsRTdata_3.longitude = msg->data;
}
void gps_3_status_Callback(const std_msgs::Float64::ConstPtr &msg) {
  _gpsRTdata_3.status = msg->data;
}
void gps_3_num_NVS_Callback(const std_msgs::Float64::ConstPtr &msg) {
  _gpsRTdata_3.num_NVS = msg->data;
}
void gps_3_altitude_Callback(const std_msgs::Float64::ConstPtr &msg) {
  _gpsRTdata_3.altitude = msg->data;
}
void gps_3_weight_GPS_Callback(const std_msgs::Float64::ConstPtr &msg) {
  _gpsRTdata_3.weight_GPS = msg->data;
}
void gps_3_ready_GPS_Callback(const std_msgs::Float64::ConstPtr &msg) {
  _gpsRTdata_3.ready_GPS = msg->data;
}
void gps_3_Alarm_GPS_Callback(const std_msgs::Float64::ConstPtr &msg) {
  _gpsRTdata_3.Alarm_GPS = msg->data;
}

// //    回调55-58号数据

void gyro_1_heading_Callback(const std_msgs::Float64::ConstPtr &msg) {
  _gyroRTdata_1.heading = (msg->data);
}

void gyro_1_weight_gyro_Callback(const std_msgs::Float64::ConstPtr &msg) {
  _gyroRTdata_1.weight_Gyro = msg->data;
}
void gyro_1_ready_gyro_Callback(const std_msgs::Float64::ConstPtr &msg) {
  _gyroRTdata_1.ready_Gyro = msg->data;
}

void gyro_1_Alarm_gyro_Callback(const std_msgs::Float64::ConstPtr &msg) {
  _gyroRTdata_1.Alarm_Gyro = msg->data;
}

// //回调59-62数据
void gyro_2_heading_Callback(const std_msgs::Float64::ConstPtr &msg) {
  _gyroRTdata_2.heading = msg->data;
}

void gyro_2_weight_gyro_Callback(const std_msgs::Float64::ConstPtr &msg) {
  _gyroRTdata_2.weight_Gyro = msg->data;
}
void gyro_2_ready_gyro_Callback(const std_msgs::Float64::ConstPtr &msg) {
  _gyroRTdata_2.ready_Gyro = msg->data;
}

void gyro_2_Alarm_gyro_Callback(const std_msgs::Float64::ConstPtr &msg) {
  _gyroRTdata_2.Alarm_Gyro = msg->data;
}

// 回调63-66数据

void gyro_3_heading_Callback(const std_msgs::Float64::ConstPtr &msg) {
  _gyroRTdata_3.heading = msg->data;
}

void gyro_3_weight_gyro_Callback(const std_msgs::Float64::ConstPtr &msg) {
  _gyroRTdata_3.weight_Gyro = msg->data;
}
void gyro_3_ready_gyro_Callback(const std_msgs::Float64::ConstPtr &msg) {
  _gyroRTdata_3.ready_Gyro = msg->data;
}

void gyro_3_Alarm_gyro_Callback(const std_msgs::Float64::ConstPtr &msg) {
  _gyroRTdata_3.Alarm_Gyro = msg->data;
}

// //回调67-71
void VRU_1_roll_Callback(const std_msgs::Float64::ConstPtr &msg) {
  _VRURTdata_1.roll = msg->data;
}
void VRU_1_pitch_Callback(const std_msgs::Float64::ConstPtr &msg) {
  _VRURTdata_1.pitch = msg->data;
}
void VRU_1_weight_VRU_Callback(const std_msgs::Float64::ConstPtr &msg) {
  _VRURTdata_1.weight_VRU = msg->data;
}
void VRU_1_ready_VRU_Callback(const std_msgs::Float64::ConstPtr &msg) {
  _VRURTdata_1.ready_VRU = msg->data;
}
void VRU_1_Alarm_VRU_Callback(const std_msgs::Float64::ConstPtr &msg) {
  _VRURTdata_1.Alarm_VRU = msg->data;
}

// //回调72-76
void VRU_2_roll_Callback(const std_msgs::Float64::ConstPtr &msg) {
  _VRURTdata_2.roll = msg->data;
}
void VRU_2_pitch_Callback(const std_msgs::Float64::ConstPtr &msg) {
  _VRURTdata_2.pitch = msg->data;
}
void VRU_2_weight_VRU_Callback(const std_msgs::Float64::ConstPtr &msg) {
  _VRURTdata_2.weight_VRU = msg->data;
}
void VRU_2_ready_VRU_Callback(const std_msgs::Float64::ConstPtr &msg) {
  _VRURTdata_2.ready_VRU = msg->data;
}
void VRU_2_Alarm_VRU_Callback(const std_msgs::Float64::ConstPtr &msg) {
  _VRURTdata_2.Alarm_VRU = msg->data;
}

//回调77-81

void VRU_3_roll_Callback(const std_msgs::Float64::ConstPtr &msg) {
  _VRURTdata_3.roll = msg->data;
}
void VRU_3_pitch_Callback(const std_msgs::Float64::ConstPtr &msg) {
  _VRURTdata_3.pitch = msg->data;
}
void VRU_3_weight_VRU_Callback(const std_msgs::Float64::ConstPtr &msg) {
  _VRURTdata_3.weight_VRU = msg->data;
}
void VRU_3_ready_VRU_Callback(const std_msgs::Float64::ConstPtr &msg) {
  _VRURTdata_3.ready_VRU = msg->data;
}
void VRU_3_Alarm_VRU_Callback(const std_msgs::Float64::ConstPtr &msg) {
  _VRURTdata_3.Alarm_VRU = msg->data;
}
// 回调82-88
void fusiondata_roll_Callback(const std_msgs::Float64::ConstPtr &msg) {
  _fusiondata.roll_fusion = msg->data;
}
void fusiondata_pitch_Callback(const std_msgs::Float64::ConstPtr &msg) {
  _fusiondata.pitch_fusion = msg->data;
}
void fusiondata_kpoint_x_Callback(const std_msgs::Float64::ConstPtr &msg) {
  _fusiondata.kpoint_x_fusion = msg->data;
}
void fusiondata_kpoint_y_Callback(const std_msgs::Float64::ConstPtr &msg) {
  _fusiondata.kpoint_y_fusion = msg->data;
}
void fusiondata_kpoint_deg_Callback(const std_msgs::Float64::ConstPtr &msg) {
  _fusiondata.kpoint_deg_fusion = msg->data;
}
void fusiondata_NEkpoint_x_Callback(const std_msgs::Float64::ConstPtr &msg) {
  _fusiondata.NEkpoint_x_fusion = msg->data;
}
void fusiondata_NEkpoint_y_Callback(const std_msgs::Float64::ConstPtr &msg) {
  _fusiondata.NEkpoint_y_fusion = msg->data;
}
// 89-91 的数据
void vesselState_vessel_velocity_Callback(
    const std_msgs::Float64::ConstPtr &msg) {
  _vesselState.vessel_velocity = msg->data;
}
void vesselState_vessel_heading_Callback(
    const std_msgs::Float64::ConstPtr &msg) {
  _vesselState.vessel_heading = (msg->data);
}
void vesselState_speed_heading_Callback(
    const std_msgs::Float64::ConstPtr &msg) {
  _vesselState.vessel_speed_heading = (msg->data);
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "sensordata2ipc");
  ros::NodeHandle nh;

  IPCserver _IPCserver;
  std::string buffer_trans;
  char bufsend[1280] = {0};
  // 将订阅到的信息进行发布
  std_msgs::String msg;
  // std::string buffer;
  ros::Publisher shipdata_pub = nh.advertise<std_msgs::String>("ship1_data", 5);

  //////////////////////////////////////////////////////////需要完善的
  //订阅需要的消息
  // cyscan_1 横坐标、纵坐标、船艏倾角
  ros::Subscriber sub_cyscan_1_x =
      nh.subscribe("/cyscan1/raw_cyscan_data", 1, cyscan_1_x_Callback);

  ros::Subscriber sub_cyscan_1_y =
      nh.subscribe("/cyscan1/raw_cyscan_data", 1, cyscan_1_y_Callback);
  ros::Subscriber sub_cyscan_1_deg =
      nh.subscribe("/cyscan1/raw_cyscan_data", 1, cyscan_1_deg_Callback);
  // ros::Subscriber sub_cyscan_1_weight =
  //     nh.subscribe("/cyscan1/raw_cyscan_data", 1, cyscan_1_weight_Callback);
  // ros::Subscriber sub_cyscan_1_ready =
  //     nh.subscribe("/cyscan1/raw_cyscan_data", 1, cyscan_1_ready_Callback);
  // ros::Subscriber sub_cyscan_1_alarm =
  //     nh.subscribe("/cyscan1/raw_cyscan_data", 1, cyscan_1_alarm_Callback);

  // cyscan_2 横坐标、纵坐标、船艏倾角
  ros::Subscriber sub_cyscan_2_x =
      nh.subscribe("/cyscan2/raw_cyscan_data", 1, cyscan_2_x_Callback);

  ros::Subscriber sub_cyscan_2_y =
      nh.subscribe("/cyscan2/raw_cyscan_data", 1, cyscan_2_y_Callback);
  ros::Subscriber sub_cyscan_2_deg =
      nh.subscribe("/cyscan2/raw_cyscan_data", 1, cyscan_2_deg_Callback);
  // ros::Subscriber sub_cyscan_2_weight =
  //     nh.subscribe("/cyscan2/raw_cyscan_data", 1, cyscan_2_weight_Callback);
  // ros::Subscriber sub_cyscan_2_ready =
  //     nh.subscribe("/cyscan2/raw_cyscan_data", 1, cyscan_2_ready_Callback);
  // ros::Subscriber sub_cyscan_2_alarm =
  //     nh.subscribe("/cyscan2/raw_cyscan_data", 1, cyscan_2_alarm_Callback);

  // radius_1 横坐标、纵坐标、船艏倾角
  ros::Subscriber sub_radius_1_x =
      nh.subscribe("/radius1/raw_radius_data", 1, radius_1_x_Callback);

  ros::Subscriber sub_radius_1_y =
      nh.subscribe("/radius1/raw_radius_data", 1, radius_1_y_Callback);
  ros::Subscriber sub_radius_1_deg =
      nh.subscribe("/radius1/raw_radius_data", 1, radius_1_deg_Callback);
  ros::Subscriber sub_radius_1_weight =
      nh.subscribe("/radius1/raw_radius_data", 1, radius_1_weight_Callback);
  ros::Subscriber sub_radius_1_ready =
      nh.subscribe("/radius1/raw_radius_data", 1, radius_1_ready_Callback);
  ros::Subscriber sub_radius_1_alarm =
      nh.subscribe("/radius1/raw_radius_data", 1, radius_1_alarm_Callback);

  // radius_2 横坐标、纵坐标、船艏倾角
  ros::Subscriber sub_radius_2_x =
      nh.subscribe("/radius2/raw_radius_data", 1, radius_2_x_Callback);

  ros::Subscriber sub_radius_2_y =
      nh.subscribe("/radius2/raw_radius_data", 1, radius_2_y_Callback);
  ros::Subscriber sub_radius_2_deg =
      nh.subscribe("/radius2/raw_radius_data", 1, radius_2_deg_Callback);
  ros::Subscriber sub_radius_2_weight =
      nh.subscribe("/radius2/raw_radius_data", 1, radius_2_weight_Callback);
  ros::Subscriber sub_radius_2_ready =
      nh.subscribe("/radius2/raw_radius_data", 1, radius_2_ready_Callback);
  ros::Subscriber sub_radius_2_alarm =
      nh.subscribe("/radius2/raw_radius_data", 1, radius_2_alarm_Callback);

  // GPS_1 纬度、经度
  ros::Subscriber sub_gps_1_lat =
      nh.subscribe("/gps1/raw_gps_data", 1, gps_1_latitude_Callback);
  ros::Subscriber sub_gps_1_lon =
      nh.subscribe("/gps1/raw_gps_data", 1, gps_1_longitude_Callback);
  // ros::Subscriber sub_gps_1_status =
  //     nh.subscribe("/gps1/raw_gps_data", 1, gps_1_status_Callback);
  // ros::Subscriber sub_gps_1_num_NVS =
  //     nh.subscribe("/gps1/raw_gps_data", 1,
  //     gps_1_num_NVS_Callback);
  // ros::Subscriber sub_gps_1_alti =
  //     nh.subscribe("/gps1/raw_gps_data", 1, gps_1_altitude_Callback);
  // ros::Subscriber sub_gps_1_weight =
  //     nh.subscribe("/gps1/raw_gps_data", 1,
  //     gps_1_weight_GPS_Callback);
  // ros::Subscriber sub_gps_1_ready =
  //     nh.subscribe("/gps1/raw_gps_data", 1,
  //     gps_1_ready_GPS_Callback);
  // ros::Subscriber sub_gps_1_Alarm =
  //     nh.subscribe("/gps1/raw_gps_data", 1,
  //     gps_1_Alarm_GPS_Callback);

  // GPS_2 纬度、经度
  ros::Subscriber sub_gps_2_lat =
      nh.subscribe("/gps2/raw_gps_data", 1, gps_2_latitude_Callback);
  ros::Subscriber sub_gps_2_lon =
      nh.subscribe("/gps2/raw_gps_data", 1, gps_2_longitude_Callback);
  // ros::Subscriber sub_gps_2_status =
  //     nh.subscribe("/gps2/raw_gps_data", 1, gps_2_status_Callback);
  // ros::Subscriber sub_gps_2_num_NVS =
  //     nh.subscribe("/gps2/raw_gps_data", 1,
  //     gps_2_num_NVS_Callback);
  // ros::Subscriber sub_gps_2_alti =
  //     nh.subscribe("/gps2/raw_gps_data", 1, gps_2_altitude_Callback);
  // ros::Subscriber sub_gps_2_weight =
  //     nh.subscribe("/gps2/raw_gps_data", 1,
  //     gps_2_weight_GPS_Callback);
  // ros::Subscriber sub_gps_2_ready =
  //     nh.subscribe("/gps2/raw_gps_data", 1,
  //     gps_2_ready_GPS_Callback);
  // ros::Subscriber sub_gps_2_Alarm =
  //     nh.subscribe("/gps2/raw_gps_data", 1,
  //     gps_2_Alarm_GPS_Callback);

  // GPS_3 纬度、经度
  ros::Subscriber sub_gps_3_lat =
      nh.subscribe("/gps3/raw_gps_data", 1, gps_3_latitude_Callback);
  ros::Subscriber sub_gps_3_lon =
      nh.subscribe("/gps3/raw_gps_data", 1, gps_3_longitude_Callback);
  // ros::Subscriber sub_gps_3_status =
  //     nh.subscribe("/gps3/raw_gps_data", 1, gps_3_status_Callback);
  // ros::Subscriber sub_gps_3_num_NVS =
  //     nh.subscribe("/gps3/raw_gps_data", 1,
  //     gps_3_num_NVS_Callback);
  // ros::Subscriber sub_gps_3_alti =
  //     nh.subscribe("/gps3/raw_gps_data", 1, gps_3_altitude_Callback);
  // // ros::Subscriber sub_gps_3_weight =
  //     nh.subscribe("/gps3/raw_gps_data", 1,
  //     gps_3_weight_GPS_Callback);
  // ros::Subscriber sub_gps_3_ready =
  //     nh.subscribe("/gps3/raw_gps_data", 1,
  //     gps_3_ready_GPS_Callback);
  // ros::Subscriber sub_gps_3_Alarm =
  //     nh.subscribe("/gps3/raw_gps_data", 1,
  //     gps_3_Alarm_GPS_Callback);

  // Gyro_1
  ros::Subscriber sub_gyro_1_heading =
      nh.subscribe("/imu1/raw_imu", 1, gyro_1_heading_Callback);
  // ros::Subscriber sub_gyro_1_weight = nh.subscribe(
  //     "/imu1/raw_imu", 1, gyro_1_weight_Gyro_Callback);
  // ros::Subscriber sub_gyro_1_ready = nh.subscribe(
  //     "/imu1/raw_imu", 1, gyro_1_ready_Gyro_Callback);
  // ros::Subscriber sub_gyro_1_Alarm = nh.subscribe(
  //     "/imu1/raw_imu", 1, gyro_1_Alarm_Gyro_Callback);

  // Gyro_2
  ros::Subscriber sub_gyro_2_heading =
      nh.subscribe("/imu2/raw_imu", 1, gyro_2_heading_Callback);
  // ros::Subscriber sub_gyro_2_weight = nh.subscribe(
  //     "/imu2/raw_imu", 1, gyro_2_weight_Gyro_Callback);
  // ros::Subscriber sub_gyro_2_ready = nh.subscribe(
  //     "/imu2/raw_imu", 1, gyro_2_ready_Gyro_Callback);
  // ros::Subscriber sub_gyro_2_Alarm = nh.subscribe(
  //     "/imu2/raw_imu", 1, gyro_2_Alarm_Gyro_Callback);
  // gyro_3
  ros::Subscriber sub_gyro_3_heading =
      nh.subscribe("/imu3/raw_imu", 1, gyro_3_heading_Callback);
  // ros::Subscriber sub_gyro_3_weight = nh.subscribe(
  //     "/imu3/raw_imu", 1, gyro_3_weight_Gyro_Callback);
  // ros::Subscriber sub_gyro_3_ready = nh.subscribe(
  //     "/imu3/raw_imu", 1, gyro_3_ready_Gyro_Callback);
  // ros::Subscriber sub_gyro_3_Alarm = nh.subscribe(
  //     "/imu3/raw_imu", 1, gyro_3_Alarm_Gyro_Callback);
  // vru_1
  ros::Subscriber sub_VRU_1_roll =
      nh.subscribe("/imu1/raw_imu", 1, VRU_1_roll_Callback);
  ros::Subscriber sub_VRU_1_pitch =
      nh.subscribe("/imu1/raw_imu", 1, VRU_1_pitch_Callback);
  // ros::Subscriber sub_VRU_1_weight =
  //     nh.subscribe("/imu1/weight", 1, VRU_1_weight_VRU_Callback);
  // ros::Subscriber sub_VRU_1_ready =
  //     nh.subscribe("/imu1/ready", 1, VRU_1_ready_VRU_Callback);
  // ros::Subscriber sub_VRU_1_Alarm =
  //     nh.subscribe("/imu1/Alarm", 1, VRU_1_Alarm_VRU_Callback);

  // VRU_2
  ros::Subscriber sub_VRU_2_roll =
      nh.subscribe("/imu2/raw_imu", 1, VRU_2_roll_Callback);
  ros::Subscriber sub_VRU_2_pitch =
      nh.subscribe("/imu2/raw_imu", 1, VRU_2_pitch_Callback);
  // ros::Subscriber sub_VRU_2_weight =
  //     nh.subscribe("/imu2/weight", 1, VRU_2_weight_VRU_Callback);
  // ros::Subscriber sub_VRU_2_ready =
  //     nh.subscribe("/imu2/ready", 1, VRU_2_ready_VRU_Callback);
  // ros::Subscriber sub_VRU_2_Alarm =
  //     nh.subscribe("/imu2/Alarm", 1, VRU_2_Alarm_VRU_Callback);
  // VRU_3
  ros::Subscriber sub_VRU_3_roll =
      nh.subscribe("/imu3/raw_imu", 1, VRU_3_roll_Callback);
  ros::Subscriber sub_VRU_3_pitch =
      nh.subscribe("/imu3/raw_imu", 1, VRU_3_pitch_Callback);
  // ros::Subscriber sub_VRU_3_weight =
  //     nh.subscribe("/imu3/weight", 1, VRU_3_weight_VRU_Callback);
  // ros::Subscriber sub_VRU_3_ready =
  //     nh.subscribe("/imu3/ready", 1, VRU_3_ready_VRU_Callback);
  // ros::Subscriber sub_VRU_3_Alarm =
  //     nh.subscribe("/imu3/Alarm", 1, VRU_3_Alarm_VRU_Callback);
  // fusion_data

  ros::Subscriber sub_fusiondata_roll =
      nh.subscribe("/imu_fusion", 1, fusiondata_roll_Callback);
  ros::Subscriber sub_fusiondata_pitch =
      nh.subscribe("/imu_fusion", 1, fusiondata_pitch_Callback);
  ros::Subscriber sub_fusiondata_kpoint_x =
      nh.subscribe("/kpoint_fusion", 1, fusiondata_kpoint_x_Callback);
  ros::Subscriber sub_fusiondata_kpoint_y =
      nh.subscribe("/kpoint_fusion", 1, fusiondata_kpoint_y_Callback);
  ros::Subscriber sub_fusiondata_kpoint_deg =
      nh.subscribe("/kpoint_fusion", 1, fusiondata_roll_Callback);
  ros::Subscriber sub_fusiondata_NEkpoint_x =
      nh.subscribe("/NEkpoint_fusion", 1, fusiondata_NEkpoint_x_Callback);
  ros::Subscriber sub_fusiondata_NEkpoint_y =
      nh.subscribe("/NEkpoint_fusion", 1, fusiondata_NEkpoint_y_Callback);

  // void vesselState_vessel_velocity_Callback(
  //     const std_msgs::Float64::ConstPtr &msg) {
  //   _vesselState.vessel_velocity = msg->data;
  // }
  // void vesselState_vessel_heading_Callback(
  //     const std_msgs::Float64::ConstPtr &msg) {
  //   _vesselState.vessel_heading = (msg->data);
  // }
  // void vesselState_speed_heading_Callback(
  //     const std_msgs::Float64::ConstPtr &msg) {
  //   _vesselState.vessel_speed_heading = (msg->data);
  // }

  ros::Subscriber sub_vessel_velocity =
      nh.subscribe("/vesssel_state", 1, vesselState_vessel_velocity_Callback);
  ros::Subscriber sub_vessel_heading =
      nh.subscribe("/imu_fusion", 1, vesselState_vessel_heading_Callback);
  ros::Subscriber sub_speed_heading =
      nh.subscribe("/vesssel_state", 1, vesselState_speed_heading_Callback);

  ros::Rate loop_rate(10);
  while (ros::ok()) {
    // _systemInfo.time = getNowTime();

    // std::cout << "打包开始" << std::endl;
    //将更新的数据打包成string

    _IPCserver.senddata2other(
        _cyscanRTdata_1, _cyscanRTdata_2, _radiusRTdata_1, _radiusRTdata_2,
        _gpsRTdata_1, _gpsRTdata_2, _gpsRTdata_3, _gyroRTdata_1, _gyroRTdata_2,
        _gyroRTdata_3, _VRURTdata_1, _VRURTdata_2, _VRURTdata_3, _fusiondata,
        _vesselState, buffer_trans);
    // std::cout << "打包完成" << std::endl;

         strcpy(bufsend, buffer_trans.c_str());
         msg.data = bufsend;
     shipdata_pub.publish(msg);
    //打印出发送给UI的string
    std::cout << _IPCserver << std::endl;


    ////////////////////////////需要完善的部分
    // 给发送的消息赋值
  
    /////////////////////////////////////////////////
    ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
}
