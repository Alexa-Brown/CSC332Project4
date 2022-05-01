/*
 * Ryan Phadnis and Alexa Brown
 * Project 4 -- CSC 332 
 * Dr. Paul Pauca -- Wake Forest University
 * April/May 2022
 */


const int ldrPin = A2;
const int ledPin = 13;
const int buzzerPin = 12;
const int rightClick = 8;
const int leftClick = 9;
;


void setup() 
{
  Serial.begin(9600);
  pinMode(leftClick,INPUT);    
  pinMode(rightClick,INPUT);
  pinMode(ldrPin, INPUT); //light sensor
  pinMode(ledPin,OUTPUT); //LED
  pinMode(buzzerPin, OUTPUT);
  digitalWrite(leftClick,HIGH);
  digitalWrite(rightClick,HIGH);
  digitalWrite(ledPin,LOW);
  digitalWrite(buzzerPin,LOW);

}

void loop() {
  int ldrStatus = analogRead(ldrPin);
  int bright = 100;
  int prev_bright = 1000;
  int prev_state=0;   // previous state of switch
  int prev_state_right=0;
  int z=0,xpos=0,ypos=0,f=0;
  int x=analogRead(A0);
  int y=analogRead(A1);


  if (ldrStatus <= 400)
  {
    prev_bright = bright;
    bright = 10;
    digitalWrite(ledPin, HIGH);
   // digitalWrite(buzzerPin, HIGH);     //can uncomment this code to allow the buzzer to buzz when the room light changes



  }
  if(ldrStatus > 400)
  {
    prev_bright = bright;
    bright = 100;
    digitalWrite(ledPin, LOW);
   // digitalWrite(buzzerPin, LOW);     //can uncomment this code to allow the buzzer to buzz when the room light changes

  }
    


  int sensitivity= 12;    // you can adjust the sensitivity based on your comfort
  if(x>=550)                     // when moved up 
    xpos=map(x,550,1023,0,sensitivity); 
  if(x<=450)                   // when moved down
    xpos=map(x,450,0,0,-sensitivity);   
  if(y>=550)                    // when moved right
    ypos=map(y,550,1023,0,sensitivity);  
  if(y<=450)                  // when moved left
    ypos=map(y,450,0,0,-sensitivity); 
  
  int curr_state=digitalRead(9);
  int curr_state_right = digitalRead(8);
  if(curr_state==1 && prev_state==0)   // when SW is pressed 
    z=1;
  else
    z=0;

  if (curr_state_right==1 && prev_state_right==0)
    f=1;
  else
    f=0;

 
  if(xpos!=0 or ypos!=0 or z==1 or f==1 or bright != prev_bright or bright == 50) // prints only when the joystick is moved or when room light changes 
  {
    Serial.print(ypos);    // print the data and separating by ":"
    Serial.print(":");
    Serial.print(xpos);
    Serial.print(":");
    Serial.print(z);
    Serial.print(":");
    Serial.print(f);
    Serial.print(":");
    Serial.println(bright);
    Serial.flush();

  }
  prev_state=curr_state;
  prev_state_right=curr_state_right;
  
  delay(10);         // for normal operation
}
