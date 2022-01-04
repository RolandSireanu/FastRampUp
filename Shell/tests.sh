#!/bin/bash


# test is not often called directly. test is more frequently called as [. [ is a symbolic link to test, just to make shell programs more readable.
# if [$foo="bar"]  	 This will not work, it is interpreted as if test$foo = "bar" ]

# Tests :
# equality string => =
# equality int    => -eq

# semicolon ";" it is used for joining two line together
# The backslash (\) serves a similar, but opposite purpose: it tells the shell that this is not the end of the line, but that the following line should be treated as part of the current line.


comparison()
{
	if [ -n "$1" ]; then
		if [ "$1" -lt "0" ]; then
			echo "Argument is smaller than 0 "
		fi

		if [ "$1" -gt "0" ]; then
			echo "Argument is greater than 0"
		fi

		# String comparison
		if [ "$1" = "0" ]
		then
			echo "Argument is the string 0"
		fi

		if [ "$1" != "Hello" ]; then
			echo "Argument is not Hello"
		fi
	else
		echo "No argument has been provided"
	fi
}


check_if_exists()
{
	if [ -f "$1" ]; then
		if [ -x "$1" ]; then
			echo "File exists and it is executable "
		else
			echo "File exists"
		fi
	else
		echo "File doesn't exists"
	fi

	if [ "$1" -nt "/etc/passwd" ]; then
		echo "File is newer than passwd"
	fi

}


comparison 2
comparison "0"
comparison
check_if_exists /tmp/GMT
check_if_exists /bin/ls