#include <Arduino.h>

#define POT_PIN 34
//#define BUTTON_PIN 21 // GIOP21 pin connected to button
#define RELAY_PIN 26

const int MAX_ANALOG_VAL = 4095;
const int PWM_CHANNEL = 0;
const int PWM_FREQ = 100;
const int PWM_RESOLUTION = 8;

// The max duty cycle value based on PWM resolution (will be 255 if resolution is 8 bits)
const int MAX_DUTY_CYCLE = (int)(pow(2, PWM_RESOLUTION) - 1);

int duty_cycle = 0;
bool is_going_up = true;

int relay_state;
int relay_state_off;
int relay_state_on;

int button_state_off;
int button_state_on;
int button_state; // the current state of button

void on_relay_toggle_normally_closed()
{
  if (relay_state == HIGH)
  {
    relay_state = LOW;
    Serial.println("Current not Flowing");
  }
  if (relay_state == LOW)
  {
    relay_state = HIGH;
    Serial.println("Current Flowing");
  }
  digitalWrite(RELAY_PIN, LOW);
}

void setup()
{
  Serial.begin(115200);

  // potentiometer
  pinMode(POT_PIN, INPUT);

  // configure LED PWM functionalitites
  ledcSetup(PWM_CHANNEL, PWM_FREQ, PWM_RESOLUTION);
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(RELAY_PIN, PWM_CHANNEL);

  // // normally closed relay
  // relay_state_off = LOW;
  // relay_state_on = HIGH;
  // relay_state = relay_state_off;
  // pinMode(RELAY_PIN, OUTPUT);

  // // initialize the pushbutton pin as an pull-up input
  // pinMode(BUTTON_PIN, INPUT_PULLUP);
  // button_state_off = digitalRead(BUTTON_PIN);
  // button_state_on = !button_state_off;
}

void loop_potentiometer()
{
  int potVal = analogRead(POT_PIN);
  duty_cycle = map(potVal, 0, MAX_ANALOG_VAL, 0, MAX_DUTY_CYCLE);
  ledcWrite(PWM_CHANNEL, duty_cycle);

  Serial.println((String)potVal + ", " + duty_cycle);

  delay(10);
}

void loop()
{
  loop_potentiometer();
}

// void loop_button()
// {
//   button_state = digitalRead(BUTTON_PIN);
//   if (button_state == button_state_on)
//   {
//     if (is_going_up)
//     {
//       Serial.print("going up");
//       // GOING UP
//       duty_cycle++;
//       if (duty_cycle == 255)
//       {
//         is_going_up = false;
//         ledcWrite(ledChannel, 0);
//         delay(500);
//       }
//     }
//     else
//     {
//       Serial.print("going down");
//       duty_cycle--;
//       if (duty_cycle == 0)
//       {
//         is_going_up = true;
//       }
//     }
//     ledcWrite(ledChannel, duty_cycle);
//     delay(15);
//   };

// button_state = digitalRead(BUTTON_PIN);
// if (button_state == button_state_off)
// {
//   Serial.println("Current Stopped");
//   digitalWrite(RELAY_PIN, relay_state_off);
// }
// if (button_state == button_state_on)
// {
//   Serial.println("Current Flowing");
//   digitalWrite(RELAY_PIN, relay_state_on);
// }
//}
