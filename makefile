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

.PHONY : run
run : $(EXEC)

$(EXEC) : $(OBJS)
	$(LC) -o $@ $^ $(LDFLAGS)

$(OBJDIR)/%.o : $(SRCDIR)/%.c $(DEPDIR)/%.d
		$(COMPILE.c) $<
		$(POSTCOMPILE)

$(DEPDIR)/%.d : ;
.PRECIOUS : $(DEPDIR)/%.d

.PHONY : clean
clean :
	rm -f $(OBJDIR)/*.o
	rm -f $(DEPDIR)/*.d

.PHONY : purge
purge : clean
		rm -f $(EXEC)

.PHONY : rebuild
rebuild : purge run

.PHONY : help
help:
	@echo "Makefile for the small http server"
	@echo "Options are:"
	@echo ""
	@echo "run:     Incremental build of the server"
	@echo "clean:   Remove all object and deps files from build directory"
	@echo "purge:   clean + remove already produced bin"
	@echo "rebuild: purge + run"

-include $(DEPS)
