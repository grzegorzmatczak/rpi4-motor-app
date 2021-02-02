#include "acquisitionraspi.h"

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>

constexpr auto WIDTH{ "Width" };
constexpr auto HEIGHT{ "Height" };
constexpr auto CAP{ "Cap" };

class QJsonObject;

#define DEBUG false

ImageAcquisition::ImageAcquisition(QJsonObject const& a_config)
	: m_width{ a_config[WIDTH].toInt() }
	, m_height{ a_config[HEIGHT].toInt() }
	, m_capture(new Capture(a_config))
	, m_dataSize(0)
	, m_framerate(0)
	, m_counter(0)
	, m_addingCounter(0)
	, m_framerateAdd(0)
{
	configure(a_config);
}

ImageAcquisition::~ImageAcquisition()
{
	Logger->debug("ImageAcquisition::~ImageAcquisition()");
	delete m_capture;
}

void ImageAcquisition::configure(QJsonObject const& a_config)
{
	Logger->trace("ImageAcquisition::configure()");
	m_width = { a_config[WIDTH].toInt() };
	m_height = { a_config[HEIGHT].toInt() };
	m_dataSize = m_width * m_height;
	if (m_dataSize < 1)
	{
		Logger->error("ImageAcquisition::configure() data size not set");
	}
}

void ImageAcquisition::onUpdate()
{
	m_counter++;
	Logger->trace("ImageAcquisition::onAddImage() grab");
	cv::Mat m_image;
	QTime _timer;

	m_capture->grab(m_image);
	if (m_image.empty() or m_image.cols == 0 or m_image.rows == 0)
	{
		Logger->error("ImageAcquisition::onAddImage() m_capture failed capture a frame");
		return;
	}

	_timer.start();

	cv::Mat m_imageGrayResized;
	ChangeSizeAndColor(m_image, m_imageGrayResized);

	if (!m_imageGrayResized.empty())
	{
		emit(update(m_imageGrayResized));
		m_framerate = static_cast<int>(1000.0 / m_lastFrameReciveTime.restart());
		Logger->trace("Recived new frame.framerate {}", m_framerate);
		
#if(DEBUG)
		QString test(ImgByteI.toHex());
		Logger->trace("ImageAcquisition::onAddImage() string:{}", test.toStdString());
#endif
	}

	quint32 _millisec = (quint32)_timer.elapsed();
	m_framerateAdd += m_framerate;
	m_addingCounter += _millisec;
	if (m_counter >= 100)
	{
		ImageAcquisition::ShowFramerate(m_imageGrayResized);
	}
}

void ImageAcquisition::ShowFramerate(cv::Mat const& image)
{
	Logger->warn("(timer)ImageAcquisition time:{}  framerate:{}", ((double)m_addingCounter / (double)m_counter),
		m_framerateAdd / (double)m_counter);

	m_addingCounter = 0;
	m_counter = 0;
	m_framerateAdd = 0;
	if (!image.empty())
	{
		QByteArray ImgByteI((char*)(image.data), m_dataSize); // 32x24x1
		Logger->trace("(configure)ImageAcquisition emit(sendImage(ImgByteI));");
		emit(sendImage(3, ImgByteI));
	}
}

void ImageAcquisition::ChangeSizeAndColor(cv::Mat const & image, cv::Mat & out)
{
	
	cv::Mat m_imageGray;
	cv::Mat m_imageGrayResized;

	if (image.channels() == 3)
	{
		cvtColor(image, m_imageGray, cv::COLOR_RGBA2GRAY);
	}
	else
	{
		m_imageGray = image.clone();
	}

	try
	{
		cv::resize(m_imageGray, out, cv::Size(m_width, m_height));
	}
	catch (cv::Exception& e)
	{
		const char* err_msg = e.what();
		qDebug() << "exception caught: " << err_msg;
		Logger->error("exception caught in ImageAcquisition::ChangeSizeAndColor()");
	}
}