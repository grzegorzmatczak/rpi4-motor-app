#ifndef I2C_ARDUINO_CONTROL_H
#define I2C_ARDUINO_CONTROL_H

#include <QJsonObject>
#include "structures.h"

#include <iostream>

#include <QElapsedTimer>
#include <QDebug>

#ifdef _WIN32
#endif // _WIN32
#ifdef __linux__
#include <wiringPiI2C.h>
#endif // _UNIX



class ArduinoControl : public QObject {
	Q_OBJECT
public:
	explicit ArduinoControl(QJsonObject m_config);

signals:

public slots:
	void onUpdate();
	void configure(QJsonObject const& a_config);

private:
	int m_fd;
	int m_deviceId;

	QJsonObject m_config;
	QElapsedTimer timer;
	uint8_t m_dataToSend;
};

#endif // I2C_ARDUINO_CONTROL_H
