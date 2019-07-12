
#define ENA 6
#define IN3 9
#define IN4 11

#define SPEED_TARGET 81
#define SPACER 45
#define STEPPING 1

inline void prepIO() {
  pinMode(IN3, OUTPUT);     //set IO pin mode OUTPUT
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
}

inline void forward1And2() {
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH); 
}

inline void halt1And2() {
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
}

inline void setSpeed(int target, bool killRotation) {
  analogWrite(ENA, 255); // charge caps? (squeals terribly without)
  forward1And2();
  delay(2);
  if (killRotation) {
    halt1And2();
    delay(2);
  }
  analogWrite(ENA, target); // set
}

inline void enableRightSide() {
  digitalWrite(ENA, HIGH); 
  setSpeed(SPEED_TARGET, true);
}

void setup() {
  prepIO();
  enableRightSide();
}

void loop() {
#if STEPPING
  setSpeed(SPEED_TARGET, false);
  forward1And2();
  delay(SPACER);
  halt1And2();
  delay(SPACER);
#else
  forward1And2();
#endif
}
