CC=/cygdrive/c/PICC/Ccsc.exe
CFLAGS=+FH +LN -T -A -M -Z +DF +Y=9 +STDOUT
DFLAGS=+FM +LN -T -A -M -Z +DF +Y=9 +STDOUT
objs=src/*.ccspjt src/*.cof src/*.err src/*.esym src/*.hex src/*.lst src/*.xsym

all: master slave sim

master: src/master.c
	$(CC) $(CFLAGS) src/master.c
	mv $(objs) Debug
	
slave: src/slave.c
	$(CC) $(CFLAGS) src/slave.c
	mv $(objs) Debug
	
sim: src/sim.c
	$(CC) $(DFLAGS) src/sim.c
	mv $(objs) Debug

clean:
	rm Debug/*