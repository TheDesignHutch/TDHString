#ifndef PERCEIVE_FIXEDSTRING_H
#define PERCEIVE_FIXEDSTRING_H

#include "StringT.h"
#include <cassert>

/** Stores the string wihtin a member array of fixed size.
	\remarks The memory will be allocated on the stack/heap based on where the owning String is created
*/
template < class _CharT, size_t _MaxStorageLen >
class StringFixedT
{
public:

	StringFixedT() 
	{ assert(_MaxStorageLen); m_str[0] = '\0'; }

	StringFixedT( const StringFixedT& rhs ) 
	{ *this = rhs; }

	const _CharT* c_str() const
	{ return m_str; }

	size_t capacity() const
	{ return _MaxStorageLen; }

	size_t length() const
	{ return strlen(m_str); }

	bool resize( size_t size )
	{
		//TODO: to error, or not to error, to crimp off, or fail etc
		return size <= capacity(); 
	}

	void operator = ( const StringFixedT& rhs )
	{ memcpy_s( m_str, sizeof(*m_str) * capacity(), rhs.m_str, sizeof(*rhs.m_str) * rhs.length()+1 ); }

protected:
	_CharT m_str[_MaxStorageLen];
	template < class _LhsTraits, class _RhsTraits > friend struct StringCopy;
};

template < class _CharT, size_t _MaxStorageLen >
class StringFixedHeapT
{
public:

	StringFixedHeapT() 
		: m_str( new _CharT[_MaxStorageLen] )
	{ m_str[0] = '\0'; }

	StringFixedHeapT( const StringFixedHeapT& rhs ) 
		: m_str( new _CharT[_MaxStorageLen] )
	{ *this = rhs; }

	~StringFixedHeapT() 
	{ delete[] m_str; }

	const _CharT* c_str() const
	{ return m_str; }

	size_t capacity() const
	{ return _MaxStorageLen; }

	size_t length() const
	{ return strlen(m_str); }

	bool resize( size_t size )
	{
		//TODO: to error, or not to error, to crimp off, or fail etc
		return size <= capacity(); 
	}

	void operator = ( const StringFixedHeapT& rhs )
	{ memcpy_s( m_str, sizeof(*m_str) * capacity(), rhs.m_str, sizeof(*rhs.m_str) * rhs.length()+1 ); }

protected:
	_CharT* m_str;

	template < class _LhsTraits, class _RhsTraits > friend struct StringCopy;
};

#endif