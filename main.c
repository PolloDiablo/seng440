/* ----------------------------------------------
 * SENG 440
 * RSA Cryptography Project
 * 
 * By: Jeremy Kroeker and Daniel Faulkner
 * ------------------------------------------- */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define n 64
#define m 64
//39
#define BYTE_COUNT 8

typedef unsigned char BYTE;

void encrypt(unsigned char* out, unsigned const char* input, unsigned const char* pubkey, unsigned const char* modulus);
void decrypt(unsigned char* out, unsigned const char* input, unsigned const char* privkey, unsigned const char* modulus);
void exponentiate(unsigned char* out, unsigned const char* input, unsigned const char* exponent, unsigned const char* modulus);
void montgomerize(unsigned char* out, unsigned const char* x, unsigned const char* y, unsigned const char* modulus);

void multiply_wc(unsigned char* out, unsigned const char* a, unsigned const char* b);
unsigned char add_wc(unsigned char* out, unsigned const char* a, unsigned const char* b);
unsigned char subtract_wc(unsigned char* out, unsigned const char* a, unsigned const char* b);
void rightshift_wc(unsigned char* a);
int gte(unsigned const char* a, unsigned const char* b);

// TEMP functions
void print_array(unsigned const char* arr);
void mont_test();
void full_test();
//

unsigned const char P[BYTE_COUNT] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0xF3, 0xBD };
unsigned const char Q[BYTE_COUNT] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x0E, 0xCD };
unsigned const char M[BYTE_COUNT] = { 0x00, 0x00, 0x00, 0x53, 0xAC, 0x6E, 0x84, 0x59 };
unsigned const char E[BYTE_COUNT] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x21 };
//unsigned const char D[BYTE_COUNT] = { 0x00, 0x00, 0x00, 0x05, 0x12, 0x35, 0x3E, 0x53 };
unsigned const char D[BYTE_COUNT] = { 0x00, 0x00, 0x00, 0x51, 0x23, 0x40, 0x7D, 0xE1 };
unsigned const char Nr[BYTE_COUNT] = { 0x00, 0x00, 0x00, 0x2F, 0x13, 0x4F, 0xEB, 0xAE };

int main(int argc, char **argv) {
    //mont_test();
    full_test();
    exit(0);
}

void print_array(unsigned const char* arr) {
    int i;

    for (i = 0; i < BYTE_COUNT; i++) {
        printf("%02x ", arr[i]);
    }
    printf("\n");
}

void mont_test() {
    unsigned char output[BYTE_COUNT];
    unsigned char x[BYTE_COUNT] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11 };
    unsigned char y[BYTE_COUNT] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16 };
    unsigned char mod[BYTE_COUNT] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x17 };
    montgomerize(output, x, y, mod); 
    print_array(output);
}

void full_test() {
    //char* teststring = "hi world";
    unsigned char teststring[BYTE_COUNT] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x48, 0x49 };
    unsigned char output[BYTE_COUNT];
    unsigned char next_output[BYTE_COUNT];
    encrypt(output, teststring, E, M);
    decrypt(next_output, output, D, M);
    print_array(output);
    print_array(next_output);
    //printf("%.*s\n", BYTE_COUNT, next_output);
}

void encrypt(unsigned char* out, unsigned const char* input, unsigned const char* pubkey, unsigned const char* modulus) {
    exponentiate(out, input, pubkey, modulus);
}

void decrypt(unsigned char* out, unsigned const char* input, unsigned const char* privkey, unsigned const char* modulus) {
    exponentiate(out, input, privkey, modulus);
}

void exponentiate(unsigned char* out, unsigned const char* input, unsigned const char* exponent, unsigned const char* modulus) {
    unsigned char One[BYTE_COUNT] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01 };
    unsigned char Z[BYTE_COUNT];
    unsigned char P_loc[BYTE_COUNT];
    unsigned char P_next[BYTE_COUNT];
    unsigned char E_loc[BYTE_COUNT];

    montgomerize(Z, One, Nr, modulus);
    montgomerize(P_loc, input, Nr, modulus);

    //memcpy(P_loc, input, BYTE_COUNT);
    memcpy(E_loc, exponent, BYTE_COUNT);

    int i;
    
    for (i = 0; i < n; i++) {
        montgomerize(P_next, P_loc, P_loc, modulus);
        if (E_loc[7] & 0x01) {
            montgomerize(Z, Z, P_loc, modulus);
        } else {
            // Do nothing!
        }

        memcpy(P_loc, P_next, BYTE_COUNT);
        rightshift_wc(E_loc);
    }
    montgomerize(Z, One, Z, modulus);
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
        printf("MMM loop iteration number %i:\n", i);
        x0 = x_loc[7] & 0x01;
        temp_bit = (T[7] & 0x01) + (x0 & y[7]);
        printf("T0: %02x | X(i): %02x | Y(0): %02x | result: %02x", T[7] & 0x01, x0, y[7], temp_bit);
        if(x0){
            add_wc(T, T, y);
        }
        if(temp_bit){
            add_wc(T, T, modulus);
        }
        rightshift_wc(T);
        rightshift_wc(x_loc);
        print_array(T);
    }

    if(gte(T,M)){
        subtract_wc(T, T, M);
    }
    memcpy(out, T, BYTE_COUNT);
}

void multiply_wc(unsigned char* out, unsigned const char* a, unsigned const char* b){
    //TODO
}

unsigned char add_wc(unsigned char* out, unsigned const char* a, unsigned const char* b){
    int i;
    unsigned char overflow = 0;
    unsigned char msb_a;
    unsigned char msb_b;
    unsigned char msb_c;
    unsigned char msb_d;

    for (i = BYTE_COUNT - 1; i >= 0; i--) {
        msb_a = a[i] & 0x80;
        out[i] = a[i] + overflow;
        msb_b = out[i] & 0x80;
        msb_c = b[i] & 0x80;
        out[i] += b[i];
        msb_d = out[i] & 0x80;

        overflow = ((msb_a & (0x80 ^ msb_b)) | (msb_b & msb_c) | ((msb_b | msb_c) & (0x80 ^ msb_d))) >> 7;
    }

    return overflow;
}

unsigned char subtract_wc(unsigned char* out, unsigned const char* a, unsigned const char* b){
    int i;
    unsigned char borrow = 0;
    unsigned char gt;
    unsigned char msb_a;
    unsigned char msb_b;

    for (i = BYTE_COUNT - 1; i >= 0; i--) {
        gt = (unsigned char)(b[i] > a[i]);
        out[i] = a[i] - b[i];
        msb_a = out[i] & 0x80;
        out[i] -= borrow;
        msb_b = out[i] & 0x80;

        borrow = gt | (((0x80 ^ msb_a) & msb_b) >> 7);
    }

    return borrow;
}

void rightshift_wc(unsigned char* a){
    int i;
    char carry = 0x00;

    for (i = 0; i < BYTE_COUNT; i++) {
        char next_carry = a[i] & 0x01;
        a[i] = (a[i] >> 1) | carry << 7;
        carry = next_carry;
    }
}

//
// Checks if char array a is greater than or equal to char array b.
// 
// Return: 1 if a >= b; 0 otherwise
//
int gte(unsigned const char* a, unsigned const char* b){
    int is_gte = 1;
    int i = 0;

    while (i < BYTE_COUNT) {
        if ((a[i] & b[i]) != a[i]) {
            is_gte = a[i] > b[i];
            break;
        }

        i++;
    }

    return is_gte;
}
