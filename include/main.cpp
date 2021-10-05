#include <WiFi.h>
#include <HTTPClient.h>

//curl -d "pgn=1. e4 e5 2. Nf3 Nf6 3. Nxe5 Qe7 4. d4 d6 5. Nf3 Qxe4+ 6. Be2 Be7 7. Nc3 Qg6 8. Bf4 Qxg2 9. Kd2 Qxf2 10. Rf1 Qg2 11. Qe1" -Ls -w %{url_effective} -o /dev/null https://lichess.org/import

const char* ssid = "Rep Oscar Cavara";
const char* password =  "tanoquadro";
const char* serverName = "https://lichess.org/api/import";

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
}



void loop() {
  if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status
  
    HTTPClient http;   
  
    http.begin(serverName);  //Specify destination for HTTP request
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");             //Specify content-type header
  
    int httpResponseCode = http.POST("pgn=1. e4 e5 2. Nf3 Nf6 3. Nxe5 Qe7 4. d4 d6 5. Nf3 Qxe4+ 6. Be2 Be7 7. Nc3 Qg6 8. Bf4 Qxg2 9. Kd2 Qxf2 10. Rf1 Qg2 11. Qe1");   //Send the actual POST request
  
  if(httpResponseCode>0){
  
    String response = http.getString();  //Get the response to the request
  
    Serial.println(httpResponseCode);   //Print return code
    Serial.println(response);           //Print request answer
  }

  else{
    Serial.print("Error on sending POST: ");
    Serial.println(httpResponseCode);
  
  }
  
  http.end();  //Free resources
  }

  else{
  
    Serial.println("Error in WiFi connection");   
  
 }
  
  delay(60000);  //Send a request every 60 seconds
  
}