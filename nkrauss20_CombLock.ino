/*
 * Nate Krauss
 * CS450HO - Combination Lock Project
 */

//LIBRARIES
#include <Password.h>
#include <elapsedMillis.h>

//VARIABLES
#define motor 6
#define redLED 9
#define greenLED 8
#define blueLED 7
#define but1 13
#define but2 12
#define but3 11
#define but4 10

#define passLength 4 //defines password length as 4
int currentLength = 0; //creates var for current length of pin entered
Password password = Password("4311"); //PassLib define password

//create var for how long red LED blinks for
unsigned int bruteDelay = 1000;

//SETUP
void setup() {
  //LEDs
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
  //BUTTONs
  pinMode(but1, INPUT);
  pinMode(but2, INPUT);
  pinMode(but3, INPUT);
  pinMode(but4, INPUT);

  //enable serial monitor
  while (!Serial); //enable Serial Monitor for debugging
  Serial.begin(9600);

  //test password
  password.append('4'); 
  password.append('3');
  password.append('1');
  password.append('1');
  Serial.println(password.evaluate()?"true":"false");

  //end of setup...
}

//FUCTIONS
void loop() { 
  //run functions
  buttonPress();
  passCheck();

  delay(10); //delay to prevent button "bouncing"
  //end of loop...
}

void buttonPress() {
  if (digitalRead(but1) == LOW) {
    //enter #1 into pin code
    password.append('1');

    //print #1 into serial monitor
    Serial.println("1");
  } else if (digitalRead(but2) == LOW) {
    //enter #2 into pin code
    password.append('2');

    //print #1 into serial monitor
    Serial.println("2");
  } else if (digitalRead(but3) == LOW) {
    //enter #3 into pin code
    password.append('3');
    
    //print #1 into serial monitor
    Serial.println("3");
  } else if (digitalRead(but4) == LOW) {
    //enter #4 into pin code
    password.append('4');
    
    //print #1 into serial monitor
    Serial.println("4");
  } else {
    
  }
  //end of buttonPress...
}

void passCheck() {
  //if password is "passLength" (4) digits long...
  if (passLength == currentLength) {
    /*if password is right/wrong...
     *uses Password library
     */
    if (password.evaluate()) {
      passCorrect();
    } else {
      passWrong();
    }
  } else {
    //turns blue LED on when password length isn't 4
    digitalWrite(blueLED, HIGH);
    //stops motor from spinning
    digitalWrite(motor, LOW);
  }
  
  //end of passCheck...
}

void passCorrect() {
  //prints to serial monitor
  Serial.println("Password Correct");

  //turns off blue LED
  digitalWrite(blueLED, LOW);
  //turns on green LED
  digitalWrite(greenLED, HIGH);
  //spins motor
  digitalWrite(motor, HIGH);

  //resets brute force delay timer to one second
  bruteDelay = 1000;

  //resets "currentLength" and password reset
  currentLength = 0;
  password.reset();

  //end of passCorrect...
}

void passWrong() {
  //create var timeElapsed using elaspedMillis Library
  elapsedMillis timeElapsed;

  //prints to serial monitor
  Serial.println("Password Incorrect");

  //turns off blue LED
  digitalWrite(blueLED, LOW);
  //brute force delay with red LED blinking
  while(timeElapsed < bruteDelay) {
    //blinks every 1/4 second
    digitalWrite(redLED, HIGH);
    delay(250);
    digitalWrite(redLED, LOW);
    delay(250);
  }

  //adds 1sec to brute force delay for each wrong pin
  bruteDelay = bruteDelay + 1000;

  //resets "currentLength" and password reset
  currentLength = 0;
  password.reset();

  //end of passWrong...
}
