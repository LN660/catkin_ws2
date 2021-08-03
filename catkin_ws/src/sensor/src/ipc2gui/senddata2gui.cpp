#include <arpa/inet.h>
#include <math.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include "sensor/OSserverData.h"

#include <ros/ros.h>

#include <std_msgs/Float64.h>
#include <std_msgs/String.h>
#include <cmath>
#include <iostream>

#define BUF_SIZE 1600
std::string buffer_ship1;
std::string buffer_ship2;
std::string buffer_ship3;
std::string buffer_sub;

systemInfo _systemInfo{
  1,  // wlan
  0,  //   double time;
  1,  //   int all_ready;
};

double getNowTime()
{
  double timestring;
  double tmp;
  time_t tt;
  time(&tt);
  tt = tt + 8 * 3600;  // transform the time zone
  tm *t = gmtime(&tt);
  // std::cout << tt << std::endl;
  // printf("%d-%02d-%02d %02d:%02d:%02d\n",
  //        t->tm_year + 1900,
  //        t->tm_mon + 1,
  //        t->tm_mday,
  //        t->tm_hour,
  //        t->tm_min,
  //        t->tm_sec);

  timestring = t->tm_sec + t->tm_min * 100 + t->tm_hour * 10000 + t->tm_mday * 1000000 + (t->tm_mon + 1) * 100000000 +
               (t->tm_year + 1900) * 10000000000;
  return timestring;
}

void ship1data_Callback(const std_msgs::String::ConstPtr &msg)
{
  buffer_ship1 = msg->data;
}
void ship2data_Callback(const std_msgs::String::ConstPtr &msg)
{
  buffer_ship2 = msg->data;
}
void ship3data_Callback(const std_msgs::String::ConstPtr &msg)
{
  buffer_ship3 = msg->data;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "sendData2gui");
  ros::NodeHandle nh;
  ros::NodeHandle private_nh("~");
  int _port;
  private_nh.param("port", _port, 10089);
  // ros::Publisher localdata_pub =
  // nh.advertise<std_msgs::String>("localdata", 1);

  char bufsend[1600] = { 0 };
  //////////////////////////////////////////////////////////需要完善的
  //订阅需要的消息
  ros::Subscriber ship1data_sub = nh.subscribe("ship1_data", 1, ship1data_Callback);
  ros::Subscriber ship2data_sub = nh.subscribe("ship2_data", 1, ship2data_Callback);
  ros::Subscriber ship3data_sub = nh.subscribe("ship3_data", 1, ship3data_Callback);

  // socket通信

  //创建套接字
  int serv_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  //向服务器（特定的IP和端口）发起请求
  struct sockaddr_in serv_addr;
  memset(&serv_addr, 0, sizeof(serv_addr));       //每个字节都用0填充
  serv_addr.sin_family = AF_INET;                 //使用IPv4地址
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);  //具体的IP地址
  serv_addr.sin_port = htons(_port);              //端口
  bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

  listen(serv_sock, 5);
  printf("waitting client...\n");
  struct sockaddr_in clnt_addr;
  socklen_t clnt_addr_size = sizeof(clnt_addr);
  int clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_size);
  if (-1 == clnt_sock)
  {
    printf("error\n");
    return 2;
  }
  printf("connectc client success..\n");
  //数据的处理
  ros::Rate loop_rate(5);
  while (ros::ok())
  {
    // 对字符串数据进行编辑
    buffer_ship1 = buffer_ship1.substr(10);
    // cout << "ship1d " << buffer_ship1 << endl;
    // // str.erase(str.end() - 1);
    buffer_ship1 = buffer_ship1.substr(0, buffer_ship1.length() - 1);
    // cout << "ship1 data 去尾 " << buffer_ship1 << endl;
    buffer_ship2 = buffer_ship2.substr(10);
    buffer_ship2 = buffer_ship2.substr(0, buffer_ship2.length() - 1);
    buffer_ship3 = buffer_ship3.substr(10);
    // cout << "ship1d " << buffer_ship2 << endl;
    buffer_ship3 = buffer_ship3.substr(0, buffer_ship3.length() - 2);
    // cout << "ship1d " << buffer_ship3 << endl;
    buffer_sub = buffer_ship1 + buffer_ship2 + buffer_ship3;
    std::cout << "合并完成的数据为" << buffer_sub << std::endl;

    _systemInfo.now_time = getNowTime();
    long int timecut = _systemInfo.now_time;
    buffer_sub = "SKLOEA" + buffer_sub +=
        "," + std::to_string(_systemInfo.wlan) + std::to_string(timecut) + std::to_string(_systemInfo.all_ready) + ",*";

    strcpy(bufsend, buffer_sub.c_str());

    // char bufsend[] = buffer;
    write(clnt_sock, bufsend, sizeof(bufsend));
    std::cout << "Message send to gui:" << bufsend << std::endl;

    //关闭套接字

    memset(bufsend, 0, sizeof(bufsend));

    ros::spinOnce();
    loop_rate.sleep();
  }
  close(clnt_sock);
  close(serv_sock);
  return 0;
}