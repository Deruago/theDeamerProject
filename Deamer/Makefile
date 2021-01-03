SRCDIR := ./lib
HEADERDIR := ./include
HEADERSDIR := $(shell find include/Deamer/ -type d -maxdepth 1)
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
	mkdir -p ./Deamer
	ar rcs ./Deamer/libDeamer.a $(OBJS)

uninstall:
	sudo rm -f ./Deamer/*

install_into_system_dirs: uninstall_from_system_dirs $(OBJS)
	sudo cp -r $(HEADERSDIR) /usr/include/Deamer/
	ar rcs /usr/lib/Deamer/libDeamer.a $(OBJS)
	
uninstall_from_system_dirs:
	sudo rm -r -f /usr/include/Deamer/*
	sudo rm -f /usr/lib/Deamer/*
