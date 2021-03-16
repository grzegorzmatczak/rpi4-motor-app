#include "uart.h"

constexpr auto GENERAL{"General"};
constexpr auto DEVICE_ID{ "DeviceId" };

Uart::Uart(QJsonObject a_config)
{
	m_serialPort = new QSerialPort();
	m_serialPort->setPortName("/dev/ttyUSB0");
	const int serialPortBaudRate =  QSerialPort::Baud9600;
	m_serialPort->setBaudRate(serialPortBaudRate);

	if (!m_serialPort->open(QIODevice::ReadOnly)) {
		Logger->error("serialPort.open(QIODevice::ReadOnly) failed!!");
	}
	else
	{
		Logger->error("serialPort.open(QIODevice::ReadOnly) ok!!");
	}
	m_serialPortReader = new SerialPortReader(m_serialPort);
	m_serialPortWriter = new SerialPortWriter(m_serialPort);
}

void Uart::onUpdate()
{
#ifdef __linux__

#endif // __linux__
}

void Uart::configure(QJsonObject const& a_config)
{
	Logger->info("MainLoop::configure()");
}

void Uart::write(const QByteArray& writeData)
{
	m_serialPortWriter->write(writeData);
}