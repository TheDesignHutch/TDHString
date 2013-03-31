#ifndef PERCEIVE_STRINGDYNAMIC_H
#define PERCEIVE_STRINGDYNAMIC_H

/** Dynamically allocates memory on the heap. Essentially std::string
*/

template < class _CharT >
class StringDynamicHeapT
{
public:

	StringDynamicHeapT() 
		: m_str(0)
		, m_capacity(0)
		, m_length(0)
	{}

	StringDynamicHeapT( const StringDynamicHeapT& rhs ) 
		: m_str(0)
		, m_capacity( rhs.length()+1 )
		, m_length(0)
	{ 
		m_str = new _CharT[ m_capacity ];
		*this = rhs; 
	}

	~StringDynamicHeapT() 
	{ delete[] m_str; }

	const _CharT* c_str() const
	{ return m_str; }

	_CharT& operator[] ( const size_t index )
	{ assert( index < capacity() ); return m_str[index]; }

	const _CharT operator[] ( const size_t index ) const
	{ assert( index < capacity() ); return m_str[index]; }

	size_t capacity() const
	{ return m_capacity; }

	size_t length() const
	{ return m_length; }

	bool reserve( size_t newLength )
	{
		if ( newLength < capacity() )
			return true;

		size_t oldCapacity = m_capacity;
		m_capacity = newLength+1;

		_CharT* oldStr = m_str;
		m_str = new _CharT[m_capacity];
		if ( !m_str )
			return assert(false), false;
		if ( oldStr )
			memcpy_s( m_str, sizeof(*m_str) * oldCapacity, oldStr, sizeof(*oldStr) * oldCapacity ); 
		return true;
	}

	bool resize( size_t newLength )
	{
		bool ret = reserve(newLength);
		assert(ret);
		m_length = newLength;
		return ret;
	}

	void operator = ( const StringDynamicHeapT& rhs )
	{
		m_length = rhs.m_length;
		resize( m_length );
		memcpy_s( m_str, sizeof(*m_str) * capacity(), rhs.m_str, sizeof(*rhs.m_str) * m_length ); 
		m_str[m_length] = '\0';
	}

private:
	_CharT* m_str;
	size_t m_capacity;
	size_t m_length;

	template<class _CharT> friend struct StringCopy;
};

#if 0
//TODO: implement using StackAlloc
class DynamicStackString
{
};
#endif

#endif