#Makefile
all: pcap-test

pcap-test: pcap-test.o
	gcc -o pcap-test pcap-test.o -lpcap

pcap-test.o: ethernet.h ip.h tcp.h pcap-test.c
	gcc -g -c -o pcap-test.o pcap-test.c

clean:
	rm -f pcap-test *.o
