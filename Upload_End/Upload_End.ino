/* 
 * Typical pin layout used:
 * -----------------------------------------------------------------------------------------
 *             MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
 *             Reader/PCD   Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro
 * Signal      Pin          Pin           Pin       Pin        Pin              Pin
 * -----------------------------------------------------------------------------------------
 * RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
 * SPI SS      SDA(SS)      10            53        D10        10               10
 * SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
 * SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
 * SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
 */

#include <SPI.h>
#include <MFRC522.h>
#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>

#define RST_PIN         5                                         // Configurable, see typical pin layout above
#define SS_PIN          4                                        // Configurable, see typical pin layout above
#define FIREBASE_HOST "vendor-d7e9b.firebaseio.com"               // Firebase Host Name
#define FIREBASE_AUTH "sThPXEnVlOE5zmPCEphGKGgCHnw6XFtLGxtBUb8V"  // Firebase Authorisation Key
#define WIFI_SSID "Xperia"                                        // Name of the Hotspot to be connected
#define WIFI_PASSWORD "qwerty12345"                               // Password of the hotspot

MFRC522 mfrc522(SS_PIN, RST_PIN);                                 // Create MFRC522 instance

void setup()
{
	Serial.begin(9600);		                                          // Initialize serial communications with the PC
  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                           // WI-FI initialisation begins
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);                   // Firebase Communication setup
  Firebase.reconnectWiFi(true);

	SPI.begin();			                                              // Initialise SPI bus
	mfrc522.PCD_Init();		                                          // Initialise MFRC522
  mfrc522.PCD_DumpVersionToSerial();	                            // Show details of PCD - MFRC522 Card Reader details
  Serial.println("Scan PICC to see UID, SAK, type, and data blocks...");
}

String UID_prev = "";
FirebaseData firebaseData; //Define FirebaseESP8266 data object

void loop()
{
	if ( ! mfrc522.PICC_IsNewCardPresent())                       // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
	{
		return;
	}

	if ( ! mfrc522.PICC_ReadCardSerial())                         // Select one of the cards
	{
		return;
	}

  String UID="";
  for (byte i = 0; i < mfrc522.uid.size; i++)                    // To store the RFID in the string UID this loop is used 
  {
    UID.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    UID.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  UID.toUpperCase();
  
  if(UID_prev == UID)                                           // To check whether new UID is found
  {
    return ;
  }
  Serial.print(F("Card UID:"));  
  Serial.println(UID);
  UID_prev = UID;

  Serial.println(Firebase.pushString(firebaseData, "/Doctor", UID)); // Push Data to Firebase
}
