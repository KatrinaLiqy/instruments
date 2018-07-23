//


//Flex sensors//
int r[4], g[4], b[4], c[4], col[4], tcs[4], a[4], o[4];
const int FLEX_PIN2 = A0; // Pin connected to voltage divider output
const int FLEX_PIN3 = A1;
const int FLEX_PIN4 = A2;
const int FLEX_PIN5 = A3;
float oldAngle2;
float oldAngle3;
float oldAngle4;
float oldAngle5;
const float VCC2 = 4.98; 
const float R_DIV2 = 47500.0;
const float VCC3 = 4.98; 
const float R_DIV3 = 47500.0;
const float VCC4 = 4.98; 
const float R_DIV4 = 47500.0;
const float VCC5 = 4.98; 
const float R_DIV5 = 47500.0;
const float STRAIGHT_RESISTANCE = 37300.0; // resistance when straight
const float BEND_RESISTANCE = 90000.0; // resistance at 90 deg

//Color sensor (TCS34725)//

#include <Wire.h>
#include "Adafruit_TCS34725.h"
 
// Adafruit_TCS34725 tcs = Adafruit_TCS34725();

int colordecide(int p)// p from 0 to 3 / include r[],g[],b[] from 0 to 3
{
  if (r[p]>10 && g[p]>10 && b[p]>10)
    col[p]=4;
  else if (r[p]>10)
    col[p]=1;
  else if (g[p]>10)
    col[p]=2;
  else if (b[p]>10)
    col[p]=3;
  else//default, don't play music
    col[p]=5;
  return col[p];
}
void duration(int p)
{  
  if (o[p]<=0.0 && a[p] >=0.0)
  {
    //Serial.write(p);
    Serial.println(1);
  }
  else if(a[p] <= 0.0)
  {
    //Serial.write(p);
    Serial.println(0);
  }
}
/* Initialise with specific int time and gain values */
Adafruit_TCS34725 tcs[0] = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_1X);
Adafruit_TCS34725 tcs[1] = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_1X);
Adafruit_TCS34725 tcs[2] = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_1X);
Adafruit_TCS34725 tcs[3] = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_1X);
void setup() 
{
  //Flex sensors//
  Serial.begin(9600);
  pinMode(FLEX_PIN2, INPUT);
  pinMode(FLEX_PIN3, INPUT);
  pinMode(FLEX_PIN4, INPUT);
  pinMode(FLEX_PIN5, INPUT);
  //Color Sensor//
  /*if (tcs.begin()) {
  Serial.println("Found sensor");
  } else {
  Serial.println("No TCS34725 found ... check your connections");
  while (1);
  }*/
}





void loop() {
  //Color sensor//
  uint16_t r, g, b, c, colorTemp, lux;//

  //Flex sensors//
  // Read the ADC, and calculate voltage and resistance from it
  int flexADC2 = analogRead(FLEX_PIN2);
  float flexV2 = flexADC2 * VCC2 / 1023.0;
  float flexR2 = R_DIV2 * (VCC2 / flexV2 - 1.0);

  int flexADC3 = analogRead(FLEX_PIN3);
  float flexV3 = flexADC3 * VCC3 / 1023.0;
  float flexR3 = R_DIV3 * (VCC3 / flexV3 - 1.0);
  
  int flexADC4 = analogRead(FLEX_PIN4);
  float flexV4 = flexADC4 * VCC4 / 1023.0;
  float flexR4 = R_DIV4 * (VCC4 / flexV4 - 1.0);
  
  int flexADC5 = analogRead(FLEX_PIN5);
  float flexV5 = flexADC5 * VCC5 / 1023.0;
  float flexR5 = R_DIV5 * (VCC5 / flexV5 - 1.0);
  //Serial.write("Resistance: " + String(flexR) + " ohms");
  // Use the calculated resistance to estimate the sensor's
  // bend angle:
  float angle2 = map(flexR2, STRAIGHT_RESISTANCE, BEND_RESISTANCE,0, 90.0);
  float angle3 = map(flexR3, STRAIGHT_RESISTANCE, BEND_RESISTANCE,0, 90.0);
  float angle4 = map(flexR4, STRAIGHT_RESISTANCE, BEND_RESISTANCE,0, 90.0);
  float angle5 = map(flexR5, STRAIGHT_RESISTANCE, BEND_RESISTANCE,0, 90.0);

  /*if (oldAngle2<=0.0 && angle2 >=0.0)
  {
    Serial.write(2);
    Serial.write(1);
  }
  //else 
  if(angle2 <= 0.0)
  {
    Serial.write(2);
    Serial.write(0);
  }
  //-------------------
  if (oldAngle3<=0.0 && angle3 >=0.0)
  {
    Serial.write(3);
    Serial.write(1);
  }
  //else 
  if(angle3 <= 0.0)
  {
    Serial.write(3);
    Serial.write(0);
  }
  //-------------------
  if (oldAngle4<=0.0 && angle4 >=0.0)
  {
    Serial.write(4);
    Serial.write(1);
  }
  //else 
  if(angle4 <= 0.0)
  {
    Serial.write(4);
    Serial.write(0);
  }
  //-------------------
  if (oldAngle5<=0.0 && angle5 >=0.0)
  {
    
   Serial.write(5);
   Serial.write(1);
    
  }
  //else 
  if(angle5 <= 0.0)
  {
    Serial.write(5);
    Serial.write(0);
   
  }*/
  //Serial.write("Bend2: " + String(angle2) + " degrees");
  //Serial.write("Bend3: " + String(angle3) + " degrees");
  //Serial.write("Bend4: " + String(angle4-5) + " degrees");
  //Serial.write("Bend5: " + String(angle5-8) + " degrees");
  //Serial.write("------");
  oldAngle2 = angle2;
  oldAngle3 = angle3;
  oldAngle4 = angle4;
  oldAngle5 = angle5;
  //delay(1500);

  //Color sensor//
  
  for (int i=0; i < 4 ; i++ )
  {
    tcs[i].getRawData(&r[i], &g[i], &b[i], &c[i]);//can i remove c[i]??
    //colorTemp = tcs[i].calculateColorTemperature(r, g, b);
    //lux = tcs.calculateLux(r, g, b);
    r[i]=map(r[i],1,65535,1,63);
    g[i]=map(g[i],1,65535,1,63);
    b[i]=map(b[i],1,65535,1,63);
  }
  for (int i = 0; i < 4 ; i++)
  {
    colordecide(i);
    Serial.println(col[i],i);
    duration(i);
  }
//  for (int j = 0; j < 4 ; j++)
//  {
//    Serial.println(col[j],j);
//  }
  //Serial.print("Color Temp: "); Serial.print(colorTemp, DEC); Serial.print(" K - ");
  //Serial.print("Lux: "); Serial.print(lux, DEC); Serial.print(" - ");
 /* Serial.print("R: "); Serial.print(r, DEC); Serial.print(" ");
  Serial.print("G: "); Serial.print(g, DEC); Serial.print(" ");
  Serial.print("B: "); Serial.print(b, DEC); Serial.print(" ");
  //Serial.print("C: "); Serial.print(c, DEC); Serial.print(" ");
  Serial.println(" ");
  */
}



//211
//21 =>#64
