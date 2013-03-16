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
	{}

	StringDynamicHeapT( const StringDynamicHeapT& rhs ) 
		: m_str(0)
		, m_capacity( rhs.length()+1 )
	{ 
		m_str = new _CharT[ m_capacity ];
		*this = rhs; 
	}

	~StringDynamicHeapT() 
	{ delete[] m_str; }

	const _CharT* c_str() const
	{ return m_str; }

	size_t capacity() const
	{ return m_capacity; }

	size_t length() const
	{ return m_str ? strlen(m_str) : 0; }

	bool reserve( size_t size )
	{
		if ( size <= capacity() || !size )
			return true;
		
		//TODO: to error, or not to error, to crimp off, or fail etc
		return resize(size); 
	}

	bool resize( size_t newCapacity )
	{
		if ( newCapacity <= capacity() || !newCapacity )
			return true;

		_CharT* oldStr = m_str;
		m_str = new _CharT[ newCapacity ];
		if ( !m_str )
			return assert(false), false;
		if ( oldStr )
			memcpy_s( m_str, sizeof(*m_str) * capacity(), oldStr, sizeof(*oldStr) * strlen(oldStr)+1 ); 
		m_capacity = newCapacity;
		return true;
	}

	void operator = ( const StringDynamicHeapT& rhs )
	{
		const size_t rhsLength = rhs.length()+1;
		resize( rhsLength );
		memcpy_s( m_str, sizeof(*m_str) * capacity(), rhs.m_str, sizeof(*rhs.m_str) * rhsLength ); 
	}

protected:
	_CharT* m_str;
	size_t m_capacity;

	template < class _LhsTraits, class _RhsTraits > friend struct StringCopy;
};

#if 0
//TODO: implement using StackAlloc
class DynamicStackString
{
};
#endif

#endif