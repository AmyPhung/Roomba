//
// Created by amy on 6/20/20.
//

#include "Teleop.h"


RoombaTeleop::RoombaTeleop():
        linear_(1),
        angular_(2)
{

    nh_.param("axis_linear", linear_, linear_);
    nh_.param("axis_angular", angular_, angular_);
    nh_.param("scale_angular", a_scale_, a_scale_);
    nh_.param("scale_linear", l_scale_, l_scale_);


    vel_pub_ = nh_.advertise<geometry_msgs::Twist>("/cmd_vel", 1);

    joy_sub_ = nh_.subscribe<sensor_msgs::Joy>("joy", 10, &RoombaTeleop::joyCallback, this);

}

void RoombaTeleop::joyCallback(const sensor_msgs::Joy::ConstPtr& joy)
{
    geometry_msgs::Twist twist;
    twist.angular.z = a_scale_*joy->axes[angular_];
    twist.linear.x = l_scale_*joy->axes[linear_];
    vel_pub_.publish(twist);
}


int main(int argc, char** argv)
{
    ros::init(argc, argv, "RoombaTeleop");
    RoombaTeleop roomba_teleop;

    ros::spin();
}