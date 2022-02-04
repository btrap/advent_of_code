#pragma once

struct Risk_Node
{
    int risk_Level;

    int neighbors[4];
    int neighbors_Dist[4];
};

struct Risk_Map
{
    int width;
    int height;

    Risk_Node *risk_Nodes;
};

void PrintRiskNode(Risk_Map *risk_Map, int pos)
{
    printf("Value (%d) - %d", pos, risk_Map->risk_Nodes[pos].risk_Level);
    printf(" L(%d) - %d", risk_Map->risk_Nodes[pos].neighbors[0], risk_Map->risk_Nodes[pos].neighbors_Dist[0]);
    printf(" R(%d) - %d", risk_Map->risk_Nodes[pos].neighbors[1], risk_Map->risk_Nodes[pos].neighbors_Dist[0]);
    printf(" U(%d) - %d", risk_Map->risk_Nodes[pos].neighbors[2], risk_Map->risk_Nodes[pos].neighbors_Dist[0]);
    printf(" D(%d) - %d", risk_Map->risk_Nodes[pos].neighbors[3], risk_Map->risk_Nodes[pos].neighbors_Dist[0]);
    printf("\n");
}

void PrintRiskMap(Risk_Map *risk_Map)
{
    for(int j = 0; j < risk_Map->height; ++j)
    {
        for(int i = 0; i < risk_Map->width; ++i)
        {
            PrintRiskNode(risk_Map, j *risk_Map->width + i);
        }
    }
    printf("\n");
}

void SetupPathMap(Risk_Map *risk_Map)
{
    int pos = 0;
    for(int j = 0; j < risk_Map->height; ++j)
    {
        for(int i = 0; i < risk_Map->width; ++i)
        {
            pos = j * risk_Map->height + i;

            if(i - 1 >= 0)
            {
                risk_Map->risk_Nodes[pos].neighbors[0] = pos - 1;
            }
            if(i + 1 < risk_Map->width)
            {
                risk_Map->risk_Nodes[pos].neighbors[1] = pos + 1;
            }
            if(j - 1 >= 0)
            {
                risk_Map->risk_Nodes[pos].neighbors[2] = (j - 1) * risk_Map->height + i;
            }
            if(j + 1 < risk_Map->width)
            {
                risk_Map->risk_Nodes[pos].neighbors[3] = (j + 1) * risk_Map->height + i;
            }

            //PrintRiskNode(risk_Map, pos);
        }
    }
}

void SetupDistanceMap(Risk_Map *risk_Map)
{
    int pos = 0;
    for(int j = 0; j < risk_Map->height; ++j)
    {
        for(int i = 0; i < risk_Map->width; ++i)
        {
            pos = j * risk_Map->height + i;

            for(int n = 0; n < 4; ++n)
            {
                if(risk_Map->risk_Nodes[pos].neighbors[n] > 0)
                {
                    risk_Map->risk_Nodes[pos].neighbors_Dist[n] = risk_Map->risk_Nodes[risk_Map->risk_Nodes[pos].neighbors[n]].risk_Level;
                }
                else
                {
                    risk_Map->risk_Nodes[pos].neighbors_Dist[n] = -1;
                }
            }

            //PrintRiskNode(risk_Map, pos);
        }
    }
}

int MinimumRisk(int *risk_Value, int *visited)
{
    int min_Risk = -1;
    int min_Pos = -1;

    bool test_New = false;
    bool test_Other = false;

    for(int i = 0; i < 4; ++i)
    {
        test_New = (min_Risk == -1) && (visited[i] == -1);
        test_Other = (visited[i] < 0) && (risk_Value[i] != -1) && (risk_Value[i] < min_Risk);
        if(test_New || test_Other)
        {
            min_Risk = risk_Value[i];
            min_Pos = i;
        }
    }

    return min_Pos;
}

int CalculateRisk(Risk_Map *risk_Map)
{
    int risk = 0;

    int max_Count = risk_Map->height * risk_Map->width;
    int *visited = 0;
    STORE_TEMP_DATA(visited, max_Count * 2);
    //int *risk_Value = visited + max_Count;

    // Mark all visited nodes as unvisited
    //
    int pos = 0;
    for(int j = 0; j < risk_Map->height; ++j)
    {
        for(int i = 0; i < risk_Map->width; ++i)
        {
            pos = j * risk_Map->height + i;
            visited[pos] = -1;
            //risk_Value[pos] = risk_Map->risk_Nodes[pos].risk_Level;
        }
    }

    SetupDistanceMap(risk_Map);

    // set starting point
    visited[0] = 1;
    //risk_Value[0] = 0;

    int visited_Count = 1;
    int min_Risk = -1;
    int next_Pos = 0;
    for(int j = 0; j < max_Count - 1; ++j)
    {
        min_Risk = MinimumRisk(risk_Map->risk_Nodes->neighbors_Dist, visited);
        PrintRiskNode(risk_Map, min_Risk);
        visited[min_Risk] = 1;

        for(int n = 0; n < 4; ++n)
        {
            next_Pos = risk_Map->risk_Nodes[min_Risk].neighbors[n];
            //if(next_Pos != -1 && !visited[next_Pos] && (risk_Value[min_Risk] + risk_Map->risk_Nodes[next_Pos].risk_Level < risk_Value[next_Pos]))
            //{
            //    risk_Value[next_Pos] = risk_Value[min_Risk] + risk_Map->risk_Nodes[next_Pos].risk_Level;
            //}
        }
    }

    return risk;
}

void Advent_Of_Code_2021_15()
{
    int result1 = 0;
    int result2 = 0;

    FILE *day15_File = fopen("C:\\Users\\brand\\Software\\GitHub\\cardEngine\\assets\\xmas\\day15_test_input.txt", "r");
    //FILE *day15_File = fopen("C:\\Users\\brand\\Software\\GitHub\\cardEngine\\assets\\xmas\\day15_input.txt", "r");
    if(day15_File)
    {
        int width = 0;
        int height = 0;
        char value = 0;
        // Get length
        while(fscanf(day15_File, "%c", &value) != EOF)
        {
            if(value == '\n')
            {
                ++height;
                break;
            }
            ++width;
        }
        // Get height
        while(fscanf(day15_File, "%c", &value) != EOF)
        {
            if(value == '\n')
            {
                ++height;
            }
        }

        fseek(day15_File, 0, SEEK_SET);

        Risk_Map risk_Map = {};
        risk_Map.height = height;
        risk_Map.width = width;
        STORE_PERM_DATA(risk_Map.risk_Nodes, width * height);

        int pos = 0;
        for(int j = 0; j < risk_Map.height; ++j)
        {
            for(int i = 0; i < risk_Map.width; ++i)
            {
                fscanf(day15_File, "%c", &value);
                pos = i + j * risk_Map.width;
                risk_Map.risk_Nodes[pos].risk_Level = value - '0';
                for(int n = 0; n < 4; ++n)
                {
                    risk_Map.risk_Nodes[pos].neighbors[n] = -1;
                }
            }
            fscanf(day15_File, "%c", &value); // newline
        }

        fclose(day15_File);

        SetupPathMap(&risk_Map);

        //PrintRiskMap(&risk_Map);
        CalculateRisk(&risk_Map);
    }

    //ASSERT(result1 == 000);
    printf("The twenty first star answer is - %d\n", result1);
    //ASSERT(result2 == 000);
    printf("The twenty second star answer is - %d\n", result2);
}
