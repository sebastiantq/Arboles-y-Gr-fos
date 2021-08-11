#include <iostream>
#include <vector>

using namespace std;

string linea;
bool impreso = false, imprimir = true;
int numeroListas, numeroLinea = 1, numeroElementos, posicionElemento, tiempo = 0, prioridadElemento;
vector<int> informacion, colaDePrioridad, vectorNumeroLeido;
vector<int>::iterator iteradorInformacion, iteradorColaDePrioridad, iteradorNumeroLeido;

int elevar(int base, int potenciaFinal){
  int potencia = 1, resultado = base;

  if(potenciaFinal == 0){
    return 1;
  }else{
    while (potencia < potenciaFinal){
      resultado = resultado * base;

      potencia++;
    }
  }

  return resultado;
}

void imprimirTiempo(){
  int temporal;

  iteradorInformacion = informacion.begin();
  iteradorColaDePrioridad = colaDePrioridad.begin();

  numeroElementos = *informacion.begin();
  posicionElemento = *(informacion.begin() + 1);
  prioridadElemento = *(colaDePrioridad.begin() + *(informacion.begin() + 1));

  while (!impreso) {
    for (int elemento = 0; elemento < numeroElementos; elemento++) {
      if(*(colaDePrioridad.begin() + elemento) > *colaDePrioridad.begin()){ // Verificamos si es el de mayor prioridad
        imprimir = false;
      }
    }

    // cout << "Pos: " << posicionElemento << " - Imprimir: "<< (int)imprimir << endl;

    if(posicionElemento == 0 && imprimir){
      tiempo++;
      cout << tiempo << endl;
      impreso = true;
    }else if(posicionElemento != 0 && imprimir){
      colaDePrioridad.erase(colaDePrioridad.begin());
      numeroElementos--;
      posicionElemento--;
      tiempo++;
    }else if(posicionElemento == 0 && !imprimir){
      temporal = *(colaDePrioridad.begin());
      colaDePrioridad.erase(colaDePrioridad.begin());
      colaDePrioridad.push_back(temporal);
      posicionElemento = numeroElementos - 1;
    }else{
      temporal = *colaDePrioridad.begin();
      colaDePrioridad.erase(colaDePrioridad.begin());
      colaDePrioridad.push_back(temporal);
      posicionElemento--;
    }

    imprimir = true;
  }

  // Reseteamos las variables

  tiempo = 0;
  impreso = false;
  imprimir = true;

  informacion.clear();
  colaDePrioridad.clear();

  return;
}

int main() {
  int digitos = 0, numeroLeido = 0;

  while (getline(cin, linea)) { // Leemos la linea
    if(numeroLinea == 1){ // Leemos cuantas listas hay por leer
      for (int caracter = 0; caracter < linea.length(); caracter++) { // Recorremos caracter a caracter la linea y guardamos la información en un vector
        if(linea[caracter] != ' '){
          digitos++;

          if(0 <= (int)linea[caracter] - 48 && (int)linea[caracter] - 48 <= 9){ // 48 = 0 y 57 == 9 en ASCII
            vectorNumeroLeido.push_back((int)linea[caracter] - 48);
          }
        }

        if(linea[caracter] == ' ' || caracter == linea.length() - 1){
          for (int digito = 0; digito < digitos; digito++) {
            numeroLeido += *(vectorNumeroLeido.begin() + digito) * elevar(10, (digitos - digito) - 1);
          }

          numeroListas = numeroLeido;

          digitos = 0;
        }
      }
    }

    digitos = 0;
    numeroLeido = 0;
    vectorNumeroLeido.clear();

    if(numeroLinea > 1){
      for (int caracter = 0; caracter < linea.length(); caracter++) { // Recorremos caracter a caracter la linea y guardamos la información en un vector
        if(linea[caracter] != ' '){
          digitos++;

          if(0 <= (int)linea[caracter] - 48 && (int)linea[caracter] - 48 <= 9){ // 48 = 0 y 57 == 9 en ASCII
            vectorNumeroLeido.push_back((int)linea[caracter] - 48);
          }
        }

        if(linea[caracter] == ' ' || caracter == linea.length() - 1){
          for (int digito = 0; digito < digitos; digito++) {
            numeroLeido += *(vectorNumeroLeido.begin() + digito) * elevar(10, (digitos - digito) - 1);
          }

          if(numeroLinea % 2 == 0){ // Identificamos si es información o es la cola de prioridad
            informacion.push_back(numeroLeido);
          }else{
            colaDePrioridad.push_back(numeroLeido);
          }

          digitos = 0;
          numeroLeido = 0;
          vectorNumeroLeido.clear();
        }
      }
    }

    if(numeroLinea > 1 && numeroLinea % 2 != 0){ // Si la linea es la cola de prioridad pasamos a imprimir su tiempo para vaciar los vectores
      imprimirTiempo();
    }

    numeroLinea++;
  }

  return 0;
}
