#include "acquisition.h"

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
  //, m_showDebugView{ a_config[OPENCV_PREVIEW].toBool() }
{
  loadCapture();
  //m_capture.set(cv::CAP_PROP_FRAME_WIDTH, 320);
  //m_capture.set(cv::CAP_PROP_FRAME_HEIGHT, 240);
  //m_capture.set(cv::CAP_PROP_FPS, 90);
}

void ImageAcquisition::configure(QJsonObject const &a_config)
{
  Logger->trace("ImageAcquisition::configure()");
  m_width = { a_config[WIDTH].toInt() };
  m_height = { a_config[HEIGHT].toInt() };
  //m_colorCode = { a_config[COLOR_CODE].toInt() };
  Logger->trace("ImageAcquisition::configure()");
  Logger->trace("ImageAcquisition::configure() m_width:{}", m_width);
  Logger->trace("ImageAcquisition::configure() m_height:{}", m_height);
}

void ImageAcquisition::loadCapture()
{
  Logger->trace("ImageAcquisition::loadCapture()");
  m_capture = cv::VideoCapture("E:/repo/CrossCompilerQtRpi2/image/%d.png");
  m_capture >> m_image;
#if(DEBUG)
  cv::imshow("image", m_image);
      cv::waitKey(1);
#endif

  if (m_image.empty() == true)
  {
    for (int i = 0; i < 20; i++)
    {
      if (m_image.empty() == true)
      {
        m_capture = cv::VideoCapture(i);
        m_capture >> m_image;
        if (m_image.empty() == false)
        {
          break;
        }
      }
    }
  }
  Logger->trace("ImageAcquisition::loadCapture() done");
}

void ImageAcquisition::onUpdate()
{
  Logger->trace("ImageAcquisition::onUpdate()");
  m_counter++;
  m_framerate = 999;
  QTime myTimer;
  if (m_capture.isOpened())
  {
    Logger->trace("ImageAcquisition::onUpdate() m_capture.isOpened():{}", m_capture.isOpened());
    m_capture >> m_image;
    if (m_image.empty())
    {
      loadCapture();
    }
    //if (m_showDebugView)
    // {
    //  emit(showImagesOpenCV3(m_image, "m_imageGrayResized"));
    //}
    if (m_image.channels() == 3)
    {
        cvtColor(m_image, m_imageGray, cv::COLOR_RGBA2GRAY);
    }
    else
    {
        m_imageGray = m_image.clone();
    }
    myTimer.start();
    cv::resize(m_imageGray, m_imageGrayResized, cv::Size(m_width, m_height));
    if (!m_imageGrayResized.empty())
    {
      m_framerate = static_cast<int>(1000.0 / m_lastFrameReciveTime.restart());
      Logger->trace("ImageAcquisition::onUpdate() Recived new frame.framerate {}", m_framerate);

      Logger->trace("ImageAcquisition::onUpdate() emit(update(m_imageGrayResized))");

      Logger->trace("ImageAcquisition::onUpdate() resize from {}x{}x{} to {}x{}x{}", m_image.cols, m_image.rows, m_image.channels(),
                      m_imageGrayResized.cols, m_imageGrayResized.rows, m_imageGrayResized.channels());
      emit(update(m_imageGrayResized));
    }
  }
  else {
      m_capture = cv::VideoCapture("E:/repo/CrossCompilerQtRpi2/image/%d.png");

  }
#if(DEBUG)
  cv::imshow("m_imageGrayResized", m_imageGrayResized);
  cv::waitKey(1);


  QByteArray ImgByteI((char*)(m_imageGrayResized.data), 768); // 32x24x1
  Logger->trace("ImageAcquisition::onUpdate() emit(sendImage(ImgByteI));");

  emit(sendImage(3,ImgByteI));

#endif
  quint32 nMilliseconds2 = (quint32)myTimer.elapsed();
  m_framerateAdd += m_framerate;
  m_addingCounter += nMilliseconds2;
  if (m_counter >= 100)
  {
    Logger->warn("ImageAcquisition::onUpdate() (configure)ImageAcquisition time:{}", ((double)m_addingCounter / (double)m_counter));
    Logger->warn("ImageAcquisition::onUpdate() (configure)ImageAcquisition framerate:{}", m_framerateAdd / (double)m_counter);
    m_addingCounter = 0;
    m_counter = 0;
    m_framerateAdd = 0;
  }
}
