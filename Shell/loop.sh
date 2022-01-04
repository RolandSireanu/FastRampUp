#!/bin/bash

for i in 1 2 3
do
	echo "Loop number $i"
done

for i in salut 1 * 2 goodbye
do
	echo "Loop number $i"
done


while [ "$INPUT" != "bye" ]
do
	echo "Tell me something : "
	read INPUT
	echo "You told me $INPUT"
done