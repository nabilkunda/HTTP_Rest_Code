/* RestClient simple GET request

   by Fabiano França (fabianofranca)
*/

#include <ArduinoJson.h>
#include "RestClient.h"

#define switch_1 16
#define switch_2 5
#define switch_3 4
#define switch_4 2

int state_1 = LOW;
int state_2 = LOW;
int state_3 = LOW;
int state_4 = LOW;

String GUID = "4aef5569966a4de68da2237b68f83f95";
char* ssid = "Lenovo";
char* pass = "razinmemon";

RestClient client = RestClient("testsmarthome.azurewebsites.net");

//Setup
void setup() {
  pinMode(switch_1, OUTPUT);
  digitalWrite(switch_1, state_1);

  pinMode(switch_2, OUTPUT);
  digitalWrite(switch_2, state_2);

  pinMode(switch_3, OUTPUT);
  digitalWrite(switch_3, state_3);

  pinMode(switch_4, OUTPUT);
  digitalWrite(switch_4, state_4);

  Serial.begin(115200);
  Serial.println("connect to WiFi network");
  client.begin(ssid, pass);
  Serial.println("WIFI Connected");
  Serial.println("Setup!");
}

void loop() {
  String response = "";
  String urlString = "/api/status/Ping";
  const char* url = urlString.c_str();
  // String s = "{\"NodeId\" : \""+GUID+"\",\"SwitchesStatus\":[{\"SwitchNumber\":1, \"IsOn\":"+state_1+"}, {\"SwitchNumber\":2, \"IsOn\":"+state_2+"}, {\"SwitchNumber\":3, \"IsOn\":"+state_3+"}, {\"SwitchNumber\":4, \"IsOn\":"+state_4+"}]}";
  StaticJsonBuffer<500> requestJsonBuffer;
  JsonObject& request = requestJsonBuffer.createObject();
  request["NodeId"] = GUID;
  JsonArray& ss = request.createNestedArray("SwitchesStatus");
  JsonObject& sw1 = ss.createNestedObject();
  sw1["SwitchNumber"] = 1;
  sw1["IsOn"] = state_1;
  JsonObject& sw2 = ss.createNestedObject();
  sw2["SwitchNumber"] = 2;
  sw2["IsOn"] = state_2;
  JsonObject& sw3 = ss.createNestedObject();
  sw3["SwitchNumber"] = 3;
  sw3["IsOn"] = state_3;
  JsonObject& sw4 = ss.createNestedObject();
  sw4["SwitchNumber"] = 4;
  sw4["IsOn"] = state_4;
  String s;
  request.printTo(s);
const char* str = s.c_str();

 Serial.print("request to server: ");
  Serial.println(str);
  client.setContentType("application/json");
  int statusCode = client.post(url, str, &response);
  response.remove(0, response.indexOf("["));
  
  Serial.print("Status code from server: ");
  Serial.println(statusCode);
  Serial.print("Response body from server: ");
  Serial.println(response);
  
  if (statusCode == 200)
  {
    DynamicJsonBuffer jsonBuffer(200);

    JsonArray& root = jsonBuffer.parseArray(response);


    if (!root.success())
    {
      Serial.println("parsing failed");
    }
    else {
      for (int i = 0; i < root.size(); i++)
      {
        JsonObject& statusObject = root[i];
        int switchNumber = statusObject["switchNumber"].as<int>();
        int s = statusObject["status"].as<bool>() ? HIGH : LOW;
        Serial.print("Switch Number : ");
        Serial.println(switchNumber);
        Serial.print("Switch status: ");
        Serial.println(s);
        switch(switchNumber){
          case 1:
            Serial.println("Switch 1");
            state_1 = s;
            digitalWrite(switch_1, state_1);
            break;
           case 2:
            Serial.println("Switch 2");
            state_2 = s;
            digitalWrite(switch_2, state_2);
            break;
           case 3:
            Serial.println("Switch 3");
            state_3 = s;
            digitalWrite(switch_3, state_3);
            break;
           case 4:
            Serial.println("Switch 4");
            state_4 = s;
            digitalWrite(switch_4, state_4);
            break;
        }
      }
    }
  }
  delay(5000);
}
