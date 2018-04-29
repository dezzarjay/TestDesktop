/*
  Blink - HI

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Blink
*/

#define MYLED 12
int sensorPin = A0;
int sensorValue = 0;

int mode=0;         //as per above
int phase=0;        //0=ready,1=running
int oldstate=0;     //to detect changes
int threshold=170;  //starting default threshold

unsigned long t;    //for keeping track of running time.

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(MYLED, OUTPUT);
  
  Serial.begin(9600);
  
}

// the loop function runs over and over again forever
void loop() {

  int state;
  unsigned long tt; 
  
  //digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  //digitalWrite(MYLED, LOW);     
  //delay(500);                       // wait for a second
  //digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(MYLED, HIGH);    // turn the LED off by making the voltage LOW
 // delay(500);                       // wait for a second

  sensorValue = analogRead(sensorPin);
  //Serial.println(sensorValue);

  tt=millis();
  if(sensorValue<threshold){
    state=0; //start or stop signal
  }else{
    state=1;
  }

  Serial.print(state);
  Serial.print(" ");
  Serial.print(phase);
  Serial.print(" ");
  Serial.print(tt);
  Serial.print(" ");
  Serial.print(0);  // To freeze the lower limit
  Serial.print(" ");
  Serial.print(1000);  // To freeze the upper limit
  Serial.print(" ");
  Serial.println(sensorValue);  // To send all three 'data' points to the plotter
  
  switch(mode){     //test for different conditions
    case 0:
      if((!state)&&(oldstate)&&(phase==0)){phase=1;t=tt;state=1;delay(5);}                     //start on beam break
      if((!state)&&(oldstate)&&(phase==1)){phase=0;showtime(tt-t);t=tt;}      //lap done on beam break
      break;
    case 1:
      if((!state)&&(oldstate)&&(phase==0)){phase=1;t=tt;}                     //start on beam break
      if((state)&&(!oldstate)&&(phase==1)){phase=0;showtime(tt-t);t=tt;}      //lap done on beam make
      break;
    case 2:
      if((state)&&(!oldstate)&&(phase==0)){phase=1;t=tt;}                     //start on beam make
      if((!state)&&(oldstate)&&(phase==1)){phase=0;showtime(tt-t);t=tt;}      //lap done on beam break
      break;
  }
  oldstate=state;   //record old state for next cycle

  

  //showtime(1001);
  delay(10); 
}

void showtime(unsigned long mm){     //take time in ms and show as hh:mm:ss.sss
  unsigned long h,m,s,ss;
  s=mm/1000;
  m=s/60;
  h=m/60;
  //mm=mm%1000;
  s=s%60;
  m=m%60;
  h=h%100;

  Serial.print(mm);
  Serial.print(" ");
  delay(3000);
  /*Serial.print(h/10+'0');
  Serial.print(h%10+'0');
  Serial.print(':');
  Serial.print(m/10+'0');
  Serial.print(m%10+'0');
  Serial.print(':');
  Serial.print(s/10+'0');
  Serial.print(s%10+'0');
  Serial.print('.');
  Serial.print(mm/100+'0');
  Serial.print((mm/10)%10+'0');
  Serial.print(mm%10+'0');
  //lcd.setCursor(0,1);     //move cursor to be ready for number */
}

