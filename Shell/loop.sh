#!/bin/bash

for i in 1 2 3
do
	echo "Loop number $i"
done

for i in salut 1 * 2 goodbye
do
	echo "Loop number $i"
done

for ((i=0; i<10; i++))
do
	echo "Counter $i"
done

for i in $(seq 0 10)
do
	echo "Counter $i"

done

i=0
while [[ $i -lt 10 ]]
do
	echo "Counter $i"
	let i++
done

while [ "$INPUT" != "bye" ]
do
	echo "Tell me something : "
	read INPUT
	echo "You told me $INPUT"
done