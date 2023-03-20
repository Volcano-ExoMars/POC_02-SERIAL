#include<arduino.h>

// Liaison Série
uint8_t indexChar = 0;
uint8_t typeMessage;

void initCommandeSerie() {
    for (uint8_t i=0; i<sizeof(mqttMsg)-1; i++)
    mqttMsg[i]=' ';
    indexChar = 0;
}

void traitementSerial() {
        char caractereLu = char(Serial2.read());

        switch( caractereLu) {
            case 'T' : {
                typeMessage = 0;
                initCommandeSerie();
                break;
            }
            case 'H' : {
                typeMessage = 1;
                initCommandeSerie();
                break;
            }
           case 'P' : {
                typeMessage = 2;
                initCommandeSerie();
                break;
            }
           case 'G' : {
                typeMessage = 3;
                initCommandeSerie();
                break;
            }
            case 'X' : {
                sprintf(mqttTopic, "ROBOTS/%s/%s", ROBOT_NUM, topicMQTT[typeMessage]);         
                mqtt.publish(mqttTopic, mqttMsg);
                Serial.println(mqttTopic);
                Serial.println(mqttMsg);
                break;
            }
            default : {
                if ( indexChar< sizeof(mqttMsg) )
                    mqttMsg[indexChar++] = caractereLu;
            }
        }
}