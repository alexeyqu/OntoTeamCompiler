#pragma once

#include "ST/CSymbol.h"

class CLabel
{
public:
	CLabel();
	explicit CLabel( const CSymbol* symbol );
	const std::string& Name() const;
	bool operator ==( const CLabel& other ) const;
	bool operator != ( const CLabel& other ) const;

private:
	std::string name;

	static int uniqueId;
	static const std::string prefix;
};

namespace std
{
	template<>
	struct hash <CLabel> {
		size_t operator()( const CLabel& label ) const
		{
			return hash<string>()( label.Name() );
		}
	};
}