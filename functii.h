#ifndef FUNCTII_H
#define FUNCTII_H
#include "structuri.h"

Node *createNode(Team *team);
void addTeamToBack(Node **head, Team *team);
Node *readTeams(FILE *in);
void freeList(Node *head);
void enqueue(Queue *queue, Team *team);
Team *dequeue(Queue *queue);
int isEmptyQueue(Queue *queue);
void formMatches(Node *teamList, Queue *queue);
void processMatches(Queue *queue, Queue *losers, Queue *winners, int **adj_matrix);
double calculate_P_r(double q, int r, int l);


#endif // FUNCTII_H