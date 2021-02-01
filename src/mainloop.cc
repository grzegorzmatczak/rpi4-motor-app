#include "mainloop.h"

constexpr auto GENERAL{ "General" };
constexpr auto THREADSMAX{ "ThreadsMax" };
constexpr auto ARDUINO{ "Arduino" };
constexpr auto IMAGE_ACQUISITION{ "ImageAcquisition" };
constexpr auto SERVER{ "Server" };
constexpr auto INFO_TOPIC{ "InfoTopic" };
constexpr auto COMMAND_TOPIC{ "CommandTopic" };
constexpr auto IMAGE_TOPIC{ "ImageTopic" };

MainLoop::MainLoop(QJsonObject a_config)
	:m_config{ a_config },
	m_threadsMax{ a_config[GENERAL].toObject()[THREADSMAX].toInt() },
	m_firstTime(true)
{
	Logger->trace("ConfigManager:: m_threadsMax:{}", m_threadsMax);
	MainLoop::createStartupThreads();
}

void MainLoop::onUpdate()
{
	if (m_firstTime)
	{
		QVector<int> topics{ m_config[SERVER].toObject()[INFO_TOPIC].toInt() };
		Logger->info("Sub on topics:{}", m_config[SERVER].toObject()[INFO_TOPIC].toInt());
		m_server->onSubscribe(topics);
		m_firstTime = false;
	}
}

void MainLoop::configure(QJsonObject const& a_config)
{
	Logger->info("MainLoop::configure()");
}

void MainLoop::createStartupThreads()
{
	m_arduinoControlThread = new QThread();
	m_arduinoControl = new ArduinoControl(m_config[ARDUINO].toObject());

	m_arduinoControl->moveToThread(m_arduinoControlThread);
	connect(m_arduinoControlThread, &QThread::finished, m_arduinoControl, &QObject::deleteLater);
	m_arduinoControlThread->start();

	m_timer = new QTimer(this);
	m_timer->start(1000);
	connect(m_timer, SIGNAL(timeout()), m_arduinoControl, SLOT(onUpdate()));
	connect(m_timer, SIGNAL(timeout()), this, SLOT(onUpdate()));

	// Broadcaster:
	m_serverThread = new QThread();
	m_server = new Broadcaster(m_config[SERVER].toObject());
	m_server->moveToThread(m_serverThread);
	connect(m_serverThread, &QThread::finished, m_server, &QObject::deleteLater);
	m_serverThread->start();

	// ImageAcquisition:
	m_imageAcquisition = new ImageAcquisition(m_config[IMAGE_ACQUISITION].toObject());
	m_ImageAcquisitionThread = new QThread();
	m_imageAcquisition->moveToThread(m_ImageAcquisitionThread);
	connect(m_ImageAcquisitionThread, &QThread::finished, m_imageAcquisition, &QObject::deleteLater);
	m_ImageAcquisitionThread->start();
	connect(m_imageAcquisition, &ImageAcquisition::sendImage, m_server, &Broadcaster::onSendImage);
	m_timerAcquisition = new QTimer(this);
	m_timerAcquisition->start(100);
	connect(m_timerAcquisition, SIGNAL(timeout()), m_imageAcquisition, SLOT(onUpdate()));

}