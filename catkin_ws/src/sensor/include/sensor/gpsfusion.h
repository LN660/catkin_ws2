#ifndef _GPSFUSION_H_
#define _GPSFUSION_H_

//#include <geometry_msgs/PointStamped.h>
#include <ros/ros.h>
#include <sensor/gps_msgs.h>
//#include <tf/transform_listener.h>

class gps_fusion {
 private:
  double UTMx;
  double UTMy;
  double latitude;
  double longitude;
  // double altitude;
  double GPS_POS[3];
  int sample_num;
  double sigma_UTMx = 0;
  double sigma_UTMy = 0;
  double imu_head;
  double maxsigma, minsigma;
  int switch_gps, inner_switch;
  std::vector<double> UTMx_array;
  std::vector<double> UTMy_array;
  std::string frame_id;

  double ave(std::vector<double> a, int n) {
    double sum = 0;
    for (int i = 0; i < n; i++) {
      sum += a[i];
    }
    // std::cout << "sample_num" << n << std::endl;

    return sum / n;
  }  //平均值

  double variance(std::vector<double> a, int n) {
    double sigma = 0;
    double average = ave(a, n);
    for (int i = 0; i < n; i++) sigma += (a[i] - average) * (a[i] - average);
    if (!std::isnormal(sigma) || sigma == 0) {
      sigma = maxsigma * n + n;
    }
    return sigma / n;
  }

 public:
  explicit gps_fusion(
      const double _GPS_POS[3], const int &_sample_num, const int &_switch_gps,
      const double &_minsigma,
      const double &_maxsigma)  // 如果要在函数中读取地址的话 必须引用
      : sample_num(_sample_num),
        switch_gps(_switch_gps),
        minsigma(_minsigma),
        maxsigma(_maxsigma) {
    latitude = 0;
    longitude = 0;
    // altitude = 0;
    for (int i = 0; i < 3; i++) {
      GPS_POS[i] = _GPS_POS[i];
    }
    for (int i = 0; i < sample_num; i++)  //初始化
    {
      UTMx_array.push_back(0);
      UTMy_array.push_back(0);
    }
  }
  void Callback_head(const std_msgs::Float64 &msg) {
    imu_head = msg.data;
    // std::cout << "读取的imu首相角为" << imu_head << std::endl;
  }
  void callback(const sensor::gps_msgs &msg) {
    latitude = msg.latitude;
    longitude = msg.longitude;

    double UTMx_temp, UTMy_temp;
    UTMx_temp = msg.UTMx;
    UTMy_temp = msg.UTMy;
    // geometry_msgs::PointStamped
    // 融合前卫星数据
    std::cout << "融合前船舶中心点的utmx  " << UTMx_temp << std::endl;
    std::cout << "融合前船舶中心点的utmy  " << UTMy_temp << std::endl;
    //    GPS_point;  //这里定义了一个相对于laser_link坐标系的点
    // GPS_point.header.frame_id = frame_id;
    // GPS_point.header.stamp = ros::Time();
    // GPS_point.point.x = -GPS_POS[0];  //设置相对于laser_link坐标系的坐标
    // GPS_point.point.y = -GPS_POS[1];
    // GPS_point.point.z = -GPS_POS[2];
    // geometry_msgs::PointStamped base_point;
    // listener->transformPoint("odom", GPS_point, base_point);
    UTMx = UTMx_temp - GPS_POS[0] * cos(imu_head) - GPS_POS[1] * sin(imu_head);
    UTMy = UTMy_temp - GPS_POS[1] * cos(imu_head) + GPS_POS[0] * sin(imu_head);
    std::cout << "船舶中心点的utmx  " << UTMx << std::endl;
    std::cout << "船舶中心点的utmy  " << UTMy << std::endl;
    for (int i = 0; i < sample_num - 1; i++) {
      UTMx_array[sample_num - i - 1] = UTMx_array[sample_num - i - 2];

      // update the data of gps1 longitude
      UTMy_array[sample_num - i - 1] = UTMy_array[sample_num - i - 2];
    }
    // for (int i = 0; i != sample_num; i++) {
    //   std::cout << std::fixed << std::setprecision(3) << UTMx_array[i] << "
    //   ";
    // }
    if (std::isnan(UTMx_temp))
      UTMx_array[0] = UTMx_array[1];
    else
      UTMx_array[0] = UTMx_temp;
    if (std::isnan(UTMy_temp))
      UTMy_array[0] = UTMy_array[1];
    else
      UTMy_array[0] = UTMy_temp;
  }

  void calculate_sigma() {
    //计算方差 加altitude
    // for (int i = 0; i != sample_num; i++)
    // {
    //     std::cout << std::fixed << std::setprecision(3) << UTMx_array[i] << "
    //     ";
    // }
    sigma_UTMx = variance(UTMx_array, sample_num);
    sigma_UTMy = variance(UTMy_array, sample_num);
    inner_switch = switch_gps;
    // std::cout << "inner_switch" << switch_gps << std::endl;
    if (!((sigma_UTMx > minsigma && sigma_UTMx < maxsigma) &&
          (sigma_UTMy > minsigma && sigma_UTMy < maxsigma) &&
          std::isnormal(sigma_UTMx) && std::isnormal(sigma_UTMy)))
      inner_switch = 0;  // 方差若不在范围内 则权值强制归零
    // std::cout << sigma_UTMy << std::endl;
    // std::cout << "inner_switch_after" << inner_switch << std::endl;
  }
  double get_latitude() { return latitude; }
  double get_longitude() { return longitude; }
  // double get_altitude() { return altitude; }
  double get_UTMx() { return UTMx; }
  double get_UTMy() { return UTMy; }
  double get_UTMx_array(const int &i) { return UTMx_array[i]; }
  double get_UTMy_array(const int &i) { return UTMy_array[i]; }
  double get_sigma_UTMx() { return sigma_UTMx; }
  double get_sigma_UTMy() { return sigma_UTMy; }
  int get_inner_switch() { return inner_switch; }
  void update_parameter(const double POS[3], const int new_sample_num,
                        const int new_switch_gps, const double new_minsigma,
                        const double new_maxsigma) {
    GPS_POS[0] = POS[0];
    GPS_POS[1] = POS[1];
    GPS_POS[2] = POS[2];
    sample_num = new_sample_num;
    switch_gps = new_switch_gps;
    // std::cout << "new_switch_gps: " << new_switch_gps << std::endl;

    minsigma = new_minsigma;
    maxsigma = new_maxsigma;
  }
};
#endif