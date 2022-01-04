#!/bin/bash


while read dep
do
	apt-get install $dep -y
done < dependencies_file