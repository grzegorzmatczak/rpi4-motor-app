#include "acquisitionraspicam.h"

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>

constexpr auto WIDTH{ "Width" };
constexpr auto HEIGHT{ "Height" };
constexpr auto COLOR_CODE{ "ColorCode" };
constexpr auto OPENCV_PREVIEW{ "OpenCV_Preview" };

class QJsonObject;

#define DEBUG true

ImageAcquisition::ImageAcquisition(QJsonObject const &a_config)
  : m_width{ a_config[WIDTH].toInt() }
  , m_height{ a_config[HEIGHT].toInt() }
  , m_counter(0)
  , m_addingCounter(0)
  , m_framerateAdd(0)

{
    Logger->trace("ImageAcquisition::ImageAcquisition()");

	/*
	RASPIVID_CONFIG* config = (RASPIVID_CONFIG*)malloc(sizeof(RASPIVID_CONFIG));
	config->width = 320;//320;
	config->height = 240;//240;
	config->bitrate = 10;	// zero: leave as default
	config->framerate = 100;
	config->monochrome = 1;
	//bMonochrome = 1;


	cv::Mat temp = cvCreateImage(cvSize(iConfig.width, iConfig.height), IPL_DEPTH_8U, 1);
	m_capture = (RaspiCamCvCapture*)raspiCamCvCreateCameraCapture2(0, config);
	free(config);

	*/
}

void ImageAcquisition::configure(QJsonObject const &a_config)
{

}

void ImageAcquisition::loadCapture()
{
}

void ImageAcquisition::onUpdate()
{

	RaspiCamCvCapture* camera = raspiCamCvCreateCameraCapture(0);
	cv::Mat image(raspiCamCvQueryFrame(camera));
	//cv::namedWindow("Display", CV_WINDOW_AUTOSIZE);
	//cv::imshow(window_name, image);
	//cv::waitKey(0);



	/*
	Logger->trace("ImageAcquisition::onUpdate()");
	//frame = raspiCamCvQueryFrame(m_capture);	// Load frame from camera.
	m_imageGray = raspiCamCvQueryFrame(m_capture);	// Load frame from camera.
	cv::resize(m_imageGray, m_imageGrayResized, cv::Size(m_width, m_height));
	if (!m_imageGrayResized.empty())
	{
		Logger->trace("ImageAcquisition::onUpdate() emit");
		QByteArray ImgByteI((char*)(m_imageGrayResized.data), 768); // 32x24x1
		Logger->trace("ImageAcquisition::onUpdate() emit(sendImage(ImgByteI));");
		emit(sendImage(3, ImgByteI));
	}*/
}
