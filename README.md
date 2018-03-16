# Prerequisites:
- [Node-RED](https://nodered.org/docs/getting-started/installation)
- npm packages:
  - node-red-dashboard
- [Mosquitto](https://mosquitto.org/download/)


# Usage
## Setup Raspberry Pi:
1. Start mosquitto broker (Should run automatically as a service after first start)
2. Copy `nodered_flow.json` as your flow (usually in `~/.node-red` folder)
3. Configure the network to use the static local IP address specified in the arduino sketch (192.168.0.101)
4. Setup the wireless card to connect automatically to the local WLAN
5. Either configure node-red to start automatically after boot, or start it manually through ssh. Remember to start it with the correct sketch name (e.g. $ node-red nodered_flow.json)

## Setup Feather:
1. Add Feather Huzzah ESP8266 to Arduino IDE ([board manager URL](http://arduino.esp8266.com/stable/package_esp8266com_index.json))
2. Get `Adafruit Motor Shield V2` and `PubSubClient` Arduiono IDE libraries.
3. Configure MQTT broker IP, WiFi, and motor port in `sketch.ino`.
4. Flash the code on to the board



