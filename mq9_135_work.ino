
void setup() { 
 Serial.begin(9600); 
 
} 
void loop() {  
 float sensor_volt_mq9,sensor_volt_mq135; 
 float RS_gas_mq9,RS_gas_mq135; 
 float ratio_mq9,ratio_mq135;

  
//-Replace the name "R0" with the value of R0 in the demo of First Test -/ 
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
}
