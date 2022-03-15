# exhaust-control
## Bluetooth command

List of available command for exhaust-control bluetooth module

| Command | Response | Description |
| ------ | ------ | ------ |
| valve_open | valve_open OK | Fully open the valve |
| valve_close | valve_close OK | Fully close the valve |
| valve_open_ms XXX | valve_open_ms XXX OK | Open the valve for XXX ms (no limit) |

## Connection between HC-05 and arduino nano

| HC-05 pin | Arduino nano pin |
| ------ | ------ |
| STATE | Not connected |
| RXD | D3 |
| TXD | D2 |
| GND | GND |
| VCC | 3V3 |
| EN | Not connected |

## Connection between arduino and the mosfets

| Arduino nano pin | Mosfet |
| ------ | ------ |
| D4 | Power supply |
| D5 | Control |

## Configure the HC-05

- HC-05 on AT mode (press STATE button on power up)
- HC-05 baud rate = 38400
- COM console must have NL&CR

### Change name
```sh
AT+NAME=REMUS
```

### Change password
```sh
AT+PSWD="2802"
```