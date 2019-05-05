#include <IRremote.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
static const int RXPin = 6, TXPin =10;
static const uint32_t GPSBaud = 9600;
// The TinyGPS++ object
TinyGPSPlus gps; 
int pulsePin =A0;  
int fadeRate = 0; 
// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);
const int RECV_PIN = 7;
IRrecv irrecv(RECV_PIN);
decode_results results;
const unsigned long v2=0XFF18E7;
const unsigned long v5=0XFF38C7;
const unsigned long v4=0XFF10EF;
const unsigned long v6=0XFF5AA5;
const unsigned long v8=0XFF4AB5;
const unsigned long v7=0XFF42BD;
const unsigned long v0=0XFF6897;
const unsigned long v9=0XFF52AD;
const unsigned long v1=0xFF30CF;
//+++++++++++++++++++++++++++++++++

volatile float BPM;                   // int that holds raw Analog in 0. updated every 2mS
volatile int Signal;                // holds the incoming raw data
volatile int IBI = 600;             // int that holds the time interval between beats! Must be seeded! 
volatile boolean Pulse = false;     // "True" when User's live heartbeat is detected. "False" when not a "live beat". 
volatile boolean QS = false;        // becomes true when Arduoino finds a beat.
static boolean serialVisual = true;   // Set to 'false' by Default.  Re-set to 'true' to see Arduino Serial Monitor ASCII Visual Pulse 
 volatile int rate[10];                      // array to hold last ten IBI values
 volatile unsigned long sampleCounter = 0;          // used to determine pulse timing
 volatile unsigned long lastBeatTime = 0;           // used to find IBI
 volatile int P = 512;                      // used to find peak in pulse wave, seeded
 volatile int T = 512;                     // used to find trough in pulse wave, seeded
 volatile int thresh = 525;                // used to find instant moment of heart beat, seeded
 volatile int amp = 100;                   // used to hold amplitude of pulse waveform, seeded
 volatile boolean firstBeat = true;        // used to seed rate array so we startup with reasonable BPM
 volatile boolean secondBeat = false;      // used to seed rate array so we startup with reasonable BPM
long cm;
long microseconds;
float ar;
int echoPin = 11; // Echo Pin stin11
int trigPin = 12; // Trigger Pin stin 12
//k apostash
float k = 10;
float a;
#define LS  8    // left sensor MATI arduino
#define  RS 9    // right sensor MATI arduino
//x,y joystick
int x;
int y;
int d0;
int d2 = 0;
int d3 = 0;
//kleidomata apo ir
int ka1 = 0;
int kd1 = 0;
int km1 = 0;
int ks1 = 0;
int kp1 = 0;
//kleidoma auto me w=1 exv auto kai allo pathma apo tv (koympi 0)stop auto
int w = 10;
//out se rele
int in1 = 2;
int in2 = 3;
int in3 = 4;
int in4 = 5;
float heart = A0;
float kels = A1;

void setup() {
  // put your setup code here, to run once:
Serial.end();
  
  Serial.begin(9600);
ss.begin(GPSBaud);

// Serial.end();
  irrecv.enableIRIn();
  irrecv.blink13(true);
  pinMode(in1, OUTPUT);//ARDUINO -> RELE   D2
  pinMode(in2, OUTPUT);//                   D3
  pinMode(in3, OUTPUT);//                   D4
  pinMode(in4, OUTPUT);//                   D5
  //            RX                          D6  gps
  //                                        D7  IF
  pinMode(LS, INPUT);// LEFT EYE            D8
  pinMode(RS, INPUT);// RIGHT EYE           D9
 //             TX                          D10 gps
  pinMode(echoPin,INPUT);//                 D11 SONAR ECHO
  pinMode(trigPin,OUTPUT);//                D12 SONAR TRIG
  pinMode(13, OUTPUT);//                    D13 ARDUINO ->RAS 
  pinMode(A0, INPUT);//HEART                A0
  pinMode(A1, INPUT);//CEL H STOP JOYSTICK  A1
  pinMode(A2, INPUT);//X                    A2
  pinMode(A3, INPUT);//Y                    A3
  pinMode(A4, INPUT);//RAS -> ARDUINO       A4
  pinMode(A5, INPUT);//RAS -> ARDUINO       A5
    
//interruptSetup(); 
}

void loop() {
serialOutput();  
    gps.encode(ss.read());

    x=analogRead(A2);//timh portas joystick
    y=analogRead(A3);//timh portas joystick
    d0=analogRead(A1);//timh portas joystick

  a = k;
    if (y>1000){pi_slow();Serial.println("piso");}
    if (y<10){mp_slow();Serial.println("mpros"); }
    if ((x<5)&&(y>500)){st();ar_slow();Serial.println("left");}
    if (x>1000){st();de_slow();Serial.println("right"); }
  if (d0==0){st();}
 
  //st();
  //++
    if (irrecv.decode(&results)){
    Serial.println(results.value, HEX);
    switch(results.value){
    case v1:
    w=0;
    digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
int  duration = pulseIn(echoPin, HIGH);
 long  a = duration/29/2;
   Serial.println(a);
   delay(3000);
    } 
    switch(results.value){
    case v2:
        w=0;
   //   mp_slow();
    if ((km1==0)&&(a>=k)){km1=1;}
    }
    switch(results.value){
    case v5:
    //case 0xFF38C7: //Keypad button "5 ar stop"
    w=0;
    st();
    if (a>=k){st();km1=0;ka1=0;kd1=0;kp1=0;}
    }
    switch(results.value){
      case v6:
      //case 0xFF5AA5: //Keypad button "6 AR   dejia"
    w=0;
    //de_slow();
    if ((kd1==0)&&(a>=k)){kd1=1;}
    }
    switch(results.value){
      case v4:
      //case 0xFF10EF: //Keypad button "4 AR   aristera "
    w=0;
    //ar_slow();
    if ((ka1==0)&&(a>=k)){ka1=1;}
    }
    switch(results.value){
      case v8:
  //    case 0xFF4AB5 : //Keypad button 8 DOYLEYOYN piso
    w=0;
     //pi_slow();
    if ((kp1==0)&&(a>=k)){kp1=1;}
    }
    switch(results.value){
      case v7:
      //case 0xFF42BD : //Keypad button 7 DOYLEYOYN MATIA MONO // auto.............
    w=1;
   //Serial.println(digitalRead(LS));
   //Serial.println(digitalRead(RS));
   // delay(1000);
    }
    switch(results.value){
      case v9:
  
  //  case 0xFF52AD : //Keypad button 9 DOYLEYOYN uermokrasia hxo kardias................................................
    //kai enalages d9 d8 gia to test koposeos  sto sum1 sum2
    //Serial.begin(9600);
st();
    w=3;
    int  s2=analogRead(kels);
    float milliVolts = (s2/1024.0)*5000;
    float cel = milliVolts / 10;
    Serial.println("TEMPORARY  BODY");
    Serial.println(cel);
delay(2000);
   }
    switch(results.value){
      case v0:
  //  case 0xFF6897 : //Keypad button 0 DOYLEYOYN gps 
//Serial.end();
  //  Serial.begin(9600);
//  ss.begin(GPSBaud);
st();
//    gps.encode(ss.read());
//delay(5000);
for(int i=1;i<5;i++){
    if (gps.location.isUpdated()){
      Serial.print("Latitude= "); 
      Serial.print(gps.location.lat(), 6);
      Serial.print(" Longitude= "); 
      Serial.println(gps.location.lng(), 6);
   }
   delay(1000);
}
    w=0;
    //st();
    Serial.println("SET  Ο FROM  TV");
delay(1000);
    }

    irrecv.resume();
    {
   //sensor();
    if ((w==0)&&(a>=k)&&(km1==1)){mp_slow();ka1=0;kd1=0;kp1=0;}
    if ((w==0)&&(a>=k)&&(ka1==1)){ar_slow();km1=0;kd1=0;kp1=0;}
    if ((w==0)&&(a>=k)&&(kd1==1)){de_slow();ka1=0;km1=0;kp1=0;}
    if ((w==0)&&(a>=k)&&(kp1==1)){pi_slow();ka1=0;kd1=0;km1=0;}

    }//end resume
    }//end inf
if((w==1)&&(digitalRead(LS)==0) && (digitalRead(RS)==0)&&(a>=k)){
    Serial.println("go AUTO LEFT");
    ar_slow(); 
    delay(500);
   // ka1=1;
    }
    if((w==1)&&(digitalRead(LS)==1) && (digitalRead(RS)==1)&&(a>=k)){
    Serial.println("go AUTO RIGHT");
    de_slow(); 
    delay(500);
    //kd1=1;
    }
    if((w==1)&&(digitalRead(LS)==0) && (digitalRead(RS)==1)&&(a>=k)){
    Serial.println("go AUTO  FWD");
    mp_slow();
    delay(500);
    //km1=1;
    }

if(w==3){   

  Signal = analogRead(pulsePin);              // read the Pulse Sensor 
  sampleCounter += 2;                         // keep track of the time in mS with this variable
  int N = sampleCounter - lastBeatTime;       // monitor the time since the last beat to avoid noise
                                              //  find the peak and trough of the pulse wave
  if(Signal < thresh && N > (IBI/5)*3) // avoid dichrotic noise by waiting 3/5 of last IBI
    {      
      if (Signal < T) // T is the trough
      {                        
        T = Signal; // keep track of lowest point in pulse wave 
      }
    }

  if(Signal > thresh && Signal > P)
    {          // thresh condition helps avoid noise
      P = Signal;                             // P is the peak
    }                                        // keep track of highest point in pulse wave

  //  NOW IT'S TIME TO LOOK FOR THE HEART BEAT
  // signal surges up in value every time there is a pulse
  if (N > 250)
  {                                   // avoid high frequency noise
    if ( (Signal > thresh) && (Pulse == false) && (N > (IBI/5)*3) )
      {        
        Pulse = true;                               // set the Pulse flag when we think there is a pulse
      //  digitalWrite(blinkPin,HIGH);                // turn on pin 13 LED
        IBI = sampleCounter - lastBeatTime;         // measure time between beats in mS
        lastBeatTime = sampleCounter;               // keep track of time for next pulse
  
        if(secondBeat)
        {                        // if this is the second beat, if secondBeat == TRUE
          secondBeat = false;                  // clear secondBeat flag
          for(int i=0; i<=9; i++) // seed the running total to get a realisitic BPM at startup
          {             
            rate[i] = IBI;                      
          }
        }
  
        if(firstBeat) // if it's the first time we found a beat, if firstBeat == TRUE
        {                         
          firstBeat = false;                   // clear firstBeat flag
          secondBeat = true;                   // set the second beat flag
          sei();                               // enable interrupts again
          return;                              // IBI value is unreliable so discard it
        }   
      // keep a running total of the last 10 IBI values
      word runningTotal = 0;                  // clear the runningTotal variable    

      for(int i=0; i<=8; i++)
        {                // shift data in the rate array
          rate[i] = rate[i+1];                  // and drop the oldest IBI value 
          runningTotal += rate[i];              // add up the 9 oldest IBI values
        }

      rate[9] = IBI;                          // add the latest IBI to the rate array
      runningTotal += rate[9];                // add the latest IBI to runningTotal
      runningTotal /= 10;                     // average the last 10 IBI values 
      BPM = 60000/runningTotal;               // how many beats can fit into a minute? that's BPM!
      QS = true;                              // set Quantified Self flag 
      // QS FLAG IS NOT CLEARED INSIDE THIS ISR
    }                       
  }

  if (Signal < thresh && Pulse == true)
    {   // when the values are going down, the beat is over
      //digitalWrite(blinkPin,LOW);            // turn off pin 13 LED
      Pulse = false;                         // reset the Pulse flag so we can do it again
      amp = P - T;                           // get amplitude of the pulse wave
      thresh = amp/2 + T;                    // set thresh at 50% of the amplitude
      P = thresh;                            // reset these for next time
      T = thresh;
    }

  if (N > 2500)
    {                           // if 2.5 seconds go by without a beat
      thresh = 512;                          // set thresh default
      P = 512;                               // set P default
      T = 512;                               // set T default
      lastBeatTime = sampleCounter;          // bring the lastBeatTime up to date        
      firstBeat = true;                      // set these to avoid noise
      secondBeat = false;                    // when we get the heartbeat back
    }



  if (QS == true) // A Heartbeat Was Found
    {     
      // BPM and IBI have been Determined
      // Quantified Self "QS" true when arduino finds a heartbeat
      fadeRate = 255; // Makes the LED Fade Effect Happen, Set 'fadeRate' Variable to 255 to fade LED with pulse
  Happens(); // A Beat Happened, Output that to serial.     
      
     
      
      QS = false; // reset the Quantified Self flag for next time    
    }
     
  //ledFadeToBeat(); // Makes the LED Fade Effect Happen 
  delay(20); //  take a break
}




}//end loop

//moter all stop
void st(){//delay(27);
  digitalWrite(in1, LOW); analogWrite(in2, LOW); analogWrite(in3, LOW); analogWrite(in4, LOW); Serial.println("moter stop");
  //void st() {digitalWrite(in1,L);analogWrite(in2,L);analogWrite(in3,L);analogWrite(in4,L);
}
//Serial.println("moter stop");
//moter aristero argo
void ar_slow() {delay(40);
  digitalWrite(in1, HIGH); digitalWrite(in2, LOW); digitalWrite(in3, LOW); digitalWrite(in4, HIGH);Serial.println("moter GO LEFT");
}
//Serial.println("moter   ++");
//moter deji argo
void de_slow() {delay(27);
  digitalWrite(in1, LOW); digitalWrite(in2, HIGH); digitalWrite(in3, HIGH); digitalWrite(in4, LOW); Serial.println("moter GO RIGHT ");
}
// Serial.println("moter --");
//mros arga
void mp_slow() {delay(27);
//  digitalWrite(in1, LOW); digitalWrite(in2, HIGH); digitalWrite(in3, LOW); digitalWrite(in4, HIGH); //Serial.println("moter FWD");
digitalWrite(in1, HIGH); digitalWrite(in2, LOW); digitalWrite(in3, HIGH); digitalWrite(in4, LOW);Serial.println("moter FWD");
}
//Serial.println("moter -+");
//piso arga
void pi_slow() {delay(27);
  //digitalWrite(in1, HIGH); digitalWrite(in2, LOW); digitalWrite(in3, HIGH); digitalWrite(in4, LOW); //Serial.println("moter BACK");
 digitalWrite(in1, LOW); digitalWrite(in2, HIGH); digitalWrite(in3, LOW); digitalWrite(in4, HIGH);Serial.println("moter BACK");
}


//Serial.println("moter +-");
void serialOutput()
{   // Decide How To Output Serial. 
 if (serialVisual == true)
  {  
     arduinoSerialMonitorVisual('-', Signal);   // goes to function that makes Serial Monitor Visualizer
  } 
 else
  {
   //   sendDataToSerial('S', Signal);     // goes to sendDataToSerial function
   }        
}


void Happens()
{    
 if (serialVisual == true) //  Code to Make the Serial Monitor Visualizer Work
   {            
    Serial.print("*** Heart-Beat Happened *** ");  //ASCII Art Madness
     Serial.print("BPM: ");
     Serial.println(BPM);
    // lcd.clear();
    // lcd.print("BPM: ");
    // lcd.print(BPM);
   }
 else
   {
   sendDataToSerial('B',BPM);   // send heart rate with a 'B' prefix
   sendDataToSerial('Q',IBI);   // send time between beats with a 'Q' prefix
   }   
}

void arduinoSerialMonitorVisual(char symbol, int data )
{    
  const int sensorMin = 0;      // sensor minimum, discovered through experiment
  const int sensorMax = 1024;    // sensor maximum, discovered through experiment
  int sensorReading = data; // map the sensor range to a range of 12 options:
  int range = map(sensorReading, sensorMin, sensorMax, 0, 11);
  // do something different depending on the 
  // range value:
  //delay(100);
   switch (range) 
  {
    case 0:     
      Serial.println("");     /////ASCII Art Madness
      break;
    case 1:   
      Serial.println("---");
      break;
    case 2:    
      Serial.println("------");
      break;
    case 3:    
      Serial.println("---------");
      break;
    case 4:   
      Serial.println("------------");
      break;
    case 5:   
      Serial.println("--------------|-");
      break;
    case 6:   
      Serial.println("--------------|---");
      break;
    case 7:   
      Serial.println("--------------|-------");
      break;
    case 8:  
      Serial.println("--------------|----------");
      break;
    case 9:    
      Serial.println("--------------|----------------");
      break;
    case 10:   
      Serial.println("--------------|-------------------");
      break;
    case 11:   
      Serial.println("--------------|-----------------------");
      break;
  } 
  
}

void sendDataToSerial(char symbol, int data )
{
   Serial.print(symbol);
 Serial.print(data);                
}

