all: a b c d

a: parta.c
	gcc -pthread -g parta.c -o parta

b: partb.c
	gcc -pthread -g partb.c -o partb

c: partc.c
	gcc -pthread -g partc.c -o partc

d: partd.c
	gcc -pthread -g partd.c -o partd

clean:
	rm -f parta
	rm -f partb
	rm -f partc
	rm -f partd
