# This is a Makefile for project 1 of the class ECEN5013
# Author:
# Sarang Kulkarni
#
#
#
# This Makefile is aimed at being able to compile code on the host machine, Beaglebone Black and for the
# Freescale FRDM Boards.

# variables common to all environments

# Declaring vpath variables
vpath %.c src
vpath %.i preproc
vpath %.o obj

INCLUDE = ./include
# Name of the Target file
TARGET = project

# Name of the source files
SRC = main.c add.c

#Directory to put the preprocessor files and variable to store all preprocessed files
PREPROC_DIR =./preproc
PREPROC = $(patsubst %.c,%.i,$(SRC))

#Directory to put the asembly files and variable to store all assembly files
ASM_DIR = ./asm
ASM= $(patsubst %.i, %.s, $(PREPROC))

# Directory to put the object file. Dot(.) for current directory and variable to store all OBJ files
OBJ_DIR = ./obj
OBJ = $(patsubst %.s, %.o, $(ASM))

# Flags to generate dependencies
DEPFLAGS = -M ./dep/make.dep

# Flags to generate map files
LDFLAGS = -Wl,-Map=make.map

# Optimisation level for the compiler it can be [0,1,2,s]
OPT = 0

# C standard used for compilation. C99 as per requrirement
CSTANDARD = -std=c99

# Creating CFLAGS common to all architecture
# -Wall to enable warnings put by the GCC
#  -g to eanble debug
CFLAGS = -Wall -g

# Setting the optimisation level for GCC
CFLAGS += -O$(OPT)

# Setting the C standars
CFLAGS += $(CSTANDARD)

# This target will determine the Architecture entered and will make changes to the variables
# accordingly
ifeq ($(ARCH),bbb)
CC = arm-linux-gnueabihf-gcc
CFLAGS += -march=armv7-a -mtune=cortex-a8 -mfpu=neon
SIZE = arm-linux-gnueabihf-size
OBJDUMP = arm-linux-gnueabi-objdump


MESSAGE_ARCH = Compiling for BBB:


else ifeq ($(ARCH), frdm)
CC = arm-none-eabi-gcc
SIZE = arm-none-eabi-size
OBJDUMP = arm-none-eabi-objdump

MESSAGE_ARCH = Compiling for FRDM:
else
CC = gcc
SIZE = size
OBJDUMP = objdump

MESSAGE_ARCH = Compiling for host:
endif

#Target for building
build: message $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ_DIR)/*.o
	@if [ ! -d ./dep ]; then echo ;echo "Making directory for dependencies:"; mkdir ./dep;fi
	$(CC) -M -I $(INCLUDE) ./src/*.c > ./dep/make.dep
	@echo
	@echo "making map file:"
	$(CC) $(LDFLAGS) $(OBJ_DIR)/*.o --output make.map
	@echo
	@echo "Displaying size of executable:"
	$(SIZE) $(TARGET)
# Targets for creating only preprocessed .i files
preprocess: $(PREPROC)

%.i : %.c
	@echo
	@echo "Compiling:$<"
	@if [ ! -d ./preproc ];then mkdir ./preproc ;fi
	$(CC) -E -I $(INCLUDE) $(CFLAGS) -o $(PREPROC_DIR)/$@ $<

# Targets for creating assembler files with .s extention
asm: $(ASM)

%.s : %.i
	@if [ ! -d ./asm ];then mkdir ./asm ;fi
	$(CC) -S $(CFLAGS) -o $(ASM_DIR)/$@ $(PREPROC_DIR)/$<

# Targets for creating object files. Obeject files can be stored in derectory mentioned by $(OBJDIR)
compile-all: $(OBJ)

%.o : %.s
	@if [ ! -d ./obj ];then mkdir ./obj ;fi
	$(CC) -c $(CFLAGS) -o $(OBJ_DIR)/$@ $(ASM_DIR)/$<

objdump:
	$(OBJDUMP) -D $(TARGET)
# Target for cleaning all the files
clean:
	@echo
	@echo "Cleaning directory:"
	rm -f $(TARGET)
	rm -rf $(PREPROC_DIR)
	rm -rf $(ASM_DIR)
	rm -rf $(OBJ_DIR)
	rm -rf ./dep
	rm -rf make.map
	@echo

message:
	@echo
	@echo $(MESSAGE_ARCH)

.PHONEY: arch clean compile-all asm preprocess build
