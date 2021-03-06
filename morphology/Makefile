ROOT=../bcl

CPPFLAGS = -I$(ROOT)/include -I.
CFLAGS   = -Wall -Wextra -Werror -pedantic -std=c99
LDFLAGS  = -L$(ROOT)/lib
LDLIBS   = -lbcl -lm

VIEWER = pvisu
DATA   = ../data

BIN=\
	make-se\
	labeling\
	dilation\
	erosion\
	opening\
	closing\
	add\
	substract\
	binarization\
	labeling-color

.PHONY: all
all: $(OBJ) $(BIN)

morphology.o: se.o
make-se: se.o
dilation: morphology.o se.o
erosion: morphology.o se.o
opening: morphology.o se.o
closing: morphology.o se.o
add: morphology.o se.o
substract: morphology.o se.o

.PHONY: extract-gear
extract-gear:
	$(VIEWER) $(DATA)/gear.ppm
	./opening 2 20 $(DATA)/gear.ppm a.ppm
	$(VIEWER) a.ppm
	./substract $(DATA)/gear.ppm a.ppm b.ppm
	$(VIEWER) b.ppm
	./binarization 200 255 b.ppm c.ppm
	$(VIEWER) c.ppm
	./labeling-color c.ppm result.ppm
	$(VIEWER) result.ppm

.PHONY: morphology-mrg morphology-lex morphology-bit
morphology-mrg: se.o
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o morphology.o $@.c
	make test-color
morphology-lex: se.o
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o morphology.o $@.c
	make test-color
morphology-bit: se.o
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o morphology.o $@.c
	make test-color

.PHONY: test-color
test-color: all
	./dilation 2 1 $(DATA)/mm-color.ppm a.ppm; #$(VIEWER) a.ppm

.PHONY: clean cleanall
clean:
	$(RM) *.o *.ppm
cleanall: clean
	$(RM) $(BIN)
