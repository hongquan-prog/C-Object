.PHONY: all clean

SRCS := $(wildcard $(DIR_SRC)/*$(TYPE_SRC))
SRCS := $(notdir $(SRCS))
OBJS := $(SRCS:$(TYPE_SRC)=$(TYPE_OBJ))
DEPS := $(SRCS:$(TYPE_SRC)=$(TYPE_DEP))
OBJS := $(addprefix $(DIR_BUILD)/,$(OBJS))
DEPS := $(addprefix $(DIR_BUILD)/,$(DEPS))

all: $(ERROR_OUTPUT) $(APP)

$(ERROR_OUTPUT): $(ERROR_INPUT)
	error-generator -i=$^ -o=$@ -input-begin=$(ERROR_BEGIN) -input-end=$(ERROR_END) -output-begin=$(OUTPUT_BEGIN) -output-end=$(OUTPUT_END)

$(APP):$(OBJS)
	$(CC) -o $@ $^

ifeq ("$(MAKECMDGOALS)", "all")
-include $(DEPS)
endif

ifeq ("$(MAKECMDGOALS)", "")
-include $(DEPS)
endif

ifeq ("$(wildcard $(DIR_BUILD))","")
$(DIR_BUILD)/%$(TYPE_DEP):$(DIR_BUILD) %$(TYPE_SRC)
else
$(DIR_BUILD)/%$(TYPE_DEP):%$(TYPE_SRC)
endif
	$(CC) $(CFLAGS) -MM -E $(filter %$(TYPE_SRC), $^) | sed 's,\(.*\)\.o[ :]*,$(DIR_BUILD)/\1.o $@:,g' > $@

$(DIR_BUILD)/%$(TYPE_OBJ):%$(TYPE_SRC)
	$(CC) $(CFLAGS) -o $@ -c $(filter %$(TYPE_SRC), $^)

$(DIR_BUILD):
	$(MKDIR) $@

clean:
	$(RM) $(DIR_BUILD)
