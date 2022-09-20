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

class ModbusServer : public esphome::uart::UARTDevice, public Component, public Stream {
 public:
  explicit ModbusServer();

  void setup() override;
  void loop() override;
  uint32_t baudRate();

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
