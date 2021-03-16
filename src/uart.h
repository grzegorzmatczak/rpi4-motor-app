#ifndef UART_H
#define UART_H

#include <QJsonObject>
#include "structures.h"
#include <QSerialPort>
#include <QStringList>
#include <QTextStream>
#include "serialportreader.h"
#include "serialportwriter.h"

#ifdef _WIN32
#endif // _WIN32
#ifdef __linux__
#include <wiringPiI2C.h>
#endif // _UNIX


class Uart : public QObject {
	Q_OBJECT
public:
	explicit Uart(QJsonObject m_config);

signals:

public slots:
	void onUpdate();
	void configure(QJsonObject const& a_config);
	void write(const QByteArray& writeData);

private:
	QSerialPort *m_serialPort;
	SerialPortReader* m_serialPortReader;
	SerialPortWriter* m_serialPortWriter;
};

#endif // UART_H
