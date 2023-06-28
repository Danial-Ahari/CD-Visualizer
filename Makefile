# This is the makefile for the RCEU 2023 project "Host-Based CD-ROM Data Recovery"

SRC_DIR := src
INCL_DIR := include
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
DEPS := $(wildcard $(INCL_DIR)/*.hpp)

cdvisualizer: $(SRC_FILES) $(DEPS)
	g++ $(SRC_FILES) $(DEPS) -o $@ `pkg-config --cflags --libs gtkmm-3.0`
	
clean:
	rm -f cdvisualizer
