#ifndef CIRCLE_H
#define CIRCLE_H

namespace TestBinary {
	//��AVL_Tree�з���ͳ�ƽڵ�����������ƽ��״��
	//�Ƚ���height()���������ӣ�
	enum Balance_factor :int;
	//���ڵ�
	template<typename Binary_entry>
	struct Binary_Node {
		Binary_entry data;
		Binary_Node<Binary_entry> *left;
		Binary_Node<Binary_entry> *right;
		Binary_Node();
		Binary_Node(const Binary_entry &item);
		//������Ҫͨ������ָ���������2�������ຯ��
		virtual void set_balance(Balance_factor b);
		virtual Balance_factor get_balance()const;
	};
	//������
	template<typename Binary_entry>
	class Binary_Tree {
	public:
		Binary_Tree();
		~Binary_Tree();
		//����
		bool empty()const;
		//��������Բ������麯��
		virtual int height()const;
		int count()const;
		int leaf_count()const;//Ҷ�ڵ�ĸ���
	    //�������
		void preorder_traversal(void(*visit)(Binary_entry &item));
		//�������
		void inorder_traversal(void(*visit)(Binary_entry &item));
		//�������
		void postorder_traversal(void(*visit)(Binary_entry &item));
		//�޸�
		void clear();
		void insert(const Binary_entry &item);
		//�����������ʵ����̳�
	protected:
		Binary_Node<Binary_entry> *root;
		//������������ֹ�Ӵ���root�ڵ�
		void assistent_clear(Binary_Node<Binary_entry> *sub_root);
		int assistent_leaf_count(Binary_Node<Binary_entry> *sub_root)const;
		int assistent_count(Binary_Node<Binary_entry> *sub_root)const;
		void assistent_insert(Binary_Node<Binary_entry> *&sub_root, const Binary_entry &item);
		int assistent_height(Binary_Node<Binary_entry> *sub_root)const;
		//��������
		void assistent_preorder(Binary_Node<Binary_entry> *sub_root, void(*visit)(Binary_entry &item));
		void assistent_inorder(Binary_Node<Binary_entry> *&sub_root, void(*visit)(Binary_entry &item));
		void assistent_postorder(Binary_Node<Binary_entry> *sub_root, void(*visit)(Binary_entry &item));
	};
	enum Error_code :int;

	//������������������С�ڵ��ڸ��ڵ㣬���������ڸ��ڵ�
	template<typename Binary_entry>
	class Search_Tree :public Binary_Tree<Binary_entry> {
	public:
		Error_code tree_search(const Binary_entry &target)const;
		//�������ڻ���ͬ��������void
		virtual Error_code insert(const Binary_entry &item);
		Error_code remove(const Binary_entry &item);
	private:
		Binary_Node<Binary_entry>* search_for_node(Binary_Node<Binary_entry> *sub_root, const Binary_entry &target)const;
		Error_code search_and_insert(Binary_Node<Binary_entry> *&sub_root, const Binary_entry &item);
		Error_code remove_root(Binary_Node<Binary_entry> *&sub_root);
		Error_code search_and_remove(Binary_Node<Binary_entry> *sub_root, const Binary_entry &target);
	};
	//���ʹ��height()�������������������ĸ߶ȵ�ʱ�临�Ӷȸ���
	template<typename Binary_entry>
	struct AVL_Node : public Binary_Node<Binary_entry> {
		//ö�������޷���Ĭ�ϳ�ʼ��
		Balance_factor balance;
		//�����޷�ʹ�ü̳й��캯��
		AVL_Node();
		AVL_Node(const Binary_entry &item);
		//override����ȷ���Ƿ񸲸ǻ�����麯��
		void set_balance(Balance_factor b)override;
		Balance_factor get_balance()const override;
	};
	
	//ƽ��������������ڶ�β����ɾ���󱣳�ÿ���ڵ�����������߶�֮�����1
	template<typename Binary_entry>
	class AVL_Tree :public Search_Tree<Binary_entry> {
	public:
		Error_code insert(const Binary_entry &item)override;
		Error_code remove(const Binary_entry &item);
		int height()const override;
	private:
		int assistent_height(Binary_Node<Binary_entry> *sub_root)const;
		//������Ҫ�޸�ƽ������ĺ��������ָ�������������Ⱥ�����
		Error_code avl_insert(Binary_Node<Binary_entry> *&sub_root,const Binary_entry &item,bool &taller);
		void rotate_left(Binary_Node<Binary_entry> *&sub_root);
		void rotate_right(Binary_Node<Binary_entry> *&sub_root);
		void right_balance(Binary_Node<Binary_entry> *&sub_root);
		void left_balance(Binary_Node<Binary_entry> *&sub_root);
		Error_code avl_remove(Binary_Node<Binary_entry> *&sub_root, const Binary_entry &item, bool &shorter);
		//�����Ƿ����ȡ��ʹ��Error_code��
		Error_code avl_remove_left(Binary_Node<Binary_entry> *&sub_root, const Binary_entry &item, bool &shorter);
		Error_code avl_remove_right(Binary_Node<Binary_entry> *&sub_root, const Binary_entry &item, bool &shorter);
	};
	
	
}
/*

*/

#endif
#pragma once

