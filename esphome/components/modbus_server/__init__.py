import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import uart
from esphome.const import CONF_ADDRESS, CONF_ID


modbus_server_ns = cg.esphome_ns.namespace("modbus_server")
ModbusDeviceComponent = modbus_server_ns.class_("ModbusServer", cg.Component)

DEPENDENCIES = ["uart"]

CONFIG_SCHEMA = (
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(ModbusDeviceComponent),
            cv.Required(CONF_ADDRESS): cv.positive_int,
            cv.Optional("holding_registers"): cv.ensure_list(
                cv.Schema(
                    {
                        cv.Required("offset"): cv.positive_int,
                        cv.Optional("default", 0): cv.positive_int,
                        cv.Optional("number", 1): cv.positive_int,
                    }
                )
            ),
        }
    )
    .extend(uart.UART_DEVICE_SCHEMA)
    .extend(cv.COMPONENT_SCHEMA)
)

MULTI_CONF = True


async def to_code(config):

    cg.add_library("emelianov/modbus-esp8266", "4.1.0")
    id = config[CONF_ID]
    uart = await cg.get_variable(config["uart_id"])
    server = cg.new_Pvariable(id)
    cg.add(server.set_uart_parent(uart))
    cg.add(server.set_address(config[CONF_ADDRESS]))
    if "holding_registers" in config:
        for reg in config["holding_registers"]:
            cg.add(
                server.add_holding_register(
                    reg["offset"], reg["default"], reg["number"]
                )
            )

    await cg.register_component(server, config)

    return
