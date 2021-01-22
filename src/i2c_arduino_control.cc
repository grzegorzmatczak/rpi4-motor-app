#include "i2c_arduino_control.h"

constexpr auto GENERAL{"General"};
constexpr auto DEVICE_ID{ "DeviceId" };

ArduinoControl::ArduinoControl(QJsonObject a_config)
	:m_config{ a_config }
{
    m_deviceId = m_config[DEVICE_ID].toInt();
#ifdef __linux__

    m_fd = wiringPiI2CSetup(m_deviceId);
    if (m_fd == -1) {
        Logger->error("ArduinoControl::ArduinoControl() Failed to init I2C communication.");
        return;
    }
    Logger->info("ArduinoControl::ArduinoControl() I2C communication successfully setup.");
#endif // __linux__

    m_dataToSend = 0;
    timer.start();
}

void ArduinoControl::onUpdate()
{
    timer.restart();
    m_dataToSend++;
#ifdef __linux__
    wiringPiI2CWrite(m_fd, m_dataToSend);
    
    Logger->trace("ArduinoControl::ArduinoControl() Send test data to arduino");
    int received_data = wiringPiI2CRead(m_fd);
    Logger->trace("ArduinoControl::ArduinoControl() Data received:{}", received_data);
    if (received_data == m_dataToSend) {
        Logger->trace("ArduinoControl::ArduinoControl() Success {}", timer.elapsed());
        qDebug() << "ArduinoControl::ArduinoControl():" << timer.elapsed() << "milliseconds";
    }
#endif // __linux__

}

void ArduinoControl::configure(QJsonObject const& a_config)
{
	Logger->info("MainLoop::configure()");
}
