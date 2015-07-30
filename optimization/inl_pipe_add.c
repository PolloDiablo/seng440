/* ----------------------------------------------
 * SENG 440
 * RSA Cryptography Project
 * 
 * By: Jeremy Kroeker and Daniel Faulkner
 * ------------------------------------------- */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define m 64
#define BYTE_COUNT 8

void encrypt(unsigned char* out, unsigned const char* input, unsigned const char* pubkey, unsigned const char* modulus);
void decrypt(unsigned char* out, unsigned const char* input, unsigned const char* privkey, unsigned const char* modulus);
void mme(unsigned char* out, unsigned const char* input, unsigned const char* exponent, unsigned const char* modulus);
void mmm(unsigned char* out, unsigned const char* x, unsigned const char* y, unsigned const char* modulus);

inline unsigned char add_wc(unsigned char* out, unsigned const char* a, unsigned const char* b);
inline void rightshift_wc(unsigned char* a);

// TEMP functions --------------------------
void print_array(unsigned const char* arr);
void mont_test();
void full_test();

int DEBUG_LINES = 0;
// -----------------------------------------

unsigned const char P[BYTE_COUNT] = { 0x00, 0x00, 0x00, 0x02, 0xD8, 0x2F, 0xA7, 0x6D };     // 12216936301
unsigned const char Q[BYTE_COUNT] = { 0x00, 0x00, 0x00, 0x00, 0x14, 0xD5, 0x4E, 0x53 };     // 349523539
unsigned const char M[BYTE_COUNT] = { 0x3B, 0x42, 0x77, 0x85, 0x6E, 0x27, 0x7E, 0x57 };     // 4270106811663089239
unsigned const char E[BYTE_COUNT] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x95 };     // 149
unsigned const char D[BYTE_COUNT] = { 0x12, 0xB1, 0x50, 0xA6, 0x96, 0xB1, 0x8D, 0x05 };     // 134694643998500549
unsigned const char Nr[BYTE_COUNT] = { 0x0B, 0xC8, 0xEC, 0x02, 0xEF, 0xBA, 0x65, 0x3B };    // 849188027115398459

//
// Runs the full test with a default value and exits.
//
int main() {
    full_test();
    //mont_test();
    exit(0);
}

//
// For testing - prints the octets of a char array. Assumes the array contains
// exactly BYTE_COUNT octets.
//
void print_array(unsigned const char* arr) {
    int i;

    for (i = 0; i < BYTE_COUNT; i++) {
        printf("%02x ", arr[i]);
    }
    printf("\n");
}

//
// For testing - runs the mmm funtion using the x, y, and modulus values
// given in the example in the slides. Prints the resulting array.
//
void mont_test() {
    unsigned char output[BYTE_COUNT];
    unsigned char x[BYTE_COUNT] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11 };
    unsigned char y[BYTE_COUNT] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16 };
    unsigned char mod[BYTE_COUNT] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x17 };
    mmm(output, x, y, mod); 
    print_array(output);
}

//
// For testing - encrypts the test input, then decrypts it. Prints both char arrays.
//
void full_test() {
    unsigned char teststring[BYTE_COUNT] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x48, 0x49 };
    unsigned char output[BYTE_COUNT];
    unsigned char next_output[BYTE_COUNT];
    int i;
    for (i = 0; i < 1000; i++) {
        encrypt(output, teststring, E, M);
        decrypt(next_output, output, D, M);
    }
    print_array(output);
    print_array(next_output);
}

//
// Encrypts the input by calling the montgomery modular exponentiation function with the public key.
// All char arrays must be BYTE_COUNT bytes long.
//
//   out:       The char array the output will be written to.
//   input:     The value to encrypt.
//   pubkey:    The public key to encrypt with.
//   modulus:   The shared modulus to encrypt with.
//
void encrypt(unsigned char* out, unsigned const char* input, unsigned const char* pubkey, unsigned const char* modulus) {
    mme(out, input, pubkey, modulus);
}

//
// Decrypts the input by calling the montgomery modular exponentiation function with the private key.
// All char arrays must be BYTE_COUNT bytes long.
//
//   out:       The char array the output will be written to.
//   input:     The cypher to decrypt.
//   privkey:   The private key to decrypt with.
//   modulus:   The shared modulus to decrypt with.
//
void decrypt(unsigned char* out, unsigned const char* input, unsigned const char* privkey, unsigned const char* modulus) {
    mme(out, input, privkey, modulus);
}

//
// Runs montgomery modular exponentiation function on the input, using the exponent and modulus provided and writes
// the result to the output char array. All char arrays must be BYTE_COUNT long.
//
// This function calculates (input ^ exponent) MOD modulus.
//
//   out:       The char array the output will be written to.
//   input:     The base of the mathematical function.
//   exponent:  The exponent of the mathematical function.
//   modulus:   The modulus of the mathematical function.
//
void mme(unsigned char* out, unsigned const char* input, unsigned const char* exponent, unsigned const char* modulus) {
    unsigned char One[BYTE_COUNT] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01 };
    unsigned char Z[BYTE_COUNT];
    unsigned char P_loc[BYTE_COUNT];
    unsigned char P_next[BYTE_COUNT];
    unsigned char E_loc[BYTE_COUNT];
    int i;

    // Pre-scale the initial values.
    mmm(Z, One, Nr, modulus);
    mmm(P_loc, Nr, input, modulus);

    memcpy(E_loc, exponent, BYTE_COUNT);
    
    for (i = 0; i < m; i++) {
        mmm(P_next, P_loc, P_loc, modulus);
        if (E_loc[7] & 0x01) {
            mmm(Z, Z, P_loc, modulus);
        } else {
            // Zi+1 gets the value of Zi; this is accomplished by leaving Z as it is.
        }

        memcpy(P_loc, P_next, BYTE_COUNT);
        rightshift_wc(E_loc);
    }

    // Remove the R ^ -1 factor from the result.
    mmm(out, One, Z, modulus);
}

//
// Runs montgomery modular multiplication function on the input, using the x and y values with the modulus provided.
// Writes the result to the output char array. All char arrays must be BYTE_COUNT long.
//
// This function calculates (x * y * R ^ -1 MOD modulus), where R ^ -1 is (2 ^ 2m) MOD modulus.
//
//    out:      The char array the output will be written to.
//    x:        One of the two multiplicands of the mathematical function.
//    y:        One of the two multiplicands of the mathematical function.
//    modulus:  The modulus of the mathematical function.
//
void mmm(unsigned char* out, unsigned const char* x, unsigned const char* y, unsigned const char* modulus){
    unsigned char T[BYTE_COUNT] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    unsigned char x_loc[BYTE_COUNT];
    
    memcpy(x_loc, x, BYTE_COUNT);

    int i;
    char temp_bit;
    char x0; // register
    unsigned char overflow;

    for(i = 0 ; i < m ; i++){
        x0 = x_loc[7] & 0x01;
        temp_bit = ((T[7] & 0x01) + (x0 & y[7])) & 0x01;

        // Adds values to the product based on the flags. Records overflow if it occurs.
        if (x0) {
            overflow = add_wc(T, T, y);
        }
        if (temp_bit) {
            overflow += add_wc(T, T, modulus);
        }
        
        rightshift_wc(T);
        T[0] |= (overflow << 7);
        overflow = 0x00;
        rightshift_wc(x_loc);
    }

    memcpy(out, T, BYTE_COUNT);
}

//
// Adds two words together and writes to the output char array. All char arrays must be BYTE_COUNT long.
//
//    out:      The char array that the output will be written to.
//    a:        One of the two summands.
//    b:        One of the two summands.
//
//    returns:  1 if there was overflow; 0 otherwise.
//
inline unsigned char add_wc(unsigned char* out, unsigned const char* a, unsigned const char* b) {
    int i;
    unsigned char overflow = 0;
    unsigned char msb_a;
    unsigned char msb_b;
    unsigned char msb_c;
    unsigned char msb_d;

    register unsigned char temp_a;
    register unsigned char temp_b;
    register unsigned char temp_out;

    for (i = BYTE_COUNT - 1; i >= 0; i--) {
        temp_a = a[i];
        temp_b = b[i];

        msb_a = temp_a & 0x80;
        temp_out = temp_a + overflow;
        msb_b = temp_out & 0x80;
        msb_c = temp_b & 0x80;
        temp_out += temp_b;
        msb_d = temp_out & 0x80;

        out[i] = temp_out;
        
        overflow = ((msb_a & (0x80 ^ msb_b)) | (msb_b & msb_c) | ((msb_b | msb_c) & (0x80 ^ msb_d))) >> 7;
    }

    return overflow;
}

//
// Shifts the given word right by one. Performed in place. The char array must be BYTE_COUNT long.
//
//   a:     The char array bit shifted in place one to the right.
//
inline void rightshift_wc(unsigned char* a){
    register unsigned char temp_a;
    register unsigned char temp_b;
    register unsigned char carry_a;
    register unsigned char carry_b;
    
    temp_a = a[0];
    carry_a = (temp_a & 0x01) << 7;
    temp_a = temp_a >> 1;

    temp_b = a[1];
    carry_b = (temp_b & 0x01) << 7;
    temp_b = (temp_b >> 1) | carry_a;

    a[0] = temp_a;
    a[1] = temp_b;

    temp_a = a[2];
    carry_a = (temp_a & 0x01) << 7;
    temp_a = (temp_a >> 1) | carry_b;

    temp_b = a[3];
    carry_b = (temp_b & 0x01) << 7;
    temp_b = (temp_b >> 1) | carry_a;

    a[2] = temp_a;
    a[3] = temp_b;

    temp_a = a[4];
    carry_a = (temp_a & 0x01) << 7;
    temp_a = (temp_a >> 1) | carry_b;

    temp_b = a[5];
    carry_b = (temp_b & 0x01) << 7;
    temp_b = (temp_b >> 1) | carry_a;

    a[4] = temp_a;
    a[5] = temp_b;

    temp_a = a[6];
    carry_a = (temp_a & 0x01) << 7;
    temp_a = (temp_a >> 1) | carry_b;

    temp_b = a[7];
    temp_b = (temp_b >> 1) | carry_a;
    
    a[6] = temp_a;
    a[7] = temp_b;
}

