#include "ros/ros.h"
#include "std_msgs/String.h"
#include "sensor_msgs/image_encodings.h"
#include "cv_bridge/cv_bridge.h"
#include "opencv2/highgui/highgui.hpp"
//#include "image_transport/image_transport.h"
//#include "opencv2/imgproc/imgproc.hpp"

void callback_Func1(const sensor_msgs::ImageConstPtr& rgb_msg) //Image
{
  //ROS_INFO("callback_1");
  cv_bridge::CvImagePtr cv_ptr1;
  try
    {
      cv_ptr1 = cv_bridge::toCvCopy(rgb_msg, sensor_msgs::image_encodings::BGR8);
    }
  catch (cv_bridge::Exception& e1)
  {
    ROS_ERROR("cv_bridge exception: %s", e1.what());
    return;
  }
  cv::imshow("rgb_image",cv_ptr1->image);
  cv::waitKey(3);
}
void callback_Func2(const sensor_msgs::ImageConstPtr& depth_msg) //Image
{
  //ROS_INFO("callback_2");
  cv_bridge::CvImagePtr cv_ptr2;
  try
    {
      cv_ptr2 = cv_bridge::toCvCopy(depth_msg, sensor_msgs::image_encodings::TYPE_16UC1);
    }
  catch (cv_bridge::Exception& e2)
  {
    ROS_ERROR("cv_bridge exception: %s", e2.what());
    return;
  }
  cv::imshow("depth_image",cv_ptr2->image);
  cv::waitKey(3);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "realsense_image_sub");
  ros::NodeHandle nh;

  //multi thread
  ros::AsyncSpinner spinner(0);//'0' means using many threads / if 3 => using only 3 threads
  spinner.start();

  ros::Subscriber sub_rgb = nh.subscribe("/camera/color/image_raw", 10, callback_Func1);
  ros::Subscriber sub_depth = nh.subscribe("/camera/depth/image_rect_raw",10,callback_Func2);

  ros::waitForShutdown();
  return 0;
}