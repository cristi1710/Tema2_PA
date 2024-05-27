#ifndef STRUCTURI_H
#define STRUCTURI_H

#define NO_TEAMS 32
#define NO_ROUNDS 5

typedef struct Team
{
    char *name;
    int team_index;
    int wins;
    float total_score;
} Team;

typedef struct Node
{
    Team *team;
    struct Node *next;
} Node;

typedef struct QueueNode{
    Team* team;
    struct QueueNode *next;
} QueueNode;

typedef struct Queue {
    QueueNode *front;
    QueueNode *rear;
} Queue;

#endif // STRUCTURI_H