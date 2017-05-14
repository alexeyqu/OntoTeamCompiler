#pragma once

#include <string>
#include <unordered_map>

class CSymbol {
public:
	static CSymbol* GetSymbol( const std::string& key );
	const std::string& GetString() const;


private:
	CSymbol( const std::string& str ) : stringKey( str ) {};

	const std::string stringKey;
	static std::unordered_map<std::string, CSymbol*> stringTable;		
};