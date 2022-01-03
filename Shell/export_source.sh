#!/bin/sh
#Due to line above, a new shell is spawned to run the script

# We need to export the variable for it to be inherited by another program - including a shell script
# If we export the VAR before running the current script, the value will be propagated here
# export VAR=5   this means that "VAR values is 5"

echo VAR value is $VAR
VAR=25

# Any moddification to VAR will not be seen outside of the current shell, if the script has been executed ./test.sh

#If you want the var's moddifications outside :
# In order to receive environment changes back from the script, we must SOURCE the script - this effectively runs the script within our own interactive shell, instead of spawning another shell to run it.

echo New VAR value is $VAR