MKDIR := mkdir
RM := rm -r
CC := gcc
CFLAGS := $(addprefix -I,$(DIR_INC)) 
DEBUG := true

ifeq ($(DEBUG), true)
CFLAGS += -g
endif

LFLAGS := 