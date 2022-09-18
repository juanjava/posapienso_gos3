////////////STATUS/////////////STATUS/////////////
/*interfaz grafica posible acabada, con menu de edicion de hora del sistema
falta arreglar hacer caso encoder para edicion de fecha y hora de sistema 
vigilar endoder que me esta dando la chapa
testear botones analogicos y su funcionamiento por el mostrar_menu
guardado de enables en eeprom seguramente arreglado, falta testeo*/
////////////STATUS/////////////STATUS/////////////

/////////librerias//////////////
#include <Wire.h>
#include <RTClib.h>
//#include "RTClib.h"
///#include <LiquidCrystal_I2C.h>/////una o la otra
#include <LiquidCrystal.h>
#include <EEPROM.h>
#include <Servo.h>

////////////////////////////////////PINES//////////////////////

///ROTARY ENCODER//////////////
int CLK = 2;//CLK->D2
byte DT = 3;//DT->D3   //shield lcd 456789
byte SW = 11;//SW->
const int interrupt0 = 0;// Interrupt 0 在 pin 2 上

//a4 y a5 scl y sda el rtc
byte pinservotrampilla = 12;
byte pinservomeneo = 13;

///////////////LCD///////////////////////
///LiquidCrystal_I2C lcd(0x27, 16, 2); ////uno u otro
LiquidCrystal  lcd ( 8 ,  9 ,  4 ,  5 ,  6 ,  7 );            // seleccione los pines utilizados en el panel LCD
////LiquidCrystal lcd(8, 9, 4, 5, 6, 7);           // select the pins used on the LCD panel
RTC_DS3231 rtc;//el reloj
Servo servotrampilla;
Servo servomeneo;


/////////////////////VARIABLES///////////////////////////

///////////////EL MENU////////////////////////
///byte submenu = 0; ///ANDE ANDO
int posscroll = 0;///////////donde estoy en el menu()
int count = 0;//Define the count
int lastCLK = 0;//CLK initial value
long millisantes = 0;
boolean estado_boton_enc_antes = false;
int ultimoclick = 0;

/////////////minimos y maximos del menu////////////////////
byte minmax[4][2] = {///para ponerle limites al encoder
  {00, 03},
  {10, 14},
  {20, 24},
  {30, 34}
};////por legibilidad///

///SHIELD LCD//////////////////////////ANALOGICOS
int lectura_boton = 0;
boolean botonpulsado = false;//anti aguantar//
String botones[] = {"select", "izquierda", "abajo", "arriba", "derecha", "nada"};
int boton = 0;
int estado_boton_antes = 0;
int estado_boton_ahora = 0;


//////////////////ESTADOS AJUSTES//////////////////////
boolean ajustando_reloj_sistema = false;
boolean ajustando_anyo = false;
boolean ajustando_mes = false;
boolean ajustandoalgo = false;///metido en encoder (ClockChanged) y en ajustarbrilloled
boolean ajustandohora = false;///metido en encoder (ClockChanged) y en ajustarbrilloled
boolean ajustandominuto = false;///metido en encoder (ClockChanged) y en ajustarbrilloled
boolean ajustandocantidad = false;///metido en encoder (ClockChanged) y en ajustarbrilloled
boolean ajustandoestado = false;///metido en encoder (ClockChanged) y en ajustarbrilloled
////reloj sistema: pòsscroll 50,51,52,53,54
//ajustes horas y demas: *10

//////////////////////////////COMIDAS///////////////////////////////////////
byte numerocomida = 0;////para todo, cargar, guardar, etc
int horas[3][2];///HORAS y minutos
boolean comidas_habilitadas[3] = {false, false, false};///HABILITADAS O NO//
int cantidades[3] = {0, 0, 0};
int cantidad = 0;////VARIABLE AUX

///variables////////     ////////son millis()
unsigned long ahora = 0;
unsigned long millismeneo = 0;
unsigned long milliscant = 0;////VARIABLE AUX
unsigned long millisdebug = 0;
unsigned long millisantes_enc = 0;

boolean pos_servo = false;
boolean piensopuesto = false;
byte hora = 0;
byte minuto = 0;
//byte dia_semana = 0;
byte mes = 0;
int anyo = 0;
byte dia = 0;
//////////////////////////RELOJ RTC////////////
//String daysOfTheWeek[7] = { "Domingo", "Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sabado" };
///String monthsNames[12] = { "Enero", "Febrero", "Marzo", "Abril", "Mayo",  "Junio", "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre" };


void setup() {
  // Inicializar el LCD
  ///lcd.init();///i2c
  //Encender la luz de fondo.
  ///lcd.backlight();////i2c
  lcd.begin(16, 2);              // inicia la biblioteca
  lcd.setCursor ( 0 , 0 );

  ////ENCODER
  pinMode(SW, INPUT);
  ///pinMode(SW, INPUT_PULLUP);
  digitalWrite(SW, HIGH);
  pinMode(CLK, INPUT);
  pinMode(DT, INPUT);
  attachInterrupt(interrupt0, ClockChanged, LOW); //Set the interrupt 0 handler, trigger level change
  servotrampilla.attach(pinservotrampilla);
  servomeneo.attach(pinservomeneo);
  Serial.begin(9600);
  Serial.println("Estoy en el setup");
  iniciar_borrar_memoria_horas();

  ///guardar_datos_test();
  //iniciar_borrar_memoria_horas();
  cargar_variables_eeprom();
}

void iniciar_borrar_memoria_horas(){
  Serial.print(" iniciar_borrar_memoria_horas");
    ////poner a cero todo el array
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 2; j++) {
      horas[i][j] = 0;
    }
  }
}
void loop() {
  ///mostrar menu
  ///mirar boton
  //mirar si es hora de comer
  llenarpantalla();
  revisar_analogicos();
  case_boton_analogico(); 
  ///mirarboton();
  mirarboton_menu_lcd();
  horapienso();
  ///mostrar_encoder();
  ///volcado_variables_serial();
  Serial.println(posscroll);
  /*if(posscroll>34){    
    Serial.print("Error critico desconocido posscroll,numerocomida");
    Serial.print("  ");
    Serial.print(posscroll);
    Serial.print("  ");
    Serial.println(numerocomida);
    posscroll=0;
  }*/
  Serial.println("");
  Serial.println("");
  Serial.println("");
}
void volcado_variables_serial(){//////cada segundo
  if (millis() > (millisdebug + 1000)) {
    millisdebug = millis();
      mostrar_datos_cargados();
  }
}
/////////////////////////////////RELOJ RTC//////////////////////////////////////
/////////////////////////////////RELOJ RTC//////////////////////////////////////

void cargar_hora() {
  if (rtc.begin()) { ////si está
    if (rtc.lostPower()) {///le quitastes la pila
      // Fijar a fecha y hora de compilacion
      rtc.adjust(DateTime(2022, 9, 18, 20, 27, 0));
    } else {///tenia pila
      // Obtener fecha actual y mostrar por Serial
      DateTime now = rtc.now();
      ///printDate(now);
      cargar_fecha_hora(now);
    }
  } else { ///no está
    Serial.println(F("Couldn't find RTC"));
    for (int i = 0; i < 10; i++) {
      Serial.println(F("Couldn't find RTC"));
    }
  }
}

void horapienso() {
  DateTime ahora = rtc.now();
  ////boolean comidas_habilitadas[3] = {false, false, false};///HABILITADAS O NO//
  for (byte i = 0; i < 3; i++) {
    if (horas[i][0] == ahora.hour()) {
      ///mirar los minutos
      if (horas[i][1] == ahora.minute()) {
        if (comidas_habilitadas[i] == true) {
          if(!piensopuesto){///anti varios en un mismo minuto
          ponerpienso(i);
          }
        }
      }else{
        piensopuesto = false;
      }
      if (horas[i][1] == (ahora.minute() + 3)) {
        ///auto-reseteo pienso puesto
        piensopuesto = false;
      }
    }
  }///fin for
}
/*
void printDate(DateTime date) {
  Serial.print(date.year(), DEC);
  Serial.print('/');
  Serial.print(date.month(), DEC);
  Serial.print('/');
  Serial.print(date.day(), DEC);
  Serial.print(" (");
  Serial.print(daysOfTheWeek[date.dayOfTheWeek()]);
  Serial.print(") ");
  Serial.print(date.hour(), DEC);
  Serial.print(':');
  Serial.print(date.minute(), DEC);
  Serial.print(':');
  Serial.print(date.second(), DEC);
  Serial.println();
}*/
void cargar_fecha_hora(DateTime date) {
  anyo = date.year(), DEC;
  mes = date.month(), DEC;
  dia = date.day();
  hora = date.hour(), DEC;
  minuto = date.minute(), DEC;
}
void cargar_fecha_hora_auto() {
   if (rtc.begin())  {//si está
    DateTime date = rtc.now();
    anyo = date.year(), DEC;
    mes = date.month(), DEC;
    dia = date.day();
    hora = date.hour(), DEC;
    minuto = date.minute(), DEC;
   }
}
// Comprobar si esta programado el encendido

void cambiar_hora_reloj(){
  /*byte hora = 0;byte minuto = 0;byte dia_semana = 0;byte mes = 0;byte año = 0;*/
   if (rtc.begin()) { ////si está
    rtc.adjust(DateTime(anyo, mes, dia, hora, minuto, 0));
    lcd.setCursor(0,0);
    lcd.print("HORA CAMBIADA");
    delay(2000);
  } else { ///no está
    lcd.setCursor(0,0);
    lcd.print("Couldn't find RTC");
    lcd.setCursor(0,1);
    lcd.print("Couldn't find RTC");
    delay(2000);
  } 
}

/////////////////////////////////TESTEO//////////////////////////////////////
void guardar_datos_test(){
    for (int i = 0; i < 3; i++) {
    horas[i][0] = 22;
    horas[i][1] = 22;
    guardar_horario(i);
    ///comidas_habilitadas[i] = false;
    guardar_enables(i, false);
    ///cantidades[i] = 400;
    guardarcantidad(i, 300);
  }
}
void mostrar_datos_cargados() {
    Serial.println("DATOS DE LAS COMIDAS");
    Serial.print("comida 1 ");
    Serial.print(horas[0][0]);
    Serial.print(":");
    Serial.println((horas[0][1]));
    Serial.print("enable: ");
    Serial.println(comidas_habilitadas[0]);
    Serial.print("cantidad: ");
    Serial.println(cantidades[0]);

    Serial.print("comida 2 ");
    Serial.print(horas[1][0]);
    Serial.print(":");
    Serial.println((horas[1][1]));
    Serial.print("enable: ");
    Serial.println(comidas_habilitadas[1]);
    Serial.print("cantidad: ");
    Serial.println(cantidades[1]);

    Serial.print("comida 3 ");
    Serial.print(horas[2][0]);
    Serial.print(":");
    Serial.println((horas[2][1]));
    Serial.print("enable: ");
    Serial.println(comidas_habilitadas[2]);
    Serial.print("cantidad: ");
    Serial.println(cantidades[2]);
    Serial.println();
    Serial.print("hora sistema: ");
          cargar_hora();
      Serial.print(anyo);
      Serial.print("YY");
      Serial.print(dia);
      Serial.print("d");
      Serial.print(mes);
      Serial.print("M");
      Serial.print(hora);
      Serial.print(":");
      Serial.println(minuto);
      mostrar_encoder();
}
void mostrar_encoder() {
  int clkValue = digitalRead(CLK);//Read the CLK pin level
  int dtValue = digitalRead(DT);//Read the DT pin level
  int swvalue = digitalRead(SW);
  Serial.print("CLK ");
  Serial.print(clkValue);
  Serial.print(" DT ");
  Serial.print(dtValue);
  Serial.print(" SW ");
  Serial.println(swvalue);
}

