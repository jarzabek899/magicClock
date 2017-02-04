#include "FastLED.h"
#include "ESP8266.h"
#include <SoftwareSerial.h>

///leds define
#define NUM_LEDS 14
#define LEDS_PER_SEGMENT 2
#define LED_DATA_PIN 6
#define NUM_BYTES (NUM_LEDS*3)
#define BRIGHTNESS 100
#define UPDATES_PER_SECOND 1000

byte led_active[NUM_LEDS * 4]; //4 segments  0hours 1hours 2minutes 3 minutes
CRGB leds[NUM_LEDS];
byte buffer[NUM_BYTES];

int TIME[4];

CRGBPalette16 currentPalette = RainbowColors_p;
TBlendType    currentBlending = LINEARBLEND;
uint8_t startIndex = 0;


//wifi define
#define HOST_NAME   "82.209.243.241"
#define HOST_PORT   (123)
#define ssid "bulonowka"
#define pass "df64kitw0"

SoftwareSerial espSerial(10, 11);
ESP8266 wifi(espSerial, 9600);



void setup()
{
  Serial.begin(9600);
  ///led setup
  FastLED.clear(true);
  FastLED.addLeds<WS2812B, LED_DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  
  //wifi setup
  espSerial.begin(115200);
  wyslij("AT+CIOBAUD=9600", "OK", 500);
  espSerial.begin(9600);
  while (!wyslij("AT", "OK", 100)) {
   // Serial.println("Error connection to wifi modul");
    delay(1000);
  }

  wyslij("AT+CWMODE=1",  "OK", 500);
  wyslij("AT+CIPMODE=0", "OK", 500);
  wyslij("AT+CIPMUX=0",  "OK", 500);
  while (!wyslij("AT+CWJAP=\"bulonowka\",\"df64kitw0\"", "OK", 2000))
  {
  }
 // Serial.println("Connected to AP!");
  wyslij("AT+CIPSTA=\"192.168.1.105\"", "OK", 500);
  delay(200);

  /*  Serial.print("setup begin\r\n");
  Serial.print("Join AP success\r\n");
  Serial.print("IP: ");
  Serial.println(wifi.getLocalIP().c_str());

  /*  if (wifi.disableMUX()) {
  Serial.print("single ok\r\n");
  } else {
  Serial.print("single err\r\n");
  }*/

  //Serial.print("setup end\r\n");

}

void loop()
{
  ntpupdate();
  wyswietl(TIME[0], 0, 0);
  fillLEDsFromPaletteColors();
  FastLED.show();
}

///leds function
void fillLEDsFromPaletteColors()
{
  startIndex++; // speed

  uint8_t colorIndex = startIndex;
  for (int i = 0; i < NUM_LEDS; i++) {
    if (led_active[i] == 1)
      leds[i] = ColorFromPalette(currentPalette, colorIndex, BRIGHTNESS, currentBlending);
    else
      leds[i] = CRGB(0, 0, 0);
    colorIndex += 3;
  }

  FastLED.delay(1000 / UPDATES_PER_SECOND);
}

void wyswietl(int x,int segment,int offset)
{

  for (int i = 0; i < NUM_LEDS * 4; i++)
    led_active[i] = 0;


  if (x == 0) liczba0(segment,offset);
  else if (x == 1) liczba1(segment, offset);
  else if (x == 2) liczba2(segment, offset);
  else if (x == 3) liczba3(segment, offset);
  else if (x == 4) liczba4(segment, offset);
  else if (x == 5) liczba5(segment, offset);
  else if (x == 6) liczba6(segment, offset);
  else if (x == 7) liczba7(segment, offset);
  else if (x == 8) liczba8(segment, offset);
  else liczba9(segment, offset);

}

void segment1(int segment, int offset)
{
  for(int i=0;i<LEDS_PER_SEGMENT;i++)
  led_active[i+14 * segment + offset] = 1;
}
void segment2(int segment, int offset)
{
  led_active[2 + 14 * segment + offset] = 1;
  led_active[3 + 14 * segment + offset] = 1;
}
void segment3(int segment, int offset)
{
  led_active[4 + 14 * segment + offset] = 1;
  led_active[5 + 14 * segment + offset] = 1;
}
void segment4(int segment, int offset)
{
  led_active[6 + 14 * segment + offset] = 1;
  led_active[7 + 14 * segment + offset] = 1;
}
void segment5(int segment, int offset)
{
  led_active[8 + 14 * segment + offset] = 1;
  led_active[9 + 14 * segment + offset] = 1;
}
void segment6(int segment, int offset)
{
  led_active[10 + 14 * segment + offset] = 1;
  led_active[11 + 14 * segment + offset] = 1;
}
void segment7(int segment, int offset)
{
  led_active[12 + 14 * segment + offset] = 1;
  led_active[13 + 14 * segment + offset] = 1;
}

void liczba0(int segment, int offset)
{
  segment2(segment,offset);
  segment3(segment, offset);
  segment4(segment, offset);
  segment5(segment, offset);
  segment6(segment, offset);
  segment7(segment, offset);
}
void liczba1(int segment, int offset)

{
  segment2(segment, offset);
  segment7(segment, offset);
}
void liczba2(int segment, int offset)
{
  segment1(segment, offset);
  segment2(segment, offset);
  segment3(segment, offset);
  segment5(segment, offset);
  segment6(segment, offset);

}
void liczba3(int segment, int offset)
{
  segment1(segment, offset);
  segment2(segment, offset);
  segment3(segment, offset);
  segment6(segment, offset);
  segment7(segment, offset);
}
void liczba4(int segment, int offset)
{
  segment4(segment, offset);
  segment1(segment, offset);
  segment2(segment, offset);
  segment7(segment, offset);
}
void liczba5(int segment, int offset)
{
  segment1(segment, offset);
  segment4(segment, offset);
  segment3(segment, offset);
  segment7(segment, offset);
  segment6(segment, offset);

}
void liczba6(int segment, int offset)
{
  segment1(segment, offset);
  segment3(segment, offset);
  segment4(segment, offset);
  segment5(segment, offset);
  segment6(segment, offset);
  segment7(segment, offset);
}
void liczba7(int segment, int offset)
{
  segment2(segment, offset);
  segment3(segment, offset);
  segment7(segment, offset);
}
void liczba8(int segment, int offset)
{
  segment1(segment, offset);
  segment2(segment, offset);
  segment3(segment, offset);
  segment4(segment, offset);
  segment5(segment, offset);
  segment6(segment, offset);
  segment7(segment, offset);

}
void liczba9(int segment, int offset)
{
  segment1(segment, offset);
  segment2(segment, offset);
  segment3(segment, offset);
  segment4(segment, offset);
  segment6(segment, offset);
  segment7(segment, offset);
}



//wifi function
boolean wyslij(String Komenda_AT, char *Odpowiedz_AT, int czas_czekania) {
  espSerial.println(Komenda_AT);
  delay(czas_czekania);
  while (espSerial.available()>0) {
    if (espSerial.find(Odpowiedz_AT)) {
      return 1;
    }
  }
  return 0;
}

void ntpupdate()
{
  uint8_t buffer[128] = { 0 };

  if (wifi.registerUDP(HOST_NAME, HOST_PORT)) {
    //  Serial.print("register udp ok\r\n");
  }
  else {
    //   Serial.print("register udp err\r\n");
  }

  static const char PROGMEM
    timeReqA[] = { 227,  0,  6, 236 },
    timeReqB[] = { 49, 78, 49,  52 };
  // Assemble and issue request packet
  uint8_t       buf[48];
  memset(buf, 0, sizeof(buf));
  memcpy_P(buf, timeReqA, sizeof(timeReqA));
  memcpy_P(&buf[12], timeReqB, sizeof(timeReqB));


  //    char *buf = "Hello, this is client!";
  wifi.send((const uint8_t*)buf, 48);

  uint32_t len = wifi.recv(buffer, sizeof(buffer), 10000);
  if (len > 0) {
   // Serial.print("Godzina ");

    // Serial.print(buffer[42]);
    unsigned long t = (((unsigned long)buffer[40] << 24) |
      ((unsigned long)buffer[41] << 16) |
      ((unsigned long)buffer[42] << 8) |
      (unsigned long)buffer[43]) - 2208988800UL + 3600UL;


    unsigned long day = 86400;
    t = t % 86400;
    int godzina = t / 3600;
    t = t - (unsigned long)godzina * 3600;
    int minuta = t / 60;
    int sekunda = t - minuta * 60;
    TIME[0] = sekunda % 10;
    /*Serial.print(godzina);
    Serial.print(":");
    Serial.print(minuta);
    Serial.print(":");
    Serial.println(sekunda);
    /* Serial.print("unix time");
    Serial.println(t);*/
  }

  if (wifi.unregisterUDP()) {
   // Serial.print("unregister udp ");
   // Serial.println(" ok");
  }
  else {
  //  Serial.print("unregister udp ");
  //  Serial.println(" err");
  }

}
