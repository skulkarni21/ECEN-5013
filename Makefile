# This is a Makefile for project 1 of the class ECEN5013
# Author:
# Sarang Kulkarni
#
#
#
# This Makefile is aimed at being able to compile code on the host machine, Beaglebone Black and for the
# Freescale FRDM Boards.

# variables common to all environments

# Name of the Target file
TARGET = project

# Name of the source file
SRC = $(wildcard *.c)

#Directory to put the preprocessor files and variable to store all preprocessed files
PREPROC_DIR =.
PREPROC = $(patsubst %.c,%.i,$(SRC))

#Directory to put the asembly files and variable to store all assembly files
ASMDIR = .
ASM= $(patsubst %.i, %.s, $(PREPROC))

# Directory to put the object file. Dot(.) for current directory and variable to store all OBJ files
OBJDIR = .
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
all: arch
	$(CC) $(CFLAGS) -o $(TARGET) main.c

# This target will determine the Architecture entered and will make changes to the variables
# accordingly
arch:
ifeq ($(ARCH),bbb)
# Eval is used for telling the makefile to evaluate the expressiom and assign the variable
	$(eval CC = arm-linux-gnueabihf-gcc)
	$(eval CFLAGS += -march=armv7-a -mtune=cortex-a8 -mfpu=neon)
else ifeq ($(ARCH), frdm)
	$(eval CC = arm-none-eabi-gcc)
else
	$(eval CC = gcc)
endif

#Target for building
build: arch $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $^

# Targets for creating only preprocessed .i files
preprocess: arch $(PREPROC)

%.i : %.c
	$(CC) -E -I. $(CFLAGS) -o $@ $<

# Targets for creating assembler files with .s extention
asm: arch $(ASM)

%.s : %.i
	$(CC) -S $(CFLAGS) -o $@ $<

# Targets for creating object files. Obeject files can be stored in derectory mentioned by $(OBJDIR)
compile-all: arch $(OBJ)

$(OBJDIR)/%.o : %.s
	$(CC) -c $(CFLAGS) -o $@ $<

# Target for cleaning all the files
clean:
	rm -f $(TARGET)
	rm -f *.i
	rm -f *.s
	rm -f $(OBJDIR)/*.o

.PHONEY: arch
