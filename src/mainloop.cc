#include "mainloop.h"

constexpr auto GENERAL{"General"};
constexpr auto THREADSMAX{"ThreadsMax"};
constexpr auto ARDUINO{ "Arduino" };


MainLoop::MainLoop(QJsonObject a_config)
	:m_config{ a_config },
	m_threadsMax{ a_config[GENERAL].toObject()[THREADSMAX].toInt() }
{
	
	Logger->trace("ConfigManager:: m_threadsMax:{}", m_threadsMax);
	MainLoop::createStartupThreads();
}

void MainLoop::onUpdate()
{
	
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
	//connect(m_timer, QTimer::timeout(QTimer::QPrivateSignal) , m_arduinoControl, ArduinoControl::onUpdate);
}