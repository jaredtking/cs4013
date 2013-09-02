SDIR=src
IDIR=include
LDIR=lib
ODIR=obj

CC=gcc
CFLAGS=-Wall -I$(IDIR)

LIBS=

_DEPS =
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = $(patsubst $(SDIR)/%.c,%.o,$(wildcard $(SDIR)/*.c))
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	mkdir -p $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS)

all: $(OBJ)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
