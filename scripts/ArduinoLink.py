#!/usr/bin/env python

# ROS Imports
import rospy
from geometry_msgs.msg import Twist

# Python Imports
import serial, time


class ArduinoLink:
    def __init__(self, port, baud, rate=10):
        # TODO: Implement timeout & heartbeat
        self.arduino = serial.Serial(port, baud)

        rospy.init_node('arduino_link')
        self.twist_sub = rospy.Subscriber("/cmd_vel", Twist, self.twistCB)
        self.twist_cmd = None
        self.update_rate = rospy.Rate(5)

    def _serializeTwist(self, twist_msg):
        if twist_msg.linear.x >= 0:
            lin_sign = '+'
        else:
            lin_sign = '-'

        if twist_msg.angular.z >= 0:
            ang_sign = '+'
        else:
            ang_sign = '-'

        lin_val = str(abs(int(twist_msg.linear.x * 1000)))
        ang_val = str(abs(int(twist_msg.angular.z * 1000)))

        msg = "SL" + lin_sign + lin_val + "A" + ang_sign + ang_val + "E"
        return msg

    def twistCB(self, msg):
        self.twist_cmd = self._serializeTwist(msg)

    def run(self):
        while not rospy.is_shutdown():
            if self.twist_cmd:
                print(self.twist_cmd)
                self.arduino.write(self.twist_cmd)
                self.twist_cmd = None # Reset to avoid duplicates

            while self.arduino.in_waiting:
                # Display output from Arduino
                print("[ARDUINO] %s" % self.arduino.readline().rstrip('\n'))
            self.update_rate.sleep()


if __name__ == "__main__":
    al = ArduinoLink('/dev/ttyACM0', 115200)
    al.run()
