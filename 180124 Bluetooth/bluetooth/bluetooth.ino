int bluetoothLedPin = 6; 
int laserOutputPin = 13;
int state = 0;
int flag = 0; 

int laserPin = 9;
int laserDetect = 0;

int trigPin = 11;
int echoPin = 2;
int ultraled = 10;
 
void setup() {
 pinMode(ultraled, OUTPUT);
 pinMode (laserPin, INPUT);
  pinMode(bluetoothLedPin, OUTPUT);
  
 digitalWrite(bluetoothLedPin, HIGH);
 digitalWrite(laserOutputPin, LOW);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
 
 Serial.begin(9600); // Default connection rate for my BT module
}
 
void loop() {

  //Ultrasoinc part

  long duration, distance;
    digitalWrite(trigPin,HIGH);
    delayMicroseconds(1000);
    digitalWrite(trigPin, LOW);
    duration=pulseIn(echoPin, HIGH);
    distance =(duration/2)/29.1;
    Serial.print(distance);
    Serial.println("CM");
    delay(10);
   
   if((distance<=80)) 
   {
      digitalWrite(ultraled, LOW);
   }
     else if(distance>80)
   {
       digitalWrite(ultraled, HIGH);
   }



//Laser part 

 laserDetect =  digitalRead(laserPin); 

 if (laserDetect == LOW) {
 digitalWrite(laserOutputPin, HIGH);
 }
 else if (laserDetect == HIGH) {
 digitalWrite(laserOutputPin, LOW);
 }


 

//Bluetooth part

 if(Serial.available() > 0){
 state = Serial.read();
 flag=0;
 }

 if (state == '0') {
 digitalWrite(bluetoothLedPin, LOW);
 if(flag == 0){
 Serial.println("LED: off");
 flag = 1;
 }
 }

 else if (state == '1') {
 digitalWrite(bluetoothLedPin, HIGH);
 if(flag == 0){
 Serial.println("LED: on");
 flag = 1;
 }
 }



 
}
