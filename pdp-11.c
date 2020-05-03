#include <stdio.h>
#include <assert.h>

typedef unsigned char byte;      // 8 bit
typedef unsigned short int word; // 16 bit
typedef word Adress;             // 16 bit

#define MEMSIZE (64*1024)

byte mem[MEMSIZE];

void b_write(Adress adr, byte b);
byte b_read(Adress adr);
void w_write(Adress adr, word w);
word w_read(Adress adr);

void test_mem() {
	byte b0 = 0x0a;
	// write byte, read byte
	b_write(2, b0);
	byte bres = b_read(2);
	//printf("%02hhx = %02hhx\n", b0, bres);
	assert(b0 == bres);
	
	// write 2 byte, read word
	Adress a = 4;
	byte b1 = 0xcb;
	b0 = 0x0a;
	word w = 0xcb0a;
	b_write(a, b0);
	b_write(a+1, b1);
	word wres = w_read(a);
	//printf("ww/br\t %04hx = %02hhx%02hhx\n", wres, b1, b0);
	assert(w == wres);
	
	// write word, read word
	a = 6;
	w_write(a, w);
	wres = w_read(a);
	printf("ww/wr\t %04hx = %04hx\n", wres, w);
	assert(w == wres);
}
	
int main() {
	test_mem();
	return 0;
}

void w_write(Adress a, word w){
	mem[a] = w & 0xFF;
	//printf("%02x\n", mem[a]);
	mem[a+1] = (w  >> 8) & 0xFF;
	//printf("%02x\n", mem[a+1]);
}

word w_read(Adress a){
	word w = ((word)mem[a+1]) << 8;
	//printf("w1 = %x\n", w);
	w = w | mem[a];
	//printf("w2 = %x\n", w);	
	return w;
}

void b_write(Adress adr, byte b) {
	mem[adr] = b;
}


byte b_read(Adress adr) {
	return mem[adr];
}
