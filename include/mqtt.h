#include <arduino.h>
#include <PubSubClient.h>

// Fonction de (re)connexion au serveur MQTT
// Et abonnement au topic ctrlled
void reconnect() {
// Connecté au Broker ?    
    while( !mqtt.connected() ) {
        Serial.println("\nConnexion serveur MQTT");
// Si non, on se connecte        
        if ( !mqtt.connect(HOSTNAME,mqtt_user, mqtt_passwd) ) {
            Serial.print("   MQTT KOOOOO, rc=");
            Serial.println(mqtt.state() );
            delay(5000);
            continue;
        }
    Serial.println("   MQTT OK!");
// Connecté, on s'abonne au topic "ctrlled"
    mqtt.subscribe("check");
    }
}

// Fonction appelée lors de la reception du topic paramétré dans la fonction connect
// Les paramétres sont imposés par la librairie MQTT
void callback(char* topic, uint8_t* payload, uint16_t length) {
// Affichage du topic reçu    
    Serial.print("Message [");
    Serial.print(topic);
    Serial.print("]= ");
// Affichage du payload (la donnée reçue)    
    for (uint16_t i = 0; i< length; i++)
        Serial.print((char) payload[i]);
    Serial.println();

// Action lors de la reception
// Le 1er caratère est "1" => Allumage de la LED
/*    if ( (char)payload[0] == '1' )   
        digitalWrite(PIN_LED, HIGH);
    else 
        digitalWrite(PIN_LED, LOW);
*/
}