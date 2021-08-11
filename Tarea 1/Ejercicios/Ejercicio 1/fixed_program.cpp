#include <iostream>
#include <vector>

using namespace std;

string linea;
vector<int> indexElementosID, indexElementosDI;
bool parejaEncontrada, malBalanceadaID, malBalanceadaDI, tieneAsterizco = false;
int caracterARevisar, elementosVector = 0, inicioIndexLinea, topeIndexLinea, asciiPareja, indexError;

int tieneParejaID(int indexCaracter){ // Revisamos el caracter y buscamos su pareja
  char caracter = linea[indexCaracter];

  parejaEncontrada = false;

  if(caracter == '('){
    asciiPareja = (int)caracter + 1; // En ascii el parentesis ) le sigue al (

    if(linea[indexCaracter + 1] == '*'){
      tieneAsterizco = true;
    }else{
      tieneAsterizco = false;
    }
  }else{
    asciiPareja = (int)caracter + 2; // Mientras que en el resto de agrupadores hay otro simbolo en medio
    tieneAsterizco = false;
  }

  if(elementosVector < 2){ // Si hay menos de 2 elementos se comienza desde la posición 0 y se va hasta el final de la cadena
    inicioIndexLinea = 1;
    topeIndexLinea = linea.length();
  }else{ // De lo contrario
    if(caracterARevisar > indexElementosID[elementosVector - 1]){ // Revisamos si el nuevo agrupador se encuentra dentro de otros
      inicioIndexLinea = indexElementosID[elementosVector - 1] + 1; // Si no, entonces leemos en un rango de una posición mas
      topeIndexLinea = linea.length(); // Hasta el final
    }else{
      inicioIndexLinea = indexElementosID[elementosVector - 2] + 1; // Si sí, entonces leemos entre una posición mas del abridor
      topeIndexLinea = indexElementosID[elementosVector - 1]; // Hasta el final de la agrupación
    }
  }

  for (int indexCaracterSiguiente = inicioIndexLinea; indexCaracterSiguiente < topeIndexLinea; indexCaracterSiguiente++) {
    if((int)linea[indexCaracterSiguiente] == asciiPareja){ // Se comprueba si es la pareja
      if(tieneAsterizco){
        if(indexCaracterSiguiente >= inicioIndexLinea){
          if(linea[indexCaracterSiguiente - 1] == '*' && indexCaracter != indexCaracterSiguiente - 2){
            indexElementosID.push_back(indexCaracter); // Se añaden los dos index al vector, el del abridor
            indexElementosID.push_back(indexCaracterSiguiente); // Y el de su pareja

            elementosVector += 2;
            parejaEncontrada = true;

            break;
          }
        }
      }else{
        if(caracter == '('){
          if(linea[indexCaracterSiguiente - 1] != '*'){
            if(indexCaracterSiguiente >= inicioIndexLinea){
              indexElementosID.push_back(indexCaracter); // Se añaden los dos index al vector, el del abridor
              indexElementosID.push_back(indexCaracterSiguiente); // Y el de su pareja

              elementosVector += 2;
              parejaEncontrada = true;

              break;
            }else{
              // cout << indexCaracterSiguiente << " <= " << inicioIndexLinea << endl;
            }
          }
        }else{
          indexElementosID.push_back(indexCaracter); // Se añaden los dos index al vector, el del abridor
          indexElementosID.push_back(indexCaracterSiguiente); // Y el de su pareja

          elementosVector += 2;
          parejaEncontrada = true;

          break;
        }
      }
    }
  }

  if(!parejaEncontrada){
    indexError = topeIndexLinea - 1;
    return 0;
  }else{
    return 1;
  }
}

int tieneParejaDI(int indexCaracter){ // Revisamos la cadena a la inversa
  char caracter = linea[indexCaracter];

  parejaEncontrada = false;

  if(caracter == ')'){
    asciiPareja = (int)caracter - 1; // En ascii el parentesis ( precede al )

    if(linea[indexCaracter - 1] == '*'){
      tieneAsterizco = true;
    }else{
      tieneAsterizco = false;
    }
  }else{
    asciiPareja = (int)caracter - 2; // Mientras que en el resto de agrupadores hay otro simbolo en medio
    tieneAsterizco = false;
  }

  if(elementosVector < 2){ // Si hay menos de 2 elementos se comienza desde la posición 0 y se va hasta el final de la cadena
    inicioIndexLinea = linea.length() - 2;
    topeIndexLinea = 0;
  }else{ // De lo contrario
    if(caracterARevisar < indexElementosDI[elementosVector - 1]){ // Revisamos si el nuevo agrupador se encuentra dentro de otros
      inicioIndexLinea = indexElementosDI[elementosVector - 1] - 1; // Si no, entonces leemos en un rango de una posición menos
      topeIndexLinea = 0; // Hasta el final
    }else{
      inicioIndexLinea = indexElementosDI[elementosVector - 2] - 1; // Si sí, entonces leemos entre una posición menos del abridor
      topeIndexLinea = indexElementosDI[elementosVector - 1]; // Hasta el final de la agrupación
    }
  }

  for (int indexCaracterSiguiente = inicioIndexLinea; indexCaracterSiguiente >= topeIndexLinea; indexCaracterSiguiente--) {
    if((int)linea[indexCaracterSiguiente] == asciiPareja){ // Se comprueba si es la pareja
      if(tieneAsterizco){
        if(indexCaracterSiguiente - 1 < inicioIndexLinea){
          if(linea[indexCaracterSiguiente + 1] == '*' && indexCaracter != indexCaracterSiguiente + 2){
            indexElementosDI.push_back(indexCaracter); // Se añaden los dos index al vector, el del abridor
            indexElementosDI.push_back(indexCaracterSiguiente); // Y el de su pareja

            elementosVector += 2;
            parejaEncontrada = true;

            break;
          }
        }
      }else{
        if(caracter == ')'){
          if(linea[indexCaracterSiguiente + 1] != '*'){
            if(indexCaracterSiguiente - 1 < inicioIndexLinea){
              indexElementosDI.push_back(indexCaracter); // Se añaden los dos index al vector, el del abridor
              indexElementosDI.push_back(indexCaracterSiguiente); // Y el de su pareja

              elementosVector += 2;
              parejaEncontrada = true;

              break;
            }
          }
        }else{
          indexElementosDI.push_back(indexCaracter); // Se añaden los dos index al vector, el del abridor
          indexElementosDI.push_back(indexCaracterSiguiente); // Y el de su pareja

          elementosVector += 2;
          parejaEncontrada = true;

          break;
        }
      }
    }
  }

  if(!parejaEncontrada){
    return 0;
  }else{
    return 1;
  }
}

int main() {
  while (getline(cin, linea)) { // Leemos la linea
    elementosVector = 0;
    caracterARevisar = 0;
    malBalanceadaID = false;
    malBalanceadaDI = false;

    while (caracterARevisar < linea.length()) { // Revisamos la linea caracter por caracter
      if(linea[caracterARevisar] == '(' || linea[caracterARevisar] == '['
      || linea[caracterARevisar] == '{' || linea[caracterARevisar] == '<'){
        if(!tieneParejaID(caracterARevisar)){ // Revisamos si tiene pareja
          if(topeIndexLinea == linea.length()){
            indexError = linea.length();
          }else{
            indexError = caracterARevisar;
          }
          malBalanceadaID = true; // Si no tiene terminamos la ejecución de la revision de la linea
          break;
        }
      }

      caracterARevisar++;
    }

    elementosVector = 0;
    caracterARevisar = linea.length() - 1;

    if(!malBalanceadaID){
      while (caracterARevisar > 0) { // Revisamos la linea caracter por caracter
        if(linea[caracterARevisar] == ')' || linea[caracterARevisar] == ']'
        || linea[caracterARevisar] == '}' || linea[caracterARevisar] == '>'){
          if(!tieneParejaDI(caracterARevisar)){ // Revisamos si tiene pareja
            indexError = caracterARevisar - 1;
            malBalanceadaDI = true; // Si no tiene terminamos la ejecución de la revision de la linea
            break;
          }
        }

        caracterARevisar--;
      }
    }

    if(malBalanceadaID || malBalanceadaDI){
      cout << "NO " << indexError + 1 << endl;
    }else{
      cout << "YES" << endl;
    }

    indexElementosDI.clear();
    indexElementosID.clear();
  }

  return 0;
}
