#include <string.h>
#include "modbus_server.h"
#include "esphome/core/log.h"

#define TAG "ModbusServer"

namespace esphome {
namespace modbus_server {
ModbusServer::ModbusServer() {}

uint32_t ModbusServer::baudRate() { return this->parent_->get_baud_rate(); }

void ModbusServer::setup() {
  ESP_LOGI(TAG, "setup()");
  mb.begin(this);
  mb.addHreg(10);
  mb.Hreg(10, 79);
}

void ModbusServer::set_address(uint8_t address) { mb.slave(address); }
bool ModbusServer::add_holding_register(uint16_t offset, uint16_t value, uint16_t numregs) {
  return mb.addHreg(offset, value, numregs);
}
bool ModbusServer::set_holding_register(uint16_t offset, uint16_t value) { return mb.Hreg(offset, value); }

// Stream class implementation:
size_t ModbusServer::write(uint8_t data) { return uart::UARTDevice::write(data); }
int ModbusServer::available() { return uart::UARTDevice::available(); }
int ModbusServer::read() { return uart::UARTDevice::read(); }
int ModbusServer::peek() { return uart::UARTDevice::peek(); }
void ModbusServer::flush() { uart::UARTDevice::flush(); }

void ModbusServer::loop() { mb.task(); };
}  // namespace modbus_server

}  // namespace esphome
