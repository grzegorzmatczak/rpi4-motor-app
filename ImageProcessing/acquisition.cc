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
	, m_counter(0)
	, m_addingCounter(0)
	, m_framerateAdd(0)
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
		//QStringList sl = filename.split(".");
		temp.push_back(filename);
	}
	return temp;
}

void ImageAcquisition::loadCapture()
{
	Logger->trace("ImageAcquisition::loadCapture()");
	//m_capture = cv::VideoCapture("E:/repo/CrossCompilerQtRpi2/image/%d.png"); 
	//m_capture.open("E:/repo/CrossCompilerQtRpi2/image/%d.png");


	m_imageList = scanAllImages("E:/repo/CrossCompilerQtRpi2/image/");
	//std::sort(m_imageList.begin(), m_imageList.end());
	if (m_imageList.size() > 0)
	{

	}


	Logger->trace("ImageAcquisition::loadCapture() done");
}

void ImageAcquisition::onUpdate()
{
	Logger->trace("ImageAcquisition::onUpdate()");
	m_counter++;
	m_framerate = 999;
	QTime myTimer;

		Logger->trace("ImageAcquisition::onUpdate() m_capture.isOpened():{}", m_capture.isOpened());
		m_image = cv::imread("E:/repo/CrossCompilerQtRpi2/image/"+ m_imageList[m_counter].toStdString());
		Logger->info("open:{}","E:/repo/CrossCompilerQtRpi2/image/"+ m_imageList[m_counter].toStdString());
		if (m_image.empty())
		{
			loadCapture();
		}
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
			emit(update(m_imageGrayResized));
		}
	

#if(DEBUG)
	cv::imshow("m_imageGrayResized", m_imageGrayResized);
	cv::waitKey(1);

	
#endif
	QByteArray ImgByteI((char*)(m_imageGrayResized.data), 768); // 32x24x1
	Logger->trace("ImageAcquisition::onUpdate() emit(sendImage(ImgByteI));");
	emit(sendImage(3, ImgByteI));


	quint32 nMilliseconds2 = (quint32)myTimer.elapsed();
	m_framerateAdd += m_framerate;
	m_addingCounter += nMilliseconds2;
	if (m_counter >= 1300)
	{
		Logger->warn("ImageAcquisition::onUpdate() (configure)ImageAcquisition time:{}", ((double)m_addingCounter / (double)m_counter));
		Logger->warn("ImageAcquisition::onUpdate() (configure)ImageAcquisition framerate:{}", m_framerateAdd / (double)m_counter);
		m_addingCounter = 0;
		m_counter = 0;
		m_framerateAdd = 0;
	}
}
