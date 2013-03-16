// StringTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "TDHString\String.h"

#include <cassert>

#define BEGIN_TESTS \
	printf( ">>Started: " __FUNCTION__ "\n" ); \
	unsigned int failureCount = 0;

#define TEST( _test, _check ) { \
	int result = (_test); \
	if ( !(_check) ) { \
		++failureCount; \
		printf( "\t-FAIL: " #_test "\n\t\tTest " #_check ", result= %d\n", result ); \
	} else { \
		printf( "\t+PASS: " #_test "\n\t\tTest " #_check ", result= %d\n", result ); \
	} }

#define END_TESTS \
	if ( failureCount != 0 ) \
		printf( "--FAILED: " __FUNCTION__ ". Failure count %u\n", failureCount ); \
	else \
		printf( "++PASSED: " __FUNCTION__ "\n" ); \
	return failureCount == 0;

//#define TESTS_FUNCTION( _name ) \

//-------------------------------------------------------------
// StringCompare test
//-------------------------------------------------------------
bool testCompare()
{
	BEGIN_TESTS;

	//Case sensitive
	TEST( (StringCompare<char,true>()("a", "a")), (result == 0) );
	TEST( (StringCompare<char,true>()("a", "b")), (result == -1) );
	TEST( (StringCompare<char,true>()("b", "a")), (result == 1) );

	//Case insensitive
	TEST( (StringCompare<char,false>()("a", "a")), (result == 0) );
	TEST( (StringCompare<char,false>()("a", "b")), (result == -1) );
	TEST( (StringCompare<char,false>()("b", "a")), (result == 1) );
	TEST( (StringCompare<char,false>()("A", "a")), (result == 0) );
	TEST( (StringCompare<char,false>()("A", "b")), (result == -1) );
	TEST( (StringCompare<char,false>()("B", "a")), (result == 1) );

	//Case sensitive
	TEST( (StringCompare_Equal<char,true>()("a", "a")), (result == 1) );
	TEST( (StringCompare_Equal<char,true>()("a", "b")), (result == 0) );
	TEST( (StringCompare_Equal<char,true>()("b", "a")), (result == 0) );

	//Case insensitive
	TEST( (StringCompare_Equal<char,false>()("a", "a")), (result == 1) );
	TEST( (StringCompare_Equal<char,false>()("a", "b")), (result == 0) );
	TEST( (StringCompare_Equal<char,false>()("b", "a")), (result == 0) );
	TEST( (StringCompare_Equal<char,false>()("A", "a")), (result == 1) );
	TEST( (StringCompare_Equal<char,false>()("A", "b")), (result == 0) );
	TEST( (StringCompare_Equal<char,false>()("B", "a")), (result == 0) );

	//Case sensitive
	TEST( (StringCompare_Less<char,true>()("a", "a")), (result == 0) );
	TEST( (StringCompare_Less<char,true>()("a", "b")), (result == 1) );
	TEST( (StringCompare_Less<char,true>()("b", "a")), (result == 0) );

	//Case insensitive
	TEST( (StringCompare_Less<char,false>()("a", "a")), (result == 0) );
	TEST( (StringCompare_Less<char,false>()("a", "b")), (result == 1) );
	TEST( (StringCompare_Less<char,false>()("b", "a")), (result == 0) );
	TEST( (StringCompare_Less<char,false>()("A", "a")), (result == 0) );
	TEST( (StringCompare_Less<char,false>()("A", "b")), (result == 1) );
	TEST( (StringCompare_Less<char,false>()("B", "a")), (result == 0) );

	//Case sensitive
	TEST( (StringCompare_Greater<char,true>()("a", "a")), (result == 0) );
	TEST( (StringCompare_Greater<char,true>()("a", "b")), (result == 0) );
	TEST( (StringCompare_Greater<char,true>()("b", "a")), (result == 1) );

	//Case insensitive
	TEST( (StringCompare_Greater<char,false>()("a", "a")), (result == 0) );
	TEST( (StringCompare_Greater<char,false>()("a", "b")), (result == 0) );
	TEST( (StringCompare_Greater<char,false>()("b", "a")), (result == 1) );
	TEST( (StringCompare_Greater<char,false>()("A", "a")), (result == 0) );
	TEST( (StringCompare_Greater<char,false>()("A", "b")), (result == 0) );
	TEST( (StringCompare_Greater<char,false>()("B", "a")), (result == 1) );

	END_TESTS;
}

template< class _TString >
bool testStringConstructAssign8()
{
	BEGIN_TESTS;

	//Test strings
	const int kSCount = 7;
	const char* s[kSCount] = {
		"1", "12", "123", "1234", "12345", "123456", "1234567" };

	//Error strings
	const int kECount = 7;
	const char* e[2] = {
		0, "12345678" };

	_TString fixedDefault;
	//For fixed strings there is always a valid zero length string
	if ( fixedDefault.c_str() )
		TEST( (fixedDefault[0]), (result == '\0') )
	else
		TEST( ((int)fixedDefault.c_str()), (result == 0) )

	TEST( (fixedDefault.length()), (result == 0) );

	//Constructor from string
	for ( int i =0; i < kSCount; ++i )
	{
		_TString fixed( s[i] );
		TEST( (StringCompare_Equal<char>()(fixed, s[i])), (result == 1) );
	}

	//Assignment multiple times to existing instance
	for ( int i =0; i < kSCount; ++i )
	{
		fixedDefault = s[i];
		TEST( (StringCompare_Equal<char>()(fixedDefault, s[i])), (result == 1) );
	}
	
	//Assignment to a default initialised string array
	_TString arrFixedDefault[kSCount];
	for ( int i =0; i < kSCount; ++i )
	{
		arrFixedDefault[i] = s[i];
		TEST( (StringCompare_Equal<char>()(arrFixedDefault[i], s[i])), (result == 1) );
	}

	//Copy from string to string
	_TString arrFixedDefault2[kSCount];
	for ( int i =0; i < kSCount; ++i )
	{
		arrFixedDefault2[i] = arrFixedDefault[i];
		TEST( (StringCompare_Equal<char>()(arrFixedDefault2[i], s[i])), (result == 1) );
	}

	const _TString arrInit[kSCount] = {
		s[0], s[1], s[2], s[3], s[4], s[5], s[6] };
	for ( int i =0; i < kSCount; ++i )
	{
		TEST( (StringCompare_Equal<char>()(arrInit[i], s[i])), (result == 1) );
	}

	END_TESTS;
}


template< class _TString >
bool testStringAppend8()
{
	BEGIN_TESTS;

	//Test strings
	const int kSCount = 7;
	const _TString sA[kSCount] = {
		"1", "12", "123", "1234", "12345", "123456", "1234567" };

	const _TString sB[kSCount] = {
		"234567", "34567", "4567", "567", "67", "7", "" };
	
	const _TString sAB = "1234567";

	//Construct, append
	for ( int i =0; i < kSCount; ++i )
	{
		_TString conc( sA[i] );
		conc += sB[i];
		TEST( (StringCompare_Equal<char>()(conc, sAB)), (result == 1) );
	}

	//Assign, append
	for ( int i =0; i < kSCount; ++i )
	{
		_TString conc;
		conc = sA[i];
		conc += sB[i];
		TEST( (StringCompare_Equal<char>()(conc, sAB)), (result == 1) );
	}

	//Append, append
	for ( int i =0; i < kSCount; ++i )
	{
		_TString conc;
		conc += sA[i];
		conc += sB[i];
		TEST( (StringCompare_Equal<char>()(conc, sAB)), (result == 1) );
	}

	END_TESTS;
}

template< class _TStringA,class _TStringB >
bool testStringAssign8()
{
	BEGIN_TESTS;
	const char* s1[3] = { "a", "b", "c" };
	const char* s2[3] = { "a", "b", "c" };

	_TStringA a[3] = { s1[0], s1[1], s1[2] };	
	for ( int i =0; i < 3; ++i )
		TEST( (StringCompare_Equal<char>()(a[i], s1[i])), (result == 1) );

	_TStringB b[3] = { s2[0], s2[1], s2[2] };
	for ( int i =0; i < 3; ++i )
		TEST( (StringCompare_Equal<char>()(b[i], s2[i])), (result == 1) );

	//Make copy of b into a
	for ( int i =0; i < 3; ++i )
	{
		a[i] = b[i];
		TEST( (StringCompare_Equal<char>()(a[i], s2[i])), (result == 1) );
		TEST( (StringCompare_Equal<char>()(b[i], s2[i])), (result == 1) );
		TEST( (StringCompare_Equal<char>()(a[i], b[i])), (result == 1) );
	}

	//Replace values in b with s1
	for ( int i =0; i < 3; ++i )
	{
		b[i] = s1[i];
		TEST( (StringCompare_Equal<char>()(a[i], s2[i])), (result == 1) );
		TEST( (StringCompare_Equal<char>()(b[i], s1[i])), (result == 1) );
	}

	END_TESTS;
}

//-------------------------------------------------------------
// StringCompare test
//-------------------------------------------------------------
typedef StringT<char,StringLiteralT<char>> Literal;
typedef StringT<char,StringFixedT<char,8>> Fixed;
typedef StringT<char,StringFixedHeapT<char,8>> FixedHeap;
typedef StringT<char,StringDynamicHeapT<char>> DynamicHeap;

bool testStringAssign()
{
	BEGIN_TESTS;	


	TEST( (testStringConstructAssign8< Literal >()), (result == 1) );
	TEST( (testStringConstructAssign8< Fixed >()), (result == 1) );
	TEST( (testStringConstructAssign8< FixedHeap >()), (result == 1) );
	TEST( (testStringConstructAssign8< DynamicHeap >()), (result == 1) );
	
	TEST( (testStringAssign8< Literal, Literal >()), (result == 1) );
	
	TEST( (testStringAssign8< Fixed, Literal >()), (result == 1) );
	TEST( (testStringAssign8< Fixed, Fixed >()), (result == 1) );
	TEST( (testStringAssign8< FixedHeap, Fixed >()), (result == 1) );
	TEST( (testStringAssign8< DynamicHeap, Fixed >()), (result == 1) );

	TEST( (testStringAssign8< FixedHeap, Literal >()), (result == 1) );
	TEST( (testStringAssign8< Fixed, FixedHeap >()), (result == 1) );
	TEST( (testStringAssign8< FixedHeap, FixedHeap >()), (result == 1) );
	TEST( (testStringAssign8< DynamicHeap, FixedHeap >()), (result == 1) );

	TEST( (testStringAssign8< DynamicHeap, Literal >()), (result == 1 ) );
	TEST( (testStringAssign8< Fixed, DynamicHeap >()), (result == 1) );
	TEST( (testStringAssign8< FixedHeap, DynamicHeap >()), (result == 1) );
	TEST( (testStringAssign8< DynamicHeap, DynamicHeap >()), (result == 1) );

	END_TESTS;
}

bool testStringAppend()
{
	BEGIN_TESTS;	

	TEST( (testStringAppend8< Fixed >()), (result == 1) );
	TEST( (testStringAppend8< FixedHeap >()), (result == 1) );
	TEST( (testStringAppend8< DynamicHeap >()), (result == 1) );

	END_TESTS;
}


bool runTests()
{
	BEGIN_TESTS;
	TEST( (testCompare()), (result == 1) );
	TEST( (testStringAssign()), (result == 1) );
	TEST( (testStringAppend()), (result == 1) );

	END_TESTS;
}

int _tmain(int argc, _TCHAR* argv[])
{
	bool ret = runTests();
	assert(ret);


	return ret;
}

