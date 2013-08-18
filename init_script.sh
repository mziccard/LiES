#!/bin/sh

# Extracting solver dir from JAR
jar -xf LiES.jar csolver/

# Building solver
cd csolver
make
cd ..
mv csolver/main solver

# Removing source files and other stuff
rm -rf csolver

# Executing JAR
java -jar LiES.jar
