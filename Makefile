SDIR=src
IDIR=include
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
OBJ_TEST = $(filter-out obj/lexer.o,$(OBJ))

TESTS = $(wildcard $(TESTSDIR)/*.c)

$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	@mkdir -p $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS)

$(OUTDIR)/$(OUTNAME): $(OBJ)
	@mkdir -p $(OUTDIR)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean check test

clean:
	rm -f $(ODIR)/*.o *~ core $(IDIR)/*~ $(OUTDIR)/$(OUTNAME) $(OUTDIR)/tests

check: $(TESTS) $(OBJ_TEST)
	@mkdir -p $(OUTDIR)
	gcc -o $(OUTDIR)/tests $^ `pkg-config --cflags --libs check` $(CFLAGS) $(LIBS)
	@./$(OUTDIR)/tests
	@rm -f $(OUTDIR)/tests

test:
	@make check