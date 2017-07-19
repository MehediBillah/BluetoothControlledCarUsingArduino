
#include <SoftwareSerial.h>
SoftwareSerial mySerial(12, 13); // RX, TX

#define ARC 90


#define trigPinL 32
#define echoPinL 33
int motor_L_E = 5;
int motor_L_C1 = 6;
int motor_L_C2 = 7;

int motor_R_E = 8;
int motor_R_C1 = 9;
int motor_R_C2 = 10;
int Buzzer=36;
int ledPin=50;
int ledPin2=42;
int flag=0;
int count=0;

void forward();
void stops();
void right();
void left();
void backword();
long distance(int trigPin, int echoPin);
//void speeds();




//int sL, sR, L, R, M, uL, uR;
//long l,c,r;
//int count = 0;

int MAX=225;


void setup()
{
    // put your setup code here, to run once:
    Serial.begin(9600);
    
    pinMode(ledPin, OUTPUT);
    pinMode(ledPin2, OUTPUT);
	
  


 Serial.println("Goodnight moon!");
  mySerial.begin(9600);

  // set the data rate for the SoftwareSerial port
  //mySerial.println("Hello, world?");


    pinMode(motor_L_E, OUTPUT);
    pinMode(motor_L_C1, OUTPUT);
    pinMode(motor_L_C2, OUTPUT);

    pinMode(motor_R_E, OUTPUT);
    pinMode(motor_R_C1, OUTPUT);
    pinMode(motor_R_C2, OUTPUT);
     pinMode(trigPinL,OUTPUT);
     pinMode(echoPinL,INPUT);
    pinMode(Buzzer, OUTPUT);
    



}







void loop()
{



char a;

  if (mySerial.available())
  {  
Serial.print(a=mySerial.read());

	if(a=='A'){
		forward();
          count++;
             
 
        }
        
        if(a=='C'){
		left();
                
        }
        
        if(a=='D'){
		right();
          
        }
        
        if(a=='B'){
                backword();
        }
        if(a=='E'){
                stops();
                count--;
        }
        
        if(a=='F'){
                digitalWrite(Buzzer,HIGH);
                    
                       
                       delay(1000);
                      
                        digitalWrite(Buzzer,LOW);
        }
        if(a=='G')
       {
         while(1)
         {
             forward();
             int t=distance(trigPinL, echoPinL);
             if(t<70){
               digitalWrite(Buzzer,HIGH);
             }
             if(t>80){
               digitalWrite(Buzzer,LOW);
             }
             if(t<50)
             {
                  Serial.print(t);
                  //digitalWrite(Buzzer,HIGH);
                  digitalWrite(ledPin, HIGH); 
                   stops();
                  //backword();
                  for(int i=0;i<10;i++){
                      delay(100);
                      if(mySerial.available())
                      break;
                  }
    
                  digitalWrite(Buzzer,LOW);
                  digitalWrite(ledPin, LOW); 
                  right();
                  delay(500);
             }
             if(mySerial.available())
             break;
       
         }
       }
    
  if (Serial.available())
    mySerial.write(Serial.read());
    
    while(flag==1){
       digitalWrite(ledPin, HIGH); 
       if(mySerial.available())
         break;
       }
    digitalWrite(ledPin, LOW);
    
    if(count==2){
      digitalWrite(ledPin2, HIGH);
    }
    if(count==1){
            digitalWrite(ledPin2, LOW);
    }
}


                  
               


    

     
}

//--------------------------Function Definations-------------------------//

void forward()
{
    flag=0;
    analogWrite(motor_L_E,MAX);
    digitalWrite(motor_L_C1,HIGH);
    digitalWrite(motor_L_C2,LOW);

    analogWrite(motor_R_E,MAX);
    digitalWrite(motor_R_C1,HIGH);
    digitalWrite(motor_R_C2,LOW);
    
}

void left()
{
    flag=0;
    analogWrite(motor_L_E,ARC);
    digitalWrite(motor_L_C1,HIGH);
    digitalWrite(motor_L_C2,LOW);

    analogWrite(motor_R_E,MAX);
    digitalWrite(motor_R_C1,HIGH);
    digitalWrite(motor_R_C2,LOW);
}

void right()
{
    flag=0;
    analogWrite(motor_L_E,MAX);
    digitalWrite(motor_L_C1,HIGH);
    digitalWrite(motor_L_C2,LOW);

    analogWrite(motor_R_E,ARC);
    digitalWrite(motor_R_C1,HIGH);
    digitalWrite(motor_R_C2,LOW);
}

void backword()
{
    flag=1;
    analogWrite(motor_L_E,MAX);
    digitalWrite(motor_L_C1,LOW);
    digitalWrite(motor_L_C2,HIGH);

    analogWrite(motor_R_E,MAX);
    digitalWrite(motor_R_C1,LOW);
    digitalWrite(motor_R_C2,HIGH);
}

void stops()
{
   
    flag=1;
    
    
    flag=0;
    analogWrite(motor_L_E,MAX);
    digitalWrite(motor_L_C1,LOW);
    digitalWrite(motor_L_C2,LOW);

    analogWrite(motor_R_E,MAX);
    digitalWrite(motor_R_C1,LOW);
    digitalWrite(motor_R_C2,LOW);
    
    
    for(int i=0;i<15;i++){
    delay(100);
    if(mySerial.available())
    break;
    }
    
}

long distance(int trigPin, int echoPin) //find distance upto 50cm
{
    long duration;
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2); // init
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10); // 10us pulse, then off
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH,7000); //max timeout for 51cm
    if (duration==0)duration=6000; //change 0, if timeout reached

    return  (duration/58.224); // in CM T(us)/(2*29.1)
}


