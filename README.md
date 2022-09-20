# esphome-modbus-server
ESPHome Modbus Server component


Example configuration:

```yaml

esphome:
  name: 'modbus-slave'

esp32:
  board: esp32dev
  variant: esp32
  framework:
    type: arduino
    version: '2.0.2'
    platform_version: '4.0.0'

external_components:
  - source: github://epiclabs-io/esphome-modbus-server@master
    refresh: 60s
    components:
      - modbus_server

# Enable logging
logger:
#  level: VERBOSE

# Enable Home Assistant API
api:
ota:
wifi:
  ssid: YourSSID
  password: YourPassword

uart:
  - id: intmodbus
    tx_pin: 13
    rx_pin: 16
    baud_rate: 9600
    stop_bits: 1
    data_bits: 8
    parity: NONE
    debug:
      direction: BOTH

modbus_server:
  - id: modbuserver
    uart_id: intmodbus
    address: 1
    holding_registers:
      - offset: 79
        default: 82
        number: 10
        on_read: |
          ESP_LOGI("ON_READ", "This is a lambda. address=%d, value=%d", address, value);
          return value+1;
      - offset: 200
        number: 1
        on_write: |
          if(value)
            id(testswitch)->turn_on();
          else
            id(testswitch)->turn_off();
          return value;
        on_read: |
          return id(testswitch)->state ? 1 : 0;

switch:
  - platform: gpio
    pin: 2
    id: testswitch
