#pragma once

// This ESPHome component wraps around the modbus-esp8266 by @emelianov:
// https://github.com/emelianov/modbus-esp8266
//
// by @jpeletier - Epic Labs, 2022

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

// callback for read and write lambdas
typedef std::function<uint16_t(uint16_t reg, uint16_t val)> cbOnReadWrite;

class ModbusServer : public esphome::uart::UARTDevice, public Component, public Stream {
 public:
  explicit ModbusServer();

  void setup() override;
  void loop() override;
  uint32_t baudRate();  // for compatibility with ModbusRTU lib
  /// @brief Sets the slave address for this instance
  /// @param address the slave address this instance will respond as
  void set_address(uint8_t address);

  /// @brief Adds a new range of holding registers
  /// @param start_address Address of the first register
  /// @param value Default value for the registers
  /// @param numregs Number of registers in the range
  /// @return true if successful
  bool add_holding_register(uint16_t start_address, uint16_t value, uint16_t numregs = 1);

  /// @brief Sets a holding register to the specified value
  /// @param address Address of the register
  /// @param value New value for the register
  /// @return true if successful
  bool write_holding_register(uint16_t address, uint16_t value);

  /// @brief Retrieves the current value of the given register
  /// @param address Address of the register to read
  /// @return the register value
  uint16_t read_holding_register(uint16_t address);

  /// @brief Sets a callback to be invoked when the specified register range is read
  /// @param address start address of the register range to watch
  /// @param cb callback to be called when a register is read. The callback can return a new value to be sent
  /// @param numregs number of registers to watch
  void on_read_holding_register(uint16_t address, cbOnReadWrite cb, uint16_t numregs = 1);

  /// @brief Sets a callback to be invoked when the specified register range is written
  /// @param address start address of the register range to watch
  /// @param cb callback to be called when a register is written
  /// @param numregs number of registers to watch
  void on_write_holding_register(uint16_t address, cbOnReadWrite cb, uint16_t numregs = 1);

  // Stream implementation required by ModbusRTU library
  size_t write(uint8_t);
  int available();
  int read();
  int peek();
  void flush();

 private:
  ModbusRTU mb;  // ModbusRTU instance, the man behind the curtain
};

}  // namespace modbus_server
}  // namespace esphome
