PROJECT_NAME := Deamer
SRCDIR := ./lib
HEADERDIR := ./include
HEADERSDIR := $(shell find include/$(PROJECT_NAME)/ -type d -maxdepth 1)
OBJDIR := .obj
DEPDIR := .dep
CHEADERDIR := .cheader

COMPILER := clang++
COMPILER_ARGS := -Wall

SRCS     := $(shell find $(SRCDIR) -name "*.cpp")
OBJS     := $(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
DEPS     := $(SRCS:$(SRCDIR)/%.cpp=$(DEPDIR)/%.d)

HEADERS  := $(shell find $(HEADERDIR) -name "*.h")

TREE     := $(patsubst %/,%,$(dir $(OBJS)))
CPPFLAGS  = -MMD -MP -MF $(@:$(OBJDIR)/%.o=$(DEPDIR)/%.d)  $(COMPILER_ARGS) -I$(HEADERDIR)

.PHONY: all clean uninstall install

all: $(OBJS)

.SECONDEXPANSION:
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $$(@D)
ifdef debug
	$(COMPILER) $(CPPFLAGS) $(CXXFLAGS) -g -o $@ -c $<	
else
	$(COMPILER) $(CPPFLAGS) $(CXXFLAGS) -o $@ -c $<
endif
$(TREE): %:
	mkdir -p $@
	mkdir -p $(@:$(OBJDIR)%=$(DEPDIR)%)

clean:
	$(RM) -r $(OBJDIR) $(DEPDIR)

ifeq "$(MAKECMDGOALS)" ""
-include $(DEPS)
endif

install: uninstall
	mkdir -p ./$(PROJECT_NAME)
	ar rcs ./$(PROJECT_NAME)/lib$(PROJECT_NAME).a $(OBJS)

uninstall:
	sudo rm -f ./$(PROJECT_NAME)/*

install_into_system_dirs: uninstall_from_system_dirs $(OBJS)
	sudo cp -r $(HEADERSDIR) /usr/include/$(PROJECT_NAME)/
	ar rcs /usr/lib/$(PROJECT_NAME)/lib$(PROJECT_NAME).a $(OBJS)
	
uninstall_from_system_dirs:
	sudo rm -r -f /usr/include/$(PROJECT_NAME)/*
	sudo rm -f /usr/lib/$(PROJECT_NAME)/*
