IDIR =../headers
CC=g++
CFLAGS=-I$(IDIR)

ODIR=obj
LDIR =../lib

LIBS=-lm -lGL -lGLU -lglut

_DEPS = camera.h constants.h moon.h planet.h solarsystem.h imageloader.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = camera.o main.o moon.o planet.o solarsystem.o imageloader.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.cpp $(DEPS)
	@ mkdir -p $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS)

solarsystem: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ solarsystem
	rmdir obj
