#include "utilities.h"
#include "node.h"
#define COMMENT_MARKER '#'
#define BUFF_SIZE 1024

void buildNode(Node *nodeList, char buffer[], FILE *fp)
{

    char value[50];
    int i = 0;
    while (!feof(fp))
    {
        // Read in file line by line
        fgets(buffer, BUFF_SIZE, fp);

        // Handle oversized buffer
        checkString(buffer, BUFF_SIZE);

        // Remove comments
        stripComment(buffer);

        // memory address at s is set when ',' is found
        char *s = strchr(buffer, ',');
        if (s != NULL)
        {
            // Scan the buffer to look for comma and if found assign NodeID and connection count to memory address of nodeList[i]
            sscanf(buffer, "%d, %d", &nodeList[i].nodeID, &nodeList[i].conCount);
            printf("Found nodeId: %d\nConnection Count: %d\n", nodeList[i].nodeID, nodeList[i].conCount);
            // dynamically allocate memory for conList
            nodeList->conList = (int *)malloc(sizeof(int) * nodeList[i].conCount);

            // Look through buffer conCount amount of times and assign
            int x, j = 0;
            for (x = 0; x < nodeList->conCount; x++)
            {
                for (j; j < nodeList[i].conCount; j++)
                {

                    fgets(buffer, BUFF_SIZE, fp);
                    if (buffer[0] == COMMENT_MARKER)
                    {
                        j -= 1;
                        continue;
                    }
                    sscanf(buffer, "%d", &nodeList->conList[j]);
                    printf("Connection %d: %d\n", x, nodeList->conList[j]);
                    x++;
                }
            }
        }
        sscanf(buffer, "%s", value);
        if (strcmp(value, "endNode") == 0)
        {
            // printf("Found endnode\n");
            printf("---------------\n");
            continue;
        }

        if (strcmp(value, "endNet") == 0)
        {
            // printf("Found endNet\n");
            break;
        }
    }
}

void build_sim(Log *simList, char buffer[], FILE *sim)
{
    while (!feof(sim))
    {
        int i = 0;
        fgets(buffer, BUFF_SIZE, sim);
        checkString(buffer, BUFF_SIZE);
        stripComment(buffer);
        size_t len = strlen(buffer);
        int columns = check_columns(buffer);
        for (i = 0; i < len; i++)
        {
            
            if (columns == 0)
            {
                printf("Buffer is empty or Columns function failed");
            }
            if (columns == 4)
            {
                sscanf(buffer, "%u,%[^,],%u,%u,%u", &simList[i].start_time, simList[i].msg, &simList[i].msg_id, &simList[i].start_node, &simList[i].end_node);
                printf("Timestamp: %u\nMessage: %s\nMessage ID: %u\nStart Node: %u\nEnd Node: %u\n---------------\n", simList[i].start_time, simList[i].msg, simList[i].msg_id, simList[i].start_node, simList[i].end_node);
                i++;
                break;
            }
            else if (columns == 2 && strstr(buffer, "rep"))
            {
                sscanf(buffer, "%u,%[^,],%u", &simList[i].start_time, simList[i].msg, &simList[i].start_node);
                printf("Timestamp: %u\nRepMsg: %s\nNode ID: %u\n---------------\n", simList[i].start_time, simList[i].msg, simList[i].start_node);
                i++;
                break;
            }
            else if (columns == 1 && strstr(buffer, "rep"))
            {
                sscanf(buffer, "%u,%[^,],%s", &simList[i].start_time, simList[i].msg);
                printf("Timestamp: %u\nRepMsg: %s\n---------------\n", simList[i].start_time, simList[i].msg);
                i++;
                break;
            }
            else if(columns == 1 && strstr(buffer, "endSim"))
            {
                sscanf(buffer, "%u,%s", &simList[i].start_time, simList[i].msg);
                printf("Timestamp: %u\nEndMsg: %s\n****************\n", simList[i].start_time, simList[i].msg);
                i++;
                break;
            }
        }
    }
}


