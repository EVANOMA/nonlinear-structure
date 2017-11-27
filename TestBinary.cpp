#include<iostream>
using namespace std;

#include "TestBinary.h"
namespace TestBinary {

	template<typename BinaryEntry>
	BinaryNode<BinaryEntry>::BinaryNode() :
		left(nullptr), right(nullptr)
	{}
	template<typename BinaryEntry>
	BinaryNode<BinaryEntry>::BinaryNode(const BinaryEntry &item) :
		data(item), left(nullptr), right(nullptr)
	{}
	template<typename BinaryEntry>
	void BinaryNode<BinaryEntry>::set_balance(BalanceFactor b)
	{}
	template<typename BinaryEntry>
	BalanceFactor BinaryNode<BinaryEntry>::get_balance()const
	{
		return equal_height;
	}
	template<typename BinaryEntry>
	BinaryTree<BinaryEntry>::BinaryTree() :
		root(nullptr)
	{}
	template<typename BinaryEntry>
	BinaryTree<BinaryEntry>::~BinaryTree()
	{
		clear();
	}
	template<typename BinaryEntry>
	bool BinaryTree<BinaryEntry>::empty()const
	{
		return root == nullptr;
	}
	template<typename BinaryEntry>
	int BinaryTree<BinaryEntry>::assistent_height(BinaryNode<BinaryEntry> *sub_root)const
	{
		if (sub_root == nullptr) return 0;
		int h1 = assistent_height(sub_root->left);
		int h2 = assistent_height(sub_root->right);
		if (h1 > h2)  return 1 + h1;
		else       return 1 + h2;
	}
	template<typename BinaryEntry>
	int BinaryTree<BinaryEntry>::height()const
	{
		return assistent_height(root);
	}
	template<typename BinaryEntry>
	int BinaryTree<BinaryEntry>::assistent_count(BinaryNode<BinaryEntry> *sub_root)const
	{
		if (sub_root == nullptr) return 0;
		return 1 + assistent_count(sub_root->left) + assistent_count(sub_root->right);
	}
	template<typename BinaryEntry>
	int BinaryTree<BinaryEntry>::count()const
	{
		return assistent_count(root);
	}
	template<typename BinaryEntry>
	void BinaryTree<BinaryEntry>::assistent_insert(BinaryNode<BinaryEntry> *&sub_root,
		const BinaryEntry &item)
	{
		if (sub_root == nullptr) {
			//由于new成功后会返回指针，如果没有使用引用则root不会改变
			try {
				sub_root = new BinaryNode<BinaryEntry>(item);
				//bad_alloc只能使用默认初始化
				if (sub_root == nullptr) throw bad_alloc();
				//throw语句的作用类似于return的作用
				//编译器将执行完catch语句后退出该函数
			}
			catch (bad_alloc err) {
				cout << err.what() << endl;
			}
		}
		//让二叉树保持平衡
		//由于该递归函数没有使用return，所以要用else，否则会产生多次递归
		else if (assistent_height(sub_root->right) < assistent_height(sub_root->left))
			assistent_insert(sub_root->right, item);
		else
			//默认放在左边
			assistent_insert(sub_root->left, item);
	}
	template<typename BinaryEntry>
	void BinaryTree<BinaryEntry>::insert(const BinaryEntry &item)
	{
		assistent_insert(root, item);
	}
	template<typename BinaryEntry>
	int BinaryTree<BinaryEntry>::assistent_leaf_count(BinaryNode<BinaryEntry> *sub_root)const
	{
		if (sub_root == nullptr) return 0;
		if (sub_root->left == nullptr&&sub_root->right == nullptr)
			return 1;
		return assistent_leaf_count(sub_root->left) + assistent_leaf_count(sub_root->right);
	}
	template<typename BinaryEntry>
	int BinaryTree<BinaryEntry>::leaf_count()const
	{
		return assistent_leaf_count(root);
	}
	template<typename BinaryEntry>
	void BinaryTree<BinaryEntry>::assistent_clear(BinaryNode<BinaryEntry> *sub_root)
	{
		if (sub_root == nullptr)return;
		assistent_clear(sub_root->left);
		assistent_clear(sub_root->right);
		delete sub_root;
		//指针被delete后不会为空
		sub_root = nullptr;
	}
	template<typename BinaryEntry>
	void BinaryTree<BinaryEntry>::clear()
	{
		assistent_clear(root);
	}
	//先序遍历
	template<typename BinaryEntry>
	void BinaryTree<BinaryEntry>::preorder_traversal(void(*visit)(BinaryEntry &item))
	{
		assistent_preorder(root, visit);
	}
	template<typename BinaryEntry>
	void BinaryTree<BinaryEntry>::assistent_preorder(BinaryNode<BinaryEntry> *sub_root,
		void(*visit)(BinaryEntry &item))
	{
		if (sub_root != nullptr) {
			(*visit)(sub_root->data);
			assistent_preorder(sub_root->left, visit);
			assistent_preorder(sub_root->right, visit);
		}
	}
	//中序遍历
	template<typename BinaryEntry>
	void BinaryTree<BinaryEntry>::inorder_traversal(void(*visit)(BinaryEntry &item))
	{
		assistent_inorder(root, visit);
	}
	template<typename BinaryEntry>
	void BinaryTree<BinaryEntry>::assistent_inorder(BinaryNode<BinaryEntry> *&sub_root,
		void(*visit)(BinaryEntry &item))
	{
		if (sub_root != nullptr) {
			//在递归版本中各个节点的值不会改变
			assistent_inorder(sub_root->left, visit);
			(*visit)(sub_root->data);
			assistent_inorder(sub_root->right, visit);
		}
	}
	//后序遍历
	template<typename BinaryEntry>
	void BinaryTree<BinaryEntry>::postorder_traversal(void(*visit)(BinaryEntry &item))
	{
		assistent_postorder(root, visit);
	}
	template<typename BinaryEntry>
	void BinaryTree<BinaryEntry>::assistent_postorder(BinaryNode<BinaryEntry> *sub_root,
		void(*visit)(BinaryEntry &item))
	{
		if (sub_root != nullptr) {
			assistent_postorder(sub_root->left, visit);
			assistent_postorder(sub_root->right, visit);
			(*visit)(sub_root->data);
		}
	}
	template<typename BinaryEntry>
	BinaryNode<BinaryEntry>* SearchTree<BinaryEntry>::search_for_node(BinaryNode<BinaryEntry> *sub_root, const BinaryEntry &target)const
	{
		while (sub_root != nullptr && sub_root->data != target)
			if (sub_root->data < target)
				//在迭代版本中会改变root的值，所以不能使用引用
				sub_root = sub_root->right;
			else sub_root = sub_root->left;
			return sub_root;
	}
	template<typename BinaryEntry>
	bool SearchTree<BinaryEntry>::tree_search
	(const BinaryEntry &target)const
	{
		auto found = search_for_node(root, target);
		if (found == nullptr)
			return false;
		else  return true;
	}
	template<typename BinaryEntry>
	void SearchTree<BinaryEntry>::search_and_insert
	(BinaryNode<BinaryEntry> *&sub_root, const BinaryEntry &item)
	{
		if (sub_root == nullptr) {
			//由于new成功后会返回指针，如果没有使用引用则root不会改变
			try {
				sub_root = new BinaryNode<BinaryEntry>(item);
				//bad_alloc只能使用默认初始化
				if (sub_root == nullptr) throw bad_alloc();
				//throw语句的作用类似于return的作用
				//编译器将执行完catch语句后退出该函数
			}
			catch (bad_alloc err) {
				cout << err.what() << endl;
			}
		}
		else if (item < sub_root->data)
			//由于必须使用引用，所以必须使用递归版本
			return search_and_insert(sub_root->left, item);
		else if (item > sub_root->data)
			return search_and_insert(sub_root->right, item);
		else {
			cout << "Error:" << __FILE__ << ": in function "
				<< __func__ << " at line " << __LINE__ << endl;
			cout << "there has the same vector" << endl;
		}
	}
	template<typename BinaryEntry>
	void SearchTree<BinaryEntry>::insert
	(const BinaryEntry &item)
	{
		return search_and_insert(root, item);
	}
	template<typename BinaryEntry>
	void SearchTree<BinaryEntry>::remove_root(BinaryNode<BinaryEntry> *&sub_root)
	{
		if (sub_root == nullptr) {
			cout << "Error:" << __FILE__ << ": in function "
				<< __func__ << " at line " << __LINE__ << endl;
			cout << "SearchTree is empty" << endl;
		}
		auto to_delete = sub_root;
		//被删除的节点只有1个子树时，直接向上移动
		if (sub_root->left == nullptr)
			//由于需要改变指针的地址，所以必须使用引用
			sub_root = sub_root->right;
		else if (sub_root->right == nullptr)
			sub_root = sub_root->left;
		else {
			auto parent = sub_root;
			to_delete = sub_root->left;
			//寻找离小于被删除节点最近的节点进行替换
			//位于左子树的最右边
			while (to_delete->right != nullptr) {
				parent = to_delete;
				to_delete = to_delete->right;
			}
			sub_root->data = to_delete->data;
			//由于被删除节点的左子节点是最近的节点
			//所以需要向上移动左子树
			if (parent == sub_root)
				sub_root->left = to_delete->left;
			else
				//将被删除节点的右子树作为新的右子树
				//无需移动左子树
				sub_root->right = to_delete->left;
		}
		delete  to_delete;
	}
	template<typename BinaryEntry>
	void SearchTree<BinaryEntry>::search_and_remove
	(BinaryNode<BinaryEntry> *sub_root, const BinaryEntry &target)
	{
		while (sub_root != nullptr && sub_root->data != target)
			if (sub_root->data < target)
				//在迭代版本中会改变root的值，所以不能使用引用
				sub_root = sub_root->right;
			else sub_root = sub_root->left;
			return remove_root(sub_root);

	}
	template<typename BinaryEntry>
	void SearchTree<BinaryEntry>::remove(const BinaryEntry &item)
	{
		return search_and_remove(root, item);
	}
	enum BalanceFactor {
		//该节点的高度不变
		equal_height,
		//左右子树的高度差为1
		left_higher,
		right_higher
	};
	template<typename BinaryEntry>
	AVLNode<BinaryEntry>::AVLNode() :
		BinaryNode(), balance(equal_height)
	{}
	template<typename BinaryEntry>
	AVLNode<BinaryEntry>::AVLNode(const BinaryEntry &item) :
		BinaryNode(item), balance(equal_height)
	{}
	template<typename BinaryEntry>
	void AVLNode<BinaryEntry>::set_balance(BalanceFactor b)
	{
		balance = b;
	}
	template<typename BinaryEntry>
	BalanceFactor AVLNode<BinaryEntry>::get_balance()const
	{
		return balance;
	}
	//高度为左右子树的节点个数的最大值
	//不包括根节点
	template<typename BinaryEntry>
	int AVLTree<BinaryEntry>::assistent_height
	(BinaryNode<BinaryEntry> *sub_root)const
	{
		int height = 0;
		while (sub_root != nullptr) {
			++height;
			if (sub_root->get_balance() == right_higher)
				sub_root = sub_root->right;
			else
				sub_root = sub_root->left;
		}
		return height;
	}
	template<typename BinaryEntry>
	int AVLTree<BinaryEntry>::height()const
	{
		return assistent_height(root);
	}
	//麻烦节点的右子树的右边高
	//通过左旋转增加左边的高度，降低右边的高度
	template<typename BinaryEntry>
	void AVLTree<BinaryEntry>::rotate_left(BinaryNode<BinaryEntry> *&sub_root)
	{
		if (sub_root == nullptr || sub_root->right == nullptr)
			cout << "program error in rotate_left" << endl;
		else {
			//由下向上移动
			auto right_tree = sub_root->right;
			sub_root->right = right_tree->left;
			right_tree->left = sub_root;
			sub_root = right_tree;
		}
	}
	//麻烦节点的左子树的左边高
	//通过右旋转增加右边的高度，降低左边的高度
	template<typename BinaryEntry>
	void AVLTree<BinaryEntry>::rotate_right(BinaryNode<BinaryEntry> *&sub_root)
	{
		if (sub_root == nullptr || sub_root->left == nullptr)
			cout << "program error in rotate_right" << endl;
		else {
			//由下向上移动
			auto left_tree = sub_root->left;
			sub_root->left = left_tree->right;
			left_tree->right = sub_root;
			//指针本身被改变
			sub_root = left_tree;
		}
	}
	//由于在右子树更高的情况下
	//在右子树添加新节点或者在左子树减少节点
	template<typename BinaryEntry>
	void AVLTree<BinaryEntry>::insert_right_balance(BinaryNode<BinaryEntry> *&sub_root)
	{
		//在RL旋转中需要更新该节点指向右子树的指针本身
		auto &right_tree = sub_root->right;
		switch (right_tree->get_balance()) {
		case right_higher:
			//左旋转			   			   
			right_tree->set_balance(equal_height);
			sub_root->set_balance(equal_height);
			//由于旋转后sub_root指向的节点发生变化
			//所以在旋转之前更新节点的情况更为方便
			rotate_left(sub_root);
			break;
			//P403情况3a
			//在左子树减少节点
		case equal_height:
			cout << "program error in rotate_left of insert_right_balance" << endl
			     << "right_tree can't be equal_height" << endl;
			break;
			//右子树的左边更高 
		case left_higher:
			auto sub_tree = right_tree->left;
			switch (sub_tree->get_balance()) {
				//在有1边达到h时就需要调整
				//节点的两边一样高是不可能的
			case equal_height:
				cout << "program error in rotate_left of insert_right_balance" << endl
				<< "sub_tree can't be equal_height" << endl;
				break;
				//T1=h,T2=h
			case left_higher:
				sub_root->set_balance(equal_height);
				right_tree->set_balance(right_higher);
				break;
				//T2=h
			case right_higher:
				sub_root->set_balance(left_higher);
				right_tree->set_balance(equal_height);
				break;
			}
			//RL旋转
			sub_tree->set_balance(equal_height);
			rotate_right(right_tree);
			rotate_left(sub_root);
			break;
		}
	}
	//麻烦节点的左边高
	template<typename BinaryEntry>
	void AVLTree<BinaryEntry>::insert_left_balance(BinaryNode<BinaryEntry> *&sub_root)
	{
		auto &left_tree = sub_root->left;
		switch (left_tree->get_balance()) {
			//左子树的左边更高   
		case left_higher:
			//右旋转
			  //由于在旋转之后，left_tree指向的1变为根节点
			  //所以建议在旋转之前更新平衡情况
			left_tree->set_balance(equal_height);
			sub_root->set_balance(equal_height);
			rotate_right(sub_root);
			break;
			//在有1边达到h时就需要调整
			//节点的两边一样高是不可能的
		case equal_height:
			cout << "program error in rotate_left of insert_right_balance" << endl
			<< "left_tree can't be equal_height" << endl;
			break;
			//左子树的右边更高 
		case right_higher:
			auto sub_tree = left_tree->right;
			//异常(equal_height)发生后依然进行了旋转
			switch (sub_tree->get_balance()) {
				//在有1边达到h时就需要调整
				//节点的两边一样高是不可能的
			case equal_height:
				cout << "program error in RL of insert_right_balance" << endl
				<< "sub_tree can't be equal_height" << endl;
				break;
				//T1=h
			case left_higher:
				sub_root->set_balance(left_higher);
				left_tree->set_balance(equal_height);
				break;
				//T2=h
			case right_higher:
				sub_root->set_balance(equal_height);
				left_tree->set_balance(right_higher);
				break;
			}
			//LR旋转
			sub_tree->set_balance(equal_height);
			rotate_left(left_tree);
			rotate_right(sub_root);
			break;
		}
	}
	//插入后父节点更新为：
	//equal_height停止更新
	//调整后为equal_height停止更新
	//right_height或left_height继续更新
	template<typename BinaryEntry>
	bool AVLTree<BinaryEntry>::avl_insert
	(BinaryNode<BinaryEntry> *&sub_root, const BinaryEntry &item)
	{
		bool taller;
		if (sub_root == nullptr) {
			try {
				//由于new成功后会返回指针，如果没有使用引用则root不会改变
				sub_root = new AVLNode<BinaryEntry>(item);
				//静态类型为BinaryNode，动态类型为AVLNode
				if (sub_root == nullptr) throw bad_alloc();
				//throw语句的作用类似于return的作用
				//编译器将执行完catch语句后退出该函数
			}
			catch (bad_alloc err) {
				cout << err.what() << endl;
			}
			return true;
		}
		else if (item == sub_root->data) {
			cout << "Error:" << __FILE__ << ": in function "
				<< __func__ << " at line " << __LINE__ << endl
				<< "can't insert the same vector in AVLTree" << endl;
			return false;
		}
		//在左子树插入并调整
		else if (item < sub_root->data) {
			taller = avl_insert(sub_root->left, item);
			//taller在成功插入时为true，插入失败时为false
			if (taller == true)
				//插入完成后更新其父节点的平衡状况
				switch (sub_root->get_balance()) {
				case left_higher:
					//高度之差为2
					insert_left_balance(sub_root);
					taller= false;
					break;
					//由于在插入之前树是平衡的
					//由于每个上面的节点的是平衡的，所以不存在多层之上的节点会需要调整
					//所以在下面的节点的高度保持不变时，可以保证上面的节点保持高度之差不超过1
					//由于该节点的右边更高
				case right_higher:
					//现在在左边新增节点后使两边高度一致
					sub_root->set_balance(equal_height);
					taller= false;
					break;
					//由于该节点的两边一样高
				case equal_height:
					//现在在左边新增节点后使左边更高
					sub_root->set_balance(left_higher);
					//在此情况下没有改变taller的值
					//因为需要返回到上一层判断平衡是否被打破
					taller= true;
					break;
				}
		}
		//在右子树插入并调整
		else {
			taller = avl_insert(sub_root->right, item);
			if (taller == true)
				switch (sub_root->get_balance()) {
				case left_higher:
					sub_root->set_balance(equal_height);
					taller= false;
					break;
				case right_higher:
					insert_right_balance(sub_root);
					taller= false;
					break;
				case equal_height:
					sub_root->set_balance(right_higher);
					taller= true;
					break;
				}
		}
		return taller;
	}
	template<typename BinaryEntry>
	void AVLTree<BinaryEntry>::insert(const BinaryEntry &item)
	{
		avl_insert(root, item);
	}
	template<typename BinaryEntry>
	void AVLTree<BinaryEntry>::remove(const BinaryEntry &item)
	{
		avl_remove(root, item);
	}
	//找到需要删除的节点
	template<typename BinaryEntry>
	bool AVLTree<BinaryEntry>::avl_remove
	(BinaryNode<BinaryEntry> *&sub_root, const BinaryEntry &item)
	{
		BinaryNode<BinaryEntry> *temp = nullptr;
		//无法寻找 
		if (sub_root == nullptr) {
			cout << "Error:" << __FILE__ << ": in function "
				<< __func__ << " at line " << __LINE__ << endl
				<< "AVLTree is empty" << endl;
			return false;
		}
		//在左子树寻找并删除
		else if (item < sub_root->data)
			return avl_remove_left(sub_root, item);
		//在右子树寻找并删除
		else if (item > sub_root->data)
			return avl_remove_right(sub_root, item);

		//找到节点
		//只有右子树或者为叶节点
		else if (sub_root->left == nullptr) {
			temp = sub_root;
			sub_root = sub_root->right;
			delete temp;
			return true;//删除成功
		}
		//只有左子树
		else if (sub_root->right == nullptr) {
			temp = sub_root;
			sub_root = sub_root->left;
			delete temp;
			return true;//删除成功
		}
		//有2个子树时减少更高的子树的高度
		//左子树更高
		else if (sub_root->get_balance() == left_higher) {
			//寻找小于中的最大值
			temp = sub_root->left;
			while (temp->right != nullptr)
				temp = temp->right;
			sub_root->data = temp->data;
			//将该最大值从子树中删除并调整
			return avl_remove_left(sub_root, temp->data);
		}
		else {
			//寻找大于中的最小值
			temp = sub_root->right;
			while (temp->left != nullptr)
				temp = temp->left;
			sub_root->data = temp->data;
			//将该最小值从子树中删除并调整
			return avl_remove_right(sub_root, temp->data);
		}
	}
	//在删除之后进行调整
	template<typename BinaryEntry>
	bool AVLTree<BinaryEntry>::avl_remove_left
	(BinaryNode<BinaryEntry> *&sub_root, const BinaryEntry &item)
	{
		bool shorter = avl_remove(sub_root->left, item);
		if (shorter == true)
			switch (sub_root->get_balance()) {
				//根据删除后节点的高度是否变短决定是否更新
			case left_higher:
				sub_root->set_balance(equal_height);
				//如P403的情况2，该节点的高度减少
				//所以需要继续更新
				return true;
			case equal_height:
				sub_root->set_balance(right_higher);
				//如P403的情况1，该节点的高度并未改变
				//所以无需更新
				return false;
				//在右子树更高的情况下减少左子树的高度
			case right_higher:
				auto temp = sub_root->right;
				switch (temp->get_balance()) {
					//情况3a
				case equal_height:
					temp->set_balance(left_higher);
					rotate_left(sub_root);
					//调整后节点的高度未变
					return false;
					//情况3b
				case right_higher:
					sub_root->set_balance(equal_height);
					temp->set_balance(equal_height);
					rotate_left(sub_root);
					//高度减1
					return true;
					//情况3c
				case left_higher:
					auto temp_left = temp->left;
					//RL旋转
					//高度减1			
					switch (temp_left->get_balance()) {
						//T2=T3=h-1
					case equal_height:
						sub_root->set_balance(equal_height);
						temp->set_balance(equal_height);
						break;
						//T2=h-2,T3=h-1
					case right_higher:
						sub_root->set_balance(left_higher);
						temp->set_balance(equal_height);
						break;
						//T2=h-1,T3=h-2
					case left_higher:
						sub_root->set_balance(equal_height);
						temp->set_balance(right_higher);
						break;
					}
					temp_left->set_balance(equal_height);
					rotate_right(sub_root->left);
					rotate_left(sub_root);
					return true;
				}
			}
	}
	//在删除之后进行调整
	template<typename BinaryEntry>
	bool AVLTree<BinaryEntry>::avl_remove_right
	(BinaryNode<BinaryEntry> *&sub_root, const BinaryEntry &item)
	{
		bool shorter = avl_remove(sub_root->right, item);
		if (shorter == true)
			switch (sub_root->get_balance()) {
				//根据删除后节点的高度是否变短决定是否更新
			case equal_height:
				sub_root->set_balance(left_higher);
				//如P403的情况1，该节点的高度并未改变
				//所以无需更新
				return false;
			case right_higher:
				sub_root->set_balance(equal_height);
				//如P403的情况2，该节点的高度减少
				//所以需要继续更新				
				return true;
				//在左子树更高的情况下减少右子树的高度
			case left_higher:
				auto temp = sub_root->left;
				switch (temp->get_balance()) {
					//情况3a
				case equal_height:
					rotate_right(sub_root);
					temp->set_balance(right_higher);
					//调整后节点的高度未变
					return false;
					//情况3b			
				case left_higher:
					rotate_right(sub_root);
					//高度减1
					sub_root->set_balance(equal_height);
					temp->set_balance(equal_height);
					return true;
				case right_higher:
					auto temp_right = temp->right;
					//LR旋转
					//高度减1			    
					switch (temp_right->get_balance()) {
						//T2=T3=h-1
					case equal_height:
						sub_root->set_balance(equal_height);
						temp->set_balance(equal_height);
						break;
						//T2=h-2,T3=h-1
					case right_higher:
						sub_root->set_balance(equal_height);
						temp->set_balance(left_higher);
						break;
						//T2=h-1,T3=h-2
					case left_higher:
						sub_root->set_balance(right_higher);
						temp->set_balance(equal_height);
						break;
					}
					temp_right->set_balance(equal_height);
					rotate_left(sub_root->left);
					rotate_right(sub_root);
					return true;
				}
			}
	}
}