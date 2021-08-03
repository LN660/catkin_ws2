#include <arpa/inet.h>
#include <math.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <ros/ros.h>

#include <std_msgs/Float64.h>
#include <std_msgs/String.h>
#include <cmath>
#include <iostream>

#define BUF_SIZE 500
std::string buffer;
void shipdata_Callback(const std_msgs::String::ConstPtr &msg)
{
  buffer = msg->data;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "sendData2ship3");
  ros::NodeHandle nh;
  ros::NodeHandle private_nh("~");
  int _port;
  private_nh.param("port", _port, 10087);
  // ros::Publisher localdata_pub =
  // nh.advertise<std_msgs::String>("localdata", 1);

  char bufsend[500] = { 0 };
  //////////////////////////////////////////////////////////需要完善的
  //订阅需要的消息
  ros::Subscriber shipdata_sub = nh.subscribe("ship1_data", 1, shipdata_Callback);

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
    strcpy(bufsend, buffer.c_str());

    write(clnt_sock, bufsend, sizeof(bufsend));
    std::cout << "Message send to  ship3 :" << bufsend << std::endl;

    //关闭套接字

    memset(bufsend, 0, sizeof(bufsend));

    ros::spinOnce();
    loop_rate.sleep();
  }
  close(clnt_sock);
  close(serv_sock);
  return 0;
}
