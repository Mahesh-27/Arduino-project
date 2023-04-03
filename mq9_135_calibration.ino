/* 
MQ9 Calibration 
modified on 19 Feb 2019 
by Saeed Hosseini 
https://electropeak.com/learn/ 
*/ 
void setup() { 
 Serial.begin(9600); 
} 
void loop() { 
 float sensor_volt_mq9,sensor_volt_mq135;  
 float RS_air_mq9,RS_air_mq135; //  Rs in clean air 
 float R0_mq9,R0_mq135;  // R0 in 1000 ppm LPG 
 float sensorValue_mq9,sensorValue_mq135; 
//Average   
   for(int x = 0 ; x < 100 ; x++) 
 { 
   sensorValue_mq9 = sensorValue_mq9 + analogRead(A0); 
   sensorValue_mq135 = sensorValue_mq135 + analogRead(A1); 
 } 
 sensorValue_mq9 = sensorValue_mq9/100.0; 
 sensorValue_mq135 = sensorValue_mq135/100.0; 
//-----------------------------------------------/ 
 sensor_volt_mq9 = (sensorValue_mq9/1024)*5.0;
 sensor_volt_mq135 = (sensorValue_mq135/1024)*5.0;
  
 RS_air_mq9 = (10.0-sensor_volt_mq9)/sensor_volt_mq9; // Depend on RL on yor module 
 R0_mq9 = RS_air_mq9/9.9; // According to MQ9 datasheet table 

  
 RS_air_mq135 = (10.0-sensor_volt_mq135)/sensor_volt_mq135; // Depend on RL on yor module 
 R0_mq135 = RS_air_mq135/9.9; // According to MQ9 datasheet table 
 
 
 Serial.print("sensor_volt_mq9 = "); 
 Serial.print(sensor_volt_mq9); 
 Serial.println("V");
 Serial.print("R0 = "); 
 Serial.println(R0_mq9); 
 delay(1000); 
  
 Serial.print("sensor_volt_mq135 = "); 
 Serial.print(sensor_volt_mq135); 
 Serial.println("V");
 Serial.print("R0 = "); 
 Serial.println(R0_mq135); 
 delay(1000); 

}
