#include <stdio.h>

int n;                    /* number of states */
int eps[20][20] = {0};    /* eps[i][j] = 1 if there is an ε-edge i -> j */
int visited[20];          /* visited[j] = 1 if j is in the current closure */

void dfs(int cur) {
    visited[cur] = 1;

    for (int next = 0; next < n; next++) {
        if (eps[cur][next] && !visited[next])
            dfs(next);
    }
}

int main() {
    int num_trans, u, v;
    char symbol;

    printf("Enter the number of states: ");
    scanf("%d", &n);

    printf("Enter the total number of transitions: ");
    scanf("%d", &num_trans);

    printf("Enter transitions (from_state symbol to_state, 'e' for epsilon):\n");
    for (int i = 0; i < num_trans; i++) {
        scanf("%d %c %d", &u, &symbol, &v);
        if (symbol == 'e')
            eps[u][v] = 1;
    }

    printf("\nEpsilon closures:\n");
    for (int s = 0; s < n; s++) {

        /* clear the marks left over from the previous state */
        for (int i = 0; i < n; i++)
            visited[i] = 0;

        dfs(s);

        printf("ε-closure(q%d) = { ", s);
        for (int i = 0; i < n; i++)
            if (visited[i])
                printf("q%d ", i);
        printf("}\n");
    }

    return 0;
}






output

Enter the number of states: 3
Enter the total number of transitions: 4
Enter transitions (from_state symbol to_state, 'e' for epsilon):
0 e 1
1 e 2
2 a 2
2 b 1

Epsilon closures:
ε-closure(q0) = { q0 q1 q2 }
ε-closure(q1) = { q1 q2 }
ε-closure(q2) = { q2 }
