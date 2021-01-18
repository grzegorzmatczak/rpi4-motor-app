#include "mainloop.h"

constexpr auto GENERAL{"General"};
constexpr auto THREADSMAX{"ThreadsMax"};


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
	m_dataMemoryThread = new QThread();
	//m_dataMemory = new DataMemory();
	//connect(m_dataMemory, &DataMemory::memoryLoaded, this, &MainLoop::onMemoryLoaded);
	//m_dataMemory->moveToThread(m_dataMemoryThread);
	//connect(m_dataMemoryThread, &QThread::finished, m_dataMemory, &QObject::deleteLater);
	//m_dataMemoryThread->start();


	m_timer = new QTimer(this);
	m_timer->start(1000);
	//connect(m_timer, SIGNAL(timeout()), this, SLOT(onUpdate()));
	
}