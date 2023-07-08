#include "arduinoFFT.h"
#include <Servo.h>

#define SAMPLES 128            
#define SAMPLING_FREQUENCY 512 

arduinoFFT FFT = arduinoFFT();
Servo myservo;  // create servo object to control a servo

int pos = 0;    
int servoPin = 3;
 
unsigned int samplingPeriod;
unsigned long microSeconds;
 
double vReal[SAMPLES]; //create vector of size SAMPLES to hold real values
double vImag[SAMPLES]; //create vector of size SAMPLES to hold imaginary values
 
void setup() 
{
    Serial.begin(115200); 
    samplingPeriod = round(1000000*(1.0/SAMPLING_FREQUENCY)); //Period in microseconds 
    myservo.attach(servoPin);

}
 
void loop() 
{  
    int frequency = findFrequency(0); //Find frequency using the signal on analog pin 0 on the Arduino
    Serial.println(frequency);
    int rotationAmountx = rotationAmount(frequency); //Figure out by how much to rotate the motor
    rotateMotorFunction(rotationAmountx, 2); //Rotate the motor
}

void rotateMotorFunction (int endPos,int delayNum) {
  for (int startPos = 0; startPos <= endPos; startPos += 1) { // goes from 0 degrees to endPos degrees in steps of 1 degree
    myservo.write(startPos);              // tell servo to go to position in variable 'startpos'
    delay(delayNum);                      // waits delayNum for the servo to reach the position
  }
  
  int currentFrequency = findFrequency(0);
  while(endPos/3.6 + 5 > currentFrequency && endPos/3.6 - 5 < currentFrequency){
      currentFrequency = findFrequency(0);
      //While the light frequency is within 5Hz of the initial frequency, do not rotate the motor back
    }
  
   for (int goingBack = endPos; goingBack >= 0; goingBack -= 1) { // goes from endPos degrees to 0 degrees
    myservo.write(goingBack);              
    delay(delayNum);                      
  }
}

double findFrequency(int phototransistorAnalogPinNumber) { 
  /*Sample SAMPLES times*/
    for(int i=0; i<SAMPLES; i++)
    {
        microSeconds = micros();    //Returns the number of microseconds since the Arduino board began running the current script
     
        vReal[i] = analogRead(phototransistorAnalogPinNumber); 
        vImag[i] = 0; //Makes imaginary term 0 always

        /*remaining wait time between samples if necessary*/
        while(micros() < (microSeconds + samplingPeriod))
        {
          //do nothing
        }
    }

    float mean = findAverage (vReal);
    if (mean < 50) return 0;

    //Fourier transform application
    FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
    FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
    FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);

    //Find peak frequency and print peak
    double peak = FFT.MajorPeak(vReal, SAMPLES, SAMPLING_FREQUENCY);
    return peak;
}
 
float findAverage (double * array)  
    {
      long sum = 0L ;  
      for (int i = 0 ; i < 128; i++)
        sum += array [i] ;
      return  ((float) sum) / 128 ;  
    }


int rotationAmount(int rawFrequency) {
  int frequency = round(rawFrequency);
  if (frequency < 10 || frequency > 50) return 0;
  return frequency * 3.6;
}
