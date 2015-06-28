/*
SENG 440
Cryptography Project

By: Jeremy Kroeker and Daniel Faulkner
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define m 64
#define BYTE_COUNT 8

char* encrypt(char* input, char* pubkey, char* modulus);
char* decrypt(char* input, char* privkey, char* modulus);
char* exponentiate(char* input, char* exponent, char* modulus);
char* montgomerize(char* x, char* y, char* modulus);

char* mulitiply_wc(char* a, char* b);
char* add_wc(char* a, char* b);
char* rightshift_wc(char* a);

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
    char* output = encrypt(teststring, E, M);
    printf("%.*s\n", 8, output);
    
	exit(0);
}

char* encrypt(char* input, char* pubkey, char* modulus) {
    return exponentiate(input, pubkey, modulus);
}

char* decrypt(char* input, char* privkey, char* modulus) {
    return exponentiate(input, privkey, modulus);
}

char* exponentiate(char* input, char* exponent, char* modulus) {
    unsigned char Z[BYTE_COUNT] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01 };
    unsigned char *P_loc = char[BYTE_COUNT];
    unsigned char *P_next = char[BYTE_COUNT];
    unsigned char *E_loc = char[BYTE_COUNT];

    memcpy(P_loc, input, BYTE_COUNT);
    memcpy(E_loc, exponent, BYTE_COUNT);

    int i;
    
    for (i = 0; i < m; i++) {
        memcpy(P_next, montgomerize(P_loc, P_loc, modulus), BYTE_COUNT);
        if (E_loc[7] & 0x01) {
            Z = montgomerize(Z, P_loc, modulus);
        } else {
            // Do nothing!
        }

        memcpy(P_loc, P_next, BYTE_COUNT);
        E_loc = rightshift_wc(E_loc);
    }
        
}

