#include "ros/ros.h"
#include "std_msgs/Float64.h"
#include "sensor/imu_msgs.h"
#include <cmath>
//话题回调函数
//

double roll,pitch,head;

void rollCallback(const std_msgs::Float64 &msg){
    roll=msg.data/180*M_PI;
	ROS_INFO("roll  [%lf]", roll*180/M_PI);
}
void pitchCallback(const std_msgs::Float64 &msg){
    pitch=msg.data/180*M_PI;
	ROS_INFO("pitch    [%lf]", pitch*180/M_PI);
}
void headCallback(const std_msgs::Float64 &msg){
	if(msg.data<=0)
    head=(-msg.data)/180*M_PI;
   else
   	head=(360-msg.data)/180*M_PI;
   ROS_INFO("head [%lf]",head*180/M_PI);
}
 
int main(int argc, char **argv)
{
	
	ros::init(argc, argv, "imu_driver_rpy");	
	ros::NodeHandle n;	//节点句柄实例化
    sensor::imu_msgs imu_data;
	ros::Subscriber sub1 = n.subscribe("roll_raw_data", 10, rollCallback);
	ros::Subscriber sub2 = n.subscribe("pitch_raw_data", 10, pitchCallback);	
	ros::Subscriber sub3 = n.subscribe("yaw_raw_data", 10, headCallback);
	ros::Publisher pub_navsat=n.advertise<sensor::imu_msgs>("imu1/raw_imu",20);
	ros::Rate loop_rate(20);
	while(ros::ok()){
	imu_data.roll=roll;
	imu_data.pitch=pitch;
	imu_data.head=head;	
    pub_navsat.publish(imu_data);
	 ros::spinOnce();	//程序进入循环，直到ros::ok()返回false，进程结束
	  loop_rate.sleep();
	}
 
	return 0;
}