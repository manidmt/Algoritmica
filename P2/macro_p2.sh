#!/bin/bash

# Comprobamos argumentos
if !(( $# == 2 )); then
    echo "Error en argumentos: <inicio> <final>"
    exit 1
fi

# Argumentos
INICIO=$1
FINAL=$2

# Constantes
N=25
SALTO=$(( ($FINAL-$INICIO)/($N-1) ))
MEDIO=$(( ($FINAL-$INICIO)/2 ))
PROGRAMA="algoritmos"

# Main

rm out_$PROGRAMA.txt

echo "K  N  T_PROPUESTO T_NUESTRO T_BRUTO T_OTRO" >> out_$PROGRAMA.txt

g++ $PROGRAMA.cpp -o $PROGRAMA 

for ((i=$INICIO; i<=$FINAL; i+=$SALTO)) 
do
    ./$PROGRAMA $i $i >> out_$PROGRAMA.txt
done

printf "\n\n" >> out_$PROGRAMA.txt

for ((i=$INICIO; i<=$FINAL; i+=$SALTO)) 
do
    ./$PROGRAMA $i $MEDIO >> out_$PROGRAMA.txt
done

printf "\n\n" >> out_$PROGRAMA.txt

for ((i=$INICIO; i<=$FINAL; i+=$SALTO)) 
do
    ./$PROGRAMA $i $MEDIO >> out_$PROGRAMA.txt
done