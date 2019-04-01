/*
  Input Pull-up Serial

  This example demonstrates the use of pinMode(INPUT_PULLUP). It reads a digital
  input on pin 2 and prints the results to the Serial Monitor.

  The circuit:
  - momentary switch attached from pin 2 to ground
  - built-in LED on pin 13

  Unlike pinMode(INPUT), there is no pull-down resistor necessary. An internal
  20K-ohm resistor is pulled to 5V. This configuration causes the input to read
  HIGH when the switch is open, and LOW when it is closed.

  created 14 Mar 2012
  by Scott Fitzgerald

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/InputPullupSerial
*/
#define ON HIGH
#define OFF LOW
#define SLEEP_TIME 60
int count = 0;
String stringOne = "Hello String";                    // using a constant String

class fan_auto{
  public:
    int sleep_time;
    int pir_pin;
    int relay_pin;
    void inline switch_on(){
    
    }
    void inline switch_off(){
      
    }

    fan_auto(int secs)
    {
      sleep_time = secs;
      pinMode(pir_pin, INPUT);
      pinMode(relay_pin, OUTPUT);
    }

    void check_pir()
    {
        delay(1000);
        //read the pushbutton value into a variable
        
        if (LOW == digitalRead(2))
        {
          count ++;
          if (SLEEP_TIME == count)
            digitalWrite(relay_pin, LOW);
          
        }
        else
        {    
          digitalWrite(13, HIGH);
          count = 0;
        }
    }
  
};

fan_auto fan1{SLEEP_TIME};

void setup() {
  //start serial connection
  Serial.begin(9600);
  //configure pin 2 as an input and enable the internal pull-up resistor

  
}

void loop() {
  fan1.check_pir();
}
