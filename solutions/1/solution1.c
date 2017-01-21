#if 0
	gcc -fsanitize=address -std=c99 -g -D_GNU_SOURCE $0 -o solution1
	exit
#endif
/* LESSON 1 - Strings */
#include <stdlib.h>

/* XXX: Implement me #1
    Input:
        String -> A null terminated string.
        Which  -> The character whose position we are looking for.
    Requirement:
        Return the index in String that Which first appears.
        i.e. returning 0 means that Which appears at String[0].
        If it does not appear at all, return -1
*/
int DudeWheresMyChar(const char *String, char Which)
{
    for(const char *c = String; *c; ++c){
        if(*c == Which) return c - String;
    }
    return -1;
}

/* XXX: Implement me #2
    Input:
        StrA     -> A null terminated string.
        StrB     -> A NON-null terminated string.
        StrBSize -> The length of StrB in characters.
    Requirement:
        Compare StrA and StrB.
        If all characters are equal, return 1
        Otherwise return 0.
*/
int AreStringsTheSame(const char *StrA, const char *StrB, int StrBSize)
{
    for(int i = 0; i < StrBSize; ++i){
        if(!StrA[i] || StrA[i] != StrB[i]) return 0;
    }
    return !StrA[StrBSize];
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
    int NeedleSize = 0;
    for(const char *c = Needle; *c; ++c){
        ++NeedleSize;
    }

    if(NeedleSize > HaystackSize){
        return ERROR_TRYPANOPHOBIA;
    }

    for(int i = 0; i < HaystackSize; ++i){
        int j = i;
        for(const char *c = Needle; *c; ++c){
            if(Haystack[j] == *c){
                ++j;
            } else {
                break;
            }
        }
        if((j - i) == NeedleSize){
            return i;
        }
    }

    return ERROR_JUST_HAY;
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
    int WordLen = 0;
    int Found = 0;

    for(const char* c = Word; *c; ++c) ++WordLen;

    for(int i = 0; i < ArrayCount; ++i){
        char *p = StrArray[i];
        char *end = p;
        while(*end) ++end;

        int pos;
        while((pos = FindSubString(p, end - p, Word)), pos >= 0){
            Found = 1;
            p += pos;
            for(int j = 0; j < WordLen; ++j){
                *p++ = 'X';
            }
        }
    }

    return Found;
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
    int ArraySize = 0;
    for(const char** c = StrArray; *c; ++c) ++ArraySize;

    int Total = 0;
    for(int i = 0; i < ArraySize; ++i){
        Total += SizeArray[i];
    }

    char *NewStr = malloc(Total + 1);
    char *p = NewStr;

    for(int i = 0; i < ArraySize; ++i){
        for(int j = 0; j < SizeArray[i]; ++j){
            *p++ = StrArray[i][j];
        }
    }
    *p++ = 0;

    return NewStr;
}

/* do not edit beyond this point */
#include "../../test_harness/1.c"
int main(void){	return test_lesson(); }
