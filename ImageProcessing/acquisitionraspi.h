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

private:
	void ChangeSizeAndColor(cv::Mat const& image, cv::Mat& out);
	void ShowFramerate(cv::Mat const& image);

signals:
	void update(cv::Mat image);
	void sendImage(const qint32 topic, QByteArray image);

public slots:
	void onUpdate();

private:
	QTime m_lastFrameReciveTime{};
	qint32 m_framerate{};

private:
	qint32 m_width{};
	qint32 m_height{};
	quint32 m_dataSize{};
	quint32 m_counter{};
	quint32 m_addingCounter{};
	quint32 m_framerateAdd{};

private:
	Capture* m_capture;
};

#endif // IMAGEACQUISITION_H
