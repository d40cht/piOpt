#!/bin/sh
g++ -DNDEBUG -mcpu=arm1176jzf-s -mfpu=neon -mfloat-abi=softfp -O2 -I eigen invTest/test.cpp -o invTest/test
#g++ -g -I eigen invTest/test.cpp -o invTest/test
