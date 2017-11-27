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
			//����new�ɹ���᷵��ָ�룬���û��ʹ��������root����ı�
			try {
				sub_root = new BinaryNode<BinaryEntry>(item);
				//bad_allocֻ��ʹ��Ĭ�ϳ�ʼ��
				if (sub_root == nullptr) throw bad_alloc();
				//throw��������������return������
				//��������ִ����catch�����˳��ú���
			}
			catch (bad_alloc err) {
				cout << err.what() << endl;
			}
		}
		//�ö���������ƽ��
		//���ڸõݹ麯��û��ʹ��return������Ҫ��else������������εݹ�
		else if (assistent_height(sub_root->right) < assistent_height(sub_root->left))
			assistent_insert(sub_root->right, item);
		else
			//Ĭ�Ϸ������
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
		//ָ�뱻delete�󲻻�Ϊ��
		sub_root = nullptr;
	}
	template<typename BinaryEntry>
	void BinaryTree<BinaryEntry>::clear()
	{
		assistent_clear(root);
	}
	//�������
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
	//�������
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
			//�ڵݹ�汾�и����ڵ��ֵ����ı�
			assistent_inorder(sub_root->left, visit);
			(*visit)(sub_root->data);
			assistent_inorder(sub_root->right, visit);
		}
	}
	//�������
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
				//�ڵ����汾�л�ı�root��ֵ�����Բ���ʹ������
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
			//����new�ɹ���᷵��ָ�룬���û��ʹ��������root����ı�
			try {
				sub_root = new BinaryNode<BinaryEntry>(item);
				//bad_allocֻ��ʹ��Ĭ�ϳ�ʼ��
				if (sub_root == nullptr) throw bad_alloc();
				//throw��������������return������
				//��������ִ����catch�����˳��ú���
			}
			catch (bad_alloc err) {
				cout << err.what() << endl;
			}
		}
		else if (item < sub_root->data)
			//���ڱ���ʹ�����ã����Ա���ʹ�õݹ�汾
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
		//��ɾ���Ľڵ�ֻ��1������ʱ��ֱ�������ƶ�
		if (sub_root->left == nullptr)
			//������Ҫ�ı�ָ��ĵ�ַ�����Ա���ʹ������
			sub_root = sub_root->right;
		else if (sub_root->right == nullptr)
			sub_root = sub_root->left;
		else {
			auto parent = sub_root;
			to_delete = sub_root->left;
			//Ѱ����С�ڱ�ɾ���ڵ�����Ľڵ�����滻
			//λ�������������ұ�
			while (to_delete->right != nullptr) {
				parent = to_delete;
				to_delete = to_delete->right;
			}
			sub_root->data = to_delete->data;
			//���ڱ�ɾ���ڵ�����ӽڵ�������Ľڵ�
			//������Ҫ�����ƶ�������
			if (parent == sub_root)
				sub_root->left = to_delete->left;
			else
				//����ɾ���ڵ����������Ϊ�µ�������
				//�����ƶ�������
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
				//�ڵ����汾�л�ı�root��ֵ�����Բ���ʹ������
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
		//�ýڵ�ĸ߶Ȳ���
		equal_height,
		//���������ĸ߶Ȳ�Ϊ1
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
	//�߶�Ϊ���������Ľڵ���������ֵ
	//���������ڵ�
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
	//�鷳�ڵ�����������ұ߸�
	//ͨ������ת������ߵĸ߶ȣ������ұߵĸ߶�
	template<typename BinaryEntry>
	void AVLTree<BinaryEntry>::rotate_left(BinaryNode<BinaryEntry> *&sub_root)
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
	template<typename BinaryEntry>
	void AVLTree<BinaryEntry>::rotate_right(BinaryNode<BinaryEntry> *&sub_root)
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
	//���������������ߵ������
	//������������½ڵ���������������ٽڵ�
	template<typename BinaryEntry>
	void AVLTree<BinaryEntry>::insert_right_balance(BinaryNode<BinaryEntry> *&sub_root)
	{
		//��RL��ת����Ҫ���¸ýڵ�ָ����������ָ�뱾��
		auto &right_tree = sub_root->right;
		switch (right_tree->get_balance()) {
		case right_higher:
			//����ת			   			   
			right_tree->set_balance(equal_height);
			sub_root->set_balance(equal_height);
			//������ת��sub_rootָ��Ľڵ㷢���仯
			//��������ת֮ǰ���½ڵ�������Ϊ����
			rotate_left(sub_root);
			break;
			//P403���3a
			//�����������ٽڵ�
		case equal_height:
			cout << "program error in rotate_left of insert_right_balance" << endl
			     << "right_tree can't be equal_height" << endl;
			break;
			//����������߸��� 
		case left_higher:
			auto sub_tree = right_tree->left;
			switch (sub_tree->get_balance()) {
				//����1�ߴﵽhʱ����Ҫ����
				//�ڵ������һ�����ǲ����ܵ�
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
			//RL��ת
			sub_tree->set_balance(equal_height);
			rotate_right(right_tree);
			rotate_left(sub_root);
			break;
		}
	}
	//�鷳�ڵ����߸�
	template<typename BinaryEntry>
	void AVLTree<BinaryEntry>::insert_left_balance(BinaryNode<BinaryEntry> *&sub_root)
	{
		auto &left_tree = sub_root->left;
		switch (left_tree->get_balance()) {
			//����������߸���   
		case left_higher:
			//����ת
			  //��������ת֮��left_treeָ���1��Ϊ���ڵ�
			  //���Խ�������ת֮ǰ����ƽ�����
			left_tree->set_balance(equal_height);
			sub_root->set_balance(equal_height);
			rotate_right(sub_root);
			break;
			//����1�ߴﵽhʱ����Ҫ����
			//�ڵ������һ�����ǲ����ܵ�
		case equal_height:
			cout << "program error in rotate_left of insert_right_balance" << endl
			<< "left_tree can't be equal_height" << endl;
			break;
			//���������ұ߸��� 
		case right_higher:
			auto sub_tree = left_tree->right;
			//�쳣(equal_height)��������Ȼ��������ת
			switch (sub_tree->get_balance()) {
				//����1�ߴﵽhʱ����Ҫ����
				//�ڵ������һ�����ǲ����ܵ�
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
	template<typename BinaryEntry>
	bool AVLTree<BinaryEntry>::avl_insert
	(BinaryNode<BinaryEntry> *&sub_root, const BinaryEntry &item)
	{
		bool taller;
		if (sub_root == nullptr) {
			try {
				//����new�ɹ���᷵��ָ�룬���û��ʹ��������root����ı�
				sub_root = new AVLNode<BinaryEntry>(item);
				//��̬����ΪBinaryNode����̬����ΪAVLNode
				if (sub_root == nullptr) throw bad_alloc();
				//throw��������������return������
				//��������ִ����catch�����˳��ú���
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
		//�����������벢����
		else if (item < sub_root->data) {
			taller = avl_insert(sub_root->left, item);
			//taller�ڳɹ�����ʱΪtrue������ʧ��ʱΪfalse
			if (taller == true)
				//������ɺ�����丸�ڵ��ƽ��״��
				switch (sub_root->get_balance()) {
				case left_higher:
					//�߶�֮��Ϊ2
					insert_left_balance(sub_root);
					taller= false;
					break;
					//�����ڲ���֮ǰ����ƽ���
					//����ÿ������Ľڵ����ƽ��ģ����Բ����ڶ��֮�ϵĽڵ����Ҫ����
					//����������Ľڵ�ĸ߶ȱ��ֲ���ʱ�����Ա�֤����Ľڵ㱣�ָ߶�֮�����1
					//���ڸýڵ���ұ߸���
				case right_higher:
					//��������������ڵ��ʹ���߸߶�һ��
					sub_root->set_balance(equal_height);
					taller= false;
					break;
					//���ڸýڵ������һ����
				case equal_height:
					//��������������ڵ��ʹ��߸���
					sub_root->set_balance(left_higher);
					//�ڴ������û�иı�taller��ֵ
					//��Ϊ��Ҫ���ص���һ���ж�ƽ���Ƿ񱻴���
					taller= true;
					break;
				}
		}
		//�����������벢����
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
	//�ҵ���Ҫɾ���Ľڵ�
	template<typename BinaryEntry>
	bool AVLTree<BinaryEntry>::avl_remove
	(BinaryNode<BinaryEntry> *&sub_root, const BinaryEntry &item)
	{
		BinaryNode<BinaryEntry> *temp = nullptr;
		//�޷�Ѱ�� 
		if (sub_root == nullptr) {
			cout << "Error:" << __FILE__ << ": in function "
				<< __func__ << " at line " << __LINE__ << endl
				<< "AVLTree is empty" << endl;
			return false;
		}
		//��������Ѱ�Ҳ�ɾ��
		else if (item < sub_root->data)
			return avl_remove_left(sub_root, item);
		//��������Ѱ�Ҳ�ɾ��
		else if (item > sub_root->data)
			return avl_remove_right(sub_root, item);

		//�ҵ��ڵ�
		//ֻ������������ΪҶ�ڵ�
		else if (sub_root->left == nullptr) {
			temp = sub_root;
			sub_root = sub_root->right;
			delete temp;
			return true;//ɾ���ɹ�
		}
		//ֻ��������
		else if (sub_root->right == nullptr) {
			temp = sub_root;
			sub_root = sub_root->left;
			delete temp;
			return true;//ɾ���ɹ�
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
			return avl_remove_left(sub_root, temp->data);
		}
		else {
			//Ѱ�Ҵ����е���Сֵ
			temp = sub_root->right;
			while (temp->left != nullptr)
				temp = temp->left;
			sub_root->data = temp->data;
			//������Сֵ��������ɾ��������
			return avl_remove_right(sub_root, temp->data);
		}
	}
	//��ɾ��֮����е���
	template<typename BinaryEntry>
	bool AVLTree<BinaryEntry>::avl_remove_left
	(BinaryNode<BinaryEntry> *&sub_root, const BinaryEntry &item)
	{
		bool shorter = avl_remove(sub_root->left, item);
		if (shorter == true)
			switch (sub_root->get_balance()) {
				//����ɾ����ڵ�ĸ߶��Ƿ��̾����Ƿ����
			case left_higher:
				sub_root->set_balance(equal_height);
				//��P403�����2���ýڵ�ĸ߶ȼ���
				//������Ҫ��������
				return true;
			case equal_height:
				sub_root->set_balance(right_higher);
				//��P403�����1���ýڵ�ĸ߶Ȳ�δ�ı�
				//�����������
				return false;
				//�����������ߵ�����¼����������ĸ߶�
			case right_higher:
				auto temp = sub_root->right;
				switch (temp->get_balance()) {
					//���3a
				case equal_height:
					temp->set_balance(left_higher);
					rotate_left(sub_root);
					//������ڵ�ĸ߶�δ��
					return false;
					//���3b
				case right_higher:
					sub_root->set_balance(equal_height);
					temp->set_balance(equal_height);
					rotate_left(sub_root);
					//�߶ȼ�1
					return true;
					//���3c
				case left_higher:
					auto temp_left = temp->left;
					//RL��ת
					//�߶ȼ�1			
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
	//��ɾ��֮����е���
	template<typename BinaryEntry>
	bool AVLTree<BinaryEntry>::avl_remove_right
	(BinaryNode<BinaryEntry> *&sub_root, const BinaryEntry &item)
	{
		bool shorter = avl_remove(sub_root->right, item);
		if (shorter == true)
			switch (sub_root->get_balance()) {
				//����ɾ����ڵ�ĸ߶��Ƿ��̾����Ƿ����
			case equal_height:
				sub_root->set_balance(left_higher);
				//��P403�����1���ýڵ�ĸ߶Ȳ�δ�ı�
				//�����������
				return false;
			case right_higher:
				sub_root->set_balance(equal_height);
				//��P403�����2���ýڵ�ĸ߶ȼ���
				//������Ҫ��������				
				return true;
				//�����������ߵ�����¼����������ĸ߶�
			case left_higher:
				auto temp = sub_root->left;
				switch (temp->get_balance()) {
					//���3a
				case equal_height:
					rotate_right(sub_root);
					temp->set_balance(right_higher);
					//������ڵ�ĸ߶�δ��
					return false;
					//���3b			
				case left_higher:
					rotate_right(sub_root);
					//�߶ȼ�1
					sub_root->set_balance(equal_height);
					temp->set_balance(equal_height);
					return true;
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
					return true;
				}
			}
	}
}