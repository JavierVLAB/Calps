// TFT touch
#include <UTFT.h>
#include <UTouch.h>

extern uint8_t BigFont[];
extern uint8_t SevenSegNumFont[];
extern uint8_t Grotesk16x32[];
extern uint8_t Grotesk24x48[];
extern uint8_t GroteskBold32x64[];
extern uint8_t GroteskBold24x48[];

const long drawTime = 500;
unsigned long drawLastTime = 0;

UTFT myGLCD(CTE70, 25, 26, 27, 28);
UTouch myTouch( 6, 5, 32, 3, 2);

int width = 800;
int height = 480;
int w2 = 400;
int h2 = 240;



void screenTFTsetup() {

  myGLCD.InitLCD();
  myGLCD.clrScr();
  //myTouch.InitTouch();
  //myTouch.setPrecision(PREC_LOW);

}

void check_screenTouchs() {

  if (myTouch.dataAvailable()) {
    myGLCD.setColor(0, 255, 0);
    myTouch.read();

    //situacion = situacion == 3 ? 0 : situacion + 1;

    /*
    int16_t x = myTouch.getX();
    int16_t y = myTouch.getY();

    myGLCD.drawRoundRect (x - 20, y - 20, x + 20, y + 20);
    myGLCD.printNumI(x, width / 2, height / 2 - 30);
    myGLCD.printNumI(y, width / 2, height / 2 + 30);
    myGLCD.printNumI(counter, width / 2, height / 2 + 90);
    counter++;
    */
  }
}

void draw_calypso(unsigned long currentTime){

  if (currentTime - drawLastTime >= drawTime) {
    drawLastTime = currentTime;


    draw_TyH();
    draw_centro();
    draw_frases();
    draw_on();
    draw_onLux();
    draw_Gas();
    draw_humedadPlanta();


  }
}

void drawCosas(unsigned long currentTime) {

  if (currentTime - drawLastTime >= drawTime) {
    drawLastTime = currentTime;

    draw_TyH();
    draw_centro();
    draw_frases();
    draw_on();
    draw_onLux();
    draw_Gas();
    draw_humedadPlanta();

  }
}

void grid(){
  myGLCD.setColor(255,255,255);
  for(int x = 20; x < 800; x+=20){
    for(int y = 20; y < 480; y+=20){
      myGLCD.drawPixel(x,y);
    }
  }
}

void draw_TyH() {
  //myGLCD.setColor(0, 0, 0);

  myGLCD.setFont(GroteskBold32x64);
  myGLCD.setBackColor(0, 0, 0);


    myGLCD.setColor(255, 255, 255);
    myGLCD.print("T:", 40, 30);

    if(temperature < umbralT){
      myGLCD.setColor(232, 48, 137);
    } else {
      myGLCD.setColor(255,0,0);
    }
    myGLCD.printNumI(temperature, 110, 30,2);
    myGLCD.print("C", 180, 30);




    myGLCD.setColor(255, 255, 255);
    myGLCD.print("H:", 40, 110);
    if(humidityAir > umbralHumedadAir){
      myGLCD.setColor(232, 48, 137);
    } else {
      myGLCD.setColor(255,0,0);
    }
    myGLCD.printNumI(humidityAir, 110, 110,2);
    myGLCD.print("%", 180, 110);


}

void draw_centro() {

  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRect(301, 20, 499, 460);
  //circulos

  myGLCD.drawCircle(400, 50, 10);
  myGLCD.drawCircle(400, 160, 10);

  myGLCD.setColor(249, 178, 50);
  myGLCD.drawCircle(400, 50, 20);

  myGLCD.drawCircle(400, 160, 50);
  myGLCD.drawCircle(400, 160, 75);

  //ventiladores
  myGLCD.setColor(255, 255, 255);
  ventilador(355, 265, 15);
  ventilador(400, 290, 15);
  ventilador(445, 265, 15);

  myGLCD.setColor(0,0,255);
  myGLCD.drawRect(368,326,432,412);
  myGLCD.drawRect(367,325,433,413);
  linea_disc(290,365,370,365);
  linea_disc(290,366,370,366);
  maceta(400, 362);
  maceta(400 + 65, 362 + 45);
  maceta(400 - 65, 362 - 45);
  maceta(400 + 65, 362 - 45);
  maceta(400 - 65, 362 + 45);



}

void ventilador(int x, int y, int r){
  myGLCD.drawCircle(x, y, r);
  for(int i = 0; i < 8; i++){
    int xi = r*cos(radians (45*i));
    int yi = r*sin(radians (45*i));
    myGLCD.drawLine(x,y,x+xi,y+yi);
  }
}

void maceta(int xc, int yc) {

  myGLCD.setColor(148, 193, 31);
  myGLCD.drawCircle(xc, yc - 24, 4);
  myGLCD.drawCircle(xc - 11, yc - 20, 3);
  myGLCD.drawCircle(xc + 11, yc - 20, 3);

  myGLCD.drawLine(xc, yc, xc, yc - 15);
  myGLCD.drawLine(xc, yc - 6, xc + 9, yc - 13);
  myGLCD.drawLine(xc, yc - 6, xc - 9, yc - 13);

  myGLCD.setColor(130, 53, 139);
  myGLCD.drawLine(xc - 19, yc, xc + 19, yc);
  myGLCD.drawLine(xc + 19, yc, xc + 12, yc + 34);
  myGLCD.drawLine(xc + 12, yc + 34, xc - 12, yc + 34);
  myGLCD.drawLine(xc - 12, yc + 34, xc - 19, yc);

  myGLCD.setColor(107, 193, 180);
  myGLCD.drawRect(xc - 6, yc + 10, xc + 6, yc + 22);

}

void draw_frases() {


  myGLCD.setFont(Grotesk16x32);
  if(changeSituacion){
    myGLCD.setColor(0, 0, 0);
    myGLCD.fillRect(500, 120, 800, 460);
    changeSituacion = false;
  }
  //myGLCD.fillRect(530, 390, 775, 460);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRect(530, 390, 775, 460);
  myGLCD.setColor(255,255,255);

  switch (situacion) {
    case 1:
    situacion1();
    break;
    case 3:
    situacion3();
    break;
    case 2:
    situacion2();
    break;
    case 0:
    situacion0();
    break;
  }
  situacionOLD = situacion;
}


void situacion1(){
  myGLCD.print("REGAR PLANTAS", 550, 410);
  draw_gotas(557,204,16);
  draw_gotas(696,230, 8);
  draw_gotas(602,222,12);
  draw_gotas(645,262,10);
  draw_gotas(652,199,11);
  draw_gotas(711,282,15);
  draw_gotas(572,301,13);
  draw_gotas(720,211,10);
  draw_gotas(632,315, 7);
  draw_gotas(682,300,11);
}

void situacion3(){
  myGLCD.print("ABRIR VENTANA", 550, 410);

  if(blink){
    myGLCD.setColor(255,0,0);
  } else {
    myGLCD.setColor(0,0,0);
  }

  myGLCD.fillRect(635,180,665,320);
  myGLCD.fillRect(635,330,665,360);

}

void situacion3999(){
  myGLCD.print("SOL ENCENDIDO", 550, 410);
  myGLCD.setColor(255,255,0);
  myGLCD.drawCircle(650,280,75);
  myGLCD.drawCircle(650,280,76);
  myGLCD.drawCircle(650,280,77);
  myGLCD.drawCircle(650,280,51);
  myGLCD.drawCircle(650,280,52);
  myGLCD.drawCircle(650,280,50);
}

void situacion2(){
  myGLCD.print("ABRIR VENTANA", 550, 410);
  myGLCD.setColor(255,0,0);
  myGLCD.drawCircle(650,280,75);
  myGLCD.drawCircle(650,280,76);
  myGLCD.drawCircle(650,280,77);
  myGLCD.drawCircle(650,280,51);
  myGLCD.drawCircle(650,280,52);
  myGLCD.drawCircle(650,280,50);
  myGLCD.drawCircle(650,280,10);
  myGLCD.drawCircle(650,280,11);
  myGLCD.drawCircle(650,280,12);
}

void situacion0(){

  myGLCD.print("   CONFORT", 550, 410);
  myGLCD.setFont(GroteskBold32x64);

  if(blink){
    myGLCD.setColor(255,0,0);
    myGLCD.print("OK", 650-32, 280);
  } else {
    myGLCD.setColor(0,0,0);
    myGLCD.print("OK", 650-32, 280);
  }

}


void draw_gotas(int x, int y, int r){

  myGLCD.setColor(0, 255, 255);
  myGLCD.drawCircle(x,y,r);
  myGLCD.setColor(0, 0, 0);

  myGLCD.fillRect(x-r-1,y-r-1,x+r+1,y);
  myGLCD.setColor(0, 255, 255);
  myGLCD.drawLine(x, y - 2 * r, x + r - 1, y);
  myGLCD.drawLine(x, y - 2 * r, x - r + 1, y);

}


void draw_on() {
  myGLCD.setFont(GroteskBold24x48);
  myGLCD.setColor(255, 255, 255);

  int xi = 100;
  int yi = 260;
  myGLCD.print("ON", xi, yi - 40);

  switch (iFan) {
    case 0:
    myGLCD.setColor(0,0,0);
    myGLCD.fillRect(xi + 60, yi, xi + 73, yi - 22);
    myGLCD.fillRect(xi + 80, yi, xi + 93, yi - 28);
    myGLCD.fillRect(xi +100, yi, xi + 113, yi - 34);
    myGLCD.setColor(255, 255, 255);
    //myGLCD.drawRect(xi + 60 -1, yi-1, xi + 74, yi - 23);
    //myGLCD.drawRect(xi + 80 -1, yi-1, xi + 94, yi - 29);
    //myGLCD.drawRect(xi +100 -1, yi-1, xi + 114, yi - 35);
    break;

    case 1:
    myGLCD.setColor(0,0,0);
    myGLCD.fillRect(xi + 80, yi, xi + 93, yi - 28);
    myGLCD.fillRect(xi +100, yi, xi + 113, yi - 34);
    myGLCD.setColor(255, 255, 255);
    myGLCD.fillRect(xi + 60, yi, xi + 73, yi - 22);
    //myGLCD.drawRect(xi + 80, yi, xi + 93, yi - 28);
    //myGLCD.drawRect(xi +100, yi, xi + 113, yi - 34);
    break;
    case 2:
    myGLCD.setColor(0,0,0);
    myGLCD.fillRect(xi +100, yi, xi + 113, yi - 34);
    myGLCD.setColor(255, 255, 255);
    myGLCD.fillRect(xi + 60, yi, xi + 73, yi - 22);
    myGLCD.fillRect(xi + 80, yi, xi + 93, yi - 28);
    //myGLCD.drawRect(xi +100, yi, xi + 113, yi - 34);
    break;
    case 3:
    myGLCD.setColor(255, 255, 255);
    myGLCD.fillRect(xi + 60, yi, xi + 73, yi - 22);
    myGLCD.fillRect(xi + 80, yi, xi + 93, yi - 28);
    myGLCD.fillRect(xi +100, yi, xi + 113, yi - 34);
    break;
  }

  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRect(xi + 60 -1, yi-1, xi + 74, yi - 23);
  myGLCD.drawRect(xi + 80 -1, yi-1, xi + 94, yi - 29);
  myGLCD.drawRect(xi +100 -1, yi-1, xi + 114, yi - 35);

  linea_disc(220,260,340,260);
  linea_disc(220,259,340,259);

}


void draw_onLux(){
  myGLCD.setColor(255,240,0);
  myGLCD.setFont(GroteskBold24x48);

  switch(iLight){
    case 0:
    myGLCD.print("OFF", 600, 70);
    myGLCD.setFont(Grotesk16x32);
    myGLCD.print("       ", 580, 125);
    break;
    case 1:
    myGLCD.print(" ON", 600, 70);
    myGLCD.setFont(Grotesk16x32);
    myGLCD.print(" 33 LUX", 580, 125);
    break;
    case 2:
    myGLCD.print(" ON", 600, 70);
    myGLCD.setFont(Grotesk16x32);
    myGLCD.print(" 66 LUX", 580, 125);
    break;
    case 3:
    myGLCD.print(" ON", 600, 70);
    myGLCD.setFont(Grotesk16x32);
    myGLCD.print("100 LUX", 580, 125);
    break;
  }
  linea_disc(430,51,650,51);
  linea_disc(430,50,650,50);
  linea_disc(650,50,650,80);
  linea_disc(651,50,651,80);
}

void linea_disc(int xi, int yi, int xf, int yf){

  if(yi == yf){   // linea horizontal
    for(int x = xi; x < xf; x += 20){
      myGLCD.drawLine(x,yi, x+10, yi);
    }

  }
  if(xi == xf) { // linea vertical
    for(int y = yi; y < yf; y += 20){
      myGLCD.drawLine(xi,y, xi, y+10);
    }
  }

}

void draw_Gas(){


    myGLCD.setColor(255, 255, 255);
    myGLCD.setFont(Grotesk16x32);
    myGLCD.print( "Calidad Aire",  25, 300);

    int lx = 170;

    int l = map(gas, 0, 100, 0, lx);

    if(gas < umbralGas){
      myGLCD.print("Buena", 210, 350);
      myGLCD.setColor(  0, 255, 0);

    }else{
      myGLCD.print(" Mala", 210, 350);
      myGLCD.setColor(  255, 0, 0);

    }
    myGLCD.fillRect( 25,350,25 + l ,380);

    myGLCD.setColor(  0,  0,  0);
    myGLCD.fillRect(25+l,350,25+lx,380);

    myGLCD.setColor(255,255,255);
    myGLCD.drawRect( 24,349,26+lx,381);


}

void draw_humedadPlanta(){

    myGLCD.setFont(Grotesk24x48);
    myGLCD.setColor(255, 255, 255);
    myGLCD.print("H", 130, 410);

    if(humidityPlant < umbralHumedadPlant){
      myGLCD.setColor(255, 0, 0);
    } else {
      myGLCD.setColor(255, 255, 255);
    }

    myGLCD.printNumI(humidityPlant, 30, 410,2);
    myGLCD.print("%", 90, 410);

    linea_disc(160,441,320,441);
    linea_disc(160,440,320,440);


}
