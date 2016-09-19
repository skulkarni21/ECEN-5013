
# Declaring vpath variables
vpath %.c src
vpath %.i preproc
vpath %.o obj

# Name of the source files
SRC = main.c memory.c project_1.c

INCLUDE = ./include

#Directory to put the preprocessor files and variable to store all preprocessed files
PREPROC_DIR =./preproc
PREPROC = $(patsubst %.c,%.i,$(SRC))

#Directory to put the asembly files and variable to store all assembly files
ASM_DIR = ./asm
ASM= $(patsubst %.i, %.s, $(PREPROC))

# Directory to put the object file. Dot(.) for current directory and variable to store all OBJ files
OBJ_DIR = ./obj
OBJ = $(patsubst %.s, %.o, $(ASM))
