#pragma once
#include "CTreeNode.h"

namespace CompilerCore
{
	class CLogicExpTree
	{
	private:
		CTreeNode* m_root;
	public:
		CLogicExpTree();
		CLogicExpTree(CTreeNode* root)
		{
			m_root = root;
		}
		~CLogicExpTree();
	};

}