#pragma once

#include "CSymbol.h"

template<class Object>
class CSymbolStorage {
public:
	CSymbolStorage<Object>() {};

	void InsertObject( CSymbol* symbol, Object value ) {
		table[symbol] = value;
	}

	typedef typename std::unordered_map<CSymbol*, Object>::const_iterator tableIt;

	tableIt GetBegin() const {
		return table.begin();
	}

	tableIt GetEnd() const {
		return table.end();
	}

	Object GetObject( CSymbol* symbol ) const {
		auto result = table.find( symbol );
		return result != table.end() ? result->second : NULL;
	}

	int Size() const {
		return table.size();
	}

private:
	std::unordered_map<CSymbol*, Object> table;
};