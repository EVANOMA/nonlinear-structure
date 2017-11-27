#ifndef CIRCLE_H
#define CIRCLE_H

namespace TestBinary {
	//��AVLTree�з���ͳ�ƽڵ�����������ƽ��״��
	enum BalanceFactor :int;
	//���ڵ�
	template<typename BinaryEntry>
	struct BinaryNode {
		BinaryEntry data;
		BinaryNode<BinaryEntry> *left;
		BinaryNode<BinaryEntry> *right;
		BinaryNode();
		BinaryNode(const BinaryEntry &item);
		//������Ҫͨ������ָ���������2�������ຯ��
		//�����������Ϊ���麯�������ǽ�����ֱ�Ӵ������ڵ�
		virtual void set_balance(BalanceFactor b);
		virtual BalanceFactor get_balance()const;
	};
	//������
	template<typename BinaryEntry>
	class BinaryTree {
	public:
		BinaryTree();
		virtual ~BinaryTree();
		//����
		bool empty()const;
		//��������Բ������麯��
		virtual int height()const;
		int count()const;
		int leaf_count()const;//Ҷ�ڵ�ĸ���
	    //�������
		void preorder_traversal(void(*visit)(BinaryEntry &item));
		//�������
		void inorder_traversal(void(*visit)(BinaryEntry &item));
		//�������
		void postorder_traversal(void(*visit)(BinaryEntry &item));
		//�޸�
		void clear();
		virtual void insert(const BinaryEntry &item);
		//���ڶ������Ĳ���û�й��ɣ���Ҫ�����������Ľڵ�Ѱ��
		//��Ҫɾ���Ľڵ㡣ʱ�临�Ӷȸ�
		//�����������ʵ����̳�
	protected:
		BinaryNode<BinaryEntry> *root;
		//������������ֹ�Ӵ���root�ڵ�
		void assistent_clear(BinaryNode<BinaryEntry> *sub_root);
		int assistent_leaf_count(BinaryNode<BinaryEntry> *sub_root)const;
		int assistent_count(BinaryNode<BinaryEntry> *sub_root)const;
		void assistent_insert(BinaryNode<BinaryEntry> *&sub_root, const BinaryEntry &item);
		int assistent_height(BinaryNode<BinaryEntry> *sub_root)const;
		//��������
		void assistent_preorder(BinaryNode<BinaryEntry> *sub_root, void(*visit)(BinaryEntry &item));
		void assistent_inorder(BinaryNode<BinaryEntry> *&sub_root, void(*visit)(BinaryEntry &item));
		void assistent_postorder(BinaryNode<BinaryEntry> *sub_root, void(*visit)(BinaryEntry &item));
	};

	//������������������С�ڵ��ڸ��ڵ㣬���������ڸ��ڵ�
	template<typename BinaryEntry>
	class SearchTree :public BinaryTree<BinaryEntry> {
	public:
		//����SearchTree�������ݳ�Ա
		//�ñ���������ϳɵ�Ĭ�Ϲ������������
		bool tree_search(const BinaryEntry &target)const;
		//����������ظ���Ԫ��
		virtual void insert(const BinaryEntry &item);
		void remove(const BinaryEntry &item);
	private:
		BinaryNode<BinaryEntry>* search_for_node(BinaryNode<BinaryEntry> *sub_root, const BinaryEntry &target)const;
		void search_and_insert(BinaryNode<BinaryEntry> *&sub_root, const BinaryEntry &item);
		void remove_root(BinaryNode<BinaryEntry> *&sub_root);
		void search_and_remove(BinaryNode<BinaryEntry> *sub_root, const BinaryEntry &target);
	};
	//���ʹ��height()�������������������ĸ߶ȵ�ʱ�临�Ӷȸ���
	template<typename BinaryEntry>
	struct AVLNode : public BinaryNode<BinaryEntry> {
		//ö�������޷���Ĭ�ϳ�ʼ��
		BalanceFactor balance;
		//�����޷�ʹ�ü̳й��캯��
		AVLNode();
		AVLNode(const BinaryEntry &item);
		//override����ȷ���Ƿ񸲸ǻ�����麯��
		void set_balance(BalanceFactor b)override;
		BalanceFactor get_balance()const override;
	};
	
	//ƽ��������������ڶ�β����ɾ���󱣳�ÿ���ڵ�����������߶�֮�����1
	template<typename BinaryEntry>
	class AVLTree :public SearchTree<BinaryEntry> {
	public:
		void insert(const BinaryEntry &item)override;
		void remove(const BinaryEntry &item);
		int height()const override;
	private:
		int assistent_height(BinaryNode<BinaryEntry> *sub_root)const;
		//������Ҫ�޸�ƽ������ĺ��������ָ�������������Ⱥ�����
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

