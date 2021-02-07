#include "bounds.h"

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>

constexpr auto CAP{ "Cap" };
constexpr auto OPENCV_PREVIEW{ "OpenCV_Preview" };
constexpr auto DECISION_THRESHOLD{ "DecisionThreshold" };
constexpr auto WIDTH{ "Width" };
constexpr auto HEIGHT{ "Height" };
constexpr auto VOTE{ "Vote" };

class QJsonObject;

#define DEBUG false

Bounds::Bounds(QJsonObject const& a_config)
	: m_firstTime(true)
	, m_counter(0)
	, m_addingCounter(0)
	, m_showDebugView{ a_config[OPENCV_PREVIEW].toBool() }
	, m_areaAcc(0)
	, m_thresh{ a_config[DECISION_THRESHOLD].toInt() }
	, m_width{ a_config[WIDTH].toInt() }
	, m_height{ a_config[HEIGHT].toInt() }
	, m_dataSize{ a_config[WIDTH].toInt() * a_config[HEIGHT].toInt() }
	, m_vote{ a_config[VOTE].toDouble() }
	, m_cameraCounter(0)
	, m_debugPreview(true)
	, m_debugFrames(30)
	, m_debugFramesColor(30)
{

}

void Bounds::configure(QJsonObject const& a_config)
{
	Logger->debug("Bounds::configure()");
	m_showDebugView = { a_config[OPENCV_PREVIEW].toBool() };
	m_thresh = { a_config[DECISION_THRESHOLD].toInt() };
	m_width = { a_config[WIDTH].toInt() };
	m_height = { a_config[HEIGHT].toInt() };
	m_vote = { a_config[VOTE].toDouble() };

	Logger->debug("Bounds::configure() m_showDebugView:{}", m_showDebugView);
	Logger->debug("Bounds::configure() m_thresh:{}", m_thresh);
	Logger->debug("Bounds::configure() m_width:{}", m_width);
	Logger->debug("Bounds::configure() m_height:{}", m_height);
	Logger->debug("Bounds::configure() m_vote:{}", m_vote);
}

Bounds::~Bounds()
{
	Logger->debug("Bounds::~Bounds()");
}

void Bounds::onUpdate(cv::Mat image)
{
	QTime myTimer;
	myTimer.start();
	m_cameraCounter++;

	Logger->debug("BoundariesFinder::onUpdate() image.cols:{}", image.cols);
	Logger->debug("BoundariesFinder::onUpdate() image.rows:{}", image.rows);
	Logger->debug("BoundariesFinder::onUpdate() image.channel:{}", image.channels());

	int cols = image.cols;
	int rows = image.rows;

	cv::Mat image2 = image.clone();
	cv::resize(image2, image2, cv::Size(m_width, m_height), 0, 0, cv::INTER_CUBIC);
	cv::threshold(image2, image2, m_thresh, 255, cv::THRESH_BINARY_INV);

	findCountour(image2);

	int middleCountour = 0;
	if (m_areaAcc > 0)
	{
		for (unsigned int i = 0; i < m_contours.size(); i++)
		{
			cv::Rect boundRect = cv::boundingRect(m_contours[i]);
			double area = cv::contourArea(m_contours[i]);
			int areaRatio = int(area / m_areaAcc * m_vote); // 10 g³osów:

			middleCountour += (boundRect.x + (boundRect.width / 2)) * areaRatio;
		}
	}
	middleCountour = middleCountour / m_vote;
	double dir = ((middleCountour - (m_width / 2.0)) / 6.4);
	Logger->debug("BoundariesFinder::onUpdate() dir:{}", dir);
	cv::circle(image2, cv::Point(middleCountour, image2.rows / 2), 2, cv::Scalar(255), -1);
	cv::circle(image2, cv::Point(middleCountour, image2.rows / 2), 1, cv::Scalar(0), -1);

	double error = dir;
	if (error > 100.0)
	{
		error = 100.0;
	}
	if (error <= -100.0)
	{
		error = -100.0;
	}

			cv::circle(image2, cv::Point(middleCountour, image2.rows / 2), 2, cv::Scalar(255), -1);
			cv::circle(image2, cv::Point(middleCountour, image2.rows / 2), 1, cv::Scalar(0), -1);
			m_cameraCounter = 0;

			QByteArray ImgByteI((char*)(image2.data), m_dataSize);
			Logger->trace("ImageAcquisition::onUpdate() emit(sendImage(ImgByteI));");
			emit(sendImage(4, ImgByteI));
			emit(sendError(error));


	m_counter++;

	if (m_showDebugView)
	{
		//emit(showImagesOpenCV3(image2, "BoundariesFinder"));
	}
	quint32 nMilliseconds2 = (quint32)myTimer.elapsed();
	m_addingCounter += nMilliseconds2;
	if (m_counter >= 1000)
	{
		Logger->info("(timer)BoundariesFinder time:{}", ((double)m_addingCounter / (double)m_counter));
		//refreshIP(qint32(((double)m_addingCounter / (double)m_counter)));
		m_addingCounter = 0;
		m_counter = 0;
	}
}

void Bounds::findCountour(cv::Mat& image)
{
	double area = 0.0;

	std::vector<std::vector<cv::Point>> contoursBEST;
	std::vector<cv::Vec4i> hierarchyBEST;

	Logger->debug("BoundariesFinder::findContours()");
	cv::findContours(image, m_contours, m_hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE, cv::Point(0, 0));

	m_areaAcc = 0;
	for (unsigned int i = 0; i < m_contours.size(); i++)
	{
		area = cv::contourArea(m_contours[i]);
		if (area >= (1.0))
		{
			contoursBEST.push_back(m_contours[i]);
			hierarchyBEST.push_back(m_hierarchy[i]);
			m_areaAcc += area;
		}
	}
	Logger->debug("BoundariesFinder::findContours() finitio contoursBEST.size:{}", contoursBEST.size());
	m_contours.swap(contoursBEST);
	m_hierarchy.swap(hierarchyBEST);
}
