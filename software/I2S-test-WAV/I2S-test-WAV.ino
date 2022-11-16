/*

 This example generates a square wave based tone at a specified frequency
 and sample rate. Then outputs the data using the I2S interface to a
 MAX98357 I2S Amp Breakout board.
 Circuit:
 * Arduino Zero, MKR family and Nano 33 IoT
 * MAX98357:
   * GND connected GND
   * VIN connected 5V
   * LRC connected to pin 0 (Zero) or 3 (MKR) or A2 (Nano)
   * BCLK connected to pin 1 (Zero) or 2 (MKR) or A3 (Nano)
   * DIN connected to pin 9 (Zero) or A6 (MKR) or 4 (Nano)

 */

#include <SD.h> 
#include <ArduinoSound.h>

const char file1[] = "1_YEAH.WAV";
SDWaveFile waveFile1;

void setup() {

  Serial.begin(9600);
  while (!Serial);
  Serial.println("Playing .WAV test");
  


   Serial.print("Initializing SD card...");
  if (!SD.begin()) {
    Serial.println("failed!");
  }
  
  Serial.println("SD Card Initialized");
  
  waveFile1 = SDWaveFile(file1);
   if (!waveFile1) {

    Serial.println("wave file is invalid!");

  }

  Serial.print("Bits per sample = ");

  Serial.println(waveFile1.bitsPerSample());

  long channels = waveFile1.channels();

  Serial.print("Channels = ");

  Serial.println(channels);

  long sampleRate = waveFile1.sampleRate();

  Serial.print("Sample rate = ");

  Serial.print(sampleRate);

  Serial.println(" Hz");

  long duration = waveFile1.duration();

  Serial.print("Duration = ");

  Serial.print(duration);

  Serial.println(" seconds");

   AudioOutI2S.volume(100.0);

   if (!AudioOutI2S.canPlay(waveFile1)) {

    Serial.println("unable to play wave file using I2S!");

    while (1); // do nothing

  }

  // start playback

  Serial.println("starting playback");

  AudioOutI2S.play(waveFile1);
}

void loop() {

  // check if playback is still going on

  if (!AudioOutI2S.isPlaying()) {

    // playback has stopped

    Serial.println("playback stopped");

    AudioOutI2S.play(waveFile1);

  }

}
