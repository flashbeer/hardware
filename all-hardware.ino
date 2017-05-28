//Code made with many basic examples of LiquidCrystal, FlowSensor and Data Bluetooth.
//Flash Beer, Startup idea
//Made in AngelHack 2010
//Director of harware engineering: Karolina Ladino @KaroLadinop
//Director of mechanical engineering: Santiago Aljure @SantiagoAljureO

// Libraries
#include <LiquidCrystal.h> // LCD
#include <Wire.h> // Sensor
 
// Inicialing variables
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
unsigned char i; // LCD
char blueToothVal; // Blue
char lastValue; // Blue
volatile int NbTopsFan; //Measuring the rising edges of the signal
int Calc; 
int hallsensor = 12; //The pin location of the sensor: D12

//Fuction of interrupt calls
void rpm () //Interrupt calls

//Function of sensor
{ 
  NbTopsFan++;  // Signal
} 

// Setup
void setup()
{
lcd.begin(16, 2); // LCD
pinMode(hallsensor, INPUT);
Serial.begin(9600); //Blue 
pinMode(11,OUTPUT); //Output valve
attachInterrupt(0, rpm, RISING); //Interrupt
}

// Loop
void loop()
{
  NbTopsFan = 0; // NbTops to 0 
  sei(); // Enables interrupts
  delay (200); // Wait 200 mili second
  cli(); // Disable interrupts
  Calc = (NbTopsFan * 60 / 7.5); // (Pulse frequency x 60) / 7.5Q, = flow rate in L/hour
  Serial.print (Calc, DEC); // Prints the number calculated above

  if(Serial.available()) // Blue available
  {
    blueToothVal = Serial.read(); // Read 
    Serial.println(blueToothVal); // Print
  }
  if (blueToothVal=='1')
  {
    digitalWrite(11,HIGH); // On valve
    if (lastValue!='1')
    Serial.println(F("Valvue is on")); // Print info
    lastValue=blueToothVal;

    lcd.setCursor(i, 0); // Set the cursor
    lcd.print("Pouring..."); // Print a message LCD
    delay(200); // 200 delay
    lcd.clear(); // Clear  
  }
  else if (blueToothVal=='0')
  {
    digitalWrite(11,LOW); // Off valve
    if (lastValue!='0')
      Serial.println(F("Valvue is off")); // Print info
    lastValue=blueToothVal;
    
    lcd.setCursor(i, 1); // Set the cursor
    lcd.print("14 L left...");  // Print a message  LCD
    delay(200); // 200ms delay
    lcd.clear(); // Clear  
  }
}
