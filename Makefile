SDIR=src
IDIR=$(SDIR)
ODIR=obj
LDIR=lib
OUTDIR=bin
TESTSDIR=tests
OUTNAME=lexer

CC=gcc
CFLAGS=-Wall -I$(IDIR)

LIBS=

_DEPS =
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = $(patsubst $(SDIR)/%.c,%.o,$(wildcard $(SDIR)/*.c))
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

TESTS = $(wildcard $(TESTSDIR)/*.c)

$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	@mkdir -p $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS)

$(OUTDIR)/$(OUTNAME): $(OBJ)
	@mkdir -p $(OUTDIR)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean check

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ $(OUTDIR)/$(OUTNAME) $(OUTDIR)/tests

check: $(TESTS)
	@mkdir -p $(OUTDIR)
	@gcc -o $(OUTDIR)/tests $^ `pkg-config --cflags --libs check`
	./$(OUTDIR)/tests
	@rm -f $(OUTDIR)/tests