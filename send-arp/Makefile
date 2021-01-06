LDLIBS=-lpcap

all: send-arp

send-arp: send-arp.o
	g++ -o send-arp send-arp.o ethhdr.o mac.o arphdr.o ip.o  -lpcap

send-arp.o: arphdr.o ethhdr.o ip.o mac.o send-arp.cpp
	g++ -c -o send-arp.o send-arp.cpp

ethhdr.o: ethhdr.h ethhdr.cpp
	g++ -c -o ethhdr.o ethhdr.cpp

mac.o: mac.h mac.cpp
	g++ -c -o mac.o mac.cpp

arphdr.o: arphdr.h arphdr.cpp
	g++ -c -o arphdr.o arphdr.cpp

ip.o: ip.h ip.cpp
	g++ -c -o ip.o ip.cpp


clean:
	rm -f send-arp *.o
