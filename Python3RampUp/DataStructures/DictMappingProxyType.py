# MappingProxyType makes read-only dictionaries 

from types import MappingProxyType 

writeable = {"one":1 , "two":2 , "three":3}

readonly = MappingProxyType(writeable)

readonly["one"] = -1;
