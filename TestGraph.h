#ifndef TESTGRAPH_H
#define TESTGRAPH_H

#include "D:/code/test1/test1/TestStack.h"
#include "D:/code/test1/test1/TsetQueue.h"
#include "D:/code/test1/test1/TestList.h"
#include <map>
#include <set>
namespace tsetgraph {

	using tsetstack::NodeStack;
	using tsetqueue::NodeQueue;
	using testlist::List;
	using std::map;
	using std::set;

	//Ĭ��ģ�����ֻ��������ģ�����������
	template<typename Vertex=int>
	class Graph {
	public:
		Graph();
		//void read();
		//void write();
		int size();
		void depth_sort();
		void breadth_sort();
	private:
		//�ڽӱ�
		map<Vertex, List<Vertex>> neighbors;//Vertex�����ܹ��Ƚ�	
		//��Աģ��
		template<typename TestSTL>
		void assistant_travel(TestSTL& s1);
		template<typename TestSTL>
		void assistant_travers(set<Vertex>& visited, TestSTL& s1);
	};
	//���ڱ�������ʵ����ģ��ʱ��Ҫ���ն���
	//��ģ����Ķ������������һ�����ͷ�ļ�ʱ���������.cpp�ļ�ʹ��ʱֻ��Ҫinclude��Ӧ��.h�ļ�
	//����������.cpp�ļ��У�ʹ��ʱ��Ҫinclude��Ӧ��.cpp�ļ�
	template<typename Vertex>
	Graph<Vertex>::Graph()
	{
		/*
		cout << "set the graph_size" << endl;
		cin >> graph_size;
		for (int i = 0;i < graph_size;++i) {			
		}
		*/		
		Vertex v = 0;
		List<Vertex> l1;
		//ͨ������ÿ���ڵ����ڵĽڵ�����ʼ��ͼ
		l1.insert(0, 1);
		//��Ҫʹ���Զ���Ŀ������캯��������ʹ�úϳɵĿ������캯��;
		//�ϳɿ������캯��ֻ�Ḵ��ͷָ�룬��û�и��ƽڵ������
		neighbors.insert({ v,l1 });
		l1.clear();
		v = 1;
		l1.insert(0, 0);
		l1.insert(1, 2);
		neighbors.insert({ v,l1 });
		l1.clear();
		v = 2;
		l1.insert(0, 1);
		l1.insert(1, 3);
		neighbors.insert({ v,l1 });
		l1.clear();
		v = 3;
		l1.insert(0, 2);
		l1.insert(1, 4);
		l1.insert(2, 5);
		neighbors.insert({ v,l1 });
		l1.clear();
		v = 4;
		l1.insert(0, 3);
		l1.insert(1, 5);
		neighbors.insert({ v,l1 });
		l1.clear();
		v = 5;
		l1.insert(0, 3);
		l1.insert(1, 4);
		neighbors.insert({ v,l1 });
	}
	template<typename Vertex>
	int Graph<Vertex>::size()
	{
		return neighbors.size();
	}
	//��Ⱥ͹�ȱ�������������ʵ�ֻ�������ݽṹ��ͬ
	template<typename Vertex>
	void Graph<Vertex>::depth_sort()
	{
		NodeStack<Vertex> s1;
		assistant_travel(s1);
	}
	template<typename Vertex>
	void Graph<Vertex>::breadth_sort()
	{
		NodeQueue<Vertex> q1;
		assistant_travel(q1);
	}
	template<typename Vertex>
	template<typename TestSTL>//����ģ��ͨ��ʵ��ȷ��ģ��ʵ��
	void Graph<Vertex>::assistant_travel(TestSTL& s1)
	{
		set<Vertex> visited;
		auto map_iter = neighbors.cbegin();
		auto end_iter = neighbors.cend();
		//�������нڵ�
		while (map_iter != end_iter) {
			//����ȷ���ýڵ�û�б�������
			while (visited.find(map_iter->first) != visited.end()) {
				++map_iter;
				if (map_iter == end_iter)	
				  return;//��ֹmap_iter����end_iterʱ��������find
			}					
			//����ýڵ����ڵ�Ԫ�ؼ����ջ
			int size = map_iter->second.size();
			Vertex v;
			for (int i = 0;i < size;++i) {
				map_iter->second.retrieve(i, v);
				//ȷ�������ջ�Ľڵ㶼��δ��������
				//��Ҫ�ȶ�insert��pop��find֮��ĸ��Ӷ�
				//if(visited.find(v) == visited.end())
				s1.push(v);
			}
			//����Ѿ��������Ľڵ�
			auto ret = visited.insert(map_iter->first);
			//ȷ������ɹ�
			if (!ret.second) {
				cout << "Error:" << __FILE__ << ": in function "
					<< __func__ << " at line " << __LINE__ << endl
					<< "fail when set insert" << endl;
				return;
			}
			cout << map_iter->first << endl;
			++map_iter;
			assistant_travers(visited, s1);
		}
	}
	template<typename Vertex>
	template<typename TestSTL>
	void Graph<Vertex>::assistant_travers(set<Vertex>& visited, TestSTL& s1)
	{
		Vertex v;
		//if(!s1.empty()) s1.pop(v);	
				
		while(!s1.empty()) {
			s1.pop(v);
			cout << "yes" << endl;
			//�ҳ�δ���������ڽӵ�
			while (visited.find(v) != visited.end()) {
				if (s1.empty()) return;
				else            s1.pop(v);
			}
			//���������ڵĽڵ�����ջ
			auto iter = neighbors.find(v);
			int size = iter->second.size();
			for (int i = 0;i < size;++i) {
				iter->second.retrieve(i, v);
				s1.push(v);
			}
			//����Ѿ��������Ľڵ�
			auto ret = visited.insert(iter->first);
			//ȷ������ɹ�
			if (!ret.second) {
				cout << "Error:" << __FILE__ << ": in function "
					<< __func__ << " at line " << __LINE__ << endl
					<< "fail when set insert" << endl;
				return;
			}
			cout << "assistant: " << iter->first << endl;
		}
				 		
	}

}//namespace tsetgraph
#endif
#pragma once
