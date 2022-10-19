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
            int x = 0;
            int j = 0;

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
        sscanf(buffer, "%s", value);
        if (strcmp(value, "endNode") == 0)
        {
            printf("---------------\n");
            continue;
        }

        if (strcmp(value, "endNet") == 0)
        {
            break;
        }
    }
}

void build_sim(Log *simList, Rep *repList, char buffer[], FILE *sim)
{
    int sim_count = 0;
    int rep_count = 0;

    while (!feof(sim))
    {
        fgets(buffer, BUFF_SIZE, sim);
        checkString(buffer, BUFF_SIZE);
        stripComment(buffer);
        int columns = check_columns(buffer);
        if (columns == 4)
        {
            sscanf(buffer, "%u,%[^,],%u,%u,%u", &simList[sim_count].start_time, simList[sim_count].msg, &simList[sim_count].msg_id, &simList[sim_count].start_node, &simList[sim_count].end_node);
            sim_count++;
        }
        else if (columns == 2 && strstr(buffer, "rep,"))
        {
            sscanf(buffer, "%u,%[^,],%u", &repList[rep_count].start_time, repList[rep_count].msg, &repList[rep_count].selected_node);

            rep_count++;
            int j = 0;
            int k = 0;

            for (j; j < rep_count; ++j)
            {
                for (k; k < sim_count; ++k)
                {
                    if (repList[j].selected_node == simList[k].msg_id)
                    {
                        printf("REPORT START\nMsgID:%d\n", simList[k].msg_id);
                        printRep(&simList[k]);
                        printf("REPORT END\n");
                    }
                }
                k = 0;
            }
        }
        else if (columns == 1 && strstr(buffer, "rep"))
        {
            sscanf(buffer, "%u,%[^,]", &repList[rep_count].start_time, repList[rep_count].msg);
            printf("FULL REPORT START\n");
            printAllRep(simList, sim_count);
            printf("FULL REPORT END\n");
            rep_count++;
        }
        else if (columns == 1 && strstr(buffer, "endSim"))
        {
            sscanf(buffer, "%u,%s", &repList[rep_count].start_time, repList[rep_count].msg);
            printf("Timestamp: %u\nEndMsg: %s\n****************\n", repList[rep_count].start_time, repList[rep_count].msg);
        }
    }
}
