#include <dynamic_reconfigure/server.h>
#include <ros/ros.h>
#include <sensor/imu_fusionConfig.h>
#include <sensor/imu_msgs.h>
#include <std_msgs/Float64.h>
#include "sensor/imufusion.h"
std::vector<double> imu1_roll, imu1_pitch, imu1_head, imu2_roll, imu2_pitch,
    imu2_head, imu3_roll, imu3_pitch, imu3_head;
double roll[3], pitch[3], head[3], sigma_roll[3], sigma_pitch[3], sigma_head[3],
    omega_roll[3], omega_pitch[3], omega_head[3];
double fused_roll, fused_pitch, fused_head;
int switch_imu1, switch_imu2, switch_imu3;
double minsigma_roll, maxsigma_roll, minsigma_pitch, maxsigma_pitch,
    minsigma_head, maxsigma_head;
int inner_switch[3];
//这个是求方差的
void dynamic_callback(sensor::imu_fusionConfig &config, uint32_t level) {
  switch_imu1 = (int)config.switch_imu1_bool;
  switch_imu2 = (int)config.switch_imu2_bool;
  switch_imu3 = (int)config.switch_imu3_bool;
  maxsigma_head = config.maxsigma_head;
  minsigma_head = config.minsigma_head;
  maxsigma_roll = config.maxsigma_roll;
  minsigma_roll = config.minsigma_roll;
  maxsigma_pitch = config.maxsigma_pitch;
  minsigma_pitch = config.minsigma_pitch;
}
void run_fusion() {
  //判断有几个sensor，进而确定权值
  double sum_weight;
  sum_weight = 1 / sigma_roll[0] * inner_switch[0] +
               1 / sigma_roll[1] * inner_switch[1] +
               1 / sigma_roll[2] * inner_switch[2];
  std::cout << "inner_switch0:  " << inner_switch[0] << std::endl;
  std::cout << "inner_switch1:  " << inner_switch[1] << std::endl;
  std::cout << "inner_switch2:  " << inner_switch[2] << std::endl;

  std::cout << "sum sum_weight:  " << sum_weight << std::endl;
  if (sum_weight == 0)
    ROS_INFO_STREAM("NO IMU DATA");
  else if (sum_weight != 0) {
    for (int i = 0; i < 3; i++) {
      omega_roll[i] = 1 / sigma_roll[i] * inner_switch[i] / sum_weight;
      std::cout << "omega:  " << omega_roll[i] << std::endl;
      std::cout << "sigma_roll:  " << sigma_roll[i] << std::endl;
    }
  }

  sum_weight = 1 / sigma_pitch[0] * inner_switch[0] +
               1 / sigma_pitch[1] * inner_switch[1] +
               1 / sigma_pitch[2] * inner_switch[2];
  if (sum_weight == 0)
    ROS_INFO_STREAM("NO IMU DATA");
  else if (sum_weight != 0) {
    for (int i = 0; i < 3; i++) {
      omega_pitch[i] = 1 / sigma_pitch[i] * inner_switch[i] / sum_weight;
    }
  }
  sum_weight = 1 / sigma_head[0] * inner_switch[0] +
               1 / sigma_head[1] * inner_switch[1] +
               1 / sigma_head[2] * inner_switch[2];
  if (sum_weight == 0)
    ROS_INFO_STREAM("NO IMU DATA");
  else if (sum_weight != 0) {
    for (int i = 0; i < 3; i++) {
      omega_head[i] = 1 / sigma_head[i] * inner_switch[i] / sum_weight;
    }
  }

  fused_roll = roll[0] * omega_roll[0] + roll[1] * omega_roll[1] +
               roll[2] * omega_roll[2];  // if (sigma_latitude[0] == 0)
  fused_pitch = pitch[0] * omega_pitch[0] + pitch[1] * omega_pitch[1] +
                pitch[2] * omega_pitch[2];  // if (sigma_latitude[0] == 0)
  fused_head = head[0] * omega_head[0] + head[1] * omega_head[1] +
               head[2] * omega_head[2];  // if (sigma_latitude[0] == 0)
}

int main(int argv, char **argc) {
  ros::init(argv, argc, "imu_fusion");
  ros::NodeHandle n;
  ros::NodeHandle private_nh("~");
  std::string topic_name1, topic_name2, topic_name3;
  int looprate;
  int sample_num;

  private_nh.param("topic_name1", topic_name1, std::string("imu1/raw_imu"));
  private_nh.param("topic_name2", topic_name2, std::string("imu2/raw_imu"));
  private_nh.param("topic_name3", topic_name3, std::string("imu3/raw_imu"));
  private_nh.param("loop_rate", looprate, 50);
  private_nh.param("sample_num", sample_num, 50);
  private_nh.param("minsigma_roll", minsigma_roll, 0.0);
  private_nh.param("maxsigma_roll", maxsigma_roll, 50.0);
  private_nh.param("minsigma_pitch", minsigma_pitch, 0.0);
  private_nh.param("maxsigma_pitch", maxsigma_pitch, 50.0);
  private_nh.param("minsigma_head", minsigma_head, 0.0);
  private_nh.param("maxsigma_head", maxsigma_head, 50.0);
  private_nh.param("switch_imu1", switch_imu1, 1);
  private_nh.param("switch_imu2", switch_imu2, 0);
  private_nh.param("switch_imu3", switch_imu3, 0);

  imu_fusion imu1(sample_num, switch_imu1, minsigma_roll, maxsigma_roll,
                  minsigma_pitch, maxsigma_pitch, minsigma_head, maxsigma_head);
  imu_fusion imu2(sample_num, switch_imu2, minsigma_roll, maxsigma_roll,
                  minsigma_pitch, maxsigma_pitch, minsigma_head, maxsigma_head);
  imu_fusion imu3(sample_num, switch_imu3, minsigma_roll, maxsigma_roll,
                  minsigma_pitch, maxsigma_pitch, minsigma_head, maxsigma_head);
  ros::Subscriber sub_imu1 =
      n.subscribe(topic_name1, 1, &imu_fusion::callback, &imu1);
  ros::Subscriber sub_imu2 =
      n.subscribe(topic_name2, 1, &imu_fusion::callback, &imu2);
  ros::Subscriber sub_imu3 =
      n.subscribe(topic_name3, 1, &imu_fusion::callback, &imu3);

  dynamic_reconfigure::Server<sensor::imu_fusionConfig> server;
  server.setCallback(boost::bind(&dynamic_callback, _1, _2));
  ros::Publisher pub_roll = n.advertise<std_msgs::Float64>("imu_roll", 1);
  ros::Publisher pub_pitch = n.advertise<std_msgs::Float64>("imu_pitch", 1);
  ros::Publisher pub_head = n.advertise<std_msgs::Float64>("imu_head", 1);

  std_msgs::Float64 msg_roll;
  std_msgs::Float64 msg_pitch;
  std_msgs::Float64 msg_head;

  ros::Rate loop_rate(looprate);
  while (ros::ok()) {
    imu1.update_parameter(switch_imu1, minsigma_roll, maxsigma_roll,
                          minsigma_pitch, maxsigma_pitch, minsigma_head,
                          maxsigma_head);
    imu2.update_parameter(switch_imu2, minsigma_roll, maxsigma_roll,
                          minsigma_pitch, maxsigma_pitch, minsigma_head,
                          maxsigma_head);
    imu3.update_parameter(switch_imu3, minsigma_roll, maxsigma_roll,
                          minsigma_pitch, maxsigma_pitch, minsigma_head,
                          maxsigma_head);

    imu1.calculate_sigma();
    imu2.calculate_sigma();
    imu3.calculate_sigma();
    sigma_roll[0] = imu1.get_sigma_roll();
    sigma_roll[1] = imu2.get_sigma_roll();
    sigma_roll[2] = imu3.get_sigma_roll();
    sigma_pitch[0] = imu1.get_sigma_pitch();
    sigma_pitch[1] = imu2.get_sigma_pitch();
    sigma_pitch[2] = imu3.get_sigma_pitch();
    sigma_head[0] = imu1.get_sigma_head();
    sigma_head[1] = imu2.get_sigma_head();
    sigma_head[2] = imu3.get_sigma_head();
    roll[0] = imu1.get_roll();
    roll[1] = imu2.get_roll();
    roll[2] = imu3.get_roll();
    pitch[0] = imu1.get_pitch();
    pitch[1] = imu2.get_pitch();
    pitch[2] = imu3.get_pitch();
    head[0] = imu1.get_head();
    head[1] = imu2.get_head();
    head[2] = imu3.get_head();
    inner_switch[0] = imu1.get_inner_switch();
    inner_switch[1] = imu2.get_inner_switch();
    inner_switch[2] = imu3.get_inner_switch();

    run_fusion();
   if(!std::isnan(fused_roll))
    msg_roll.data = fused_roll;  //弧度制
   if(!std::isnan(fused_pitch))

    msg_pitch.data = fused_pitch;
   if(!std::isnan(fused_head))

    msg_head.data = fused_head;


  
    pub_roll.publish(msg_roll);
    pub_pitch.publish(msg_pitch);
    pub_head.publish(msg_head);
    ROS_INFO_STREAM("fused_roll    " << fused_roll / M_PI * 180);
    ROS_INFO_STREAM("fused_pitch   " << fused_pitch / M_PI * 180);
    ROS_INFO_STREAM("fused_heading " << fused_head / M_PI * 180);
    ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
}
