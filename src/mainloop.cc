#include "mainloop.h"

constexpr auto GENERAL{ "General" };
constexpr auto THREADSMAX{ "ThreadsMax" };
constexpr auto ARDUINO{ "Arduino" };
constexpr auto IMAGE_ACQUISITION{ "ImageAcquisition" };
constexpr auto IMAGE_BOUNDS{ "ImageBounds" };
constexpr auto SERVER{ "Server" };
constexpr auto INFO_TOPIC{ "InfoTopic" };
constexpr auto COMMAND_TOPIC{ "CommandTopic" };
constexpr auto IMAGE_TOPIC{ "ImageTopic" };
constexpr auto TICK{ "Tick" };


MainLoop::MainLoop(QJsonObject a_config)
	:m_config{ a_config }
	, m_threadsMax{ a_config[GENERAL].toObject()[THREADSMAX].toInt() }
	, m_firstTime(true)
	, m_tickAcquisition(a_config[GENERAL].toObject()[TICK].toInt())
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
	//m_arduinoControlThread->start();

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

	// Uart:
	m_uartThread = new QThread();
	m_uart = new Uart(m_config[SERVER].toObject());
	m_uart->moveToThread(m_uartThread);
	connect(m_uartThread, &QThread::finished, m_uart, &QObject::deleteLater);
	m_uartThread->start();

	// ImageAcquisition:
	m_imageAcquisition = new ImageAcquisition(m_config[IMAGE_ACQUISITION].toObject());
	m_ImageAcquisitionThread = new QThread();
	m_imageAcquisition->moveToThread(m_ImageAcquisitionThread);
	connect(m_ImageAcquisitionThread, &QThread::finished, m_imageAcquisition, &QObject::deleteLater);
	m_ImageAcquisitionThread->start();
	connect(m_imageAcquisition, &ImageAcquisition::sendImage, m_server, &Broadcaster::onSendImage);
	m_timerAcquisition = new QTimer(this);
	m_timerAcquisition->start(m_tickAcquisition);
	connect(m_timerAcquisition, SIGNAL(timeout()), m_imageAcquisition, SLOT(onUpdate()));


	// Bounds:
	m_imageBounds = new Bounds(m_config[IMAGE_BOUNDS].toObject());
	m_imageBoundsThread = new QThread();
	m_imageBounds->moveToThread(m_imageBoundsThread);
	connect(m_imageBoundsThread, &QThread::finished, m_imageBounds, &QObject::deleteLater);
	m_imageBoundsThread->start();
	connect(m_imageAcquisition, &ImageAcquisition::update, m_imageBounds, &Bounds::onUpdate);
	connect(m_imageBounds, &Bounds::sendImage, m_server, &Broadcaster::onSendImage);
	connect(m_imageBounds, &Bounds::sendError, m_server, &Broadcaster::onSendError);
}