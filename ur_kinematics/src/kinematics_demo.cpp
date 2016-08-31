#include <iostream>
#include <ros/ros.h>
#include <trajectory_msgs/JointTrajectory.h>


// std::vector<string> joint_names = 
// {
//   "shoulder_pan_joint" ,
//   "shoulder_lift_joint", 
//   "elbow_joint",
//   "wrist_1_joint" ,
//   "wrist_2_joint" ,
//   "wrist_3_joint"};

int main(int argc, char** argv)
{
  ros::init(argc, argv, "kinematic_demo");
  ros::NodeHandle nh;
  trajectory_msgs::JointTrajectory trajectory_msg;


  ros::Publisher trajectory_pub = 
  nh.advertise<trajectory_msgs::JointTrajectory>("/arm_controller/command", 1);


  std::vector<double> Q1 = {2.2,0,-1.57,0,0,0};
  std::vector<double> Q2 = {1.5,0,-1.57,0,0,0};
  std::vector<double> Q3 = {1.5,-0.2,-1.57,0,0,0};

  trajectory_msgs::JointTrajectoryPoint points;

    // Trajectory message
  trajectory_msg.points.resize(1);
  trajectory_msg.points[0].positions = Q1;
  trajectory_msg.points[0].time_from_start = ros::Duration(1.0);

  // trajectory_msg.points[1].positions = Q2;
  // trajectory_msg.points[1].time_from_start = ros::Duration(2.0);

  // trajectory_msg.points[2].positions = Q3;
  // trajectory_msg.points[2].time_from_start = ros::Duration(4.0);

  trajectory_msg.header.stamp = ros::Time(0.5);
  trajectory_msg.joint_names = {
  "shoulder_pan_joint" ,
  "shoulder_lift_joint", 
  "elbow_joint",
  "wrist_1_joint" ,
  "wrist_2_joint" ,
  "wrist_3_joint"};
 
  ros::Rate loop_rate(1);
  int count = 0;
  while(ros::ok())
  {
   
    
    trajectory_msg.header.stamp = ros::Time::now();
    for(int i = 3; i < Q1.size(); i++)
    {
      Q1[i] += rand() % 100 / 1000.0;
    }
    trajectory_msg.points[0].positions = Q1;
    trajectory_msg.points[0].time_from_start = ros::Duration(1.0);


     trajectory_pub.publish(trajectory_msg);
    count++;
    loop_rate.sleep();
  }

  return 0;
}
