#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <iostream>
using std::iostream;

#include <stack>
using std::stack;

#include <string>
using std::string;

#include <list>
using std::list;

//interface
std::string PatternSearch(const unsigned char* pStr, const unsigned char* pMatch);

//helper functions
std::string MatchStack(const unsigned char* pStr, const unsigned char* pMatch, int d, list<unsigned char> operrantList);
std::string Matcher(const unsigned char* pStr, const unsigned char* pMatch);
/**
*
*
**/

//stack<unsigned char> operatorStack;
//container not null-terminated string just container, hence need to be transfered to null-terminated const string or string object in the future.
//list<unsigned char> operrantList; 

int MatchState;

//helper function for stacks processing
std::string MatchStack(const unsigned char* pStr, const unsigned char* pMatch, int d, list<unsigned char> operrantList){
	int len = operrantList.size();

	//obtain the memories dynamically from memory stack
	unsigned char* strList = (unsigned char*)malloc(sizeof(unsigned char) * (len + 1));
	 
	int i = 0;
	for(std::list<unsigned char>::iterator iter = operrantList.begin(); iter != operrantList.end(); iter++){
		strList[i] = *iter;
		i++;
	}
	strList[len] = '\0';

	string prefix = "";
	string curr;
	while(d > 0 && MatchState == 1){
		//implicitly casting
		 curr = Matcher(pStr, strList);

		 if(MatchState == 0){
			return prefix + curr;
		 }

		 prefix = prefix + curr;

		 pStr = pStr + curr.length();
		 d--;
	}

	//There is no need to explicitly reset the MatchState here.
	// In case of d == 0 && MatchState == 0
	if(MatchState == 1){
		curr = Matcher(pStr, pMatch);
	}

	free(strList);
	strList = NULL;
	return prefix + curr;
}

/**
*	This function is called by the PatternSearch interface. 
*	Since returned string is overwirtten, 
*	I didn't use key word 'const' to decorate the helper function
**/

/**
*	Backtracing Strategy:
**/
std::string Matcher(const unsigned char* pStr, const unsigned char* pMatch){

	switch(*pMatch){
		case '\0':
			return string("\0");
		case '$':
			return string("\0");
		default:
			break;
	}
/**
*	Wildcard character
**/
	//stack processing 1
	if(*(pMatch + 1) == '*'){
		char c = *pStr;
		const char cc[] = {c, '\0'};
		string prefix = "";
		string curr;
		do{
			curr = Matcher(pStr, pMatch + 2);
			if(MatchState == 1){
				return prefix + curr;
			}
			//try again
			MatchState = 1;
			
			prefix = prefix + cc;
			//The unique positon at which pStr changes
		}while(*pStr != '\0' && (*pStr++ == c || c == '.'));

		MatchState = 0;
		return prefix + curr;
	}
/**
*	Character Processing;
*	C++ forbids a goto to control bypass an initialization of non-POD object;
*	Transfer the declearation outside of the switch stences since a switch in C++ is an essentially goto sentence 
**/
	const unsigned char rptRegex[] = "{\d}";
	string rptMode;

	stack<unsigned char> operatorStack;
	list<unsigned char> operrantList;
	switch(*pMatch){
		case '.':
			if(*pStr != '\0'){
				const char curr[] = {*pStr, '\0'};
				return string(curr) + Matcher(pStr+1, pMatch+1);
			}else{
				MatchState = 0;
				
				return string("\0");
			}
		case '[':
			//stack processing 2

			//step1 : build comparison mode 
			operatorStack.push('[');
			
			//the unique position which change the Regex pointer at current stage.
			pMatch++;
			while(!operatorStack.empty()){
				if(*pMatch == '\0'){
					MatchState = 0;
					return string("\0");
				}

				else if(*pMatch == '['){
					operatorStack.push('[');
					operrantList.push_back(*pMatch);
				}

				//There is no need to judge the peek element in this case
				else if(*pMatch == ']'){
					operatorStack.pop();
					if(!operatorStack.empty()){
						operrantList.push_back(*pMatch);
					}
				}

				else {
					operrantList.push_back(*pMatch);
				}
				pMatch++;
			}//endWhile
			
			//rptMode = Matcher(pMatch, rptRegex);
			if(*pMatch == '{' && *(pMatch + 1) >= '0' && *(pMatch + 1) <= '9' && *(pMatch + 2) == '}'){
				
			}else{
				MatchState = 0;
				return string("\0");
			}

			if(MatchState == 1){
				//int d = rptMode.c_str()[1] - '0';
				int d = *(pMatch + 1) - '0';
				// Recursive Matching Entry
				return MatchStack(pStr, pMatch + 3, d, operrantList);
			}else{
				return string("\0");
			}
			
		case '{':
			//stack processing 3
		case '\d':
			if(*pStr > '0' && *pStr < '9'){
				const char curr[] = {*pStr, '\0'};
				return string(curr) + Matcher(pStr+1, pMatch+1);
			}else{
				return string("\0");
			}

		default:
			if(*pStr != '\0'){
				if(*pStr == *pMatch){
					const char curr[] = {*pStr, '\0'};
					return string(curr) + Matcher(pStr+1, pMatch+1);
				}else{
					return Matcher(pStr+1, pMatch);
				}
			}else{
				MatchState = 0;
				return string("");
			}	
	}
}

std::string PatternSearch(const unsigned char* pStr, const unsigned char* pMatch){
	//initializtion
	MatchState = 1;
	/*
	while(!operatorStack.empty()){
		operatorStack.pop();
	}
	*/

	//operrantList.clear();

	//launch the routine
	string result = Matcher(pStr, pMatch);

	if(MatchState == 1){
		return result;
	}else{
		return string("Regex Error! or Not Match!");
	}
}