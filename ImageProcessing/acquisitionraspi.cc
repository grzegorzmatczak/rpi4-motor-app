#include "acquisitionraspi.h"

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>

constexpr auto WIDTH{ "Width" };
constexpr auto HEIGHT{ "Height" };
constexpr auto COLOR_CODE{ "ColorCode" };
constexpr auto OPENCV_PREVIEW{ "OpenCV_Preview" }; 
constexpr auto CAP{ "Cap" };

class QJsonObject;

#define DEBUG true

ImageAcquisition::ImageAcquisition(QJsonObject const &a_config)
  : m_width{ a_config[WIDTH].toInt() }
  , m_height{ a_config[HEIGHT].toInt() }
  , m_counter(0)
  , m_addingCounter(0)
  , m_framerateAdd(0)
    , m_cap{ a_config[CAP].toInt() }
{
    Logger->trace("ImageAcquisition::ImageAcquisition()");
    //m_camera = new raspicam::RaspiCam_Cv();
    //m_camera.open();
    Logger->trace("ImageAcquisition::ImageAcquisition() after open");
  //loadCapture();
  //m_capture.set(cv::CAP_PROP_FRAME_WIDTH, 320);
  //m_capture.set(cv::CAP_PROP_FRAME_HEIGHT, 240);
  //m_capture.set(cv::CAP_PROP_FPS, 90);
    /*
    if (!m_camera.open()) {
        Logger->trace("ImageAcquisition::ImageAcquisition() Error opening camera");
    }
  m_camera.set(cv::CAP_PROP_FRAME_WIDTH, 320);
  m_camera.set(cv::CAP_PROP_FRAME_HEIGHT, 240);*/
  
  //std::cout << "Connected to camera =" << m_camera.getId() << std::endl;
   //raspicam::RaspiCam_Cv m_camera;
    m_capture.open(m_cap);
    m_capture.set(cv::CAP_PROP_FRAME_WIDTH, 320);
    m_capture.set(cv::CAP_PROP_FRAME_HEIGHT, 240); 
    m_capture.set(cv::CAP_PROP_FORMAT, -1);
}


void ImageAcquisition::configure(QJsonObject const &a_config)
{
  Logger->trace("ImageAcquisition::configure()");
  m_width = { a_config[WIDTH].toInt() };
  m_height = { a_config[HEIGHT].toInt() };
  Logger->trace("ImageAcquisition::configure()");
  Logger->trace("ImageAcquisition::configure() m_width:{}", m_width);
  Logger->trace("ImageAcquisition::configure() m_height:{}", m_height);
}

void ImageAcquisition::loadCapture()
{
}

void ImageAcquisition::onUpdate()
{

    m_capture >> m_image;

        if (m_image.channels() == 3)
        {
            cvtColor(m_image, m_imageGray, cv::COLOR_RGBA2GRAY);
        }
        else
        {
            m_imageGray = m_image.clone();
        }
        cv::resize(m_imageGray, m_imageGrayResized, cv::Size(m_width, m_height));


        if (!m_imageGrayResized.empty())
        {
            Logger->trace("m_imageGrayResized:{}x{}x{};", m_imageGrayResized.cols, m_imageGrayResized.rows, m_imageGrayResized.channels());

            QByteArray ImgByteI((char*)(m_imageGrayResized.data), 768); // 32x24x1
            Logger->trace("ImageAcquisition::onUpdate() emit(sendImage(ImgByteI));");

            emit(sendImage(3, ImgByteI));
        }
        else {
            Logger->error("m_imageGrayResized.empty()");
        }
   
    
  
}
