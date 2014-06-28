#include "../rbstring.h"

#include <stdlib.h>
#include <stdio.h>

static void assertNotEqualInt(int a,int b){
	if(a==b){
		fprintf(stderr, "[line %d] Integers are equal: actual: %d; expected %d ",
			__LINE__,a,b);
		exit(1);
	}
}

static void assertEqualInt(int a,int b){
	if(a!=b){
		fprintf(stderr, "[line %d] Integers differs: actual: %d; expected %d ",
			__LINE__,a,b);
		exit(1);
	}
}

static void assertEqualStr(const char *a,const char *b){
	if(!(0==strcmp(a,b))){
		fprintf(stderr, "[line %d] Strings differs: %s != %s ",
			__LINE__,a,b);
		exit(1);
	}
}

static void test1(){
	strbuffer_t strbuff;
	strbuffer_init(&strbuff);

	assertEqualInt(strlen(strbuffer_value(&strbuff)),0);

	const char *str = "Hello world!";
	strbuffer_append(&strbuff,str);

	assertEqualStr(str,strbuffer_value(&strbuff));
}

static void test_append_escaped1(){
	strbuffer_t strbuff;
	strbuffer_init(&strbuff);

	assertEqualInt(strlen(strbuffer_value(&strbuff)),0);

	const char *str     = "Hello \"world\"!";
	const char *res_str = "Hello \\\"world\\\"!";
	strbuffer_append_escaped(&strbuff,str,"\"");

	assertNotEqualInt(0,strcmp(str,strbuffer_value(&strbuff)));
	assertEqualStr(res_str,strbuffer_value(&strbuff));
}

static void test_append_escaped2(){
	strbuffer_t strbuff;
	strbuffer_init(&strbuff);

	assertEqualInt(strlen(strbuffer_value(&strbuff)),0);

	// str = Hello \"world\"
	// res = Hello \\\"world\\\"
	const char *str     = "Hello \\\"world\\\"!"; 
	const char *res_str = "Hello \\\\\\\"world\\\\\\\"!";
	strbuffer_append_escaped(&strbuff,str,"\"\\");

	assertNotEqualInt(0,strcmp(str,strbuffer_value(&strbuff)));
	assertEqualStr(res_str,strbuffer_value(&strbuff));
}

int main(void){
	test1();
	test_append_escaped1();
	test_append_escaped2();
	return 0;
}