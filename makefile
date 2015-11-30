CC=/cygdrive/c/PICC/Ccsc.exe

UNIT=SERIAL
UNIT_FILE=main

CFLAGS=+FH +LN -T -A -M -Z +DF +Y=9 +STDOUT
DFLAGS=+FM +LN -T -A -M -Z +DF +Y=9 +STDOUT
OBJS=src/*.ccspjt src/*.cof src/*.err src/*.esym src/*.hex src/*.lst src/*.xsym

all: $(UNIT)

$(UNIT): src/$(UNIT_FILE).c
	$(CC) $(CFLAGS) src/$(UNIT_FILE).c
	mv $(OBJS) Debug

clean:
	rm Debug/*