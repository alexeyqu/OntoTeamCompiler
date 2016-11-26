#include "CSymbolTable.h"
#include <cstdio>

bool CSymbolTable::Add( CClassSymbol* symbol ) {
	if( table.find( symbol->name ) != table.end() ) {
		return false;
	}
	table.insert( std::make_pair( symbol->name, symbol ) );
	return true;
}
ISymbol* CSymbolTable::FindMethod( std::string& className, std::string& mehodName ) {
	auto classIt = table.find( className );
	if( classIt == table.end() ) {
		return nullptr;
	} else {
		auto methodIt = classIt->second->methods.find( mehodName );
		if( methodIt == classIt->second->methods.end() ) {
			return nullptr;
		} else {
			return methodIt->second;
		}
	}
}

ISymbol* CSymbolTable::FindVariable( std::string& className, std::string& mehodName, std::string& varName ) {
	auto classIt = table.find( className );
	if( classIt == table.end() ) {
		return nullptr;
	} else {
		auto methodIt = classIt->second->methods.find( mehodName );
		if( methodIt == classIt->second->methods.end() ) {
			return nullptr;
		} else {
			auto argIt = methodIt->second->arguments.find( varName );
			if( argIt == methodIt->second->arguments.end() ) {
				auto varIt = methodIt->second->variables.find( varName );
				if( varIt == methodIt->second->variables.end() ) {
					return nullptr;
				} else {
					return varIt->second;
				}
			} else {
				return argIt->second;
			}
		}
	}
}
