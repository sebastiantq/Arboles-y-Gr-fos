from sys import stdin

leyendo = True

numeroLinea = 0
numeroEquipos = 0
numeroPartidos = 0
equipos = []
tablaEquipos = []

def procesarLinea(lineaInput):
    global numeroLinea, numeroEquipos, numeroPartidos, equipos, puntosEquipos, leyendo

    linea = lineaInput

    if(len(linea) != 0):
        if(linea[0].isdigit()):
            linea = linea.split(' ')

            if(int(linea[0]) == 0 and int(linea[1]) == 0):
                ordenarTabla()

                leyendo = False

                return
            elif(numeroLinea != 0):
                ordenarTabla()

                numeroLinea = 0
                equipos.clear()
                tablaEquipos.clear()

                # with open('output.txt', 'a+') as output:
                #     output.write("\n")
                print("")

                procesarLinea(lineaInput)

                return

            numeroEquipos = int(linea[0])
            numeroPartidos = int(linea[1])
        elif(numeroLinea > 0 and numeroLinea <= numeroEquipos): # Leemos los nombres de los equipos
            equipos.append(linea)
            tablaEquipos.append([0, linea, 0, 0, 0, 0, 0, 0.0])
        elif(numeroLinea > numeroEquipos and numeroLinea <= numeroEquipos + numeroPartidos):
            linea = linea.split(" - ")

            equipo1 = linea[0].split(' ')
            equipo2 = linea[1].split(' ')

            # Incrementamos el número de paritdos jugados
            tablaEquipos[equipos.index(equipo1[0])][3] += 1
            tablaEquipos[equipos.index(equipo2[1])][3] += 1

            # Actualizamos los goles marcados
            tablaEquipos[equipos.index(equipo1[0])][4] += int(equipo1[1])
            tablaEquipos[equipos.index(equipo2[1])][4] += int(equipo2[0])

            # Actualizamos la diferencia de gol
            tablaEquipos[equipos.index(equipo1[0])][6] += int(equipo1[1])
            tablaEquipos[equipos.index(equipo2[1])][6] += int(equipo2[0])

            # Actualizamos los goles en contra
            tablaEquipos[equipos.index(equipo1[0])][5] -= -1 * int(equipo2[0])
            tablaEquipos[equipos.index(equipo2[1])][5] -= -1 * int(equipo1[1])

            # Actualizamos la diferencia de gol
            tablaEquipos[equipos.index(equipo1[0])][6] -= int(equipo2[0])
            tablaEquipos[equipos.index(equipo2[1])][6] -= int(equipo1[1])

            if(equipo1[1] > equipo2[0]):
                tablaEquipos[equipos.index(equipo1[0])][2] += 3
            elif(equipo1[1] == equipo2[1]):
                tablaEquipos[equipos.index(equipo1[0])][2] += 1
                tablaEquipos[equipos.index(equipo2[1])][2] += 1
            elif(equipo1[1] < equipo2[1]):
                tablaEquipos[equipos.index(equipo2[1])][2] += 3

            # Actualizamos el porcentaje de puntos ganados
            if(tablaEquipos[equipos.index(equipo1[0])][3] > 0):
                tablaEquipos[equipos.index(equipo1[0])][7] = "%0.2f" % ((tablaEquipos[equipos.index(equipo1[0])][2] / ((tablaEquipos[equipos.index(equipo1[0])][3]) * 3)) * 100)

            if(tablaEquipos[equipos.index(equipo2[1])][3] > 0):
                tablaEquipos[equipos.index(equipo2[1])][7] = "%0.2f" % ((tablaEquipos[equipos.index(equipo2[1])][2] / ((tablaEquipos[equipos.index(equipo2[1])][3]) * 3)) * 100)
        elif(numeroLinea == numeroEquipos + numeroPartidos + 1):
            numeroLinea = 0
            equipos.clear()
            tablaEquipos.clear()

            procesarLinea(lineaInput)
    else:
        ordenarTabla()
        leyendo = False
        return

    numeroLinea += 1

def ordenarTabla():
    global numeroLinea, numeroEquipos, numeroPartidos, equipos, puntosEquipos

    tablaEquipos.sort(key = lambda x: (-x[2], -x[6], -x[4], x[1].upper()))

    asignarPuestos()

    for equipo in range(len(tablaEquipos)):
        imprimirOutput(tablaEquipos[equipo])

def asignarPuestos():
    global tablaEquipos

    posicion = 1

    for equipo in range(len(tablaEquipos)):
        if(posicion > 1):
            if(tablaEquipos[equipo][2] != tablaEquipos[equipo - 1][2] or
               tablaEquipos[equipo][6] != tablaEquipos[equipo - 1][6] or
               tablaEquipos[equipo][4] != tablaEquipos[equipo - 1][4]):
               tablaEquipos[equipo][0] = posicion
        else:
            tablaEquipos[equipo][0] = posicion

        posicion += 1

def concatenarEspacios(cadena, numeroEspacios):
    for espacio in range(0, numeroEspacios):
        cadena += " "

    return cadena

def imprimirOutput(linea):
    if(linea[0] != 0):
        lineaIdentada = concatenarEspacios("", 2 - len(str(linea[0]))) + str(linea[0]) + "." # Posición
    else:
        lineaIdentada = concatenarEspacios("", 3)

    lineaIdentada = concatenarEspacios(lineaIdentada, 16 - len(linea[1])) + linea[1] # Nombre
    lineaIdentada = concatenarEspacios(lineaIdentada, 4 - len(str(linea[2]))) + str(linea[2]) # Puntos
    lineaIdentada = concatenarEspacios(lineaIdentada, 4 - len(str(linea[3]))) + str(linea[3]) # Partidos jugados
    lineaIdentada = concatenarEspacios(lineaIdentada, 4 - len(str(linea[4]))) + str(linea[4]) # Goles a favor
    lineaIdentada = concatenarEspacios(lineaIdentada, 4 - len(str(linea[5]))) + str(linea[5]) # Goles en contra
    lineaIdentada = concatenarEspacios(lineaIdentada, 4 - len(str(linea[6]))) + str(linea[6]) # Diferencia de gol

    if(linea[7] == 0 and numeroPartidos == 0): # Porcentaje de puntos
        lineaIdentada = concatenarEspacios(lineaIdentada, 4) + "N/A"
    else:
        lineaIdentada = concatenarEspacios(lineaIdentada, 7 - len(str(linea[7]))) + str(linea[7])

    # with open('output.txt', 'a+') as output:
        # output.write(lineaIdentada + "\n")
    print(lineaIdentada)

# with open('output.txt', 'w') as output: # Limpiamos el output
    # output.close()

# with open('input.txt', 'r') as input:

while leyendo:
    linea = stdin.readline()

    if linea:
        procesarLinea(linea.replace("\n", ""));
        if(len(linea) == 0):
            ordenarTabla()
            leyendo = False


    # input.close()
