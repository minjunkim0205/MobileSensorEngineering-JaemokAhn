#include <Arduino.h>

#define pulsePin A0

int gainPercent = 100; // 증폭 배율(%) EX) 150 == 150% == 1.5배
float gain = gainPercent / 100.0;

int signalValue = 0;
int adjstedSignal = 0;
int threshold = 750;

unsigned long lastBestTime = 0;
unsigned long currentTime = 0;
bool pulseDetected = false;

const int numReadings = 5;
int bpmReadings[numReadings];
int readIndex = 0;
int total = 0;
int averageBPM = 0;
int bpm = 0;

void setup()
{
  Serial.begin(9600);
  for(int i = 0; i < numReadings; i++)
  {
    bpmReadings[i] = 0;
  }
}

void loop()
{
  signalValue = analogRead(pulsePin);
  adjstedSignal = signalValue * gain;

  // 값이 1023 을 초과하지 않도록 제한
  adjstedSignal = (adjstedSignal > 1023 ? 1023 : adjstedSignal);

  currentTime = millis();
  Serial.println(adjstedSignal); // 조정된 신호 출력

  delay(30);
}