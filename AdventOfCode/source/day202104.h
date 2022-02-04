#pragma once

struct Bingo_Tile
{
    int number;
    bool marked;
};

#define BINGO_DIMINSION 5
struct Bingo_Board
{
    Bingo_Tile board_Tiles[BINGO_DIMINSION][BINGO_DIMINSION];
    bool won;
};

bool MarkBoard(Bingo_Board *board, int value)
{
    bool result = false;
    
    for(int j = 0; j < 5; ++j)
    {
        for(int k = 0; k < 5; ++k)
        {
            result = board->board_Tiles[j][k].number == value;
            if(result)
            {
                board->board_Tiles[j][k].marked = result;
                return result;
            }
        }
    }

    return result;
}

bool GameWon(Bingo_Board *board)
{
    bool result = false;
    
    int vert = 0;
    int hori = 0;
    for(int j = 0; j < 5; ++j)
    {
        for(int k = 0; k < 5; ++k)
        {
            if(board->board_Tiles[j][k].marked)
            {
                ++hori;
            }
        }
        if(hori == 5)
        {
            result = true;
            board->won = true;
            return result;
        }
        hori = 0;
    }

    for(int k = 0; k < 5; ++k)
    {
        for(int j = 0; j < 5; ++j)
        {
            if(board->board_Tiles[j][k].marked)
            {
                ++vert;
            }
        }
        if(vert == 5)
        {
            result = true;
            board->won = true;
            return result;
        }
        vert = 0;
    }

    return result;
}

int ScoreBoard(Bingo_Board *board)
{
    int result = 0;
    
    for(int j = 0; j < 5; ++j)
    {
        for(int k = 0; k < 5; ++k)
        {
            if(!board->board_Tiles[j][k].marked)
            {
                result += board->board_Tiles[j][k].number;
            }
        }
    }

    return result;
}

void PrintBoard(Bingo_Board *board)
{
    for(int j = 0; j < 5; ++j)
    {
        for(int k = 0; k < 5; ++k)
        {
            if(board->board_Tiles[j][k].marked)
            {
                printf("(%d),", board->board_Tiles[j][k].number);
            }
            else
            {
                printf("%d,", board->board_Tiles[j][k].number);
            }
        }
        printf("\n");
    }
    
    printf("\n");
}

void Advent_Of_Code_2021_04()
{
    int result1 = 0;
    int result2 = 0;

    FILE *day4_File = fopen("C:\\Users\\brand\\Software\\GitHub\\cardEngine\\assets\\xmas\\day4_input.txt", "r");
    if(day4_File)
    {
        int draw_Count = 0;
        int board_Count = 0;
        int *draws;
        Bingo_Board *boards = {0};

        int value = 0;
        char comma = 0;
        while(fscanf(day4_File, "%d%c", &value, &comma) != EOF && comma == ',')
        {
            ++draw_Count;
        }
        ++draw_Count;

        char buff[64];
        while(!feof(day4_File))
        {
            fgets(buff, 64, day4_File);
            if(buff[0] != '\n')
            {
                ++board_Count;
            }
        } // bug it counts the EOF as a line that isn't \n
        board_Count /= 5;

        fseek(day4_File, 0, SEEK_SET);

        STORE_PERM_DATA(draws, draw_Count); // 27
        STORE_PERM_DATA(boards, sizeof(Bingo_Board) * board_Count); // 3
        for(int i = 0; i < draw_Count; ++i)
        {
            fscanf(day4_File, "%d,", &value);
            draws[i] = value;
        }

        for(int i = 0; i < board_Count; ++i)
        {
            for(int j = 0; j < 5; ++j)
            {
                for(int k = 0; k < 5; ++k)
                {
                    fscanf(day4_File, "%d", &value);
                    boards[i].board_Tiles[j][k].number = value;
                }
            }
        }

        fclose(day4_File);

        for(int i = 0; i < board_Count; ++i)
        {
            PrintBoard(&boards[i]);
        }

        for(int i = 0; i < draw_Count; ++i)
        {
            for(int j = 0; j < board_Count; ++j)
            {
                if(!boards[j].won && MarkBoard(&boards[j], draws[i]))
                {
                    if(GameWon(&boards[j]))
                    {
                        //PrintBoard(&boards[j]);

                        if(!result1)
                            result1 = ScoreBoard(&boards[j]) * draws[i];

                        result2 = ScoreBoard(&boards[j]) * draws[i];

                        //break;
                    }
                }

            }

            //if(result1)
            //{
            //    break;
            //}

            //for(int j = 0; j < board_Count; ++j)
            //{
            //    PrintBoard(&boards[j]);
            //}
        }
    }

    ASSERT(result1 == 60368);
    printf("The seventh star answer is - %d\n", result1);
    ASSERT(result2 == 17435);
    printf("The eigth star answer is - %d\n", result2);
}

