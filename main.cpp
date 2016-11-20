#include <iostream>
struct Edge {
    int node1;
    int node2;
    int cost = -1;
};

int total_edges_count, nodes_count, separator, prescribed_cross_river_count, non_river_edges_count, river_edges_count;
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

void k_subset_successor(int *cur, int n, int k) {

    int i = k;
    while(i>=1 && cur[i-1]==n-k+i) i--;
    int c = cur[i-1];
    for(int j=i; j<=k; j++) {
        cur[j-1] = c+1+j-i;
    }

}

int min(int a, int b)
{
    return (a<b)? a: b;
}

// uses: http://www.geeksforgeeks.org/dynamic-programming-set-9-binomial-coefficient/
int binomial_coef(int n, int k) {
    int C[n+1][k+1];
    int i, j;

    // Caculate value of Binomial Coefficient in bottom up manner
    for (i = 0; i <= n; i++) {
        for (j = 0; j <= min(i, k); j++) {
            // Base Cases
            if (j == 0 || j == i) {
                C[i][j] = 1;
            }
                // Calculate value using previosly stored values
            else {
                C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
            }
        }
    }

    return C[n][k];
}


int main() {

    std::cin >> total_edges_count;
    std::cin >> nodes_count;
    std::cin >> separator;
    std::cin >> prescribed_cross_river_count;

    edges = new Edge[total_edges_count];
    crossriver_edges = new Edge[total_edges_count];
    nodes = new int[nodes_count];

    int same_bank_count = 0;
    int crossriver_count = 0;
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
            crossriver_count++;
        }

    }

    while(edges[non_river_edges_count].cost != -1) {
        non_river_edges_count++;
    }
    river_edges_count = total_edges_count - non_river_edges_count;
    sort_by_cost(edges, non_river_edges_count);


    // build every combination of edges cross river
    int *coords = new int[prescribed_cross_river_count];
    for(int i = 0; i<prescribed_cross_river_count; i++) {
        coords[i] = i+1;
    }


    for(int i = binomial_coef(river_edges_count, prescribed_cross_river_count); i>1; i--) {

        k_subset_successor(coords,river_edges_count,prescribed_cross_river_count);


    }




    delete edges;
    delete crossriver_edges;
    delete nodes;
    delete [] coords;




    return 0;
}