#include <iostream>
struct Edge {
    int node1;
    int node2;
    int cost = -1;
};

int total_edges_count, nodes_count, separator, prescribed_cross_river_count, non_river_edges_count;
Edge *edges;
Edge *crossriver_edges;
int *nodes;

bool is_same_bank(int a, int b) {
    return (a<=separator && b<=separator) || (a>separator && b>separator);
}

void sort_by_cost(Edge *edges, int size) {

    for(int i=0; i<size-1; i++) {
        for(int j=0; j<size-i-1; j++) {
            if(edges[j+1].cost < edges[j].cost) {
                Edge tmp = edges[j+1];
                edges[j+1] = edges[j];
                edges[j] = tmp;
            }
        }
    }

}


int main() {

    std::cin >> total_edges_count;
    std::cin >> nodes_count;
    std::cin >> separator;
    std::cin >> prescribed_cross_river_count;

    edges = new Edge[total_edges_count];
    crossriver_edges = new Edge[total_edges_count];
    nodes = new int[nodes_count];

    int same_bank_count,crossriver_count;
    for(int i=0; i<total_edges_count; i++) {

        int start, finish, cost;
        std::cin >> start;
        std::cin >> finish;
        std::cin >> cost;

        if(is_same_bank(start,finish)) {
            edges[same_bank_count].node1 = start;
            edges[same_bank_count].node2 = finish;
            edges[same_bank_count].cost = cost;
            same_bank_count++;
        } else {
            crossriver_edges[crossriver_count].node1 = start;
            crossriver_edges[crossriver_count].node2 = finish;
            crossriver_edges[crossriver_count].cost = cost;
        }

    }

    while(edges[non_river_edges_count].cost != -1) {
        non_river_edges_count++;
    }



    int i = 0;
    while(edges[i].cost != -1) {
        std::cout << edges[i].cost << std::endl;
        i++;
    }

    sort_by_cost(edges, non_river_edges_count);

    std::cout << std::endl;
    i = 0;
    while(edges[i].cost != -1) {
        std::cout << edges[i].cost << std::endl;
        i++;
    }


    delete edges;
    delete crossriver_edges;
    delete nodes;

    return 0;
}