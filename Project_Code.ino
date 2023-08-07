#include "arduinoFFT.h"
#include <Servo.h>

#define SAMPLES 128            
#define SAMPLING_FREQUENCY 512 

arduinoFFT FFT = arduinoFFT();
// create servo object to control a servo
Servo myservo; 

int pos = 0;    
int servoPin = 3;
 
unsigned int samplingPeriod;
unsigned long microSeconds;

// creating vector of size Samples to hold real & imaginary values
double vReal[SAMPLES]; 
double vImag[SAMPLES];
 
void setup() 
{
    Serial.begin(115200); 
    // Find Period in microseconds
    samplingPeriod = round(1000000*(1.0/SAMPLING_FREQUENCY));  
    myservo.attach(servoPin);

}
 
void loop() 
{  
    int frequency = findFrequency(0); 
    Serial.println(frequency);
    // Figuring out rotation amount of motor based on detected frequency from analog pin 0 on Arduino
    int rotationAmountx = rotationAmount(frequency); 
    rotateMotorFunction(rotationAmountx, 2);
}
//carries out rotation of motor from 0 degrees to desired 'endPos' degrees
void rotateMotorFunction (int endPos,int delayNum) {
  for (int startPos = 0; startPos <= endPos; startPos += 1) { 
    myservo.write(startPos);              
    delay(delayNum);                      
  }
  
  int currentFrequency = findFrequency(0);
  // While the light frequency is within 5Hz of the initial frequency, do not rotate the motor back
  while(endPos/3.6 + 5 > currentFrequency && endPos/3.6 - 5 < currentFrequency){
      currentFrequency = findFrequency(0);
    }
   //for loop to rotate back from 'endPos' to 0 degrees
   for (int goingBack = endPos; goingBack >= 0; goingBack -= 1) {
    myservo.write(goingBack);              
    delay(delayNum);                      
  }
}

double findFrequency(int phototransistorAnalogPinNumber) { 
  /*Sample SAMPLES times*/
    for(int i=0; i<SAMPLES; i++)
    {
        //Returns the number of microseconds since the Arduino board began running the current script
        microSeconds = micros(); 
     
        vReal[i] = analogRead(phototransistorAnalogPinNumber); 
        vImag[i] = 0; 

        /*remaining wait time between samples if necessary*/
        while(micros() < (microSeconds + samplingPeriod))
        {
          //do nothing
        }
    }

    float mean = findAverage (vReal);
    if (mean < 50) return 0;

    //Fourier transform application using 'ArduinoFFT' library
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
