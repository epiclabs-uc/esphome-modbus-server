#pragma once

#include "esphome/core/component.h"
#include "esphome/core/entity_base.h"
#include "esphome/core/preferences.h"
#include "esphome/core/helpers.h"
#include "esphome/components/uart/uart.h"
#include <ModbusRTU.h>
#include <Stream.h>

namespace esphome {
namespace modbus_server {
using namespace std;

typedef std::function<uint16_t(uint16_t reg, uint16_t val)> cbOnRead;  // Callback function Type

class ModbusServer : public esphome::uart::UARTDevice, public Component, public Stream {
 public:
  explicit ModbusServer();

  void setup() override;
  void loop() override;
  uint32_t baudRate();
  void set_address(uint8_t address);
  bool add_holding_register(uint16_t offset, uint16_t value, uint16_t numregs = 1);
  bool write_holding_register(uint16_t offset, uint16_t value);
  uint16_t read_holding_register(uint16_t offset);

  void on_read_holding_register(uint16_t offset, cbOnRead cb, uint16_t numregs = 1);

  // Stream
  size_t write(uint8_t);
  int available();
  int read();
  int peek();
  void flush();

 private:
  ModbusRTU mb;
};

}  // namespace modbus_server
}  // namespace esphome
