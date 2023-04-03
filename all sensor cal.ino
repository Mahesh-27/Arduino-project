#include <Wire.h> 
#include <LiquidCrystal.h>

int red = 0;  
int green = 0;  
int blue = 0;  
int sensorValue_mq9 = analogRead(A0); 
int sensorValue_mq135 = analogRead(A1); 
int turbiditypin = A2;
int tempPin = A3;
const int s0=6,s1=7,s2=8,s3=9,out=10;
const int rs = 12, en = 11, d4 = 2, d5 = 3, d6 = 4, d7 = 5;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

float volt;
float ntu; 
int val;

float round_to_dp( float in_value, int decimal_place )
{
  float multiplier = powf( 10.0f, decimal_place );
  in_value = roundf( in_value * multiplier ) / multiplier;
  return in_value;
}

void air_quality()
{
float sensor_volt_mq9,sensor_volt_mq135; 
 float RS_gas_mq9,RS_gas_mq135; 
 float ratio_mq9,ratio_mq135;
 float R0_mq9 = -0.10,R0_mq135 = -0.09; //need to calibrate mq9 and mq135 to know R0
 
 int sensorValue_mq9 = analogRead(A0); 
 int sensorValue_mq135 = analogRead(A1); 

 sensor_volt_mq9 = ((float)sensorValue_mq9 / 1024) * 5.0; 
RS_gas_mq9 = (10.0 - sensor_volt_mq9) / sensor_volt_mq9; // Depend on RL on yor module 
 ratio_mq9 = RS_gas_mq9 / R0_mq9; // ratio = RS/R0 

 sensor_volt_mq135 = ((float)sensorValue_mq135 / 1024) * 5.0; 
RS_gas_mq135 = (10.0 - sensor_volt_mq135) / sensor_volt_mq135; // Depend on RL on yor module 
 ratio_mq135 = RS_gas_mq135 / R0_mq135; // ratio = RS/R0 
//------------------------------------------------------------/ 
 
 Serial.print("sensor_volt_mq9 = "); 
 Serial.println(sensor_volt_mq9); 
 Serial.print("RS_ratio_mq9 = "); 
 Serial.println(RS_gas_mq9); 
 Serial.print("Rs/R0 = "); 
 Serial.println(ratio_mq9); 
 Serial.print("\n\n"); 
 delay(1000); 
 Serial.print("sensor_volt_mq135 = "); 
 Serial.println(sensor_volt_mq135); 
 Serial.print("RS_ratio_mq135 = "); 
 Serial.println(RS_gas_mq135); 
 Serial.print("Rs/R0 = "); 
 Serial.println(ratio_mq135); 
 Serial.print("\n\n"); 
 delay(1000); 
   lcd.setCursor(0,0); 
   lcd.print("MQ9: ");
   lcd.print(ratio_mq9);
   lcd.setCursor(0,1); 
   lcd.print("MQ135: ");
   lcd.print(ratio_mq135);
   delay(2000);
   lcd.clear();

  
  }

void color()
{
  digitalWrite(s2, LOW);  
  digitalWrite(s3, LOW);    //s0=6,s1=7,s2=8,s3=9,out=10;
  red = pulseIn(out,LOW);
  delay(200);  
  digitalWrite(s2, LOW);  
  digitalWrite(s3, HIGH);  
  blue = pulseIn(out,LOW); 
  delay(200);
  digitalWrite(s2, HIGH); 
  digitalWrite(s3, HIGH);    
  green = pulseIn(out,LOW);    
  delay(200);
    lcd.setCursor(0,0); 
    lcd.print("Red: ");
    lcd.print((int)red);
    delay(1500);
    lcd.setCursor(0,0); 
    lcd.print("Blue: ");
    lcd.print((int)blue);
    delay(1500);
    lcd.setCursor(0,0); 
    lcd.print("Green: ");
    lcd.print((int)green);
    
  Serial.println(" Red ");
  Serial.println(red);
  Serial.println(" Blue");
  Serial.println(blue);
  Serial.println(" Green");
  Serial.println(green);
  delay(1500);

  
  }

void turbidity()
{
  volt = 0;
 for(int i=0; i<800; i++)
    {
        volt += ((float)analogRead(turbiditypin)/1023)*5;
    }
    volt = volt/800;
    volt = round_to_dp(volt,2);
    ntu = -1120.4*square(volt)+5742.3*volt-4353.8; 
   

    lcd.setCursor(0,0); 
    lcd.print("Turbidity: ");
    lcd.print(ntu);
    
    Serial.println("Voltage Value =");
    Serial.print(volt);
    Serial.println("  V");
    delay(2000);
    Serial.println("Turbidity Value =");
    Serial.print(ntu);
    Serial.println("  NTU");
    delay(1000);
    lcd.clear();
  }
void temp()
{
  
val = analogRead(tempPin);
float mv = ( val/1023.0)*5000.0;
float cel = mv/40;
float farh = (cel*9)/5 + 32;

   lcd.setCursor(0,0); 
   lcd.print("Temp (*c): ");
   lcd.print(cel);

   
Serial.print("TEMPRATURE = ");
Serial.print(cel);
Serial.print("*C");
Serial.println();
delay(1000);
Serial.print("TEMPRATURE = ");
Serial.print(farh);
Serial.print("*F");
Serial.println();
lcd.clear();
 }


void setup()   
{ 
    
  pinMode(s0, OUTPUT);   //s0 
  pinMode(s1, OUTPUT);   //s1
  pinMode(s2, OUTPUT);  //s2
  pinMode(s3, OUTPUT);  //s3
  pinMode(out, INPUT);  //out
  lcd.begin(16, 2);
  lcd.clear();
  digitalWrite(s0, HIGH);  
  digitalWrite(s1, LOW); 

  Serial.begin(9600); 
}  

    
void loop() 
{  
    air_quality();
    delay(1000);

    color();
    delay(1000);

    turbidity();
     delay(1000);
     
    temp();
    delay(1500);
 }  
