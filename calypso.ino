
bool led = true;

bool touch = false;
int counter = 0;

//void sensoresSetup();



void setup() {
  screenTFTsetup();
  sensoresSetup();

  //drawCosas();
}

void loop() {

  unsigned long currentTime = millis();

  check_sensors(currentTime);
  blinkState(currentTime);
  lightDecision();
  salidas();
  //check_screenTouchs();

  //drawCosas(currentTime);

  draw_calypso(currentTime);


}
