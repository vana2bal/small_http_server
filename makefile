# Compiler and Linker
CC = gcc
LC = gcc

# Main directories of the project
SRCDIR = ./src
INCDIR = ./include
BINDIR = ./bin
OBJDIR = ./build
DEPDIR = $(OBJDIR)/.d

# Defines Exec Name, Sources, Object Files and Make Dependance Files
EXEC = $(BINDIR)/smallhttpserver
SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
DEPS = $(SRCS:$(SRCDIR)/%.c=$(DEPDIR)/%.d)
$(shell mkdir -p $(DEPDIR)>/dev/null)

# Flags used by the CC and the LC
CFLAGS = -Wall -Werror -O3
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.Td
LDFLAGS =


# Various commands
COMPILE.c = $(CC) $(DEPFLAGS) $(CFLAGS) -I$(INCDIR) -o $@ -c
POSTCOMPILE = mv -f $(DEPDIR)/$*.Td $(DEPDIR)/$*.d

run : $(EXEC)

$(EXEC) : $(OBJS)
	$(LC) -o $@ $^ $(LDFLAGS)

$(OBJDIR)/%.o : $(SRCDIR)/%.c $(DEPDIR)/%.d
		$(COMPILE.c) $<
		$(POSTCOMPILE)

$(DEPDIR)/%.d: ;
.PRECIOUS: $(DEPDIR)/%.d

-include $(DEPS)
