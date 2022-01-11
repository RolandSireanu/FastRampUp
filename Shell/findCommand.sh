#!/bin/bash

# Find all files by user
find . -user daniel

# Find all directories with name nasa
# f = file , l = link , s = socket , d = directory
find . -name nasa -type d

# Find everything over 1MB
find ~/Movies/ -size +1024M

#The find command supports the -exec option that allows arbitrary commands 
#to be performed on found files. The following are equivalent.
# {} is a symbolic representation of the current pathname,
# exec command launches a new instance of the command for every file (pretty slow)
# By changing the semicolon to a "+" sign, we activate the ability of find to combine
# all the inputs into a single command
find ./foo -type f -name "*.txt" -exec rm {} \; 
find ./foo -type f -name "*.txt" | xargs rm     #way faster


# With "print0" find will separate the filenames with a null character (a zero ) 
find . -iname "*" -type f -print0 | xargs -0 tar -cvzf file.tar.gz

# Look for a pattern "ab" in every file
 find . -type f -exec grep ab {} \