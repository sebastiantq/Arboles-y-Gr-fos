#include <iostream>
#include <stdio.h>
#include <cstring>

using namespace std;

int elementos = 0, *indexElementos;
string linea, *elementosEncontrados;
string::iterator iterador;

void printResult(){
  for (int index = 0; index < elementos; index++) {
    switch (elementosEncontrados[index][0]) {
      case '(':
        if(elementosEncontrados[elementos - 1 - index] != ")"){
          cout << "NO " << indexElementos[index] + 1;
          return;
        }
        break;
      case '[':
        if(elementosEncontrados[elementos - 1 - index] != "]"){
          cout << "NO " << indexElementos[index] + 1;
          return;
        }
        break;
      case '{':
        if(elementosEncontrados[elementos - 1 - index] != "}"){
          cout << "NO " << indexElementos[index] + 1;
          return;
        }
        break;
      case '<':
        if(elementosEncontrados[elementos - 1 - index] != ">"){
          cout << "NO " << indexElementos[index] + 1;
          return;
        }
        break;
      case '*':
        if(elementosEncontrados[elementos - 1 - index] != "*"){
          cout << "NO " << indexElementos[index];
          return;
        }
        break;
      default:
        break;
    }
  }

  cout << "YES";
}

void readLetter(string::iterator iterador){
  if(*iterador == '(' || *iterador == ')'
  || *iterador == '[' || *iterador == ']'
  || *iterador == '{' || *iterador == '}'
  || *iterador == '<' || *iterador == '>'){
    indexElementos[elementos] = iterador - linea.begin();
    elementosEncontrados[elementos] = *iterador;
    elementos++;
  }else if(*iterador == '*'){
    iterador--;

    if(*iterador == '('){
      iterador++;

      indexElementos[elementos] = iterador - linea.begin();
      elementosEncontrados[elementos] = *iterador;
      elementos++;
    }else{
      iterador++;
      iterador++;

      if(*iterador == ')'){
        iterador--;

        indexElementos[elementos] = iterador - linea.begin();
        elementosEncontrados[elementos] = *iterador;
        elementos++;
      }
    }
  }
}

int main() {
  while (getline(cin, linea)) {
    iterador = linea.begin();
    indexElementos = (int*)malloc(sizeof(int) * linea.length());
    elementosEncontrados = (string*)malloc(sizeof(string) * linea.length());

    while (iterador != linea.end()) {
      readLetter(iterador);
      iterador++;
    }

    printResult();

    cout << endl;

    elementos = 0;
  }

  free(indexElementos);
  free(elementosEncontrados);

  return 0;
}
