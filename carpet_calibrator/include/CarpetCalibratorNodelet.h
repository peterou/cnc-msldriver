/*
 * CarpetCalibratorNodelet.h
 *
 *  Created on: May 20, 2015
 *      Author: cn
 */

#ifndef CNC_MSLDRIVER_CARPET_CALIBRATOR_SRC_CARPETCALIBRATORNODELET_H_
#define CNC_MSLDRIVER_CARPET_CALIBRATOR_SRC_CARPETCALIBRATORNODELET_H_

#include <nodelet/nodelet.h>
#include <ros/package.h>
#include <ros/ros.h>
#include <boost/thread.hpp>
#include <pluginlib/class_list_macros.h>
#include "XVDisplay.h"
#include <image_transport/image_transport.h>


using namespace std;

namespace msl_vision
{
	typedef struct {
		uint8_t u;
		uint8_t y1;
		uint8_t v;
		uint8_t y2;
	} YUV422DoublePixel;
	class CarpetCalibratorNodelet : public nodelet::Nodelet
	{
	public:
		 CarpetCalibratorNodelet();
		 ~CarpetCalibratorNodelet();
	     virtual void onInit();
	     void run();
	     void imageCb(const sensor_msgs::ImageConstPtr& image_msg,
	     				                             const sensor_msgs::CameraInfoConstPtr& info_msg);
	     void connectCb();
	private:

	     XVDisplay * xvDisplay = NULL;

	     boost::shared_ptr<image_transport::ImageTransport> it_;
	     image_transport::CameraSubscriber sub_camera_;
		 ros::NodeHandle nh;
		 boost::shared_ptr<boost::thread> deviceThread_;
	};

}
#endif /* CNC_MSLDRIVER_CARPET_CALIBRATOR_SRC_CARPETCALIBRATORNODELET_H_ */
