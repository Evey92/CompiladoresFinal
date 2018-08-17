#pragma once
using namespace System;
#include <stack>
#include "CToken.h"
#include "LexicoModule.h"
#include "CErrModule.h"
#include "Symbol.h"
#include "CSymbolTable.h"

namespace CompilerCore
{
	public struct SintaxBlob
	{
		int lineNum;
		int dimension;
		std::string symbol;
		std::string varType;
		std::string functionName;
	};

	public class SyntaxStateMachine
	{
		class SyntaxState
		{
			//Esta clase es de donde heredan todas las consiguientes
		public:
			

			SyntaxState();
			SyntaxState();
			virtual void CheckSyntax() {}
		};

	private:
		LexicoModule * m_lex;
		msclr::gcroot<CErrModule^> m_err;

		std::stack<SyntaxState> StateStack;
	public:
		SyntaxState * m_state;
		SyntaxStateMachine(LexicoModule* lexicon, CErrModule^ error);
		~SyntaxStateMachine();

		void Run(LexicoModule* lexicMachine, CErrModule^ errorModule, CSymbolTable* table);
		
	
	};

	SyntaxStateMachine::SyntaxStateMachine(LexicoModule* lexicon, CErrModule^ error)
	{
		m_lex = lexicon;
		m_err = error;
	}
	SyntaxStateMachine::~SyntaxStateMachine()
	{

	}
	void SyntaxStateMachine::Run(LexicoModule* lexicMachine, CErrModule^ errorModule, CSymbolTable* table)
	{
		do
		{
			m_state = m_state->Process(lexicMachine, errorModule, table);
		} while (m_state != nullptr);
	}

}

