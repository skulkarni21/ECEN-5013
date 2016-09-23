# This is a Makefile for project 1 of the class ECEN5013
# Author:
# Sarang Kulkarni
#
# Group Members : Sarang Kulkarni Yu-Chih Cho
#
# This Makefile is aimed at being able to compile code on the host machine, Beaglebone Black and for the
# Freescale FRDM Boards.

# variables common to all environments

include source.mk
# Name of the Target file
TARGET = project

# Variables for Beaglebone and FRDM paths
BEAGLE_IP = 192.168.7.2
BEAGLE_USR = root
BEAGLE_PATH = /home/debian/bin

# Sets the shell command scp to UPLOAD variable
UPLOAD = scp

# Path to copy executable to FRDM
FRDM_PATH = /media/$$USER/FRDM-KL25Z

# Flags to generate dependencies
DEPFLAGS = -M ./dep/$(TARGET).dep

# Flags to generate map files
LDFLAGS = -Wl,-Map=$(TARGET).map

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
# CC = Compiler
# CFLAGS = Options for GCC compiler
# SIZE = mentions the GNU size
# OBJDUMP = mention the GNU objdump
# AR= mentions the GNU ar utility
# REMOTE = mentions the remote path to SCP

ifeq ($(ARCH),bbb)
CC = arm-linux-gnueabihf-gcc
CFLAGS += -march=armv7-a -mtune=cortex-a8 -mfpu=neon
SIZE = arm-linux-gnueabihf-size
OBJDUMP = arm-linux-gnueabi-objdump
AR = arm-linux-gnueabi-ar
REMOTE = $(BEAGLE_USR)@$(BEAGLE_IP):$(BEAGLE_PATH)

MESSAGE_ARCH = Compiling for BBB:

else ifeq ($(ARCH), frdm)
CC = arm-none-eabi-gcc
CFLAGS += -mcpu=cortex-m0plus -mthumb --specs=nosys.specs -march=armv6-m
SIZE = arm-none-eabi-size
OBJDUMP = arm-none-eabi-objdump
AR = arm-none-eabi-ar
REMOTE = $(FRDM_PATH)

MESSAGE_ARCH = Compiling for FRDM:

else
CC = gcc
SIZE = size
OBJDUMP = objdump
AR = ar

MESSAGE_ARCH = Compiling for host:
endif

#Target for building
build: message $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ_DIR)/*.o
	@if [ ! -d ./dep ]; then echo ;echo "Making directory for dependencies:"; mkdir ./dep;fi
	$(CC) -M -I $(INCLUDE) ./src/*.c > ./dep/$(TARGET).dep
	@echo
	@echo "Making map file:"
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ_DIR)/*.o --output $(TARGET).map
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

# Targets for creating assembler files w:qaith .s extention
asm: $(ASM)

%.s : %.i
	@if [ ! -d ./asm ];then mkdir ./asm ;fi
	$(CC) -S $(CFLAGS) -o $(ASM_DIR)/$@ $(PREPROC_DIR)/$<

# Targets for creating object files. Obeject files can be stored in derectory mentioned by $(OBJDIR)
compile-all: $(OBJ)

%.o : %.s
	@if [ ! -d ./obj ];then mkdir ./obj ;fi
	$(CC) -c $(CFLAGS) -o $(OBJ_DIR)/$@ $(ASM_DIR)/$<

# Target
objdump:
	$(OBJDUMP) -D $(TARGET)

upload:
	@if [ ! -f $(TARGET) ]; then echo ; echo " No executable, run make build first" ;echo ; exit 2; fi
	$(UPLOAD) $(TARGET) $(REMOTE)

build-lib:
	$(AR) cr libproject1.a ./obj/*.o

# Target for cleaning all the files
clean:
	@echo
	@echo "Cleaning directory:"
	rm -f $(TARGET)
	rm -rf $(PREPROC_DIR)
	rm -rf $(ASM_DIR)
	rm -rf $(OBJ_DIR)
	rm -rf ./dep
	rm -rf $(TARGET).map
	@echo

message:
	@echo
	@echo "Using the following compiler:"
	@ $(CC) --version
	@echo
	@echo $(MESSAGE_ARCH)

.PHONEY: arch asm build build-lib compile-all clean message objdump preprocess upload
