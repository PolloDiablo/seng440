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
#define INT_COUNT 2

void encrypt(unsigned int* out, unsigned const int* input, unsigned const int* pubkey, unsigned const int* modulus);
void decrypt(unsigned int* out, unsigned const int* input, unsigned const int* privkey, unsigned const int* modulus);
void mme(unsigned int* out, unsigned const int* input, unsigned const int* exponent, unsigned const int* modulus);
void mmm(unsigned int* out, unsigned const int* x, unsigned const int* y, unsigned const int* modulus);

inline unsigned int add_wc(unsigned int* out, unsigned const int* a, unsigned const int* b);
inline void rightshift_wc(unsigned int* a);

// TEMP functions --------------------------
void print_array(unsigned const int* arr);
void mont_test();
void full_test();

int DEBUG_LINES = 0;
// -----------------------------------------

unsigned const int P[INT_COUNT] = { 0x00000002, 0xD82FA76D };     // 12216936301
unsigned const int Q[INT_COUNT] = { 0x00000000, 0x14D54E53 };     // 349523539
unsigned const int M[INT_COUNT] = { 0x3B427785, 0x6E277E57 };     // 4270106811663089239
unsigned const int E[INT_COUNT] = { 0x00000000, 0x00000095 };     // 149
unsigned const int D[INT_COUNT] = { 0x12B150A6, 0x96B18D05 };     // 134694643998500549
unsigned const int Nr[INT_COUNT] = { 0x0BC8EC02, 0xEFBA653B };    // 849188027115398459

//
// Runs the full test with a default value and exits.
//
int main() {
    full_test();
    //mont_test();
    exit(0);
}

//
// For testing - prints the octets of an int array. Assumes the array contains
// exactly INT_COUNT octets.
//
void print_array(unsigned const int* arr) {
    int i;

    for (i = 0; i < INT_COUNT; i++) {
        printf("%08x ", arr[i]);
    }
    printf("\n");
}

//
// For testing - runs the mmm funtion using the x, y, and modulus values
// given in the example in the slides. Prints the resulting array.
//
void mont_test() {
    unsigned int output[INT_COUNT];
    unsigned int x[INT_COUNT] = { 0x00000000, 0x00000011 };
    unsigned int y[INT_COUNT] = { 0x00000000, 0x00000016 };
    unsigned int mod[INT_COUNT] = { 0x00000000, 0x00000017 };
    mmm(output, x, y, mod); 
    print_array(output);
}

//
// For testing - encrypts the test input, then decrypts it. Prints both int arrays.
//
void full_test() {
    unsigned int teststring[INT_COUNT] = {0x00000000, 0x00004849 };
    unsigned int output[INT_COUNT];
    unsigned int next_output[INT_COUNT];
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
// All int arrays must be INT_COUNT bytes long.
//
//   out:       The int array the output will be written to.
//   input:     The value to encrypt.
//   pubkey:    The public key to encrypt with.
//   modulus:   The shared modulus to encrypt with.
//
void encrypt(unsigned int* out, unsigned const int* input, unsigned const int* pubkey, unsigned const int* modulus) {
    mme(out, input, pubkey, modulus);
}

//
// Decrypts the input by calling the montgomery modular exponentiation function with the private key.
// All int arrays must be INT_COUNT bytes long.
//
//   out:       The int array the output will be written to.
//   input:     The cypher to decrypt.
//   privkey:   The private key to decrypt with.
//   modulus:   The shared modulus to decrypt with.
//
void decrypt(unsigned int* out, unsigned const int* input, unsigned const int* privkey, unsigned const int* modulus) {
    mme(out, input, privkey, modulus);
}


//
// Runs montgomery modular exponentiation function on the input, using the exponent and modulus provided and writes
// the result to the output int array. All int arrays must be INT_COUNT long.
//
// This function calculates (input ^ exponent) MOD modulus.
//
//   out:       The int array the output will be written to.
//   input:     The base of the mathematical function.
//   exponent:  The exponent of the mathematical function.
//   modulus:   The modulus of the mathematical function.
//
void mme(unsigned int* out, unsigned const int* input, unsigned const int* exponent, unsigned const int* modulus) {
    unsigned int One[INT_COUNT] = { 0x00000000, 0x00000001 };
    unsigned int Z[INT_COUNT];
    unsigned int P_loc[INT_COUNT];
    unsigned int P_next[INT_COUNT];
    unsigned int E_loc[INT_COUNT];
    int i;

    // Pre-scale the initial values.
    mmm(Z, One, Nr, modulus);
    mmm(P_loc, Nr, input, modulus);

    memcpy(E_loc, exponent, INT_COUNT * sizeof(int));
    
    for (i = 0; i < m; i++) {
        mmm(P_next, P_loc, P_loc, modulus);
        if (E_loc[1] & 0x00000001) {
            mmm(Z, Z, P_loc, modulus);
        } else {
            // Zi+1 gets the value of Zi; this is accomplished by leaving Z as it is.
        }

        memcpy(P_loc, P_next, INT_COUNT * sizeof(int));
        rightshift_wc(E_loc);
    }

    // Remove the R ^ -1 factor from the result.
    mmm(out, One, Z, modulus);
}

//
// Runs montgomery modular multiplication function on the input, using the x and y values with the modulus provided.
// Writes the result to the output int array. All int arrays must be INT_COUNT long.
//
// This function calculates (x * y * R ^ -1 MOD modulus), where R ^ -1 is (2 ^ 2m) MOD modulus.
//
//    out:      The int array the output will be written to.
//    x:        One of the two multiplicands of the mathematical function.
//    y:        One of the two multiplicands of the mathematical function.
//    modulus:  The modulus of the mathematical function.
//
void mmm(unsigned int* out, unsigned const int* x, unsigned const int* y, unsigned const int* modulus){
    unsigned int T[INT_COUNT] = {0x00000000, 0x00000000};
    unsigned int x_loc[INT_COUNT];
    
    memcpy(x_loc, x, INT_COUNT * sizeof(int));

    int i;
    unsigned int temp_bit;
    unsigned int x0; // register
    unsigned int overflow;

    for(i = 0 ; i < m ; i++){
        x0 = x_loc[1] & 0x00000001;
        temp_bit = ((T[1] & 0x00000001) + (x0 & y[1])) & 0x00000001;

        // Adds values to the product based on the flags. Records overflow if it occurs.
        if (x0) {
            overflow = add_wc(T, T, y);
        }
        if (temp_bit) {
            overflow += add_wc(T, T, modulus);
        }
        
        rightshift_wc(T);
        T[0] |= (overflow << 31);
        overflow = 0x00000000;
        rightshift_wc(x_loc);
    }

    memcpy(out, T, INT_COUNT * sizeof(int));
}

//
// Adds two words together and writes to the output int array. All int arrays must be INT_COUNT long.
//
//    out:      The int array that the output will be written to.
//    a:        One of the two summands.
//    b:        One of the two summands.
//
//    returns:  1 if there was overflow; 0 otherwise.
//
inline unsigned int add_wc(unsigned int* out, unsigned const int* a, unsigned const int* b){
    int i;
    unsigned int overflow = 0;
    unsigned int msb_a;
    unsigned int msb_b;
    unsigned int msb_c;
    unsigned int msb_d;
	
    register unsigned int temp_a;
    register unsigned int temp_b;
    register unsigned int temp_out;

    for (i = INT_COUNT - 1; i >= 0; i--) {
        temp_a = a[i];
        temp_b = b[i];

        msb_a = temp_a & 0x80000000;
        temp_out = temp_a + overflow;
        msb_b = temp_out & 0x80000000;
        msb_c = temp_b & 0x80000000;
        temp_out += temp_b;
        msb_d = temp_out & 0x80000000;

        out[i] = temp_out;
        
        overflow = ((msb_a & (0x80000000 ^ msb_b)) | (msb_b & msb_c) | ((msb_b | msb_c) & (0x80000000 ^ msb_d))) >> 31;
    }

    return overflow;
}

//
// Shifts the given word right by one. Performed in place. The int array must be INT_COUNT long.
//
//   a:     The int array bit shifted in place one to the right.
//
inline void rightshift_wc(unsigned int* a){
    register unsigned int temp_a;
    register unsigned int temp_b;
    register unsigned int carry_a;
    
    temp_a = a[0];
    carry_a = (temp_a & 0x00000001) << 31;
    temp_a = temp_a >> 1;

    temp_b = a[1];
    temp_b = (temp_b >> 1) | carry_a;

    a[0] = temp_a;
    a[1] = temp_b;
}
