#pragma once
#include <string>
#include <vector>
#include "CToken.h"

using std::string;
using std::vector;

namespace CompilerCore
{
	public class CExpLog
	{
		int m_lineNum;
		string m_funcName;
		string m_statement;
		vector<CToken*> m_infixExp;
		vector<CToken*> m_postfixExp;
		//ExpLogTree* m_tree;
		//NODE_RESULT m_expectedResult;
		string m_symbolToUpdate;
		int m_symbolIndexToUpdate;



	public:
		//Ctor | Dtor
		void buildTree();
		bool validateTree();

		CExpLog();
	};
}
