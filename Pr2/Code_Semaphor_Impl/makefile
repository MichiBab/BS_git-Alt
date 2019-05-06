TARGET   = Produce_Consume_Semaphore

CC       = gcc
# compiling flags here
CFLAGS   = 

LINKER   = gcc -o
# linking flags here
LFLAGS   = -Wall -I. -lm -lpthread -pthread

# change these to set the proper directories where each files shoould be
SRCDIR   = src
OBJDIR   = obj
TESTDIR   = test
INSTALLDIR = bin

SOURCES  := $(wildcard $(SRCDIR)/*.c)
INCLUDES := $(wildcard $(SRCDIR)/*.h)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
rm       = rm -f

all: dirs $(TESTDIR)/$(TARGET)

dirs: 
	mkdir -p $(TESTDIR)
	mkdir -p $(OBJDIR)
	mkdir -p $(INSTALLDIR)

$(TESTDIR)/$(TARGET): $(OBJECTS)
	@$(LINKER) $@ $(LFLAGS) $(OBJECTS)
	@echo "Linking complete!"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully!"

install: 
	cp $(TESTDIR)/* $(INSTALLDIR)/
	chmod 744 $(INSTALLDIR)/$(TARGET)

.PHONEY: clean
clean:
	@$(rm) $(OBJECTS)
	@echo "Cleanup complete!"

.PHONEY: remove
remove: clean
	rm -r $(TESTDIR)
	rm -r $(OBJDIR)
	rm -r $(INSTALLDIR)
	@echo "Executable removed!"
