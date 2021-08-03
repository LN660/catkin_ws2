#ifndef _RADIUSFUSION_H_
#define _CYSCANFUSION_H_
#include <geometry_msgs/PointStamped.h>
#include <ros/ros.h>
#include <sensor/cyscan_msgs.h>
#include <cmath>

class cyscan_fusion {
 private:
  double kpx;
  double kpy;
  double kpdeg;
  double cyscan_pos[2];
  double target_pos[2];
  int sample_num;
  double sigma_kpx = 0;
  double sigma_kpy = 0;
  double sigma_kpdeg = 0;
  double maxsigma_kpx, minsigma_kpx, maxsigma_kpy, minsigma_kpy, maxsigma_deg,
      minsigma_deg;
  int switch_cyscan, inner_switch;
  std::vector<double> kpx_array, kpy_array, kpdeg_array;

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
    // std::cout << "sigma***:  " << sigma << std::endl;
    if (!std::isnormal(sigma) || sigma == 0) {
      sigma = maxsigma_kpx * n + n;
    }
    // std::cout << "sigma!!!:  " << sigma << std::endl;
    return sigma / n;
  }

 public:
  explicit cyscan_fusion(
      const double _cyscan_pos[2], const double _target_pos[2],
      const int &_sample_num, const int &_switch_cyscan,
      const double &_minsigma_kpx, const double &_maxsigma_kpx,
      const double &_minsigma_kpy, const double &_maxsigma_kpy,
      const double &_minsigma_deg,
      const double &_maxsigma_deg)  // 如果要在函数中读取地址的话 必须引用
      : sample_num(_sample_num),
        switch_cyscan(_switch_cyscan),
        minsigma_kpx(_minsigma_kpx),
        maxsigma_kpx(_maxsigma_kpx),
        minsigma_kpy(_minsigma_kpy),
        maxsigma_kpy(_maxsigma_kpy),
        minsigma_deg(_minsigma_deg),
        maxsigma_deg(_maxsigma_deg) {
    kpx = 0;
    kpy = 0;
    kpdeg = 0;
    for (int i = 0; i < 2; i++) {
      cyscan_pos[i] = _cyscan_pos[i];
      target_pos[i] = _target_pos[i];
    }

    for (int i = 0; i < sample_num; i++)  //初始化
    {
      kpx_array.push_back(0);
      kpy_array.push_back(0);
      kpdeg_array.push_back(0);
    }
    std::cout << "switch_cyscan " << switch_cyscan << std::endl;
  }

  void callback(const sensor::cyscan_msgs &msg) {
    double temp_x, temp_y, temp_deg, temp_deg_sigma;
    temp_x = msg.x;
    temp_y = msg.y;
    temp_deg = msg.deg;
    // std::cout << "传入的数据    " << temp_deg << std::endl;
    temp_deg_sigma = asin(sin(msg.deg / 180 * M_PI));
    // kpx = target_pos[0] * cos(temp_deg) + target_pos[1] * sin(temp_deg) +
    //       temp_x + cyscan_pos[0];
    // kpy = target_pos[1] * cos(temp_deg) - target_pos[0] * sin(temp_deg) +
    //       temp_y + cyscan_pos[1];
    // kpx = target_pos[0] + target_pos[1] + temp_x + cyscan_pos[0];
    // kpy = target_pos[1] - target_pos[0] + temp_y + cyscan_pos[1];
    kpx = -cyscan_pos[0] * cos(temp_deg / 180 * M_PI) -
          cyscan_pos[1] * sin(temp_deg / 180 * M_PI) + target_pos[0] + temp_x;
    kpy = -cyscan_pos[1] * cos(temp_deg / 180 * M_PI) +
          cyscan_pos[0] * sin(temp_deg / 180 * M_PI) + target_pos[1] + temp_y;
    std::cout << "融合前的数据  kpx   " << kpx << std::endl;
    std::cout << "融合前的数据kpy    " << kpy << std::endl;

    std::cout << "target_pos[0]     " << target_pos[0] << std::endl;
    std::cout << "target_pos[1]     " << target_pos[1] << std::endl;
    std::cout << "cyscan_pos[0]     " << cyscan_pos[0] << std::endl;
    std::cout << "cyscan_pos[1]     " << cyscan_pos[1] << std::endl;

    kpdeg = temp_deg;
    for (int i = 0; i < sample_num - 1;
         i++) {  // update the data of cyscan1 kpy
      kpx_array[sample_num - i - 1] = kpx_array[sample_num - i - 2];
      kpy_array[sample_num - i - 1] = kpy_array[sample_num - i - 2];
      kpdeg_array[sample_num - i - 1] = kpdeg_array[sample_num - i - 2];
    }
    if (std::isnormal(kpx))
      kpx_array[0] = kpx;
    else
      kpx_array[0] = kpx_array[1];
    if (std::isnormal(kpy))
      kpy_array[0] = kpy;
    else
      kpy_array[0] = kpy_array[1];
    if (std::isnormal(kpdeg))
      kpdeg_array[0] = temp_deg_sigma;
    else
      kpdeg_array[0] = kpdeg_array[1];
  }

  void calculate_sigma() {
    //计算方差 加kpdeg
    // for (int i = 0; i != sample_num; i++)
    // {
    //     std::cout << std::fixed << std::setprecision(3) << kpx_array[i] << "
    //     ";
    // }
    sigma_kpx = variance(kpx_array, sample_num);
    sigma_kpy = variance(kpy_array, sample_num);
    sigma_kpdeg = variance(kpdeg_array, sample_num);
    inner_switch = switch_cyscan;
    std::cout << "inner_switch new" << inner_switch << std::endl;
    if (!((sigma_kpx > minsigma_kpx && sigma_kpx < maxsigma_kpx) &&
          (sigma_kpy > minsigma_kpy && sigma_kpy < maxsigma_kpy) &&
          (sigma_kpdeg > minsigma_deg && sigma_kpdeg < maxsigma_deg) &&
          std::isnormal(sigma_kpx) && std::isnormal(sigma_kpy) &&
          std::isnormal(sigma_kpdeg)))
      inner_switch = 0;  // 方差若不在范围内 则权值强制归零
                         // std::cout << sigma_kpx << std::endl;
    // std::cout << "minsigma_kpx   " << minsigma_kpx << std::endl;
    // std::cout << "maxsigma_kpx   " << maxsigma_kpx << std::endl;
    // std::cout << "minsigma_kpy   " << minsigma_kpx << std::endl;
    // std::cout << "maxsigma_kpy  " << maxsigma_kpx << std::endl;
    // std::cout << "minsigma_kpdeg   " << minsigma_deg << std::endl;
    // std::cout << "maxsigma_kpdeg  " << maxsigma_deg << std::endl;
    // std::cout << "isnormal(sigma_kpx)   " << std::isnormal(sigma_kpx)
    //           << std::endl;
    // std::cout << "isnormal(sigma_kpy)   " << std::isnormal(sigma_kpy)
    //           << std::endl;
    // std::cout << "isnormal(sigma_kdeg)   " << std::isnormal(sigma_kpdeg)
    //           << std::endl;
    // std::cout << "inner_switch" << inner_switch << std::endl;
  }
  double get_kpx() { return kpx; }
  double get_kpy() { return kpy; }
  double get_kpdeg() { return kpdeg; }
  double get_kpx_array(const int &i) { return kpx_array[i]; }
  double get_kpy_array(const int &i) { return kpy_array[i]; }
  double get_kpdeg_array(const int &i) { return kpdeg_array[i]; }

  double get_sigma_kpx() { return sigma_kpx; }
  double get_sigma_kpy() { return sigma_kpy; }
  double get_sigma_kpdeg() { return sigma_kpdeg; }
  int get_inner_switch() { return inner_switch; }
  void update_parameter(
      const double new_cyscan_pos[2], const double new_target_pos[2],
      const int &new_switch_cyscan,  //这部分是在实现什么功能呢
      const double &new_minsigma_kpx, const double &new_maxsigma_kpx,
      const double &new_minsigma_kpy, const double &new_maxsigma_kpy,
      const double &new_minsigma_kpdeg, const double &new_maxsigma_kpdeg) {
    cyscan_pos[0] = new_cyscan_pos[0];
    cyscan_pos[1] = new_cyscan_pos[1];
    target_pos[0] = new_target_pos[0];
    target_pos[1] = new_target_pos[1];
    switch_cyscan = new_switch_cyscan;
    minsigma_kpx = new_minsigma_kpx;
    maxsigma_kpx = new_maxsigma_kpx;
    minsigma_kpy = new_minsigma_kpy;
    maxsigma_kpy = new_maxsigma_kpy;
    minsigma_deg = new_minsigma_kpdeg;
    maxsigma_deg = new_maxsigma_kpdeg;
  }
};
#endif