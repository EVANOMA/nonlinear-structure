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
		//�ö���������ƽ��
		//���ڸõݹ麯��û��ʹ��return������Ҫ��else������������εݹ�
		else if (assistent_height(sub_root->right) < assistent_height(sub_root->left))
			assistent_insert(sub_root->right, item);
		else
			//Ĭ�Ϸ������
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
	//�������
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
	//�������
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
			//�ڵݹ�汾�и����ڵ��ֵ����ı�
			assistent_inorder(sub_root->left, visit);
			(*visit)(sub_root->data);
			assistent_inorder(sub_root->right, visit);
		}
	}
	//�������
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
				//�ڵ����汾�л�ı�root��ֵ�����Բ���ʹ������
				sub_root = sub_root->right;
			else sub_root = sub_root->left;

			return sub_root;
			/*
			�ݹ�汾
			if (sub_root == nullptr || sub_root->data == target)
			return sub_root;
			//ɾ��else
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
			//����new�ɹ���᷵��ָ�룬���û��ʹ��������root����ı�
			sub_root = new Binary_Node<Binary_entry>(item);
			return success;
		}
		else if (item < sub_root->data)
			//���ڱ���ʹ�����ã����Ա���ʹ�õݹ�汾
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
		//��ɾ���Ľڵ�ֻ��1������ʱ��ֱ�������ƶ�
		if (sub_root->left == nullptr)
			//������Ҫ�ı�ָ��ĵ�ַ�����Ա���ʹ������
			sub_root = sub_root->right;
		else if (sub_root->right == nullptr)
			sub_root = sub_root->left;
		else {
			to_delete = sub_root->left;
			Binary_Node<Binary_entry> *parent = sub_root;
			//Ѱ����С�ڱ�ɾ���ڵ�����Ľڵ�����滻
			//λ�������������ұ�
			while (to_delete->right != nullptr) {
				parent = to_delete;
				to_delete = to_delete->right;
			}
			sub_root->data= to_delete->data;
			//���ڱ�ɾ���ڵ�����ӽڵ�������Ľڵ�
			//������Ҫ�����ƶ�������
			if(parent== sub_root)
				sub_root->left= to_delete->left;
			else
				//����ɾ���ڵ����������Ϊ�µ�������
				//�����ƶ�������
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
				//�ڵ����汾�л�ı�root��ֵ�����Բ���ʹ������
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
		//�ýڵ�ĸ߶Ȳ���
		equal_height, 
		//���������ĸ߶Ȳ�Ϊ1
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
	//�߶�Ϊ���������Ľڵ���������ֵ
	//���������ڵ�
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
	//�鷳�ڵ�����������ұ߸�
	//ͨ������ת������ߵĸ߶ȣ������ұߵĸ߶�
	template<typename Binary_entry>
	void AVL_Tree<Binary_entry>::rotate_left(Binary_Node<Binary_entry> *&sub_root)
	{
		if (sub_root == nullptr || sub_root->right == nullptr)
			cout << "program error in rotate_left" << endl;
		else {
			//���������ƶ�
			auto right_tree = sub_root->right;
			sub_root->right = right_tree->left;
			right_tree->left = sub_root;
			sub_root = right_tree;
		}
	}
	//�鷳�ڵ������������߸�
	//ͨ������ת�����ұߵĸ߶ȣ�������ߵĸ߶�
	template<typename Binary_entry>
	void AVL_Tree<Binary_entry>::rotate_right(Binary_Node<Binary_entry> *&sub_root)
	{
		if (sub_root == nullptr || sub_root->left == nullptr)
			cout << "program error in rotate_right" << endl;
		else {
			//���������ƶ�
			auto left_tree = sub_root->left;
			sub_root->left = left_tree->right;
			left_tree->right = sub_root;
			//ָ�뱾���ı�
			sub_root = left_tree;
		}
	}
	//�鷳�ڵ���ұ߸�
	template<typename Binary_entry>
	void AVL_Tree<Binary_entry>::right_balance(Binary_Node<Binary_entry> *&sub_root)
	{
		Binary_Node<Binary_entry> *&right_tree = sub_root->right;
		switch (right_tree->get_balance()) {			
		    //���������ұ߸���    
		    case right_higher:	
				//����ת			   			   
			   right_tree->set_balance(equal_height);
			   sub_root->set_balance(equal_height);
			   rotate_left(sub_root);
			   break;
			//����1�ߴﵽhʱ����Ҫ����
			//�ڵ������һ�����ǲ����ܵ�
		    case equal_height:
			   cout << "program error in rotate_left of right_balance" << endl;
			   break;//�Ƿ���Ҫ��ӣ�			   
			//����������߸��� 
		    case left_higher:
			   auto sub_tree = right_tree->left;
			   switch (sub_tree->get_balance()) {
				   //����1�ߴﵽhʱ����Ҫ����
				   //�ڵ������һ�����ǲ����ܵ�
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
			  //RL��ת
			  sub_tree->set_balance(equal_height);
			  rotate_right(right_tree);
			  rotate_left(sub_root);			  
			  break;
		}								
	}
	//�鷳�ڵ����߸�
	template<typename Binary_entry>
	void AVL_Tree<Binary_entry>::left_balance(Binary_Node<Binary_entry> *&sub_root)
	{
		//Ϊʲôleft_tree������������ת֮���ʧЧ��
		//���ʹ��*left_treeʵ��ָ����ǽڵ�1
		//��֤���󶨵���sub_root->left�����ǽڵ�1
		Binary_Node<Binary_entry> *&left_tree = sub_root->left;
		switch (left_tree->get_balance()) {
			//����������߸���   
		    case left_higher:
			//����ת
			  //��������ת֮��left_treeָ���1��Ϊ���ڵ�
			  //���Ա�������ת֮ǰ����ƽ�����
			  left_tree->set_balance(equal_height);
			  sub_root->set_balance(equal_height);
			  //���ǲ����ų��쳣������û����ת����ȴ�ı���ƽ��ļ�¼
			  rotate_right(sub_root);	 			 
			  break;
			  //����1�ߴﵽhʱ����Ҫ����
			  //�ڵ������һ�����ǲ����ܵ�
			case equal_height:
				cout << "program error in rotate_left of right_balance" << endl;
				break;//�Ƿ���Ҫ��ӣ�			   
			//���������ұ߸��� 
			case right_higher:
				auto sub_tree = left_tree->right;
				//���ж�sub_tree��״̬��ֹ�쳣(equal_height)�ķ���
				switch (sub_tree->get_balance()) {
					//����1�ߴﵽhʱ����Ҫ����
					//�ڵ������һ�����ǲ����ܵ�
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
				//LR��ת
				sub_tree->set_balance(equal_height);
				rotate_left(left_tree);
				rotate_right(sub_root);
				break;
		}
	}
	//����󸸽ڵ����Ϊ��
	//equal_heightֹͣ����
	//������Ϊequal_heightֹͣ����
	//right_height��left_height��������
	template<typename Binary_entry>
	Error_code AVL_Tree<Binary_entry>::avl_insert
	(Binary_Node<Binary_entry> *&sub_root, const Binary_entry &item, bool &taller)
	{
		Error_code result = success;
		if (sub_root == nullptr) {
			//����new�ɹ���᷵��ָ�룬���û��ʹ��������root����ı�
			sub_root = new AVL_Node<Binary_entry>(item);
			//��̬����ΪBinary_Node����̬����ΪAVL_Node
			taller=true;
			return success;
		}
		else if (item == sub_root->data) {
			taller = false;
			return repeat_error;
		}
		//�����������벢����
		else if (item <sub_root->data) {
			result = avl_insert(sub_root->left,item,taller);
			//taller�ڳɹ�����ʱΪtrue������ʧ��ʱΪfalse
			if(taller==true)
				//������ɺ�����丸�ڵ��ƽ��״��
				switch (sub_root->get_balance()) {
				    case left_higher:
					//�߶�֮��Ϊ2
					    left_balance(sub_root);
					    taller = false;
					    //�����ڲ���֮ǰ����ƽ���
					    //����ÿ������Ľڵ����ƽ��ģ����Բ����ڶ��֮�ϵĽڵ����Ҫ����
					    //����������Ľڵ�ĸ߶ȱ��ֲ���ʱ�����Ա�֤����Ľڵ㱣�ָ߶�֮�����1
					    break;
				   //���ڸýڵ���ұ߸���
				   case right_higher:
					   //��������������ڵ��ʹ���߸߶�һ��
					   sub_root->set_balance(equal_height);
					   taller = false;
					   break;
				  //���ڸýڵ������һ����
				  case equal_height:
					   //��������������ڵ��ʹ��߸���
					   sub_root->set_balance(left_higher);
					   //�ڴ������û�иı�taller��ֵ
					   //��Ϊ��Ҫ���ص���һ���ж�ƽ���Ƿ񱻴���
					   break;
				}							
		}	
		//�����������벢����
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
	//�ҵ���Ҫɾ���Ľڵ�
	template<typename Binary_entry>
	Error_code AVL_Tree<Binary_entry>::avl_remove
	(Binary_Node<Binary_entry> *&sub_root, const Binary_entry &item, bool &shorter)
	{
		Binary_Node<Binary_entry> *temp=nullptr;
		if (sub_root == nullptr) 			
			return range_error;
		//��������Ѱ�Ҳ�ɾ��
		else if (item <sub_root->data) 
			return avl_remove_left(sub_root, item, shorter);
		//��������Ѱ�Ҳ�ɾ��
		else if (item >sub_root->data)
			return avl_remove_right(sub_root, item, shorter);
		//�ҵ��ڵ�
		//ֻ������������ΪҶ�ڵ�
		else if (sub_root->left == nullptr) {
			temp = sub_root;
			sub_root= sub_root->right;
			delete temp;
			shorter = true;//ɾ���ɹ�
		}
		//ֻ��������
		else if (sub_root->right == nullptr) {
			temp = sub_root;
			sub_root = sub_root->left;
			delete temp;
			shorter = true;//ɾ���ɹ�
		}
		//��2������ʱ���ٸ��ߵ������ĸ߶�
		//����������
		else if (sub_root->get_balance() == left_higher) {
			//Ѱ��С���е����ֵ
			temp = sub_root->left;
			while (temp->right != nullptr)
				temp = temp->right;
			sub_root->data = temp->data;
			//�������ֵ��������ɾ��������
			return avl_remove_left(sub_root, temp->data, shorter);
		}
		else {
			//Ѱ�Ҵ����е���Сֵ
			temp = sub_root->right;
			while (temp->left != nullptr)
				temp = temp->left;
			sub_root->data = temp->data;
			//������Сֵ��������ɾ��������
			return avl_remove_right(sub_root, temp->data, shorter);
		}
		return success;
	}
	//��ɾ��֮����е���
	template<typename Binary_entry>
	Error_code AVL_Tree<Binary_entry>::avl_remove_left
	(Binary_Node<Binary_entry> *&sub_root, const Binary_entry &item, bool &shorter)
	{
		Error_code result= avl_remove(sub_root->left, item, shorter);
		if(shorter==true)
			switch (sub_root->get_balance()) {
				//����ɾ����ڵ�ĸ߶��Ƿ��̾����Ƿ����
			   case left_higher:				
				   sub_root->set_balance(equal_height);
				   //��P403�����2���ýڵ�ĸ߶ȼ���
				   //������Ҫ��������
				   break;				   
			   case equal_height:
				  sub_root->set_balance(right_higher);
				  //��P403�����1���ýڵ�ĸ߶Ȳ�δ�ı�
				  //�����������
				  shorter = false;
				  break;
			   //�����������ߵ�����¼����������ĸ߶�
			   case right_higher:
				   auto temp = sub_root->right;
				   switch (temp->get_balance()) {
				      //���3a
				      case equal_height:
						  temp->set_balance(left_higher);
						  rotate_left(sub_root);
						  //������ڵ�ĸ߶�δ��
						  shorter = false;
					      break;
					  //���3b
					  case right_higher:
						  sub_root->set_balance(equal_height);
						  temp->set_balance(equal_height);
						  rotate_left(sub_root);
						  //�߶ȼ�1
					   //���3c
				       case left_higher:
						  auto temp_left = temp->left;
						  //RL��ת
						  //�߶ȼ�1
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
	//��ɾ��֮����е���
	template<typename Binary_entry>
	Error_code AVL_Tree<Binary_entry>::avl_remove_right
	(Binary_Node<Binary_entry> *&sub_root, const Binary_entry &item, bool &shorter)
	{
		Error_code result = avl_remove(sub_root->right, item, shorter);
		if (shorter == true)
			switch (sub_root->get_balance()) {
				//����ɾ����ڵ�ĸ߶��Ƿ��̾����Ƿ����
			    case equal_height:
				    sub_root->set_balance(left_higher);
				    //��P403�����1���ýڵ�ĸ߶Ȳ�δ�ı�
				    //�����������
				    shorter = false;
				    break;			
			    case right_higher:
				    sub_root->set_balance(equal_height);
				    //��P403�����2���ýڵ�ĸ߶ȼ���
				    //������Ҫ��������				
				    break;
			    //�����������ߵ�����¼����������ĸ߶�
			    case left_higher:					
				    auto temp = sub_root->left;
					switch (temp->get_balance()) {
						//���3a
					case equal_height:
						rotate_right(sub_root);
						temp->set_balance(right_higher);
						//������ڵ�ĸ߶�δ��
						shorter = false;
						break;
						//���3b			
					case left_higher:
						rotate_right(sub_root);
						//�߶ȼ�1
						sub_root->set_balance(equal_height);
						temp->set_balance(equal_height);
						break;
					case right_higher:
						auto temp_right = temp->right;
						//LR��ת
						//�߶ȼ�1			    
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