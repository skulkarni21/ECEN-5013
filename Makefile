#This is a Makefile for project 1 of the class ECEN5013
#Contribitors: Sarang Kulkarni
#			   Yu-Chih Cho
#
#
# This Makefile is aimed at being able to compile code on the host machine, Beaglebone Black and for the
# Freescale FRDM Boards.

#variables common to all environments

#Name of the Target file
TARGET = project

#Name of the source file
SRC = main.c

#Directory to put the object file. Dot(.) for current directory
OBJDIR = .

#Optimisation level for the compiler it can be [0,1,2,s]
OPT = 0

#C standard used for compilation
CSTANDARD = -std=gnu99

#Creating CFLAGS common to all architecture
#-Wall to enable warnings put by the GCC
CFLAGS = -Wall

#Setting the optimisation level for GCC
CFLAGS += -O$(OPT)

#Setting the C standars
CFLAGS += $(CSTANDARD)

#Default Target which compiles, links and creates output files
all: arch
	$(CC) $(CFLAGS) -o $(TARGET) main.c

#This target will determine the Architecture entered and will make changes to the variables
#accordingly
arch:
ifeq ($(ARCH),bbb)
	$(eval CC = arm-linux-gnueabihf-gcc)					     #Changing compiler for beaglebone
	$(eval CFLAGS += -march=armv7-a -mtune=cortex-a8 -mfpu=neon) #Modifying CFLAGS for Beaglebone
else ifeq ($(ARCH), frdm)
	$(eval CC = arm-none-eabi)
else
	$(eval CC = gcc)										#Default compiler will be gcc on host machine
endif

#Target for creating only preprocessed .i files
%.i : %.c
	$(CC) -E -I. $(CFLAGS) -o $@ $<

#Target for creating assembler files with .s extention
%.s : %.c
	$(CC) -S $(CFLAGS) -o $@ $<

#Target for creating object files. Obeject files can be stored in derectory mentioned by $(OBJDIR)
$(OBJDIR)/%.o : %.c
	$(CC) -c $(CFLAGS) -o $@ $<

#Target for cleaning all the files
clean:
	rm -f $(TARGET)
	rm -f *.i
	rm -f *.s
	rm -f $(OBJDIR)/*.o


