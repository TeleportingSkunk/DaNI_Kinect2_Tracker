// DaNI_Kinect2_Tracker.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <opencv2\core.hpp>
#include <opencv2\imgproc.hpp>
#include <opencv2\highgui.hpp>
#include <Kinect.h>
#include <Windows.h>

IKinectSensor * sensorKinect; 
IColorFrameReader * ColorReader;
int height, width;
bool initKinectColor();
unsigned int bufferSize = 0;
unsigned char * pBuffer = nullptr;
IColorFrame * frame = NULL; //"frame" is a pointer which points to the address in which an IColorFrame object will be stored. It is 
							// currently assigned to NULL location.
int main()
{
	initKinectColor();
	
	cv::Mat ocvImage;
	while (1) {
		if (SUCCEEDED(ColorReader->AcquireLatestFrame(&frame))) {

			if SUCCEEDED(frame->AccessRawUnderlyingBuffer(&bufferSize, &pBuffer))
				frame->Release();
			ocvImage = cv::Mat(1080, 1920, CV_16U, pBuffer);
			cv::namedWindow("AAAA", cv::WINDOW_NORMAL);
			cv::imshow("AAAA", ocvImage);
		}
		if (!cv::waitKey(0))
			break;
	}
	cv::destroyAllWindows();

    return 0;
}


bool initKinectColor() {
	if (FAILED(GetDefaultKinectSensor(&sensorKinect))) 
		return false;

	if (sensorKinect) {
		sensorKinect->Open();
		
		IColorFrameSource* framesource = NULL;
		sensorKinect->get_ColorFrameSource(&framesource);
		framesource->OpenReader(&ColorReader);
		if (framesource) {
			framesource->Release();
			framesource = NULL;
		}
		return true;

	}
	else
		return false;
}