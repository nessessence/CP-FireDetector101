#include <TridentTD_LineNotify.h>  
#include <ESP8266WiFi.h>
// note NodeMCU ESP8266 + MQ2gas sensor(use analog) + IR flame sensor(digital but change the resistance on sensor to appropriate value , because ESP8266 can use only one analog input ) 
#define ssid "nnut98"  //you wifi router
#define pass "nnnnnnutt"  //password of wifi
#define lv1_token "pIdn6hCQwco82zxBozKBxuTvPuc7XWy3pETQXqD45oL"  //Line Notification --> Eng Ess Group  , line token at https://notify-bot.line.me/en/
#define lv2_token "IDouiBxWEXTUhfe06quSpTHIX5Smz630zZM2kniVD2f" // Owen 's Home  --> 911 

TridentTD_LineNotify lv1_ntf(lv1_token);
TridentTD_LineNotify lv2_ntf(lv2_token);  // --> 911

int sensorValue;
int isSmokepin = D0;
int isFlamePin = D1;
int isFlame = HIGH;
int isSmoke = HIGH;


bool DSmoke = 0;
bool DFlame = 0;

void setup() {
  Serial.begin(115200);
  pinMode(isSmokepin, INPUT);
  pinMode(isFlamePin, INPUT);
  
  WiFi.begin(ssid, pass);
  
}

void loop() {
  smokeDetect();
  flameDetect();
  Serial.println(DFlame);
  Serial.println(DSmoke);

   if (DFlame == 1 && DSmoke == 1 ) {
    lv2_ntf.notify(" Hey ! sir , your home is  on fire(flame&smoke detect) ");  //  Messenger to line notification
    lv2_ntf.notifyPicture("http://www.ise.eng.chula.ac.th/images/theme/page/contact/pic-ISE-map-big-new.jpg") ;
    lv1_ntf.notify(" Hey ! sir , your home is  on fire ");
    Serial.println("Warnig, Warning, Warning");
    delay(5000);
  }
  
  else if (DFlame == 0 && DSmoke == 1) {
    lv1_ntf.notify(" Hey ! sir , your home is  on fire(smoke detected) ");  //  Messenger to line notification
    Serial.println("Warning, Warning, Warning");
    delay(5000);
  }
  else if (DFlame == 1 && DSmoke == 0) {
    lv1_ntf.notify(" Hey ! sir , your home is  on fire(flame detected) ");  //  Messenger to line notification
    Serial.println("Warning, Warning, Warning");
    delay(5000);
  }
  delay(2000);
}


void flameDetect() {
  isFlame = digitalRead(isFlamePin);
  if (isFlame == LOW) {
    DFlame = 1;
    Serial.println("FLAME, FLAME, FLAME");
  } else {
    DFlame = 0;
    Serial.println("no flame");
  }
}

void smokeDetect() {
  sensorValue = analogRead(A0);
  Serial.println(sensorValue);
  if (sensorValue > 450) {
    DSmoke = 1;
    Serial.println("SMOKE, SMOKE, SMOKE");
  } else {
    DSmoke = 0;
    Serial.println("NO SMOKE");
  }
}
// note  https://github.com/TridentTD/
