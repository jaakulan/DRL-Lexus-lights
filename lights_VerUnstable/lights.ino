#include <FastLED.h>
#include<SoftwareSerial.h>

#define NUM_LEDS 59          // how many lights the strip has
#define DATA_PIN1 7          //light strip connected to data pin 7
#define DATA_PIN2 4          //light strip connected to data pin 4

CRGB leds1[NUM_LEDS];         //led array
CRGB leds2[NUM_LEDS];
SoftwareSerial btSerial(10, 11);        // Tx pin of the bluetooth module must be connected to Rx pin on arduino ((((on arduinio(tx,rx)
                                        // Rx pin of the bluetooth module must be connected to Tx pin on arduino

int color;
int offset =20;
String col_val = "so";
String old_data = "so";
String turn_val = "lc";


void TwinkleRandom(int Count, int SpeedDelay, boolean OnlyOne);
void setPixel(int Pixel, byte red, byte green, byte blue);
void BouncingColoredBalls(int BallCount, byte colors[][3], boolean continuous);
void Fire(int Cooling, int Sparking, int SpeedDelay);
void meteorRain(byte red, byte green, byte blue, byte meteorSize, byte meteorTrailDecay, boolean meteorRandomDecay, int SpeedDelay);
void rainbowCycle(int SpeedDelay);
void fill_color(String col_val);
void start_up();

                                        
void setup() {
  // put your setup code here, to run once:
  
  FastLED.addLeds<WS2812, DATA_PIN1, GRB>(leds1, NUM_LEDS);   //adds the type/# of leds and where the data for them are stores
  FastLED.addLeds<WS2812, DATA_PIN2, GRB>(leds2, NUM_LEDS);
  Serial.begin(9600);
  btSerial.begin(9600);                                       //start communication with bluetooth module
  start_up();
}

void loop() {
  
  // voltage equations
  int right_turn = analogRead(A0);// read the input
  int left_turn = analogRead(A1);
  double right_voltage = map(right_turn,0,1023, 0, 2500) + offset;// map 0-1023 to 0-2500 and add correction offset
  double left_voltage = map(left_turn,0,1023, 0, 2500) + offset;// map 0-1023 to 0-2500 and add correction offset
  right_voltage /=100;// divide by 100 to get the decimal values
  left_voltage /=100;
  
  if(right_voltage > 1.5 || left_voltage > 1.5){
  if(right_voltage > 1.5 && left_voltage > 1.5){
    while(right_voltage > 1.5 && left_voltage > 1.5){
      turn_signal(turn_val, 0);
      right_turn = analogRead(A0);
      right_voltage = map(right_turn,0,1023, 0, 2500) + offset;
      right_voltage /=100;
      left_turn = analogRead(A1);
      left_voltage = map(left_turn,0,1023, 0, 2500) + offset;
      left_voltage /=100;
    }
  }
  else if(right_voltage > 1.5){
    while(right_voltage > 1.5 && left_voltage < 1.5){
      turn_signal(turn_val, 1);
      right_turn = analogRead(A0);
      right_voltage = map(right_turn,0,1023, 0, 2500) + offset;
      right_voltage /=100;
      left_turn = analogRead(A1);
      left_voltage = map(left_turn,0,1023, 0, 2500) + offset;
      left_voltage /=100;
    }
  }
  else if(left_voltage > 1.5){
    while(left_voltage > 1.5 && right_voltage < 1.5){
      turn_signal(turn_val, 2);
      left_turn = analogRead(A1);
      left_voltage = map(left_turn,0,1023, 0, 2500) + offset;
      left_voltage /=100;
      right_turn = analogRead(A0);
      right_voltage = map(right_turn,0,1023, 0, 2500) + offset;
      right_voltage /=100;
    }
  }
  fill_color(col_val);
  }

  //bluetooth input checker
  if(btSerial.available()){
    col_val = btSerial.readStringUntil('\n');
    Serial.println(col_val);
  }

    if(col_val == "af"){
      fill_solid(leds1, NUM_LEDS, CRGB(255, 255,0));
      fill_solid(leds2, NUM_LEDS, CRGB(255, 255,0));
      Fire(55,120,30);
    }
    else if(col_val == "am"){
      meteorRain(0xff,0xff,0xff,10, 64, true, 50);
    }
    else if(col_val == "ar"){
      rainbowCycle(20);
    }
    else if(col_val == "as"){
      TwinkleRandom(12, 100, false);
    }
    else if(col_val == "ab"){
      byte colors[3][3] = { {0xff, 0x00, 0x00}, 
                                      {0xff, 0xff, 0xff}, 
                                      {0x00, 0x00, 0xff} };
      BouncingColoredBalls(3, colors, false);
    }
    else if(col_val == "ac"){
      fill_solid(leds1, NUM_LEDS, CRGB(0,0,255));
      fill_solid(leds2, NUM_LEDS, CRGB(255,0,0));
      FastLED.show();
      delay(190);
      fill_solid(leds1, NUM_LEDS, CRGB(0,0,0));
      fill_solid(leds2, NUM_LEDS, CRGB(0,0,0));
      FastLED.show();
      delay(60);
      fill_solid(leds1, NUM_LEDS, CRGB(0,0,255));
      fill_solid(leds2, NUM_LEDS, CRGB(255,0,0));
      FastLED.show();
      delay(190);
      fill_solid(leds1, NUM_LEDS, CRGB(0,0,0));
      fill_solid(leds2, NUM_LEDS, CRGB(0,0,0));
      FastLED.show();
      delay(60);
      fill_solid(leds1, NUM_LEDS, CRGB(255,0,0));
      fill_solid(leds2, NUM_LEDS, CRGB(0,0,255));
      FastLED.show();
      delay(160);
      fill_solid(leds1, NUM_LEDS, CRGB(0,0,255));
      fill_solid(leds2, NUM_LEDS, CRGB(255,0,0));
      FastLED.show();
      delay(160);
      fill_solid(leds1, NUM_LEDS, CRGB(255,0,0));
      fill_solid(leds2, NUM_LEDS, CRGB(0,0,255));
      FastLED.show();
      delay(160);
      fill_solid(leds1, NUM_LEDS, CRGB(0,0,255));
      fill_solid(leds2, NUM_LEDS, CRGB(255,0,0));
      FastLED.show();
      delay(160);
      fill_solid(leds1, NUM_LEDS, CRGB(255,0,0));
      fill_solid(leds2, NUM_LEDS, CRGB(0,0,255));
      FastLED.show();
      delay(160);
      fill_solid(leds1, NUM_LEDS, CRGB(0,0,255));
      fill_solid(leds2, NUM_LEDS, CRGB(255,0,0));
      FastLED.show();
      delay(190);
      fill_solid(leds1, NUM_LEDS, CRGB(0,0,0));
      fill_solid(leds2, NUM_LEDS, CRGB(0,0,0));
      FastLED.show();
      delay(60);
      fill_solid(leds1, NUM_LEDS, CRGB(0,0,255));
      fill_solid(leds2, NUM_LEDS, CRGB(255,0,0));
      FastLED.show();
      delay(190);
    }
    else if(col_val == "li"||col_val == "lb"||col_val == "lf"||col_val == "lc"||col_val == "lm"||col_val == "ls"||col_val == "lq"){
      turn_signal(col_val,0);
      col_val = old_data;
      fill_color(col_val);
    }
    
    
    if(col_val != old_data){
      fill_color(col_val);
      old_data = col_val;
    }
    
 }
 
void start_up(){
  fill_solid(leds1, NUM_LEDS, CRGB(255,0,0));
  fill_solid(leds2, NUM_LEDS, CRGB(255,0,0));
  FastLED.show();
  delay(200);
  fill_solid(leds1, NUM_LEDS, CRGB(255,92,0));
  fill_solid(leds2, NUM_LEDS, CRGB(255,92,0));
  FastLED.show();
  delay(200);
  fill_solid(leds1, NUM_LEDS, CRGB(255,255,0));
  fill_solid(leds2, NUM_LEDS, CRGB(255,255,0));
  FastLED.show();
  delay(200);
  fill_solid(leds1, NUM_LEDS, CRGB(0,255,0));
  fill_solid(leds2, NUM_LEDS, CRGB(0,255,0));
  FastLED.show();
  delay(200);
  fill_solid(leds1, NUM_LEDS, CRGB(0,0,255));
  fill_solid(leds2, NUM_LEDS, CRGB(0,0,255));
  FastLED.show();
  delay(200);
  fill_solid(leds1, NUM_LEDS, CRGB(127,0,255));
  fill_solid(leds2, NUM_LEDS, CRGB(127,0,255));
  FastLED.show();
  delay(200);
  fill_solid(leds1, NUM_LEDS, CRGB(255,0,0));
  fill_solid(leds2, NUM_LEDS, CRGB(255,0,0));
  FastLED.show();
  delay(200);
  fill_solid(leds1, NUM_LEDS, CRGB(255,92,0));
  fill_solid(leds2, NUM_LEDS, CRGB(255,92,0));
  FastLED.show();
  delay(200);
  fill_solid(leds1, NUM_LEDS, CRGB(255,255,0));
  fill_solid(leds2, NUM_LEDS, CRGB(255,255,0));
  FastLED.show();
  delay(200);
  fill_solid(leds1, NUM_LEDS, CRGB(0,255,0));
  fill_solid(leds2, NUM_LEDS, CRGB(0,255,0));
  FastLED.show();
  delay(200);
  fill_solid(leds1, NUM_LEDS, CRGB(0,0,255));
  fill_solid(leds2, NUM_LEDS, CRGB(0,0,255));
  FastLED.show();
  delay(200);
  fill_solid(leds1, NUM_LEDS, CRGB(255,92,0));
  fill_solid(leds2, NUM_LEDS, CRGB(255,92,0));
  FastLED.show();
}

void turn_signal(String col_val, int turn){
    if(col_val == "li"){
      load_in(turn);
      turn_val = "li";
    }
    else if(col_val == "lb"){
      blinker(turn);
      turn_val = "lb";
    }
    else if(col_val == "lf"){
      fade_sequ(turn);
      turn_val = "lf";
    }
    else if(col_val == "lm"){
      cm(turn);
      turn_val = "lm";
    }
    else if(col_val == "ls"){
      sequential(turn);
      turn_val = "ls";
    }
    else if(col_val == "lq"){
      if(turn == 1){
      fill_solid(leds1, NUM_LEDS, CRGB(255, 102,0));
      FastLED.show();
      }
      if(turn == 2){
      fill_solid(leds2, NUM_LEDS, CRGB(255, 102,0));
      FastLED.show();
      }
      if(turn == 0){
      fill_solid(leds1, NUM_LEDS, CRGB(255, 102,0));
      fill_solid(leds2, NUM_LEDS, CRGB(255, 102,0));
      FastLED.show();
      }
      turn_val = "lq";
    }
    else if(col_val == "lc"){
      inv_cm(turn);
      turn_val = "lc";
    }
}

void fill_color(String col_val){
  
  //off
  if(col_val == "sO")
  {
    fill_solid(leds1, NUM_LEDS, CRGB(0,0,0));
    fill_solid(leds2, NUM_LEDS, CRGB(0,0,0));
    FastLED.show();
  }
  else if(col_val == "sw")
  {
    fill_solid(leds1, NUM_LEDS, CRGB(255,255,255));
    fill_solid(leds2, NUM_LEDS, CRGB(255,255,255));
    FastLED.show();
  }
  else if(col_val == "so") {
    fill_solid(leds1, NUM_LEDS, CRGB(255,92,0)); 
    fill_solid(leds2, NUM_LEDS, CRGB(255,92,0)); 
    FastLED.show();
  }
  else if(col_val == "sr") {
    fill_solid(leds1, NUM_LEDS, CRGB(255,0,0));
    fill_solid(leds2, NUM_LEDS, CRGB(255,0,0));
    FastLED.show();
  }
  else if(col_val == "sb") {
    fill_solid(leds1, NUM_LEDS, CRGB(0,0,255));
    fill_solid(leds2, NUM_LEDS, CRGB(0,0,255));
    FastLED.show();
  }
  else if(col_val == "sg") {
    fill_solid(leds1, NUM_LEDS, CRGB(0,255,0));
    fill_solid(leds2, NUM_LEDS, CRGB(0,255,0));
    FastLED.show();
  }
  else if(col_val == "su") {
    fill_solid(leds1, NUM_LEDS, CRGB(85,28,0));
    fill_solid(leds2, NUM_LEDS, CRGB(85,28,0));
    FastLED.show();
  }
  else if(col_val == "sy") {
    fill_solid(leds1, NUM_LEDS, CRGB(255,255,0)); 
    fill_solid(leds2, NUM_LEDS, CRGB(255,255,0)); 
    FastLED.show();
  }
  else if(col_val == "sp") {
    fill_solid(leds1, NUM_LEDS, CRGB(127,0,255));
    fill_solid(leds2, NUM_LEDS, CRGB(127,0,255));
    FastLED.show();
  }
  else if(col_val == "sf") {
    fill_solid(leds1, NUM_LEDS, CRGB(255,51,255));
    fill_solid(leds2, NUM_LEDS, CRGB(255,51,255));
    FastLED.show();
  }
  else if(col_val == "sP") {
    fill_solid(leds1, NUM_LEDS, CRGB(255,100,255));
    fill_solid(leds2, NUM_LEDS, CRGB(255,100,255));
    FastLED.show();
  }
  else if(col_val == "st") {
    fill_solid(leds1, NUM_LEDS, CRGB(64,244,208));
    fill_solid(leds2, NUM_LEDS, CRGB(64,244,208));
    FastLED.show();
  }
  else if(col_val == "sG") {
    fill_solid(leds1, NUM_LEDS, CRGB(255,100,0));
    fill_solid(leds2, NUM_LEDS, CRGB(255,100,0));
    FastLED.show();
  }
  else if(col_val == "sl") {
    fill_solid(leds1, NUM_LEDS, CRGB(51,255,51));
    fill_solid(leds2, NUM_LEDS, CRGB(51,255,51));
    FastLED.show();
  }
  else if(col_val == "sc") {
    fill_solid(leds1, NUM_LEDS, CRGB(255,126,84));
    fill_solid(leds2, NUM_LEDS, CRGB(255,126,84));
    FastLED.show();
  }
  else if(col_val == "sB") {
    fill_solid(leds1, NUM_LEDS, CRGB(89,60,31));
    fill_solid(leds2, NUM_LEDS, CRGB(89,60,31));
    FastLED.show();
  }
  
}

void blinker(int turn){
  
  if(turn == 1){
  fill_solid(leds1, NUM_LEDS, CRGB(0,0,0));
  FastLED.show();
  delay(500);
  fill_solid(leds1, NUM_LEDS, CRGB(255,102,0));
  FastLED.show();
  delay(500);
  fill_solid(leds1, NUM_LEDS, CRGB(0,0,0));
  FastLED.show();
  delay(500);
  fill_solid(leds1, NUM_LEDS, CRGB(255,102,0));
  FastLED.show();
  delay(500);
  }
  else if(turn == 2){
  fill_solid(leds2, NUM_LEDS, CRGB(0,0,0));
  FastLED.show();
  delay(500);
  fill_solid(leds2, NUM_LEDS, CRGB(255,102,0));
  FastLED.show();
  delay(500);
  fill_solid(leds2, NUM_LEDS, CRGB(0,0,0));
  FastLED.show();
  delay(500);
  fill_solid(leds2, NUM_LEDS, CRGB(255,102,0));
  FastLED.show();
  delay(500);
  }
  else{
  fill_solid(leds1, NUM_LEDS, CRGB(0,0,0));
  fill_solid(leds2, NUM_LEDS, CRGB(0,0,0));
  FastLED.show();
  delay(500);
  fill_solid(leds1, NUM_LEDS, CRGB(255,102,0));
  fill_solid(leds2, NUM_LEDS, CRGB(255,102,0));
  FastLED.show();
  delay(500);
  fill_solid(leds1, NUM_LEDS, CRGB(0,0,0));
  fill_solid(leds2, NUM_LEDS, CRGB(0,0,0));
  FastLED.show();
  delay(500);
  fill_solid(leds1, NUM_LEDS, CRGB(255,102,0));
  fill_solid(leds2, NUM_LEDS, CRGB(255,102,0));
  FastLED.show();
  delay(500);
  }
}

void cm(int turn){
  
  if(turn == 1){
  CRGB temp;
  int i;

  for(i=0;i<NUM_LEDS;i++){
    leds1[i] = CRGB(255,102,0);
    FastLED.show();
  }
  
  for(i=0;i<9;i++){
    leds1[i] = CRGB(0,0,0);
    FastLED.show();
    delay(30);
  }
  
  for(int j=0;j<NUM_LEDS-10;j++){
    temp=leds1[NUM_LEDS-1];
    for(i=NUM_LEDS-1;i>0;i--)
    {
        leds1[i]=leds1[i-1];
    }
   leds1[0]=temp;
   FastLED.show();
   delay(30);
  }
  }
  else if(turn == 2){
  CRGB temp;
  int i;
  for(i=0;i<NUM_LEDS;i++){
    leds2[i] = CRGB(255,102,0);
    FastLED.show();
  }
  
  for(i=0;i<9;i++){
    leds2[i] = CRGB(0,0,0);
    FastLED.show();
    delay(30);
  }
  
  for(int j=0;j<NUM_LEDS-10;j++){
    temp=leds2[NUM_LEDS-1];
    for(i=NUM_LEDS-1;i>0;i--)
    {
        leds2[i]=leds2[i-1];
    }
   leds2[0]=temp;
   FastLED.show();
   delay(30);
  }
  }
  else{
  CRGB temp;
  int i;

  for(i=0;i<NUM_LEDS;i++){
    leds1[i] = CRGB(255,102,0);
    leds2[i] = CRGB(255,102,0);
    FastLED.show();
  }
  
  for(i=0;i<9;i++){
    leds1[i] = CRGB(0,0,0);
    leds2[i] = CRGB(0,0,0);
    FastLED.show();
    delay(30);
  }
  
  for(int j=0;j<NUM_LEDS-10;j++){
    temp=leds1[NUM_LEDS-1];
    for(i=NUM_LEDS-1;i>0;i--)
    {
        leds1[i]=leds1[i-1];
        leds2[i]=leds1[i-1];
    }
   leds1[0]=temp;
   leds2[0]=temp;
   FastLED.show();
   delay(30);
  }
  }
  
}


void fade_sequ(int turn){
  int i,j,r,g,k;
  float e;

  if (turn == 1){
  fill_solid(leds1, NUM_LEDS, CRGB(0,0,0));
  FastLED.show();
    delay(40);
  for(int i=0;i<NUM_LEDS;i++){
    leds1[i] = CRGB(255,102,0);
    for(j=i;j>0;j--){
        e=pow(0.75, i-j);
        r=round(255*e);
        g=round(102*e);
        leds1[j] = CRGB(r,g,0);
        if(r<4 && g<2){
          leds1[j] = CRGB(0,0,0);
        }
    }
    leds1[0] = CRGB(0,0,0);
    FastLED.show();
    delay(25);
  }
  }
  else if(turn ==2){
  fill_solid(leds2, NUM_LEDS, CRGB(0,0,0));
  FastLED.show();
    delay(40);
  for(int i=0;i<NUM_LEDS;i++){
    leds2[i] = CRGB(255,102,0);
    for(j=i;j>0;j--){
        e=pow(0.75, i-j);
        r=round(255*e);
        g=round(102*e);
        leds2[j] = CRGB(r,g,0);
        if(r<4 && g<2){
          leds2[j] = CRGB(0,0,0);
        }
    }
    leds2[0] = CRGB(0,0,0);
    FastLED.show();
    delay(25);
  }
  }
  else{
  fill_solid(leds1, NUM_LEDS, CRGB(0,0,0));
  fill_solid(leds2, NUM_LEDS, CRGB(0,0,0));
  FastLED.show();
    delay(40);
  for(int i=0;i<NUM_LEDS;i++){
    leds1[i] = CRGB(255,102,0);
    leds2[i] = CRGB(255,102,0);
    for(j=i;j>0;j--){
        e=pow(0.75, i-j);
        r=round(255*e);
        g=round(102*e);
        leds1[j] = CRGB(r,g,0);
        leds2[j] = CRGB(r,g,0);
        if(r<4 && g<2){
          leds1[j] = CRGB(0,0,0);
          leds2[j] = CRGB(0,0,0);
        }
    }
    leds1[0] = CRGB(0,0,0);
    leds2[0] = CRGB(0,0,0);
    FastLED.show();
    delay(25);
  }
  }

}

void inv_cm(int turn){
  
  if(turn == 1){
  CRGB temp;
  int i;

  for(i=0;i<NUM_LEDS;i++){
    leds1[i] = CRGB(0,0,0);
    FastLED.show();
  }
  
  for(i=0;i<9;i++){
    leds1[i] = CRGB(255,102,0);
    FastLED.show();
    delay(20);
  }
  
  for(int j=0;j<NUM_LEDS-10;j++){
    temp=leds1[NUM_LEDS-1];
    for(i=NUM_LEDS-1;i>0;i--)
    {
        leds1[i]=leds1[i-1];
    }
   leds1[0]=temp;
   FastLED.show();
   delay(20);
  }
  }
  else if(turn == 2){
  CRGB temp;
  int i;
  
  for(i=0;i<NUM_LEDS;i++){
    leds2[i] = CRGB(0,0,0);
    FastLED.show();
  }
  
  for(i=0;i<9;i++){
    leds2[i] = CRGB(255,102,0);
    FastLED.show();
    delay(20);
  }
  
  for(int j=0;j<NUM_LEDS-10;j++){
    temp=leds2[NUM_LEDS-1];
    for(i=NUM_LEDS-1;i>0;i--)
    {
        leds2[i]=leds2[i-1];
    }
   leds2[0]=temp;
   FastLED.show();
   delay(20);
  }
  }
  else{
  CRGB temp;
  int i;

  for(i=0;i<NUM_LEDS;i++){
    leds1[i] = CRGB(0,0,0);
    leds2[i] = CRGB(0,0,0);
    FastLED.show();
  }
  
  for(i=0;i<9;i++){
    leds1[i] = CRGB(255,102,0);
    leds2[i] = CRGB(255,102,0);
    FastLED.show();
    delay(20);
  }
  
  for(int j=0;j<NUM_LEDS-10;j++){
    temp=leds1[NUM_LEDS-1];
    for(i=NUM_LEDS-1;i>0;i--)
    {
        leds1[i]=leds1[i-1];
        leds2[i]=leds1[i-1];
    }
   leds1[0]=temp;
   leds2[0]=temp;
   FastLED.show();
   delay(20);
  }
  }
  
}

void load_in(int turn){
  
  if(turn == 1){
  fill_solid(leds1, NUM_LEDS, CRGB(0,0,0));
  FastLED.show();
    delay(30);
  for(int i=19;i>=0;i--){
    for(int j=0;j<i;j++){
    leds1[j] = CRGB(255,102,0);
    FastLED.show();
    delay(5);
    leds1[j] = CRGB(0,0,0);
    }
    leds1[i] = CRGB(255,102,0);
    FastLED.show();
    delay(5);
  }
  delay(40);
  }
  else if(turn == 2){
  fill_solid(leds2, NUM_LEDS, CRGB(0,0,0));
  FastLED.show();
    delay(30);
  for(int i=19;i>=0;i--){
    for(int j=0;j<i;j++){
    leds2[j] = CRGB(255,102,0);
    FastLED.show();
    delay(5);
    leds2[j] = CRGB(0,0,0);
    }
    leds2[i] = CRGB(255,102,0);
    FastLED.show();
    delay(5);
  }
  delay(40);
  }
  else{
  fill_solid(leds1, NUM_LEDS, CRGB(0,0,0));
  fill_solid(leds2, NUM_LEDS, CRGB(0,0,0));
  FastLED.show();
    delay(30);
  for(int i=19;i>=0;i--){
    for(int j=0;j<i;j++){
    leds1[j] = CRGB(255,102,0);
    leds2[j] = CRGB(255,102,0);
    FastLED.show();
    delay(5);
    leds1[j] = CRGB(0,0,0);
    leds2[j] = CRGB(0,0,0);
    }
    leds1[i] = CRGB(255,102,0);
    leds2[i] = CRGB(255,102,0);
    FastLED.show();
    delay(5);
  }
  delay(40);
  }
  
}

void sequential(int turn){
  
  if(turn == 1){
  fill_solid(leds1, NUM_LEDS, CRGB(0,0,0));
  FastLED.show();
    delay(30);
  for(int i=0;i<NUM_LEDS;i++){
    leds1[i] = CRGB(255,102,0);
    FastLED.show();
    delay(20);
  }
  }
  else if(turn == 2){
  fill_solid(leds2, NUM_LEDS, CRGB(0,0,0));
  FastLED.show();
    delay(30);
  for(int i=0;i<NUM_LEDS;i++){
    leds2[i] = CRGB(255,102,0);
    FastLED.show();
    delay(20);
  }
  }
  else{
  fill_solid(leds1, NUM_LEDS, CRGB(0,0,0));
  fill_solid(leds2, NUM_LEDS, CRGB(0,0,0));
  FastLED.show();
    delay(30);
  for(int i=0;i<NUM_LEDS;i++){
    leds1[i] = CRGB(255,102,0);
    leds2[i] = CRGB(255,102,0);
    FastLED.show();
    delay(20);
  }
  }
}

void BouncingColoredBalls(int BallCount, byte colors[][3], boolean continuous) {
  float Gravity = -9.81;
  int StartHeight = 1;
  
  float Height[BallCount];
  float ImpactVelocityStart = sqrt( -2 * Gravity * StartHeight );
  float ImpactVelocity[BallCount];
  float TimeSinceLastBounce[BallCount];
  int   Position[BallCount];
  long  ClockTimeSinceLastBounce[BallCount];
  float Dampening[BallCount];
  boolean ballBouncing[BallCount];
  boolean ballsStillBouncing = true;
  
  for (int i = 0 ; i < BallCount ; i++) {   
    ClockTimeSinceLastBounce[i] = millis();
    Height[i] = StartHeight;
    Position[i] = 0; 
    ImpactVelocity[i] = ImpactVelocityStart;
    TimeSinceLastBounce[i] = 0;
    Dampening[i] = 0.90 - float(i)/pow(BallCount,2);
    ballBouncing[i]=true; 
  }

  while (ballsStillBouncing) {
    for (int i = 0 ; i < BallCount ; i++) {
      TimeSinceLastBounce[i] =  millis() - ClockTimeSinceLastBounce[i];
      Height[i] = 0.5 * Gravity * pow( TimeSinceLastBounce[i]/1000 , 2.0 ) + ImpactVelocity[i] * TimeSinceLastBounce[i]/1000;
  
      if ( Height[i] < 0 ) {                      
        Height[i] = 0;
        ImpactVelocity[i] = Dampening[i] * ImpactVelocity[i];
        ClockTimeSinceLastBounce[i] = millis();
  
        if ( ImpactVelocity[i] < 0.01 ) {
          if (continuous) {
            ImpactVelocity[i] = ImpactVelocityStart;
          } else {
            ballBouncing[i]=false;
          }
        }
      }
      Position[i] = round( Height[i] * (NUM_LEDS - 1) / StartHeight);
    }

    ballsStillBouncing = false; // assume no balls bouncing
    for (int i = 0 ; i < BallCount ; i++) {
      setPixel(Position[i],colors[i][0],colors[i][1],colors[i][2]);
      if ( ballBouncing[i] ) {
        ballsStillBouncing = true;
      }
    }
    
    FastLED.show();
    fill_solid(leds1, NUM_LEDS, CRGB(0,0,0));
    fill_solid(leds2, NUM_LEDS, CRGB(0,0,0));
  }
}

void Fire(int Cooling, int Sparking, int SpeedDelay) {
  static byte heat[NUM_LEDS];
  int cooldown;
  
  // Step 1.  Cool down every cell a little
  for( int i = 0; i < NUM_LEDS; i++) {
    cooldown = random(0, ((Cooling * 10) / NUM_LEDS) + 2);
    
    if(cooldown>heat[i]) {
      heat[i]=0;
    } else {
      heat[i]=heat[i]-cooldown;
    }
  }
  
  // Step 2.  Heat from each cell drifts 'up' and diffuses a little
  for( int k= NUM_LEDS - 1; k >= 2; k--) {
    heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
  }
    
  // Step 3.  Randomly ignite new 'sparks' near the bottom
  if( random(255) < Sparking ) {
    int y = random(7);
    heat[y] = heat[y] + random(160,255);
    //heat[y] = random(160,255);
  }

  // Step 4.  Convert heat to LED colors
  for( int j = 0; j < NUM_LEDS; j++) {
    setPixelHeatColor(j, heat[j] );
  }

  FastLED.show();
  delay(SpeedDelay);
}


void setPixelHeatColor (int Pixel, byte temperature) {
  // Scale 'heat' down from 0-255 to 0-191
  byte t192 = round((temperature/255.0)*191);
 
  // calculate ramp up from
  byte heatramp = t192 & 0x3F; // 0..63
  heatramp <<= 2; // scale up to 0..252
 
  // figure out which third of the spectrum we're in:
  if( t192 > 0x80) {                     // hottest
    setPixel(Pixel, 255, 255, heatramp);
  } else if( t192 > 0x40 ) {             // middle
    setPixel(Pixel, 255, heatramp, 0);
  } else {                               // coolest
    setPixel(Pixel, heatramp, 0, 0);
  }
}


void meteorRain(byte red, byte green, byte blue, byte meteorSize, byte meteorTrailDecay, boolean meteorRandomDecay, int SpeedDelay) {  
   fill_solid(leds1, NUM_LEDS, CRGB(0,0,0));
   fill_solid(leds2, NUM_LEDS, CRGB(0,0,0));
  
  for(int i = 0; i < NUM_LEDS+NUM_LEDS; i++) {
    
    
    // fade brightness all LEDs one step
    for(int j=0; j<NUM_LEDS; j++) {
      if( (!meteorRandomDecay) || (random(10)>5) ) {
        fadeToBlack(j, meteorTrailDecay );        
      }
    }
    
    // draw meteor
    for(int j = 0; j < meteorSize; j++) {
      if( ( i-j <NUM_LEDS) && (i-j>=0) ) {
        setPixel(i-j, red, green, blue);
      } 
    }
   
    FastLED.show();
    delay(SpeedDelay);
  }
}

void fadeToBlack(int ledNo, byte fadeValue) {
 #ifdef ADAFRUIT_NEOPIXEL_H 
    // NeoPixel
    uint32_t oldColor;
    uint8_t r, g, b;
    int value;
    
    oldColor = strip.getPixelColor(ledNo);
    r = (oldColor & 0x00ff0000UL) >> 16;
    g = (oldColor & 0x0000ff00UL) >> 8;
    b = (oldColor & 0x000000ffUL);

    r=(r<=10)? 0 : (int) r-(r*fadeValue/256);
    g=(g<=10)? 0 : (int) g-(g*fadeValue/256);
    b=(b<=10)? 0 : (int) b-(b*fadeValue/256);
    
    strip.setPixelColor(ledNo, r,g,b);
 #endif
 #ifndef ADAFRUIT_NEOPIXEL_H
   // FastLED
   leds1[ledNo].fadeToBlackBy( fadeValue );
   leds2[ledNo].fadeToBlackBy( fadeValue );
 #endif  
}

void TwinkleRandom(int Count, int SpeedDelay, boolean OnlyOne) {
  fill_solid(leds1, NUM_LEDS, CRGB(0,0,0));
  fill_solid(leds2, NUM_LEDS, CRGB(0,0,0));
  
  for (int i=0; i<Count; i++) {
     setPixel(random(NUM_LEDS),random(0,255),random(0,255),random(0,255));
     FastLED.show();
     delay(SpeedDelay);
     if(OnlyOne) { 
       fill_solid(leds1, NUM_LEDS, CRGB(255,0,0));
       fill_solid(leds2, NUM_LEDS, CRGB(255,0,0));
     }
   }
}

void rainbowCycle(int SpeedDelay) {
  byte *c;
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< NUM_LEDS; i++) {
      c=Wheel(((i * 256 / NUM_LEDS) + j) & 255);
      setPixel(i, *c, *(c+1), *(c+2));
    }
    FastLED.show();
    delay(SpeedDelay);
  }
}

void showStrip() {
   FastLED.show();
}

void setPixel(int Pixel, byte red, byte green, byte blue) {
   leds1[Pixel].r = red;
   leds1[Pixel].g = green;
   leds1[Pixel].b = blue;
   leds2[Pixel].r = red;
   leds2[Pixel].g = green;
   leds2[Pixel].b = blue;
}

void setAll(byte red, byte green, byte blue) {
  for(int i = 0; i < NUM_LEDS; i++ ) {
    setPixel(i, red, green, blue);
  }
  showStrip();
}

byte * Wheel(byte WheelPos) {
  static byte c[3];
  
  if(WheelPos < 85) {
   c[0]=WheelPos * 3;
   c[1]=255 - WheelPos * 3;
   c[2]=0;
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   c[0]=255 - WheelPos * 3;
   c[1]=0;
   c[2]=WheelPos * 3;
  } else {
   WheelPos -= 170;
   c[0]=0;
   c[1]=WheelPos * 3;
   c[2]=255 - WheelPos * 3;
  }

  return c;
}
