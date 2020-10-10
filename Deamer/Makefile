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
	$(COMPILER) $(CPPFLAGS) $(CXXFLAGS) -o $@ -c $<

$(TREE): %:
	mkdir -p $@
	mkdir -p $(@:$(OBJDIR)%=$(DEPDIR)%)

clean:
	$(RM) -r $(OBJDIR) $(DEPDIR)

ifeq "$(MAKECMDGOALS)" ""
-include $(DEPS)
endif

install: uninstall $(OBJS)
	sudo cp -r $(HEADERSDIR) /usr/include/Deamer/
	ar rcs /usr/lib/Deamer/libDeamer.a $(OBJS)
	
uninstall:
	sudo rm -r -f /usr/include/Deamer/*
	sudo rm -f /usr/lib/Deamer/*
