#include <stdio.h>
#include <time.h>

int count_bits_1(unsigned int);

int count_bits_2(unsigned int);

int count_bits_3(unsigned long long);

/**
 * test performance
 * @return
 */
int main() {
//    for (int i = 0; i < 100000000; i++) {
//        count_bits_1(i);
////        count_bits_2(i);
//    }
//    printf("%ld", clock());

    return 0;
}

/**
 * use loop to count the lowest bit
 * @param x
 * @return
 */
int count_bits_1(unsigned int x) {
    register unsigned int xx = x;
    int result = 0;
    for (int i = 32; i > 0; i--) {
        result += (xx & 0x00000001);
        xx = (xx >> 1);
    }
    return result;
}

/**
 * another way to count the bits
 *   0   1   0   1   0   1   0   1   0   1   0   1   0   1   0   1   0   1   0   1   0   1   0   1   0   1   0   1   0   1   0   1
 * x01 x02 x03 x04 x05 x06 x07 x08 x09 x10 x11 x12 x13 x14 x15 x16 x17 x18 x19 x20 x21 x22 x23 x24 x25 x26 x27 x28 x29 x30 x31 x32  2m + n
 *
 *   0 x01   0 x03   0 x05   0 x07   0 x09   0 x11   0 x13   0 x15   0 x17   0 x19   0 x21   0 x23   0 x25   0 x27   0 x29   0 x31  ((xx >> 1) & 0x55555555) -> m
 *
 * x01   0 x03   0 x05   0 x07   0 x09   0 x11   0 x13   0 x15   0 x17   0 x19   0 x21   0 x23   0 x25   0 x27   0 x29   0 x31   0  2m
 *
 *   0 x02   0 x04   0 x06   0 x08   0 x10   0 x12   0 x14   0 x16   0 x18   0 x20   0 x22   0 x24   0 x26   0 x28   0 x30   0 x32   n
 *
 * @param x
 * @return
 */
int count_bits_2(unsigned int x) {
    register unsigned int xx = x;
    xx = xx - ((xx >> 1) & 0x55555555);
    xx = (xx & 0x33333333) + ((xx >> 2) & 0x33333333);
    xx = (xx + (xx >> 4)) & 0x0f0f0f0f;
    xx = xx + (xx >> 8);
    return (xx + (xx >> 16)) & 0xff;
}

int count_bits_3(unsigned long long x) {
    register unsigned long long xx = x;
    xx = xx - ((xx >> 1) & 0x5555555555555555);
    xx = (xx & 0x3333333333333333) + ((xx >> 2) & 0x3333333333333333);
    xx = (xx + (xx >> 4)) & 0x0f0f0f0f0f0f0f0f;
    xx = (xx + (xx >> 8)) & 0x00ff00ff00ff00ff;
    xx = (xx + (xx >> 16));
    return (xx + (xx >> 32)) & 0x000000000000ffff;
}
