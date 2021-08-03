#include <dynamic_reconfigure/server.h>
#include <ros/ros.h>
#include <sensor/cyscan_fusionConfig.h>
#include <sensor/cyscan_msgs.h>
#include <std_msgs/Float64.h>
#include "sensor/cyscanfusion.h"
std::vector<double> cyscan1_kpx, cyscan1_kpy, cyscan1_deg, cyscan2_kpx,
    cyscan2_kpy, cyscan2_deg, cyscan3_kpx, cyscan3_kpy, cyscan3_deg;
double kpx[3], kpy[3], deg[3], sigma_kpx[3], sigma_kpy[3], sigma_deg[3],
    omega_kpx[3], omega_kpy[3], omega_deg[3];
double fused_kpx, fused_kpy, fused_deg;
int switch_cyscan1, switch_cyscan2, switch_cyscan3;
double minsigma_kpx, maxsigma_kpx, minsigma_kpy, maxsigma_kpy, minsigma_deg,
    maxsigma_deg;
double _cyscan1_pos[2], _cyscan2_pos[2], _cyscan3_pos[2], _target1_pos[2],
    _target2_pos[2], _target3_pos[2];
int inner_switch[3];

//这个是求方差的
void dynamic_callback(sensor::cyscan_fusionConfig &config,
                      uint32_t level)  //这部分的主要作用
{
  switch_cyscan1 = (int)config.switch_cyscan1_bool;
  switch_cyscan2 = (int)config.switch_cyscan2_bool;
  switch_cyscan3 = (int)config.switch_cyscan3_bool;
  maxsigma_deg = config.maxsigma_deg;
  minsigma_deg = config.minsigma_deg;
  maxsigma_kpx = config.maxsigma_kpx;
  minsigma_kpx = config.minsigma_kpx;
  maxsigma_kpy = config.maxsigma_kpy;
  minsigma_kpy = config.minsigma_kpy;
}

void run_fusion() {
  //判断有几个sensor，进而确定权值
  double sum_weight;
  sum_weight = 1 / sigma_kpx[0] * inner_switch[0] +
               1 / sigma_kpx[1] * inner_switch[1] +
               1 / sigma_kpx[2] * inner_switch[2];
  std::cout << "inner_switch0:    " << inner_switch[0] << std::endl;
  std::cout << "inner_switch1:    " << inner_switch[1] << std::endl;
  std::cout << "inner_switch2:    " << inner_switch[2] << std::endl;

  // std::cout << "sum sum_weight:  " << sum_weight << std::endl;
  // if (sum_weight == 0)
  //   ROS_INFO_STREAM("NO cyscan DATA");
  if (sum_weight != 0) {
    for (int i = 0; i < 3; i++) {
      omega_kpx[i] = 1 / sigma_kpx[i] * inner_switch[i] / sum_weight;
      // std::cout << "omega:  " << omega_kpx[i] << std::endl;
      // std::cout << "sigma_kpx:  " << sigma_kpx[i] << std::endl;
    }
  }

  sum_weight = 1 / sigma_kpy[0] * inner_switch[0] +
               1 / sigma_kpy[1] * inner_switch[1] +
               1 / sigma_kpy[2] * inner_switch[2];
  // if (sum_weight == 0)
  //   ROS_INFO_STREAM("NO cyscan DATA");
  // else
  if (sum_weight != 0) {
    for (int i = 0; i < 3; i++) {
      omega_kpy[i] = 1 / sigma_kpy[i] * inner_switch[i] / sum_weight;
    }
  }
  sum_weight = 1 / sigma_deg[0] * inner_switch[0] +
               1 / sigma_deg[1] * inner_switch[1] +
               1 / sigma_deg[2] * inner_switch[2];
  // if (sum_weight == 0)
  //   ROS_INFO_STREAM("NO cyscan DATA");
  if (sum_weight != 0) {
    for (int i = 0; i < 3; i++) {
      omega_deg[i] = 1 / sigma_deg[i] * inner_switch[i] / sum_weight;
    }
  }
  // std::cout << "fusion running" << std::endl;
  fused_kpx = kpx[0] * omega_kpx[0] + kpx[1] * omega_kpx[1] +
              kpx[2] * omega_kpx[2];  // if (sigma_latitude[0] == 0)
  fused_kpy = kpy[0] * omega_kpy[0] + kpy[1] * omega_kpy[1] +
              kpy[2] * omega_kpy[2];  // if (sigma_latitude[0] == 0)
  fused_deg = deg[0] * omega_deg[0] + deg[1] * omega_deg[1] +
              deg[2] * omega_deg[2];  // if (sigma_latitude[0] == 0)
}

int main(int argv, char **argc) {
  ros::init(argv, argc, "cyscan_fusion");
  ros::NodeHandle n;
  ros::NodeHandle private_nh("~");
  std::string topic_name1, topic_name2, topic_name3;
  int looprate;
  int sample_num;
  std::vector<double> cyscan_x, cyscan_y, target_x, target_y;

  private_nh.param("topic_name1", topic_name1,
                   std::string("cyscan1/raw_cyscan_data"));
  private_nh.param("topic_name2", topic_name2,
                   std::string("cyscan2/raw_cyscan_data"));
  private_nh.param("topic_name3", topic_name3,
                   std::string("cyscan3/raw_cyscan_data"));
  private_nh.param("loop_rate", looprate, 1);
  private_nh.param("sample_num", sample_num, 30);
  private_nh.param("minsigma_kpx", minsigma_kpx, 0.0);
  private_nh.param("maxsigma_kpx", maxsigma_kpx, 1000.0);
  private_nh.param("minsigma_kpy", minsigma_kpy, 0.0);
  private_nh.param("maxsigma_kpy", maxsigma_kpy, 1000.0);
  private_nh.param("minsigma_deg", minsigma_deg, 0.0);
  private_nh.param("maxsigma_deg", maxsigma_deg, 1000.0);
  private_nh.param("switch_cyscan1", switch_cyscan1, 1);
  private_nh.param("switch_cyscan2", switch_cyscan2, 1);
  private_nh.param("switch_cyscan3", switch_cyscan3, 0);

  n.getParam("cyscan_x", cyscan_x);
  n.getParam("cyscan_y", cyscan_y);
  n.getParam("target_x", target_x);
  n.getParam("target_y", target_y);

  _cyscan1_pos[0] = cyscan_x[0];
  _cyscan1_pos[1] = cyscan_y[0];
  _cyscan2_pos[0] = cyscan_x[1];
  _cyscan2_pos[1] = cyscan_y[1];
  _cyscan3_pos[0] = cyscan_x[2];
  _cyscan3_pos[1] = cyscan_y[2];
  _target1_pos[0] = target_x[0];
  _target1_pos[1] = target_y[0];
  _target2_pos[0] = target_x[1];
  _target2_pos[1] = target_y[1];
  _target3_pos[0] = target_x[2];
  _target3_pos[1] = target_y[2];

  cyscan_fusion cyscan1(_cyscan1_pos, _target1_pos, sample_num, switch_cyscan1,
                        minsigma_kpx, maxsigma_kpx, minsigma_kpy, maxsigma_kpy,
                        minsigma_deg, maxsigma_deg);
  cyscan_fusion cyscan2(_cyscan2_pos, _target2_pos, sample_num, switch_cyscan2,
                        minsigma_kpx, maxsigma_kpx, minsigma_kpy, maxsigma_kpy,
                        minsigma_deg, maxsigma_deg);
  cyscan_fusion cyscan3(_cyscan3_pos, _target3_pos, sample_num, switch_cyscan3,
                        minsigma_kpx, maxsigma_kpx, minsigma_kpy, maxsigma_kpy,
                        minsigma_deg, maxsigma_deg);
  ros::Subscriber sub_cyscan1 =
      n.subscribe(topic_name1, 1, &cyscan_fusion::callback, &cyscan1);
  ros::Subscriber sub_cyscan2 =
      n.subscribe(topic_name2, 1, &cyscan_fusion::callback, &cyscan2);
  ros::Subscriber sub_cyscan3 =
      n.subscribe(topic_name3, 1, &cyscan_fusion::callback, &cyscan3);

  dynamic_reconfigure::Server<sensor::cyscan_fusionConfig>
      server;  //这部分的主要作用
  server.setCallback(boost::bind(&dynamic_callback, _1, _2));
  ros::Publisher pub_kpx = n.advertise<std_msgs::Float64>("kpx", 1);
  ros::Publisher pub_kpy = n.advertise<std_msgs::Float64>("kpy", 1);
  ros::Publisher pub_deg = n.advertise<std_msgs::Float64>("kpdeg", 1);

  std_msgs::Float64 msg_kpx;
  std_msgs::Float64 msg_kpy;
  std_msgs::Float64 msg_deg;

  ros::Rate loop_rate(looprate);
  while (ros::ok()) {
    cyscan1.update_parameter(_cyscan1_pos, _target1_pos, switch_cyscan1,
                             minsigma_kpx, maxsigma_kpx, minsigma_kpy,
                             maxsigma_kpy, minsigma_deg, maxsigma_deg);
    cyscan2.update_parameter(_cyscan2_pos, _target2_pos, switch_cyscan2,
                             minsigma_kpx, maxsigma_kpx, minsigma_kpy,
                             maxsigma_kpy, minsigma_deg, maxsigma_deg);
    cyscan3.update_parameter(_cyscan3_pos, _target3_pos, switch_cyscan3,
                             minsigma_kpx, maxsigma_kpx, minsigma_kpy,
                             maxsigma_kpy, minsigma_deg, maxsigma_deg);

    cyscan1.calculate_sigma();
    cyscan2.calculate_sigma();
    cyscan3.calculate_sigma();
    sigma_kpx[0] = cyscan1.get_sigma_kpx();
    sigma_kpx[1] = cyscan2.get_sigma_kpx();
    sigma_kpx[2] = cyscan3.get_sigma_kpx();
    sigma_kpy[0] = cyscan1.get_sigma_kpy();
    sigma_kpy[1] = cyscan2.get_sigma_kpy();
    sigma_kpy[2] = cyscan3.get_sigma_kpy();
    sigma_deg[0] = cyscan1.get_sigma_kpdeg();
    sigma_deg[1] = cyscan2.get_sigma_kpdeg();
    sigma_deg[2] = cyscan3.get_sigma_kpdeg();
    kpx[0] = cyscan1.get_kpx();
    kpx[1] = cyscan2.get_kpx();
    kpx[2] = cyscan3.get_kpx();
    kpy[0] = cyscan1.get_kpy();
    kpy[1] = cyscan2.get_kpy();
    kpy[2] = cyscan3.get_kpy();
    deg[0] = cyscan1.get_kpdeg();
    deg[1] = cyscan2.get_kpdeg();
    deg[2] = cyscan3.get_kpdeg();

    // std::cout << "sigma kpx0    " << sigma_kpx[0] << "  sigma kpx1      "
    //           << sigma_kpx[1] << "   sigma kpx2     " << sigma_kpx[2]
    //           << std::endl;
    inner_switch[0] = cyscan1.get_inner_switch();
    inner_switch[1] = cyscan2.get_inner_switch();
    inner_switch[2] = cyscan3.get_inner_switch();
    // std::cout << inner_switch[0] << inner_switch[1] << inner_switch[2]
    // << std::endl;  // wenti inner_switch 全部变成0？？？
    run_fusion();
    if (!std::isnan(fused_kpx)) msg_kpx.data = fused_kpx;
    if (!std::isnan(fused_kpy)) msg_kpy.data = fused_kpy;
    if (!std::isnan(fused_deg)) msg_deg.data = fused_deg;
    // if (msg_deg.data > 2 * 3.1415926)
    //   msg_deg.data = msg_deg.data - 2 * 3.1415926;
    pub_kpx.publish(msg_kpx);
    pub_kpy.publish(msg_kpy);
    pub_deg.publish(msg_deg);
    ROS_INFO_STREAM("fused_kpx" << fused_kpx);
    ROS_INFO_STREAM("fused_kpy" << fused_kpy);
    ROS_INFO_STREAM("fused_deg" << fused_deg);
    ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
}
