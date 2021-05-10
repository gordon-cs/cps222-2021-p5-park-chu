# Compiler flags: extra warnings (-Wall), debugging (-g), and Google Test
# Use C 2011 (required by Google Test, and a good idea anyway)
CXXFLAGS = -std=c++11

# -Wall and -Wextra requests more warnings -- fix them for clean code
# -g compiles for debugging
# CPPFLAGS = -I $(GTEST_ROOT)/include -Wall -Wextra -g

#Default target
all:	project5_main

# Build program for manual testing
project5_main: Main.o Network.o Road.o Town.o
	g++ -o $@ $^

# Dependencies
Main.o:	Network.h
Network.o: Road.h Town.h Network.h
Road.o: Road.h
Town.o: Town.h