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
char* ssid = "JioFi3_85F74E";
char* pass = "3c6k9smpd1";

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
  String urlString = "/api/status?node=" + GUID + "&pin1=" + state_1 + "&pin2=" + state_2 + "&pin3=" + state_3 + "&pin4=" + state_4;
  Serial.println(urlString);
  Serial.print("Size of urlstring is :");
  Serial.println(sizeof(urlString.length()+1));
  //char url[sizeof(urlString)];
  const char* url = urlString.c_str();
  //urlString.toCharArray(url,sizeof(urlString.length()+1));
  Serial.println(url);
  int statusCode = client.get(url, &response);
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
        const char* switchName = statusObject["switchName"].as<const char*>();
        int s = statusObject["status"].as<int>();
        if (strcmp(switchName, "switch_1") == 0) {
          state_1 = s;
          digitalWrite(switch_1, state_1);
        }
        else if (strcmp(switchName, "switch_2") == 0) {
          state_2 = s;
          digitalWrite(switch_2, state_2);
        }
        else if (strcmp(switchName, "switch_3") == 0) {
          state_3 = s;
          digitalWrite(switch_3, state_3);
        }
        else if (strcmp(switchName, "switch_4") == 0) {
          state_4 = s;
          digitalWrite(switch_4, state_4);
        }
      }
    }
  }
  delay(1000);
}

const char* Convert(String s) {
  char* charArray;
  s.toCharArray(charArray, s.length());
  const char* constChar;
  strcpy(charArray, constChar);
  return constChar;
}
