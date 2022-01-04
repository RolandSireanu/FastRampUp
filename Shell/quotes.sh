#!/bin/bash

echo Hello	World
echo "Hello 	World"
echo "Hello           World"

# The first and last " character wrap the whole lot into a single parameter passed to echo so
# that the spacing between the words is keept.

# Characters : " $ ` \ are still interpreted by the sheel even if they are in double quotes.
MY_VAR=3
echo "MY_VAR=$MY_VAR"