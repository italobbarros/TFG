#include "connection.h"
#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "ChessBoard.h"

//curl -d "pgn=1. e4 e5 2. Nf3 Nf6 3. Nxe5 Qe7 4. d4 d6 5. Nf3 Qxe4+ 6. Be2 Be7 7. Nc3 Qg6 8. Bf4 Qxg2 9. Kd2 Qxf2 10. Rf1 Qg2 11. Qe1" -Ls -w %{url_effective} -o /dev/null https://lichess.org/import

const char* ssid = "Italo";
const char* password =  "277512340001";
DynamicJsonDocument doc(1024);
const char* serverName = "https://lichess.org/api/import";

String apiKey = "318651";              //Add your Token number that bot has sent you on WhatsApp messenger
String phone_number = "+553599082130"; //Add your WhatsApp app registered phone number (same number that bot send you in url)

String url;                            //url String will be used to store the final generated URL

String urlencode(String str)  // Function used for encoding the url
{
    String encodedString="";
    char c;
    char code0;
    char code1;
    char code2;
    for (int i =0; i < str.length(); i++){
      c=str.charAt(i);
      if (c == ' '){
        encodedString+= '+';
      } else if (isalnum(c)){
        encodedString+=c;
      } else{
        code1=(c & 0xf)+'0';
        if ((c & 0xf) >9){
            code1=(c & 0xf) - 10 + 'A';
        }
        c=(c>>4)&0xf;
        code0=c+'0';
        if (c > 9){
            code0=c - 10 + 'A';
        }
        code2='\0';
        encodedString+='%';
        encodedString+=code0;
        encodedString+=code1;
        //encodedString+=code2;
      }
      yield();
    }
    return encodedString;
}

void postData()     //userDefine function used to call api(POST data)
{
  int httpCode;     // variable used to get the responce http code after calling api
  HTTPClient http;  // Declare object of class HTTPClient
  http.begin(url);  // begin the HTTPClient object with generated url
  httpCode = http.POST(url); // Finaly Post the URL with this function and it will store the http code
  if (httpCode == 200)      // Check if the responce http code is 200
  {
    Serial.println("Sent ok."); // print message sent ok message
  }
  else                      // if response HTTP code is not 200 it means there is some error.
  {
    Serial.println("Error."); // print error message.
  }
  http.end();          // After calling API end the HTTP client object.
}

void  message_to_whatsapp(String message)       // user define function to send meassage to WhatsApp app
{
  //adding all number, your api key, your message into one complete url
  url = "https://api.callmebot.com/whatsapp.php?phone=" + phone_number + "&apikey=" + apiKey + "&text=" + urlencode(message);

  postData(); // calling postData to run the above-generated url once so that you will receive a message.
}

void connectWiFI()
{

  Serial.begin(115200);
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
}

void sendPGN() 
{
  if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status
  
    HTTPClient http;   
  
    http.begin(serverName);  //Specify destination for HTTP request
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");             //Specify content-type header
  
    int httpResponseCode = http.POST(getPGN());//Send the actual POST request
  
  if(httpResponseCode>0){
  
    String response = http.getString();  //Get the response to the request
    deserializeJson(doc,response);
    const char* url = doc["url"];
    Serial.println(url);
    Serial.println(httpResponseCode);   //Print return code
    Serial.println(response);           //Print request answer
    message_to_whatsapp(url);
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
  
  //delay(60000);  //Send a request every 60 seconds
  
}
