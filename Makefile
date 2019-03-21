CFLAGS=-c -Wall

output: Cmain.o Client.o
	gcc Cmain.o Client.o -o Client

client.o: Client.c Client.h
	gcc $(CFLAGS) Client.c Client.h

clean:
	rm *.o Client