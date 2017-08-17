#include <stdio.h>
#include <stdint.h>
#include <string.h>

/*
33 was chosen because: hello

1) multiplication is easy to compute using shift and add.

2) As you can see from the shift and add implementation, using 33 makes two copies of most of the 
input bits in the hash accumulator, and then spreads those bits relatively far apart. This helps 
produce good avalanching. Using a larger shift would duplicate fewer bits, using a smaller shift 
would keep bit interactions more local and make it take longer for the interactions to spread.

3) The shift of 5 is relatively prime to 32 (the number of bits in the register), which helps with 
avalanching. While there are enough characters left in the string, each bit of an input byte will 
eventually interact with every preceding bit of input.

4) The shift of 5 is a good shift amount when considering ASCII character data. An ASCII character 
can sort of be thought of as a 4-bit character type selector and a 4-bit character-of-type 
selector. E.g. the digits all have 0x3 in the first 4 bits. So an 8-bit shift would cause bits 
with a certain meaning to mostly interact with other bits that have the same meaning. 
A 4-bit or 2-bit shift would similarly produce strong interactions between like-minded bits. 
The 5-bit shift causes many of the four low order bits of a character to strongly interact with 
many of the 4-upper bits in the same character.

As stated elsewhere, the choice of 5381 isn't too important and many other choices 
should work as well here.

This is not a fast hash function since it processes it's input a character at a time and doesn't try
 to use instruction level parallelism. It is, however, easy to write. Quality of the output divided 
by ease of writing the code is likely to hit a sweet spot.

On modern processors, multiplication is much faster than it was when this algorithm was developed 
and other multiplication factors (e.g. 2^13 + 2^5 + 1) may have similar performance, slightly
 better output, and be slightly easier to write.

Contrary to an answer above, a good non-cryptographic hash function doesn't want to produce a random output.
 Instead, given two inputs that are nearly identical, it wants to produce widely different outputs.
 If you're input values are randomly distributed, you don't need a good hash function, you can just use
 an arbitrary set of bits from your input.
 Some of the modern hash functions (Jenkins 3, Murmur, probably CityHash) produce a better distribution 
of outputs than random given inputs that are highly similar.

*/
void dbj_hash(char *main)
{   int i;
    unsigned long hash = 5381;
    size_t m_len = strlen(main);
    uint32_t m_hash = 0;

    printf("\nString is: %s", main);
    for (i=0; i < m_len; i++) {
         m_hash = ((m_hash << 5) + m_hash) + main[i]; //hash = hash * 33 + c
    }
    printf (" \nHash is %u", m_hash);
         
    return;
}
int main (int argc, char **argv)
{
    char *main_text = "Hello Everyone, am with you...";

    dbj_hash(main_text);
    return 69;
}
