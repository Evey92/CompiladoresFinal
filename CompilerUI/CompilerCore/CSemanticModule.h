#pragma once
#include "LexicoModule.h"
#include "CErrModule.h"
#include "CToken.h"
#include "CSyntaxModule.h"
#include "CSymbolTable.h"
#include "CLogicExpression.h"
#include<stack>

using namespace System;

namespace CompilerCore
{
	class CSemanticModule
	{
	private:
		LexicoModule * m_lexicon;
		CSymbolTable* m_symbolsTable;
		//CErrModule^ m_error;
		std::vector<CLogicExpression> m_expLogVector;
		

	public:

		CSemanticModule(LexicoModule* lexicon, CErrModule^ error);
		~CSemanticModule();
		void CreateExpressionTrees();
		std::vector<CToken> InfixToPostfix(std::vector<CToken> infixVector);
		void AddLogicalExp(std::vector<CToken> exp, int lineNum, std::string funcName, std::string statement, NODE_TYPE expectedRes, std::string symbol, int symbolIndex);
		bool IsOperand(const CToken token);
		bool IsOperator(const CToken token);
	
	};

	void CSemanticModule::CreateExpressionTrees() 
	{
		for (CLogicExpression currentExpLog : m_expLogVector)
		{
			std::stack<CTreeNode> tree;

			for (int i = 0; i < currentExpLog.m_vPostfixExp.size(); i++)
			{
				if (IsOperand(currentExpLog.m_vPostfixExp[i]))
				{
					CTreeNode newNode(currentExpLog.m_vPostfixExp[i].GetType());
					tree.push(newNode);
				}
				else if (IsOperator(currentExpLog.m_vInfixExp[i]))
				{
					CTreeNode newNode(currentExpLog.m_vPostfixExp[i].GetType());
					newNode.SetRightNode(&tree.top());
					tree.pop();
					newNode.SetLeftNode(&tree.top());

					if (newNode.Evaluate())
					{
						tree.pop();
						tree.push(newNode);
					}
				}
			}
			CLogicExpTree logExpTree(&tree.top());
			while (!tree.empty())
			{
				tree.pop();
			}
			currentExpLog.SetTree(logExpTree);
			m_expLogVector.push_back(currentExpLog);
		}
	}

	void CSemanticModule::AddLogicalExp(std::vector<CToken> exp, int lineNum, std::string funcName, std::string statement, NODE_TYPE expectedRes, std::string symbol, int symbolIndex)
	{
		InfixToPostfix(exp);
		CLogicExpression logicExp(lineNum,funcName, statement,expectedRes,symbol,symbolIndex);
		m_expLogVector.push_back(logicExp);
		
	}

	std::vector<CToken> CSemanticModule::InfixToPostfix(std::vector<CToken> infixVector)
	{
		stack<CToken> tokenStack;

		std::vector<CToken> postFixVector;
		for (CToken infixToken : infixVector)
		{
			if (infixToken.GetLex() ==  " " || infixToken.GetLex() == ",") continue;

			else if (IsOperator(infixToken))
			{
				while (!tokenStack.empty() && tokenStack.top().GetLex() != "(" && HasMoreWeight(tokenStack.top(), infixToken))
				{
					postFixVector.push_back(tokenStack.top());
					tokenStack.pop();
				}
				tokenStack.push(infixToken);
			}
			else if (IsOperand(infixToken))
			{
				postFixVector.push_back(infixToken);
			}
			else if (infixToken.GetLex() == "(")
			{
				tokenStack.push(infixToken);
			}
			else if (infixToken.GetLex() == ")")
			{
				while (!tokenStack.empty() && tokenStack.top().GetLex() != "(") {
					postFixVector.push_back(tokenStack.top());
					tokenStack.pop();
				}
				tokenStack.pop();
			}
		}
		
		while (!tokenStack.empty()) {
			postFixVector.push_back(tokenStack.top());
			tokenStack.pop();
		}

		return postFixVector;

	}

	bool CSemanticModule::IsOperand(const CToken token)
	{
		if (token.GetType() == "ID" ||token.GetType() == "INT" ||token.GetType() == "FLOAT")
		{
			return true;
		}
		 return false;
	}

	bool CSemanticModule::IsOperator(const CToken token)
	{
		if (token.GetLex() == "+" || token.GetLex() == "-" || token.GetLex() == "*" || token.GetLex() == "/" || token.GetLex() == "^" || token.GetLex() == ">" || token.GetLex() == "<")
		{
			return true;
		}
		return false;
	}

	int HasMoreWeight(CToken token1, CToken token2)
	{
		int operator1Weight = GetOperatorWeight(token1);
		int operator2Weight = GetOperatorWeight(token2);

		if (operator1Weight == operator2Weight)
		{
			if (IsRightAssociative(token1))
				return false;
			
			else return true;
		}
		return operator1Weight > operator2Weight ? true : false;
	}
	
	int GetOperatorWeight(CToken operatorToken)
	{
		int weight = -1;
		if (operatorToken.GetLex() == ">" || operatorToken.GetLex() == "<")
		{
			weight = 1;
		}
		if (operatorToken.GetLex() == "+" || operatorToken.GetLex() == "-")
		{
			weight = 2;
		}
		if (operatorToken.GetLex() == "*" || operatorToken.GetLex() == "/")
		{
			weight = 3;
		}
		if (operatorToken.GetLex() == "^")
		{
			weight = 4;
		}
		return weight;
	}

	int IsRightAssociative(CToken operatorToken)
	{
		if (operatorToken.GetLex() == "^") 
			return true;

		return false;
	}

}
