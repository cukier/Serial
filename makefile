CC=ccsc
CFLAGS=+FH +LN -T -A -M -Z +DF +Y=9 +STDOUT

all: master slave

master: master.c
	$(CC) $(CFLAGS) master.c
	
slave: slave.c
	$(CC) $(CFLAGS) slave.c

clean:
	rm *.cof *.err *.esym *.hex *.lst