//Created by Dylan Rice

int count = 0; //Integer for keeping track of hall sensor events.

bool hall_effectA = true; //boolean gate for hall A.

bool hall_effectB = true; //boolean gate for hall B.

bool hall_effectN = true; //Boolean gate for hall N, where both A and B are false.

//directionality code.

int hall_effectM = 1;

double h1 = 0;

double h2 = 0;

//Pid Code.

bool count_print = true; //Boolean gate for printing out the number of counted hall events.

int time_new = 0;

int time_old = 0;

int current_error = 0;

int total_error = 0; //Keeps track of the total amount of error. Integral error.

int target = 100; //target tick location.

int Speed = 0; //speed of the motor.


int enable_pin = 7; //define pin 7 as the pwm output pin.

void setup()
{
  DDRC = 0b11010011; //Setting a value to 1 makes it an output zero an input. In the future I should really just put all the ones and zeros on the same side.

  PORTC = 0b00101100; //Setting a value to 1 turns on the pull up resistor for that register.

  PORTC &= 0b11111111;

  pinMode(enable_pin, OUTPUT); //Set pin 7 as the pwm output pin. For driving the speedo the motor.

  Serial.begin(9600); //Get the serial going.
}

void loop()
{

  //Hall A Logic.

  if (!(PINC & 0b00001000)) //If the values of PinC anded with the binary mask 0b00000010 is not true then blink the led.
  {

    if (hall_effectA == true)
    {
      PORTC |= 0b0000010; //Turn the last bit on. This causes pin 0 on port c to go high blinking the LED.

      hall_effectA = false; //lock the boolean gate.

      count++; //iterate the encoding

      Direction(true);
    }
  }
  else
  {
    PORTC &= 0b11111101; //Turn the last bit off

    hall_effectA = true; //Reopen the boolean gate.
  }


  //Hall B logic.

  if (!(PINC & 0b00000100))
  {
    if (hall_effectB == true) //
    {
      PORTC |= 0b00010000;

      count++; //iterate the encoding

      hall_effectB = false;

      Direction(true);

    }

  }
  else
  {
    PORTC &= 0b11101111;

    hall_effectB = true;
  }



  //hall effect n logic.

  if ((hall_effectA == true) && (hall_effectB == true))
  {
    if (hall_effectN == true)
    {
      count++; //iterate the encoding

      hall_effectN = false;

      Direction(false);
    }

  }
  else
  {
    hall_effectN = true;
  }











  
  //limit switch logic.

  if (!(PINC & 0b00100000))
  {
    PORTC |= 0b000000001; //Turn the red led on.

    if (count_print == true)//if count_print is true then print out the count integer and set count_print to false.
    {
      //Serial.println(hall_effect_order);//serial print.

      count_print = false; //set the gate to false so we don't get a whole bunch of print outs.
    }

    count = 0; //reset the counter
  }

  else
  {
    PORTC &= 0b11111110;

    count_print = true; //Reset the count_print boolean gate.
  }

  //Serial.println(count);

  //The actual PID control code.

  /*

    current_error = target - count;

    Speed = (target - count) * 0.64577 + (time_new - time_old)*1.3 + (target - count) * (time_new - time_old) ; //set the speed.

    if(Speed < 100)
    {
    Speed = 0;

    Serial.println(count);
    }

    setMotor(Speed, false);

  */
}

void setMotor(int speed, boolean reverse)
{
  analogWrite(enable_pin, speed);

  PORTC |= 0b10000000;

  PORTC &= 0b10111111;
}

void Direction(boolean type)
{
  if ((type == true) & (hall_effectM == 1))
  {
    h1 = millis();

    hall_effectM = 2;

    
  }
  if ((type == true) & (hall_effectM == 2))
  {
    h2 = millis();

    hall_effectM = 1;

    Serial.println(h2 - h1);
  }
  
}


