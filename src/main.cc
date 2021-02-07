#include <QJsonObject>
#include <QMetaEnum>
#include <QCoreApplication>
#include <QObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

#include "mainloop.h"
#include "structures.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

constexpr auto GENERAL{"General"};
constexpr auto PID{"Pid"};
constexpr auto LOG_LEVEL{"LogLevel"};


void intro();

int main(int argc, char* argv[]) {
	QCoreApplication application(argc, argv);

	qRegisterMetaType<cv::Mat>("cv::Mat");

	Logger->set_pattern("[%Y-%m-%d] [%H:%M:%S.%e] [%t] [%^%l%$] %v");
	Logger->debug("Start main logger with LogLevel:{}", 0);
	intro();
	
	//Config:
	QJsonObject m_config;
	QString configPathWithName = "config.json";
	if (argc > 1)
	{
		configPathWithName = QString::fromStdString(argv[1]);
	}
	Logger->trace("MainLoop::MainLoop() open config file:{}", configPathWithName.toStdString());

	ConfigReader* configReader = new ConfigReader();
	if (!configReader->readConfig(configPathWithName, m_config)) {
		Logger->error("File {} not readed", configPathWithName.toStdString());
		return -66;
	}
	delete configReader;

	Logger->set_level(static_cast<spdlog::level::level_enum>(m_config[GENERAL].toObject()[LOG_LEVEL].toInt()));
	intro();

	MainLoop mainLoop{ m_config};
	return application.exec();
}

void intro()
{
	Logger->info(
		"\n\n\t\033[1;31mrpi4-motor-app \033[0m\n"
		"\tAuthor: Grzegorz Matczak\n"
		"\t07.02s.2021\n");
}
