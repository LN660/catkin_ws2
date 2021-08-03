#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define BUF_SIZE 500

#include <ros/ros.h>
#include <std_msgs/String.h>
#include <iostream>
#include <sstream>

int main(int argc, char **argv) {
  ros::init(argc, argv, "guidata");
  ros::NodeHandle n;
  ros::Publisher recvdata_pub = n.advertise<std_msgs::String>("ship2_data", 1);

  //创建套接字
  int sock = socket(AF_INET, SOCK_STREAM, 0);
  //向服务器（特定的IP和端口）发起请求
  struct sockaddr_in serv_addr;
  memset(&serv_addr, 0, sizeof(serv_addr));  //每个字节都用0填充
  serv_addr.sin_family = AF_INET;            //使用IPv4地址
  serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");  //具体的IP地址
  serv_addr.sin_port = htons(10086);                   //端口

  char bufrecv[BUF_SIZE] = {0};

  ros::Rate loop_rate(1);
  while (ros::ok()) {
    std_msgs::String msg;
    //读取服务器传回的数据
    connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    read(sock, bufrecv, 500);

    printf("Message form server1: %s\n", bufrecv);
    //这里的buffer——recv可以直接用sscanf函数吗？
    msg.data = bufrecv;
    recvdata_pub.publish(msg);
    // printf("Message form server2: %s\n", msg.data.c_str());
    memset(bufrecv, 0, BUF_SIZE);

    //关闭套接字
    ros::spinOnce();
    loop_rate.sleep();
  }
  close(sock);
  return 0;
}

