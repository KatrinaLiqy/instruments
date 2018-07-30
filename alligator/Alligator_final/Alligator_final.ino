#include <Adafruit_MPR121.h>
Adafruit_MPR121 sensor = Adafruit_MPR121();
int delays[] = {1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000};
int copy_delays[] = {1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000};
int buttons[12];
int old_buttons[12];
int changingButton;
int oldChangingButton = 0;
int switchButton = 0;
int oldSwitchButton = 0;
int pressesChange = 0;
int presses
int easterEgg = 0;
int easterEggOld = 0;
int repeats[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
int const global_delay = 100;
void setup() {
  Serial.begin(9600);
  sensor.begin(0x5A);

  for(int i = 2; i < 12; i ++)
  {
    pinMode(i, INPUT_PULLUP);
    old_buttons[i] = 0;
  }
  pinMode(A1, INPUT_PULLUP);
  pinMode(A2, INPUT_PULLUP);
  old_buttons[0] = 0;
  old_buttons[1] = 0;
  pinMode(12, INPUT_PULLUP);
  pinMode(A3, INPUT_PULLUP);
  pinMode(A0, INPUT_PULLUP);
}

void loop() {
  for(int i = 2; i < 12; i ++)
  {
    buttons[i] = digitalRead(i);
  }
  buttons[0] = digitalRead(A2);
  buttons[1] = digitalRead(A1);
  switchButton = !digitalRead(A3);
  changingButton = !digitalRead(12);
  easterEgg = !digitalRead(A0);
  pressesChange += changingButton*(changingButton - oldChangingButton);
  oldChangingButton = changingButton;
  //Serial.println(pressesChange);
  for(int i = 0; i < 6; i++)
  {
      if (buttons[i] == 0 && (buttons[i] != old_buttons[i]))
    {
        if(pressesChange % 2 == 0)
        {
         // Serial.print("changing button = ");
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
      if(pressesChange % 2 == 0)
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
   else if (delays[i] <= 0){delays[i] = 1000;} 
    
      //Serial.print(F("delays["));
      //Serial.print(i);
     // Serial.print(F("] = "));
     // Serial.println(delays[i]);
  
  }
if (resetButton == 1){
  for (int i = 0; i < 12; i++){
    copy_delays[i] = delays[i];
  }
}
  short bits = sensor.touched();
  for(int i = 0; i < 12; i++)
  {
    int temp = bitRead(bits, i);
    copy_delays[i] = copy_delays[i] - 125;
    if (copy_delays[i] <= 0){
      ///Serial.print(F("temp = "));
      Serial.write(temp);
      Serial.write(repeats[i]*temp);
      copy_delays[i] = delays[i];

    }
    else{
     Serial.write(0);
     Serial.write(0);
    }
     // Serial.print(F("copy_delays["));
     // Serial.print(i);
      //Serial.print(F("] = "));
      //Serial.println(copy_delays[i]);
  }
    for(int i = 0; i < 12; i ++)
    {
      old_buttons[i] = buttons[i];
    }
    if ((easterEgg * (easterEgg - easterEggOld)) == 1) {
      int quote = rand() %6 + 1;
      Serial.write(quote);
    } else {Serial.write(0);}
    easterEggOld = easterEgg;
    //Serial.println("e");
  oldSwitchButton = SwitchButton;
  delay(rand() %5 + 50);
}
