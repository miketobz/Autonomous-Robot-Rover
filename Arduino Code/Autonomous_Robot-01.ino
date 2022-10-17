//Hardware used:
//  *TB6612FNG motor driver.
//  *HC-SR04 ultrasonic distance sensor.

//------------------------------------------------------------------------------------------------------------------------



//Motor driver pins:


  //* Channel A:
  const int AIN1 = 13;                   //controls pin 1 of channel A.
  const int AIN2 = 12;                   //controls pin 2 of channel A.
  const int PWMA = 11;                   //controls the speed of the right motor.



  //* Channel B:
  const int BIN1 = 8;                   //controls pin 1 of channel B.
  const int BIN2 = 9;                   //controls pin 2 of channel B.
  const int PWMB = 10;                  //controls the speed of the left motor.








//Distance sensor pins:


  const int trigPin = 6;                //sends out an ultrasonic pulse.
  
  const int echoPin = 7;                //measures the duration taken by pulses to return to-
                                        //-the sensor.







const int switchPin = 4;                //will turn the robot ON or OFF.

const int ledPin = 2;                   //turns green LED ON and OFF.

float distance = 0;                     //the distance measured by the sensor.







//Robot behaviour variables:

  int backupTime = 95;                //time taken(ms) to reverse once an object is in front.
    
  int turnTime = 150;                  //time taken(ms) to turn robot after it has reversed.




//------------------------------------------------------------------------------------------------------------------------




void setup() {

  //* Distance sensor pins:
    pinMode(trigPin, OUTPUT);           //set pin as an O/P.
    pinMode(echoPin, INPUT);            //set pin as an I/P.



  //* Switch pin:
    pinMode(switchPin, INPUT_PULLUP);   //senses whether the switch is flipped.


    

  //* LED pin:
    pinMode(ledPin, OUTPUT);            //controls the green LED.




  //* Motor driver pins:

    //Channel A:
      pinMode(AIN1, OUTPUT);            //set pin as O/P.
      pinMode(AIN2, OUTPUT);            //set pin as O/P.
      pinMode(PWMA, OUTPUT);            //set pin as O/P.



    //Channel B:
      pinMode(BIN1, OUTPUT);            //set pin as O/P.
      pinMode(BIN2, OUTPUT);            //set pin as O/P.
      pinMode(PWMB, OUTPUT);            //set pin as O/P.

      





  Serial.begin(9600);                       //starts serial comm. with your computer.

  Serial.print("To infinity and beyond!");  //displays the sentense.
    

}




//-----------------------------------------------------------------------------------------------------------------------




void loop() {

  //Displays how close an object is to the robot:

    distance = getDistance();

     Serial.print("Distance: ");
     Serial.print(distance);
     Serial.println(" inches.");          // print the units.



  if(digitalRead(switchPin) == LOW){     //if the robot is turned ON.


    if(distance < 10){                   //if an object is detected; < 10 inches away-
                                         //-back up and turn.
        Serial.print(" ");
        Serial.print("BACK!");


      //stop for a moment:
        rightMotor(0);
        leftMotor(0);
        delay(200);


      //back up:
        rightMotor(-255);
        leftMotor(-255);
        delay(backupTime);


      //turn to the right:
        rightMotor(-255);
        leftMotor(255);    
        delay(turnTime);


    






    
    }else{                             //if no obstacle is detected, drive it forward.
      
      Serial.print(" ");
      Serial.print("Moving...");


      
     digitalWrite(ledPin, HIGH);   // Turn on the LED.
  
     delay(1500);              // Wait for one and a half seconds.

     digitalWrite(ledPin, LOW);    // Turn off the LED.
  
     delay(1500);              // Wait for one and a half seconds.




      rightMotor(255);
      leftMotor(255);


    }

    
  } 





  
  else{                         //if the robot is OFF.

      digitalWrite(ledPin, LOW);    // Turn off the LED. 
                               
      rightMotor(0);            //stop the motors.
      leftMotor(0);

      
  }



  delay(50);                    //wait 50 milliseconds between distance readings.



  
}




//----------------------------------------------***FUNCTIONS***------------------------------------------------------------------------



//Drives the right motor:

  void rightMotor(int motorSpeed){
      
      if(motorSpeed > 0){               //if motor speed is positive, drive robot forward.
        
         digitalWrite(AIN1, HIGH);
         digitalWrite(AIN2, LOW);     
      }

      
      else if(motorSpeed < 0){         //if motor speed is negative, drive robot backward.
        
         digitalWrite(AIN1, LOW);
         digitalWrite(AIN2, HIGH);  
      }


      else{                            //if motor speed is 0, DO NOT drive motors.
        
         digitalWrite(AIN1, LOW);
         digitalWrite(AIN2, LOW);  
        
      }


  analogWrite(PWMA, abs(motorSpeed));  //controls the motor speed.
  
  
  }




//****************************************************************************************************************************************



//Drives the left motor:

  void leftMotor(int motorSpeed){
      
      if(motorSpeed > 0){               //if motor speed is positive, drive robot forward.
        
         digitalWrite(BIN1, HIGH);
         digitalWrite(BIN2, LOW);     
      }

      
      else if(motorSpeed < 0){         //if motor speed is negative, drive robot backward.
        
         digitalWrite(BIN1, LOW);
         digitalWrite(BIN2, HIGH);  
      }


      else{                            //if motor speed is 0, DO NOT drive motors.
        
         digitalWrite(BIN1, LOW);
         digitalWrite(BIN2, LOW);  
        
      }


  analogWrite(PWMB, abs(motorSpeed));  //controls the motor speed.
  
  
  }







//*********************************************************************************************************************************




//RETURNS THE DISTANCE MEASURED BY THE HC-SR04 DISTANCE SENSOR:

  float getDistance()
  {
    float echoTime;                   //store the time taken for a pulse to bounce off object.
    float calcualtedDistance;         //stores the distance calculated from the echo time.
    

    //send out an ultrasonic pulse that's 10ms (period) long:
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10); 
      digitalWrite(trigPin, LOW);


    echoTime = pulseIn(echoPin, HIGH);      //see how long it takes for the pulse to returm to the sensor.

    calcualtedDistance = echoTime / 148.0;  //calculate the distance of object that reflected the pulse(half the bounce time multiplied by the speed of sound)

    return calcualtedDistance;              //returns the distance that was calculated (inches).
    
}

















