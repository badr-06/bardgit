#!/bin/bash

BUILD_DIR = build
CMAKE = cmake

.PHONY: all configure build run clean uninstall

all: build

configure:
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && $(CMAKE) ..

build: configure
	$(CMAKE) --build $(BUILD_DIR)

run: build
	./$(BUILD_DIR)/maze_qt

clean:
	rm -rf $(BUILD_DIR)

uninstall: clean
