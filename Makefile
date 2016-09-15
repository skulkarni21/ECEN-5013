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
CSTANDARD = -std=C99

#Creating CFLAGS common to all architecture
#-Wall to enable warnings put by the GCC
CFLAGS = -Wall

#Setting the optimisation level for GCC
CFLAGS += -O$(OPT)

#Setting the C standars
CFLAGS += $(CSTANDARD)

#----------------------------------------- Host Machine------------------------------------------------------
CC = gcc


