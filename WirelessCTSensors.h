#ifndef WebCTSensors_h
#define WebCTSensors_h

#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

#include "Main.h"
#include "src\Utils.h"
#include "src\Base.h"

#include <ESP8266HTTPClient.h>
#include "CTSensor.h"
#include "SimpleTimer.h"


//define the number of CTSensor
#define NUMBER_OF_CTSENSOR 3

const char appDataPredefPassword[] PROGMEM = "ewcXoCt4HHjZUvY1";

class WebCTSensors : public Application
{
private:
  float clampRatios[3] = {0.0, 0.0, 0.0};
  float noiseCancellation[3] = {0.0, 0.0, 0.0};

  typedef struct
  {
    bool enabled = false;
    bool tls = false;
    char hostname[64 + 1] = {0};
    char apiKey[48 + 1] = {0};
    char commandType[10 + 1] = {0};
    int clampIds[3] = {0, 0, 0};

    byte fingerPrint[20] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  } Jeedom;
  Jeedom jeedom;

  CTSensor _ctSensors[NUMBER_OF_CTSENSOR];
  SimpleTimer _sendTimer;
  char serialBuffer[12] = {0};

  String _requests[NUMBER_OF_CTSENSOR];
  int _requestResults[NUMBER_OF_CTSENSOR];

  void SendTimerTick();

  void SetConfigDefaultValues();
  void ParseConfigJSON(JsonObject &root);
  bool ParseConfigWebRequest(AsyncWebServerRequest *request);
  String GenerateConfigJSON(bool forSaveFile);
  String GenerateStatusJSON();
  bool AppInit(bool reInit);
  void AppInitWebServer(AsyncWebServer &server, bool &shouldReboot, bool &pauseApplication);
  void AppRun();

  String GetStatus();

public:
  WebCTSensors(char appId, String fileName);
};

#endif