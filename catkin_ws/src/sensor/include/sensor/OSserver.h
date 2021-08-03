/*
***********************************************************************
* OSserver.h: package the IPC data to string and send to other vessels
* This header file can be read by C++ compilers
*
*  by LN(SJTU)
***********************************************************************
*/

#ifndef _OSserver_H_
#define _OSserver_H_

#include <iostream>
#include "OSserverData.h"
// #include "tcpserver.h"

class OSserver {
  friend std::ostream &operator<<(std::ostream &, const OSserver &);

 public:
  OSserver() : send_buffer("") {}
  ~OSserver() {}
  void senddata2gui(
      const cyscanRTdata &_cyscanRTdata_1_1,
      const cyscanRTdata &_cyscanRTdata_1_2,
      const radiusRTdata &_radiusRTdata_1_1,
      const radiusRTdata &_radiusRTdata_1_2, const gpsRTdata &_gpsRTdata_1_1,
      const gpsRTdata &_gpsRTdata_1_2, const gpsRTdata &_gpsRTdata_1_3,
      const gyroRTdata &_gyroRTdata_1_1, const gyroRTdata &_gyroRTdata_1_2,
      const gyroRTdata &_gyroRTdata_1_3, const VRURTdata &_VRURTdata_1_1,
      const VRURTdata &_VRURTdata_1_2, const VRURTdata &_VRURTdata_1_3,
      const fusiondata &_fusiondata_1, const vesselState &_vesselstate_1,
      const cyscanRTdata &_cyscanRTdata_2_1,
      const cyscanRTdata &_cyscanRTdata_2_2,
      const radiusRTdata &_radiusRTdata_2_1,
      const radiusRTdata &_radiusRTdata_2_2, const gpsRTdata &_gpsRTdata_2_1,
      const gpsRTdata &_gpsRTdata_2_2, const gpsRTdata &_gpsRTdata_2_3,
      const gyroRTdata &_gyroRTdata_2_1, const gyroRTdata &_gyroRTdata_2_2,
      const gyroRTdata &_gyroRTdata_2_3, const VRURTdata &_VRURTdata_2_1,
      const VRURTdata &_VRURTdata_2_2, const VRURTdata &_VRURTdata_2_3,
      const fusiondata &_fusiondata_2, const vesselState &_vesselstate_2,
      const cyscanRTdata &_cyscanRTdata_3_1,
      const cyscanRTdata &_cyscanRTdata_3_2,
      const radiusRTdata &_radiusRTdata_3_1,
      const radiusRTdata &_radiusRTdata_3_2, const gpsRTdata &_gpsRTdata_3_1,
      const gpsRTdata &_gpsRTdata_3_2, const gpsRTdata &_gpsRTdata_3_3,
      const gyroRTdata &_gyroRTdata_3_1, const gyroRTdata &_gyroRTdata_3_2,
      const gyroRTdata &_gyroRTdata_3_3, const VRURTdata &_VRURTdata_3_1,
      const VRURTdata &_VRURTdata_3_2, const VRURTdata &_VRURTdata_3_3,
      const fusiondata &_fusiondata_3, const vesselState &_vesselstate_3,
      const systemInfo &_systemInfo, std::string &_buffer_trans) {
    send_buffer.clear();
    send_buffer = "$SKLOEA";
    convert2string(_cyscanRTdata_1_1, send_buffer);
    convert2string(_cyscanRTdata_1_2, send_buffer);
    convert2string(_radiusRTdata_1_1, send_buffer);
    convert2string(_radiusRTdata_1_2, send_buffer);
    convert2string(_gpsRTdata_1_1, send_buffer);
    convert2string(_gpsRTdata_1_2, send_buffer);
    convert2string(_gpsRTdata_1_3, send_buffer);
    convert2string(_gyroRTdata_1_1, send_buffer);
    convert2string(_gyroRTdata_1_2, send_buffer);
    convert2string(_gyroRTdata_1_3, send_buffer);
    convert2string(_VRURTdata_1_1, send_buffer);
    convert2string(_VRURTdata_1_2, send_buffer);
    convert2string(_VRURTdata_1_3, send_buffer);
    convert2string(_fusiondata_1, send_buffer);
    convert2string(_vesselstate_1, send_buffer);

    convert2string(_cyscanRTdata_2_1, send_buffer);
    convert2string(_cyscanRTdata_2_2, send_buffer);
    convert2string(_radiusRTdata_2_1, send_buffer);
    convert2string(_radiusRTdata_2_2, send_buffer);
    convert2string(_gpsRTdata_2_1, send_buffer);
    convert2string(_gpsRTdata_2_2, send_buffer);
    convert2string(_gpsRTdata_2_3, send_buffer);
    convert2string(_gyroRTdata_2_1, send_buffer);
    convert2string(_gyroRTdata_2_2, send_buffer);
    convert2string(_gyroRTdata_2_3, send_buffer);
    convert2string(_VRURTdata_2_1, send_buffer);
    convert2string(_VRURTdata_2_2, send_buffer);
    convert2string(_VRURTdata_2_3, send_buffer);
    convert2string(_fusiondata_2, send_buffer);
    convert2string(_vesselstate_2, send_buffer);

    convert2string(_cyscanRTdata_3_1, send_buffer);
    convert2string(_cyscanRTdata_3_2, send_buffer);
    convert2string(_radiusRTdata_3_1, send_buffer);
    convert2string(_radiusRTdata_3_2, send_buffer);
    convert2string(_gpsRTdata_3_1, send_buffer);
    convert2string(_gpsRTdata_3_2, send_buffer);
    convert2string(_gpsRTdata_3_3, send_buffer);
    convert2string(_gyroRTdata_3_1, send_buffer);
    convert2string(_gyroRTdata_3_2, send_buffer);
    convert2string(_gyroRTdata_3_3, send_buffer);
    convert2string(_VRURTdata_3_1, send_buffer);
    convert2string(_VRURTdata_3_2, send_buffer);
    convert2string(_VRURTdata_3_3, send_buffer);
    convert2string(_fusiondata_3, send_buffer);
    convert2string(_vesselstate_3, send_buffer);
    convert2string(_systemInfo, send_buffer);
    send_buffer += ",";
    send_buffer += "*";
    strcpy(send_buffer_char, send_buffer.c_str());
    // _tcpserver.selectserver(recv_buffer_char, send_buffer_char, recv_size,
    //                         send_size);
    // std::cout << recv_buffer_char << std::endl;
    // recv_buffer = recv_buffer_char;
    _buffer_trans = send_buffer_char;
  }

 private:
  std::string send_buffer;
  std::string recv_buffer;
  // tcpserver _tcpserver;
  char recv_buffer_char[150] = {0};  //接收的字符串缓存
  char send_buffer_char[1280] = {0};
  const int recv_size = 150;
  const int send_size = 1280;
  std::string my_to_string(double a, int num) {
    std::string temp = {};
    temp = std::to_string(a);
    for (int i = 0; i < temp.size(); i++) {
      if (temp[i] == '.') {
        if (temp.size() - i >= num + 1) {
          temp = temp.substr(0, i + num + 1);
        };
        if (temp.size() - i < (num + 1)) {
          for (int j = 0; j < num + 1 - temp.size() + i; j++) {
            temp.push_back('0');
          }
        };
        return temp;
      }
    };
    return temp;
  }
  //转换成字符串
  void convert2string(const cyscanRTdata &_cyscanRTdata, std::string &_str) {
    _str += ",";
    _str += my_to_string(_cyscanRTdata.cyscan_x, 4);
    _str += ",";
    _str += my_to_string(_cyscanRTdata.cyscan_y, 4);
    _str += ",";
    _str += my_to_string(_cyscanRTdata.cyscan_deg, 4);
    _str += ",";
    _str += my_to_string(_cyscanRTdata.cyscan_weight, 4);
    _str += ",";
    _str += std::to_string(_cyscanRTdata.cyscan_ready);
    _str += ",";
    _str += std::to_string(_cyscanRTdata.cyscan_alarm);
  }
  void convert2string(const radiusRTdata &_radiusRTdata, std::string &_str) {
    _str += ",";
    _str += my_to_string(_radiusRTdata.radius_x, 4);
    _str += ",";
    _str += my_to_string(_radiusRTdata.radius_y, 4);
    _str += ",";
    _str += my_to_string(_radiusRTdata.radius_deg, 4);
    _str += ",";
    _str += my_to_string(_radiusRTdata.radius_weight, 4);
    _str += ",";
    _str += std::to_string(_radiusRTdata.radius_ready);
    _str += ",";
    _str += std::to_string(_radiusRTdata.radius_alarm);
  }
  void convert2string(const gpsRTdata &_gpsRTdata, std::string &_str) {
    _str += ",";
    _str += my_to_string(_gpsRTdata.latitude, 4);
    _str += ",";
    _str.push_back(_gpsRTdata.latitude_hemisphere);
    // _str += std::to_string(_gpsRTdata.latitude_hemisphere);
    _str += ",";
    _str += my_to_string(_gpsRTdata.longitude, 4);
    _str += ",";
    _str.push_back(_gpsRTdata.longitude_hemisphere);
    // _str += std::to_string(_gpsRTdata.longitude_hemisphere);
    _str += ",";
    _str += std::to_string(_gpsRTdata.status);
    _str += ",";
    _str += std::to_string(_gpsRTdata.num_NVS);
    _str += ",";
    _str += my_to_string(_gpsRTdata.altitude, 4);
    _str += ",";
    _str += my_to_string(_gpsRTdata.weight_GPS, 4);
    _str += ",";
    _str += std::to_string(_gpsRTdata.ready_GPS);
    _str += ",";
    _str += std::to_string(_gpsRTdata.Alarm_GPS);
  }

  void convert2string(const gyroRTdata &_gyroRTdata, std::string &_str) {
    _str += ",";
    _str += my_to_string(_gyroRTdata.heading, 4);
    _str += ",";
    _str += my_to_string(_gyroRTdata.weight_Gyro, 4);
    _str += ",";
    _str += std::to_string(_gyroRTdata.ready_Gyro);
    _str += ",";
    _str += std::to_string(_gyroRTdata.Alarm_Gyro);
  }

  void convert2string(const VRURTdata &_VRURTdata, std::string &_str) {
    _str += ",";
    _str += my_to_string(_VRURTdata.roll, 4);
    _str += ",";
    _str += my_to_string(_VRURTdata.pitch, 4);
    _str += ",";
    _str += my_to_string(_VRURTdata.weight_VRU, 4);
    _str += ",";
    _str += std::to_string(_VRURTdata.ready_VRU);
    _str += ",";
    _str += std::to_string(_VRURTdata.Alarm_VRU);
  }

  void convert2string(const fusiondata &_fusiondata, std::string &_str) {
    _str += ",";
    _str += my_to_string(_fusiondata.roll_fusion, 4);
    _str += ",";
    _str += my_to_string(_fusiondata.pitch_fusion, 4);
    _str += ",";
    _str += my_to_string(_fusiondata.kpoint_x_fusion, 4);
    _str += ",";
    _str += my_to_string(_fusiondata.kpoint_y_fusion, 4);
    _str += ",";
    _str += my_to_string(_fusiondata.kpoint_deg_fusion, 4);
    _str += ",";
    _str += my_to_string(_fusiondata.NEkpoint_x_fusion, 4);
    _str += ",";
    _str += my_to_string(_fusiondata.NEkpoint_y_fusion, 4);
  }

  void convert2string(const vesselState &_vesselState, std::string &_str) {
    _str += ",";
    _str += my_to_string(_vesselState.vessel_velocity, 4);
    _str += ",";
    _str += my_to_string(_vesselState.vessel_heading, 4);
    _str += ",";
    _str += my_to_string(_vesselState.vessel_speed_heading, 4);
  }

  void convert2string(const systemInfo &_systemInfo, std::string &_str) {
    _str += ",";
    _str += std::to_string(_systemInfo.wlan);
    _str += ",";
    // _str += _systemInfo.time;
    long int timecut = _systemInfo.now_time;
    _str += std::to_string(timecut);
    _str += ",";
    _str += std::to_string(_systemInfo.all_ready);
  }
};

std::ostream &operator<<(std::ostream &os, const OSserver &_OSserver) {
  os << _OSserver.send_buffer;
  return os;
}

#endif /* _OSsever_H_ */