


///////////////////////////funciones poner pienso////////////////////////////////////////////////////

void ponerpienso(int numerocomidaaa) {
  Serial.print(" ponerpienso");
  cantidad = cantidades[numerocomidaaa];
  milliscant = millis();
  abrirtrampilla();
  while (millis() < (milliscant + cantidad * 10)) {////invento
    menear_pienso();////algo bloqueante///
  }
  cerrartrampilla();
  piensopuesto = true;
}
void abrirtrampilla() {
  servotrampilla.write(180);
}
void cerrartrampilla() {
  servotrampilla.write(0);
}
void menear_pienso() {
  if (millis() > millismeneo + 500) {
    pos_servo = !pos_servo;
    millismeneo = millis();
  }
  if (pos_servo) {
    servomeneo.write(180);
  } else {
    servomeneo.write(0);
  }
}


///////////////////////////MENU SIN LIBRERIA////////////////////////////////////////////////////
///////////////////////////MENU SIN LIBRERIA////////////////////////////////////////////////////


///////////PRIMERO MOSTRAR EN PANTALLA LO QUE TOQUE///////////////
void pantallasajustes(){
  if(ajustando_reloj_sistema){
    Serial.print("ajustando_reloj_sistema - pantallasajustes");
    if (ajustandominuto) {
      ajustar_minuto();
    }else if (ajustandohora) {
      ajustar_hora();
    }else if(ajustando_anyo){
      ajustar_anyo();
    } else {
      ajustando_reloj_sistema = false;
      ajustandoalgo = false;
    }
  }else if (ajustandoalgo) {
   if (ajustandohora) {
      ajustar_hora();
    } else if (ajustandominuto) {
      ajustar_minuto();
    } else if (ajustar_cantidad) {
      ajustar_cantidad();
    } else if (ajustandoestado) {
      ajustar_habilitar_comida();
    } else {
      ajustandoalgo = false;
    }
  } else {
    mostrar_menu();////MENU EN SI
  }
}
void llenarpantalla() {
  Serial.print ("Estoy en el llenarpantalla -");
  if(!ajustando_reloj_sistema||!ajustandoalgo){
    mostrar_menu();////MENU EN SI
  }else{
    pantallasajustes();
  }
}
void mostrar_menu() {///escribe la priumera linea, y la segunda si hay mas para escribir
  Serial.print(" mostrar_menu -");
  lcd.setCursor(0, 0);///desplazo algo a la derecha el elemento seleccionado
  lcd.print(">");///flecha
  mostrarlinea(posscroll);
  Serial.println();
  lcd.print("      ");///BORRAR CARACTERES VIEJOS
  lcd.setCursor(0, 1);
  byte aux = posscroll / 10; ////fila para minmax
  if (posscroll >= minmax[aux][1]) {
    ////no imprimo nada; puede quedar la de abajo vacia///
    if(posscroll==3){
            ////mostrarhora reloj en pantalla
      ///lcd.setCursor(0, 1);
      lcd.print(anyo);
      lcd.print("YY");
      lcd.print(dia);
      lcd.print("d");
      lcd.print(mes);
      lcd.print("M");
      lcd.print(hora);
      lcd.print(":");
      lcd.print(minuto);
    }
  } else {
    Serial.print(" mostrar_menu -");
    mostrarlinea(posscroll + 1); ////la siguiente
  }
  lcd.print("                   ");////////quito restos de caracteres viejos
}
void mostrarlinea(int lineamenu) {////llamo a las de abajo, solo para dividir el switch case
  Serial.print(" mostrarlinea-");
  Serial.print(lineamenu);
  if (lineamenu >= 0 && lineamenu < 10) {
    menuinicio(lineamenu);
  } else if (lineamenu >= 10 && lineamenu < 20) {
    submenu1( lineamenu);
  } else if (lineamenu >= 20 && lineamenu < 30) {
    submenu2(lineamenu);
  } else if (lineamenu >= 30 && lineamenu < 40) {
    submenu3(lineamenu);
  } else {}
  Serial.print(lineamenu);
}
void menuinicio(int lineamenu) {
  Serial.print(" menuinicio ");
  Serial.print (lineamenu);
  submenu = 0;
  switch (lineamenu) {
    case 0:
      lcd.print("COMIDA 1");
      break;
    case 1:
      lcd.print("COMIDA 2");
      break;
    case 2:
      lcd.print("COMIDA 3");
      break;
    case 3:
      lcd.print("AJUSTAR RELOJ");
      break;
    default:
      // statements
      break;
  }
}
void submenu1(int lineamenu) {
  Serial.print(" submenu1 -");
  submenu = 1;
  switch (lineamenu) {
    case 10:
      lcd.print("AJ HORA");
      lcd.print(horas[0][0]);
      lcd.print(":");
      lcd.print(horas[0][1]);
      lcd.print("      ");
      break;
    case 11:
      lcd.print("AJUSTAR CANTIDAD");
      lcd.print(cantidades[0]);
      lcd.print("        ");
      break;
    case 12:
      lcd.print("HABILITAR ");
      lcd.print(comidas_habilitadas[0]);
      lcd.print("        ");
      break;
    case 13:
      lcd.print("TEST");
      lcd.print(cantidades[0]);
      lcd.print("         ");
      break;
    case 14:
      lcd.print("VOLVER");
      lcd.print("         ");
      break;
    default:
      // statements
      break;
  }
}
void submenu2(int lineamenu) {
  submenu = 2;
  Serial.print(" submenu2 ");
  switch (lineamenu) {
    case 20:
      lcd.print("AJ HORA");
      lcd.print(horas[1][0]);
      lcd.print(":");
      lcd.print(horas[1][1]);
      lcd.print("      ");
      break;
    case 21:
      lcd.print("AJUSTAR CANTIDAD");
      lcd.print(cantidades[1]);
      lcd.print("      ");
      break;
    case 22:
      lcd.print("HABILITAR ");
      lcd.print(comidas_habilitadas[1]);
      lcd.print("      ");
      break;
    case 23:
      lcd.print("TEST");
      lcd.print(cantidades[1]);
      lcd.print("      ");
      break;
    case 24:
      lcd.print("VOLVER");
      lcd.print("      ");
      break;
    default:
      // statements
      break;
  }
}
void submenu3(int lineamenu) {///on//off/brillo//volver
  submenu = 3;
  Serial.print("submenu3 ");
  switch (lineamenu) {
    case 30:
      lcd.print("AJ HORA");
      lcd.print(horas[2][0]);
      lcd.print(":");
      lcd.print(horas[2][1]);
      lcd.print("      ");
      break;
    case 31:
      lcd.print("AJUSTAR CANTIDAD ");
      lcd.print(cantidades[2]);
      lcd.print("      ");
      break;
    case 32:
      lcd.print("HABILITAR ");
      lcd.print(comidas_habilitadas[2]);
      lcd.print("      ");
      break;
    case 33:
      lcd.print("TEST");
      lcd.print(cantidades[2]);
      lcd.print("      ");
      break;
    case 34:
      lcd.print("VOLVER");
      lcd.print("      ");
      break;
    default:
      // statements
      break;
  }
}
///////////////////////////PANTALLAS AJUSTES////////////////////////////////////////////////////
/*boolean ajustandoalgo = false;
   boolean ajustando_reloj_sistema = false;
  boolean ajustandohora = false;///metido en encoder (ClockChanged) y en ajustarbrilloled
  boolean ajustandominuto = false;///metido en encoder (ClockChanged) y en ajustarbrilloled
  boolean ajustandocantidad = false;///metido en encoder (ClockChanged) y en ajustarbrilloled
  boolean ajustandoestado = false;///metido en encoder (ClockChanged) y en ajustarbrilloled*/
void ajustar_reloj_sistema() {
  Serial.println("estoy en el ajustar_reloj_sistema");
  ajustando_reloj_sistema = true;
    ajustandoalgo = true;
    ajustar_anyo();
}
void ajustar_anyo() {
  Serial.println("estoy en el ajustar_anyo");
  ajustando_reloj_sistema = true;
  ajustandoalgo = true;
  ajustandohora = true;
  lcd.setCursor(1, 0);///desplazo algo a la derecha el elemento seleccionado
  lcd.print("AJUSTANDO AÑO :");
  lcd.setCursor(0, 1);
  lcd.print(anyo);
}
void ajustar_mes() {
  Serial.println("estoy en el ajustar_mes");
  ajustando_reloj_sistema = true;
  ajustandoalgo = true;
  ajustando_mes = true;
  lcd.setCursor(1, 0);///desplazo algo a la derecha el elemento seleccionado
  lcd.print("AJUSTANDO MES :");
  lcd.setCursor(0, 1);
  lcd.print("MES:");
  lcd.print(mes);
}
void ajustar_hora() {
  Serial.println("estoy en el ajustar_hora");
  ajustandoalgo = true;
  ajustandohora = true;
  ajustandominuto = false;
  lcd.setCursor(1, 0);///desplazo algo a la derecha el elemento seleccionado
  lcd.print("AJUSTANDO HORA :");
  lcd.setCursor(0, 1);
  lcd.print("hora:");
  lcd.print(horas[numerocomida][0]);
  lcd.print(":");
  lcd.print(horas[numerocomida][1]);
}
void ajustar_minuto() {
  Serial.println("estoy en el ajustar_minuto");
  ajustandoalgo = true;
  ajustandominuto = true;
  lcd.setCursor(1, 0);///desplazo algo a la derecha el elemento seleccionado
  lcd.print("AJUSTANDO MINUTO :");
  lcd.setCursor(0, 1);
  lcd.print("hora:");
  lcd.print(horas[numerocomida][0]);
  lcd.print(":");
  lcd.print(horas[numerocomida][1]);
}
void ajustar_cantidad() {
  Serial.println("estoy en el ajustar_cantidad");
  ajustandoalgo = true;
  ajustandocantidad = true;
  lcd.setCursor(1, 0);///desplazo algo a la derecha el elemento seleccionado
  lcd.print("CANTIDAD:");
  lcd.setCursor(0, 1);
  lcd.print(cantidades[numerocomida]);
}
void ajustar_habilitar_comida() {
  Serial.println("estoy en el ajustar_habilitar_comida");
  ajustandoalgo = true;
  ajustandoestado = true;
  lcd.setCursor(1, 0);///desplazo algo a la derecha el elemento seleccionado
  lcd.print("HABILITAR:");
  lcd.setCursor(0, 1);
  lcd.print(comidas_habilitadas[numerocomida]);
}
///////////////////////////ACTUAR////////////////////////////////////////////////////
/////////////////////////////////EL BOTON/////////////////////////////////////////////////

void mirarboton() {///// CON MILLIS
  ///boolean estado_boton_enc_antes = false;
  ///boolean botonpulsado = false;//anti aguantar//
  boolean estado_boton_enc_ahora = digitalRead(SW);////activa al ser false, cuando pulsas va a masa

  if (estado_boton_enc_ahora) {//high/true es NO pulsado
    estado_boton_enc_antes = true;
    botonpulsado = false;
    millisantes_enc = millis();
  } else { /////he pulsado
    ///Serial.println("                                boton pulsado");
    if (estado_boton_enc_antes != estado_boton_enc_ahora) {
      ///Serial.println("                                boton pulsado y medio caso");
      estado_boton_enc_antes = estado_boton_enc_ahora;
      millisantes_enc = millis();
      botonpulsado = false;
    } else if (millis() > (millisantes_enc + 400)) {
      ///Serial.println("                                boton pulsado y caso casoooo");
      if (!botonpulsado) { ////antirebote//anti aguantar
        hacer_caso_boton2();
        if(ultimoclick!=posscroll){///no volver a metermen dos veces en el mismo sitio
          ultimoclick=posscroll;
          ///hacer_caso_boton2();
        }        
        botonpulsado = true;
        /*
        Serial.print("Elemento pulsado: ");
        Serial.println(posscroll);*/
      }else{botonpulsado = true;
      ///millisantes_enc = millis();
      }
    } else {botonpulsado = false;}
  }//fin else he pulsado
}
void mirarboton_menu_lcd(){/////////////ARREGLADO
    if (!digitalRead(SW) && (ultimoclick != posscroll)) //leo el boton y asigno posscroll a elementopulsado
  {
    ultimoclick = posscroll;
    Serial.print("Elemento pulsado: ");
    Serial.println(ultimoclick);
    ///sacar_variables_serial();
    hacer_caso_boton2();
  }if(!digitalRead(SW)&&(ajustando_reloj_sistema||ajustandoalgo)&&botonpulsado == false;){
    hacer_caso_boton2();
    botonpulsado=true;
  }else{
    botonpulsado = false;
  }  /*    
    if(!digitalRead(SW) && ajustandoled){/// solo cuando ajustandoled = true
      ajustandoled=false;///SALGO DE AHI
        ///elementopulsado=-1;
        posscroll=submenu-1;
        ultimoclick = posscroll;
        delay(200);
        }else{}*/
}
void hacer_caso_boton() { ///esto se hara cuando pulse el boton///VERSION CORTA //AJUSTANDO ALGO NO IMPLEMENTADO//
  /////////////AJUSTANDO ALGO NO IMPLEMENTADO////////////
  if (posscroll >= 0 && posscroll < 10) { ///pulso boton en menu inicio
    submenu = 0;
    if (posscroll == 3) {////("AJUSTAR RELOJ");
      ajustandoalgo = true;
      ajustar_reloj_sistema();
    } else if (posscroll < 3) {
      numerocomida = posscroll;/////importante
      posscroll++;
      posscroll = posscroll * 10; ///me meto en submenu; opcion 0 ha de acabar en opcion 10
    } else {}


  } else { //////////mayor de 10, estoy en un subapartado    
      calcular_submenu_numerocomida();
      submenu_actuar(posscroll % 10);//int subapartado = posscroll % 10; //% DEVUELVE EL RESTO DE LA DIVISION
  }
}
void  hacer_caso_boton2() {/////////////////VERSION LARGA
  if(ajustando_reloj_sistema){
    if(ajustando_anyo){
      ajustando_anyo= false;
      ajustando_mes=true;
    }else if(ajustando_mes){
      ajustando_mes=false;
      ajustandohora = true;
    }else if(ajustandohora){
        ajustandohora =false;
        ajustandominuto = true;        
      }else if(ajustandominuto){
        ajustandominuto = false;
        ajustando_reloj_sistema = false;
      }else{}
      delay(2000);
    }else if (ajustandoalgo) { ///al pulsar sale de ahi
    salir_de_todo();
    salir_a_menu_inicio();
  } else {/////AQUI VA EL SWITCH DE ABAJO
  /*void entrarsubmenu() {
    numerocomida = posscroll;/////importante
    posscroll++;
    posscroll = posscroll * 10; ///me meto en submenu; opcion 0 ha de acabar en opcion 10
    }*/
  switch (posscroll) {
    case 0:
      entrarsubmenu();
      break;
    case 1:
      entrarsubmenu();
      break;
    case 2:
      entrarsubmenu();
      break;
    case 3:///lcd.print("AJUSTAR RELOJ");
      ajustar_reloj_sistema();
      break;

    case 10:///lcd.print("AJUSTAR HORA");
      submenu = (posscroll / 10); ////submenu 1, comida 0, posscroll 10
      numerocomida = submenu - 1;
      ajustar_hora();
      break;
    case 11:///lcd.print("AJUSTAR cantidad");
      submenu = (posscroll / 10); ////submenu 1, comida 0, posscroll 10
      numerocomida = submenu - 1;
      ajustandoalgo = true;
      ajustandocantidad = true;
      ajustar_cantidad();
      break;
    case 12://///lcd.print("habilitar");
      submenu = (posscroll / 10); ////submenu 1, comida 0, posscroll 10
      numerocomida = submenu - 1;
      ajustandoalgo = true;
      ajustandoestado = true;
      ajustar_habilitar_comida();
      break;
    case 13://///lcd.print("test");
      submenu = (posscroll / 10); ////submenu 1, comida 0, posscroll 10
      numerocomida = submenu - 1;
      ponerpienso(numerocomida);
      break;
    case 14:
      submenu = (posscroll / 10); ////submenu 1, comida 0, posscroll 10
      numerocomida = submenu - 1;
      /////salimos
      posscroll = numerocomida;
      submenu = 0;
      break;
    //////VES COMO SE REPITE CODIGO??
    ///POR ESO LA MANIA DE CREAR FUNCIONES
    /*void calcular_submenu_numerocomida(){
          submenu = (posscroll / 10); ///submenu 1, comida 0, posscroll 10
          numerocomida = submenu - 1;
      }*/
    case 20://///lcd.print("ajustar hora");
      calcular_submenu_numerocomida();
      submenu_actuar(0);
      break;
    case 21://///lcd.print("ajustar cantidad");
      calcular_submenu_numerocomida();
      submenu_actuar(1);
      break;
    case 22://///lcd.print("habilitar");
      calcular_submenu_numerocomida();
      submenu_actuar(2);
      break;
    case 23://///lcd.print("test");
      calcular_submenu_numerocomida();
      ponerpienso(3);
      break;
    case 24:
      salir_a_menu_inicio();
      break;
    /*    case 30:
        lcd.print("AJUSTAR HORA");
      case 31:
        lcd.print("AJUSTAR CANTIDAD");
      case 32:
        lcd.print("HABILITAR ");
      case 33:
        lcd.print("TEST");
      case 34:
        lcd.print("VOLVER");*/
    case 30:
      calcular_submenu_numerocomida();
      submenu_actuar(0);
      break;
    case 31:
      calcular_submenu_numerocomida();
      submenu_actuar(1);
      break;
    case 32:
      calcular_submenu_numerocomida();
      submenu_actuar(2);
      break;
    case 33:
      calcular_submenu_numerocomida();
      ponerpienso(numerocomida);
      break;
    case 34:
      salir_a_menu_inicio();
      break;
  }}
}
void calcular_submenu_numerocomida() {
  submenu = (posscroll / 10); ///submenu 1, comida 0, posscroll 10
  numerocomida = submenu - 1;
}
void entrarsubmenu() {
  numerocomida = posscroll;/////importante
  posscroll++;
  posscroll = posscroll * 10; ///me meto en submenu; opcion 0 ha de acabar en opcion 10
}
void submenu_actuar(int subapartado) {///////////////////////
  if (subapartado == 0) {///lcd.print("AJUSTAR HORA");
    ajustar_hora();
  }  else if (subapartado == 1) {///lcd.print("AJUSTAR CANTIDAD");
  ajustar_cantidad();
  }  else if (subapartado == 2) {///lcd.print("HABILITAR ");
  ajustar_habilitar_comida();
  }  else if (subapartado == 3) {
    ponerpienso(numerocomida);
  } else if (subapartado == 4) {///lcd.print("VOLVER");*/
    ///////VOLVER A MENU INICIO
    salir_a_menu_inicio();
  } else {}
}
void salir_a_menu_inicio() {
  submenu = (posscroll / 10); ///submenu 1, comida 0, posscroll 10
  numerocomida = submenu - 1;
  /////salimos
  posscroll = numerocomida;
  submenu = 0;
}
void salir_de_todo() { //lo llamo tb desde izquierda
if (ajustandominuto) {
    ajustandominuto = false;
    ajustandoalgo = false;
    guardar_horario(numerocomida);
  } else   if (ajustandohora) {
    ajustandohora = false;
    ajustandominuto = true;
    delay(500);
  }  else if (ajustandocantidad) {
    ajustandocantidad = false;
    ajustandoalgo = false;
   guardarcantidad(numerocomida, cantidades[numerocomida]); ////////////////////////////////////////////
  } else if (ajustandoestado) {
    ajustandoestado = false;
    ajustandoalgo = false;
    guardar_enables(numerocomida, comidas_habilitadas[numerocomida]); ////////////////////////////////
  }

  if (ajustandoalgo == false) { ///SALGO DE AHI
    posscroll = submenu - 1;
  }
  ///salir_a_menu_inicio();
}


///////////////////////////INTERRUPCION LLAMADA POR EL ENCODER////////////////////////////////////////////////////

void ClockChanged() {////////////del ejemplo del encoder
  int clkValue = digitalRead(CLK);//Read the CLK pin level
  int dtValue = digitalRead(DT);//Read the DT pin level
 Serial.println("Encoder"); 
 Serial.println("                                                endoder");
    if (!ajustandoalgo&!ajustando_reloj_sistema) { ///no estoy ajustando nada
      if (clkValue == dtValue) {
        sumando();
      } else {
        restando();
      }
    } else { ////ajustando algun valor
      if (clkValue == dtValue) {
        ajustar_valores_encoder_sumando(true);
      } else {
        ajustar_valores_encoder_sumando(false);
      }
      ///ajustar_valores_encoder(clkValue, dtValue);
    }/////fin del else de ajustando algo
  sacar_variables_serial();
}
void sumando() {
  Serial.println("Sumando");
  if (posscroll < minmax[submenu][1]) {
    posscroll++;
    Serial.println("Sumando:  ");
  }
   delay(200);
}
void restando() {
  Serial.println("Restando");
  if (posscroll > minmax[submenu][0]) {
    posscroll--;
    Serial.println("Restando:  ");
  }
  delay(200);
}

void ajustar_valores_encoder_sumando(boolean sumando) {
  if (ajustandohora) {
    ///hora = horas[numerocomida][0];
    if (sumando) {
      if (horas[numerocomida][0] < 23) {
        ///hora++;
        horas[numerocomida][0]++;
      }
      if(horas[numerocomida][0]>23){
        horas[numerocomida][0] = 23;}
    } else {
      if (horas[numerocomida][0] > 0) {
        //hora--;
        horas[numerocomida][0]--;
      }if(horas[numerocomida][0]<0){
        horas[numerocomida][0]=0;}
    }
    ///horas[numerocomida][0] = hora;
  } else if (ajustandominuto) {
    ///minuto = horas[numerocomida][1];
    if (sumando) {
      if (minuto < 59) {
        ///minuto++;
        horas[numerocomida][1]++;
      }
    } else {
      if (minuto > 0) {
        ///minuto--;
        horas[numerocomida][1]--;
      }
    }
    ///horas[numerocomida][1]= minuto;
  } else if (ajustandocantidad) {
    ///cantidades[3]
    cantidad = cantidades[numerocomida];
    if (sumando) {
      if (cantidad < 30000) {
        cantidad = cantidad + 10;
      }
    } else {
      if (cantidad > 9) {
        cantidad = cantidad - 10;
      }
    }
    cantidades[numerocomida] = cantidad;
  } else if (ajustandoestado) {
    if (sumando) {
      comidas_habilitadas[numerocomida] = !comidas_habilitadas[numerocomida];
    } else {
      comidas_habilitadas[numerocomida] = !comidas_habilitadas[numerocomida];
    }
  }
}

void sacar_variables_serial() { ////////////ACABAT/////////////
  //////limites del menu
  /*Serial.println("limites del menu");
    for(int i = 0;i<4;i++){
    for(int j=0;j<2;j++){
      Serial.print(minmax[i][j]);
      }
      Serial.println();
    }*/
  Serial.print("Posicion del encoder: ");
  Serial.println(posscroll);
  Serial.print("Submenu:  ");
  ///Serial.print(submenu);

  Serial.println();
  Serial.println("--------------------------------------");
}

///////////////////////////BOTONES ANALOGICOS////////////////////////////////////////////////////
///////////////////////////BOTONES ANALOGICOS////////////////////////////////////////////////////
void revisar_analogicos() {
  lectura_boton = analogRead(0);
  if (lectura_boton > 1000) {////sin pulsar nada
    botonpulsado = false;
    boton = 5;
  } else {
    nombreboton();
    estado_boton_ahora = boton;
    if (estado_boton_ahora != estado_boton_antes) {
      estado_boton_antes = estado_boton_ahora;
      millisantes = millis();
      botonpulsado = false;
    } else if (estado_boton_ahora == estado_boton_antes && millis() > (millisantes + 400)) {
      ///400 milisegundos para que te haga caso///antirebote
      if (!botonpulsado) { ////////anti pulsar y aguantar
        ///nombreboton();
        botonpulsado = true;
      } else {////////anti pulsar y aguantar
        boton = 5;
      }
    } else {////no ha hecho los 400 milisegundos///no hago nada, reseteo boton si no me mueve letra
      botonpulsado = false;
      boton = 5;
    }
  }
}
///String botones[] = {"select", "izquierda", "abajo", "arriba", "derecha", "nada"};
void nombreboton() {
  if (lectura_boton > 600 && lectura_boton < 700) {
    boton = 0;
  } else  if (lectura_boton > 350 && lectura_boton < 450) {
    boton = 1;
  } else  if (lectura_boton > 200 && lectura_boton < 300) {
    boton = 2;
  } else  if (lectura_boton > 50 && lectura_boton < 150) {
    boton = 3;
  } else if (lectura_boton >= 0 && lectura_boton < 50) {
    boton = 4;
  } else {
    boton = 5;
  }
}

void case_boton_analogico() {////switch case
  ///byte posletra[2] = {0, 0};   /////select 638;left 405;down 253;up 500;right 0;
  ///Serial.println("moverletra");
  //String botones[] = {"select", "izquierda", "abajo", "arriba", "derecha", "nada"};
  switch (boton) {
    case 0:///select
      if (posscroll < 3) {
        entrarsubmenu();
      } else if (posscroll == 4) {
        ajustar_hora();
      }
      break;
    case 1:///izquierda");////salir
      if (ajustandoalgo) {
        if (ajustandominuto) {
          ajustar_hora();
        } else if(ajustandohora){
          //salir_de_todo();
          salir_a_menu_inicio();
        }
      } else {
        salir_a_menu_inicio();
      }
      break;
    case 2:///abajo");
      if (ajustandoalgo) {
        restando();
      } else {
        ajustar_valores_encoder_sumando(false);///ves por que funciones??
      }
      break;
    case 3:///arriba");
      if (ajustandoalgo) {
        sumando();
      } else {
        ajustar_valores_encoder_sumando(true);///ves por que funciones??
      }
      break;
    case 4:///derecha");
      if (ajustandoalgo) {
        if (ajustandohora) {
          ajustar_minuto();
        }
      }
      if (posscroll < 3) {
        entrarsubmenu();
      } else if (posscroll > 10) {
        ///actuaremos si no es salir
        byte acabadoen = 0;
        acabadoen = posscroll % 10; ///resto de la division
        if (acabadoen != 4) { //distinto de///salir
          submenu_actuar(acabadoen);
        }
      }
      break;
    case 5://nada
      break;
    default:
      Serial.println("No vale ninguna de los valores anteriores");
  }
}
