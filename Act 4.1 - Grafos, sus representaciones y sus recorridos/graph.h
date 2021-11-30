#ifndef Graph_H_
#define Graph_H_

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

using namespace std;

/**
 * Graph: Incluye la estructura necesaria para ejecutar el main.cpp.
 * @file: graph.h
 * @author: Ian
 */

class Graph {
private:
    int edgesList;
    int edgesMat;
    int nodes;
    vector<int> *adjList;
    int *adjMatrix;

public:

    Graph();

    void loadGraphMat(const string &, int, int);

    void loadGraphList(const string &, int, int);


    void addEdgeAdjMatrix(int, int);

    void addEdgeAdjList(int, int);


    string printAdjMat();

    string printAdjList();


    string DFS(int, int);

    string BFS(int, int);


    void dfsHelper(int, int, stack<int> &, list<int> &, vector<vector<int>> &, stringstream &);

    void bfsHelper(int, int, queue<int> &, list<int> &, vector<vector<int>> &, stringstream &);


    static void printPath(vector<vector<int>> &, int, int, stringstream &);

    static void printVisited(list<int>, stringstream &);


    static bool contains(list<int>, int);

    void sortAdjList();
};

/**
 * @brief Construct a new Graph:: Graph object
 * 
 */
Graph::Graph() {
    edgesList = edgesMat = nodes = 0;
    adjList = {};
    adjMatrix = nullptr;
}

/**
 * @brief Carga el grafo desde un archivo de texto.
 * 
 * @param file_name 
 * @param a 
 * @param b 
 */
void Graph::loadGraphMat(const string &file_name, int a, int b) {
    adjMatrix = new int[a * b];
    nodes = a;
    for (int i = 0; i < a * b; i++)
        adjMatrix[i] = 0;
    string line;
    ifstream archivo(file_name);
    int u, v;
    if (archivo.is_open()) {
        while (getline(archivo, line)) {
            u = stoi(line.substr(1, 1));
            v = stoi(line.substr(4, 1));
            addEdgeAdjMatrix(u, v);
        }
        archivo.close(); // Closes the file
    } else {
        cout << "Unable to open file";
    }
}

/**
 * @brief Carga el grafo desde un archivo de texto.
 * 
 * @param file_name 
 * @param a 
 */
void Graph::loadGraphList(const string &file_name, int a, int b) {
    nodes = a;
    adjList = new vector<int>[nodes];

    string line;
    ifstream archivo(file_name);
    int u, v;
    if (archivo.is_open()) {
        while (getline(archivo, line)) {
            u = stoi(line.substr(1, 1));
            v = stoi(line.substr(4, 1));
            addEdgeAdjList(u, v);
        }
        archivo.close();
    } else {
        cout << "Unable to open file";
    }
}

/**
 * @brief Agrega una arista al grafo (Matriz).
 * 
 * @param u 
 * @param v 
 */
void Graph::addEdgeAdjMatrix(int u, int v) {
    adjMatrix[u * nodes + v] = 1;
    adjMatrix[v * nodes + u] = 1;
    edgesMat++;
}

/**
 * @brief Agrega una arista al grafo (Lista).
 * 
 * @param u 
 * @param v 
 */
void Graph::addEdgeAdjList(int u, int v) {
    adjList[u].push_back(v);
    adjList[v].push_back(u);
    edgesList++;
}

/**
 * @brief Imprime el grafo en forma de lista de adyacencia.
 * 
 * @return string 
 */
string Graph::printAdjList() {
    sortAdjList();
    stringstream aux;
    for (int i = 0; i < nodes; i++) {
        aux << "vertex "
            << i << " :";
        for (int j: adjList[i]) {
            aux << " " << j;
        }
        aux << " ";
    }
    return aux.str();

}

/**
 * @brief Imprime el grafo en forma de matriz de adyacencia.
 * 
 * @return string 
 */
string Graph::printAdjMat() {
    stringstream aux;
    for (int i = 0; i < nodes; i++) {
        for (int j = 0; j < nodes; j++) {
            aux << adjMatrix[i * nodes + j] << " ";
        }
    }
    return aux.str();
}

/**
 * @brief Busca un nodo con el método DFS.
 * 
 * @param start
 * @param target
 * @return string 
 */
string Graph::DFS(int start, int target) {
    stringstream aux;

    stack<int> my_stack;
    list<int> visited;
    vector<vector<int>> paths(nodes, vector<int>(1, -1));
    my_stack.push(start);

    dfsHelper(start, target, my_stack, visited, paths, aux);
    printPath(paths, start, target, aux);

    return aux.str();
}

/**
 * @brief Función de ayuda para la implementación de DFS.
 * 
 * @param current 
 * @param target
 * @param stack
 * @param visited 
 * @param paths 
 * @param aux 
 */
void Graph::dfsHelper(int current, int target, stack<int> &stack, list<int> &visited, vector<vector<int>> &paths,
                      stringstream &aux) {

    if (current == target) {
        printVisited(visited, aux);
    } else if (stack.empty()) {
        aux << "node not found";
    } else {
        current = stack.top();
        stack.pop();
        visited.push_back(current);
        for (int i = 0; i < adjList[current].size(); i++) {
            if (!contains(visited, adjList[current][i])) {
                stack.push(adjList[current][i]);
                paths[adjList[current][i]][0] = current;
            }
        }
        dfsHelper(current, target, stack, visited, paths, aux);
    }
}

/**
 * @brief Busca un nodo con el método BFS.
 * 
 * @param start
 * @param target
 * @return string 
 */
string Graph::BFS(int start, int target) {
    stringstream aux;

    queue<int> queue;
    list<int> visited;
    vector<vector<int>> paths(nodes, vector<int>(0));
    queue.push(start);

    bfsHelper(start, target, queue, visited, paths, aux);
    printPath(paths, start, target, aux);

    return aux.str();
}

/**
 * @brief Función de ayuda para la implementación de BFS.
 * 
 * @param current 
 * @param target
 * @param queue
 * @param visited 
 * @param paths 
 * @param aux 
 */
void Graph::bfsHelper(int current, int target, queue<int> &queue, list<int> &visited, vector<vector<int>> &paths,
                      stringstream &aux) {

    if (current == target) {
        printVisited(visited, aux);
    } else if (queue.empty()) {
        aux << "";
    } else {
        current = queue.front();
        queue.pop();
        visited.push_back(current);
        for (int i = 0; i < adjList[current].size(); i++) {
            if (!contains(visited, adjList[current][i])) {
                queue.push(adjList[current][i]);
                paths[adjList[current][i]].push_back(current);
            }
        }
        bfsHelper(current, target, queue, visited, paths, aux);
    }
}

/**
 * @brief Imprime la lista de nodos visitados.
 * 
 * @param visited 
 * @param aux 
 */
void Graph::printVisited(list<int> visited, stringstream &aux) {
    aux << "visited: ";
    while (!visited.empty()) {
        aux << visited.front() << " ";
        visited.pop_front();
    }
}

/**
 * @brief Imprime el camino de un nodo a otro.
 * 
 * @param path 
 * @param start
 * @param target
 * @param aux 
 */
void Graph::printPath(vector<vector<int>> &path, int start, int target, stringstream &aux) {
    aux << "path: ";
    int node = path[target][0];

    stack<int> reverse;
    reverse.push(target);

    while (node != start) {
        reverse.push(node);
        node = path[node][0];
    }

    reverse.push(start);
    while (!reverse.empty()) {
        aux << reverse.top();
        reverse.pop();
        if (!reverse.empty())
            aux << " ";
    }
}

/**
 * @brief Ordena el grafo en forma de lista de adyacencia.
 * 
 */
void Graph::sortAdjList() {
    for (int i = 0; i < nodes; i++) {
        sort(adjList[i].begin(), adjList[i].end());
    }
}

/**
 * @brief Verifica si el grafo contiene un nodo.
 * 
 * @param lista 
 * @param node 
 * @return true 
 * @return false 
 */
bool Graph::contains(list<int> lista, int node) {
    list<int>::iterator it;
    it = find(lista.begin(), lista.end(), node);

    if (it != lista.end()) {
        return true;
    } else {
        return false;
    }
}

#endif