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

	//默认模板参数只能用于类模板的声明或定义
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
		//邻接表
		map<Vertex, List<Vertex>> neighbors;//Vertex必须能够比较	
		//成员模板
		template<typename TestSTL>
		void assistant_travel(TestSTL& s1);
		template<typename TestSTL>
		void assistant_travers(set<Vertex>& visited, TestSTL& s1);
	};
	//由于编译器在实例化模板时需要掌握定义
	//当模板类的定义和声明建议一起放在头文件时，在另外的.cpp文件使用时只需要include对应的.h文件
	//如果定义放在.cpp文件中，使用时需要include对应的.cpp文件
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
		//通过设置每个节点相邻的节点来初始化图
		l1.insert(0, 1);
		//需要使用自定义的拷贝构造函数，不能使用合成的拷贝构造函数;
		//合成拷贝构造函数只会复制头指针，并没有复制节点的内容
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
	//深度和广度遍历的区别在于实现缓存的数据结构不同
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
	template<typename TestSTL>//函数模板通过实参确定模板实参
	void Graph<Vertex>::assistant_travel(TestSTL& s1)
	{
		set<Vertex> visited;
		auto map_iter = neighbors.cbegin();
		auto end_iter = neighbors.cend();
		//遍历所有节点
		while (map_iter != end_iter) {
			//首先确定该节点没有被遍历过
			while (visited.find(map_iter->first) != visited.end()) {
				++map_iter;
				if (map_iter == end_iter)	
				  return;//防止map_iter等于end_iter时继续进行find
			}					
			//将与该节点相邻的元素加入堆栈
			int size = map_iter->second.size();
			Vertex v;
			for (int i = 0;i < size;++i) {
				map_iter->second.retrieve(i, v);
				//确保加入堆栈的节点都是未遍历过的
				//需要比对insert和pop的find之间的复杂度
				//if(visited.find(v) == visited.end())
				s1.push(v);
			}
			//标记已经遍历过的节点
			auto ret = visited.insert(map_iter->first);
			//确定插入成功
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
			//找出未被遍历的邻接点
			while (visited.find(v) != visited.end()) {
				if (s1.empty()) return;
				else            s1.pop(v);
			}
			//将与其相邻的节点加入堆栈
			auto iter = neighbors.find(v);
			int size = iter->second.size();
			for (int i = 0;i < size;++i) {
				iter->second.retrieve(i, v);
				s1.push(v);
			}
			//标记已经遍历过的节点
			auto ret = visited.insert(iter->first);
			//确定插入成功
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
