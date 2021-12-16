DIR_SRC := .
DIR_INC := . 

TYPE_INC := .h
TYPE_SRC := .c
TYPE_OBJ := .o 
TYPE_DEP := .dep 

DIR_PROJECT := $(realpath .)
DIR_BUILD := build
HOST_NAME := $(shell uname)

ERROR_INPUT := err.h
ERROR_BEGIN := "// error code begin"
ERROR_END := "// error code end"

ERROR_OUTPUT := err.c
OUTPUT_BEGIN := "// generate begin"
OUTPUT_END := "// generate end"

APP := $(DIR_BUILD)/target