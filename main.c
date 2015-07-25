/* ----------------------------------------------
SENG 440
RSA Cryptography Project

By: Jeremy Kroeker and Daniel Faulkner
---------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define m 64
#define BYTE_COUNT 8

typedef unsigned char BYTE;

void encrypt(unsigned char* out, const char* input, unsigned const char* pubkey, unsigned const char* modulus);
void decrypt(unsigned char* out, const char* input, unsigned const char* privkey, unsigned const char* modulus);
void exponentiate(unsigned char* out, const char* input, unsigned const char* exponent, unsigned const char* modulus);
void montgomerize(unsigned char* out, unsigned const char* x, unsigned const char* y, unsigned const char* modulus);

void multiply_wc(unsigned const char* a, unsigned const char* b);
void add_wc(unsigned const char* a, unsigned const char* b);
void subtract_wc(unsigned const char* a, unsigned const char* b);
void rightshift_wc(unsigned const char* a);
int gte(unsigned const char* a, unsigned const char* b);


unsigned const char P[BYTE_COUNT] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0xF3, 0xBD };
unsigned const char Q[BYTE_COUNT] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x0E, 0xCD };
unsigned const char M[BYTE_COUNT] = { 0x00, 0x00, 0x00, 0x53, 0xAC, 0x6E, 0x84, 0x59 };
unsigned const char E[BYTE_COUNT] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x21 };
unsigned const char D[BYTE_COUNT] = { 0x00, 0x00, 0x00, 0x05, 0x12, 0x35, 0x3E, 0x53 };

int main(int argc, char **argv) {
	printf("Hello World\n");
	printf("Hello World?\n");
	printf("Hello World!\n");
	
    char* teststring = "hi world";
    unsigned char output[BYTE_COUNT];
    encrypt(output, teststring, E, M);
    printf("%.*s\n", 8, output);
    
	exit(0);
}

void encrypt(unsigned char* out, const char* input, unsigned const char* pubkey, unsigned const char* modulus) {
    exponentiate(out, input, pubkey, modulus);
}

void decrypt(unsigned char* out, const char* input, unsigned const char* privkey, unsigned const char* modulus) {
    exponentiate(out, input, privkey, modulus);
}

void exponentiate(unsigned char* out, const char* input, unsigned const char* exponent, unsigned const char* modulus) {
    unsigned char Z[BYTE_COUNT] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01 };
    unsigned char P_loc[BYTE_COUNT];
    unsigned char P_next[BYTE_COUNT];
    unsigned char E_loc[BYTE_COUNT];

    memcpy(P_loc, input, BYTE_COUNT);
    memcpy(E_loc, exponent, BYTE_COUNT);

    int i;
    
    for (i = 0; i < m; i++) {
        montgomerize(P_next, P_loc, P_loc, modulus);
        if (E_loc[7] & 0x01) {
            montgomerize(Z, Z, P_loc, modulus);
        } else {
            // Do nothing!
        }

        memcpy(P_loc, P_next, BYTE_COUNT);
        rightshift_wc(E_loc);
    }
    memcpy(out, Z, BYTE_COUNT);    
}

void montgomerize(unsigned char* out, unsigned const char* x, unsigned const char* y, unsigned const char* modulus){
    unsigned char T[BYTE_COUNT] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    unsigned char x_loc[BYTE_COUNT];
    
    memcpy(x_loc, x, BYTE_COUNT);
    
    int i;
    char temp_bit;
    char x0; // register

    for(i = 0 ; i < m ; i++){
        x0 = x_loc[7] & 0x01;
        temp_bit = (T[7] & 0x01) + x0 & y[7];
        if(x0){
            add_wc(T, y);
        }
        if(temp_bit){
            add_wc(T, modulus);
        }
        rightshift_wc(T);
    }

    if(gte(T,M)){
        subtract_wc(T, M);
    }
    memcpy(out, T, BYTE_COUNT);
}

void multiply_wc(unsigned const char* a, unsigned const char* b){
    //TODO
}

void add_wc(unsigned const char* a, unsigned const char* b){
    //TODO
}

void subtract_wc(unsigned const char* a, unsigned const char* b){
    //TODO
}

void rightshift_wc(unsigned const char* a){
    
}

int gte(unsigned const char* a, unsigned const char* b){
    //TODO
    return 1;
}
