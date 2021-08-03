/*
***********************************************************************
* OSserver.h: package the IPC data to string and send to other vessels
* This header file can be read by C++ compilers
*
*  by LN(SJTU)
***********************************************************************
*/

#ifndef _IPCserver_H_
#define _IPCserver_H_

#include <cstring>
#include <iostream>
#include "OSserverData.h"

class IPCserver {
  friend std::ostream &operator<<(std::ostream &, const IPCserver &);

 public:
  IPCserver() : send_buffer("") {}
  ~IPCserver() {}
  void senddata2other(
      const cyscanRTdata &_cyscanRTdata_1, const cyscanRTdata &_cyscanRTdata_2,
      const radiusRTdata &_radiusRTdata_1, const radiusRTdata &_radiusRTdata_2,
      const gpsRTdata &_gpsRTdata_1, const gpsRTdata &_gpsRTdata_2,
      const gpsRTdata &_gpsRTdata_3, const gyroRTdata &_gyroRTdata_1,
      const gyroRTdata &_gyroRTdata_2, const gyroRTdata &_gyroRTdata_3,
      const VRURTdata &_VRURTdata_1, const VRURTdata &_VRURTdata_2,
      const VRURTdata &_VRURTdata_3, const fusiondata &_fusiondata,
      const vesselState &_vesselstate, std::string &_buffer_trans) {
    send_buffer.clear();
    send_buffer = "$SKLOEIPC";
    convert2string(_cyscanRTdata_1, send_buffer);
    convert2string(_cyscanRTdata_2, send_buffer);

    convert2string(_radiusRTdata_1, send_buffer);
    convert2string(_radiusRTdata_2, send_buffer);

    convert2string(_gpsRTdata_1, send_buffer);
    convert2string(_gpsRTdata_2, send_buffer);
    convert2string(_gpsRTdata_3, send_buffer);
    convert2string(_gyroRTdata_1, send_buffer);
    convert2string(_gyroRTdata_2, send_buffer);
    convert2string(_gyroRTdata_3, send_buffer);
    convert2string(_VRURTdata_1, send_buffer);
    convert2string(_VRURTdata_2, send_buffer);
    convert2string(_VRURTdata_3, send_buffer);
    convert2string(_fusiondata, send_buffer);
    convert2string(_vesselstate, send_buffer);

    send_buffer += ",";
    send_buffer += "*";
    strcpy(send_buffer_char, send_buffer.c_str());

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
    // _str += ",";
    // _str+="*";
  }
};

std::ostream &operator<<(std::ostream &ipc, const IPCserver &_IPCserver) {
  ipc << _IPCserver.send_buffer;
  return ipc;
}

#endif /* _IPCsever_H_ */