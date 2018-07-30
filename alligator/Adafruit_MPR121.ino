#include <Adafruit_MPR121.h>
Adafruit_MPR121 sensor = Adafruit_MPR121();
int delays[] = {1000, 1000, 1000, 1000, 1000, 1000};
int copy_delays[] = {1000, 1000, 1000, 1000, 1000, 1000};
int buttons[12];
int old_buttons[12];
int changingButton;
int oldChangingButton = 0;
int delay_1 = 250;
int presses = 0;
int repeats[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
int const global_delay = 100;
void setup() {
  sensor.begin(0x5A);
  Serial.begin(9600);
  for(int i = 0; i < 12; i ++)
  {
    pinMode(i, INPUT_PULLUP);
    old_buttons[i] = 0;
  }
  pinMode(12, INPUT_PULLUP);
}

void loop() {
  for(int i = 0; i < 12; i ++)
  {
    buttons[i] = digitalRead(i);
  }
  changingButton = !digitalRead(12);
  presses += changingButton*(changingButton - oldChangingButton);
  oldChangingButton = changingButton;
  //Serial.println(presses);
  for(int i = 0; i < 6; i++)
  {
      if (buttons[i] == 0 && (buttons[i] != old_buttons[i]))
    {
        if(presses % 2 == 0)
        {
          //Serial.print("changing button = ");
          //Serial.println(changingButton);
          delays[i] += 125;
          copy_delays[i] = delays[i];
        }
        else
        {
          
          //Serial.print("changing button = ");
          //Serial.println(changingButton);
          repeats[i] += 1;
        }

    }
   else if (buttons[i + 6] == 0 && (buttons[i + 6] != old_buttons[i + 6]))
    {
      if(presses % 2 == 0)
        {
          
         // Serial.print("changing button = ");
          //Serial.println(changingButton);
          delays[i] -= 125;
          copy_delays[i] = delays[i];
        }
        else
        {
          
          //Serial.print("changing button = ");
          //Serial.println(changingButton);
          repeats[i] -= 1;
        }
    }
   else if (delays[i] <= 0){delays[i] = 250;} 
    
      //Serial.print(F("delays["));
      //Serial.print(i);
     // Serial.print(F("] = "));
     // Serial.println(delays[i]);
  
  }

  short bits = sensor.touched();
  for(int i = 0; i < 6; i++)
  {
    int temp = bitRead(bits, i);
    copy_delays[i] = copy_delays[i] - 125;
    if (copy_delays[i] <= 0){
      ///Serial.print(F("temp = "));
      Serial.write(temp);
      copy_delays[i] = delays[i];

    }
    else{
     Serial.write(0);
    }
    Serial.write(repeats[i]);
     // Serial.print(F("copy_delays["));
     // Serial.print(i);
      //Serial.print(F("] = "));
      //Serial.println(copy_delays[i]);
  }
    for(int i = 0; i < 12; i ++)
    {
      old_buttons[i] = buttons[i];
    }
    //Serial.println("e");
  ////delay(50);
}
