#ifndef PERCEIVE_STRINGLITERAL_H
#define PERCEIVE_STRINGLITERAL_H

#include <cassert>

/** Helper to replace static const char* kStr = "foo" with a type that has string comparison support
*/
template < class _CharT >
class StringLiteralT
{
public:
	StringLiteralT() 
		: m_str(0) 
	{}

	StringLiteralT( const _CharT* str ) 
		: m_str(str)
		, m_length(strlen(str))
	{}

	StringLiteralT( const _CharT* str, size_t length ) 
		: m_str(str)
		, m_length(length)
	{}

	const _CharT* c_str() const
	{ return m_str; }

	const _CharT operator[] ( const size_t index ) const
	{ assert( index < capacity() ); return m_str[index]; }

	size_t capacity() const
	{ return 0; }

	size_t length() const
	{ return m_str ? strlen(m_str) : 0; }

	bool reserve( size_t size );
	bool resize( size_t size ); //< Not implemented/supported!
	//{ assert(false); return false; }

private:
	const _CharT* m_str;
	size_t m_length;
	
	template<class _CharT> friend struct StringCopy;
};


#endif