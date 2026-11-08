#include <stdio.h>
#define MAX 20

int main() {
    int n, m, i, j, k;
    int trans[MAX][MAX], final[MAX];
    int group[MAX], newGroup[MAX];
    int changed, groups = 0;

    printf("Enter number of states: ");
    scanf("%d", &n);

    printf("Enter number of input symbols: ");
    scanf("%d", &m);

    printf("Enter transition table:\n");
    for (i = 0; i < n; i++) {
        printf("State %d: ", i);
        for (j = 0; j < m; j++)
            scanf("%d", &trans[i][j]);
    }

    printf("Enter number of final states: ");
    scanf("%d", &k);

    for (i = 0; i < n; i++)
        final[i] = 0;

    printf("Enter final states:\n");
    for (i = 0; i < k; i++) {
        int s;
        scanf("%d", &s);
        final[s] = 1;
    }

    // Initial partition: final and non-final states
    for (i = 0; i < n; i++)
        group[i] = final[i];

    // Refine partitions until no change occurs
    do {
        changed = 0;
        groups = 0;

        for (i = 0; i < n; i++) {
            int found = 0;

            for (j = 0; j < i; j++) {
                if (group[i] != group[j])
                    continue;

                for (k = 0; k < m; k++) {
                    if (group[trans[i][k]] != group[trans[j][k]])
                        break;
                }

                if (k == m) {
                    newGroup[i] = newGroup[j];
                    found = 1;
                    break;
                }
            }

            if (!found)
                newGroup[i] = groups++;
        }

        for (i = 0; i < n; i++) {
            if (group[i] != newGroup[i])
                changed = 1;
        }

        for (i = 0; i < n; i++)
            group[i] = newGroup[i];

    } while (changed);

    // Count final groups
    groups = 0;
    for (i = 0; i < n; i++)
        if (group[i] + 1 > groups)
            groups = group[i] + 1;

    printf("\nMinimized DFA:\n");
    printf("Number of states: %d\n", groups);

    printf("\nEquivalent States:\n");
    for (i = 0; i < groups; i++) {
        printf("S%d = { ", i);
        int first = 1;
        for (j = 0; j < n; j++) {
            if (group[j] == i) {
                if (!first)
                    printf(", ");
                printf("q%d", j);
                first = 0;
            }
        }
        printf(" }\n");
    }

    printf("\nMinimized Transition Table:\n\n");
    printf("State\t");
    for (j = 0; j < m; j++)
        printf("sym%d\t", j);
    printf("\n");

    for (i = 0; i < groups; i++) {
        printf("S%d\t", i);
        for (j = 0; j < m; j++) {
            for (k = 0; k < n; k++) {
                if (group[k] == i)
                    break;
            }
            printf("S%d\t", group[trans[k][j]]);
        }
        printf("\n");
    }

    printf("\nFinal States: ");
    for (i = 0; i < groups; i++) {
        for (j = 0; j < n; j++) {
            if (group[j] == i && final[j]) {
                printf("S%d ", i);
                break;
            }
        }
    }
    printf("\n");

    return 0;
}



output


enter no of states:5
enter no of symbols:2
enter the transition table:
s0 1 2
s1 3 4
s2 3 4
s3 3 4
s4 4 4
enter the no of final states:1
the final states are :
3
minimized dfa
no of states: 4equivalent state
s0 = {s0}
s1 = {s1, s2}
s2 = {s3}
s3 = {s4}
min trans table
state   s0      s1
s0      s1      s1
s1      s2      s3
s2      s2      s3
s3      s3      s3

final states s2
