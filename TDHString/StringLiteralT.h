#ifndef PERCEIVE_STRINGLITERAL_H
#define PERCEIVE_STRINGLITERAL_H


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

	size_t capacity() const
	{ return 0; }

	size_t length() const
	{ return m_str ? strlen(m_str) : 0; }

	bool resize( size_t size ); //< Not implemented/supported!
	//{ assert(false); return false; }

protected:
	const _CharT* m_str;
	size_t m_length;
	
	template < class _LhsTraits, class _RhsTraits > friend struct StringCopy;
};


#endif