CC=mpicc
CFLAGS=-O3 -Wall
LDFLAGS=
LIBS=-lpng -lm

EXE=heat_mpi
OBJS=core.o setup.o utilities.o io.o main.o pngwriter.o

all: $(EXE)

# Esta es una regla de sufijo para compilar cualquier archivo .c en un archivo .o.
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Dependencias para archivos de objeto. 
# Esto le dice a make que recompile los archivos de objeto si el archivo de encabezado heat.h cambia.
core.o setup.o utilities.o io.o main.o: heat.h
pngwriter.o: pngwriter.h

$(EXE): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS) $(LIBS)

clean:
	rm -f $(EXE) a.out *.o *.png *~
