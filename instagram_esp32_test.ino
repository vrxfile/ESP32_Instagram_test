#include <InstagramStats.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <JsonStreamingParser.h>

char ssid[] = "MGBot";
char password[] = "Terminator812";

WiFiClientSecure client;
InstagramStats instaStats(client);

unsigned long delayBetweenChecks = 10000;
unsigned long whenDueToCheck = 0;

String userName = "mgbotru";

void setup()
{
  // instaStats._debug = true;
  Serial.begin(115200);
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void getInstagramStatsForUser()
{
  Serial.println("Instagram statistics for: " + userName);
  InstagramUserStats response = instaStats.getUserStats(userName);
  Serial.print("Number of followers: ");
  Serial.println(response.followedByCount);
  Serial.println();
}

void loop()
{
  unsigned long timeNow = millis();
  if ((timeNow > whenDueToCheck))
  {
    getInstagramStatsForUser();
    whenDueToCheck = timeNow + delayBetweenChecks;
  }
}
