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
		: m_length(0)
	{ assert(_MaxStorageLen); m_str[0] = '\0'; }

	StringFixedT( const StringFixedT& rhs )
	{ *this = rhs; }

	const _CharT* c_str() const
	{ return m_str; }

	_CharT& operator[] ( const size_t index )
	{ assert( index < capacity() ); return m_str[index]; }

	const _CharT operator[] ( const size_t index ) const
	{ assert( index < capacity() ); return m_str[index]; }

	size_t capacity() const
	{ return _MaxStorageLen; }

	size_t length() const
	{ return m_length; }

	bool reserve( size_t newLength )
	{
		bool valid = newLength < capacity();
		assert(valid);
		//TODO: to error, or not to error, to crimp off, or fail etc
		return valid; 
	}

	bool resize( size_t newLength )
	{
		bool valid = newLength < capacity();
		assert(valid);
		m_length = newLength;
		//TODO: to error, or not to error, to crimp off, or fail etc
		return valid; 
	}

	void operator = ( const StringFixedT& rhs )
	{
		m_length = rhs.m_length;
		memcpy_s( m_str, sizeof(*m_str) * capacity(), rhs.m_str, sizeof(*rhs.m_str) * m_length+1 ); 
	}

protected:
	_CharT m_str[_MaxStorageLen];
	size_t m_length;
	template<class _CharT> friend struct StringCopy;
};

template < class _CharT, size_t _MaxStorageLen >
class StringFixedHeapT
{
public:

	StringFixedHeapT() 
		: m_str( new _CharT[_MaxStorageLen] )
		, m_length(0)
	{ m_str[0] = '\0'; }

	StringFixedHeapT( const StringFixedHeapT& rhs ) 
		: m_str( new _CharT[_MaxStorageLen] )
	{ *this = rhs; }

	~StringFixedHeapT() 
	{ delete[] m_str; }

	const _CharT* c_str() const
	{ return m_str; }

	_CharT& operator[] ( const size_t index )
	{ assert( index < capacity() ); return m_str[index]; }

	const _CharT operator[] ( const size_t index ) const
	{ assert( index < capacity() ); return m_str[index]; }

	size_t capacity() const
	{ return _MaxStorageLen; }

	size_t length() const
	{ return m_length; }

	bool reserve( size_t newLength )
	{
		bool valid = newLength < capacity();
		assert(valid);
		//TODO: to error, or not to error, to crimp off, or fail etc
		return valid; 
	}

	bool resize( size_t newLength )
	{
		bool valid = newLength < capacity();
		assert(valid);
		m_length = newLength;
		//TODO: to error, or not to error, to crimp off, or fail etc
		return valid; 
	}

	void operator = ( const StringFixedHeapT& rhs )
	{ 
		m_length = rhs.m_length;
		memcpy_s( m_str, sizeof(*m_str) * capacity(), rhs.m_str, sizeof(*rhs.m_str) * m_length ); 
		m_str[m_length] = '\0';
	}

private:
	_CharT* m_str;
	size_t m_length;

	template<class _CharT> friend struct StringCopy;
};

#endif