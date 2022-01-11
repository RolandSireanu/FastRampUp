# xargs command helps applications like mkdir rm echo that can't accept params
# as standard in.

# By default xargs reads items from standard input as separated by blanks 
# and executes a command once for each argument

# Print command to be executed -t
echo 'one two three' | xargs -t rm