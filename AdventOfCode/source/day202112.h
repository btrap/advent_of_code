#pragma once

struct Cave;

struct Cave
{
    char *name;
    bool small;
    int visits;

    int *connected;
    int connections;
};

struct Cave_System
{
    Cave *caves;
    int cave_Count;
    int paths;

    int special_Small;
};

int Upper(char value)
{
    bool result = value >= 'A' && value <= 'Z';
    return result;
}

void PrintCaves(Cave_System * cave_System)
{
    for(int c = 0; c < cave_System->cave_Count; ++c)
    {
        printf("name - %s\n", cave_System->caves[c].name);
        printf("small - %d\n", cave_System->caves[c].small);
        printf("visits - %d\n", cave_System->caves[c].visits);
        printf("connections - %d\n", cave_System->caves[c].connections);
        for(int s = 0; s < cave_System->caves[c].connections; ++s)
        {
            printf("connected - %s\n", cave_System->caves[cave_System->caves[c].connected[s]].name);
        }
        printf("\n");
    }
    printf("\n");
}

void VisitCaves(Cave_System *cave_System, Cave *cave)
{
    if(cave->name[0] == 'e' && cave->name[1] == 'n')
    {
        //printf("%s", cave->name);
        ++cave_System->paths;
        return;
    }

    if(cave->small && (cave->visits > 0))
    {
        //printf("(cancel push %s (%d)) ", cave->name, cave->visits);
        return;
    }

    ++cave->visits;

    //printf("%s (%d)-> ", cave->name, cave->visits);

    //printf("push %s (%d) ", cave->name, cave->visits);

    Cave *connection = 0;
    for(int s = 0; s < cave->connections; ++s)
    {
        connection = &cave_System->caves[cave->connected[s]];

        if(cave_System->special_Small == -1 && connection->small && connection->visits == 1)
        {
            //printf("push special %s (%d) ", connection->name, connection->visits);
            cave_System->special_Small = s;
            --connection->visits;

            VisitCaves(cave_System, connection);

            cave_System->special_Small = -1;
            ++connection->visits;
        }
            VisitCaves(cave_System, connection);
        
       // printf("push %s (%d) ", connection->name, connection->visits);

        //VisitCaves(cave_System, connection);
    }
    
    --cave->visits; // leaving cave
    //printf("pop %s (%d) ", cave->name, cave->visits);

    //printf("\n");
}

void Advent_Of_Code_2021_12()
{
    int result1 = 0;
    int result2 = 0;
    
    //FILE *day11_File = fopen("C:\\Users\\brand\\Software\\GitHub\\cardEngine\\assets\\xmas\\day12_test_input.txt", "r");
    //FILE *day11_File = fopen("C:\\Users\\brand\\Software\\GitHub\\cardEngine\\assets\\xmas\\day12_test3_input.txt", "r");
    FILE *day11_File = fopen("C:\\Users\\brand\\Software\\GitHub\\cardEngine\\assets\\xmas\\day12_input.txt", "r");

    int connection_Count = 0;
    char cave_NameA[8];
    char cave_NameB[8];
    Cave_System cave_System = {0};
    cave_System.special_Small = -1;
    int max_Cave_Count = 0;
    if(day11_File)
    {
        while(fscanf(day11_File, "%s - %s", &cave_NameA, &cave_NameB) != EOF)
        {
            ++connection_Count;
        }

        fseek(day11_File, 0, SEEK_SET);
        
        int start = 0;
        max_Cave_Count = connection_Count * 2;
        STORE_PERM_DATA(cave_System.caves, max_Cave_Count);
        for(int i = 0; fscanf(day11_File, "%s - %s\n", &cave_NameA, &cave_NameB) != EOF; ++i)
        {
            int cA = 0;
            while(cA < cave_System.cave_Count)
            {
                if(cave_NameA[0] == cave_System.caves[cA].name[0] && cave_NameA[1] == cave_System.caves[cA].name[1])
                {
                    break;
                }
                ++cA;
            }

            if(cA >= cave_System.cave_Count)
            {
                STORE_PERM_DATA(cave_System.caves[cave_System.cave_Count].name, StringLength(cave_NameA) + 1);
                cave_System.caves[cave_System.cave_Count].small = !Upper(cave_NameA[0]);
                cave_System.caves[cave_System.cave_Count].visits;
                StringCopy(cave_NameA, cave_System.caves[cave_System.cave_Count].name);
                STORE_PERM_DATA(cave_System.caves[cave_System.cave_Count].connected, max_Cave_Count - 1);

                if(cave_NameA[0] == 's' && cave_NameA[1] == 't')
                {
                    start = cave_System.cave_Count;
                    cave_System.caves[cave_System.cave_Count].small = false;
                }
                if(cave_NameA[0] == 'e' && cave_NameA[1] == 'n')
                {
                    cave_System.caves[cave_System.cave_Count].small = false;
                }

                ++cave_System.cave_Count;
            }

            int cB = 0;
            while(cB < cave_System.cave_Count)
            {
                if(cave_NameB[0] == cave_System.caves[cB].name[0] && cave_NameB[1] == cave_System.caves[cB].name[1])
                {
                    break;
                }
                ++cB;
            }

            if(cB >= cave_System.cave_Count)
            {
                STORE_PERM_DATA(cave_System.caves[cave_System.cave_Count].name, StringLength(cave_NameB) + 1);
                cave_System.caves[cave_System.cave_Count].small = !Upper(cave_NameB[0]);
                cave_System.caves[cave_System.cave_Count].visits;
                StringCopy(cave_NameB, cave_System.caves[cave_System.cave_Count].name);
                STORE_PERM_DATA(cave_System.caves[cave_System.cave_Count].connected, max_Cave_Count - 1);
                
                if(cave_NameB[0] == 's' && cave_NameB[1] == 't')
                {
                    start = cave_System.cave_Count;
                    cave_System.caves[cave_System.cave_Count].small = false;
                }
                if(cave_NameB[0] == 'e' && cave_NameB[1] == 'n')
                {
                    cave_System.caves[cave_System.cave_Count].small = false;
                }

                ++cave_System.cave_Count;
            }
            
            if(cave_NameB[0] != 's' && cave_NameB[1] != 't')
                cave_System.caves[cA].connected[cave_System.caves[cA].connections++] = cB;
            if(cave_NameA[0] != 's' && cave_NameA[1] != 't')
                cave_System.caves[cB].connected[cave_System.caves[cB].connections++] = cA;

        }
        fclose(day11_File);

        PrintCaves(&cave_System);

        VisitCaves(&cave_System, &cave_System.caves[start]); // support longer strings 
        result1 = cave_System.paths;
    }

    //ASSERT(result1 == 3292);
    printf("The twenty first star answer is - %d\n", result1);
    //ASSERT(result2 == 247);
    printf("The twenty second star answer is - %d\n", result2);
}
