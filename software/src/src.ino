/**
 * src.ino
 * Author: Mark Hofmeister 
 * Created: 11/19/2022
 * Last commit: 11/19/2022
 * 
 * source code for Whipper-Snapper. Reads SD card files, initializes I2S output, and waits to enter interrupt service routines. 
 */
#include <SD.h>                             //Used to read .wav files on SD card
#include <ArduinoSound.h>                   //Used for I2S output 

uint8_t numFiles = 6;

uint8_t interruptPins[] =                   //Declare pins to be used for external interrupts
{  0, 1, 4, 
   5, 6, 7  };
  
const char fileNames[][6] =                 //Define array of character strings for wave file obect initialization
{  "0.WAV", 
   "1.WAV", 
   "2.WAV", 
   "3.WAV", 
   "4.WAV", 
   "5.WAV"  };

SDWaveFile waveFile[6];                       //define SDWaveFile objects for each wave file 


void setup() {

  Serial.begin(9600);                         //Command Serial to initialize and wait 
  while (!Serial);
  Serial.println("Serial monitor initialized");
  
  Serial.print("Initializing SD card...");  //Ensure that SD card can be read 
  if (!SD.begin()) {
    Serial.println("failed!");
    while(1);
  } 
  
  Serial.println("SD Card Initialized");

  for(int i = 0; i < numFiles; i++) {
    
    waveFile[i] = SDWaveFile(fileNames[0]);     //initialize wave file objects based on file names
    
    if(!(waveFile[i])) {                          //check to see if file was initialized successfully
      Serial.print("Wave file ");
      Serial.print(i);
      Serial.println(" is invalid.");
      while(1);
      
    } 
    else if(!(AudioOutI2S.canPlay(waveFile[i]))) {    //check to see if the wave file can be played

      Serial.print("Wave file ");
      Serial.print(i);
      Serial.println(" is unplayable.");
      while(1);
      
    }
    else {
      Serial.print("Wave file ");
      Serial.print(i);
      Serial.println(" successfully Initialized.");
    }
    
  }

  AudioOutI2S.volume(50.0);               //max volume

  /*for(int i = 0; i < numFiles; i++) {                     //do later
    attachInterrupt(digitalPinToInterrupt(interruptPins[i]), 
  }*/

  attachInterrupt(digitalPinToInterrupt(interruptPins[0]),  playISR0, RISING);
  attachInterrupt(digitalPinToInterrupt(interruptPins[1]),  playISR1, RISING);
  attachInterrupt(digitalPinToInterrupt(interruptPins[2]),  playISR2, RISING);
  attachInterrupt(digitalPinToInterrupt(interruptPins[3]),  playISR3, RISING);
  attachInterrupt(digitalPinToInterrupt(interruptPins[4]),  playISR4, RISING);
  attachInterrupt(digitalPinToInterrupt(interruptPins[5]),  playISR5, RISING);

}

void loop() {

noInterrupts();

    
      AudioOutI2S.play(waveFile[1]);  
      

  delay(5000);

}

/*void (*selectISR[6])() {

  
}*/

void playISR0() {

  Serial.println("Entered playISR 0");

  if(AudioOutI2S.isPlaying()) {
    
      //do nothing. Let other file play.
      
  } else {
    
      AudioOutI2S.play(waveFile[0]);  
      
  }
  
}

void playISR1() {
  
  Serial.println("Entered playISR 1");

  if(AudioOutI2S.isPlaying()) {
    
      //do nothing. Let other file play.
      
  } else {
    
      AudioOutI2S.play(waveFile[1]);  
      
  }
  
}

void playISR2() {

  Serial.println("Entered playISR 2");

  if(AudioOutI2S.isPlaying()) {
    
      //do nothing. Let other file play.
      
  } else {
    
      AudioOutI2S.play(waveFile[2]);  
      
  }
  
}

void playISR3() {

  Serial.println("Entered playISR 3");

  if(AudioOutI2S.isPlaying()) {
    
      //do nothing. Let other file play.
      
  } else {
    
      AudioOutI2S.play(waveFile[3]);  
      
  }
  
}

void playISR4() {

  Serial.println("Entered playISR 4");

  if(AudioOutI2S.isPlaying()) {
    
      //do nothing. Let other file play.
      
  } else {
    
      AudioOutI2S.play(waveFile[4]);  
      
  }
  
}

void playISR5() {

  Serial.println("Entered playISR 5");

  if(AudioOutI2S.isPlaying()) {
    
      //do nothing. Let other file play.
      
  } else {
    
      AudioOutI2S.play(waveFile[5]);  
      
  }
  
}
