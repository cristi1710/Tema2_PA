#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "functii.h"

Node *createNode(Team *team)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->team = team;
    newNode->next = NULL;
    return newNode;
}

void addTeamToBack(Node **head, Team *team)
{
    Node *newNode = createNode(team);
    if (*head == NULL) {
        *head = newNode;
    } else {
        Node *temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

Node *readTeams(FILE *in)
{
    int i;
    Node *teamList = NULL;

    for (i = 0; i < NO_TEAMS; i++)
    {
        Team *team = (Team *)malloc(sizeof(Team));
        team->name = (char *)malloc(100 * sizeof(char));
        fscanf(in, "%f", &team->total_score);
        fgetc(in); // Consum spatiul inainte de nume
        fgets(team->name, 100, in);
        team->name[strlen(team->name) - 1] = '\0'; // elimin caracterul '\n'
        team->wins = 0;
        team->team_index = i;

        addTeamToBack(&teamList, team);
    }
    return teamList;
}

void freeList(Node *head)
{
    Node *temp;
    while (head != NULL)
    {
        temp = head;
        free(temp->team->name);
        free(temp->team);
        free(temp);
        head = head->next;
    }
}

// Implementare a cozii (Queue)
void enqueue(Queue *queue, Team *team)
{
    QueueNode *newNode = (QueueNode *)malloc(sizeof(QueueNode));
    newNode->team = team;
    newNode->next = NULL;
    if (queue->rear == NULL)
    {
        queue->front = newNode;
        queue->rear = newNode;
    }
    else
    {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
}

Team *dequeue(Queue *queue)
{
    if (queue->front == NULL)
    {
        return NULL;
    }
    QueueNode *temp = queue->front;
    Team *team = temp->team;
    queue->front = queue->front->next;
    if (queue->front == NULL)
    {
        queue->rear = NULL;
    }
    free(temp);
    return team;
}

int isEmptyQueue(Queue *queue)
{
    return queue->front == NULL;
}

void formMatches(Node *teamList, Queue *queue)
{
    Node *current = teamList;
    while (current != NULL && current->next != NULL)
    {
        enqueue(queue, current->team);
        enqueue(queue, current->next->team);
        current = current->next->next;
    }
}

void processMatches(Queue *queue, Queue *losers, Queue *winners, int **adj_matrix)
{

    while (!isEmptyQueue(queue))
    {
        Team *team1 = dequeue(queue);
        Team *team2 = dequeue(queue);
        Team *winner, *loser;
        if (team1->total_score > team2->total_score)
        {
            winner = team1;
            loser = team2;
        }
        else if (team1->total_score == team2->total_score)
        {
            if (strcmp(team1->name, team2->name) > 0)
            {
                winner = team1;
                loser = team2;
            }
            else
            {
                winner = team2;
                loser = team1;
            }
        }
        else {
            winner = team2;
            loser = team1;
        }
        winner->wins++;
        adj_matrix[loser->team_index][winner->team_index] = 1; 
        enqueue(winners, winner);
        enqueue(losers, loser);
    }
    
    while (!isEmptyQueue(winners))
    {
        Team *team = dequeue(winners);
        enqueue(queue, team);
    }
}

double calculate_P_r(double q, int r, int l) {
    double numerator = q * pow((2 - q), r);
    double denominator = pow(2, l) + pow((2 - q), l) * (q - 1);
    return numerator / denominator;
}