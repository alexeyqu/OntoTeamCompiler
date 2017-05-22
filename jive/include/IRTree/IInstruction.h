#pragma once

#include <string>
#include <map>
#include "IRTree/Temp/CLabelList.h"
#include "IRTree/Temp/CTempList.h"
#include "IRTree/Temp/CTempMap.h"

class IInstruction {

protected:
	static const char PLACEHOLDER = '`';
	std::string asmCodeTemplate;

public:
	virtual ~IInstruction() {};
	virtual CTempList* UsedVariables() const = 0;
	virtual CTempList* DefinedVariables() const = 0;
	virtual CLabelList* JumpTargets() const = 0;

	std::string Format( CTempMap* mapping ) const {

		std::map<std::string, std::string> placeholderValues;
		std::string placeholderString( 1, PLACEHOLDER );

		int i = 0;
		CTemp* temp = nullptr;
		i = 0;
		CTempList* list = UsedVariables();
		while ( list ) {
			temp = list->GetHead();
			placeholderValues[ placeholderString + "s" + std::to_string( i ) ] = mapping->Map( temp );
			list = list->GetTail();
			i++;
		}

		i = 0;
		list = DefinedVariables();
		while ( list ) {
			temp = list->GetHead();
			placeholderValues[ placeholderString + "d" + std::to_string( i ) ] = mapping->Map( temp );
			list = list->GetTail();
			i++;
		}
		// Перебираем метки (`j0, `j1 ... )
		i = 0;
		CLabelList* labelList = JumpTargets();
		CLabel* label = nullptr;
		while ( labelList ) {
			label = labelList->GetHead();
			placeholderValues[ placeholderString + "j" + std::to_string( i ) ] = label->Name();
			labelList = labelList->GetTail();
			i++;
		}

		std::string command = asmCodeTemplate;
		for ( auto& item : placeholderValues ) {
			std::string placeholder = item.first;
			std::string value = item.second;
			size_t pos = command.find( placeholder );
			if ( pos != std::string::npos ) {
				command.replace( pos, placeholder.length(), value );
			}
		}

		// Возвращаем сформированную команду
		return command;
	}
};