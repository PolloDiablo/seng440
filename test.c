#include <stdlib.h>
#include <stdio.h>

#define BYTE_COUNT 8

void print_array(unsigned const char* arr);

void test_rightshift();
void test_add();
void test_subtract();

void rightshift_wc(unsigned char* out);
char add_wc(unsigned char* out, unsigned const char* a, unsigned const char* b);
unsigned char subtract_wc(unsigned char* out, unsigned const char* a, unsigned const char* b);

int main() {
    test_rightshift();
    test_add();
    test_subtract();

    exit(0);
}

void print_array(unsigned const char* arr) {
    int i;

    for (i = 0; i < BYTE_COUNT; i++) {
        printf("%02x", arr[i]);
    }
    printf("\n");
}

void test_rightshift() {
    unsigned char E[BYTE_COUNT] = { 0x01, 0x01, 0xFF, 0x01, 0x00, 0x03, 0x00, 0x03 };

    printf("Original array:\n");
    print_array(E);
    rightshift_wc(E);
    printf("Right shifted array:\n");
    print_array(E);
}

void test_add() {
    unsigned char A[BYTE_COUNT] = { 0x01, 0x01, 0xFF, 0x01, 0x00, 0x03, 0x00, 0x03 };
    unsigned char B[BYTE_COUNT] = { 0x0E, 0xFE, 0xBC, 0x10, 0xFF, 0xFF, 0xCC, 0xED };

    printf("First summation array:\n");
    print_array(A);
    printf("Second summation array:\n");
    print_array(B);
    add_wc(A, A, B);
    printf("Summed arrays:\n");
    print_array(A);
}

void test_subtract() {
    unsigned char A[BYTE_COUNT] = { 0x01, 0x01, 0xFF, 0x01, 0x00, 0x03, 0x00, 0x03 };
    unsigned char B[BYTE_COUNT] = { 0x0E, 0xFE, 0xBC, 0x10, 0xFF, 0xFF, 0xCC, 0xED };

    printf("First subtraction array:\n");
    print_array(A);
    printf("Second subtraction array:\n");
    print_array(B);
    subtract_wc(A, A, B);
    printf("Subtracted arrays:\n");
    print_array(A);
}

void rightshift_wc(unsigned char* out) {
    int i;
    unsigned char carry = 0;

    for (i = 0; i < BYTE_COUNT; i++) {
        unsigned char next_carry = out[i] & 0x01;
        out[i] = (out[i] >> 1) | carry << 7;
        carry = next_carry;
    }
}

char add_wc(unsigned char* out, unsigned const char* a, unsigned const char* b) {
    int i;
    unsigned char overflow = 0;

    for (i = BYTE_COUNT - 1; i >=0; i--) {
        unsigned char msb_a;
        unsigned char msb_b;
        unsigned char msb_c;
        unsigned char msb_d;

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

unsigned char subtract_wc(unsigned char* out, unsigned const char* a, unsigned const char* b) {
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
