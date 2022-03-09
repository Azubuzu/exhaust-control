# exhaust-control
## Bluetooth command

List of available command for exhaust-control bluetooth module

| Command | Response | Description |
| ------ | ------ | ------ |
| valve_open | valve_open OK | Fully open the valve |
| valve_close | valve_close OK | Fully close the valve |
| valve_open_ms XXX | valve_open_ms XXX OK | Open the valve for XXX ms (no limit) |

## Connection between arduino nano and HC-05

| HC-05 pin | Arduino nano pin |
| ------ | ------ |
| STATE | Not connected |
| RXD | D3 |
| TXD | D2 |
| GND | GND |
| VCC | 3V3 |
| EN | Not connected |