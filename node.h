#ifndef _node_h
#define _node_h
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Node
{
    int nodeID;
    int conCount;
    int *conList;
} Node;

typedef struct simLog
{
    unsigned int start_time;
    char *msg[512];
    unsigned int msg_id;
    unsigned int start_node;
    unsigned int end_node;
    int *simList;
} Log;
typedef struct report
{
    unsigned int start_time;
    char *msg[512];
    unsigned int selected_node;
    int *repList;
} Rep;

void buildNode(Node *nodeList, char buffer[], FILE *fp);
void build_sim(Log *simList, Rep *repList, char buffer[], FILE *sim);
void stripComment(char buffer[]);
int checkString(char buffer[], int size);
void parseCMDLine(int argc, char *argv);
int check_columns(char buffer[]);
void printHelp();

#endif
