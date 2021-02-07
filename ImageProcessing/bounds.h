#ifndef BOUNDS_H
#define BOUNDS_H

#include <QJsonObject>
#include <QObject>
#include <QTime>

#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include "../../src/structures.h"

class Bounds : public QObject
{
	Q_OBJECT
public:
	Bounds(QJsonObject const& a_config);
	~Bounds();
	void configure(QJsonObject const& a_config);

private:
	void findCountour(cv::Mat& image);

signals:
	void sendImage(const qint32 topic, QByteArray image);

public slots:
	void onUpdate(cv::Mat image);

private:
	bool m_firstTime{};
	bool m_showDebugView{};

private:
	quint32 m_counter{};
	quint32 m_addingCounter{};

private:
	std::vector<std::vector<cv::Point>> m_contours;
	std::vector<cv::Vec4i> m_hierarchy;

	quint32 m_data{};
	std::string m_binary{};

	double m_areaAcc{};
	qint32 m_thresh{};
	qint32 m_width{};
	qint32 m_height{};
	qint32 m_dataSize{};
	double m_vote{};
	qint32 m_cameraCounter{};
	qint32 m_cameraCounterColor{};

private:
	bool m_debugPreview{};
	qint32 m_debugFrames{};
	qint32 m_debugFramesColor{};
};

#endif // BOUNDS_H
