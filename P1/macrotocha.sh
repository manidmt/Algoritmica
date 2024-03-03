#!/bin/bash

rm insercion.txt
rm seleccion.txt
rm quicksort.txt
rm heapsort.txt
rm floyd.txt
rm hanoi.txt


echo "Inserción"
	./macro.sh insercion 10000 250000

echo "Selección"
	./macro.sh seleccion 10000 250000

echo "Quicksort"
	./macro.sh quicksort 10000 2000000

echo "Heapsort"
	./macro.sh heapsort 10000 2000000

echo "Floyd"
	./macro.sh floyd 100 2000

echo "Hanoi"
	./macro.sh heap 10 35
