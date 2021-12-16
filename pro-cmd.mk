MKDIR := mkdir
RM := rm -r
CC := gcc
ERR_GENERATOR := error-generator
CFLAGS := $(addprefix -I,$(DIR_INC)) 
DEBUG := true

ifeq ($(DEBUG), true)
CFLAGS += -g
endif

LFLAGS := 