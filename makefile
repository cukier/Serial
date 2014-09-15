CC=ccsc
CFLAGS=+FH +LN -T -A -M -Z +DF +Y=9 +STDOUT
DFLAGS=+FM +LN -T -A -M -Z +DF +Y=9 +STDOUT

all: master slave sim

master: master.c
	$(CC) $(CFLAGS) master.c
	
slave: slave.c
	$(CC) $(CFLAGS) slave.c
	
sim: sim.c
	$(CC) $(DFLAGS) sim.c

clean:
	rm *.cof *.err *.esym *.hex *.lst