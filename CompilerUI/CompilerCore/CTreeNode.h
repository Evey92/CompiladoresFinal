#pragma once
#include "CToken.h"

namespace CompilerCore
{
	enum class NODE_TYPE
	{
		RESULT_INT,
		RESULT_FLOAT,
		RESULT_BOOL,
		RESULT_STRING
	};

	class CTreeNode
	{
	private:
		CTreeNode* Lnode;
		CTreeNode* Rnode;
		NODE_TYPE m_nodeType;

	public:
		CTreeNode(){}
		CTreeNode(std::string type){}
		bool Evaluate();
		void SetRightNode(CTreeNode* node);
		void SetLeftNode(CTreeNode* node);
	};
	
	void CTreeNode::SetRightNode(CTreeNode* node)
	{
		Rnode = node;
	}
	void CTreeNode::SetLeftNode(CTreeNode* node)
	{
		Lnode = node;
	}

	bool CTreeNode::Evaluate()
	{
		if ((Lnode->m_nodeType == Rnode->m_nodeType) && Lnode == nullptr)
		{
			return true;
		}
		else if (Lnode->m_nodeType == Rnode->m_nodeType)
		{
			m_nodeType = Lnode->m_nodeType;
			return true;
		}
		else if (Lnode->m_nodeType == NODE_TYPE::RESULT_INT   && Rnode->m_nodeType == NODE_TYPE::RESULT_FLOAT ||
				 Lnode->m_nodeType == NODE_TYPE::RESULT_FLOAT && Rnode->m_nodeType == NODE_TYPE::RESULT_INT ||
				 Lnode->m_nodeType == NODE_TYPE::RESULT_FLOAT && Rnode->m_nodeType == NODE_TYPE::RESULT_FLOAT)

		{
			m_nodeType = NODE_TYPE::RESULT_FLOAT;
			return true;
		}
		return false;

	}
}