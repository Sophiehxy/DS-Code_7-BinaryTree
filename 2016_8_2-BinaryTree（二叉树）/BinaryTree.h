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
	//�ݹ�ʵ��ǰ�����򡢺�������
	//eg:              1
	//              /     \
	//             2       5
	//           /  \     /  
	//          3    4   6    
	//
	//ǰ�������1 2 3 4 5 6
	//���������3 2 4 1 6 5
	//����������6 5 4 3 2 1
	
	//ǰ�������
	void PreOrder()
	{
		_PreOrder(_root);
		cout << endl;
	}

	//�������
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
	//�ǵݹ�ʵ��ǰ�����򡢺�������

	//ǰ��������ǵݹ飩
	//˼·������ջ��
	//      1.�����ڵ㲻Ϊ�գ�ѹջ
	//		2.��ջ��Ϊ�գ�whileѭ��
	//				1�����ջ�����ݣ�pop
	//				2������������Ϊ�գ�ѹ��������
	//			    3������������Ϊ�գ�ѹ��������
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
			
			//stack�ĺ���ȳ����ԣ�Ӧ��push����������push������������ʵ�������ȸ�������ҵ�˳��
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


	//����������ǵݹ飩
	//˼·��1.�����ж�cur��ջs�Ƿ�Ϊ��
	//		2.��cur��Ϊ�գ�whileѭ������ջ
	//		3.��s��Ϊ��
	//		4.��cur����ջ��Ԫ�ص�_right,��ջ
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

	//�����������ǵݹ飩
	//˼·��1.�����ж�cur��ջs�Ƿ�Ϊ��
	//		2.��cur��Ϊ�գ�whileѭ������ջ
	//		3.��ջs��Ϊ��
	//			1)�ж�ջ��Ԫ��top���������Ƿ�Ϊ�գ���top�Ƿ������һ�η��ʽڵ�prev
	//			2)��������һ��������ʾ������Ϊ�գ������Ѿ����ʹ�������������prev=top����ջ
	//			3)���������������㣬���ʾ��������δ���ʣ��������������
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
				
				//��һ��������top->_right==NULL����Ϊ���ȴ�ӡ������������ӡ���ڵ�
				//�ڶ���������top->_right==prev����Ϊ�˷�ֹ�ظ���ӡ�����������û�и�����������С�������ɻ�·��һֱѭ����ӡ
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