CC = clang
CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic

OBJDIR = ./obj
SRCDIR = ./src
HEADERFILES = ./inc
LIBRARYDIR = ./libmx

SRCFILES := $(wildcard $(SRCDIR)/*.c)
OBJFILES := $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCFILES))

BINARY = pathfinder
LIBRARY = libmx/libmx.a

.PHONY: $(LIBRARY)

all: $(BINARY)

$(BINARY): $(LIBRARY) $(OBJFILES)
	${CC} ${CFLAG} ${OBJFILES} -o ${BINARY} $(LIBRARY)

$(LIBRARY):
	cd $(LIBRARYDIR) && make

$(OBJFILES): | $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADERFILES)
	$(CC) $(CFLAGS) -o $@ -c $< -I $(HEADERFILES)

$(OBJDIR):
	mkdir -p $@

uninstall: clean
	cd $(LIBRARYDIR) && make uninstall
	rm -f $(BINARY)

clean:
	cd $(LIBRARYDIR) && make clean
	rm -r -f $(OBJDIR)

reinstall: uninstall all
