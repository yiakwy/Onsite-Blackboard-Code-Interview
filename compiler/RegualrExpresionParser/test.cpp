#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <iostream>
using std::iostream;

#include <string>
using std::string;

std::string PatternSearch(const unsigned char* pStr, const unsigned char* pMatch);

void main(){
	//const unsigned char text[]	= "??abcdefdefghi??";
	//const unsigned char regex[] = "abc[def]{2}ghi";
	//const unsigned char text[] = "?aac";
	//const unsigned char regex[] = "[a]{2}";
	const unsigned char text[] = "?abbabbac";
	const unsigned char regex[] = "[a[b]{2}]{2}";

	std::cout<<PatternSearch(text, regex)<<std::endl;
}