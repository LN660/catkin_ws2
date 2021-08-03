#include <dynamic_reconfigure/server.h>
#include <sensor/gps_fusionConfig.h>
#include <sensor_msgs/NavSatFix.h>
#include <std_msgs/Float64.h>
#include <Eigen/Core>
#include <Eigen/Dense>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>
// #include "gps.h"
#include "sensor/gpsfusion.h"
// Define a UTM projection for an arbitrary ellipsoid
const int _GPS_NUM = 3;
double latitude[_GPS_NUM] = {0}, longitude[_GPS_NUM] = {0},
       UTMx[_GPS_NUM] = {0}, UTMy[_GPS_NUM] = {0};
double sigma_UTMx[_GPS_NUM] = {0}, sigma_UTMy[_GPS_NUM] = {0};
double omega_la[_GPS_NUM] = {0}, omega_lo[_GPS_NUM] = {0},
       omega_al[_GPS_NUM] = {0};
double fused_UTMx = 0, fused_UTMy = 0, imu_head;
int sample_num;
double _GPS1_POS[3], _GPS2_POS[3], _GPS3_POS[3];
int switch_gps1, switch_gps2, switch_gps3;
double maxsigma, minsigma;
//用来存储临时数据
int inner_switch[3];

void run_fusion() {
  //判断有几个sensor，进而确定权值
  double sum_weight;
  sum_weight = 1 / sigma_UTMx[0] * inner_switch[0] +
               1 / sigma_UTMx[1] * inner_switch[1] +
               1 / sigma_UTMx[2] * inner_switch[2];
  if ((sigma_UTMx[0] == 0) && (sigma_UTMx[1] == 0) && (sigma_UTMx[2] == 0))
    ROS_INFO_STREAM("NO GPS DATA");
  else {
    for (int i = 0; i < 3; i++) {
      omega_la[i] = 1 / sigma_UTMx[i] * inner_switch[i] / sum_weight;
    }
  }
  std::cout << "inner_switch0: " << sigma_UTMx[0] << std::endl;
  std::cout << "inner_switch1: " << sigma_UTMx[1] << std::endl;
  std::cout << "inner_switch2: " << sigma_UTMx[2] << std::endl;

  sum_weight = 1 / sigma_UTMy[0] * inner_switch[0] +
               1 / sigma_UTMy[1] * inner_switch[1] +
               1 / sigma_UTMy[2] * inner_switch[2];
  if ((sigma_UTMy[0] == 0) && (sigma_UTMy[1] == 0) && (sigma_UTMy[2] == 0))
    ROS_INFO_STREAM("NO GPS DATA");
  else {
    for (int i = 0; i < 3; i++) {
      omega_lo[i] = 1 / sigma_UTMy[i] * inner_switch[i] / sum_weight;
    }
  }
  // std::cout << "sum_weight2: " << sum_weight << std::endl;
  fused_UTMx = UTMx[0] * omega_la[0] + UTMx[1] * omega_la[1] +
               UTMx[2] * omega_la[2];  // if (sigma_UTMx[0] == 0)
                                       // {
  // std::cout << "fused_UTMx: \n"
  //           << fused_UTMx << std::endl;
  // }
  // std::cout << "fused_UTMx: \n" << fused_UTMx << std::endl;
  fused_UTMy = UTMy[0] * omega_lo[0] + UTMy[1] * omega_lo[1] +
               UTMy[2] * omega_lo[2];  // if (sigma_UTMx[0] == 0)
  // {
  //    std::cout << "TRUE_longitude: \n" << std::endl;
  // }
  // std::cout << "fused_UTMy: \n" << fused_UTMy << std::endl;
}
// std::vector<double> getVertexIndices(std::string const &pointLine)
// {
//   std::istringstream iss(pointLine);

//   return std::vector<double>{std::istream_iterator<double>(iss),
//                              std::istream_iterator<double>()};
// }
// void dynamic_callback(dp_core::gps_fusionConfig &config, uint32_t level)
// {
//   switch_gps1 = (int)config.switch_gps1_bool;
//   switch_gps2 = (int)config.switch_gps2_bool;
//   switch_gps3 = (int)config.switch_gps3_bool;
//   maxsigma = config.max_sigma;
//   minsigma = config.min_sigma;
//   // if (switch_gps1 == 0)
//   //   config.switch_gps3_bool = true;
//   // std::string gps_x_str, gps_y_str, gps_z_str;
//   // gps_x_str = config.gps_x;
//   // gps_y_str = config.gps_y;
//   // gps_z_str = config.gps_z;
//   // std::vector<double> gps_x_vec, gps_y_vec, gps_z_vec;
//   // gps_x_vec = getVertexIndices(gps_x_str);
//   // gps_y_vec = getVertexIndices(gps_y_str);
//   // gps_z_vec = getVertexIndices(gps_z_str);
//   // _GPS1_POS[0] = gps_x_vec[0];
//   // _GPS1_POS[1] = gps_y_vec[0];
//   // _GPS1_POS[2] = gps_z_vec[0];
//   // _GPS2_POS[0] = gps_x_vec[1];
//   // _GPS2_POS[1] = gps_y_vec[1];
//   // _GPS2_POS[2] = gps_z_vec[1];
//   // _GPS3_POS[0] = gps_x_vec[2];
//   // _GPS3_POS[1] = gps_y_vec[2];
//   // _GPS3_POS[2] = gps_z_vec[2];

//   //还差一个更新gps_x gps_y gps_z 的函数
// }

int main(int argv, char **argc) {
  ros::init(argv, argc, "gps_fusion");
  ros::NodeHandle n;
  ros::NodeHandle private_nh("~");
  std::vector<double> gps_x, gps_y, gps_z;

  int looprate;
  int propeller_num;
  std::string _port, topic_name_head;
  private_nh.param("propeller_num", propeller_num, 0);
  private_nh.param("topic_name_head", topic_name_head, std::string("imu_head"));
  private_nh.param("switch_gps1", switch_gps1, 1);
  private_nh.param("switch_gps2", switch_gps2, 1);
  private_nh.param("switch_gps3", switch_gps3, 0);
  private_nh.param("loop_rate", looprate, 1);
  private_nh.param("sample_num", sample_num, 10);
  private_nh.param("max_sigma", maxsigma, 100000.0);
  private_nh.param("min_sigma", minsigma, 0.0);
  private_nh.param("port", _port, std::string("/dev/ttyUSB3"));

  // maxsigma = 10000;

  // std::cout << "maxsigma" << maxsigma << std::endl;
  // std::cout << "sample_num" << sample_num << std::endl;
  // std::cout << "读取的imu首相角为" << imu_head << std::endl;
  // ros::Subscriber sub_head =
  //     n.subscribe(topic_name_head, 1, Callback_head);  /////imu_fix
  // std::cout << "读取的imu首相角为" << imu_head << std::endl;
  n.getParam("gps_x", gps_x);
  n.getParam("gps_y", gps_y);
  n.getParam("gps_z", gps_z);

  _GPS1_POS[0] = gps_x[0];
  _GPS1_POS[1] = gps_y[0];
  _GPS1_POS[2] = gps_z[0];
  _GPS2_POS[0] = gps_x[1];
  _GPS2_POS[1] = gps_y[1];
  _GPS2_POS[2] = gps_z[1];
  _GPS3_POS[0] = gps_x[2];
  _GPS3_POS[1] = gps_y[2];
  _GPS3_POS[2] = gps_z[2];
  gps_fusion gps1(_GPS1_POS, sample_num, switch_gps1, minsigma, maxsigma);
  gps_fusion gps2(_GPS2_POS, sample_num, switch_gps2, minsigma, maxsigma);
  gps_fusion gps3(_GPS3_POS, sample_num, switch_gps3, minsigma, maxsigma);
  ros::Subscriber sub_head1 =
      n.subscribe(topic_name_head, 1, &gps_fusion::Callback_head, &gps1);
  ros::Subscriber sub_head2 =
      n.subscribe(topic_name_head, 1, &gps_fusion::Callback_head, &gps2);
  ros::Subscriber sub_head3 = n.subscribe(
      topic_name_head, 1, &gps_fusion::Callback_head, &gps3);  /////imu_fix
  ros::Subscriber sub_gps1 =
      n.subscribe("gps1/raw_gps_data", 1, &gps_fusion::callback, &gps1);
  ros::Subscriber sub_gps2 =
      n.subscribe("gps2/raw_gps_data", 1, &gps_fusion::callback, &gps2);
  ros::Subscriber sub_gps3 =
      n.subscribe("gps3/raw_gps_data", 1, &gps_fusion::callback, &gps3);
  ros::Publisher pub_UTMx = n.advertise<std_msgs::Float64>("UTMx", 10);
  ros::Publisher pub_UTMy = n.advertise<std_msgs::Float64>("UTMy", 10);
  // ros::Publisher pub_fusion = n.advertise<sensor::gps_msgs>("GPS_fusion",
  // 10);

  dynamic_reconfigure::Server<sensor::gps_fusionConfig> server;
  // dynamic_reconfigure::Server<dp_core::gps_fusionConfig>::CallbackType f;
  // server.setCallback(boost::bind(&dynamic_callback, _1, _2));
  std_msgs::Float64 UTMx_msg;
  std_msgs::Float64 UTMy_msg;
  // dp_core::gps_msgs fusion_msg;

  ros::Rate loop_rate(looprate);
  // UTMalt tm(6378388, 1 / 297.0, 51, true);
  while (ros::ok()) {
    // std::cout << "maxsigma" << maxsigma << std::endl;
    gps1.update_parameter(_GPS1_POS, sample_num, switch_gps1, minsigma,
                          maxsigma);
    gps2.update_parameter(_GPS2_POS, sample_num, switch_gps2, minsigma,
                          maxsigma);
    gps3.update_parameter(_GPS3_POS, sample_num, switch_gps3, minsigma,
                          maxsigma);
    private_nh.setParam("switch_gps1", switch_gps1);
    private_nh.setParam("switch_gps2", switch_gps2);
    private_nh.setParam("switch_gps3", switch_gps3);
    gps1.calculate_sigma();
    gps2.calculate_sigma();
    gps3.calculate_sigma();

    // std::cout << "omega_la1: " << omega_la[0] << std::endl;
    // std::cout << "omega_la2: " << omega_la[1] << std::endl;
    sigma_UTMx[0] = gps1.get_sigma_UTMx();
    sigma_UTMx[1] = gps2.get_sigma_UTMx();
    sigma_UTMx[2] = gps3.get_sigma_UTMx();
    // std::cout << "switch_gps1: " << switch_gps1 << std::endl;
    // std::cout << "sigma_UTMx0: " << sigma_UTMx[0] << std::endl;
    // std::cout << "sigma_UTMx1: " << sigma_UTMx[1] << std::endl;
    // std::cout << "sigma_UTMx2: " << sigma_UTMx[2] << std::endl;
    sigma_UTMy[0] = gps1.get_sigma_UTMy();
    sigma_UTMy[1] = gps2.get_sigma_UTMy();
    sigma_UTMy[2] = gps3.get_sigma_UTMy();
    inner_switch[0] = gps1.get_inner_switch();
    inner_switch[1] = gps2.get_inner_switch();
    inner_switch[2] = gps3.get_inner_switch();
    UTMx[0] = gps1.get_UTMx();
    UTMx[1] = gps2.get_UTMx();
    UTMx[2] = gps3.get_UTMx();
    UTMy[0] = gps1.get_UTMy();
    UTMy[1] = gps2.get_UTMy();
    UTMy[2] = gps3.get_UTMy();

    run_fusion();  //数据融合
    // std::cout << "UTMx0: " << UTMx[0] << std::endl;
    // std::cout << "UTMx1: " << UTMx[1] << std::endl;
    // std::cout << "UTMx1: " << UTMx[0] << std::endl;
    // std::cout << "UTMy1: " << UTMy[0] - 3e6 << std::endl;
    // std::cout << "UTMx2: " << UTMx[1] << std::endl;
    // std::cout << "UTMy2: " << UTMy[1] - 3e6 << std::endl;
    // std::cout << "fused_UTMx: \n"
    //           << fused_UTMx << std::endl;
    // tm.Reverse(fused_UTMx, fused_UTMy, fusion_msg.latitude,
    //            fusion_msg.longitude); // 坐标转换
    // fusion_msg.UTMx = fused_UTMx;     //用于输出融合后的longitude和latitude
    // fusion_msg.UTMy = fused_UTMy;
    if(!std::isnan(fused_UTMx))
UTMx_msg.data = fused_UTMx;
    if(!std::isnan(fused_UTMy))
    UTMy_msg.data = fused_UTMy;

    std::cout << "fused_UTMx: " << fused_UTMx << std::endl;
    std::cout << "fused_UTMy: " << fused_UTMy << std::endl;
    pub_UTMx.publish(UTMx_msg);
    pub_UTMy.publish(UTMy_msg);
    ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
}
