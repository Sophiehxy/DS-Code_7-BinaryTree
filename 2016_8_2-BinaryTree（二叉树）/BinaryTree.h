#pragma once
#include<stack>
template<class T>
struct BinaryTreeNode
{
	T _data;
	BinaryTreeNode<T>* _left;
	BinaryTreeNode<T>* _right;

	BinaryTreeNode(T data)
		:_data(data)
		, _left(NULL)
		, _right(NULL)
	{}
};

template<class T>
class BinaryTree
{
public:
	BinaryTree()
		:_root(NULL)
	{}

	BinaryTree(const T* a, size_t size)
	{
		int index = 0;
		_root=_CreateTree(a,size,index);
	}
	~BinaryTree()
	{}

protected:

	BinaryTreeNode<T>* _CreateTree(const T* a, size_t size,int& index)
	{
		BinaryTreeNode<T>* root = NULL;
		if (index < size&&a[index] != '#')
		{
			root = new BinaryTreeNode<T>(a[index]);
			root->_left = _CreateTree(a, size, ++index);
			root->_right = _CreateTree(a, size, ++index);
		}
		return root;
	}

public:
	//递归实现前序、中序、后续遍历
	//eg:              1
	//              /     \
	//             2       5
	//           /  \     /  
	//          3    4   6    
	//
	//前序遍历：1 2 3 4 5 6
	//中序遍历：3 2 4 1 6 5
	//后续遍历：6 5 4 3 2 1
	
	//前序遍历：
	void PreOrder()
	{
		_PreOrder(_root);
		cout << endl;
	}

	//中序遍历
	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}

	void PostOrder()
	{
		_PostOrder(_root);
		cout << endl;
	}

protected:
	void _PreOrder(BinaryTreeNode<T>* root)
	{
		if (root == NULL)
		{
			return;
		}
		cout << root->_data << " ";
		_PreOrder(root->_left);
		_PreOrder(root->_right);
	}

	void _InOrder(BinaryTreeNode<T>* root)
	{
		if (root == NULL)
		{
			return;
		}
		
		_InOrder(root->_left);
		cout << root->_data << " ";
		_InOrder(root->_right);
	}

	void _PostOrder(BinaryTreeNode<T>* root)
	{
		if (root == NULL)
		{
			return;
		}
		_PostOrder(root->_left);
		_PostOrder(root->_right);
		cout << root->_data << " ";
	}

public:
	//非递归实现前序、中序、后续遍历

	//前序遍历（非递归）
	//思路：借助栈，
	//      1.当根节点不为空，压栈
	//		2.当栈不为空，while循环
	//				1）输出栈顶数据，pop
	//				2）若右子树不为空，压入右子树
	//			    3）若左子树不为空，压入左子树
	void PreOrder_NonR()
	{
		stack<BinaryTreeNode<T>*> s;
		if (_root)
		{
			s.push(_root);
		}
		while (!s.empty())
		{
			BinaryTreeNode<T>* top = s.top();
			cout << top->_data << " ";
			s.pop();
			
			//stack的后进先出特性，应先push右子树，再push左子树，才能实现最后的先根再左后右的顺序
			if (top->_right)
			{
				s.push(top->_right);
			}
			if (top->_left)
			{
				s.push(top->_left);
			}
		}
		cout << endl;
	}


	//中序遍历（非递归）
	//思路：1.首先判断cur或栈s是否为空
	//		2.当cur不为空，while循环，入栈
	//		3.当s不为空
	//		4.让cur等于栈顶元素的_right,出栈
	void InOrder_NonR()
	{
		stack<BinaryTreeNode<T>*> s;
		BinaryTreeNode<T>* cur = _root;
		while (cur || !s.empty())
		{
			while (cur)
			{
				s.push(cur);
				cur = cur->_left;
			}
			if (!s.empty())
			{
				BinaryTreeNode<T>* top = s.top();
				cout << top->_data << " ";
				cur = top->_right;
				s.pop();
			}
		}
		cout << endl;
	}

	//后续遍历（非递归）
	//思路：1.首先判断cur或栈s是否为空
	//		2.当cur不为空，while循环，入栈
	//		3.当栈s不为空
	//			1)判断栈顶元素top的右子树是否为空，或top是否等于上一次访问节点prev
	//			2)若满足任一条件，表示右子树为空，或是已经访问过右子树，则令prev=top；出栈
	//			3)若两条件均不满足，则表示右子树还未访问，则访问其右子树
	void PostOrder_NonR()
	{
		stack<BinaryTreeNode<T>*> s;
		BinaryTreeNode<T>* cur = _root;
		BinaryTreeNode<T>* prev = NULL;
		while (cur || !s.empty())
		{
			while (cur)
			{
				s.push(cur);
				cur = cur->_left;
			}
			if (!s.empty())
			{
				BinaryTreeNode<T>* top = s.top();
				
				//第一个条件：top->_right==NULL；是为了先打印右子树，最后打印根节点
				//第二个条件：top->_right==prev；是为了防止重复打印右子树，如果没有该条件，则最小子树构成环路，一直循环打印
				if (top->_right==NULL ||top->_right==prev)
				{
					cout << top->_data << " ";
					prev = top;
					s.pop();
				}
				else
				{
					cur = top->_right;
				}
				

			}
		}
		cout << endl;
	}

private:
	BinaryTreeNode<T>* _root;

};

void Test()
{
	int array[10] = { 1, 2, 3, '#', '#', 4, '#', '#', 5, 6 }; 
	BinaryTree<int> tree((int*)array, 10);
	tree.PreOrder();
	tree.InOrder();
	tree.PostOrder();

	tree.PreOrder_NonR();
	tree.InOrder_NonR(); 
	tree.PostOrder_NonR();
}