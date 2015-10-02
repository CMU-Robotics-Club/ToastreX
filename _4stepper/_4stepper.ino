const int c1_pattern[4] = {LOW, HIGH, HIGH, LOW};
const int c2_pattern[4] = {HIGH, HIGH, LOW, LOW};

class ScannerStepper {
  const int c1, c2;//control pins 
  int ticks, pause;
  
  void busy_delay() {
    for (int i = 0; i < (pause >> 2); i++)
      delayMicroseconds(4000);
    for (int i = 0; i < (pause & 0x3); i++)
      delayMicroseconds(1000);
  }
  
  void update_pins() {
    digitalWrite(c1, c1_pattern[ticks & 0x3]);
    digitalWrite(c2, c2_pattern[ticks & 0x3]);
    busy_delay();
  }
    
public:
  ScannerStepper(int p1, int p2, int ms=1) 
   :c1(p1), c2(p2), pause(ms), ticks(0) {
    pinMode(c1, OUTPUT);
    pinMode(c2, OUTPUT);
    update_pins();
  }
  
  void step() {
    ticks++;
    update_pins();
  }
  
  void step_backward() {
    ticks--;
    update_pins();
  }
  
  void step(int n) {
    while (n > 0) {
      this->step();
      n--;
    }
    while (n < 0) {
      this->step_backward();
      n++;
    }
  }
  
  void set_step_time(int ms) {
    this->pause = ms;
  }
};

ScannerStepper tray = ScannerStepper(8, 9);
void setup() {
  //Serial.begin(9600);
  tray.set_step_time(1);
  // yay clean code
}

void loop() {
  tray.step(-1000);
  tray.step(-1000);
}
