#ifndef MAINLOOP_H
#define MAINLOOP_H

#include <QDebug>
#include <QJsonObject>
#include <QObject>
#include <QThread>
#include <QTimer>
#include <deque>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include "structures.h"
#include "i2c_arduino_control.h"
#include "../Broadcaster/include/broadcaster.h"
#include "../ImageProcessing/acquisition.h"
#include "../ImageProcessing/bounds.h"


class MainLoop : public QObject {
	Q_OBJECT
public:
	explicit MainLoop(QJsonObject m_config);

private:
	void createStartupThreads();

signals:

public slots:
	void onUpdate();
	void configure(QJsonObject const& a_config);

private:
	// Threads:
	const qint32 m_threadsMax{};

	QThread* m_arduinoControlThread;
	ArduinoControl* m_arduinoControl;

	QThread* m_serverThread;
	Broadcaster* m_server;

	QThread* m_ImageAcquisitionThread;
	ImageAcquisition* m_imageAcquisition;

	QThread* m_imageBoundsThread;
	Bounds* m_imageBounds;

private:
	// Configs:
	QJsonObject m_config;

private:
	// Timers:
	QTimer* m_timer;
	QTimer* m_timerAcquisition;

private:
	// Bools:
	bool m_firstTime{};
	qint32 m_tickAcquisition{};
};
#endif // MAINLOOP_H