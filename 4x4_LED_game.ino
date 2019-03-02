
int inputs[] = { 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37 };
int outputs[] = { 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53 };

int audio = 2;

bool broke = false;
bool start = true;
bool startSettings = false;
bool up;

unsigned long longTimer;
unsigned long wasTimer;

unsigned long timer;
unsigned long remit;
int i = 0;


int but;
int pressBut;

int sucPress = 0;

bool playPerfect;

void setup() {
  for(int i =0; i < 16; i++) {
    pinMode(inputs[i], INPUT);
  }
  for(int i =0; i < 16; i++) {
    pinMode(outputs[i], OUTPUT);
  }
  Serial.begin(9600);
}

void loop() {
  
  longTimer = millis();
  if(wasTimer != longTimer) {
    timer++;
    remit++;
  }

  if(!start) {
    waitForInput();
  } else {
    game();
    if(startSettings == false) {
      timer = 0;
      pressBut = 1;
      but = random(0,15);
      startSettings = true;
      digitalWrite(outputs[but], HIGH);
      win();
    }
  }

  if(i > 14) {
    up = false;
  }
  if(i < 1) {
    up = true;
  }
  if(broke == true) {
    i = 0;
    for(int b = 0; b < 16; b++) {
      digitalWrite(outputs[b], HIGH);
    }
    for(int b = 0; b < 20; b++) {
      tone(audio, 100 * (b / 2), 100);
      delay(20);
    }
    start = true;
    broke = false;
    delay(20);
    for(int b = 0; b < 16; b++) {
      digitalWrite(outputs[b], LOW);
    }
    delay(500);
  }
  wasTimer = longTimer;
}

void waitForInput() {
  startSettings = false;
  if(timer < 500) {
    digitalWrite(outputs[i], HIGH);
    if(digitalRead(inputs[i]) == LOW) {
      broke = true;
      return;
    }
  }
  if(timer > 500) {
    digitalWrite(outputs[i], LOW);
    if(up == true) {
      i++;
    }
    if(up == false){
      i--;
    }
    timer = 0;
  }
}
void game() {

  int scale = sucPress / 5;
  if(scale <= 0) {
    scale = 1;
  }
  
  if(digitalRead(inputs[but]) == LOW && timer <= (1510 / scale)) {
    win();
  }
  if(timer > (1500 / scale)) {
    lose();
  }
}
void win() {
  sucPress+=1;
  timer = 0;
  digitalWrite(outputs[but], LOW);
  tone(audio, 500, 100);
  but = random(0, 15);
  digitalWrite(outputs[but], HIGH);
}
void lose() {
  for(int b = 0; b < 16; b++) {
      digitalWrite(outputs[b], LOW);
  }
  tone(audio, 50, 400);
  delay(500);
  playScore();
}
void playScore() {
  if(sucPress > 17) {
    sucPress = 17;
  }
  for(int b = 0; b < (sucPress - 1); b++) {
    digitalWrite(outputs[b], HIGH);
  }
  tone(audio, 50, 45);
  delay(100);
  tone(audio, 250, 45);
  delay(100);
  tone(audio, 500, 45);
  delay(100);
  tone(audio, 750, 45);
  delay(1000);
  for(int b = 0; b < 16; b++) {
      digitalWrite(outputs[b], LOW);
  }
  sucPress = 0;
  start = false;
  delay(1000);
}
