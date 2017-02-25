#if 0
	cc -fsanitize=address -std=c99 -g -D_GNU_SOURCE $0 -o solution-structs
	exit
;
#endif
#include <stddef.h> // for NULL

/* Exercise #1 - Accessing struct fields
 * 
 * BACKGROUND
 * 
 * A struct in C is a collection of variables bundled together,
 * where each item has its own name. Each of these items is
 * sometimes called a field, or member of the struct.
 * 
 * When you have a plain struct, you access fields using the dot '.'
 * operator. e.g. struct A Mystruct; MyStruct.Field = 1;
 * 
 * When you have a pointer to a struct, you access fields using the arrow '->'
 * operator. e.g. struct A *Mystruct = ...; MyStruct->Field = 1;
 * 
 * EXERCISE
 * 
 * In the UpdateKarma function below, you are passed instances of two structs:
 * struct user, and struct karma_change.
 * 
 * You must update the given User's karma according to the Type and Value fields
 * given in the KarmaChange variable. the Type field will either be KARMA_INCREASE
 * or KARMA_DECREASE, which indicate you should add to or subtract from the User's
 * TotalKarma respectively.
 * 
 * ADDITIONAL INFO
 * 
 * As with any other type, when a struct is passed by value to a function, changes
 * made to this variable will be local to the function and not reflected back to
 * the call site of the function. Passing a pointer to the address of the variable
 * is a way to overcome this.
 * 
 * DATA TYPES */

struct user {
    int ID;
    int TotalKarma;
};

enum { KARMA_DECREASE, KARMA_INCREASE };

struct karma_change {
    int Type;
    int Value;
};

/* FUNCTION TO IMPLEMENT */

void UpdateKarma(struct user *User, struct karma_change KarmaChange)
{
    static const int Mult[] = { -1, 1 };
    User->TotalKarma += KarmaChange.Value * Mult[KarmaChange.Type];
}

/* Exercise #2 - Linked Lists
 * 
 * BACKGROUND
 * 
 * A Linked List in C allows multiple instances of a struct to be connected with pointers
 * so that a list of entries is formed, and can be iterated through.
 *
 * Linked lists support the addition and removal of individual entries at runtime.
 * Unlike a standard C array, they have no fixed maximum entry count. However, looking up
 * an entry requires a linear-time scan through the list as opposed to a constant-time array
 * index.
 * 
 * They are implemented by having a struct store a 'next' pointer to another struct of the same type,
 * see the user_ll struct below for an example.
 * 
 * EXERCISE
 * 
 * In the FindAndUpdateKarma function below, you are passed the 'head' of Linked List of type user_ll,
 * 'head' refers to the first element of the list. Each successive entry of the list can be accessed
 * via the Next field of this struct, and the Next field of that struct, and so on.
 * 
 * The final entry of the list will have a null pointer as its Next field to signify the end of the list.
 * 
 * You are additionally passed an ID which will correspond to the ID of at most one entry of the list.
 * Iterate through the linked list and find this entry if it exists. If it was found, then, as with the
 * previous exercise, update the TotalKarma based on the fields of the KarmaChange struct.
 * 
 * ADDITIONAL INFO
 * 
 * Both structs used in this exercise make use of a typedef. This allows the omission of the 'struct' keyword
 * when defining the structs. [in C++, the struct keyword can always be omitted.]
 * 
 * DATA TYPES */

typedef struct user_ll {
    int ID;
    int TotalKarma;
    struct user_ll *Next;
} user_ll;

typedef struct karma_change kchange;

/* FUNCTION TO IMPLEMENT */

void FindAndUpdateKarma(user_ll* ListHead, int ID, kchange KarmaChange)
{
    while(ListHead){
        if(ListHead->ID == ID){
            UpdateKarma((struct user*)ListHead, KarmaChange);
            break;
        }
        ListHead = ListHead->Next;
    }
}

/* Exercise #3 - Adding to the end of a Linked List
 * 
 * BACKGROUND
 * 
 * In order to add to the end of a Linked List, the final entry must be iterated to, and
 * its next pointer updated to point to the new entry.
 * 
 * An exception is an empty linked list represented as a NULL head pointer. In this case the head
 * itself should be changed to be the new entry.
 * 
 * EXERCISE
 * 
 * Add the new entry, NewUser, to the end of the linked list that begins at ListHead, and
 * return the ListHead pointer.
 * 
 * If ListHead is null, then the list is currently empty. The ListHead you return should reflect that
 * NewUser has been added.
 * 
 * ADDITIONAL INFO
 * 
 * With an advanced understanding of pointers, it is possible to complete this exercise using
 * only a single loop and no if statements. You could try this as a bonus exercise. */

/* FUNCTION TO IMPLEMENT */

user_ll* AddNewUser(user_ll* ListHead, user_ll* NewUser)
{
    user_ll** l = &ListHead;
    while(*l) l = &(*l)->Next;
    *l = NewUser;
    return ListHead;
}

/* Exercise #4 - Removing from a Linked List
 * 
 * BACKGROUND
 * 
 * Removing from a Linked List requires similar code to adding, but in this case the node to be
 * removed could appear anywhere in the list and not just at the end.
 * 
 * This requires the Next pointer of the entry preceeding the removed one to be updated to point
 * to the entry after the removed one.
 * 
 * EXERCISE
 * 
 * Iterate the Linked List begining at ListHead for an entry with an ID matching the given ID.
 * If one is found, remove this entry, and pass it to the UserFree function.
 * 
 * Like before, the function should return the (maybe updated) ListHead and deal with empty list cases.
 * 
 * UserFree function declaration: */
void UserFree(user_ll*);

/* FUNCTION TO IMPLEMENT */

user_ll* RemoveUser(user_ll* ListHead, int ID)
{
    user_ll** l = &ListHead;
    while(*l && (*l)->ID != ID) l = &(*l)->Next;
    
    if(*l){
        UserFree(*l);
        *l = (*l)->Next;
    }
    return ListHead;
}


/* do not edit beyond this point */
#include "../../test_harness/2.c"
int main(void){	return test_lesson(); }
