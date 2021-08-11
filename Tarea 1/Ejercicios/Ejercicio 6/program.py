import copy
from sys import stdin

leyendo = True

numeroLinea = 1
numeroElecciones = 0
numeroCandidatos = 0
numeroVotos = 0
votos = []

resultadosImpresos = 0

votoTemporal = []

def imprimirResultados():
    global numeroLinea, numeroCandidatos, numeroVotos, votos, resultadosImpresos

    mayoriaVotos = 0
    indexMayoriaVotos = 0
    hayGanador = True

    for voto in range(len(votos)):
        if(votos[voto][2] > mayoriaVotos):
            indexMayoriaVotos = voto
            mayoriaVotos = votos[voto][2]

    for voto in range(len(votos)):
        if(votos[voto][2] >= mayoriaVotos and voto != indexMayoriaVotos):
            hayGanador = False

    if(hayGanador):
        print(votos[indexMayoriaVotos][1])
        # with open('output.txt', 'a+') as output:
            # output.write(votos[indexMayoriaVotos][1] + "\n")
    else:
        print("tie")
        # with open('output.txt', 'a+') as output:
            # output.write("tie\n")

    resultadosImpresos += 1

    if(resultadosImpresos < numeroElecciones):
        print("")
        # with open('output.txt', 'a+') as output:
            # output.write("\n")

def procesarLinea(lineaInput):
    global numeroLinea, numeroElecciones, numeroCandidatos, numeroVotos, votos, votoTemporal

    if(len(lineaInput) != 0):
        if(lineaInput[0].isdigit()):
            if(numeroElecciones == 0):
                numeroElecciones = int(lineaInput)
            elif(numeroCandidatos == 0):
                numeroCandidatos = int(lineaInput)
            elif(numeroVotos == 0):
                numeroVotos = int(lineaInput)
        else:
            if(numeroLinea <= (numeroCandidatos * 2) + 3):
                if(numeroLinea % 2 == 0):
                    votoTemporal.append(lineaInput)
                else:
                    votoTemporal.append(lineaInput)
                    votoTemporal.append(0)
                    votos.append(copy.copy(votoTemporal))
                    votoTemporal.clear()
            else:
                for voto in range(len(votos)):
                    if(votos[voto][0] == lineaInput):
                        votos[voto][2] += 1
                        break

                # print(numeroLinea)

                if(numeroCandidatos != 0 and numeroVotos != 0):
                    if(numeroLinea == (numeroCandidatos * 2) + numeroVotos + 4):
                        imprimirResultados()
    elif(numeroLinea > 3):
        numeroLinea = 2
        numeroCandidatos = 0
        numeroVotos = 0

        votos.clear()


    numeroLinea += 1

# with open('output.txt', 'w') as output: # Limpiamos el output
    # output.close()

# with open('input.txt', 'r') as input:

while leyendo:
    linea = stdin.readline()

    if linea:
        procesarLinea(linea.replace("\n", ""));

        if(numeroElecciones == resultadosImpresos):
            leyendo = False

    # input.close()
