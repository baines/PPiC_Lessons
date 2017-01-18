#include <string.h>
#include <stdio.h>

#define countof(x) (sizeof(x)/sizeof(*x))

void test_dude(void){
	puts("Testing [DudeWheresMyChar]...");
	
	struct Test {
		const char* str;
		char c;
		int expected;
	} tests[] = {
		{ "Dude" , 'd', 2 },
		{ "Sweet", 'e', 2 },
		{ "Dude" , 'D', 0 },
		{ "Sweet", 't', 4 },
		{ "And then?", 'a', -1 },
		{ "And then?", ' ', 3 },
		{ "And then?", '\3', -1 },
	};
	
	for(int i = 0; i < countof(tests); ++i){
		struct Test* t = tests + i;
		int ret = DudeWheresMyChar(t->str, t->c);
		if(ret != t->expected){
			printf(
				"Test failed.\n"
				"Input:\n\tString: '%s'\n\tWhich: '%c'\n"
				"Output:\n\tGot: %d\n\tExpected: %d\n",
				t->str, t->c, ret, t->expected
			);
			exit(1);
		}
	}
	puts("  Passed!");
}

void test_substring(void){
	puts("Testing [SubString]...");
	
	struct Test {
		const char* haystack;
		const char* needle;
		int haylen;
		int expected;
	} tests[] = {
		{ "the quick brown fox jumps over the lazy dog", "fox", 43, 16 },
		{ "the quick brown fox jumps over the lazy dog", "dog", 20, -1 },
		{ "hello", "sailor", 5, -2 },
		{ "asdfg", "asdfg", 5, 0 },
		{ "good luck miblo", "lo", 15, 13 },
		{ "test", "testing", 4, -2 },
		{ "i like turtles", " ", 14, 1 },
		{ "interesting", "int", 1, -2 },
		{ "something", "", 9, 0 },
		{ "Badger badger badger.", "badger", 21, 7 },
		{ "Badger badger badger.", "SNAKE!", 21, -1 },
	};
	
	for(int i = 0; i < countof(tests); ++i){
		struct Test* t = tests + i;
		int ret = SubString(t->haystack, t->haylen, t->needle);
		if(ret != t->expected){
			printf(
				"Test failed.\n"
				"Input:\n\tHayStack: '%.*s'\n\tNeedle: '%s'\n"
				"Output:\n\tGot: %d\n\tExpected: %d\n",
				t->haylen, t->haystack, t->needle, ret, t->expected
			);
			exit(1);
		}
	}
	
	puts("  Passed!");
}

void test_memoryhole(void){
	puts("Testing [MemoryHole]...");
	
	struct Test {
		char** strs_in;
		char** strs_out;
		const char* word;
		int count;
		int expected;
	} tests[] = {
		{
			(char*[]){ "To: Mr Bush", "I heard 'Bush hid the facts'", "Is that true?" },
			(char*[]){ "To: Mr XXXX", "I heard 'XXXX hid the facts'", "Is that true?" },
			"Bush", 3, 1
		},
		{
			(char*[]){ "The C programming language is really Cool" },
			(char*[]){ "The X programming language is really Xool" },
			"C", 1, 1
		},
		{
			(char*[]){ "¯\\_(ツ)_/¯"},
			(char*[]){ "¯\\_(ツ)_/¯" },
			"blah", 1, 0
		},
		{
			(char*[]){ "Arr matey.", "I marks the spot." },
			(char*[]){ "Arr matey.", "X marks the spot." },
			"I", 2, 1
		},
		{
			(char*[]){ "I like watching cat videos." },
			(char*[]){ "I like watching XXX videos." },
			"cat", 1, 1
		},
	};
	
	for(int i = 0; i < countof(tests); ++i){
		struct Test* t = tests + i;
		
		for(int j = 0; j < t->count; ++j){
			t->strs_in[j] = strdupa(t->strs_in[j]);
		}
		
		int ret = MemoryHole(t->strs_in, t->count, t->word);
		
		int bad_idx = -1;
		for(int j = 0; j < t->count; ++j){
			if(strcmp(t->strs_in[j], t->strs_out[j]) != 0){
				bad_idx = j;
				break;
			}
		}

		if(ret != t->expected){
			printf(
				"Test failed.\n"
				"Input:\n\tWord: '%s'\n"
				"Output:\n\t"
				"Got:      Result=%d\n\t"
				"Expected: Result=%d\n",
				t->word, ret, t->expected
			);
			exit(1);
		}

		if(bad_idx >= 0){
			printf(
				"Test failed.\n"
				"Input:\n\tWord: '%s'\n"
				"Output:\n\t"
				"Got:      StrArray[%d]='%s'\n\t"
				"Expected: StrArray[%d]='%s'\n",
				t->word, bad_idx, t->strs_in[bad_idx], bad_idx, t->strs_out[bad_idx]
			);
			exit(1);
		}
	}
	
	puts("  Passed!");	
}

void test_concat(void){
	puts("Testing [ConcatenateAll]...");
	
	struct Test {
		const char** strs;
		int* sizes;
		const char* expected;
	} tests[] = {
		{
			(const char*[]){ "the quick *$%&(", "brown fox %$!^", "jumps over ^$^&", "the lazy doggggggg", NULL },
			(int[]){ 10, 10, 11, 12 },
			"the quick brown fox jumps over the lazy dog"
		},
		{
			(const char*[]){ "miblo", "iblom", "blomi", "lomib", "omibl", NULL },
			(int[]){ 1, 1, 1, 1, 1 },
			"miblo"
		},
		{
			(const char*[]){ "how to cook dinner", "for(int i = 0;", "tyvm", " humans", NULL },
			(int[]){ 12, 3, 0, 7 },
			"how to cook for humans"
		}
	};
	
	for(int i = 0; i < countof(tests); ++i){
		struct Test* t = tests + i;
		char* str = ConcatenateAll(t->strs, t->sizes);
		if(strcmp(str, t->expected) != 0){
			printf(
				"Test failed.\n"
				"Output:\n\tGot: '%s'\n\tExpected: '%s'\n",
				str, t->expected
			);
			exit(1);
		} else {
			free(str); // if you crash here, you did not allocate the string correctly.
		}
	}
	
	puts("  Passed!");
}

int test_lesson(void){
	test_dude();
	test_substring();
	test_memoryhole();
	test_concat();
	puts("Congratulations, You've passed Lesson 1!");
	return 0;
}
