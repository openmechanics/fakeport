volatile boolean TurnDetected;  // need volatile for Interrupts
volatile boolean up;

const int PinCLK=2;   // Generating interrupts using CLK signal
const int PinDT=3;    // Reading DT signal
const int PinSW=4;    // Reading Push Button switch

// L9110 connections
#define L9110_B_IA 10 // Pin D10 --> Motor B Input A
#define L9110_B_IB 11 // Pin D11 --> Motor B Input B
 
// Motor Speed & Direction
#define MOTOR_B_PWM L9110_B_IA // Motor PWM Speed
#define MOTOR_B_DIR L9110_B_IB // Motor Direction

// Interrupt routine runs if CLK goes from HIGH to LOW
void isr ()  {
 delay(4);  // delay for Debouncing
 if (digitalRead(PinCLK))
   up = digitalRead(PinDT);
 else
   up = !digitalRead(PinDT);
 TurnDetected = true;
}

void setup ()  {
 pinMode(PinCLK,INPUT);
 pinMode(PinDT,INPUT);  
 pinMode(PinSW,INPUT);
 digitalWrite(PinSW, HIGH); // Pull-Up resistor for switch
 
 attachInterrupt (0,isr,FALLING); // interrupt 0 always connected to pin 2 on Arduino UNO
 Serial.begin (9600);
 Serial.println("Start");
 pinMode( MOTOR_B_DIR, OUTPUT );
 pinMode( MOTOR_B_PWM, OUTPUT );
 digitalWrite( MOTOR_B_DIR, LOW ); // Set motor to off
 digitalWrite( MOTOR_B_PWM, LOW );
}

void loop ()  {
 static long RotaryPosition=0;    // STATIC to count correctly

 if (!(digitalRead(PinSW))) {   // check if button is pressed
   if (RotaryPosition == 0) {  // check if button was already pressed
   } else {
       RotaryPosition=0; // if YES, then reset position to ZERO
       digitalWrite( MOTOR_B_DIR, LOW ); // turn motor off
       analogWrite( MOTOR_B_PWM, LOW ); 
       Serial.print ("Reset = ");
       Serial.println (RotaryPosition);
   }
 }
 
 // Runs if rotation was detected
 if (TurnDetected)  {
   if (up) {
     if (RotaryPosition >= 100) { // Max value set to 100
       RotaryPosition = 100;
     }
     else {
         RotaryPosition=RotaryPosition+2;
     }
   }
   else {
     if (RotaryPosition <= -100) { 
       // Max value set to -100        
       RotaryPosition = -100;
     }        
     else {          
       RotaryPosition=RotaryPosition-2;
      }
    }    
    TurnDetected = false;  // do NOT repeat IF loop until new rotation detected
    Serial.print ("Speed = "); 
    Serial.println (RotaryPosition);     
    
    // if Rotation is Clockwise    
    if (RotaryPosition > 0 && RotaryPosition < 11) { 
      digitalWrite( MOTOR_B_DIR, LOW ); // turn motor off 
      analogWrite( MOTOR_B_PWM, LOW );
    } 
   if (RotaryPosition > 10 && RotaryPosition < 21) {
      digitalWrite( MOTOR_B_DIR, HIGH ); // direction = forward
      analogWrite( MOTOR_B_PWM, 180 ); // PWM speed = 180
    }
    if (RotaryPosition > 20 && RotaryPosition < 31) {
      digitalWrite( MOTOR_B_DIR, HIGH ); // direction = forward
      analogWrite( MOTOR_B_PWM, 160 ); // PWM speed = 160
    }
    if (RotaryPosition > 30 && RotaryPosition < 41) {
      digitalWrite( MOTOR_B_DIR, HIGH ); // direction = forward
      analogWrite( MOTOR_B_PWM, 140 ); // PWM speed = 140
    }
    if (RotaryPosition > 40 && RotaryPosition < 51) {
      digitalWrite( MOTOR_B_DIR, HIGH ); // direction = forward
      analogWrite( MOTOR_B_PWM, 120 ); // PWM speed = 120
    } 
   if (RotaryPosition > 50 && RotaryPosition < 61) {
      digitalWrite( MOTOR_B_DIR, HIGH ); // direction = forward
      analogWrite( MOTOR_B_PWM, 100 ); // PWM speed = 100 
   } 
   if (RotaryPosition > 60 && RotaryPosition < 71) {
      digitalWrite( MOTOR_B_DIR, HIGH ); // direction = forward
      analogWrite( MOTOR_B_PWM, 80 ); // PWM speed = 80 
   }
    if (RotaryPosition > 70 && RotaryPosition < 81) { 
      digitalWrite( MOTOR_B_DIR, HIGH ); // direction = forward
      analogWrite( MOTOR_B_PWM, 60 ); // PWM speed = 60
    }
    if (RotaryPosition > 80 && RotaryPosition < 91) { 
      digitalWrite( MOTOR_B_DIR, HIGH ); // direction = forward
      analogWrite( MOTOR_B_PWM, 40 ); // PWM speed = 40
    }
    if (RotaryPosition > 90) { 
     digitalWrite( MOTOR_B_DIR, HIGH ); // direction = forward
     analogWrite( MOTOR_B_PWM, 20 ); // PWM speed = 20
   }
   
   
// if Rotation is Counter-Clockwise 
   
   if (RotaryPosition < 0 && RotaryPosition > -11) {
       digitalWrite( MOTOR_B_DIR, LOW ); // turn motor off
       analogWrite( MOTOR_B_PWM, LOW );
   }
   if (RotaryPosition < -10 && RotaryPosition > -21) { 
     digitalWrite( MOTOR_B_DIR, LOW ); // direction = reverse
     analogWrite( MOTOR_B_PWM, 40 ); // PWM speed = 40
   }
   if (RotaryPosition < -20 && RotaryPosition > -31) { 
     digitalWrite( MOTOR_B_DIR, LOW ); // direction = reverse
     analogWrite( MOTOR_B_PWM, 60 ); // PWM speed = 60
   }
   if (RotaryPosition < -30 && RotaryPosition > -41) { 
     digitalWrite( MOTOR_B_DIR, LOW ); // direction = reverse
     analogWrite( MOTOR_B_PWM, 80 ); // PWM speed = 80
   }
   if (RotaryPosition < -40 && RotaryPosition > -51) { 
     digitalWrite( MOTOR_B_DIR, LOW ); // direction = reverse
     analogWrite( MOTOR_B_PWM, 100 ); // PWM speed = 100
   }
   if (RotaryPosition < -50 && RotaryPosition > -61) { 
     digitalWrite( MOTOR_B_DIR, LOW ); // direction = reverse
     analogWrite( MOTOR_B_PWM, 120 ); // PWM speed = 120
   }
   if (RotaryPosition < -60 && RotaryPosition > -71) { 
     digitalWrite( MOTOR_B_DIR, LOW ); // direction = reverse
     analogWrite( MOTOR_B_PWM, 140 ); // PWM speed = 140
   }
   if (RotaryPosition < -70 && RotaryPosition > -81) { 
     digitalWrite( MOTOR_B_DIR, LOW ); // direction = reverse
     analogWrite( MOTOR_B_PWM, 160 ); // PWM speed = 160
   }
   if (RotaryPosition < -80 && RotaryPosition > -91) { 
     digitalWrite( MOTOR_B_DIR, LOW ); // direction = reverse
     analogWrite( MOTOR_B_PWM, 180 ); // PWM speed = 180
   }
   if (RotaryPosition < -90) { 
     digitalWrite( MOTOR_B_DIR, LOW ); // direction = reverse
     analogWrite( MOTOR_B_PWM, 200 ); // PWM speed = 200
   }
 }
}
