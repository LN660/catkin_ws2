#ifndef _OSserverData_H
#define _OSserverData_H

struct cyscanRTdata {
  double cyscan_x;    // m
  double cyscan_y;    // m
  double cyscan_deg;  // deg
  double cyscan_weight;
  int cyscan_ready;  // 0,1
  int cyscan_alarm;  // 0,1
};
struct radiusRTdata {
  double radius_x;    // m
  double radius_y;    // m
  double radius_deg;  // deg
  double radius_weight;
  int radius_ready;  // 0,1
  int radius_alarm;  // 0,1
};

struct gpsRTdata {
  double latitude;
  char latitude_hemisphere;  // N/S
  double longitude;
  char longitude_hemisphere;  // E/W
  int status;                 //
  int num_NVS;                //
  double altitude;
  double weight_GPS;
  int ready_GPS;  // 0,1o
  int Alarm_GPS;  // 0,1
};
struct gyroRTdata {
  double heading;
  double weight_Gyro;
  int ready_Gyro;
  int Alarm_Gyro;
};

struct VRURTdata {
  double roll;  //+-
  double pitch;
  double weight_VRU;
  int ready_VRU;
  int Alarm_VRU;
};
struct fusiondata {
  double roll_fusion;
  double pitch_fusion;
  double kpoint_x_fusion;
  double kpoint_y_fusion;
  double kpoint_deg_fusion;
  double NEkpoint_x_fusion;
  double NEkpoint_y_fusion;
};

struct vesselState {
  double vessel_velocity;
  double vessel_heading;
  double vessel_speed_heading;
};

struct systemInfo {
  int wlan;  //判断组网是否成功
  double now_time;
  int all_ready;
};

#endif  // _OSserverData_H
