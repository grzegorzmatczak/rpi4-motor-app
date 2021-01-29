#ifndef IMAGEACQUISITION_H
#define IMAGEACQUISITION_H

#include <QJsonObject>
#include <QObject>
#include <QTime>

#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include "../../src/structures.h"
#include <raspicam_cv.h>
#include "capture.h"

class ImageAcquisition : public QObject
{
	Q_OBJECT
public:
	ImageAcquisition(QJsonObject const& a_config);
	~ImageAcquisition();
	void configure(QJsonObject const& a_config);

signals:
	void update(cv::Mat image);
	void showImagesOpenCV3(cv::Mat frame, std::string name);
	void sendImage(const qint32 topic, QByteArray image);
	void refreshAcc(qint32 imageAcc);

public slots:
	void onUpdate();

private:
	cv::Mat m_image;
	cv::Mat m_imageGray;
	cv::Mat m_imageGrayResized;

private:
	qint32 m_width{};
	qint32 m_height{};
	qint32 m_dataSize{};

private:
	Capture* m_capture;
};

#endif // IMAGEACQUISITION_H
