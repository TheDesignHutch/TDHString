#ifndef PERCEIVE_STRING_H
#define PERCEIVE_STRING_H

#include "StringT.h"
#include "StringDynamicT.h"
#include "StringFixedT.h"
#include "StringLiteralT.h"

/** Literal string type. Use for constant strings (rea-only) and pass by value to function
	\remarks Read only const char* interface
*/
typedef StringT<char,StringLiteralT<char>> StringLiteral;

/** Fixed stack/member-memory fixed length string
	\remarks If a new String32() is called then the memory is therefor eon the heap as is expected
*/
typedef StringT<char,StringFixedT<char,8>> String8;
typedef StringT<char,StringFixedT<char,16>> String16;
typedef StringT<char,StringFixedT<char,32>> String32;
typedef StringT<char,StringFixedT<char,128>> String64;
typedef StringT<char,StringFixedT<char,128>> String128;
typedef StringT<char,StringFixedT<char,256>> String256;

/** Fixed heap-memory fixed length string
	\remarks Use where a longer string is needed than StringFixedT or where stack memory is 
	limited i.e. recursive function-calls
*/
typedef StringT<char,StringFixedHeapT<char,8>> StringFixed;

/** Dynamic length string using heap-memory
	\remarks Similar to std::string or other string classes
*/
typedef StringT<char,StringDynamicHeapT<char>> String;

#endif