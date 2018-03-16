/*
Driving a DC motor with Feather Huzzah ESP8266 using DC Motor + Stepper
FeatherWing Add-on

*/

#include <ESP8266WiFi.h>
#include <PubSubClient.h>


#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <Servo.h>

// Update these with values suitable for your network.

const char* ssid = "BMWTMS";
const char* password = "BMWtms18";
const char* mqtt_server = "192.168.0.101";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61); 

// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *myMotor = AFMS.getMotor(2);
// You can also make another motor on port M2
//Adafruit_DCMotor *myOtherMotor = AFMS.getMotor(2);

Servo servo1;

void setup() {
  Serial.begin(9600);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  AFMS.begin();  // create with the default frequency 1.6KHz
  myMotor->setSpeed(150);
  myMotor->run(FORWARD);
  myMotor->run(RELEASE);

  servo1.attach(0);
}

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  Serial.println();

  char p[length + 1];
  memcpy(p, payload, length);
  p[length] = NULL;
  uint8_t setpoint = atoi(p);
 

if (String(topic) == "move") {
    Serial.println(String(setpoint));
    if (setpoint == 1) {
      Serial.println("Moving forward...");
      // open
      myMotor->run(FORWARD);
      myMotor->setSpeed(255);  

    }
    else if (setpoint == 2) {
      Serial.println("Moving backward...");
      // close  
      myMotor->run(BACKWARD);
      myMotor->setSpeed(255);  
      }
      
      else if (setpoint == 0) {
      Serial.println("Stopping...");
      // stop  
        myMotor->setSpeed(0);  
        myMotor->run(RELEASE);
      }
  }
    
   
  else if (String(topic) == "position") {

    if (setpoint == 0) {
      
      // long unfold
      myMotor->run(FORWARD);
      myMotor->setSpeed(255);  
      delay(4000);
      myMotor->setSpeed(0);
    }

    if (setpoint == 1) {
      // short unfold
      myMotor->run(FORWARD);
      myMotor->setSpeed(255);  
      delay(1000);
      myMotor->setSpeed(0);
    }

    if (setpoint == 2) {
      // long fold
      myMotor->run(BACKWARD);
      myMotor->setSpeed(255);  
      delay(4000);
      myMotor->setSpeed(0);
        
    }

    if (setpoint == 3) {
      // short fold
      myMotor->run(BACKWARD);
      myMotor->setSpeed(255);  
      delay(1000);
      myMotor->setSpeed(0);
     }
    
    }
    
    else if (String(topic) == "speed") {
     // currently just stopping
     myMotor->setSpeed(0);
     myMotor->run(RELEASE);
    }

    else if(String(topic) == "checkconnection") {
      Serial.println("Connection is up!");
      String msg_str = String(1);
      msg_str.toCharArray(msg, msg_str.length() + 1);
      client.publish("connected", msg);
    }

    else if(String(topic) == "servo1") {
      Serial.println("Activating servo1");
      servo1.write(setpoint);
      delay(50);
    }
    
     
  }

  
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("outTopic", "hello world");
      
      String msg_str = String(1);
      msg_str.toCharArray(msg, msg_str.length() + 1);
      client.publish("connected", msg);
      // ... and resubscribe
      client.subscribe("speed");
      client.subscribe("move");
      client.subscribe("position");
      client.subscribe("checkconnection");
      client.subscribe("servo1");
      
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
