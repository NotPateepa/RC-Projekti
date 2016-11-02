#define pin_ping 4
#define pin_led 13

volatile int pwm_value = 0;
volatile int prev_time = 0;
volatile int ping_time = 0;
volatile boolean state_ping = false;

void setup() 
{
  Serial.begin(115200);
  // when pin D2 goes high, call the rising function
  attachInterrupt(1, rising, RISING);
  pinMode(pin_led, OUTPUT);
  pinMode(pin_ping, OUTPUT);
}
 
void loop() 
{
  if (ping_time + 1000 > micros())
  {
    state_ping = !state_ping;
    digitalWrite(pin_ping. state_ping);
    ping_time = micros();
  }
}
 
void rising() 
{
  attachInterrupt(1, falling, FALLING);
  prev_time = micros();
}
 
void falling()  
{
  attachInterrupt(1, rising, RISING);
  pwm_value = micros() - prev_time;
  Serial.println(pwm_value);
  
  if (pwm_value > 1800) 
  {
    digitalWrite(pin_led, LOW);
  }
  else if (pwm_value < 1200)
  {
    digitalWrite(pin_led, HIGH);
  }
}
