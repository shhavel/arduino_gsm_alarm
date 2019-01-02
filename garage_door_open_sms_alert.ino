// Send SMS after garage door was opened.
// Use reed switch to monitor door state (open/closed).
#include <GSM.h>
#define REED_SWITCH 6
#define PINNUMBER "" // SIM card PIN
#define RECIPIENT_NUMBER "+380678806519"

GSM gsmAccess; 
GSM_SMS sms;
bool notConnected = true;
bool opened = false;

void setup() {
  pinMode(REED_SWITCH, INPUT);

  while(notConnected) {
    if (gsmAccess.begin(PINNUMBER) == GSM_READY) {
      notConnected = false;
    } else {
      delay(1000);
    }
  }
}

void loop() {
  if (digitalRead(REED_SWITCH) == HIGH) { // the door is closed
    opened = false;
  } else if (!opened) { // the door was just opened (the door is open and previously it was closed)
    opened = true;
    // send SMS
    sms.beginSMS(RECIPIENT_NUMBER);
    sms.print("garage door was open");
    sms.endSMS();
    // 15 minutes break
    delay(900000);
  }
}
