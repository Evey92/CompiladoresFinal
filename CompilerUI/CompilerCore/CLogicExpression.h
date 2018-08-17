#pragma once

#include "CToken.h"
#include "CLogicExpTree.h"
#include "CTreeNode.h"

namespace CompilerCore
{
	class CLogicExpression
	{
	private:
		CLogicExpTree m_expTree;
		NODE_TYPE m_expectedResult;
		std::string m_funcName;
		std::string m_statement;
		std::string m_symboltoUpdate;
		int m_lineNumber;
		int m_symbolIndextoUpdate;

		NODE_TYPE ThrowNodeResult(std::string functype);

	public:
		std::vector<CToken> m_vInfixExp;
		std::vector<CToken> m_vPostfixExp;

		CLogicExpression(int lineNum, std::string funcName, std::string statement, NODE_TYPE expectedRes, std::string symbol, int symbolIndex) 
		{
			NODE_TYPE m_expectedResult = expectedRes;
			std::string m_funcName = funcName;
			std::string m_statement = statement;
			std::string m_symboltoUpdate = symbol;
			int m_lineNumber = lineNum;
			int m_symbolIndextoUpdate = symbolIndex;
		}

		~CLogicExpression();
		void SetTree(CLogicExpTree t);
	};

	NODE_TYPE CLogicExpression::ThrowNodeResult(std::string functype)
	{
		if (functype == "boolean")
		{
			return NODE_TYPE::RESULT_BOOL;
		}
		if (functype == "float")
		{
			return NODE_TYPE::RESULT_FLOAT;
		}
		if (functype == "int")
		{
			return NODE_TYPE::RESULT_INT;
		}
	}

	void CLogicExpression::SetTree(CLogicExpTree tree)
	{
		m_expTree = tree;
	}
}