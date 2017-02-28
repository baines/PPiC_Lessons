#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define countof(x) (sizeof(x)/sizeof(*x))

static const char* __knames[] = { "KARMA_DECREASE", "KARMA_INCREASE" };

void test_update_karma(void){
    puts("Testing [UpdateKarma]...");

    for(int i = 0; i < 20; ++i){
        struct user u = { rand() % 1000, (rand() % 2000) - 1000 }, orig = u;
        kchange     k = { rand() % 2   , (rand() % 2000) - 1000 };

        UpdateKarma(&u, k);

        static const int mult[] = { -1, 1 };
        int expected = orig.TotalKarma + k.Value * mult[k.Type];

        if(u.TotalKarma != expected){
            printf(
                "Test failed.\n"
                "Input:\n"
                "\tUser:        { ID: %d, TotalKarma: %d }\n"
                "\tKarmaChange: { Type: %s, Value: %d }\n"
                "Output:\n\tGot: TotalKarma = %d\n\tExpected:         %d\n",
                orig.ID, orig.TotalKarma, __knames[k.Type], k.Value, u.TotalKarma, expected
            );
            exit(1);
        }
    }
    puts("  Passed!");
}

user_ll* __gen_ll(struct user* users){
    user_ll* head = NULL;
    user_ll** prev = &head;

    for(struct user* u = users; u && u->ID; ++u){
        user_ll* l = calloc(1, sizeof(*l));
        memcpy(l, u, sizeof(*u));
        *prev = l;
        prev = &l->Next;
    }

    return head;
}

void __free_ll(user_ll* list){
    while(list){
        user_ll* next = list->Next;
        free(list);
        list = next;
    }
}

void __print_ll(user_ll* list){
    while(list){
        printf("{ %d, %d }, ", list->ID, list->TotalKarma);
        list = list->Next;
    }
    puts("");
}

void __print_usr(struct user* users){
    while(users && users->ID){
        printf("{ %d, %d }, ", users->ID, users->TotalKarma);
        ++users;
    }
    puts("");
}

#define __usr(...) (struct user[]){ __VA_ARGS__, 0 }

void test_find_karma(void){
    puts("Testing [FindAndUpdateKarma]...");

    struct Test {
        struct user* users;
        struct user* expected;
        int id;
        kchange k;
    } tests[] = {
        {
            __usr({ 123, 456 }, { 952, 1535 }, { 341, 3590 }, { 13241, 589 }),
            __usr({ 123, 456 }, { 952, 1412 }, { 341, 3590 }, { 13241, 589 }),
            952, { 0, 123 }
        },
        {
            NULL,
            NULL,
            1234, { 1, 101 }
        },
        {
            __usr({ 321, -456 }, { 141, 1561 }, { 341, 15231 }),
            __usr({ 321, -456 }, { 141, 1561 }, { 341, 15231 }),
            1231, { 0, 123 }
        },
        {
            __usr({ 123, 456 }, { 952, 1535 }, { 341, 3590 }, { 13241, 589 }),
            __usr({ 123, 579 }, { 952, 1535 }, { 341, 3590 }, { 13241, 589 }),
            123, { 1, 123 }
        },
        {
            __usr({ 123, 456 }, { 952, 1412 }, { 341, 3590 }, { 1, 589 }),
            __usr({ 123, 456 }, { 952, 1412 }, { 341, 3590 }, { 1, 585 }),
            1, { 0, 4 }
        },
    };

    for(int i = 0; i < countof(tests); ++i){
        struct Test* t = tests + i;

        user_ll* list = __gen_ll(t->users);
        FindAndUpdateKarma(list, t->id, t->k);

        int idx = 0;
        for(user_ll* l = list; l; l = l->Next, ++idx){
            if(l->ID != t->expected[idx].ID || l->TotalKarma != t->expected[idx].TotalKarma){
                printf("Test Failed.\nInput:\n\tID=%d, KarmaChange=(%s, %d)\n\tList: ", t->id, __knames[t->k.Type], t->k.Value);
                __print_usr(t->users);
                printf("Output:\n\t");
                __print_ll(list);
                printf("Expected:\n\t");
                __print_usr(t->expected);
                __free_ll(list);
                exit(1);
            }
        }

        __free_ll(list);
    }
    puts("  Passed!");
}

void test_add_user(void){
    puts("Testing [AddNewUser]...");

    struct Test {
        int count;
        struct user* users;
        struct user_ll usr;
    } tests[] = {
        { 4, __usr({ 123, 456 }, { 952, 1535 }, { 341, 3590 }, { 13241, 589 }), { 163, 593 } },
        { 0, NULL, { 1234, 5642 } },
        { 1, __usr({ 1, 1 }), { 2, 2 } },
    };

    for(int i = 0; i < countof(tests); ++i){
        struct Test* t = tests + i;

        struct user* users = calloc(t->count+2, sizeof(*users));
        memcpy(users, t->users, sizeof(*users) * t->count);
        memcpy(users+t->count, &t->usr, sizeof(t->usr));

        user_ll* list = __gen_ll(t->users);
        user_ll* newu = calloc(1, sizeof(*newu));
        memcpy(newu, &t->usr, sizeof(*newu));

        user_ll* ret = AddNewUser(list, newu);

        int idx = 0;
        for(user_ll* l = ret; l; l = l->Next, ++idx){
            if(l->ID != users[idx].ID || l->TotalKarma != users[idx].TotalKarma){
rip:
                printf("Test Failed.\nInput:\n\tNewUser: { %d, %d }\n\tList: ", t->usr.ID, t->usr.TotalKarma);
                __print_usr(t->users);
                printf("Output:\n\tList: ");
                __print_ll(ret);
                printf("Expected:\n\tList: ");
                __print_usr(users);
                free(users);
                __free_ll(ret);
                exit(1);
            }
        }

        if(idx != t->count+1) goto rip;

        free(users);
        __free_ll(ret);
    }
    puts("  Passed!");
}

static user_ll* __last_user_free_ptr;
void UserFree(user_ll* ptr){
    __last_user_free_ptr = ptr;
}

void test_remove_user(void){
    puts("Testing [RemoveUser]...");

    struct Test {
        struct user* users;
        struct user* expected;
        int id;
        int expected_count;
        int rm_idx;
    } tests[] = {
        {
            __usr({ 123, 456 }, { 952, 1535 }, { 341, 3590 }, { 13241, 589 }),
            __usr({ 123, 456 }, { 341, 3590 }, { 13241, 589 }),
            952, 3, 1
        },
        {
            NULL,
            NULL,
            123, 0, -1
        },
        {
            __usr({ 123, 456 }, { 952, 1535 }, { 341, 3590 }),
            __usr({ 952, 1535 }, { 341, 3590 }),
            123, 2, 0
        },
        {
            __usr({ 123, 456 }),
            NULL,
            123, 0, 0
        },
    };

    for(int i = 0; i < countof(tests); ++i){
        struct Test* t = tests + i;

        user_ll* list = __gen_ll(t->users);

        user_ll* rm_ptr;
        if(t->rm_idx == -1){
            rm_ptr = (void*)0xbadc0de;
        } else {
            rm_ptr = list;
            for(int i = 0; i < t->rm_idx; ++i) rm_ptr = rm_ptr->Next;
        }

        __last_user_free_ptr = (void*)0xbadc0de;
        user_ll* ret = RemoveUser(list, t->id);
        if(__last_user_free_ptr != rm_ptr){
            if(__last_user_free_ptr == (void*)0xbadc0de){
                printf("BUG: UserFree was not called.\n");
            } else {
                printf("BUG: UserFree was called on %p, expected %p.\n", __last_user_free_ptr, rm_ptr);
            }
            goto rip;
        }

        int idx = 0;
        for(user_ll* l = ret; l; l = l->Next, ++idx){
            if(l->ID != t->expected[idx].ID || l->TotalKarma != t->expected[idx].TotalKarma){
rip:
                printf("Test Failed.\nInput:\n\tID: %d\n\tList: ", t->id);
                __print_usr(t->users);
                printf("Output:\n\tList: ");
                __print_ll(ret);
                printf("Expected:\n\tList: ");
                __print_usr(t->expected);
                __free_ll(ret);
                exit(1);
            }
        }

        if(idx != t->expected_count) goto rip;

        if(rm_ptr != (void*)0xbadc0de){
            free(rm_ptr);
        }
        __free_ll(ret);
    }
    puts("  Passed!");
}

int test_lesson(void){
    test_update_karma();
    test_find_karma();
    test_add_user();
    test_remove_user();
    puts("Congratulations, You've completed Lesson 2!");
    return 0;
}
