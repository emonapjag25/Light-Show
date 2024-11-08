//-------------------------------
//Outputs, Inputs, and Variables
//-------------------------------
// OUTPUT: LEDs use digital pins 2-4, these pins are for my potentiometer part of my code
int red = 5;      //red light in the tri-colored bulb
int green = 4;    //green light in the tri-colored bulb
int blue = 3;     //blue light in the tri-colored bulb

//OUTPUT: LEDs use digital pins 5-8, these pins are for my loop
int blue2 = 2;    //left blue light
int green2 = 6;   //left green light
int yellow2 = 7;  //left yellow light
int red2 = 8;     //left red light

//program variables for my loop
int time = 1000;

//OUTPUT: LEDs use digital pins 9-12, these pins are for my button and typing input
int blue3 = 12;   //right blue light
int green3 = 11;  //right green light
int yellow3 = 10; //right yellow light
int red3 = 9;     //right red light

//INPUT: button uses digital pin 13
int button = 13;  //button

// INPUT: potentiometer uses analog pin A0
int potPin = A0;  //potentiometer
int potVal = 0;   //the amount the potentiometer is rotated

// program variables for my potentiometer
int redVal = 0;   //variables to store the values to send to the pins
int grnVal = 0;
int bluVal = 0;

//-----------
//Void Setup
//-----------
void setup(){
  Serial.begin(9600);
  pinMode(red, OUTPUT); // sets the pins as output
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(red2, OUTPUT); 
  pinMode(yellow2, OUTPUT);
  pinMode(green2, OUTPUT);
  pinMode(blue2, OUTPUT);
  pinMode(red3, OUTPUT); 
  pinMode(yellow3, OUTPUT);
  pinMode(green3, OUTPUT);
  pinMode(blue3, OUTPUT);
  
  pinMode(button, INPUT); // sets the button as input 
}//voide setup end

//----------
//Void Loop
//----------
void loop(){
//************************
//Loop part of my code
//************************
 digitalWrite(red2, HIGH);    //turns red light on
 delay(time); //wait for the number of milliseconds time is set to
 digitalWrite(red2, LOW);     //turns red light off
 digitalWrite(yellow2, HIGH); //turns yellow light on
 delay(time); //wait for the number of milliseconds time is set to
 digitalWrite(yellow2, LOW);  //turns yellow light off
 digitalWrite(green2, HIGH);  //turns green light on
 delay(time); //wait for the number of milliseconds time is set to
 digitalWrite(green2, LOW);   //turns green light off
 digitalWrite(blue2, HIGH);   //turns blue light on
 delay(time); //wait for the number of milliseconds time is set to
 digitalWrite(blue2, LOW);    //turns blue light off
  
//*************************
//Button  part of my code
//*************************
if(digitalRead(button) ==1){//if the button is held
  digitalWrite(red3, HIGH); //turns red and green lights on
  digitalWrite(green3, HIGH);
  digitalWrite(yellow3, LOW); //yellow and blue lights stays off
  digitalWrite(blue3, LOW); 
  delay(1000); //wait 1 second
  digitalWrite(yellow3, HIGH); //turns yellow and blue lights on
  digitalWrite(blue3, HIGH); 
  digitalWrite(red3, LOW); //red and green lights turn off
  digitalWrite(green3, LOW); 
} else{//if the button is anything BUT being held
  digitalWrite(red3, LOW); //all lights are turned off
  digitalWrite(yellow3, LOW);
  digitalWrite(green3, LOW);
  digitalWrite(blue3, LOW); 
}

//************************
//Typing part of my code
//************************
if(Serial.available()>0){
  	String color = "red";//string that stores what the user types
    color = Serial.readString();
    Serial.print("color: ");//prints out what color the user typed
    Serial.println(color);
    if(color.startsWith("yellow")||color.startsWith("Yellow")){//if "yellow" or "Yellow" is typed
      	digitalWrite(yellow3, HIGH); //turns yellow light on
      	delay(2000);                 //wait 2 seconds
        digitalWrite(yellow3, LOW);  //turns yellow light off
    } 
    else if(color.startsWith("red")||color.startsWith("Red")){//if "red" or "Red" is typed
        digitalWrite(red3, HIGH);    //turns red light on
      	delay(2000);                 //wait 2 seconds
        digitalWrite(red3, LOW);     //turns red light off
    } 
    else if(color.startsWith("green")||color.startsWith("Green")){//if "green" or "Green" is typed
        digitalWrite(green3, HIGH);  //turns green light on
      	delay(2000);                 //wait 2 seconds
        digitalWrite(green3, LOW);   //turns green light off
    } 
    else if(color.startsWith("blue")||color.startsWith("Blue")){//if "blue" or "Blue" is typed
        digitalWrite(blue3, HIGH);   //turns blue light on
      	delay(2000);                 //wait 2 seconds
        digitalWrite(blue3, LOW);    //turns blue light off
    }
}
  
//*******************************
//Potentiometer part of my code
//*******************************
  potVal = analogRead(potPin);   // read the potentiometer value at the input pin
	
  if (potVal < 341){  // Lowest third of the potentiometer's range (0-340)                
    potVal = (potVal * 3) / 4; // Normalize to 0-255
    redVal = 256 - potVal;  // red light from full to off
    grnVal = potVal;        // green light from off to full
    bluVal = 1;             // blue light off
  }             
  else if (potVal < 682){ // Middle third of potentiometer's range (341-681)
    potVal = ( (potVal-341) * 3) / 4; // Normalize to 0-255
    redVal = 1;             // Red off
    grnVal = 256 - potVal;  // Green from full to off
    bluVal = potVal;        // Blue from off to full
  }
  else{  // Upper third of potentiometer"s range (682-1023)
    potVal = ( (potVal-683) * 3) / 4; // Normalize to 0-255
    redVal = potVal;        // Red from off to full
    grnVal = 1;             // Green off
    bluVal = 256 - potVal;  // Blue from full to off
  }
  //Serial.println(potVal);//prints out potVal (commented out because of my typing part of my project)
  analogWrite(red, redVal); // Write values to LED pins
  analogWrite(green, grnVal); 
  analogWrite(blue, bluVal);  
}//void loop end