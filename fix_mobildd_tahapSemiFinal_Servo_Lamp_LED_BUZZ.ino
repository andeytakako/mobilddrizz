/*
   Gamepad module provides three different mode namely Digital, JoyStick and Accerleometer.

   You can reduce the size of library compiled by enabling only those modules that you want to
   use. For this first define CUSTOM_SETTINGS followed by defining INCLUDE_modulename.

   Explore more on: https://thestempedia.com/docs/dabble/game-pad-module/
*/
#include <DabbleESP32.h>
#include <ESP32Servo.h>
//#include <FastLED.h>
#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#define LAMPUA 25
#define LAMPUB 26
#define SOUND_SPEED 0.017
#define pinservo 33
//#define NUM_LEDS 8
//#define LED_PIN 12
#define melodi 14




//CRGB leds[NUM_LEDS];
Servo servo;
int ENA = 27;
int IN1 = 16;
int IN2 = 17;
int speedK=1;
int data = 0;
const int frequency = 500;
const int pwm_channel = 0;
const int resolution = 8;
int pwm_speed = 180;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);       // make sure your Serial Monitor is also set at this baud rate.
  Dabble.begin("MobilKOKO64");  //set bluetooth name of your device
  pinMode(LAMPUA, OUTPUT);
  pinMode(LAMPUB, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(melodi, OUTPUT);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(LAMPUA, LOW);
  digitalWrite(LAMPUB, LOW);
  //FastLED.addLeds<WS2812, LED_PIN, RGB>(leds, NUM_LEDS);
  ledcSetup(pwm_channel, frequency, resolution);
  ledcAttachPin(ENA, pwm_channel);
  servo.attach(pinservo);
  servo.write(45);  //tengah 45 //0 kanan // 90 kiri
  firstled();


}

void loop() {
  Dabble.processInput();  //this function is used to refresh data obtained from smartphone.Hence calling this function is mandatory in order to get data properly from your mobile.
  Serial.print("KeyPressed: ");
  if (GamePad.isTrianglePressed()) {
    Serial.print("Triangle");
    lampudepan();
  }
  if (GamePad.isSquarePressed())
  {
    Serial.print("Square");
    speedK -=1;
    if(speedK<=1) speedK = 1;
    ledspeed();
    delay(300);
  }

  if (GamePad.isCirclePressed())
  {
    Serial.print("Circle");
    speedK +=1;
    if(speedK>=4) speedK = 4;
    ledspeed();
    delay(300);
  }
  if (GamePad.isUpPressed()) {
    Serial.print("Up");
    servo.write(45);
    delay(500);
    Serial.print(servo.read());
  }
  if (GamePad.isLeftPressed() && GamePad.isCrossPressed()) {
    kiri();
    maju();
    delay(200);
  }
  if (GamePad.isRightPressed() && GamePad.isCrossPressed()) {
    kanan();
    maju();
    delay(200);
  }
  if (GamePad.isLeftPressed()) {
    Serial.print("Left");
    kiri();
  }

  if (GamePad.isRightPressed()) {
    kanan();
  }

  if (GamePad.isCrossPressed()) {
    maju();
    autotengah();
  }

  if (GamePad.isDownPressed()) {
    Serial.print("Down");
    mundur();
  }

  if (!GamePad.isDownPressed() && !GamePad.isCrossPressed()) {
    stop();
  }
  Serial.print('\t');

  int a = GamePad.getAngle();
  Serial.print("Angle: ");
  Serial.print(a);
  Serial.print('\t');
  int b = GamePad.getRadius();
  Serial.print("Radius: ");
  Serial.print(b);
  Serial.print('\t');
  float c = GamePad.getXaxisData();
  Serial.print("x_axis: ");
  Serial.print(c);
  Serial.print('\t');
  float d = GamePad.getYaxisData();
  Serial.print("y_axis: ");
  Serial.println(d);
  Serial.println();
}

void firstled(){
  for (int i=0;i<8;i++){
    digitalWrite(melodi, HIGH);
    delay(100);
    digitalWrite(melodi, LOW);
  }
  /*
  for(int i=0;i<8;i++){
    leds[i] = CRGB::Red;
    FastLED.show();
    digitalWrite(melodi, HIGH);
    delay(100);
    leds[i] = CRGB::Black;
    FastLED.show();
    digitalWrite(melodi, LOW);
    delay(100);

  }
  for(int i=0;i<8;i++){
    leds[i] = CRGB::White;
    FastLED.show();
    delay(100);
  }
  for(int i=0;i<8;i++){
    leds[i] = CRGB::Black;
    FastLED.show();
    delay(100);
  }
  */
}
void ledspeed(){
  //String pointers[] = { "Green", "Yellow",  "Red","White"};
  if(speedK==1){
    digitalWrite(melodi, HIGH);
    delay(100);
    digitalWrite(melodi, LOW);
  }
  if(speedK==2){
    for(int i=0;i<speedK;i++){
      digitalWrite(melodi, HIGH);
      delay(100);
      digitalWrite(melodi, LOW);
    }
  }
  if(speedK==3){
    for(int i=0;i<speedK;i++){
      digitalWrite(melodi, HIGH);
      delay(100);
      digitalWrite(melodi, LOW);
    }
  }
  if(speedK==4){
    for(int i=0;i<speedK;i++){
      digitalWrite(melodi, HIGH);
      delay(100);
      digitalWrite(melodi, LOW);
    }
  }
  /*
  for(int i=0;i<8;i++){
    digitalWrite(melodi, HIGH);
    if(speedK==1) leds[i] = CRGB::Green;
    else if(speedK==2) leds[i] = CRGB::Yellow;
    else if(speedK==3) leds[i] = CRGB::Red;
    else if(speedK==4) leds[i] = CRGB::White;
    else leds[i] = CRGB::Black;
    FastLED.show();
    delay(500);
    digitalWrite(melodi, LOW);
  }
  */
}

int speedMax(int num){
  int speedmax;
  if(num==1){
    speedmax = 255;
  }
  else if(num==2){
    speedmax = 400;
  }
  else if(num==3){
    speedmax = 700;
  }
  else if(num==4){
    speedmax = 1020;
  }
  return speedmax;

}
void lampudepan() {
  Serial.print("Data1 : ");
  Serial.print(data);
  delay(100);
  if(data==0){
    digitalWrite(melodi, HIGH);
    digitalWrite(LAMPUA, HIGH);
    digitalWrite(LAMPUB, HIGH);
    delay(100);
    data = 1;
    Serial.print("Data2 : ");
    Serial.print(data);
    digitalWrite(melodi, LOW);
    return;
  }
  if(data==1){
    digitalWrite(melodi, HIGH);
    digitalWrite(LAMPUA, LOW);
    digitalWrite(LAMPUB, LOW);
    delay(100);
    data = 0;
    Serial.print("Data2 : ");
    Serial.print(data);
    digitalWrite(melodi, LOW);
    return;
  }
}

void kiri() {
  digitalWrite(melodi, HIGH);
  int data = servo.read();
  int i = data;
  i += 22;
  if (i >= 90) i = 90;
  servo.write(i);
  delay(300);
  digitalWrite(melodi, LOW);
}

void kanan() {
  digitalWrite(melodi, HIGH);
  int data = servo.read();
  int i = data;
  i -= 22;
  if (i <= 0) i = 0;
  servo.write(i);
  delay(300);
  digitalWrite(melodi, LOW);
}

void autotengah() {
  
  int data = servo.read();
  if (data > 50) {
    delay(250);
    int i = data;
    i -= 22;
    if (i <= 45) i = 45;
    servo.write(i);
    delay(200);
  }
  else if (data < 40) {
    delay(250);
    int i = data;
    i += 22;
    if (i >= 45) i = 45;
    servo.write(i);
    delay(200);
  }
}

void stop() {
  digitalWrite(melodi, LOW);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  ledcWrite(pwm_channel, 0);
  pwm_speed = 180;
}

void maju() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  for (int i = pwm_speed; i <= speedMax(speedK); i++) {
    pwm_speed = i;
    ledcWrite(pwm_channel, pwm_speed);
  }
}

void mundur() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  for (int i = pwm_speed; i <= speedMax(speedK); i++) {
    pwm_speed = i;
    ledcWrite(pwm_channel, pwm_speed);
  }
}