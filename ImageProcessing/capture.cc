#include "capture.h"

constexpr auto RPICAMERA{ "RpiCamera" };
constexpr auto RPICAMERASTILL{ "RpiCameraStill" };
constexpr auto WIDTH{ "WidthCamera" };
constexpr auto HEIGHT{ "HeightCamera" };
constexpr auto BRIGHTNESS{ "Brightness" };
constexpr auto CONTRAST{ "Contrast" };
constexpr auto SATURATION{ "Saturation" };
constexpr auto GAIN{ "Gain" };
constexpr auto CAP{ "Cap" };

Capture::Capture() {}

Capture::~Capture()
{
	if (m_rpiCamera and m_rpiCameraStill)
	{
		Logger->info("Capture::~Capture() destructor m_raspiCameraStill:");
		delete m_raspiCameraStill;
	}
	else if (m_rpiCamera)
	{
		Logger->info("Capture::~Capture() destructor m_raspiCamera:");
		delete m_raspiCamera;
	}
	else
	{
		Logger->info("Capture::~Capture() destructor m_USBCamera:");
		delete m_USBCamera;
	}
}

Capture::Capture(QJsonObject const& a_config)
	: m_rpiCamera{ a_config[RPICAMERA].toBool() }
	, m_rpiCameraStill{ a_config[RPICAMERASTILL].toBool() }
	, m_cap{ a_config[CAP].toInt() }
	, m_width{ a_config[WIDTH].toInt() }
	, m_height{ a_config[HEIGHT].toInt() }
	, m_brightness{ a_config[BRIGHTNESS].toInt() }
	, m_contrast{ a_config[CONTRAST].toInt() }
	, m_saturation{ a_config[SATURATION].toInt() }
	, m_gain{ a_config[GAIN].toInt() }
	, m_isOpened(false)
	, m_isGrabed(false)
{
	Logger->info("Capture::Capture() ");
	Logger->info("Capture::Capture() m_cap:{}", m_cap);
	confiugureFirstTime(a_config);
	confiugure(a_config);
}
void Capture::confiugureFirstTime(QJsonObject const& a_config)
{
	if (m_rpiCamera and m_rpiCameraStill)
	{
		m_raspiCameraStill = new raspicam::RaspiCam_Still_Cv;
	}
	else if (m_rpiCamera)
	{
		Logger->trace("Capture::Capture() m_rpiCamera:");
		m_raspiCamera = new raspicam::RaspiCam_Cv();
	}
	else
	{
		Logger->trace("Capture::Capture() m_USBCamera:");
		m_USBCamera = new cv::VideoCapture();
	}
}

void Capture::confiugure(QJsonObject const& a_config)
{
	Logger->trace("Capture::confiugure() ");

	Logger->trace("Capture::configure() m_width:{}", m_width);
	Logger->trace("Capture::configure() m_height:{}", m_height);
	Logger->trace("Capture::configure() m_brightness:{}", m_brightness);
	Logger->trace("Capture::configure() m_contrast:{}", m_contrast);
	Logger->trace("Capture::configure() m_saturation:{}", m_saturation);
	Logger->trace("Capture::configure() m_gain:{}", m_gain);

	if (m_rpiCamera and m_rpiCameraStill)
	{
		if (m_raspiCameraStill->open())
		{
			m_isOpened = true;
		}
		else
		{
			m_isOpened = false;
			Logger->trace("Capture::Capture() m_raspiCameraStill: failed to open device:");
		}
	}
	else if (m_rpiCamera)
	{
		Logger->trace("Capture::Capture() m_rpiCamera:");
		m_raspiCamera->set(cv::CAP_PROP_FRAME_WIDTH, m_width);
		m_raspiCamera->set(cv::CAP_PROP_FRAME_HEIGHT, m_height);
		m_raspiCamera->set(cv::CAP_PROP_BRIGHTNESS, m_brightness);
		m_raspiCamera->set(cv::CAP_PROP_CONTRAST, m_contrast);
		m_raspiCamera->set(cv::CAP_PROP_SATURATION, m_saturation);
		m_raspiCamera->set(cv::CAP_PROP_GAIN, m_gain);
		m_raspiCamera->set(cv::CAP_PROP_FPS, 90);
		m_raspiCamera->set(cv::CAP_PROP_FORMAT, CV_8UC1);
		if (m_raspiCamera->open())
		{
			m_isOpened = true;
		}
		else
		{
			Logger->trace("Capture::Capture() m_rpiCamera: failed to open device:");
		}
	}
	else
	{
		Logger->trace("Capture::Capture() m_USBCamera:");
		Capture::loadCapture();
	}
	Logger->trace("Capture::confiugure() done");
}

void Capture::grab(cv::Mat& image)
{
	Logger->trace("Capture::grab()");

	if (m_rpiCamera and m_rpiCameraStill)
	{
		if (m_raspiCameraStill->grab())
		{
			m_raspiCameraStill->retrieve(image);
			m_isGrabed = true;
		}
		else
		{
			Logger->error("Capture::grab() m_raspiCameraStill.grab() retrieve error");
			m_isGrabed = false;
		}
	}
	if (m_rpiCamera)
	{
		if (m_raspiCamera->grab())
		{
			m_raspiCamera->retrieve(image);
			Logger->trace("Capture::grab() m_raspiCamera.grab() retrieve ok");
			m_isGrabed = true;
		}
		else
		{
			m_isGrabed = false;
			Logger->error("Capture::grab() m_raspiCamera.grab() retrieve error");
		}
	}
	else
	{
		*m_USBCamera >> image;
		if (image.empty())
		{
			m_isGrabed = false;
			Logger->error("Capture::grab() image.empty()");
		}
	}
}
void Capture::loadCapture()
{
	Logger->trace("Capture::loadCapture()");
	m_USBCamera->open(m_cap);
	cv::Mat image;
	*m_USBCamera >> image;
	if (image.empty() == true)
	{
		// Check all video cap:
		for (int i = 0; i < 20; i++)
		{
			m_USBCamera->open(i);
			*m_USBCamera >> image;
			if (image.empty() == false)
			{
				Logger->warn("Capture::loadCapture() Open USB Camera capture:{}", i);
				return;
			}
			else
			{

			}
		}
	}
	Logger->error("Capture::loadCapture() Cant open USB Camera capture");
}

void Capture::changeCapture(QJsonObject const& a_config)
{
	Logger->trace("Capture::changeCapture()");

	m_width = { a_config[WIDTH].toInt() };
	m_height = { a_config[HEIGHT].toInt() };
	m_brightness = { a_config[BRIGHTNESS].toInt() };
	m_contrast = { a_config[CONTRAST].toInt() };
	m_saturation = { a_config[SATURATION].toInt() };
	m_gain = { a_config[GAIN].toInt() };
	confiugure(a_config);
}
