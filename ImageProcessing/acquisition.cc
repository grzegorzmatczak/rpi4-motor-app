#include "acquisition.h"

constexpr auto WIDTH{ "Width" };
constexpr auto HEIGHT{ "Height" };
constexpr auto COLOR_CODE{ "ColorCode" };
constexpr auto OPENCV_PREVIEW{ "OpenCV_Preview" };

class QJsonObject;

#define DEBUG false

ImageAcquisition::ImageAcquisition(QJsonObject const& a_config)
	: m_width{ a_config[WIDTH].toInt() }
	, m_height{ a_config[HEIGHT].toInt() }
	, m_dataSize{ a_config[WIDTH].toInt() * a_config[HEIGHT].toInt() }
	, m_counter(0)
	, m_addingCounter(0)
	, m_framerateAdd(0)
	, m_framerate(0)
{
	loadCapture();
}

void ImageAcquisition::configure(QJsonObject const& a_config)
{
	Logger->trace("ImageAcquisition::configure()");
	m_width = { a_config[WIDTH].toInt() };
	m_height = { a_config[HEIGHT].toInt() };
}

QVector<QString> static scanAllImages(QString path)
{
	QVector<QString> temp;
	QDir directory(path);
	QStringList images = directory.entryList(QStringList() << "*.jpg" << "*.png" << "*.PNG" << "*.JPG", QDir::Files);

	foreach(QString filename, images)
	{
		temp.push_back(filename);
	}
	return temp;
}

void ImageAcquisition::loadCapture()
{
	Logger->trace("ImageAcquisition::loadCapture()");
	m_imageList = scanAllImages("E:/repo/CrossCompilerQtRpi2/LineDataset/");
	Logger->trace("ImageAcquisition::loadCapture() done");
}

void ImageAcquisition::onUpdate()
{
	m_counter++;
	Logger->trace("ImageAcquisition::onUpdate() grab");
	cv::Mat m_image;
	QTime _timer;
	_timer.start();

	if (m_counter >= m_imageList.size())
	{
		ImageAcquisition::ShowFramerate(m_imageGrayResized);
		m_counter = 1;
	}

	Logger->trace("ImageAcquisition::onUpdate() m_capture.isOpened():{}", m_capture.isOpened());

	m_image = cv::imread("E:/repo/CrossCompilerQtRpi2/LineDataset/" + m_imageList[m_counter].toStdString());
	Logger->trace("open:{}", "E:/repo/CrossCompilerQtRpi2/LineDataset/" + m_imageList[m_counter].toStdString());

	if (m_image.empty() || m_image.cols == 0 || m_image.rows == 0)
	{
		Logger->error("ImageAcquisition::onUpdate() m_capture failed capture a frame");
		return;
	}

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
	

	if (!m_imageGrayResized.empty())
	{
		QByteArray ImgByteI((char*)(m_imageGrayResized.data), m_dataSize); // 32x24x1
		Logger->trace("(configure)ImageAcquisition emit(sendImage(ImgByteI));");
		emit(sendImage(3, ImgByteI));
	}
}

void ImageAcquisition::ShowFramerate(cv::Mat const& image)
{
	Logger->warn("(timer)ImageAcquisition time:{}  framerate:{}", ((double)m_addingCounter / (double)m_counter),
		m_framerateAdd / (double)m_counter);

	m_addingCounter = 0;
	m_framerateAdd = 0;
}

void ImageAcquisition::ChangeSizeAndColor(cv::Mat const& image, cv::Mat& out)
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