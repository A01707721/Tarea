
#ifndef Graph_H_
#define Graph_H_

#include <string>
#include <stdio.h>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <algorithm>

using namespace std;


class Graph {
private:
		int edgesList;
		int edgesMat;
		int nodes;
    vector<int> *adjList;
		int *adjMatrix;

public:
		Graph(int);
		Graph();
		void addEdgeAdjList(int, int);
		void addEdgeAdjMatrix(int, int);
		string printAdjList();
		string printAdjMat();
		string printAdjMat_clean();
		string DFS(int, int);
		string depthHelper(int, int, stack<int>&, list<int>&, vector<vector<int>>&);
		string BFS(int, int);
		string breadthHelper(int, int, queue<int>&, list<int>&, vector<vector<int>>&);
		string print_visited(list<int>);
		string print_path(vector<vector<int>>&,int ,int);
		bool contains(list<int>, int);
		void sortAdjList();
		void loadGraphList(string, int);
		void loadGraphMat(string, int, int);
};


void Graph::loadGraphList(string name, int a){
	adjList = new vector<int>[a];
	nodes = a;
	int u, v;
    for(int i=0; i < name.length(); i=i+6){
		u = stoi(name.substr(i+1,1));
		v = stoi(name.substr(i+3,1));
		addEdgeAdjList(u,v);
    }
	sortAdjList();
}

void Graph::loadGraphMat(string name, int a, int b){
	adjMatrix = new int [a*b];
	nodes = a;
	for (int i = 0; i < a*b; i++)
		adjMatrix[i] = 0;
		int u, v;
		for(int j=0; j<name.length(); j=j+6){
            u = stoi(name.substr(j+1,1));
			v = stoi(name.substr(j+3,1));
			addEdgeAdjMatrix(u,v);
        }
				
}

Graph::Graph() {
	edgesList = edgesMat = 0;
}

Graph::Graph(int n) {
	nodes = n;
	adjList = new vector<int>[nodes];
	adjMatrix = new int [nodes*nodes];
	for (int i = 0; i < nodes*nodes; i++)
		adjMatrix[i] = 0;
	edgesList = edgesMat = 0;
}

void Graph::addEdgeAdjList(int u, int v){
	adjList[u].push_back(v);
	adjList[v].push_back(u);
	edgesList++;
}

void Graph::addEdgeAdjMatrix(int u, int v){
	adjMatrix[u*nodes+v] = 1;
	adjMatrix[v*nodes+u] = 1;
	edgesMat++;
}

string Graph::printAdjList(){
	  stringstream aux;
		for (int i = 0; i < nodes; i++){
	        aux << "vertex "
	             << i << " :";
	        for (int j = 0; j < adjList[i].size(); j ++){
							 aux << " " << adjList[i][j];
					}
	        aux << " ";
    }
		return aux.str();

}

void Graph::sortAdjList(){
	for (int i = 0; i < nodes; i++)
		sort(adjList[i].begin(),adjList[i].end());
}

string Graph::printAdjMat(){
	stringstream aux;
	for (int i = 0; i < nodes; i++){
	   for (int j = 0; j < nodes; j++){
			 aux << adjMatrix[i*nodes+j] << " ";
		 }
  }
	return aux.str();
}

string Graph::printAdjMat_clean(){
	stringstream aux;
	aux << "\n nodes \t|";
	for (int i = 0; i < nodes; i++){
			aux << "\t" << i ;
	}
	aux << "\n";
	for (int i = 0; i < nodes; i++){
			aux << "__________";
	}
	aux << "\n";
	for (int i = 0; i < nodes; i++){
		 aux << i << "\t|";
	   for (int j = 0; j < nodes; j++){
			 aux << "\t" << adjMatrix[i*nodes+j];
		 }
	   aux << "\n";
  }
	return aux.str();
}

string Graph::DFS(int start, int goal) {
    stack<int> st;
    list<int> visited;
    vector<vector<int>> paths(nodes, vector<int>(1, -1));
    st.push(start);

    string answer = depthHelper(start, goal, st, visited, paths);
    if (answer != "node not found") {
        answer = answer + print_path(paths, start, goal);
    }
    return answer;
}

string Graph::depthHelper(int current, int goal, stack<int> &st, list<int> &visited, vector<vector<int>> &paths) {
    if (current == goal) {
        return print_visited(visited);
    } 
    if (st.empty()) {
        return "node not found";
    }
    else{
        current = st.top();
        st.pop();
        if (!contains(visited, current)) {
            visited.push_back(current);
            for (int i = 0; i < adjList[current].size(); i++) {
                if (!contains(visited, adjList[current][i])){
                st.push(adjList[current][i]);
                paths[adjList[current][i]][0] = current; 
                }
            }
        }
    return depthHelper(current, goal, st, visited, paths);
    }
}

string Graph::BFS(int start, int goal){
	queue<int> qu;
    list<int> visited;
    vector<vector<int>> paths(nodes, vector<int>(1,-1));
    qu.push(start);

    string answer = breadthHelper(start, goal, qu, visited, paths);
    if (answer != "node not found") {
        answer = answer + print_path(paths, start, goal);
    }
    return answer;
}

string Graph::breadthHelper(int current,
															int goal,
															queue<int> &qu,
															list<int> &visited,
															vector<vector<int>> &paths){

	if (current == goal) {
        return print_visited(visited);
    } 
    if (qu.empty()) {
        return "node not found";
    }
    else{
        current = qu.front();
        qu.pop();
        if (!contains(visited, current)) {
            visited.push_back(current);
            for (int i = 0; i < adjList[current].size(); i++) {
                if (!contains(visited, adjList[current][i])){
                qu.push(adjList[current][i]);
                paths[adjList[current][i]][0]=current; 
                }
            }
        }
    return breadthHelper(current, goal, qu, visited, paths);
    }
}


bool Graph::contains(list<int> ls, int node){
		list<int>::iterator it;
		it = find(ls.begin(), ls.end(), node);
		if(it != ls.end())
			return true;
		else
			return false;
}

string Graph::print_visited(list<int> q){
	stringstream aux;
	aux << "visited: ";
	while (!q.empty()){
    aux << q.front() << " ";
    q.pop_front();
    }
	return aux.str();
}

string Graph::print_path(vector<vector <int>> &path, int start, int goal){
	int node =  path[goal][0];
	stack<int> reverse;
	reverse.push(goal);
	stringstream aux;
	aux  << "path:";
	while (node != start) {
		reverse.push(node);
    node = path[node][0];
  }
	reverse.push(start);
	while (!reverse.empty()) {
		aux << " " << reverse.top() ;
		reverse.pop();
  }
	return aux.str();
}
#endif 
