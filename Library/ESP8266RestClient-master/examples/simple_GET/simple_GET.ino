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
  String urlString = "/api/test?node=" + GUID + "&pin1=" + state_1 + "&pin2=" + state_2 + "&pin3=" + state_3 + "&pin4=" + state_4;
  char* urlInCharArray;
  urlString.toCharArray(urlInCharArray, urlString.length());
  const char* url;
  strcpy(urlInCharArray, url);
  int statusCode = client.get(url, &response);
  response.remove(0, response.indexOf("{"));
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
        if (statusObject.containsKey("switch_1")) {
          state_1 = statusObject["switch_1"].as<int>();
          digitalWrite(switch_1, state_1);
        }

        if (statusObject.containsKey("switch_2")) {
          state_2 = statusObject["switch_2"].as<int>();
          digitalWrite(switch_2, state_2);
        }

        if (statusObject.containsKey("switch_3")) {
          state_3 = statusObject["switch_3"].as<int>();
          digitalWrite(switch_3, state_3);
        }

        if (statusObject.containsKey("switch_4")) {
          state_4 = statusObject["switch_4"].as<int>();
          digitalWrite(switch_4, state_4);
        }
      }
    }
  }
  Serial.print("Status code from server: ");
  Serial.println(statusCode);
  Serial.print("Response body from server: ");
  Serial.println(response);
  delay(1000);
}
