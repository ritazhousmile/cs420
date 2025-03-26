/*write a function to take an integer as an input argument and return the total number of leading zeros of the given number
use a while loop without a break statement
*/


int count_leading_zeros_8bit(unsigned char num) {
    int total_bits = 8; // Total bits in an 8-bit number
    int count = 0;
    unsigned char mask = 1U << (total_bits - 1); // Create a mask with leftmost bit set (10000000)
    
    while (mask && !(num & mask)) {
        count++;
        mask = mask >> 1; // Shift mask right by 1 bit
    }
    
    return count;
}