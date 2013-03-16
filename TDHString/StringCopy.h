#ifndef PERCEIVE_STRINGCOPY_H
#define PERCEIVE_STRINGCOPY_H

//-------------------------------------------------------------
// StringCopy
//-------------------------------------------------------------
template < class _LhsTraits, class _RhsTraits >
struct StringCopy
{
	void operator()( _LhsTraits& lhs, const _RhsTraits& rhs ) const;
	void operator()( size_t lhsPos, _LhsTraits& lhs, const _RhsTraits& rhs ) const;
};

template < class _LhsTraits, class _RhsTraits >
void StringCopy<_LhsTraits,_RhsTraits>::operator()( _LhsTraits& lhs, const _RhsTraits& rhs ) const
{ 
	const size_t rhsLength = rhs.length();
	lhs.resize( rhsLength+1 );
	const size_t lhsCapacity = lhs.capacity();
	memcpy_s( lhs.m_str, sizeof(*lhs.m_str) * lhsCapacity, rhs.m_str, sizeof(*rhs.m_str) * rhsLength );
	lhs.m_str[rhsLength] = '\0';//< terminate string
}

template < class _LhsTraits, class _RhsTraits >
void StringCopy<_LhsTraits,_RhsTraits>::operator()( size_t pos, _LhsTraits& lhs, const _RhsTraits& rhs ) const
{ 
	const size_t rhsLength = rhs.length();
	lhs.resize( pos + rhsLength+1 );
	const size_t lhsCapacity = lhs.capacity();
	memcpy_s( lhs.m_str+pos, sizeof(*lhs.m_str) * lhsCapacity, rhs.m_str, sizeof(*rhs.m_str) * rhsLength );
	lhs.m_str[pos+rhsLength] = '\0';//< terminate string
}

template <>
void StringCopy<typename StringLiteralT<char>,typename StringLiteralT<char>>::operator()( typename StringLiteralT<char>& lhs, const typename StringLiteralT<char>& rhs ) const
{ 
	lhs.m_str = rhs.m_str;
	lhs.m_length = rhs.m_length;
}

#endif