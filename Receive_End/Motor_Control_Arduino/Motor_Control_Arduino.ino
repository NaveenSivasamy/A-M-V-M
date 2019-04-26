#define DELAY 2000

void setup()
{
  //setting the baud rate for serial communication
  Serial.begin(9600);
  //defining the pins which control the motors as output
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
}

void loop()
{
  int8_t Med[6],count=0;

  //the following section is to serially read the No of medicines from the NodeMCU and store it in Med[6] array
  if(Serial.available())
  {
  Serial.read();
  while(count<6)
  {
    Med[count] = Serial.read();
    count++;
  }
  }
  else
  {
    return;    
  }

  //the following section is operate the motors attached to medicine carrying springs to output required amount of medicine
  while(Med[0] > 0)
  {
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    delay(DELAY);
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    Med[0] = Med[0]-5;
  }

  while(Med[1] > 0)
  {
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
    delay(DELAY);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    Med[1] = Med[1]-5;
  }

  while(Med[2] > 0)
  {
    digitalWrite(6, HIGH);
    digitalWrite(7, LOW);
    delay(DELAY);
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
    Med[2] = Med[2]-5;
  }

  while(Med[3] > 0)
  {
    digitalWrite(8, HIGH);
    digitalWrite(9, LOW);
    delay(DELAY);
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
    Med[3] = Med[3]-5;
  }

  while(Med[4] > 0)
  {
    digitalWrite(10, HIGH);
    digitalWrite(11, LOW);
    delay(DELAY);
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    Med[4] = Med[4]-5;
  }

  while(Med[5] > 0)
  {
    digitalWrite(12, HIGH);
    digitalWrite(13, LOW);
    delay(DELAY);
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);
    Med[5] = Med[5]-5;
  }
}
