#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "functii.h"

int main(int argc, char *argv[])
{
    FILE *in = fopen(argv[1], "r");
    FILE *out_graf = fopen(argv[2], "w");
    FILE *out_score;

    Node *teamList = readTeams(in);

    Queue matchQueue = {NULL, NULL};
    Queue winnersStack = {NULL, NULL};
    Queue losersStack = {NULL, NULL};

    int **adj_matrix = (int **)calloc(NO_TEAMS, sizeof(int *));
    for (int i = 0; i < NO_TEAMS; i++) {
        adj_matrix[i] = (int *)calloc(NO_TEAMS, sizeof(int));
    }

    formMatches(teamList, &matchQueue);

    while (matchQueue.front != NULL && matchQueue.front->next != NULL)
    {
        processMatches(&matchQueue, &losersStack, &winnersStack, adj_matrix);
    }

    for (int i = 0; i < NO_TEAMS; i++) {
        for (int j = 0; j < NO_TEAMS; j++) {
            fprintf(out_graf, "%d ", adj_matrix[i][j]);
        }
        fprintf(out_graf, "\n");
        free(adj_matrix[i]);
    }
    free(adj_matrix);
    fclose(in);
    fclose(out_graf);

    out_score = fopen(argv[3], "w");
    double p_r, q = 0.15;
    while(!isEmptyQueue(&losersStack)) {
        Team *loser = dequeue(&losersStack);
        p_r = calculate_P_r(q, loser->wins, NO_ROUNDS + 1);
        fprintf(out_score, "%.4lf %s\n", p_r, loser->name);
    }

    while (!isEmptyQueue(&matchQueue)) {
        Team *winner = dequeue(&matchQueue);
        p_r = calculate_P_r(q, winner->wins, NO_ROUNDS + 1);
        fprintf(out_score, "%.4lf %s\n", p_r, winner->name);
    }
    fclose(out_score);

    free(teamList);

    return 0;
}