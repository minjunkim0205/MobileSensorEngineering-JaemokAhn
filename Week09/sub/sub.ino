#include <Arduino.h>

const int pulsePin = A0;
int gainPercent = 100;
float gain = gainPercent / 100.0;

int signalValue = 0;
int adjustedSignal = 0;

const float dt = 0.03;               // 30ms = 0.03s
const int differentiationCount = 1;  // 몇 번 미분할지 설정 (1~N)

float* derivatives = nullptr;     // 미분 결과 배열
float* previousValues = nullptr;  // 이전 단계 값 저장

void setup() {
  Serial.begin(9600);
  // 동적 배열 할당
  derivatives = new float[differentiationCount + 1];
  previousValues = new float[differentiationCount + 1];

  for (int i = 0; i <= differentiationCount; i++) {
    derivatives[i] = 0;
    previousValues[i] = 0;
  }
}

void loop() {
  signalValue = analogRead(pulsePin);
  adjustedSignal = signalValue * gain;

  if (adjustedSignal > 1023) adjustedSignal = 1023;
  if (adjustedSignal < 0) adjustedSignal = 0;

  // 1차 입력값
  derivatives[0] = adjustedSignal;

  // 미분 단계 수행
  for (int i = 1; i <= differentiationCount; i++) {
    derivatives[i] = (derivatives[i - 1] - previousValues[i - 1]) / dt;
    previousValues[i - 1] = derivatives[i - 1];  // 다음 루프를 위한 저장
  }

  // 마지막 미분 결과만 출력
  Serial.println(derivatives[differentiationCount]);

  delay(30);
}

void cleanup() {
  delete[] derivatives;
  delete[] previousValues;
}