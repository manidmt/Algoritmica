#!/bin/bash

#################################################### Cabecera ##################################################################

# 
# Autor: Aarón Jerónimo Fernández
# 
# Descripción: Ejecuta 25 veces con distintos tamaños (de forma creciente) un programa al que se le debe poder pasar como
# 	       argumento dicho tamaño. Después almacena en un archivo de texto ".txt" el resultado que imprima el programa llamado.
# 	       Además, va mostrando por pantalla el tamaño para el que se está ejecutando el programa en ese momento.
# 
# USO: "./macro.sh Arg1 Arg2 Arg3"
# Arg1: Nombre del programa que se quiere ejecutar
# Arg2: Tamaño inicial
# Arg3: Tamaño final
# 
# Recomendaciones: El programa llamado deberá llevar la cuenta del tiempo debidamente.
# 

################################################ Programa pricipal #############################################################

# Creación de variables
tam=$2
avance=$(($(($3-$2))/24))

# Compilación y creación del archivo de texo
g++ $1.cpp -o $1
# rm $1.txt

# Bucle principal
while [ $tam -le $3 ]
do
	echo "Tamaño actual: "$tam
	./$1 $tam &>> $1.txt
	tam=$(($tam+$avance))
done

# Fin del programa
echo "Ejecución finalizada correctamente."
