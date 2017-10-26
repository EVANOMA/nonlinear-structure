#ifndef CIRCLE_H
#define CIRCLE_H

namespace TestBinary {
	//在AVL_Tree中方便统计节点左右子树的平衡状况
	//比较与height()函数的优劣？
	enum Balance_factor :int;
	//树节点
	template<typename Binary_entry>
	struct Binary_Node {
		Binary_entry data;
		Binary_Node<Binary_entry> *left;
		Binary_Node<Binary_entry> *right;
		Binary_Node();
		Binary_Node(const Binary_entry &item);
		//由于需要通过基类指针调用以下2个派生类函数
		virtual void set_balance(Balance_factor b);
		virtual Balance_factor get_balance()const;
	};
	//二叉树
	template<typename Binary_entry>
	class Binary_Tree {
	public:
		Binary_Tree();
		~Binary_Tree();
		//访问
		bool empty()const;
		//派生类可以不覆盖虚函数
		virtual int height()const;
		int count()const;
		int leaf_count()const;//叶节点的个数
	    //先序遍历
		void preorder_traversal(void(*visit)(Binary_entry &item));
		//中序遍历
		void inorder_traversal(void(*visit)(Binary_entry &item));
		//后序遍历
		void postorder_traversal(void(*visit)(Binary_entry &item));
		//修改
		void clear();
		void insert(const Binary_entry &item);
		//方便其他性质的树继承
	protected:
		Binary_Node<Binary_entry> *root;
		//辅助函数：防止接触到root节点
		void assistent_clear(Binary_Node<Binary_entry> *sub_root);
		int assistent_leaf_count(Binary_Node<Binary_entry> *sub_root)const;
		int assistent_count(Binary_Node<Binary_entry> *sub_root)const;
		void assistent_insert(Binary_Node<Binary_entry> *&sub_root, const Binary_entry &item);
		int assistent_height(Binary_Node<Binary_entry> *sub_root)const;
		//辅助遍历
		void assistent_preorder(Binary_Node<Binary_entry> *sub_root, void(*visit)(Binary_entry &item));
		void assistent_inorder(Binary_Node<Binary_entry> *&sub_root, void(*visit)(Binary_entry &item));
		void assistent_postorder(Binary_Node<Binary_entry> *sub_root, void(*visit)(Binary_entry &item));
	};
	enum Error_code :int;

	//二叉搜索树：左子树小于等于根节点，右子树大于根节点
	template<typename Binary_entry>
	class Search_Tree :public Binary_Tree<Binary_entry> {
	public:
		Error_code tree_search(const Binary_entry &target)const;
		//故意遮掩基类同名函数？void
		virtual Error_code insert(const Binary_entry &item);
		Error_code remove(const Binary_entry &item);
	private:
		Binary_Node<Binary_entry>* search_for_node(Binary_Node<Binary_entry> *sub_root, const Binary_entry &target)const;
		Error_code search_and_insert(Binary_Node<Binary_entry> *&sub_root, const Binary_entry &item);
		Error_code remove_root(Binary_Node<Binary_entry> *&sub_root);
		Error_code search_and_remove(Binary_Node<Binary_entry> *sub_root, const Binary_entry &target);
	};
	//如果使用height()函数来更新左右子树的高度的时间复杂度更高
	template<typename Binary_entry>
	struct AVL_Node : public Binary_Node<Binary_entry> {
		//枚举类型无法被默认初始化
		Balance_factor balance;
		//所以无法使用继承构造函数
		AVL_Node();
		AVL_Node(const Binary_entry &item);
		//override用于确认是否覆盖基类的虚函数
		void set_balance(Balance_factor b)override;
		Balance_factor get_balance()const override;
	};
	
	//平衡二叉搜索树：在多次插入和删除后保持每个节点的左右子树高度之差不超过1
	template<typename Binary_entry>
	class AVL_Tree :public Search_Tree<Binary_entry> {
	public:
		Error_code insert(const Binary_entry &item)override;
		Error_code remove(const Binary_entry &item);
		int height()const override;
	private:
		int assistent_height(Binary_Node<Binary_entry> *sub_root)const;
		//对于需要修改平衡情况的函数，检查指针的引用问题和先后问题
		Error_code avl_insert(Binary_Node<Binary_entry> *&sub_root,const Binary_entry &item,bool &taller);
		void rotate_left(Binary_Node<Binary_entry> *&sub_root);
		void rotate_right(Binary_Node<Binary_entry> *&sub_root);
		void right_balance(Binary_Node<Binary_entry> *&sub_root);
		void left_balance(Binary_Node<Binary_entry> *&sub_root);
		Error_code avl_remove(Binary_Node<Binary_entry> *&sub_root, const Binary_entry &item, bool &shorter);
		//考虑是否可以取消使用Error_code？
		Error_code avl_remove_left(Binary_Node<Binary_entry> *&sub_root, const Binary_entry &item, bool &shorter);
		Error_code avl_remove_right(Binary_Node<Binary_entry> *&sub_root, const Binary_entry &item, bool &shorter);
	};
	
	
}
/*

*/

#endif
#pragma once

