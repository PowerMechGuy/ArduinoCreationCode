/*Infrared Stepper Remote Control for the Hobby Buggy
 *This program requires a LED on pin 10, a IR receiver on pin 11,
 *and a steppers on pins 2, 3, 4, 5, 6, 7, 8, and 9. It is designed to allow the
 *accurate remote controle of the stepper with an indacating LED.
 *In order to accomplish more than one task in a single clock time,
 *it uses the millis() command. I have noticed that the initial speed
 *of the stepper decreases as you hold down the button on the remote.
 *This is not a problem, but I'm not exactly sure what to change to minimize it.
 *In this version I have added support for a second motor
 *thus completing the code.
 *
 *In this final update, I have configured all of the directions.
 *The Hobby Buggy can now go forward, backward, left, and right.
 *
 * Version 6.0.1
 *
 * Completed April 27, 2018 at around 12:43 PM
 *
 * Author: PowerMechGuy
 */

//including the infrared libarary
#include <IRremote.h>

//including the upgraded stepper library
#include <AccelStepper.h>

//Here I am telling the stepper I want it to halfstep    
#define HALFSTEP 8

    //These variables will act as
    //the pin representatives
    int pin1 = 2;
    int pin2 = 3;
    int pin3 = 4;
    int pin4 = 5;
    //More stepper definitions
        #define motorPin1 pin1 
        // IN1 on the ULN2003 driver 1 
        #define motorPin2 pin2
        // IN2 on the ULN2003 driver 1 
        #define motorPin3 pin3 
        // IN3 on the ULN2003 driver 1 
        #define motorPin4 pin4 
        // IN4 on the ULN2003 driver 1
        
        //Creating a instance of an accelstepper
        AccelStepper stepper1(HALFSTEP, pin1, pin3, pin2, pin4);

//This will be the declaration of the second stepper

//These variables will act as
    //the pin representatives
    int pin5 = 6;
    int pin6 = 7;
    int pin7 = 8;
    int pin8 = 9;
    //More stepper definitions
        #define motorPin1 pin5 
        // IN1 on the ULN2003 driver 1 
        #define motorPin2 pin6
        // IN2 on the ULN2003 driver 1 
        #define motorPin3 pin7 
        // IN3 on the ULN2003 driver 1 
        #define motorPin4 pin8 
        // IN4 on the ULN2003 driver 1
        
        //Creating a instance of an accelstepper
        AccelStepper stepper2(HALFSTEP, pin5, pin7, pin6, pin8);

//This will be the universal distance control variable for the stepper.
int stepdistance1 = 1000;
int stepdistance2 = -1000;
//The class below will be for the timing of the steppers    
class steppermotora{
    
    //These variables will hold the stepper
    //motor run time
    long onTime;
    
    //I needed to make this variable
    //public for reference below
    public: int stepmove;
    
    //These variables will be used for timing
    int stepperstate;
    unsigned long previousMillis;
    
    //This constructor will iniatialize the
    //above variables
    public:
    steppermotora(long on, int distance)
    {
        
        //Aligning the initialization of the time variables
        onTime = on;

        //Setting up time tracking variables
        stepperstate = LOW;
        previousMillis = 0;
        
        //Here I am placing the distance
        //value collected from the constructor
        //into stepmove for future reference
        stepmove = distance;

        
    } 
    
    //This handy function will keep track of time for the infraredstepper
    void Update()
    {
        //This is the crucial timekeeping variable
        //of this millis() operation
        unsigned long currentMillis = millis();
        
        //So what this if is evaluating is that
        //if the variable stepperstate has a HIGH
        //in it and that is the current time minus
        //the starting time is greater than or equal
        //to the previously set onTime, that the stepper
        //needs to stop. It then resets the stepperstate
        //variable.
        if ((stepperstate = HIGH) && (currentMillis - previousMillis >= onTime))
        {
            //stops stepper
            stepper1.stop();
            
            //resets stepper logic variable
            stepperstate = LOW;
           
        }
    } 
};

//The class below will be for the timing of the steppers    
class steppermotorb{
    
    //These variables will hold the stepper
    //motor run time
    long onTime;
    
    //I needed to make this variable
    //public for reference below
    public: int stepmove;
    
    //These variables will be used for timing
    int stepperstate;
    unsigned long previousMillis;
    
    //This constructor will iniatialize the
    //above variables
    public:
    steppermotorb(long on, int distance)
    {
        
        //Aligning the initialization of the time variables
        onTime = on;

        //Setting up time tracking variables
        stepperstate = LOW;
        previousMillis = 0;
        
        //Here I am placing the distance
        //value collected from the constructor
        //into stepmove for future reference
        stepmove = distance;

        
    } 
    
    //This handy function will keep track of time for the infraredstepper
    void Update()
    {
        //This is the crucial timekeeping variable
        //of this millis() operation
        unsigned long currentMillis = millis();
        
        //So what this if is evaluating is that
        //if the variable stepperstate has a HIGH
        //in it and that is the current time minus
        //the starting time is greater than or equal
        //to the previously set onTime, that the stepper
        //needs to stop. It then resets the stepperstate
        //variable.
        if ((stepperstate = HIGH) && (currentMillis - previousMillis >= onTime))
        {
            //stops stepper
            stepper2.stop();
            
            //resets stepper logic variable
            stepperstate = LOW;
           
        }
    } 
};
            
//This class will be for the indacator LED
class statusled{
    
  //made this public for future reference
  public: int pinnum;
    
  //basically how long I want the LED to light up.
  //This is basically here because everything
  //happens so fast and I want to see light.
  long ontime;
    
  //made this public for future reference
  //This will serve as the logic variable.
  public: int ledstate;
    
  //made this public for future reference
  //This will serve as one of the essential
  //timekeeping variables.  
  public: unsigned long oldtime;
    
    //This constructor will initialize the above variables. 
    public:
    statusled(int pin, long on)
    {
        //grap the pin number and put it in pinnum
        pinnum = pin;
        
        //designate the pin specified
        //in pinnum as OUTPUT
        pinMode(pinnum, OUTPUT);
        
        //grab the ontime
        ontime = on;
        
        //Initialize the logic variable
        ledstate = LOW;
        
        //Initialze the timekeeping variable
        oldtime = 0;
    }
    
    //This is the essential millis() timekeeping function
    void update()
    {
        //This is the essential timekeeping
        //variable of this millis() operation
        unsigned long currenttime = millis();
        
        //This if statement is evaluating the following:
        //if the ledstate variable contains a HIGH
        //and the currenttime minus the starting time equals
        //the designated ontime; then reset the ledstate logic variable
        //and write to the LED accordingly
        if ((ledstate = HIGH) && (currenttime - oldtime >= ontime))
        {
            //reset logic variable
            ledstate = LOW;
            
            //turn the LED off
            digitalWrite(pinnum, ledstate);
        }
    }  
};

//This variable will keep track of the direction
byte direction = 0;

//variable for IR receiver pin
int IRpin = 11;

//Finishing up infrared
//designating IR pin to be used
IRrecv irrecv(IRpin);

//choosing a variable to store results collected
//from the IR receiver
decode_results results;
/////////////////////////////////////////////


//This is where the instance declarations will go...
//First I'll declare a stepper timer with a ontime
//of 200 milliseconds and a stepmove of stepdistance
//which was previously defined as 1000
steppermotora infraredsteppera(200, stepdistance1);
steppermotorb infraredstepperb(200, stepdistance2);
//Next I delcare a counter for the LED
//with a pin number of 10 and a ontime
//of 200 milliseconds which I found was
//just enough time for the microcontroller
//to catch input from the remote and respond
statusled led(10, 200);

//Finally we have arrived at void setup()
void setup()
{
    
        
        //Setting up stepper runtime parameters
        //Not too sure what these are exactly...
        stepper1.setMaxSpeed(1500.0);
        stepper1.setAcceleration(100.0);
        stepper1.setSpeed(200);
        //stepper1.moveTo(stepdistance1);
        //Second Stepper
        stepper2.setMaxSpeed(1500.0);
        stepper2.setAcceleration(100.0);
        stepper2.setSpeed(200);
        //stepper2.moveTo(stepdistance2);
        
    
    //Here I am starting up the infrared receiver
    irrecv.enableIRIn(); // Start the receiver 
}
//This will contain all the continuous direction functions

void forward()
{
    
}


//Next the painstakingly constructed loop
void loop()
{
    //We start the loop with an additional
    //millis procedure. Millis is more of a
    //manual counter. So you have to take ad-
    //vantage of the loop function in order
    //to keep track of the time everytime the
    //microcontroller makes a run...
    
    //This is for the indacator LED to keep time
    led.update();
    
    //This is for the stepper to keep time
    infraredsteppera.Update();
    infraredstepperb.Update();
    
    //This if says if the stepper logic variable
    //contains a HIGH, then start the stepper
    //according to the parameters setup in the 
    //setup function.
    if (infraredsteppera.stepperstate == HIGH && infraredstepperb.stepperstate == HIGH)
    {
        //the stepper won't move without this command
        stepper1.run();
        //Second Stepper
        stepper2.run();
    }
    
    //This if is checks to to see if
    //anything was picked up on the IR
    //receiver, stores it in results, and
    //repeats
    if (irrecv.decode(&results)) {
    irrecv.resume(); // Receive the next value
    
  }
    //This if starts the LED and stepper
    //only if the button that broadcasts
    //the following number is pressed.
    if (results.value == 16754775)
    {
        //Plus button has been pressed
        //Setup direction variable
        direction = 1;
        
        //Reset Position of Motors
        stepper1.setCurrentPosition(0);
        stepper2.setCurrentPosition(0);
        
        
        //First we set the indacator logic
        //variable for the LED HIGH to start it
        led.ledstate = HIGH;
        
        //Next we actually turn it on to reflect
        //the logic of the logic variable
        digitalWrite(led.pinnum, led.ledstate);
        
        //Next we setup the start time variable
        //To actually be relevant to the current time
        led.oldtime = millis();
        
        //This sets the stepper logic variable
        //to HIGH
        infraredsteppera.stepperstate = HIGH;
        infraredstepperb.stepperstate = HIGH;
        
        //Now we setup the start time variable for the stepper
        //to be relevant to the current time
        infraredsteppera.previousMillis = millis();
        infraredstepperb.previousMillis = millis();
        
        //Finally, we reset the value variable to avoid any weird
        //stuff.
        results.value = 0;
        
        
    } 
    
    if (results.value == 16769565)
    {
        //Ch+ button has been pressed
        //Setup direction variable
        direction = 2;
        
        //Reset Position of Motors
        stepper1.setCurrentPosition(0);
        stepper2.setCurrentPosition(0);
        
        //First we set the indacator logic
        //variable for the LED HIGH to start it
        led.ledstate = HIGH;
        
        //Next we actually turn it on to reflect
        //the logic of the logic variable
        digitalWrite(led.pinnum, led.ledstate);
        
        //Next we setup the start time variable
        //To actually be relevant to the current time
        led.oldtime = millis();
        
        //This sets the stepper logic variable
        //to HIGH
        infraredsteppera.stepperstate = HIGH;
        infraredstepperb.stepperstate = HIGH;
        
        //Now we setup the start time variable for the stepper
        //to be relevant to the current time
        infraredsteppera.previousMillis = millis();
        infraredstepperb.previousMillis = millis();
        
        //Finally, we reset the value variable to avoid any weird
        //stuff.
        results.value = 0;
        
        
    }
    
    if (results.value == 16756815)
    {
        //200+ button has been pressed
        //Setup direction variable
        direction = 3;
        
        //Reset Position of Motors
        stepper1.setCurrentPosition(0);
        stepper2.setCurrentPosition(0);
        
        
        //First we set the indacator logic
        //variable for the LED HIGH to start it
        led.ledstate = HIGH;
        
        //Next we actually turn it on to reflect
        //the logic of the logic variable
        digitalWrite(led.pinnum, led.ledstate);
        
        //Next we setup the start time variable
        //To actually be relevant to the current time
        led.oldtime = millis();
        
        //This sets the stepper logic variable
        //to HIGH
        infraredsteppera.stepperstate = HIGH;
        infraredstepperb.stepperstate = HIGH;
        
        //Now we setup the start time variable for the stepper
        //to be relevant to the current time
        infraredsteppera.previousMillis = millis();
        infraredstepperb.previousMillis = millis();
        
        //Finally, we reset the value variable to avoid any weird
        //stuff.
        results.value = 0;
        
        
    }
    
    if (results.value == 16732845)
    {
        //9 button has been pressed
        //Setup direction variable
        direction = 4;
        
        //Reset Position of Motors
        stepper1.setCurrentPosition(0);
        stepper2.setCurrentPosition(0);
        
        
        //First we set the indacator logic
        //variable for the LED HIGH to start it
        led.ledstate = HIGH;
        
        //Next we actually turn it on to reflect
        //the logic of the logic variable
        digitalWrite(led.pinnum, led.ledstate);
        
        //Next we setup the start time variable
        //To actually be relevant to the current time
        led.oldtime = millis();
        
        //This sets the stepper logic variable
        //to HIGH
        infraredsteppera.stepperstate = HIGH;
        infraredstepperb.stepperstate = HIGH;
        
        //Now we setup the start time variable for the stepper
        //to be relevant to the current time
        infraredsteppera.previousMillis = millis();
        infraredstepperb.previousMillis = millis();
        
        //Finally, we reset the value variable to avoid any weird
        //stuff.
        results.value = 0;
        
        
    }
    
        //This if was put in place to exploit a feature
        //of IR transceivers. They always seem to emit
        //a finishing signal with the following value
        //continuously. I used this to perform the 
        //following tasks so the the microcontroller
        //will have something to do when a button is
        //held down.
        if (results.value == 4294967295)
            {
                //Extend LED time by ressetting the start time
                //variable according to the current time
                led.oldtime = millis();
        
                //This resets the stepper start time variable
                //To a close of just out of reach start time as well
                infraredsteppera.previousMillis = millis();
                infraredstepperb.previousMillis = millis();
        
                //This is actually the command that is responsible
                //for the continuous movement of the stepper. Keeping time
                //only seems to slow it down. In order to trick the stepper
                //into continuous movement, you just make it's final destination
                //farther away. I found that adding 1000 (or stepdistance) to
                //its final destination was adequate.
        
                //I'll use a switch statement to change direction.
                
                switch (direction)
                {
                    case 1:
                    stepper1.moveTo(stepper1.currentPosition() + stepdistance1);
                    //Second Stepper
                    stepper2.moveTo(stepper2.currentPosition() + stepdistance2);
        
                    //Then we reset the IR results variable once again
                    //to avoid any weird stuff or unwanted repeats.
                    results.value = 0;
                    break;
                    
                    case 2:
                    stepper1.moveTo(stepper1.currentPosition() - stepdistance1);
                    //Second Stepper
                    stepper2.moveTo(stepper2.currentPosition() - stepdistance2);
        
                    //Then we reset the IR results variable once again
                    //to avoid any weird stuff or unwanted repeats.
                    results.value = 0;
                    break;
            
                    case 3:
                    stepper1.moveTo(stepper1.currentPosition() + stepdistance1);
                    //Second Stepper
                    stepper2.moveTo(stepper2.currentPosition() - stepdistance2);
        
                    //Then we reset the IR results variable once again
                    //to avoid any weird stuff or unwanted repeats.
                    results.value = 0;
                    break;
            
                    case 4:
                    stepper1.moveTo(stepper1.currentPosition() - stepdistance1);
                    //Second Stepper
                    stepper2.moveTo(stepper2.currentPosition() + stepdistance2);
        
                    //Then we reset the IR results variable once again
                    //to avoid any weird stuff or unwanted repeats.
                    results.value = 0;
                    break;
            
                }
                
        }
    
    
    //This particular if has no use right now.
    //But it may come in handy in the future.
    //Basically if nothing has come fromt the IR
    //then do something...
    else if (results.value == 0)
        {
            //Just cleaning up the results variable again          
            results.value = 0;
            
            //This takes us right back up to the beginning of the loop function!
            return;
        }
    
} //The end.

