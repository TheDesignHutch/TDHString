#ifndef PERCEIVE_STRINGT_H
#define PERCEIVE_STRINGT_H

#include "StringLiteralT.h"
#include "StringCopy.h"
#include "StringCompare.h"
#include <cassert>

/** Stores the string wihtin a member array of fixed size.
	\remarks The memory will be allocated on the stack/heap based on where the owning String is created
*/
template < class _CharT, class _DataT >
class StringT : public _DataT
{
public:
	typedef _DataT DataT;
	
	//TODO: create STL compatible iterator types for algo support
	typedef _CharT* iterator;
	typedef const _CharT* const_iterator;

public:	
	StringT();

	/** Copy constructor of same type
	*/
	StringT( const StringT& rhs );

	/** Copy constructor of different type
	*/
	template < class _StringT > StringT( const _StringT& rhs );

	//As stringLiteral is constant access only we cannot supply a non-const array accessor
	//TODO: fund a work aroudn other than putting this in the base!
	const _CharT operator[] ( const size_t index ) const;

	/** size() for STL container compatibility
	*/
	size_t size() const
	{ return length(); }

	/** Clear string contents
		\remarks Does not affect internal capacity etc
	*/
	void clear()
	{ 
		resize(0);
		if ( m_str )
			m_str[0] = '\0';
	}

	/** Returns if no string is stored or if the first character is null temrinator (i.e. length() == 0)
	*/
	size_t empty() const
	{ return c_str() == 0 || *c_str() == '\0'; }

	void operator += ( const _CharT* rhs );

	template < class _StringT > void operator += ( const _StringT& rhs );	

	void append( const _CharT* rhs );
	void append( const _CharT* rhs, size_t rhsLength );

	template < class _StringT > void append( const _StringT& rhs );

	template < class _StringT > bool operator == ( const _StringT& rhs ) const;	
	template < class _StringT > bool operator < ( const _StringT& rhs ) const;
	template < class _StringT > bool operator > ( const _StringT& rhs ) const;
	template < class _StringT > bool operator <= ( const _StringT& rhs ) const;
	template < class _StringT > bool operator >= ( const _StringT& rhs ) const;
	
	void assign( const _CharT* rhs );
	void assign( const _CharT* rhs, size_t rhsLength );
	void assign( size_t pos, const _CharT* rhs );
	void assign( size_t pos, const _CharT* rhs, size_t rhsLength );
	
	template < class _StringT > void assign( const _StringT& rhs );
	template < class _StringT > void assign( unsigned int index, const _StringT& rhs );

	//TODO: proper iterator support
	iterator begin()
	{ return m_str; }

	//TODO: proper iterator support
	iterator end()
	{
		if ( !m_str ) return 0;
		return m_str+length();
	}

	//TODO: proper iterator support
	iterator rbegin()
	{
		if ( !m_str ) return 0;
		size_t len = length();
		if ( len ) len -= 1; //< move before the null terminator
		return m_str + len;
	}

	//TODO: proper iterator support
	iterator rend()
	{
		if ( !m_str ) return 0;
		return m_str-1; //< Return iterator before begin
	}
};


template < class _CharT, class _DataT >
StringT<_CharT,_DataT>::StringT()
	: _DataT()
{}

template < class _CharT, class _DataT >
StringT<_CharT,_DataT>::StringT( const StringT& rhs )
	: _DataT( rhs )
{}

template < class _CharT, class _DataT >
template < class _StringT >
StringT<_CharT,_DataT>::StringT( const _StringT& rhs )
	: _DataT()
{
	assign( rhs ); 
}

template < class _CharT, class _DataT >
const _CharT StringT<_CharT,_DataT>::operator[] ( const size_t index ) const
{ assert(m_str && index<capacity()); return m_str[index]; }

/*
template < class _CharT, class _DataT >
_CharT& StringT<_CharT,_DataT>::operator[] ( const size_t index )
{ assert(m_str && index<capacity()); return m_str[index]; }
*/

template < class _CharT, class _DataT >
template < class _StringT > 
void StringT<_CharT,_DataT>::operator += ( const _StringT& rhs )
{ append( rhs ); }

template < class _CharT, class _DataT >
void StringT<_CharT,_DataT>::operator += ( const _CharT* rhs )
{ assign( rhs ); }

template < class _CharT, class _DataT >
template < class _StringT >
void StringT<_CharT,_DataT>::append( const _StringT& rhs )
{ assign( length(), rhs ); }

template < class _CharT, class _DataT >
void StringT<_CharT,_DataT>::append( const _CharT* rhs )
{ assign( length(), rhs ); }

template < class _CharT, class _DataT >
void StringT<_CharT,_DataT>::append( const _CharT* rhs, size_t rhsLength )
{ assign( length(), rhs, rhsLength ); }

template < class _CharT, class _DataT >
void StringT<_CharT,_DataT>::assign( const _CharT* rhs )
{
	return StringCopy<_DataT,StringLiteralT<_CharT>>()( *this, StringLiteralT<_CharT>(rhs) ); 
}

template < class _CharT, class _DataT >
void StringT<_CharT,_DataT>::assign( const _CharT* rhs, size_t rhsLength )
{
	return StringCopy<_DataT,StringLiteralT<_CharT>>()( *this, StringLiteralT<_CharT>(rhs, rhsLength) ); 
}

template < class _CharT, class _DataT >
void StringT<_CharT,_DataT>::assign( size_t pos, const _CharT* rhs, size_t rhsLength )
{
	return StringCopy<_DataT,StringLiteralT<_CharT>>()( pos, *this, StringLiteralT<_CharT>(rhs, rhsLength) ); 
}

template < class _CharT, class _DataT >
template < class _StringT >
void StringT<_CharT,_DataT>::assign( const _StringT& rhs )
{
	return StringCopy<_DataT,_StringT::DataT>()( *this, rhs ); 
}

template < class _CharT, class _DataT >
template < class _StringT >
void StringT<_CharT,_DataT>::assign( size_t pos, const _StringT& rhs )
{
	return StringCopy<_DataT,_StringT::DataT>()( pos, *this, rhs ); 
}
template < class _CharT, class _DataT >
template < class _StringT > 
bool StringT<_CharT,_DataT>::operator == ( const _StringT& rhs ) const
{ 
	return StringCompare_Equal<_CharT,true>()( *this, rhs ); 
}

template < class _CharT, class _DataT >
template < class _StringT > 
bool StringT<_CharT,_DataT>::operator < ( const _StringT& rhs ) const
{ 
	return StringCompare_Less<_CharT,true>()( *this, rhs ); 
}

template < class _CharT, class _DataT >
template < class _StringT > 
bool StringT<_CharT,_DataT>::operator > ( const _StringT& rhs ) const
{ 
	return StringCompare_Greater<_CharT,true>()( *this, rhs ); 
}

template < class _CharT, class _DataT >
template < class _StringT > 
bool StringT<_CharT,_DataT>::operator <= ( const _StringT& rhs ) const
{ 
	return !(*this > rhs); 
}

template < class _CharT, class _DataT >
template < class _StringT > 
bool StringT<_CharT,_DataT>::operator >= ( const _StringT& rhs ) const
{ 
	return !(*this < rhs); 
}

#endif