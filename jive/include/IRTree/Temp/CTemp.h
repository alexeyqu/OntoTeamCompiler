#pragma once

#include "ST/CSymbol.h"

class CTemp
{
public:
	CTemp();
	explicit CTemp( const CSymbol* symbol );
	const std::string& Name() const;
	bool operator==( const CTemp& other ) const;
	bool operator!=( const CTemp& other ) const;

private:
	std::string name;

	static int uniqueId;
	static const std::string prefix;
	static const std::string separator;
};

namespace std
{
	template<>
	struct hash <CTemp>
	{
		size_t operator()( const CTemp& temp ) const {
			return hash<string>()( temp.Name() );
		}
	};
}