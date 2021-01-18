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

	QThread* m_dataMemoryThread;
	//DataMemory* m_dataMemory;

private:
	// Configs:
	QJsonObject m_config;
	

private:
	// Timers:
	QTimer* m_timer;
	
private:
	// Bools:
	bool m_register{};
	bool m_recvTask{};
	bool m_validTask{};

};

#endif // MAINLOOP_H
