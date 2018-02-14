# Prerequisites:
- [Node-RED](https://nodered.org/docs/getting-started/installation)
- npm packages:
  - node-red-dashboard
- [Mosquitto](https://mosquitto.org/download/)


# Usage
1. Start mosquitto broker
2. Copy `nodered_flow.json` as your flow (usually in `~/.node-red` folder)
3. Configure IP for MQTT in the Node-RED
4. Add Feather Huzzah ESP8266 to Arduino IDE ([board manager URL](http://arduino.esp8266.com/stable/package_esp8266com_index.json))
5. Get `Adafruit Motor Shield V2` and `PubSubClient` Arduiono IDE libraries.
6. Configure MQTT broker IP, WiFi, and motor port in `sketch.ino`.



