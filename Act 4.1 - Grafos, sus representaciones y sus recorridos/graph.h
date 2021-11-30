#ifndef GRAPH_H_
#define GRAPH_H_

#include <string>
#include <cstdio>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <algorithm>

class Graph{
private:
    int edgesList;
    int edgesMat;
    int nodes;
    std::vector<int> *adjList;
    int *adjMatrix;

public:
    Graph();
    void loadGraphMat(const std::string &, int, int);
    void loadGraphList(const std::string &, int, int);
    void addEdgeAdjMatrix(int, int);
    void addEdgeAdjList(int, int);
    std::string printAdjMat();
    std::string printAdjList();
    std::string DFS(int, int);
    std::string BFS(int, int);
    void dfsHelper(int, int, std::stack<int> &, std::list<int> &, std::vector<std::vector<int>> &, std::stringstream &);
    void bfsHelper(int, int, std::queue<int> &, std::list<int> &, std::vector<std::vector<int>> &, std::stringstream &);
    static void printPath(std::vector<std::vector<int>> &, int, int, std::stringstream &);
    static void printVisited(std::list<int>, std::stringstream &);
    static bool contains(std::list<int>, int);
    void sortAdjList();
	
};

Graph::Graph(){
    edgesList = edgesMat = nodes = 0;
    adjList = {};
    adjMatrix = nullptr;
	
}

void Graph::loadGraphMat(const std::string &file_name, int a, int b){
    adjMatrix = new int[a*b];
    nodes = a;
    for(int i = 0; i < a * b; i++){
        adjMatrix[i] = 0;
		
	}
	
    std::string line;
    std::ifstream archivo(file_name);
    int u, v;
    if(archivo.is_open()){
        while(getline(archivo, line)){
            u = stoi(line.substr(1, 1));
            v = stoi(line.substr(4, 1));
            addEdgeAdjMatrix(u, v);
			
        }
		
    }else{
        std::cout << "Can´t open file";
		
    }
}

void Graph::loadGraphList(const std::string &file_name, int a, int b){
    nodes = a;
    adjList = new std::vector<int>[nodes];
    std::string line;
    std::ifstream archivo(file_name);
    int u, v;
    if(archivo.is_open()){
        while(getline(archivo, line)){
            u = stoi(line.substr(1, 1));
            v = stoi(line.substr(4, 1));
            addEdgeAdjList(u, v);
        }
        archivo.close();
		
    }else{
        std::cout << "Can´t open file";
		
    }
}

void Graph::addEdgeAdjMatrix(int u, int v) {
    adjMatrix[u*nodes + v] = 1;
    adjMatrix[v*nodes + u] = 1;
    edgesMat++;
	
}

void Graph::addEdgeAdjList(int u, int v){
    adjList[u].push_back(v);
    adjList[v].push_back(u);
    edgesList++;
	
}

std::string Graph::printAdjList(){
    sortAdjList();
    std::stringstream aux;
    for (int i = 0; i < nodes; i++){
        aux << "vertex " << i << " :";
        for(int j: adjList[i]){
            aux << " " << j;
			
        }
		
        aux << " ";
		
    }
    return aux.str();

}

std::string Graph::printAdjMat() {
    std::stringstream aux;
    for(int i = 0; i < nodes; i++){
        for(int j = 0; j < nodes; j++){
            aux << adjMatrix[i*nodes + j] << " ";
			
        }
    }
    return aux.str();
	
}

std::string Graph::DFS(int start, int target){
    std::stringstream aux;
    std::stack<int> my_stack;
    std::list<int> visited;
    std::vector<std::vector<int>> paths(nodes, std::vector<int>(1, -1));
    my_stack.push(start);
    dfsHelper(start, target, my_stack, visited, paths, aux);
    printPath(paths, start, target, aux);
    return aux.str();
	
}

void Graph::dfsHelper(int current, int target, std::stack<int> &stack, std::list<int> &visited, std::vector<std::vector<int>> &paths, std::stringstream &aux){
    if(current == target){
        printVisited(visited, aux);
		
    }else if(stack.empty()){
        aux << "Can´t found node";
		
    }else{
        current = stack.top();
        stack.pop();
        visited.push_back(current);
        for(int i = 0; i < adjList[current].size(); i++){
            if(!contains(visited, adjList[current][i])){
                stack.push(adjList[current][i]);
                paths[adjList[current][i]][0] = current;
				
            }
        }
        dfsHelper(current, target, stack, visited, paths, aux);
    }
}

std::string Graph::BFS(int start, int target){
    std::stringstream aux;
    std::queue<int> queue;
    std::list<int> visited;
    std::vector<std::vector<int>> paths(nodes, std::vector<int>(0));
    queue.push(start);
    bfsHelper(start, target, queue, visited, paths, aux);
    printPath(paths, start, target, aux);
    return aux.str();
	
}

void Graph::bfsHelper(int current, int target, std::queue<int> &queue, std::list<int> &visited, std::vector<std::vector<int>> &paths, std::stringstream &aux){
    if(current == target){
        printVisited(visited, aux);
		
    }else if(queue.empty()){
        aux << "";
		
    }else{
        current = queue.front();
        queue.pop();
        visited.push_back(current);
        for(int i = 0; i < adjList[current].size(); i++){
            if(!contains(visited, adjList[current][i])){
                queue.push(adjList[current][i]);
                paths[adjList[current][i]].push_back(current);
				
            }
        }
        bfsHelper(current, target, queue, visited, paths, aux);
    }
}

void Graph::printVisited(std::list<int> visited, std::stringstream &aux){
    aux << "visited: ";
    while(!visited.empty()){
        aux << visited.front() << " ";
        visited.pop_front();
		
    }
}

void Graph::printPath(std::vector<std::vector<int>> &path, int start, int target, std::stringstream &aux){
    aux << "path: ";
    int node = path[target][0];
    std::stack<int> reverse;
    reverse.push(target);
    while(node != start){
        reverse.push(node);
        node = path[node][0];
		
    }
    reverse.push(start);
    while(!reverse.empty()){
        aux << reverse.top();
        reverse.pop();
        if(!reverse.empty()){
            aux << " ";
			
		}
		
    }
}

void Graph::sortAdjList(){
    for(int i = 0; i < nodes; i++){
        sort(adjList[i].begin(), adjList[i].end());
		
    }
	
}

bool Graph::contains(std::list<int> lista, int node){
    std::list<int>::iterator it;
    it = find(lista.begin(), lista.end(), node);
    if(it != lista.end()){
        return true;
		
    }else{
        return false;
		
    }
}

#endif