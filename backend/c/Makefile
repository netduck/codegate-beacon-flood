all: fake_ap

fake_ap: fake_ap.c
		gcc -o fake_ap fake_ap.c utils/beacon.c -lpcap

clean:
		rm -f fake_ap *.o
