#ifndef PERCEIVE_STRINGCOPY_H
#define PERCEIVE_STRINGCOPY_H

//-------------------------------------------------------------
// StringCopy
//-------------------------------------------------------------
template< class _CharT>
struct StringCopy
{
	template < class _LhsString, class _RhsString >
	void operator()( _LhsString& lhs, const _RhsString& rhs ) const;
	
	void operator()( StringLiteralT<_CharT>& lhs, const StringLiteralT<_CharT>& rhs ) const;

	template < class _LhsString, class _RhsString >
	void operator()( size_t lhsPos, _LhsString& lhs, const _RhsString& rhs ) const;
};

template< class _CharT>
template < class _LhsString, class _RhsString >
void StringCopy<_CharT>::operator()( _LhsString& lhs, const _RhsString& rhs ) const
{ 
	const size_t rhsLength = rhs.length();
	lhs.resize( rhsLength );
	const size_t lhsCapacity = lhs.capacity();
	memcpy_s( lhs.m_str, sizeof(*lhs.m_str) * lhsCapacity, rhs.c_str(), sizeof(*rhs.c_str()) * rhsLength );
	lhs.m_str[rhsLength] = '\0';//< terminate string
}

/*template< class _CharT>
template < class _LhsString, class _RhsString >
void StringCopy<_CharT>::operator()( typename StringT<_CharT,_LhsData>& lhs, const _RhsString& rhs ) const;
{ 
}*/

template< class _CharT>
template < class _LhsString, class _RhsString >
void StringCopy<_CharT>::operator()( size_t pos, _LhsString& lhs, const _RhsString& rhs ) const
{ 
	const size_t rhsLength = rhs.length();
	lhs.resize( pos + rhsLength );
	const size_t lhsCapacity = lhs.capacity();
	memcpy_s( lhs.m_str+pos, sizeof(*lhs.m_str) * lhsCapacity, rhs.m_str, sizeof(*rhs.m_str) * rhsLength );
	lhs.m_str[pos+rhsLength] = '\0';//< terminate string
}

template< class _CharT>
void StringCopy<_CharT>::operator()( StringLiteralT<_CharT>& lhs, const StringLiteralT<_CharT>& rhs ) const
{ 
	lhs.m_str = rhs.m_str;
	lhs.m_length = rhs.m_length;
}

#endif