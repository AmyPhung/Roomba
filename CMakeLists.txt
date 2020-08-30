cmake_minimum_required(VERSION 3.0.2)
project(roomba)

find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  joy
  roscpp
  rospy
  sensor_msgs
)
