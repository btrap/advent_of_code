#pragma once

int StringLength(char * string)
{
    int result = 0;
    while(*string)
    {
        ++result;
        ++string;
    }
    return result;
}

void StringCopy(char * strA, char * strB)
{
    while(*strA)
    {
        *strB = *strA;
        ++strB;
        ++strA;
    }
    *strB = *strA;
}

enum NAV_STATUS
{
    NAV_STATUS_NORMAL,
    NAV_STATUS_INCOMPLETE,
    NAV_STATUS_CORRUPTED,
};

struct Nav_Line
{
    char *text;
    int text_Length;
    NAV_STATUS status;
};

struct Char_Test
{
    char test;
    int count;
    int value;
};

struct Nav_Stack
{
    char *text;
    int length;
};

bool IsCloser(char value)
{
    if((value == ')') || (value == ']') || (value == '}') || (value == '>'))
        return true;

    return false;
}

bool IsCorrectOpener(Nav_Stack * nav_Stack, char value)
{
    if(value == ')' && (nav_Stack->text[nav_Stack->length-1] == '('))
    {
        --nav_Stack->length;
        return true;
    }
    if(value == '}' && (nav_Stack->text[nav_Stack->length-1] == '{'))
    {
        --nav_Stack->length;
        return true;
    }
    if(value == ']' && (nav_Stack->text[nav_Stack->length-1] == '['))
    {
        --nav_Stack->length;
        return true;
    }
    if(value == '>' && (nav_Stack->text[nav_Stack->length-1] == '<'))
    {
        --nav_Stack->length;
        return true;
    }

    return false;
}

void Advent_Of_Code_2021_10()
{
    int result1 = 0;
    umax result2 = 0;

    //FILE *day10_File = fopen("C:\\Users\\brand\\Software\\GitHub\\cardEngine\\assets\\xmas\\day10_test_input.txt", "r");
    FILE *day10_File = fopen("C:\\Users\\brand\\Software\\GitHub\\cardEngine\\assets\\xmas\\day10_input.txt", "r");
    if(day10_File)
    {
        int height = 0;
        char read_Line[128];
        while(fscanf(day10_File, "%s\n", read_Line) != EOF)
        {
            ++height;
        }

        fseek(day10_File, 0, SEEK_SET);
        
        int length = 0;
        Nav_Line *nav_Lines = 0;
        STORE_PERM_DATA(nav_Lines, height);
        for(int i = 0; i < height; ++i)
        {
            fscanf(day10_File, "%s\n", read_Line);
            nav_Lines[i].text_Length = StringLength(read_Line) + 1;
            STORE_PERM_DATA(nav_Lines[i].text, nav_Lines[i].text_Length * 2);
            StringCopy(read_Line, nav_Lines[i].text);
            nav_Lines[i].status = NAV_STATUS_NORMAL;
        }

        fclose(day10_File);

        Char_Test illegal_Points[4] = { {')', 0, 3}, {']', 0, 57}, {'}', 0, 1197}, {'>', 0, 25137} };
        Char_Test complete_Points[4] = { {')', 0, 1}, {']', 0, 2}, {'}', 0, 3}, {'>', 0, 4} };
        Char_Test openings[4] = { {'(', 0, 0}, {'[', 0, 0}, {'{', 0, 0}, {'<', 0, 0} };

        umax *complete_Scores = 0;
        STORE_PERM_DATA(complete_Scores, height*2);
        int score_Count = 0;
        for(int i = 0; i < height*2; ++i)
        {
            complete_Scores[i] = 0;
        }

        Nav_Stack nav_Stack;
        char last_Open = 0;
        char curr_Char = 0;
        for(int i = 0; i < height; ++i)
        {
            nav_Stack.length = 0;
            STORE_TEMP_DATA(nav_Stack.text, nav_Lines[i].text_Length);
            for(int j = 0; j < nav_Lines[i].text_Length; ++j)
            {
                curr_Char = nav_Lines[i].text[j];
                if(IsCloser(curr_Char))
                {
                    if(nav_Stack.length == 0)
                    {
                        nav_Lines[i].status = NAV_STATUS_CORRUPTED;
                    }

                    if(!IsCorrectOpener(&nav_Stack, curr_Char))
                    {
                        nav_Lines[i].status = NAV_STATUS_CORRUPTED;

                        for(int char_Pos = 0; char_Pos < 4; ++char_Pos)
                        {
                            if(illegal_Points[char_Pos].test == curr_Char)
                            {
                                ++illegal_Points[char_Pos].count;
                            }
                        }

                        break;
                    }
                }
                else
                {
                    nav_Stack.text[nav_Stack.length] = curr_Char;
                    ++nav_Stack.length;
                }
                //printf("%s\n", nav_Stack.text);
            }

            if(nav_Stack.length > 1 && nav_Lines[i].status != NAV_STATUS_CORRUPTED)
            {
                umax curr_Score = 0;
               //printf("%s\n", nav_Lines[i].text);
                nav_Lines[i].status = NAV_STATUS_INCOMPLETE;

                while(nav_Stack.length > 1)
                {
                    curr_Char = nav_Stack.text[nav_Stack.length-2];
                    --nav_Stack.length;

                    for(int char_Pos = 0; char_Pos < 4; ++char_Pos)
                    {
                        if(openings[char_Pos].test == curr_Char)
                        {
                            curr_Score = curr_Score * 5 + (umax)complete_Points[char_Pos].value;
                            nav_Lines[i].text[nav_Lines[i].text_Length-1] = complete_Points[char_Pos].test;
                            ++nav_Lines[i].text_Length;
                            ++complete_Points[char_Pos].count;
                        }
                    }
                    //printf("%s\n", nav_Lines[i].text);
                }
                
                int new_Pos = 0;
                while((new_Pos < score_Count) && (curr_Score > complete_Scores[new_Pos]))
                {
                    ++new_Pos;
                }

                if(complete_Scores[new_Pos] > 0)
                {
                    int mover = score_Count;
                    while(mover > new_Pos)
                    {
                        complete_Scores[mover] = complete_Scores[mover-1];
                        --mover;
                    }
                    complete_Scores[new_Pos] = curr_Score;
                }
                else
                {
                    complete_Scores[score_Count] = curr_Score;
                }

                ++score_Count;
                
                //for(int i = 0; i < score_Count; ++i)
                //{
                //    printf("%lld\n", complete_Scores[i]);
                //}
            }
        }

        for(int i = 0; i < 4; ++i)
        {
            result1 += illegal_Points[i].count * illegal_Points[i].value;
        }

        result2 = complete_Scores[score_Count / 2];
    }

    ASSERT(result1 == 318099);
    printf("The nintenth star answer is - %d\n", result1);
    ASSERT(result2 == 2389738699);
    printf("The tewentith star answer is - %llu\n", result2);
}
