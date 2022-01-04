#!/bin/bash

# Brace expansion is a mechanism by which arbitrary string may be generated. It is similar to
# filename expansion, but the strings generated doesn't need to exist as files.
# { comma separated strings or a sequence expression }

echo {1..3}             => 1 2 3

#interpolation
echo {3..0}{0..3}		=> 30 31 32 33 20 21 22 23 10 11 12 13 00 01 02 03

echo {{3..0},{0..3}}		=> 3 2 1 0 0 1 2 3
a{{1..3},{a..c}}		=> a1 a2 a3 aa ab ac
touch "ps"{1..3}".py"		=> ps1.py ps2.py ps3.py
echo b{all,ell,oat}		=> ball bell boat

{a,b{1..3}{6..9},c} 		=> a b16 b17 b18 b19 b26 b27 b28 b29 b36 b37 b38 b39 c
{ab{1..3}{6..9},c}		=> ab16 ab17 ab18 ab19 ab26 ab27 ab28 ab29 ab36 ab37 ab38 ab39 c

ls {usr,usr/local}/{bin,sbin,lib}   => ls usr/bin 
                                    => ls usr/sbin 
                                    => ls usr/lib
                                    => ls usr/local/bin 
                                    ... 
                                    => ls usr/local/lib