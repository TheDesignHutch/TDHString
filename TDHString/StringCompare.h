#ifndef PERCEIVE_STRINGCOMPARE_H
#define PERCEIVE_STRINGCOMPARE_H

#include "StringT.h"
#include <string.h>

//-------------------------------------------------------------
// StringCompare
//-------------------------------------------------------------
template <  class _CharT, bool _CaseSensitive = true >
struct StringCompare
{
	/** \returns	-1 if lhs < rhs, 
					0 if lhs == rhs, 
					1 if lhs > rhs
	*/
	template < class _LhsDataT, class _RhsDataT >
	int operator()( const _LhsDataT& lhs, const _RhsDataT& rhs ) const;
	
	template < class _LhsDataT >
	int operator()( const _LhsDataT& lhs, const _CharT* rhs ) const;

	template < class _RhsDataT >
	int operator()( const _CharT* lhs, const _RhsDataT& rhs ) const;

	int operator()( const _CharT* lhs, const _CharT* rhs ) const;
};

//-------------------------------------------------------------
// StringCompare_Equal
//-------------------------------------------------------------
template <  class _CharT, bool _CaseSensitive = true >
struct StringCompare_Equal
{
	/** \returns true is lhs == rhs
	*/
	template < class _LhsDataT, class _RhsDataT >
	bool operator()( const _LhsDataT& lhs, const _RhsDataT& rhs ) const;
};

//-------------------------------------------------------------
// StringCompare_Less
//-------------------------------------------------------------
template <  class _CharT, bool _CaseSensitive = true >
struct StringCompare_Less
{
	/** \returns true is lhs < rhs
	*/
	template < class _LhsDataT, class _RhsDataT >
	bool operator()( const _LhsDataT& lhs, const _RhsDataT& rhs ) const;
};

//-------------------------------------------------------------
// StringCompare_Greater
//-------------------------------------------------------------
template <  class _CharT, bool _CaseSensitive = true >
struct StringCompare_Greater
{
	/** \returns true is lhs > rhs
	*/
	template < class _LhsDataT, class _RhsDataT >
	bool operator()( const _LhsDataT& lhs, const _RhsDataT& rhs ) const;
};

//-------------------------------------------------------------
// StringCompare Impl
//-------------------------------------------------------------
template <  class _CharT, bool _CaseSensitive>
template < class _LhsDataT, class _RhsDataT >
int StringCompare<_CharT,_CaseSensitive>::operator()( const _LhsDataT& lhs, const _RhsDataT& rhs ) const
{ return StringCompare<_CharT,_CaseSensitive>()( lhs.c_str(), rhs.c_str() ); }

template <  class _CharT, bool _CaseSensitive>
template < class _LhsDataT >
int StringCompare<_CharT,_CaseSensitive>::operator()( const _LhsDataT& lhs, const _CharT* rhs ) const
{ return StringCompare<_CharT,_CaseSensitive>()( lhs.c_str(), rhs ); }

template <  class _CharT, bool _CaseSensitive>
template < class _RhsDataT >
int StringCompare<_CharT,_CaseSensitive>::operator()( const _CharT* lhs, const _RhsDataT& rhs ) const
{ return StringCompare<_CharT,_CaseSensitive>()( lhs, rhs.c_str() ); }


template <>
int StringCompare<char,true>::operator()( const char* lhs, const char* rhs ) const
{ return strcmp( lhs, rhs ); }

# pragma warning(disable : 4996)
template <>
int StringCompare<char,false>::operator()( const char* lhs, const char* rhs ) const
{ return stricmp( lhs, rhs ); }
# pragma warning(default : 4996)

//-------------------------------------------------------------
// StringCompare_Equal Impl
//-------------------------------------------------------------
template <  class _CharT, bool _CaseSensitive >
template<class _LhsDataT, class _RhsDataT>
bool StringCompare_Equal<_CharT,_CaseSensitive>::operator()( const _LhsDataT& lhs, const _RhsDataT& rhs ) const
{ return StringCompare<_CharT,_CaseSensitive>()( lhs, rhs ) == 0; }

//-------------------------------------------------------------
// StringCompare_Less Impl
//-------------------------------------------------------------
template <  class _CharT, bool _CaseSensitive >
template<class _LhsDataT, class _RhsDataT>
bool StringCompare_Less<_CharT,_CaseSensitive>::operator()( const _LhsDataT& lhs, const _RhsDataT& rhs ) const
{ return StringCompare<_CharT,_CaseSensitive>()( lhs, rhs ) < 0; }

//-------------------------------------------------------------
// StringCompare_Greater Impl
//-------------------------------------------------------------
template <  class _CharT, bool _CaseSensitive >
template<class _LhsDataT, class _RhsDataT>
bool StringCompare_Greater<_CharT,_CaseSensitive>::operator()( const _LhsDataT& lhs, const _RhsDataT& rhs ) const
{ return StringCompare<_CharT,_CaseSensitive>()( lhs, rhs ) > 0; }

#endif
