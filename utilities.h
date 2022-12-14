#ifndef _UTILITIES_H
#define _UTILITIES_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "node.h"

bool checkNodeID(Log *simList);
void printRep(Log *simList);
void printAllRep(Log *simList, int sim_count);
void stripComment(char buffer[]);
int checkString(char buffer[], int size);
void parseCMDLine(int argc, char argv[]);
int check_columns(char buffer[]);
void printHelp();

bool checkNodeID(Log *simList)
{
    int i = 0;
    size_t len = sizeof(simList);
    for (i; i < len; ++i)
    {
        if (simList[i].start_node)
        {
            return true;
        }
    }
    return false;
}

void printRep(Log *simList)
{
    printf("----------\n");
    printf("Start time: %u\n", simList->start_time);
    printf("Message: %s\n", simList->msg);
    printf("Message ID: %u\n", simList->msg_id);
    printf("Start Node: %u\n", simList->start_node);
    printf("End Node: %u\n", simList->end_node);
    printf("----------\n");

}

void printAllRep(Log *simList, int sim_count)
{
    int i = 0;

    for (i; i < sim_count; ++i)
    {
        printRep(&simList[i]);
    }
}

// Remove comments denoted by '#'
void stripComment(char buffer[])
{
    char COMMENT_MARKER = '#'; //
    char *comment = strchr(buffer, COMMENT_MARKER);

    if (comment != NULL)
    {
        size_t len = strlen(comment);
        memset(comment, '\0', len);
    }
}
// Check buffer size
int checkString(char buffer[], int size)
{
    int buffLen = (int)strlen(buffer) - size;

    if (buffLen <= 0)
    {
        buffer = 0;
    }
    else
    {
        printf("Your input is %d over the maximum size of %d\n", buffLen, size);
    }
    return buffLen;
}
// Ensure correct amount of command line arguments are passed
void parseCMDLine(int argc, char *argv)
{
    if (argc == 1)
    {
        printf("Too few arguments\n");
        printHelp();
        exit(1);
    }
    else if (argc == 3 || argc == 5)
    {
        return;
    }
    else if (argc > 5)
    {
        printf("Error: too many arguments.\n");
        printHelp();
        exit(1);
    }
}

void printHelp()
{
    printf("Usage: rns.exe [-h help] [-n file input] [-s .sim file]\n");
    printf("Example: rns.exe -n basic.ntwk -s simple.sim\n");
}

int check_columns(char buffer[])
{
    size_t len = strlen(buffer);
    int i;
    int columns = 0;
    for (i = 0; i < len; i++)
    {
        if (buffer[i] == ',')
        {
            columns += 1;
        }
        else if (buffer[i] == NULL)
        {
            break;
        }
    }
    return columns;
}

#endif