## Lab1 TODO: create Makefile for functest here


#* version1
# # NAMES = 
# # SRCS =
# # BASE_PORT =
# # SIM_PATH = ## This is for running the simulator, you can ignore for Lab 1
# SRC_FILES = $(wildcard ./src/*.c)

# NAMES = $(basename $(notdir $(SRC_FILES)))
# SRCS = ./src/$(NAMES)
# # NAMES = add
# # SRCS = ./src/add
# BASE_PORT = ../base-port

# # -include ...
# -include $(BASE_PORT)/Makefile

#* version2
SRC_FILES = $(wildcard ./src/*.c)
NAMES = $(basename $(notdir $(SRC_FILES)))

.PHONY: all
all: $(NAMES)

%: src/%.c
	@echo "NAMES ?= $(basename $(@F))" > $@.mk
	@echo "SRCS ?= src/$(basename $(@F))" >> $@.mk
	@echo "BASE_PORT ?= ../base-port" >> $@.mk
	@echo "include ../base-port/Makefile" >> $@.mk
	@make -s -f $@.mk
	@rm -rf $@.mk

#* version3
# SRC_FILES = $(wildcard ./src/*.c)
# NAMES = $(basename $(notdir $(SRC_FILES)))

# .PHONY: all
# all: $(NAMES)

# %: src/%.c
# 	@NAMES=$(basename $(@F)) SRCS=src/$(basename $(@F)) BASE_PORT=../base-port \
# 	make -s -f ../base-port/Makefile

clean:
	@rm -rf ./build/