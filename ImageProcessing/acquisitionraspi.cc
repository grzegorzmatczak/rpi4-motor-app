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
{
	configure(a_config);
}

ImageAcquisition::~ImageAcquisition()
{
	Logger->info("ImageAcquisition::~ImageAcquisition()");
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
	Logger->trace("ImageAcquisition::onAddImage() grab");
	m_capture->grab(m_image);
	if (m_image.empty() or m_image.cols == 0 or m_image.rows == 0)
	{
		Logger->trace("ImageAcquisition::onAddImage() m_capture failed capture a frame");
		return;
	}

	if (m_image.channels() == 3)
	{
		cvtColor(m_image, m_imageGray, cv::COLOR_RGBA2GRAY);
	}
	else
	{
		m_imageGray = m_image.clone();
	}

	try
	{
		cv::resize(m_imageGray, m_imageGrayResized, cv::Size(m_width, m_height));
	}
	catch (cv::Exception& e)
	{
		const char* err_msg = e.what();
		qDebug() << "exception caught: " << err_msg;
		Logger->error("exception caught!");
	}

	if (!m_imageGrayResized.empty())
	{
		QByteArray ImgByteI((char*)(m_imageGrayResized.data), m_dataSize); // 32x24x1
		Logger->trace("(configure)ImageAcquisition emit(sendImage(ImgByteI));");
		emit(sendImage(3, ImgByteI));
#if(DEBUG)
		QString test(ImgByteI.toHex());
		Logger->trace("ImageAcquisition::onAddImage() string:{}", test.toStdString());
#endif
	}

}
