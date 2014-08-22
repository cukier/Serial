CC=ccsc
CFLAGS=+FH +LN -T -A -M -Z +P +DF +Y=9 +E

all: master slave

master: master.c
	$(CC) $(CFLAGS) master.c
	
slave: slave.c
	$(CC) $(CFLAGS) slave.c

clean:
	rm *.cof *.err *.esym *.hex *.lst