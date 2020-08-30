#!/usr/bin/env python


"""
0: left/right(1 to -1)
1: backward/forward (-1 to 1)
"""

# ROS Imports
import rospy
from geometry_msgs.msg import Twist
from sensor_msgs.msg import Joy

class Teleop:
    def __init__(self):
        rospy.init_node('teleop')

        self.joy_sub = rospy.Subscriber("/joy", Joy, self.joyCB)
        self.twist_pub = rospy.Publisher("/cmd_vel", Twist, queue_size=10)

    def joyCB(self, msg):
        joy_lin = msg.axes[1] * 0.5 # scale by max linear velocity
        joy_ang = msg.axes[0] * 4   # scale by max angular velocity

        cmd = Twist()
        cmd.linear.x = joy_lin
        cmd.angular.z = joy_ang
        self.twist_pub.publish(cmd)

if __name__ == "__main__":
    teleop = Teleop()
    rospy.spin()
