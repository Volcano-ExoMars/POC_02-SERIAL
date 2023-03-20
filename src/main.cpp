#include <Arduino.h>

// Librairies Serveur Web
#include <ESPAsyncWebServer.h>

// Librairies MQTT
#include <PubSubClient.h>
// Maison
//const char *SSID = "Livebox-A250";
//const char *PWD= "yezvypYswaeUhtGGTL";

// Partage Wifi GSM
const char *SSID = "AndroidAP1550";
const char *PWD= "973b6716f3fb";

// Paramétrage MQTT
const char * ROBOT_NUM = "01";
const char * HOSTNAME = "LES BRICOLOS";
const char * mqtt_server = "192.168.43.14";
const char * mqtt_user = "nao974";
const char * mqtt_passwd = "az$er";
WiFiClient espClientWifi;
PubSubClient mqtt(espClientWifi);
char mqttTopic[64]; // array pour le nom du topic à envoyer
char mqttMsg[16]; // array pour les données des messages à envoyer
char topicMQTT[][12]={"TEMPERATURE", "HUMIDITY", "PRESSION", "GAZ"};
uint8_t mqttInitRobot = 1;
#include <mqtt.h>

// Liaison Série
#include <serialMessage.h>

void setup() {
// Initialisation liaison Série de debug sur USB    
    Serial.begin(9600);
    delay(1000);
    Serial.println("\nDémarrage");

// Initialisation liaison avec Arduino MEGA
    Serial2.begin(9600, SERIAL_8N1, 16, 14); //RX , TX
    
// Connexion au WIFI
    Serial.println("\nInit Wifi"); 
    WiFi.begin(SSID, PWD);
	Serial.print("   Tentative de connexion...");
	
	while(WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
		delay(100);
	}
	Serial.println("");
	Serial.println("   Connexion etablie!");
	Serial.print("   Adresse IP: ");
	Serial.println(WiFi.localIP());

// Configuration du Broker MQTT
    mqtt.setServer(mqtt_server, 1883);
}

void loop() {

// sommes nous connectés au serveur MQTT ?
    if (!mqtt.connected() )
        reconnect();

    while ( Serial2.available() ) 
        traitementSerial();

  delay(1000);
}

