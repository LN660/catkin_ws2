#ifndef _IMUFUSION_H_
#define _IMUFUSION_H_

#include <ros/ros.h>
#include <sensor/imu_msgs.h>
#include <cmath>

class imu_fusion {
 private:
  double roll;
  double pitch;
  double head,head_sigma;
  int sample_num;
  double sigma_roll = 0;
  double sigma_pitch = 0;
  double sigma_head = 0;
  double maxsigma_roll, minsigma_roll, maxsigma_pitch, minsigma_pitch,
      maxsigma_head, minsigma_head;
  int switch_imu, inner_switch;
  std::vector<double> roll_array, pitch_array, head_array;

  double ave(std::vector<double> a, int n) {
    double sum = 0;
    for (int i = 0; i < n; i++) {
      sum += a[i];
    }
    std::cout << "sample_num" << n << std::endl;

    return sum / n;
  }  //平均值

  double variance(std::vector<double> a, int n) {
    double sigma = 0;
    double average = ave(a, n);
    for (int i = 0; i < n; i++) sigma += (a[i] - average) * (a[i] - average);
    std::cout << "sigma***:  " << sigma << std::endl;
    if (!std::isnormal(sigma) || sigma == 0) {
      sigma = maxsigma_roll * n + n;
    }
    std::cout << "sigma!!!:  " << sigma << std::endl;
    return sigma / n;
  }

 public:
  explicit imu_fusion(
      const int &_sample_num, const int &_switch_imu,
      const double &_minsigma_roll, const double &_maxsigma_roll,
      const double &_minsigma_pitch, const double &_maxsigma_pitch,
      const double &_minsigma_head,
      const double &_maxsigma_head)  // 如果要在函数中读取地址的话 必须引用
      : sample_num(_sample_num),
        switch_imu(_switch_imu),
        minsigma_roll(_minsigma_roll),
        maxsigma_roll(_maxsigma_roll),
        minsigma_pitch(_minsigma_pitch),
        maxsigma_pitch(_maxsigma_pitch),
        minsigma_head(_minsigma_head),
        maxsigma_head(_maxsigma_head) {
    roll = 0;
    pitch = 0;
    head = 0;
    for (int i = 0; i < sample_num; i++)  //初始化
    {
      roll_array.push_back(0);
      pitch_array.push_back(0);
      head_array.push_back(0);
    }
  }

  void callback(const sensor::imu_msgs &msg) {
    roll = msg.roll;
    pitch = msg.pitch;
    head=msg.head;
    head_sigma = asin(sin(msg.head));
    // sin_head=sin(msg.head);
    for (int i = 0; i < sample_num - 1; i++) {  // update the data of imu1 pitch
      roll_array[sample_num - i - 1] = roll_array[sample_num - i - 2];
      pitch_array[sample_num - i - 1] = pitch_array[sample_num - i - 2];
      head_array[sample_num - i - 1] = head_array[sample_num - i - 2];
    }
    if (std::isnormal(roll))
      roll_array[0] = roll;
    else
      roll_array[0] = roll_array[1];
    if (std::isnormal(pitch))
      pitch_array[0] = pitch;
    else
      pitch_array[0] = pitch_array[1];
    if (std::isnormal(head))
      head_array[0] = head_sigma;
    else
      head_array[0] = head_array[1];
  }

  void calculate_sigma() {
    //计算方差 加head
    // for (int i = 0; i != sample_num; i++)
    // {
    //     std::cout << std::fixed << std::setprecision(3) << roll_array[i] << "
    //     ";
    // }
    sigma_roll = variance(roll_array, sample_num);
    sigma_pitch = variance(pitch_array, sample_num);
    sigma_head = variance(head_array, sample_num);
    inner_switch = switch_imu;
    std::cout << "inner_switch new" << switch_imu << std::endl;
    if (!((sigma_roll > minsigma_roll && sigma_roll < maxsigma_roll) &&
          (sigma_pitch > minsigma_pitch && sigma_pitch < maxsigma_pitch) &&
          (sigma_head > minsigma_head && sigma_head < maxsigma_head) &&
          std::isnormal(sigma_roll) && std::isnormal(sigma_pitch) &&
          std::isnormal(sigma_head)))
      inner_switch = 0;  // 方差若不在范围内 则权值强制归零
    // std::cout << sigma_roll << std::endl;
    // std::cout << "inner_switch" << inner_switch << std::endl;
  }
  double get_roll() { return roll; }
  double get_pitch() { return pitch; }
  double get_head() { return head; }
  double get_roll_array(const int &i) { return roll_array[i]; }
  double get_pitch_array(const int &i) { return pitch_array[i]; }
  double get_head_array(const int &i) { return head_array[i]; }

  double get_sigma_roll() { return sigma_roll; }
  double get_sigma_pitch() { return sigma_pitch; }
  double get_sigma_head() { return sigma_head; }
  int get_inner_switch() { return inner_switch; }
  void update_parameter(const int &new_switch_imu,
                        const double &new_minsigma_roll,
                        const double &new_maxsigma_roll,
                        const double &new_minsigma_pitch,
                        const double &new_maxsigma_pitch,
                        const double &new_minsigma_head,
                        const double &new_maxsigma_head) {
    switch_imu = new_switch_imu;
    minsigma_roll = new_minsigma_roll;
    maxsigma_roll = new_maxsigma_roll;
    minsigma_pitch = new_minsigma_pitch;
    maxsigma_pitch = new_maxsigma_pitch;
    minsigma_head = new_minsigma_head;
    maxsigma_head = new_maxsigma_head;
  }
};
#endif