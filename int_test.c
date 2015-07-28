#include <stdlib.h>
#include <stdio.h>

#define INT_COUNT 2

void print_array(unsigned const int* arr);

void test_rightshift();
void test_add();
void test_subtract();

void rightshift_wc(unsigned int* out);
void opti_rightshift_wc(unsigned int* out);
unsigned int add_wc(unsigned int* out, unsigned const int* a, unsigned const int* b);
unsigned int opti_add_wc(unsigned int* out, unsigned const int* a, unsigned const int* b);
unsigned int subtract_wc(unsigned int* out, unsigned const int* a, unsigned const int* b);

int main() {
    test_rightshift();
    test_add();
    //test_subtract();

    exit(0);
}

void print_array(unsigned const int* arr) {
    int i;

    for (i = 0; i < INT_COUNT; i++) {
        printf("%08x", arr[i]);
    }
    printf("\n");
}

void test_rightshift() {
    unsigned int E[INT_COUNT] = { 0x0101FF01, 0x00030003 };
    unsigned int F[INT_COUNT] = { 0x0101FF01, 0x00030003 };

    printf("Original array:\n\n");
    print_array(E);
    rightshift_wc(E);
    printf("Right shifted array (regular shift):\n");
    print_array(E);

    opti_rightshift_wc(F);
    printf("Right shifted array (speed optimized shift):\n");
    print_array(F);
}

void test_add() {
    unsigned int A[INT_COUNT] = { 0x0101FF01, 0x00030003 };
    unsigned int B[INT_COUNT] = { 0x0EFEBC10, 0xFFFFCCED };

    unsigned int OUT_1[INT_COUNT];
    unsigned int OUT_2[INT_COUNT];

    printf("First summation array:\n");
    print_array(A);
    printf("Second summation array:\n");
    print_array(B);

    add_wc(OUT_1, A, B);
    printf("Summed arrays (regular addition):\n");
    print_array(OUT_1);

    opti_add_wc(OUT_2, A, B);
    printf("Summed arrays (speed optimized addition):\n");
    print_array(OUT_2);
}

void test_subtract() {
    unsigned int A[INT_COUNT] = { 0x0101FF01, 0x00030003 };
    unsigned int B[INT_COUNT] = { 0x0EFEBC10, 0xFFFFCCED };

    printf("First subtraction array:\n");
    print_array(A);
    printf("Second subtraction array:\n");
    print_array(B);
    subtract_wc(A, A, B);
    printf("Subtracted arrays:\n");
    print_array(A);
}

//
// Regular right shift for an integer array representing a long integer with
// INT_COUNT * 32 bits.
//
void rightshift_wc(unsigned int* out) {
    int i;
    unsigned int carry = 0;

    for (i = 0; i < INT_COUNT; i++) {
        unsigned int next_carry = out[i] & 0x00000001;
        out[i] = (out[i] >> 1) | carry << 31;
        carry = next_carry;
    }
}

//
// OPTIMIZATIONS:
//   loop unrolling
//   pipelining
//   temporary variable instead of mem accesses
//
void opti_rightshift_wc(unsigned int* out) {
    register unsigned int temp_a = out[0];
    register unsigned int temp_b = out[1];

    unsigned int carry = temp_a & 0x00000001 << 31;

    temp_b = temp_b >> 1;
    temp_a = temp_a >> 1;
    
    temp_b = temp_b | carry;

    out[0] = temp_a;
    out[1] = temp_b;
}

//
// Regular addition for two integer arrays into an output array; each represents a long
// integer with INT_COUNT * 32 bits.
//
unsigned int add_wc(unsigned int* out, unsigned const int* a, unsigned const int* b) {
    int i;
    unsigned int overflow = 0;

    for (i = INT_COUNT - 1; i >=0; i--) {
        unsigned int msb_a;
        unsigned int msb_b;
        unsigned int msb_c;
        unsigned int msb_d;

        msb_a = a[i] & 0x80000000;
        out[i] = a[i] + overflow;
        msb_b = out[i] & 0x80000000;
        msb_c = b[i] & 0x80000000;
        out[i] += b[i];
        msb_d = out[i] & 0x80000000;

        overflow = ((msb_a & (0x80000000 ^ msb_b)) | (msb_b & msb_c) | ((msb_b | msb_c) & (0x80000000 ^ msb_d))) >> 31;
    }

    return overflow;
}

//
// OPTIMIZATIONS:
//   pipelining
//   temporary variable instead of mem accesses
//
unsigned int opti_add_wc(unsigned int* out, unsigned const int* a, unsigned const int* b) {
    int i;
    unsigned int overflow = 0;

    unsigned int msb_a;
    unsigned int msb_b;
    unsigned int msb_c;
    unsigned int msb_d;

    unsigned int temp_a = a[1];
    unsigned int temp_b = b[1];
    register unsigned int temp_out;
    msb_a = temp_a & 0x80000000;
    
    for (i = 1; i >= 0; i--) {
        temp_out = temp_a + overflow;
        msb_b = temp_out & 0x80000000;
        msb_d = temp_b & 0x80000000;
        msb_a &= (0x80000000 ^ msb_b);
        msb_c = msb_b | msb_d;
        temp_out += temp_b;
        msb_b = msb_b & msb_d;
        msb_d = temp_out & 0x80000000;

        out[i] = temp_out;

        temp_a = a[0];
        temp_b = b[0];
        overflow = (msb_a | msb_b | (msb_c & (0x80000000 ^ msb_d))) >> 31;
    }

    return overflow;
}

unsigned int subtract_wc(unsigned int* out, unsigned const int* a, unsigned const int* b) {
    int i;
    unsigned int borrow = 0;
    unsigned int gt;
    unsigned int msb_a;
    unsigned int msb_b;

    for (i = INT_COUNT - 1; i >= 0; i--) {
        gt = (unsigned int)(b[i] > a[i]);
        out[i] = a[i] - b[i];
        msb_a = out[i] & 0x80000000;
        out[i] -= borrow;
        msb_b = out[i] & 0x80000000;

        borrow = gt | (((0x80000000 ^ msb_a) & msb_b) >> 31);
    }

    return borrow;
}
