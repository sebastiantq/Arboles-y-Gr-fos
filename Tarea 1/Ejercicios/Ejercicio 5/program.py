from sys import stdin

leyendo = True

numeroLinea = 1
numeroCasos = 0
numeroMedicaciones = 0
numeroMinimoDosis = 0
medicamentos = []
orden = []

impresiones = 0

def imprimirResultados():
    global numeroLinea, numeroCasos, numeroMedicaciones, numeroMinimoDosis, medicamentos, orden, impresiones

    for dosis in range(1, numeroMinimoDosis + 1):
        for medicamento in range(0, numeroMedicaciones):
            orden.append([medicamentos[medicamento][1] * dosis, medicamentos[medicamento][0], medicamentos[medicamento][2]])

    orden.sort(key = lambda dosis : (dosis[0], dosis[2]))

    for line in range(0, numeroMinimoDosis):
        print(str(orden[line][0]) + " " + orden[line][1])
        with open('output.txt', 'a+') as output:
            output.write(str(orden[line][0]) + " " + orden[line][1] + "\n")

    impresiones += 1


def procesarLinea(lineaInput):
    global numeroLinea, numeroCasos, numeroMedicaciones, numeroMinimoDosis, medicamentos

    if(numeroLinea == 1):
        numeroCasos = int(lineaInput)
    elif(numeroLinea == 2):
        linea = lineaInput.split(" ")

        numeroMedicaciones = int(linea[0])
        numeroMinimoDosis = int(linea[1])
    elif(not lineaInput[0].isdigit()):
        linea = lineaInput.split(" ")

        medicamento = [linea[0], int(linea[1]), numeroLinea]
        medicamentos.append(medicamento)
    else:
        imprimirResultados()

        numeroLinea = 2

        medicamentos.clear()
        orden.clear()

        procesarLinea(lineaInput)

        return

    numeroLinea += 1

with open('output.txt', 'w') as output: # Limpiamos el output
    output.close()

# with open('input.txt', 'r') as input:

while leyendo:
    linea = stdin.readline()

    if linea:
        procesarLinea(linea.replace("\n", ""));

        if(impresiones == numeroCasos - 1 and numeroLinea == numeroMedicaciones + 3):
            imprimirResultados()
            leyendo = False

# input.close()
