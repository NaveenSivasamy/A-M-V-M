
#include <SPI.h>
#include <MFRC522.h>
#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>

#define RST_PIN         D3                                         // Configurable, see typical pin layout above
#define SS_PIN          D4                                        // Configurable, see typical pin layout above
#define FIREBASE_HOST "vendor-d7e9b.firebaseio.com"
#define FIREBASE_AUTH "sThPXEnVlOE5zmPCEphGKGgCHnw6XFtLGxtBUb8V"
#define WIFI_SSID "Xperia"
#define WIFI_PASSWORD "qwerty12345"

MFRC522 mfrc522(SS_PIN, RST_PIN);                                 // Create MFRC522 instance
FirebaseData firebaseData;
String UID_prev;

void setup()
{

  //Serial.begin(9600);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
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

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

  SPI.begin();                                                    // Initialise SPI bus
  mfrc522.PCD_Init();                                             // Initialise MFRC522
  mfrc522.PCD_DumpVersionToSerial();                              // Show details of PCD - MFRC522 Card Reader details
  Serial.println("Scan PICC to see UID, SAK, type, and data blocks...");  
}

void sendDataSerial(String data)
 {

    int len=data.length()+1;
     char buf[len];
     data.toCharArray(buf, len) ;
     Serial.write(buf);

 }

 
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
  char buffer[100];
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
  Serial.print(("Card UID:"));  
  Serial.println(UID);
  UID_prev = UID;
  int8_t  count = 1,Med[6];
  Serial.begin(9600);
  sprintf(buffer,"/Patient/%s/Medicine_%d",UID.c_str(),count);
  if(Firebase.getString(firebaseData,buffer))
   {
    Med[count-1] = firebaseData.stringData().toInt();
    Serial.write(Med[count-1]);
   }
   count++;
   sprintf(buffer,"/Patient/%s/Medicine_%d",UID.c_str(),count);

   if(Firebase.getString(firebaseData,buffer))
   {
    Med[count-1] = firebaseData.stringData().toInt();
    Serial.write(Med[count-1]);
   }
   count++;
   sprintf(buffer,"/Patient/%s/Medicine_%d",UID.c_str(),count);

   if(Firebase.getString(firebaseData,buffer))
   {
    Med[count-1] = firebaseData.stringData().toInt();
    Serial.write(Med[count-1]);
   }
   count++;
   sprintf(buffer,"/Patient/%s/Medicine_%d",UID.c_str(),count);

   if(Firebase.getString(firebaseData,buffer))
   {
    Med[count-1] = firebaseData.stringData().toInt();
    Serial.write(Med[count-1]);
   }
   count++;
   sprintf(buffer,"/Patient/%s/Medicine_%d",UID.c_str(),count);

   if(Firebase.getString(firebaseData,buffer))
   {
    Med[count-1] = firebaseData.stringData().toInt();
    Serial.write(Med[count-1]);
   }
   count++;
   sprintf(buffer,"/Patient/%s/Medicine_%d",UID.c_str(),count);

   if(Firebase.getString(firebaseData,buffer))
   {
    Med[count-1] = firebaseData.stringData().toInt();
    Serial.write(Med[count-1]);
   }
}
