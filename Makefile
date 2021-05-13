# Makefile for project5
# Name: Hyungyu Park, Kevin Chu

CXXFLAGS = -std=c++11

all:	project5

project5: Main.o Network.o Road.o Town.o
	g++ -o $@ $^

Main.o:	Network.h
Network.o: Road.h Town.h Network.h
Road.o: Road.h
Town.o: Town.h