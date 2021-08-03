#!/usr/bin/env python
#coding=UTF-8

import rospy
import tf
from tf.transformations import *
from sensor_msgs.msg import Imu
from std_msgs.msg import Float64


def callback(data):
	
    pitch_pub=rospy.Publisher('pitch_raw_data',Float64,queue_size=10) 
    yaw_pub=rospy.Publisher('yaw_raw_data',Float64,queue_size=10) 
    #这个函数是tf中的,可以将四元数转成欧拉角
    (r,p,y) = tf.transformations.euler_from_quaternion((data.orientation.x,data.orientation.y,data.orientation.z,data.orientation.w))
    #由于是弧度制，下面将其改成角度制看起来更方便
    pitch=r*180/3.1415926
    roll=p*180/3.1415926
    yaw=y*180/3.1415926
    rospy.loginfo("Pitch = %f,Roll = %f, Yaw1 = %f",pitch,roll,yaw)
    roll_pub=rospy.Publisher('roll_raw_data',Float64,queue_size=10)
    pitch_pub=rospy.Publisher('pitch_raw_data',Float64,queue_size=10) 
    yaw_pub=rospy.Publisher('yaw_raw_data',Float64,queue_size=10)  
    roll_pub.publish(roll)
    pitch_pub.publish(pitch)
    yaw_pub.publish(yaw)
def get_imu():
    rospy.init_node('get_imu', anonymous=True)
    rospy.Subscriber("/handsfree/imu", Imu, callback) #接受topic名称
    rospy.spin()

if __name__ == '__main__':
    get_imu()
