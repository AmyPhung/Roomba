#!/usr/bin/env python


"""
0: left/right(1 to -1)
1: backward/forward (-1 to 1)
"""

# ROS Imports
import rospy
from geometry_msgs.msg import Twist
from sensor_msgs.msg import Joy

sign = lambda x: (1, -1)[x < 0]

class Teleop:
    def __init__(self):
        rospy.init_node('teleop')

        self.joy_sub = rospy.Subscriber("/joy", Joy, self.joyCB)
        self.twist_pub = rospy.Publisher("/cmd_vel", Twist, queue_size=10)

    def joyCB(self, msg):
        joy_lin = msg.axes[1] * 0.2 # scale by max linear velocity (0.5 max)
        joy_ang = sign(joy_lin) * msg.axes[0] * 1   # scale by max angular velocity (4 max)

        cmd = Twist()
        cmd.linear.x = joy_lin
        cmd.angular.z = joy_ang
        self.twist_pub.publish(cmd)

if __name__ == "__main__":
    teleop = Teleop()
    rospy.spin()
