#include "DirectedGraph.h"

DirectedGraph::DirectedGraph(Edge *edges, int size) {
    for (int i = 0; i < size; i++) {
        int src = edges[i].src, dest = edges[i].dest;
        if (nodes.count(src) == 0) {
            nodes[src] = new SingleLinkedList<int>();
        }
        nodes[src]->add(dest);
        if (nodes.count(dest) == 0) {
            nodes[dest] = new SingleLinkedList<int>();
        }
    }
}

DirectedGraph::~DirectedGraph() {
    for (auto it = nodes.begin(); it != nodes.end(); it++) {
        delete (*it).second;
    }
}

void DirectedGraph::printGraph() {
    for (auto it = nodes.begin(); it != nodes.end(); it++) {
        printf("node(%d) has edges: ", (*it).first);
        for (auto itl = (*it).second->begin(); itl != (*it).second->end(); itl++) {
            printf("%d ", (*itl));
        }
        printf("\n");
    }
}

// https://www.geeksforgeeks.org/cpp-program-for-topological-sorting/
// used this link as a reference for this function
void DirectedGraph::topologySort(int val, LinkedStack<int> &sorted, set<int> &visited) {
    visited.insert(val);
    if (nodes.at(val) == nullptr) {
        return;
    }
    for (SingleLinkedList<int>::Iterator it = nodes.at(val)->begin(); it != nodes.at(val)->end(); it++) {
        if (!visited.count(*it)) {
            topologySort(*it, sorted, visited);
        }
    }
    sorted.push(val);
}

vector<int> *DirectedGraph::topologySort() {
    set<int> visited;
    LinkedStack<int> sorted;
    for (map<int, SingleLinkedList<int> *>::iterator it = nodes.begin(); it != nodes.end(); it++) {
        if (!visited.count(it->first)) {
            topologySort(it->first, sorted, visited);
        }
    }
    vector<int>* ans = new vector<int>();
    while (!sorted.isEmpty()) {
        ans->push_back(sorted.peek());
        sorted.pop();
    }
    return ans;
}

