#define DANGER 13
#define SAVE 11

int pinAmount = 5;
int pins[] = {5, 6, 7, 8, 9};
int opened = 0;
int explode = 0;
int hacked = 0;
unsigned long time;

void setup() {
  opened = 0;
  explode = 0;
  hacked = 0;
  pinMode(DANGER, OUTPUT);
  pinMode(SAVE, OUTPUT);
  Serial.begin(9600);
  
  digitalWrite(DANGER, LOW);
  digitalWrite(SAVE, LOW);
  
  int i;
  for (i = 0; i < pinAmount; i = i + 1) {
     pinMode(i, INPUT);
  }
  delay(10);
  for (i = 0; i < pinAmount; i = i + 1) {
    if(digitalRead(pins[i]) == 0) {
      explode = 1;
      Serial.print(0);
    } else {
      Serial.print(1);
    }
  }
  Serial.println(" Start");
}

void loop() {
  if(explode == 0) {
    if(hacked == 0) {
      int n = opened;
      int i;
      for (i = 0; i < pinAmount; i = i + 1) {
        if(digitalRead(pins[i]) == 1) {
          Serial.print(1);
          
          if(i + 1 < opened) {
            // was al open geweest en mocht niet weer dicht
            explode = 1;
          }
        } else {
          Serial.print(0);
          if(i == opened) {
            // juiste in de volgorde is nu open
            n = i + 1;
          } else if(i > opened) {
            // deze mocht nog niet open
            explode = 1;
            Serial.println(" Explode");
          }
        }
      }
      Serial.println("");
      opened = n;
      
      if(opened == pinAmount) {
        hacked = 1;
        Serial.println("Hacked");
        digitalWrite(DANGER, LOW);
        digitalWrite(SAVE, HIGH);
      } else {
        // knipperen
        time = millis();
        if((time/500)%2) {
          digitalWrite(SAVE, HIGH);
        } else {
          digitalWrite(SAVE, LOW);
        }
      }
    }
  } else {
    digitalWrite(DANGER, HIGH);
    digitalWrite(SAVE, LOW);
  }
  
  // elke 50 ms opnieuw checken
  delay(50);
}
