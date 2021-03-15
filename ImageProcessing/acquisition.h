#ifndef IMAGEACQUISITION_H
#define IMAGEACQUISITION_H

#include <QJsonObject>
#include <QObject>
#include <QTime>

#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include "../src/structures.h"

class ImageAcquisition : public QObject
{
	Q_OBJECT
public:
	ImageAcquisition(QJsonObject const& a_config);
	void configure(QJsonObject const& a_config);
	void loadCapture();

signals:
	void update(cv::Mat image);
	void showImagesOpenCV3(cv::Mat frame, std::string name);
	void sendImage(const qint32 topic, QByteArray image);

public slots:
	void onUpdate();

private:
	void ChangeSizeAndColor(cv::Mat const& image, cv::Mat& out);
	void ShowFramerate(cv::Mat const& image);

private:
	cv::Mat m_image;
	cv::Mat m_imageGray;
	cv::Mat m_imageGrayResized;
	cv::VideoCapture m_capture;
	QVector<QString> m_imageList;

private:
	qint32 m_width{};
	qint32 m_height{};
	qint32 m_dataSize{};

private:
	qint32 m_colorCode{};
	QTime m_lastFrameReciveTime{};
	qint32 m_framerate{};
	qint32 m_framerateAdd{};
	quint32 m_counter{};
	quint32 m_addingCounter{};
	bool m_showDebugView{};
};

#endif // IMAGEACQUISITION_H