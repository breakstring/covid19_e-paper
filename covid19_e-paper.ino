#define ENABLE_GxEPD2_GFX 0
#include <GxEPD2_BW.h>
#include <GxEPD2_3C.h>
#include <Fonts/FreeMono9pt7b.h>
#include <Fonts/FreeSansBold18pt7b.h>

GxEPD2_3C<GxEPD2_290c, GxEPD2_290c::HEIGHT> display(GxEPD2_290c(/*CS=*/ 15, /*DC=*/ 27, /*RST=*/ 26, /*BUSY=*/ 25));
#include "bitmaps/Bitmaps3c128x296.h" // 2.9"  b/w/r
#include "Icons.h"

#include <ArduinoJson.h>
#include <WiFiClientSecure.h>


const char* ssid     = "********";     // your network SSID (name of wifi network)
const char* password = "********"; // your network password

const char*  server = "covid19.mathdro.id";  // Server URL
const String  baseURL = "https://covid19.mathdro.id/api";


const char* api_root_ca= \
"-----BEGIN CERTIFICATE-----\n" \
"MIIDSjCCAjKgAwIBAgIQRK+wgNajJ7qJMDmGLvhAazANBgkqhkiG9w0BAQUFADA/\n" \
"MSQwIgYDVQQKExtEaWdpdGFsIFNpZ25hdHVyZSBUcnVzdCBDby4xFzAVBgNVBAMT\n" \
"DkRTVCBSb290IENBIFgzMB4XDTAwMDkzMDIxMTIxOVoXDTIxMDkzMDE0MDExNVow\n" \
"PzEkMCIGA1UEChMbRGlnaXRhbCBTaWduYXR1cmUgVHJ1c3QgQ28uMRcwFQYDVQQD\n" \
"Ew5EU1QgUm9vdCBDQSBYMzCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEB\n" \
"AN+v6ZdQCINXtMxiZfaQguzH0yxrMMpb7NnDfcdAwRgUi+DoM3ZJKuM/IUmTrE4O\n" \
"rz5Iy2Xu/NMhD2XSKtkyj4zl93ewEnu1lcCJo6m67XMuegwGMoOifooUMM0RoOEq\n" \
"OLl5CjH9UL2AZd+3UWODyOKIYepLYYHsUmu5ouJLGiifSKOeDNoJjj4XLh7dIN9b\n" \
"xiqKqy69cK3FCxolkHRyxXtqqzTWMIn/5WgTe1QLyNau7Fqckh49ZLOMxt+/yUFw\n" \
"7BZy1SbsOFU5Q9D8/RhcQPGX69Wam40dutolucbY38EVAjqr2m7xPi71XAicPNaD\n" \
"aeQQmxkqtilX4+U9m5/wAl0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNV\n" \
"HQ8BAf8EBAMCAQYwHQYDVR0OBBYEFMSnsaR7LHH62+FLkHX/xBVghYkQMA0GCSqG\n" \
"SIb3DQEBBQUAA4IBAQCjGiybFwBcqR7uKGY3Or+Dxz9LwwmglSBd49lZRNI+DT69\n" \
"ikugdB/OEIKcdBodfpga3csTS7MgROSR6cz8faXbauX+5v3gTt23ADq1cEmv8uXr\n" \
"AvHRAosZy5Q6XkjEGB5YGV8eAlrwDPGxrancWYaLbumR9YbK+rlmM6pZW87ipxZz\n" \
"R8srzJmwN0jP41ZL9c8PDHIyh8bwRLtTcm1D9SZImlJnt1ir/md2cXjbDaJWFBM5\n" \
"JDGFoqgCWjBH4d1QB7wCCZAA62RjYJsWvIjJEubSfZGL+T0yjWW06XyxV3bqxbYo\n" \
"Ob8VZRzI9neWagqNdwvYkQsEjgfbKbYK7p2CNTUQ\n" \
"-----END CERTIFICATE-----\n";


const char CONFIRMED[] = "Confirmed:";
const char RECOVERED[] = "Recovered:";
const char DEATHS[] = "Deaths:";
const int COUNT = 5;
int loopFlag = 0;
const unsigned char* bitmaps[] =
  {
    gImage_IconEarth,gImage_IconChina,gImage_IconItaly,gImage_IconUSA,gImage_IconES,gImage_IconDE
  };
const String regionName[] = {
  "/","/countries/CN","/countries/IT","/countries/USA","/countries/ES","/countries/DE"
};

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(115200);
  delay(100);

  Serial.print("Attempting to connect to SSID: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  // attempt to connect to Wifi network:
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    // wait 1 second for re-trying
    delay(1000);
  }

  Serial.print("Connected to ");
  Serial.println(ssid);

  display.init(115200); // uses standard SPI pins, e.g. SCK(18), MISO(19), MOSI(23), SS(5)
  SPI.end(); // release standard SPI pins, e.g. SCK(18), MISO(19), MOSI(23), SS(5)
  SPI.begin(13, 12, 14, 15); // map and init SPI pins SCK(13), MISO(12), MOSI(14), SS(15)

}

void DrawIcon(int region_code, long confirmed,long deaths, long recovered )
{
  display.writeScreenBuffer();
  display.setRotation(3);
  display.setFullWindow();
  display.clearScreen();
  
  display.firstPage();
  do
  {
    display.fillScreen(GxEPD_WHITE);
    
    display.setFont(&FreeMono9pt7b);
    display.setTextColor(GxEPD_BLACK); 
    display.setCursor(130, 13);
    display.print(CONFIRMED); 
    display.setCursor(130, 53);
    display.print(DEATHS); 
    display.setCursor(130, 93);
    display.print(RECOVERED); 

    display.setFont(&FreeSansBold18pt7b);
    display.setTextColor(GxEPD_RED);
    display.setCursor(160, 40);
    char ConfirmedNumber[6];
    dtostrf(confirmed,1,0,ConfirmedNumber);
    int16_t tbx_c, tby_c; uint16_t tbw_c, tbh_c;
    display.getTextBounds(ConfirmedNumber, 0, 0, &tbx_c, &tby_c, &tbw_c, &tbh_c);
    display.print(ConfirmedNumber); 
    
    display.setFont(&FreeSansBold18pt7b);
    display.setTextColor(GxEPD_RED);
    char DeathsNumber[5];
    dtostrf(deaths,1,0,DeathsNumber);
    int16_t tbx_d, tby_d; uint16_t tbw_d, tbh_d;
    display.getTextBounds(DeathsNumber, 0, 0, &tbx_d, &tby_d, &tbw_d, &tbh_d);
    display.setCursor(160 + tbw_c - tbw_d, 80);
    display.print(String(deaths)); 

    display.setFont(&FreeSansBold18pt7b);
    display.setTextColor(GxEPD_BLACK);
    char RecoveredNumber[6];
    dtostrf(recovered,1,0,RecoveredNumber);
    int16_t tbx_r, tby_r; uint16_t tbw_r, tbh_r;
    display.getTextBounds(RecoveredNumber, 0, 0, &tbx_r, &tby_r, &tbw_r, &tbh_r);
    display.setCursor(160 + tbw_c - tbw_r, 120);
    display.print(RecoveredNumber); 

  }
  while (display.nextPage());
  display.drawImage(bitmaps[region_code],NULL,0,168, 128, 128,true,false,true); 
  //display.refresh(true);
}

void loop() {
  WiFiClientSecure client;
  client.setCACert(api_root_ca);
  // do nothing
  Serial.println("\nStarting connection to server...");
  if (!client.connect(server, 443))
    Serial.println("Connection failed!");
  else {
    if(loopFlag > COUNT)
      loopFlag = 0;
    // Make a HTTP request:
    String requestCmd = String( "GET " + baseURL + regionName[loopFlag] + " HTTP/1.0");
    Serial.println("Connected to server: " + requestCmd);
    loopFlag++;
    client.println(requestCmd);
    client.println("Host: covid19.mathdro.id");
    client.println("Connection: close");
    client.println();

    if (client.println() == 0) {
      Serial.println(F("Failed to send request"));
      return;
    }
    
    // Check HTTP status
    char status[32] = {0};
    client.readBytesUntil('\r', status, sizeof(status));
    if (strcmp(status, "HTTP/1.1 200 OK") != 0) {
      Serial.print(F("Unexpected response: "));
      Serial.println(status);
      return;
    }

    // Skip HTTP headers
    char endOfHeaders[] = "\r\n\r\n";
    if (!client.find(endOfHeaders)) {
      Serial.println(F("Invalid response"));
      return;
    }
    
    // Allocate the JSON document
    // Use arduinojson.org/v6/assistant to compute the capacity.
    const size_t capacity = 5*JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(10) + 740;
    DynamicJsonDocument doc(capacity);
    // Parse JSON object
    DeserializationError error = deserializeJson(doc, client);
    if (error) {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.c_str());
      return;
    }

    long c = doc["confirmed"]["value"].as<long>();
    long r = doc["recovered"]["value"].as<long>();
    long d = doc["deaths"]["value"].as<long>();  

    DrawIcon(loopFlag -1 ,c,d,r);
    client.stop();
  }

  delay(15000);
}
