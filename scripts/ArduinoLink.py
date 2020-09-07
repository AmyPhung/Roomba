#!/usr/bin/env python

# ROS Imports
import rospy
from geometry_msgs.msg import Twist
from std_msgs.msg import Int16

# Python Imports
import serial, time


class ArduinoLink:
    def __init__(self, port, baud, rate=10):
        # TODO: Implement timeout & heartbeat
        self.arduino = serial.Serial(port, baud)

        rospy.init_node('arduino_link')
        self.twist_sub = rospy.Subscriber("/cmd_vel", Twist, self.twistCB)
        self.twist_cmd = None

        self.lwheel_pub = rospy.Publisher("/lwheel", Int16, queue_size=10)
        self.rwheel_pub = rospy.Publisher("/rwheel", Int16, queue_size=10)

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

    def _parseInput(self, input):

        if input[0:5] == "L_ENC":
            l_msg = Int16()
            l_msg.data = int(input[5:])
            self.lwheel_pub.publish(l_msg)

        if input[0:5] == "R_ENC":
            r_msg = Int16()
            r_msg.data = int(input[5:])
            self.rwheel_pub.publish(r_msg)

    def twistCB(self, msg):
        self.twist_cmd = self._serializeTwist(msg)

    def run(self):
        while not rospy.is_shutdown():
            if self.twist_cmd:
                print(self.twist_cmd)
                self.arduino.write(self.twist_cmd)
                self.twist_cmd = None # Reset to avoid duplicates

            while self.arduino.in_waiting:
                arduino_msg = self.arduino.readline().rstrip('\n')
                self._parseInput(arduino_msg)

                # Display output from Arduino
                print("[ARDUINO] %s" % arduino_msg)
            self.update_rate.sleep()

#angle=((right_encoder*72*3.14/508.8)-(left_encoder*72*3.14/508.8))/235;
#
# // Convert to millimeters
# // N counts * (mm in 1 wheel revolution / counts in 1 wheel revolution) = mm
# r_enc = (right_encoder*72*3.14/508.8);
# l_enc = (left_encoder*72*3.14/508.8);

if __name__ == "__main__":
    al = ArduinoLink('/dev/ttyACM0', 115200)
    al.run()
