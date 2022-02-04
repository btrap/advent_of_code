#pragma once

int RollDie(int die_Pos, int max_Pos, int rolls)
{
    int roll_Total = 0;
    if(die_Pos < (max_Pos-1)) // 98 = 98 + 99 + 100
    {
        roll_Total = die_Pos * 3 + 3;
    }
    else
    {
        if(die_Pos == (max_Pos-1))
        {
            roll_Total = max_Pos + max_Pos; // 99 = 200
        }
        else if(die_Pos == max_Pos)
        {
            roll_Total = max_Pos + 3; // 100 = 103
        }
    }
    return roll_Total;
}


void Advent_Of_Code_2021_21()
{
    umax result1 = 0;
    umax result2 = 0;

    //FILE *day21_File = fopen("C:\\Users\\brand\\Software\\GitHub\\cardEngine\\assets\\xmas\\day21_test_input.txt", "r");
    //FILE *day21_File = fopen("C:\\Users\\brand\\Software\\GitHub\\cardEngine\\assets\\xmas\\day21_input.txt", "r");
    //if(day21_File)
    //{
    //    fseek(day21_File, 0, SEEK_SET);
    //    fclose(day21_File);
    //}

    //int startingP1 = 6;
    //int startingP2 = 9;
    int startingP1 = 4;
    int startingP2 = 8;

    int board_Length = 10;
    int board[10];
    for(int i = 1; i < board_Length; ++i)
    {
        board[i] = i;
    }
    board[0] = 10;

    int winning_Score = 1000;

    int player1_Pos = startingP1;
    umax player1_Score = 0;

    int player2_Pos = startingP2;
    umax player2_Score = 0;

    int max_Die_Pos = 100;
    int die_Pos = 1;
    int roll_Count = 3;

    int turns = 0;
    int total_Rolls = 0;

    int cur_Roll = 0;
    while(player2_Score <= winning_Score)
    {
        cur_Roll = RollDie(die_Pos, max_Die_Pos, roll_Count);
        die_Pos = (die_Pos + roll_Count) % max_Die_Pos;
        player1_Pos = (player1_Pos + cur_Roll) % (board_Length);
        player1_Score += board[player1_Pos];
        total_Rolls += 3;

        if(player1_Score >= winning_Score)
            break;

        cur_Roll = RollDie(die_Pos, max_Die_Pos, roll_Count);
        die_Pos = (die_Pos + roll_Count) % max_Die_Pos;
        player2_Pos = (player2_Pos + cur_Roll) % (board_Length);
        player2_Score += board[player2_Pos];
        total_Rolls += 3;

        ++turns;
    }

    result1 = (umax)(total_Rolls) * umax((player1_Score > player2_Score) ? player2_Score : player1_Score);

    //ASSERT(result1 == 925605);
    printf("The twenty first star answer is - %d\n", result1);
    //ASSERT(result2 == 000);
    printf("The twenty second star answer is - %d\n", result2);
}
