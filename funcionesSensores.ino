// sensor humedad y temperatura DHT11
#include <Adafruit_Sensor.h>
#include "DHT.h"
#define DHTPIN 12
#define DHTTYPE DHT11

// Umbrales

int umbralHumedadPlant = 9; // < se activa situacion 1
int umbralGas = 30;         // > se activa situacion 2
int umbralLuz1 = 200;       // > se enciende una Luz 
int umbralLuz2 = 400;       // > se encienden dos luces
int umbralLuz3 = 800;       // > se encienden tres Luces
int umbralHumedadAir = 40;  // < se activa situacion 3
int umbralT = 30;           // > se activa situacion 3

int fan1 = 80;
int fan2 = 150;
int fan3 = 255;

const long blinkTime = 4000; // tiempo de parpadeo
const long bigBlinkTime = 20*60*1000; //tiempo que pasa encendida las lamparas
const long sensorTime = 1000;   // tiempo que espera por cada sensor
                                // light lo hace cada vez
                                // los otros lo hace cada 4X
                                // el sensor de temp humedi necesita por lo menos 2 seg
                                // entonces minimo 500


int humidityAir; // % valor en porcentaje de humedad
int humidityPlant;
int temperature;  // temperatura en centrigados
DHT dht(DHTPIN, DHTTYPE);

// Sensor Luz y gas y otros
#define sensorLightPin A8
#define sensorGasPin   A9
#define sensorHPPin    A10
#define luzPin1    8
#define luzPin2    9
#define luzPin3    10
#define fanPin     11

int light;
int gas;
int iLight = 0; //intensidad Luz
int iFan   = 0; //intensidad Fan



int sensorMode = 0;
unsigned long sensorlastTime = 0;

int showSerial = true;
bool changeLight = true;
bool changeGas = true;
bool changeHA = true;
bool changeT = true;
bool changeHP = true;



int situacion = 0;   // 0: CONFORT, 1: REGAR, 2: ABRIR, 3: SOL
int situacionOLD = 1;
bool changeSituacion = true;

bool blink = true;

unsigned long blinkLastTime = 0;

bool bigBlink = true;

unsigned long bigBlinkLastTime = 0;


void sensoresSetup() {
  dht.begin();
  if(showSerial){
    Serial.begin(9600);
  }
  pinMode(luzPin1,OUTPUT);
  pinMode(luzPin2,OUTPUT);
  pinMode(luzPin3,OUTPUT);
  pinMode(fanPin,OUTPUT);
}

void sensor_humidity_temperature() {

  int h = (int) dht.readHumidity();
  int t = (int) dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    if (showSerial) {
      Serial.println("Failed to read from DHT sensor!");
      h = 1; t = 1;
    }
    return;
  }

  if (showSerial) {
    Serial.print("Humidity: ");
    Serial.print(h);
    Serial.print(" %\t");
    Serial.print("Temperature: ");
    Serial.print(t);
    Serial.println(" *C ");
  }

  /*
  if (t > temperature + 3 && t < temperature - 3) {
    changeT = false;
  } else {
    temperature = t;
    changeT = true;
  }

  if (h == humidityAir) {
    changeHA = false;
  } else {
    humidityAir = h;
    changeHA = true;
  }
  */
temperature = t;
humidityAir = h;

}

void sensor_humidity_plant() {

  int value = analogRead(sensorHPPin);



    humidityPlant = map(value,0,1024,0,100);

    if (showSerial) {
      Serial.print("Humidity value = ");
      Serial.println(humidityPlant);
    }

}

void sensor_gas() {

  int value = analogRead(sensorGasPin);



  gas = map(value,0,1024,0,100);

  if (showSerial) {
    Serial.print("Gas value = ");
    Serial.println(gas);
  }

}

void sensor_light() {
  int value = analogRead(sensorLightPin);

  if (showSerial) {
    Serial.print("ligth value = ");
    Serial.println(value);
  }

    light = value;

    if(light <= umbralLuz1){
      iLight = 0;
    } else if(light > umbralLuz1 && light <= umbralLuz2){
      iLight = 1;
    } else if(light > umbralLuz2 && light <= umbralLuz3){
      iLight = 2;
    } else {
      iLight = 3;
    }

}

void check_sensors(unsigned long currentTime) {

  if (currentTime - sensorlastTime >= sensorTime) {
    sensorlastTime = currentTime;

    switch (sensorMode) {
      case 0:
      sensor_light();
      break;
      case 1:
      sensor_humidity_temperature();
      sensor_light();
      break;
      case 2:
      sensor_gas();
      sensor_light();
      break;
      case 3:
      sensor_humidity_plant();
      sensor_light();
      break;
    }

    sensorMode++;
    if (sensorMode > 3) sensorMode = 0;

    if(humidityPlant < umbralHumedadPlant){
      if(situacion != 1){
        situacion = 1;
        iFan = 2;
        changeSituacion = true;
      } else {
        changeSituacion = false;
      }

    } else if(gas > umbralGas){
      if(situacion != 2){
        situacion = 2;
        iFan = 3;
        changeSituacion = true;
      } else {
        changeSituacion = false;
      }

    } else if(temperature > umbralT && humidityAir < umbralHumedadAir){
      if(situacion != 3){
        situacion = 3;
        iFan = 3;
        changeSituacion = true;
      } else {
        changeSituacion = false;
      }
    } else {
      if(situacion != 0){
        situacion = 0;
        iFan = 1;
        changeSituacion = true;
      } else {
        changeSituacion = false;
      }
    }

  }

}

void blinkState(unsigned long currentTime){
  if (currentTime - blinkLastTime >= blinkTime) {
    blinkLastTime = currentTime;
    blink = !blink;
  }

  if (currentTime - bigBlinkLastTime >= bigBlinkTime) {
    bigBlinkLastTime = currentTime;
    bigBlink = !bigBlink;
  }
}

void changeS(){
  if(changeSituacion) changeSituacion = false;

}

void salidas(){


  switch (iFan) {
    case 0:
    analogWrite(fanPin,0);
    break;
    case 1:
    analogWrite(fanPin,fan1);
    break;
    case 2:
    analogWrite(fanPin,fan2);
    break;
    case 3:
    analogWrite(fanPin,fan3);
    break;
  }

  switch (iLight) {
    case 3:
    digitalWrite(luzPin1,LOW);
    digitalWrite(luzPin2,LOW);
    digitalWrite(luzPin3,LOW);
    break;
    case 2:
    digitalWrite(luzPin1,LOW);
    digitalWrite(luzPin2,LOW);
    digitalWrite(luzPin3,HIGH);
    break;
    case 1:
    digitalWrite(luzPin1,LOW);
    digitalWrite(luzPin2,HIGH);
    digitalWrite(luzPin3,HIGH);
    break;
    case 0:
    digitalWrite(luzPin1,HIGH);
    digitalWrite(luzPin2,HIGH);
    digitalWrite(luzPin3,HIGH);
    break;
  }

}


void lightDecision(){

  if(situacion == 0){
    if(!bigBlink) {
      iLight = 0;
    }

  } else {
    if(!blink){
      iLight = 0;
    }
    //bigBlinkLastTime = currentTime;
    bigBlink = true;
  }

}
