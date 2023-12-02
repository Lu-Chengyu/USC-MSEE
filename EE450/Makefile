# Compiler
CC=g++

# Compiler Flags
CFLAGS=-Wall -g

# Executable names
CLIENT=client
SERVERM=serverM
SERVERS=serverS
SERVERL=serverL
SERVERH=serverH

all: $(CLIENT) $(SERVERM) $(SERVERS) $(SERVERL) $(SERVERH)

$(CLIENT):
	$(CC) $(CFLAGS) -o $(CLIENT) client.cpp

$(SERVERM):
	$(CC) $(CFLAGS) -o $(SERVERM) serverM.cpp

$(SERVERS):
	$(CC) $(CFLAGS) -o $(SERVERS) serverS.cpp

$(SERVERL):
	$(CC) $(CFLAGS) -o $(SERVERL) serverL.cpp

$(SERVERH):
	$(CC) $(CFLAGS) -o $(SERVERH) serverH.cpp

clean:
	rm -f $(CLIENT) $(SERVERM) $(SERVERS) $(SERVERL) $(SERVERH)

.PHONY: all clean
