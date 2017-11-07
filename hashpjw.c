/*****************************************************************
 *
 * hashpjw.c
 *
 * Source: "Mastering Algorithms with C" (1999, p. 146) by Kyle Loudon,
 *         published by O'Reilly & Associates.
 * Note: The function was adapted from Compilers: Principles, Techniques, and
 *       Tools (Reading, MA: Addison-Wesley, 1986), by Alfred V. Aho, Ravi
 *       Sethi, and Jeffrey D. Ullman, who attributed it to P. J. Weinberger
 *       as a hash function that performed well in hashing strings for his
 *       compiler.
 *
 * This source can be freely used, adapted, and redistributed in source or
 * binary form, so long as an acknowledgment appears in derived source files.
 * The citation should list that the code comes from the  book  "Mastering
 * Algorithms with C"  by Kyle Loudon,  published by O'Reilly & Associates.
 * This code is under copyright and cannot be included in any other book,
 * publication, or  educational product  without  permission  from  O'Reilly
 * & Associates.  No warranty is attached; we cannot take responsibility for
 * errors or  fitness for use.
 *
 *****************************************************************/


#include "hashpjw.h"


/*************************************************************//**
 * hashpjw: hash a key
 *
 * \param param_name parameter description.
 *
 * \return hash value
 ****************************************************************/
unsigned int hashpjw(const void *key, int buckets)
{
    const char *ptr;
    unsigned int val;

    /*****************************************************************
     * Hash the key by performing a number of bit operations on it.
     ****************************************************************/
    val = 0;
    ptr = key;
    while (*ptr != '\0')
    {
        unsigned int tmp;
        val = (val << 4) + (*ptr);
        if ((tmp = (val & 0xf0000000)))
        {
            val = val ^ (tmp >> 24);
            val = val ^ tmp;
        }
        ptr++;
    }
    /*****************************************************************
     * the actual table size.
     ****************************************************************/

    return val % buckets;
}
