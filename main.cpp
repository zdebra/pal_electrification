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
int global_comp;

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

void clear_nodes() {
    for(int i=0; i< nodes_count; i++) {
        nodes[i] = 0;
    }
}

/**
 *
 * @return -1 if there is no solution
 */
int find_lowest_price(int start_cost) {
    int cur = start_cost;
    int edges_added = prescribed_cross_river_count;
    for(int i=0;i<non_river_edges_count;i++) {

        Edge e = edges[i];
        int n1 = nodes[e.node1];
        int n2 = nodes[e.node2];

        if(n1 == 0 && n2 == 0) {
            nodes[e.node1] = global_comp;
            nodes[e.node2] = global_comp;
            global_comp++;
            cur += e.cost;
            edges_added++;
        }
        else if(n1 == 0) {
            nodes[e.node1] = nodes[e.node2];
            cur += e.cost;
            edges_added++;
        }
        else if(n2 == 0) {
            nodes[e.node2] = nodes[e.node1];
            cur += e.cost;
            edges_added++;
        }
        else if(n1 != n2) {
            for(int j=0; j < nodes_count; j++) {
                if(nodes[j]==n2) {
                    nodes[j] = n1;
                }
            }
            cur += e.cost;
            edges_added++;
        }


    }

    // check if it is valid solution - edges added must be n-1 where n is nodes count
    if(edges_added != nodes_count-1) {
        return -1;
    }

    return cur;
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


    // cur coords
    int *coords = new int[prescribed_cross_river_count];
    // init cur coords
    for(int i = 0; i<prescribed_cross_river_count; i++) {
        coords[i] = i+1;
    }

    // build every combination of edges cross river
    int iter = binomial_coef(river_edges_count, prescribed_cross_river_count);
    int cur_min = -1;
    do {

        // clear nodes
        clear_nodes();

        // add starting nodes
        int start_cost = 0;
        for(int i=0; i<prescribed_cross_river_count; i++) {
            nodes[crossriver_edges[coords[i]-1].node1] = 1;
            nodes[crossriver_edges[coords[i]-1].node2] = 1;
            start_cost += crossriver_edges[coords[i]-1].cost;
        }
        global_comp = 2;

        // run kruskal algorithm for current nodes
        cur_min = min(cur_min, find_lowest_price(start_cost));

        // compare it with current minimum
        k_subset_successor(coords,river_edges_count,prescribed_cross_river_count);
        iter--;
    } while(iter > 0);

    std::cout << cur_min;


    delete edges;
    delete crossriver_edges;
    delete nodes;
    delete [] coords;




    return 0;
}