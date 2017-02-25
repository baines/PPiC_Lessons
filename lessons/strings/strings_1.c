#if 0
	gcc -fsanitize=address -std=c99 -g -D_GNU_SOURCE $0 -o lesson1
	exit
#endif
/* LESSON 1 - Strings */
#include <stdlib.h>

/* XXX: Implement me #1
    Input:
        String -> A null-terminated string.
        Which  -> The character whose position we are looking for.
    Requirement:
        Return the index in String that Which first appears.
        i.e. returning 0 means that Which appears at String[0].
        If it does not appear at all, return -1
*/
int DudeWheresMyChar(const char *String, char Which)
{

}

/* XXX: Implement me #2
    Input:
        StrA     -> A null-terminated string.
        StrB     -> A NON null-terminated string.
        StrBSize -> The length of StrB in characters.
    Requirement:
        Compare StrA and StrB.
        If all characters are equal, return 1
        Otherwise, return 0.
*/
int AreStringsTheSame(const char *StrA, const char *StrB, int StrBSize)
{

}

/* XXX: Implement me #3
    Input:
        Haystack     -> A NON null-terminated string which we are searching.
        HaystackSize -> The number of characters in the Haystack string.
        Needle       -> A null-terminated String which we are searching for
    Requirement:
        If Needle appears as a substring somewhere in Haystack,
        then return the first index within Haystack at which Needle starts.

        If Needle is an empty string, return 0.

        If Needle is not found, return ERROR_JUST_HAY

        If the length of the Needle string is larger than that of Haystack,
        return ERROR_TRYPANOPHOBIA.
    Data:
        Error definitions: */
        #define ERROR_JUST_HAY      -1
        #define ERROR_TRYPANOPHOBIA -2
/**/
int FindSubString(const char *Haystack, int HaystackSize, const char *Needle)
{

}

/* XXX: Implement me #4
    Input:
        StrArray   -> An array of null-terminated strings
        ArrayCount -> The number of strings in StrArray
        Word       -> A null-terminated string to search for
    Requirement:
        For each string in StrArray, check if it contains the substring Word,
        and if it does then replace all characters of Word in this string
        with the character 'X'.

        If any replacement was done, then return 1, otherwise 0
    Example:
        Input:
            StrArray   = { "Hello friend.", "My password is 1234." };
            ArrayCount = 2
            Word       = "1234"
        Output:
            StrArray   = { "Hello friend.", "My password is XXXX." };
            Return     = 1
*/
int MemoryHole(char **StrArray, int ArrayCount, const char *Word)
{

}

/* XXX: Implement me #5
    Input:
        StrArray  -> An array of strings that are NOT null-terminated.
                     The array itself is terminated by a null pointer, however.
        SizeArray -> An array of sizes/lengths for each corresponding string
                     in StrArray
    Requirement:
        Create and return a null-terminated string that is formed by
        concatenating all strings from StrArray in order.

        The string you return should be on the heap, and it should be valid to
        pass it to free().
*/
char *ConcatenateAll(const char **StrArray, int *SizeArray)
{

}

/* do not edit beyond this point */
#include "../../test_harness/1.c"
int main(void){	return test_lesson(); }
