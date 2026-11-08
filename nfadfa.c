#include <stdio.h>

int nfa[20][20][20];
int dfa[50][20];
int dfa_states[50][20];
int n_states, n_symbols, n_dfa = 0;

int is_equal(int a[20], int b[20]) {
    for (int i = 0; i < n_states; i++) {
        if (a[i] != b[i])
            return 0;
    }
    return 1;
}

int find_state(int state[20]) {
    for (int i = 0; i < n_dfa; i++) {
        if (is_equal(dfa_states[i], state))
            return i;
    }
    return -1;
}

/* Converts a 0/1 row into text like "{q0, q1}" */
void set_to_str(int s[20], char *buf) {
    int pos = 0, first = 1;
    pos += sprintf(buf + pos, "{");
    for (int j = 0; j < n_states; j++) {
        if (s[j]) {
            if (!first)
                pos += sprintf(buf + pos, ", ");
            pos += sprintf(buf + pos, "q%d", j);
            first = 0;
        }
    }
    sprintf(buf + pos, "}");
}

int main() {
    printf("Enter number of states in NFA: ");
    scanf("%d", &n_states);

    printf("Enter number of input symbols: ");
    scanf("%d", &n_symbols);

    for (int k = 0; k < n_symbols; k++) {
        printf("Enter transition table for symbol %d (1 if transition exists, 0 otherwise):\n", k);
        for (int i = 0; i < n_states; i++) {
            for (int j = 0; j < n_states; j++) {
                scanf("%d", &nfa[k][i][j]);
            }
        }
    }

    /* Start with {q0} as the first DFA state */
    int start[20] = {0};
    start[0] = 1;
    for (int i = 0; i < n_states; i++)
        dfa_states[0][i] = start[i];
    n_dfa = 1;

    /* Subset construction */
    for (int i = 0; i < n_dfa; i++) {
        for (int k = 0; k < n_symbols; k++) {
            int move[20] = {0};

            for (int j = 0; j < n_states; j++) {
                if (dfa_states[i][j]) {
                    for (int m = 0; m < n_states; m++) {
                        if (nfa[k][j][m])
                            move[m] = 1;
                    }
                }
            }

            int state_idx = find_state(move);
            if (state_idx == -1) {
                for (int m = 0; m < n_states; m++)
                    dfa_states[n_dfa][m] = move[m];
                dfa[i][k] = n_dfa;
                n_dfa++;
            } else {
                dfa[i][k] = state_idx;
            }
        }
    }

    /* Print the table using the actual sets */
    char buf[100];

    printf("\nDFA Transition Table:\n");
    printf("%-20s", "State");
    for (int k = 0; k < n_symbols; k++) {
        char head[20];
        sprintf(head, "Sym%d", k);
        printf("%-20s", head);
    }
    printf("\n");

    for (int i = 0; i < n_dfa; i++) {
        set_to_str(dfa_states[i], buf);
        printf("%-20s", buf);

        for (int k = 0; k < n_symbols; k++) {
            set_to_str(dfa_states[dfa[i][k]], buf);
            printf("%-20s", buf);
        }
        printf("\n");
    }

    return 0;
}


Output

enter the nof of states:3
enter the nof of symbols:2
enter the transition for symbol 0
1 1 0
0 0 0
0 0 0
enter the transition for symbol 1
1 0 0
0 0 1
0 0 0

dfatransition table
state               sym0                sym1
{q0}                {q0, q1}            {q0}
{q0, q1}            {q0, q1}            {q0, q2}
{q0, q2}            {q0, q1}            {q0}
