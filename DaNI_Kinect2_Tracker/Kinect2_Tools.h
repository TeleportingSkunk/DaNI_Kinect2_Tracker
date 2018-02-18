#pragma once

#include <Windows.h>
#include <Kinect.h>
#include <opencv2/opencv.hpp>
#include <vector>
#include <array>	

#include <wrl/client.h> //TODO: find out what this is for.

using namespace Microsoft::WRL;

class Kinect
{

private: //properties here cannot be viewed or globally accessed. They can only be viewed or modified indirectly via set/get functions.

	//Create COM Pointers for color and body frames, plus a mapper between them
	ComPtr<IKinectSensor> kinect; //COM <-Component Object Model. This pointer makes inter PC use easier.

	ComPtr<ICoordinateMapper> coordinateMapper;

	ComPtr<IColorFrameReader> colorFrameReader;

	ComPtr<IBodyFrameReader> bodyFrameReader;

	//Gotta prepare the color buffer and Matrix holders
	std::vector<BYTE> colorBuffer;
	int colorWidth;
	int colorHeight;
	unsigned int colorBytesPerPixel;
	cv::Mat colorMat;

	//Body Buffer
	std::array<IBody*, BODY_COUNT> bodies = { nullptr }; //Contains the body objects themselves
	std::array<cv::Vec3b, BODY_COUNT> colors; //some shit about colours
public:
	Kinect(); //constructor

	~Kinect(); //destructor

	void run(); //processing??

private:
	void initialize();

	inline void initializeSensor();

	inline void initializeColor();

	inline void initializeBody();

	void finalize();

	void update();

	inline void updateColor();

	inline void updateBody();

	void draw();

	inline void drawColor();

	inline void drawBody();

	inline void drawEllipse(cv::Mat &image, const Joint &joint, const int radius, const cv::Vec3b &color, const int thickness = -1);

	inline void drawHandState(cv::Mat &image, const Joint &joint, HandState handState, TrackingConfidence handConfidence);

	void show();

	inline void showBody();

};
