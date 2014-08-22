CC=ccsc
CFLAGS=+FH +LN -T -A -M -Z +DF +Y=9 +STDOUT

all: master slave slave1

master: master.c
	$(CC) $(CFLAGS) master.c
	
slave: slave.c
	$(CC) $(CFLAGS) slave.c
	
slave1: slave1.c
	$(CC) $(CFLAGS) slave1.c

clean:
	rm *.cof *.err *.esym *.hex *.lst