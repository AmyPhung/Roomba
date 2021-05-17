//
// Created by amy on 6/20/20.
//

#ifndef ROOMBA_TELEOP_H
#define ROOMBA_TELEOP_H

#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/Joy.h>

class RoombaTeleop
{
public:
    RoombaTeleop();

private:
    void joyCallback(const sensor_msgs::Joy::ConstPtr& joy);

    ros::NodeHandle nh_;

    int linear_, angular_;
    double l_scale_, a_scale_;
    ros::Publisher vel_pub_;
    ros::Subscriber joy_sub_;

};

#endif //ROOMBA_TELEOP_H
