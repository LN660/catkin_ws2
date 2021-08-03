#include <dynamic_reconfigure/server.h>
#include <ros/ros.h>
#include <sensor/radius_fusionConfig.h>
#include <sensor/radius_msgs.h>
#include <std_msgs/Float64.h>
#include "sensor/radiusfusion.h"
std::vector<double> radius1_kpx, radius1_kpy, radius1_deg, radius2_kpx,
    radius2_kpy, radius2_deg, radius3_kpx, radius3_kpy, radius3_deg;
double kpx[3], kpy[3], deg[3], sigma_kpx[3], sigma_kpy[3], sigma_deg[3],
    omega_kpx[3], omega_kpy[3], omega_deg[3];
double fused_kpx, fused_kpy, fused_deg;
int switch_radius1, switch_radius2, switch_radius3;
double minsigma_kpx, maxsigma_kpx, minsigma_kpy, maxsigma_kpy, minsigma_deg,
    maxsigma_deg;
double _radius1_pos[2], _radius2_pos[2], _radius3_pos[2], _target1_pos[2],
    _target2_pos[2], _target3_pos[2];
int inner_switch[3];

//这个是求方差的
void dynamic_callback(sensor::radius_fusionConfig &config,
                      uint32_t level)  //这部分的主要作用
{
  switch_radius1 = (int)config.switch_radius1_bool;
  switch_radius2 = (int)config.switch_radius2_bool;
  switch_radius3 = (int)config.switch_radius3_bool;
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
  //   ROS_INFO_STREAM("NO radius DATA");
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
  //   ROS_INFO_STREAM("NO radius DATA");
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
  //   ROS_INFO_STREAM("NO radius DATA");
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
  ros::init(argv, argc, "radius_fusion");
  ros::NodeHandle n;
  ros::NodeHandle private_nh("~");
  std::string topic_name1, topic_name2, topic_name3;
  int looprate;
  int sample_num;
  std::vector<double> radius_x, radius_y, target_x, target_y;

  private_nh.param("topic_name1", topic_name1,
                   std::string("radius1/raw_radius_data"));
  private_nh.param("topic_name2", topic_name2,
                   std::string("radius2/raw_radius_data"));
  private_nh.param("topic_name3", topic_name3,
                   std::string("radius3/raw_radius_data"));
  private_nh.param("loop_rate", looprate, 1);
  private_nh.param("sample_num", sample_num, 30);
  private_nh.param("minsigma_kpx", minsigma_kpx, 0.0);
  private_nh.param("maxsigma_kpx", maxsigma_kpx, 1000.0);
  private_nh.param("minsigma_kpy", minsigma_kpy, 0.0);
  private_nh.param("maxsigma_kpy", maxsigma_kpy, 1000.0);
  private_nh.param("minsigma_deg", minsigma_deg, 0.0);
  private_nh.param("maxsigma_deg", maxsigma_deg, 1000.0);
  private_nh.param("switch_radius1", switch_radius1, 1);
  private_nh.param("switch_radius2", switch_radius2, 1);
  private_nh.param("switch_radius3", switch_radius3, 0);

  n.getParam("radius_x", radius_x);
  n.getParam("radius_y", radius_y);
  n.getParam("target_x", target_x);
  n.getParam("target_y", target_y);

  _radius1_pos[0] = radius_x[0];
  _radius1_pos[1] = radius_y[0];
  _radius2_pos[0] = radius_x[1];
  _radius2_pos[1] = radius_y[1];
  _radius3_pos[0] = radius_x[2];
  _radius3_pos[1] = radius_y[2];
  _target1_pos[0] = target_x[0];
  _target1_pos[1] = target_y[0];
  _target2_pos[0] = target_x[1];
  _target2_pos[1] = target_y[1];
  _target3_pos[0] = target_x[2];
  _target3_pos[1] = target_y[2];

  radius_fusion radius1(_radius1_pos, _target1_pos, sample_num, switch_radius1,
                        minsigma_kpx, maxsigma_kpx, minsigma_kpy, maxsigma_kpy,
                        minsigma_deg, maxsigma_deg);
  radius_fusion radius2(_radius2_pos, _target2_pos, sample_num, switch_radius2,
                        minsigma_kpx, maxsigma_kpx, minsigma_kpy, maxsigma_kpy,
                        minsigma_deg, maxsigma_deg);
  radius_fusion radius3(_radius3_pos, _target3_pos, sample_num, switch_radius3,
                        minsigma_kpx, maxsigma_kpx, minsigma_kpy, maxsigma_kpy,
                        minsigma_deg, maxsigma_deg);
  ros::Subscriber sub_radius1 =
      n.subscribe(topic_name1, 1, &radius_fusion::callback, &radius1);
  ros::Subscriber sub_radius2 =
      n.subscribe(topic_name2, 1, &radius_fusion::callback, &radius2);
  ros::Subscriber sub_radius3 =
      n.subscribe(topic_name3, 1, &radius_fusion::callback, &radius3);

  dynamic_reconfigure::Server<sensor::radius_fusionConfig>
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
    radius1.update_parameter(_radius1_pos, _target1_pos, switch_radius1,
                             minsigma_kpx, maxsigma_kpx, minsigma_kpy,
                             maxsigma_kpy, minsigma_deg, maxsigma_deg);
    radius2.update_parameter(_radius2_pos, _target2_pos, switch_radius2,
                             minsigma_kpx, maxsigma_kpx, minsigma_kpy,
                             maxsigma_kpy, minsigma_deg, maxsigma_deg);
    radius3.update_parameter(_radius3_pos, _target3_pos, switch_radius3,
                             minsigma_kpx, maxsigma_kpx, minsigma_kpy,
                             maxsigma_kpy, minsigma_deg, maxsigma_deg);

    radius1.calculate_sigma();
    radius2.calculate_sigma();
    radius3.calculate_sigma();
    sigma_kpx[0] = radius1.get_sigma_kpx();
    sigma_kpx[1] = radius2.get_sigma_kpx();
    sigma_kpx[2] = radius3.get_sigma_kpx();
    sigma_kpy[0] = radius1.get_sigma_kpy();
    sigma_kpy[1] = radius2.get_sigma_kpy();
    sigma_kpy[2] = radius3.get_sigma_kpy();
    sigma_deg[0] = radius1.get_sigma_kpdeg();
    sigma_deg[1] = radius2.get_sigma_kpdeg();
    sigma_deg[2] = radius3.get_sigma_kpdeg();
    kpx[0] = radius1.get_kpx();
    kpx[1] = radius2.get_kpx();
    kpx[2] = radius3.get_kpx();
    kpy[0] = radius1.get_kpy();
    kpy[1] = radius2.get_kpy();
    kpy[2] = radius3.get_kpy();
    deg[0] = radius1.get_kpdeg();
    deg[1] = radius2.get_kpdeg();
    deg[2] = radius3.get_kpdeg();

    // std::cout << "sigma kpx0    " << sigma_kpx[0] << "  sigma kpx1      "
    //           << sigma_kpx[1] << "   sigma kpx2     " << sigma_kpx[2]
    //           << std::endl;
    inner_switch[0] = radius1.get_inner_switch();
    inner_switch[1] = radius2.get_inner_switch();
    inner_switch[2] = radius3.get_inner_switch();
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
