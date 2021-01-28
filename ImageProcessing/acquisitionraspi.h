#ifndef IMAGEACQUISITION_H
#define IMAGEACQUISITION_H

#include <QJsonObject>
#include <QObject>
#include <QTime>

#include "../../src/structures.h"

#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include "raspicam_cv.h"

class ImageAcquisition : public QObject
{
  Q_OBJECT
 public:
  ImageAcquisition(QJsonObject const &a_config);
  void configure(QJsonObject const &a_config);
  void loadCapture();
  
  //raspicam::RaspiCam_Cv* m_camera;

 signals:
  void update(cv::Mat image);
  void showImagesOpenCV3(cv::Mat frame, std::string name);
  void sendImage(const qint32 topic, QByteArray image);

 public slots:
  void onUpdate();

 private:
  cv::Mat m_image;
  cv::Mat m_imageGray;
  cv::Mat m_imageGrayResized;
  cv::VideoCapture m_capture;
  int m_cap;

 private:
  qint32 m_width;
  qint32 m_height;

 private:
  qint32 m_colorCode;
  QTime m_lastFrameReciveTime{};
  int m_framerate{};
  qint32 m_framerateAdd{};
  quint32 m_counter{};
  quint32 m_addingCounter{};
  bool m_showDebugView;

  
};

#endif // IMAGEACQUISITION_H
