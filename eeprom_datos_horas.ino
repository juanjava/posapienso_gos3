///estructura memoria
/*
  0-5    5 bytes  hora minuto  cantidad (int)
  5-10    5 bytes  hora minuto  cantidad (int)
  10-15   5 bytes  hora minuto  cantidad (int)
  15-20   enable1 enable2 enable3
  20-25 fecha compilacion  dia mes año(22) hora minuto
*/

void cargar_variables_eeprom() {
  cargar_hora();
  cargar_horas_comidas();
  cargar_cantidades();
  cargar_enables();  
}
void cargar_horas_comidas(){
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 2; j++) {
      horas[i][j] = EEPROM.read((i * 5) + j);
      ///0*5 0 1*5 5
      ////ANTI EEPROM VACIA////
      if (j == 0) { ////la hora
        if (horas[i][j] > 23) {
          horas[i][j] = 23;
        }
      } else { /////MINUTO
        if (horas[i][j] > 59) {
          horas[i][j] = 59;
        }
      }////ANTI EEPROM VACIA////
    }
  }
}
void cargar_cantidades(){
  for (int i = 0; i < 3; i++) {
    byte aux = (i * 5) + 2;
     EEPROM.get(aux,cantidades[i]);
  }
}
void cargar_enables() {
  byte aux = 0;
  for (int i = 0; i < 3; i++) {
    aux = EEPROM.read(i + 15);
    ////quiero boolean 
    if (aux == 255) {
      comidas_habilitadas[i] = true;
    } else if (aux == 0) {
      comidas_habilitadas[i] = false;
    }else{
      comidas_habilitadas[i] = true;/////por si acaso
      }
  }
}

////////////////////GUARDAR////////////////////////////

void guardar_horario(int indice_horario) {
  if (indice_horario == 0) {
    int horas[3][2];
    EEPROM.update(0, horas[0][0]);
    EEPROM.update(1, horas[0][1]);
  } else if (indice_horario == 1) {
    EEPROM.update(5, horas[1][0]);
    EEPROM.update(6, horas[1][1]);
  } else if (indice_horario == 2) {
    EEPROM.update(10, horas[2][0]);
    EEPROM.update(11, horas[2][1]);
  } else {}
}
void guardarcantidad(byte comida, int cantidad) {
  EEPROM.put((comida * 5) + 2, cantidad);
  ///EEPROM.put(direccion, valor);
}
void guardar_enables(byte comida, boolean enable) {
  if(enable){
      EEPROM.put(15+comida, 255);
  ///EEPROM.put(direccion, valor);
  }else{///false
      EEPROM.put(15+comida, 0);
  }
}
