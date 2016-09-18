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

# Name of the source file
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


# Optimisation level for the compiler it can be [0,1,2,s]
OPT = 0

# C standard used for compilation. C99 as per requrirement
CSTANDARD = -std=c99

# Creating CFLAGS common to all architecture
# -Wall to enable warnings put by the GCC
CFLAGS = -Wall

# Setting the optimisation level for GCC
CFLAGS += -O$(OPT)

# Setting the C standars
CFLAGS += $(CSTANDARD)

# Default Target which compiles, links and creates output files
#all: arch
#	$(CC) $(CFLAGS) -o $(TARGET) main.c

# This target will determine the Architecture entered and will make changes to the variables
# accordingly
ifeq ($(ARCH),bbb)
CC = arm-linux-gnueabihf-gcc
CFLAGS += -march=armv7-a -mtune=cortex-a8 -mfpu=neon
else ifeq ($(ARCH), frdm)
CC = arm-none-eabi-gcc
else
CC = gcc
endif

#Target for building
build: $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ_DIR)/*.o

# Targets for creating only preprocessed .i files
preprocess: $(PREPROC)

%.i : %.c
	@if [ ! -d ./preproc ]; then echo "Making preproc directory"; mkdir ./preproc ;fi
	$(CC) -E -I $(INCLUDE) $(CFLAGS) -o $(PREPROC_DIR)/$@ $<

# Targets for creating assembler files with .s extention
asm: $(ASM)

%.s : %.i
	@if [ ! -d ./asm ]; then echo "Making directory for asembly code"; mkdir ./asm ;fi
	$(CC) -S $(CFLAGS) -o $(ASM_DIR)/$@ $(PREPROC_DIR)/$<

# Targets for creating object files. Obeject files can be stored in derectory mentioned by $(OBJDIR)
compile-all: $(OBJ)

%.o : %.s
	@if [ ! -d ./obj ]; then echo "Making directory for object file"; mkdir ./obj ;fi
	$(CC) -c $(CFLAGS) -o $(OBJ_DIR)/$@ $(ASM_DIR)/$<

# Target for cleaning all the files
clean:
	rm -f $(TARGET)
	rm -rf $(PREPROC_DIR)
	rm -rf $(ASM_DIR)
	rm -rf $(OBJ_DIR)

.PHONEY: arch clean compile-all asm preprocess build
