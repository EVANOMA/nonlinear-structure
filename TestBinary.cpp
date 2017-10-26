#include<iostream>
using namespace std;

#include "TestBinary.h"
namespace TestBinary {

	template<typename Binary_entry>
	Binary_Node<Binary_entry>::Binary_Node()
	{
		left = right = nullptr;
	}
	template<typename Binary_entry>
	Binary_Node<Binary_entry>::Binary_Node(const Binary_entry &item)
	{
		data = item;
		left = right = nullptr;
	}
	template<typename Binary_entry>
	void Binary_Node<Binary_entry>::set_balance(Balance_factor b)
	{}
	template<typename Binary_entry>
	Balance_factor Binary_Node<Binary_entry>::get_balance()const
	{
		return equal_height;
	}
	template<typename Binary_entry>
	Binary_Tree<Binary_entry>::Binary_Tree()
	{
		root = nullptr;
	}
	template<typename Binary_entry>
	Binary_Tree<Binary_entry>::~Binary_Tree()
	{
		clear();
	}
	template<typename Binary_entry>
	bool Binary_Tree<Binary_entry>::empty()const
	{
		return root == nullptr;
	}
	template<typename Binary_entry>
	int Binary_Tree<Binary_entry>::assistent_height(Binary_Node<Binary_entry> *sub_root)const
	{
		if (sub_root == nullptr) return 0;
		int h1 = assistent_height(sub_root->left);
		int h2 = assistent_height(sub_root->right);
		if (h1>h2)  return 1 + h1;
		else       return 1 + h2;
	}
	template<typename Binary_entry>
	int Binary_Tree<Binary_entry>::height()const
	{
		return assistent_height(root);
	}
	template<typename Binary_entry>
	int Binary_Tree<Binary_entry>::assistent_count(Binary_Node<Binary_entry> *sub_root)const
	{
		if (sub_root == nullptr) return 0;
		return 1 + assistent_count(sub_root->left) + assistent_count(sub_root->right);
	}
	template<typename Binary_entry>
	int Binary_Tree<Binary_entry>::count()const
	{
		return assistent_count(root);
	}
	template<typename Binary_entry>
	void Binary_Tree<Binary_entry>::assistent_insert(Binary_Node<Binary_entry> *&sub_root,
		const Binary_entry &item)
	{
		if (sub_root == nullptr)
			sub_root = new Binary_Node<Binary_entry>(item);
		//让二叉树保持平衡
		//由于该递归函数没有使用return，所以要用else，否则会产生多次递归
		else if (assistent_height(sub_root->right) < assistent_height(sub_root->left))
			assistent_insert(sub_root->right, item);
		else
			//默认放在左边
			assistent_insert(sub_root->left, item);
	}
	template<typename Binary_entry>
	void Binary_Tree<Binary_entry>::insert(const Binary_entry &item)
	{
		assistent_insert(root, item);
	}
	template<typename Binary_entry>
	int Binary_Tree<Binary_entry>::assistent_leaf_count(Binary_Node<Binary_entry> *sub_root)const
	{
		if (sub_root == nullptr) return 0;
		if (sub_root->left == nullptr&&sub_root->right == nullptr)
			return 1;
		return assistent_leaf_count(sub_root->left) + assistent_leaf_count(sub_root->right);
	}
	template<typename Binary_entry>
	int Binary_Tree<Binary_entry>::leaf_count()const
	{
		return assistent_leaf_count(root);
	}
	template<typename Binary_entry>
	void Binary_Tree<Binary_entry>::assistent_clear(Binary_Node<Binary_entry> *sub_root)
	{
		Binary_Node<Binary_entry> *temp = sub_root;
		if (sub_root == nullptr)return;
		assistent_clear(sub_root->left);
		assistent_clear(sub_root->right);
		sub_root = nullptr;
		delete temp;
	}
	template<typename Binary_entry>
	void Binary_Tree<Binary_entry>::clear()
	{
		assistent_clear(root);
	}
	//先序遍历
	template<typename Binary_entry>
	void Binary_Tree<Binary_entry>::preorder_traversal(void(*visit)(Binary_entry &item))
	{
		assistent_preorder(root, visit);
	}
	template<typename Binary_entry>
	void Binary_Tree<Binary_entry>::assistent_preorder(Binary_Node<Binary_entry> *sub_root,
		void(*visit)(Binary_entry &item))
	{
		if (sub_root != nullptr) {
			(*visit)(sub_root->data);
			assistent_preorder(sub_root->left, visit);
			assistent_preorder(sub_root->right, visit);
		}
	}
	//中序遍历
	template<typename Binary_entry>
	void Binary_Tree<Binary_entry>::inorder_traversal(void(*visit)(Binary_entry &item))
	{
		assistent_inorder(root, visit);
	}
	template<typename Binary_entry>
	void Binary_Tree<Binary_entry>::assistent_inorder(Binary_Node<Binary_entry> *&sub_root,
		void(*visit)(Binary_entry &item))
	{
		if (sub_root != nullptr) {
			//在递归版本中各个节点的值不会改变
			assistent_inorder(sub_root->left, visit);
			(*visit)(sub_root->data);
			assistent_inorder(sub_root->right, visit);
		}
	}
	//后序遍历
	template<typename Binary_entry>
	void Binary_Tree<Binary_entry>::postorder_traversal(void(*visit)(Binary_entry &item))
	{
		assistent_postorder(root, visit);
	}
	template<typename Binary_entry>
	void Binary_Tree<Binary_entry>::assistent_postorder(Binary_Node<Binary_entry> *sub_root,
		void(*visit)(Binary_entry &item))
	{
		if (sub_root != nullptr) {
			assistent_postorder(sub_root->left, visit);
			assistent_postorder(sub_root->right, visit);
			(*visit)(sub_root->data);
		}
	}
	enum Error_code {
		success, range_error, repeat_error
	};
	template<typename Binary_entry>
	Binary_Node<Binary_entry>* Search_Tree<Binary_entry>::search_for_node(Binary_Node<Binary_entry> *sub_root, const Binary_entry &target)const
	{
		while (sub_root != nullptr && sub_root->data != target)
			if (sub_root->data < target)
				//在迭代版本中会改变root的值，所以不能使用引用
				sub_root = sub_root->right;
			else sub_root = sub_root->left;

			return sub_root;
			/*
			递归版本
			if (sub_root == nullptr || sub_root->data == target)
			return sub_root;
			//删除else
			else if (sub_root->data < target)
			return search_for_node(sub_root->right, target);
			else return search_for_node(sub_root->left, target);
			*/
	}
	template<typename Binary_entry>
	Error_code Search_Tree<Binary_entry>::tree_search
	(const Binary_entry &target)const
	{
		Binary_Node<Binary_entry> *found = search_for_node(root, target);
		if (found == nullptr)
			return range_error;
		else  return success;
	}
	template<typename Binary_entry>
	Error_code Search_Tree<Binary_entry>::search_and_insert
	(Binary_Node<Binary_entry> *&sub_root, const Binary_entry &item)
	{
		if (sub_root == nullptr) {
			//由于new成功后会返回指针，如果没有使用引用则root不会改变
			sub_root = new Binary_Node<Binary_entry>(item);
			return success;
		}
		else if (item < sub_root->data)
			//由于必须使用引用，所以必须使用递归版本
			return search_and_insert(sub_root->left, item);
		else if (item >sub_root->data)
			return search_and_insert(sub_root->right, item);
		else return range_error;
	}
	template<typename Binary_entry>
	Error_code Search_Tree<Binary_entry>::insert
	(const Binary_entry &item)
	{
		return search_and_insert(root, item);
	}
	template<typename Binary_entry>
	Error_code Search_Tree<Binary_entry>::remove_root(Binary_Node<Binary_entry> *&sub_root)
	{
		if (sub_root == nullptr)
			return range_error;
		Binary_Node<Binary_entry> *to_delete = sub_root;
		//被删除的节点只有1个子树时，直接向上移动
		if (sub_root->left == nullptr)
			//由于需要改变指针的地址，所以必须使用引用
			sub_root = sub_root->right;
		else if (sub_root->right == nullptr)
			sub_root = sub_root->left;
		else {
			to_delete = sub_root->left;
			Binary_Node<Binary_entry> *parent = sub_root;
			//寻找离小于被删除节点最近的节点进行替换
			//位于左子树的最右边
			while (to_delete->right != nullptr) {
				parent = to_delete;
				to_delete = to_delete->right;
			}
			sub_root->data= to_delete->data;
			//由于被删除节点的左子节点是最近的节点
			//所以需要向上移动左子树
			if(parent== sub_root)
				sub_root->left= to_delete->left;
			else
				//将被删除节点的右子树作为新的右子树
				//无需移动左子树
				sub_root->right = to_delete->left;
		}
		delete  to_delete;
		return success;
	}
	template<typename Binary_entry>
	Error_code Search_Tree<Binary_entry>::search_and_remove
	(Binary_Node<Binary_entry> *sub_root, const Binary_entry &target)
	{
		while (sub_root != nullptr && sub_root->data != target)
			if (sub_root->data < target)
				//在迭代版本中会改变root的值，所以不能使用引用
				sub_root = sub_root->right;
			else sub_root = sub_root->left;
		return remove_root(sub_root);
			
	}
	template<typename Binary_entry>
	Error_code Search_Tree<Binary_entry>::remove(const Binary_entry &item)
	{
		return search_and_remove(root, item);
	}
	enum Balance_factor {
		//该节点的高度不变
		equal_height, 
		//左右子树的高度差为1
		left_higher, 
		right_higher
	};
	template<typename Binary_entry>
	AVL_Node<Binary_entry>::AVL_Node()
	{
		left = right = nullptr;
		balance = equal_height;
	}
	template<typename Binary_entry>
	AVL_Node<Binary_entry>::AVL_Node(const Binary_entry &item)
	{
		data = item;
		left = right = nullptr;
		balance = equal_height;
	}
	template<typename Binary_entry>
	void AVL_Node<Binary_entry>::set_balance(Balance_factor b)
	{
		balance = b;
	}
	template<typename Binary_entry>
	Balance_factor AVL_Node<Binary_entry>::get_balance()const
	{
		return balance;
	}
	//高度为左右子树的节点个数的最大值
	//不包括根节点
	template<typename Binary_entry>
	int AVL_Tree<Binary_entry>::assistent_height
	(Binary_Node<Binary_entry> *sub_root)const
	{
		if (sub_root == nullptr) return 0;
		if (sub_root ->get_balance()==right_higher) 
			return 1 + assistent_height(sub_root->right);
		return 1 + assistent_height(sub_root->left);
	}
	template<typename Binary_entry>
	int AVL_Tree<Binary_entry>::height()const
	{
		return assistent_height(root);
	}
	//麻烦节点的右子树的右边高
	//通过左旋转增加左边的高度，降低右边的高度
	template<typename Binary_entry>
	void AVL_Tree<Binary_entry>::rotate_left(Binary_Node<Binary_entry> *&sub_root)
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
	template<typename Binary_entry>
	void AVL_Tree<Binary_entry>::rotate_right(Binary_Node<Binary_entry> *&sub_root)
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
	//麻烦节点的右边高
	template<typename Binary_entry>
	void AVL_Tree<Binary_entry>::right_balance(Binary_Node<Binary_entry> *&sub_root)
	{
		Binary_Node<Binary_entry> *&right_tree = sub_root->right;
		switch (right_tree->get_balance()) {			
		    //右子树的右边更高    
		    case right_higher:	
				//左旋转			   			   
			   right_tree->set_balance(equal_height);
			   sub_root->set_balance(equal_height);
			   rotate_left(sub_root);
			   break;
			//在有1边达到h时就需要调整
			//节点的两边一样高是不可能的
		    case equal_height:
			   cout << "program error in rotate_left of right_balance" << endl;
			   break;//是否需要添加？			   
			//右子树的左边更高 
		    case left_higher:
			   auto sub_tree = right_tree->left;
			   switch (sub_tree->get_balance()) {
				   //在有1边达到h时就需要调整
				   //节点的两边一样高是不可能的
			       case equal_height:
					   cout << "program error in RL of right_balance" << endl;
				       break;
				   //T1=h
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
	template<typename Binary_entry>
	void AVL_Tree<Binary_entry>::left_balance(Binary_Node<Binary_entry> *&sub_root)
	{
		//为什么left_tree的引用在左旋转之后会失效？
		//如果使用*left_tree实际指向的是节点1
		//验证它绑定的是sub_root->left而不是节点1
		Binary_Node<Binary_entry> *&left_tree = sub_root->left;
		switch (left_tree->get_balance()) {
			//左子树的左边更高   
		    case left_higher:
			//右旋转
			  //由于在旋转之后，left_tree指向的1变为根节点
			  //所以必须在旋转之前更新平衡情况
			  left_tree->set_balance(equal_height);
			  sub_root->set_balance(equal_height);
			  //但是不能排除异常发生后没有旋转但是却改变了平衡的记录
			  rotate_right(sub_root);	 			 
			  break;
			  //在有1边达到h时就需要调整
			  //节点的两边一样高是不可能的
			case equal_height:
				cout << "program error in rotate_left of right_balance" << endl;
				break;//是否需要添加？			   
			//左子树的右边更高 
			case right_higher:
				auto sub_tree = left_tree->right;
				//先判断sub_tree的状态防止异常(equal_height)的发生
				switch (sub_tree->get_balance()) {
					//在有1边达到h时就需要调整
					//节点的两边一样高是不可能的
				case equal_height:
					cout << "program error in RL of right_balance" << endl;
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
	template<typename Binary_entry>
	Error_code AVL_Tree<Binary_entry>::avl_insert
	(Binary_Node<Binary_entry> *&sub_root, const Binary_entry &item, bool &taller)
	{
		Error_code result = success;
		if (sub_root == nullptr) {
			//由于new成功后会返回指针，如果没有使用引用则root不会改变
			sub_root = new AVL_Node<Binary_entry>(item);
			//静态类型为Binary_Node，动态类型为AVL_Node
			taller=true;
			return success;
		}
		else if (item == sub_root->data) {
			taller = false;
			return repeat_error;
		}
		//在左子树插入并调整
		else if (item <sub_root->data) {
			result = avl_insert(sub_root->left,item,taller);
			//taller在成功插入时为true，插入失败时为false
			if(taller==true)
				//插入完成后更新其父节点的平衡状况
				switch (sub_root->get_balance()) {
				    case left_higher:
					//高度之差为2
					    left_balance(sub_root);
					    taller = false;
					    //由于在插入之前树是平衡的
					    //由于每个上面的节点的是平衡的，所以不存在多层之上的节点会需要调整
					    //所以在下面的节点的高度保持不变时，可以保证上面的节点保持高度之差不超过1
					    break;
				   //由于该节点的右边更高
				   case right_higher:
					   //现在在左边新增节点后使两边高度一致
					   sub_root->set_balance(equal_height);
					   taller = false;
					   break;
				  //由于该节点的两边一样高
				  case equal_height:
					   //现在在左边新增节点后使左边更高
					   sub_root->set_balance(left_higher);
					   //在此情况下没有改变taller的值
					   //因为需要返回到上一层判断平衡是否被打破
					   break;
				}							
		}	
		//在右子树插入并调整
		else {
			result = avl_insert(sub_root->right, item, taller);
			if (taller == true)
				switch (sub_root->get_balance()) {
				    case left_higher:
					   sub_root->set_balance(equal_height);
					   taller = false;
					   break;					
				    case right_higher:					
					   right_balance(sub_root);
					   taller = false;
					   break;					
				    case equal_height:
					   sub_root->set_balance(right_higher);
					   break;
				}					
		}
		return result;
	}
	template<typename Binary_entry>
	Error_code AVL_Tree<Binary_entry>::insert
	(const Binary_entry &item)
	{
		bool taller;
		return avl_insert(root, item,taller);
	}
	template<typename Binary_entry>
	Error_code AVL_Tree<Binary_entry>::remove
	(const Binary_entry &item)
	{
		bool shorter;
		return avl_remove(root, item, shorter);
	}
	//找到需要删除的节点
	template<typename Binary_entry>
	Error_code AVL_Tree<Binary_entry>::avl_remove
	(Binary_Node<Binary_entry> *&sub_root, const Binary_entry &item, bool &shorter)
	{
		Binary_Node<Binary_entry> *temp=nullptr;
		if (sub_root == nullptr) 			
			return range_error;
		//在左子树寻找并删除
		else if (item <sub_root->data) 
			return avl_remove_left(sub_root, item, shorter);
		//在右子树寻找并删除
		else if (item >sub_root->data)
			return avl_remove_right(sub_root, item, shorter);
		//找到节点
		//只有右子树或者为叶节点
		else if (sub_root->left == nullptr) {
			temp = sub_root;
			sub_root= sub_root->right;
			delete temp;
			shorter = true;//删除成功
		}
		//只有左子树
		else if (sub_root->right == nullptr) {
			temp = sub_root;
			sub_root = sub_root->left;
			delete temp;
			shorter = true;//删除成功
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
			return avl_remove_left(sub_root, temp->data, shorter);
		}
		else {
			//寻找大于中的最小值
			temp = sub_root->right;
			while (temp->left != nullptr)
				temp = temp->left;
			sub_root->data = temp->data;
			//将该最小值从子树中删除并调整
			return avl_remove_right(sub_root, temp->data, shorter);
		}
		return success;
	}
	//在删除之后进行调整
	template<typename Binary_entry>
	Error_code AVL_Tree<Binary_entry>::avl_remove_left
	(Binary_Node<Binary_entry> *&sub_root, const Binary_entry &item, bool &shorter)
	{
		Error_code result= avl_remove(sub_root->left, item, shorter);
		if(shorter==true)
			switch (sub_root->get_balance()) {
				//根据删除后节点的高度是否变短决定是否更新
			   case left_higher:				
				   sub_root->set_balance(equal_height);
				   //如P403的情况2，该节点的高度减少
				   //所以需要继续更新
				   break;				   
			   case equal_height:
				  sub_root->set_balance(right_higher);
				  //如P403的情况1，该节点的高度并未改变
				  //所以无需更新
				  shorter = false;
				  break;
			   //在右子树更高的情况下减少左子树的高度
			   case right_higher:
				   auto temp = sub_root->right;
				   switch (temp->get_balance()) {
				      //情况3a
				      case equal_height:
						  temp->set_balance(left_higher);
						  rotate_left(sub_root);
						  //调整后节点的高度未变
						  shorter = false;
					      break;
					  //情况3b
					  case right_higher:
						  sub_root->set_balance(equal_height);
						  temp->set_balance(equal_height);
						  rotate_left(sub_root);
						  //高度减1
					   //情况3c
				       case left_higher:
						  auto temp_left = temp->left;
						  //RL旋转
						  //高度减1
						  temp_left->set_balance(equal_height);
						  rotate_right(sub_root->left);
						  rotate_left(sub_root);			
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
					      break;				   				   
				   }
			}
		return result;
	}
	//在删除之后进行调整
	template<typename Binary_entry>
	Error_code AVL_Tree<Binary_entry>::avl_remove_right
	(Binary_Node<Binary_entry> *&sub_root, const Binary_entry &item, bool &shorter)
	{
		Error_code result = avl_remove(sub_root->right, item, shorter);
		if (shorter == true)
			switch (sub_root->get_balance()) {
				//根据删除后节点的高度是否变短决定是否更新
			    case equal_height:
				    sub_root->set_balance(left_higher);
				    //如P403的情况1，该节点的高度并未改变
				    //所以无需更新
				    shorter = false;
				    break;			
			    case right_higher:
				    sub_root->set_balance(equal_height);
				    //如P403的情况2，该节点的高度减少
				    //所以需要继续更新				
				    break;
			    //在左子树更高的情况下减少右子树的高度
			    case left_higher:					
				    auto temp = sub_root->left;
					switch (temp->get_balance()) {
						//情况3a
					case equal_height:
						rotate_right(sub_root);
						temp->set_balance(right_higher);
						//调整后节点的高度未变
						shorter = false;
						break;
						//情况3b			
					case left_higher:
						rotate_right(sub_root);
						//高度减1
						sub_root->set_balance(equal_height);
						temp->set_balance(equal_height);
						break;
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
						break;
					}
			}
		return result;
	}
}