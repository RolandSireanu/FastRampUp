#!/bin/bash

# You can specify many files at once using expansions, also called globbing.

# Shell looks for a single character to replace the "?"
# Files in current directory :
# log1_system log2_user log3_login
ls log?*          	=> log1_system log2_user log3_login

# If any single character within the brackets matches a file, that file is displayed.
ls log[13]*    		=> log1_system log3_login

# Same as above but it is looking inside a range
# Other useful ranges [0-9] , [a-z] , [A-Z]
ls log[1-3]*		=> all files

# "*" means zero or more characters
ls log*_*		=> all files

# Print any files with a number in name
ls *[0-9]*		=> all files