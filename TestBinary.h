#ifndef CIRCLE_H
#define CIRCLE_H

namespace TestBinary {
	//在AVLTree中方便统计节点左右子树的平衡状况
	enum BalanceFactor :int;
	//树节点
	template<typename BinaryEntry>
	struct BinaryNode {
		BinaryEntry data;
		BinaryNode<BinaryEntry> *left;
		BinaryNode<BinaryEntry> *right;
		BinaryNode();
		BinaryNode(const BinaryEntry &item);
		//由于需要通过基类指针调用以下2个派生类函数
		//如果将其声明为纯虚函数，我们将不能直接创建树节点
		virtual void set_balance(BalanceFactor b);
		virtual BalanceFactor get_balance()const;
	};
	//二叉树
	template<typename BinaryEntry>
	class BinaryTree {
	public:
		BinaryTree();
		virtual ~BinaryTree();
		//访问
		bool empty()const;
		//派生类可以不覆盖虚函数
		virtual int height()const;
		int count()const;
		int leaf_count()const;//叶节点的个数
	    //先序遍历
		void preorder_traversal(void(*visit)(BinaryEntry &item));
		//中序遍历
		void inorder_traversal(void(*visit)(BinaryEntry &item));
		//后序遍历
		void postorder_traversal(void(*visit)(BinaryEntry &item));
		//修改
		void clear();
		virtual void insert(const BinaryEntry &item);
		//由于二叉树的插入没有规律，需要遍历整个树的节点寻找
		//需要删除的节点。时间复杂度高
		//方便其他性质的树继承
	protected:
		BinaryNode<BinaryEntry> *root;
		//辅助函数：防止接触到root节点
		void assistent_clear(BinaryNode<BinaryEntry> *sub_root);
		int assistent_leaf_count(BinaryNode<BinaryEntry> *sub_root)const;
		int assistent_count(BinaryNode<BinaryEntry> *sub_root)const;
		void assistent_insert(BinaryNode<BinaryEntry> *&sub_root, const BinaryEntry &item);
		int assistent_height(BinaryNode<BinaryEntry> *sub_root)const;
		//辅助遍历
		void assistent_preorder(BinaryNode<BinaryEntry> *sub_root, void(*visit)(BinaryEntry &item));
		void assistent_inorder(BinaryNode<BinaryEntry> *&sub_root, void(*visit)(BinaryEntry &item));
		void assistent_postorder(BinaryNode<BinaryEntry> *sub_root, void(*visit)(BinaryEntry &item));
	};

	//二叉搜索树：左子树小于等于根节点，右子树大于根节点
	template<typename BinaryEntry>
	class SearchTree :public BinaryTree<BinaryEntry> {
	public:
		//由于SearchTree不含数据成员
		//让编译器定义合成的默认构造和析构函数
		bool tree_search(const BinaryEntry &target)const;
		//不允许插入重复的元素
		virtual void insert(const BinaryEntry &item);
		void remove(const BinaryEntry &item);
	private:
		BinaryNode<BinaryEntry>* search_for_node(BinaryNode<BinaryEntry> *sub_root, const BinaryEntry &target)const;
		void search_and_insert(BinaryNode<BinaryEntry> *&sub_root, const BinaryEntry &item);
		void remove_root(BinaryNode<BinaryEntry> *&sub_root);
		void search_and_remove(BinaryNode<BinaryEntry> *sub_root, const BinaryEntry &target);
	};
	//如果使用height()函数来更新左右子树的高度的时间复杂度更高
	template<typename BinaryEntry>
	struct AVLNode : public BinaryNode<BinaryEntry> {
		//枚举类型无法被默认初始化
		BalanceFactor balance;
		//所以无法使用继承构造函数
		AVLNode();
		AVLNode(const BinaryEntry &item);
		//override用于确认是否覆盖基类的虚函数
		void set_balance(BalanceFactor b)override;
		BalanceFactor get_balance()const override;
	};
	
	//平衡二叉搜索树：在多次插入和删除后保持每个节点的左右子树高度之差不超过1
	template<typename BinaryEntry>
	class AVLTree :public SearchTree<BinaryEntry> {
	public:
		void insert(const BinaryEntry &item)override;
		void remove(const BinaryEntry &item);
		int height()const override;
	private:
		int assistent_height(BinaryNode<BinaryEntry> *sub_root)const;
		//对于需要修改平衡情况的函数，检查指针的引用问题和先后问题
		bool avl_insert(BinaryNode<BinaryEntry> *&sub_root,const BinaryEntry &item);
		void rotate_left(BinaryNode<BinaryEntry> *&sub_root);
		void rotate_right(BinaryNode<BinaryEntry> *&sub_root);
		void insert_right_balance(BinaryNode<BinaryEntry> *&sub_root);
		void insert_left_balance(BinaryNode<BinaryEntry> *&sub_root);
		bool avl_remove(BinaryNode<BinaryEntry> *&sub_root, const BinaryEntry &item);
		bool avl_remove_left(BinaryNode<BinaryEntry> *&sub_root, const BinaryEntry &item);
		bool avl_remove_right(BinaryNode<BinaryEntry> *&sub_root, const BinaryEntry &item);
	};
	
	
}
/*

*/

#endif
#pragma once

