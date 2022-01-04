#!/bin/bash

# $(command) is "command substitution".  As you seem to understand, it runs the command, captures its output, and inserts that into the command line that contains the $(…); e.g.

echo $(date)
# Tue Jan 4 19:24:09 GMT 2022



# {parameter} is a parameter substitution.
# The value of parameter is substituted. The braces are required when parameter is a positional parameter with more than one digit, or when parameter is followed by a character which is not to be interpreted as part of its name.

variable=20
echo $variable
echo ${variable}	#This form is usually used for more than 10 arguments ${10} , ${11}
			#Shell treats $11 as ${1}1, this is way we need ${11}
echo "$variable"

# !!! Note that you should always quote shell variables unless you have a good reason not to