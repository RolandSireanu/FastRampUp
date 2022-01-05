#!/bin/bash

# Awk seas spaces as delimiters for fields.
# Structure : awk [options] 'pattern {action}' file

# input_file:
# a b c
# 1 2 3

awk '{print $1,$3}' ./input_file		#This will print first and third fields in input_file
						# a c
						# 1 3
# $NF = number of fields
awk '{print$NF}' ./input_file 			# Print the last field

# Change fields separator from : to -
awk 'BEGIN{FS=":"; OFS="-"} {print $1,$6,$7}' /etc/passwd

# Items in column 2 that match yellow print the content of column 1
awk '$2=="yellow"{print $1}' colours.txt

# This condition looks at first column ($1) for a world that contains an "a" followed by at least 1 character
# and another "a" , and prints second column
# "~" means match , !~ "doesn't match"
awk '$1 ~ /a.+a/ {print $2}' ./input_file

# Numbers are interpreted naturally by awk. For instance, to print any row with a third column containing an integer greater than 5:
awk '$3>5 {print $1, $2}' colours.txt


# fields delimiter is "/" , accepts just the lines that matche the pattern specified between /pattern/
# /^\// = this means all the lines that start with a slash

awk -F "/" '/^\// {print $NF}' /etc/shells

# If you want a list with unique elements sorted
awk -F "/" '/^\// {print $NF}' /etc/shells | uniq | sort

# Take every row an replace first occurence of "ala" with "xyz" and print all the columns
awk  'sub(/ala/, "xyz") {print $0}' ./input_file

# Take every row and replace all occurences of "ala" with "xyz" and print all the columns
awk  'gsub(/ala/, "xyz") {print $0}' ./input_file