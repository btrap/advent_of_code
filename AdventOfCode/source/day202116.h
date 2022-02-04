#pragma once

struct Packet_Header;

struct Packet_Header
{
    int version;
    int type_Id;
    int length_Type_Id;
    int total_Length;
    int number_Of_Sub_Packets;

    Packet_Header *sub_Packets;
    umax literal_Value;
};

int MakeInt(char * packet_Bits, int length)
{
    int result = 0;
    for(int i = 0; i < length; ++i)
    {
        result = result << 1;
        result += packet_Bits[i];
    }
    //printf("newInt = %d\n", result);
    return result;
}

int GetVersionSum(Packet_Header* packet_Header)
{
    int result = packet_Header->version;
    for(int i = 0; i < packet_Header->number_Of_Sub_Packets; ++i)
    {
        result += GetVersionSum(&packet_Header->sub_Packets[i]);
    }
    return result;
}

int ReadPacketHeader(Packet_Header* packet_Header, char *packet_Bits, int bit_Length)
{
    int bit_Pos = 0;
    int walker = 0;
    int test_Bit = 0;

    packet_Header->literal_Value = 0;

    packet_Header->version = MakeInt(packet_Bits + bit_Pos, 3);
    bit_Pos += 3;
    packet_Header->type_Id = MakeInt(packet_Bits + bit_Pos, 3);
    printf("type_Id = %d\n", packet_Header->type_Id);
    bit_Pos += 3;

    if(packet_Header->type_Id == 4) // literal value
    {
        walker = 4;
        packet_Header->literal_Value = 0;

        do
        {
            test_Bit = MakeInt(packet_Bits + bit_Pos, 1);
            bit_Pos += 1;
            for(int i = 0; i < walker; ++i)
            {
                packet_Header->literal_Value = packet_Header->literal_Value << 1;
                packet_Header->literal_Value += (packet_Bits + bit_Pos)[i];
            }
            bit_Pos += walker;
        } while(test_Bit);
    }
    else // operator
    {
        packet_Header->length_Type_Id = MakeInt(packet_Bits + bit_Pos, 1);
        bit_Pos += 1;
        if(packet_Header->length_Type_Id)
        {
            packet_Header->number_Of_Sub_Packets = MakeInt(packet_Bits + bit_Pos, 11);
            bit_Pos += 11;
            packet_Header->total_Length = 0;

            STORE_PERM_DATA(packet_Header->sub_Packets, packet_Header->number_Of_Sub_Packets);
            
            int bits_Used = 0;
            for(int i = 0; i < packet_Header->number_Of_Sub_Packets; ++i)
            {
                bits_Used = ReadPacketHeader(&packet_Header->sub_Packets[i], packet_Bits + bit_Pos, bit_Length);
                packet_Header->total_Length += bits_Used;
                bit_Pos += bits_Used;
            }
        }
        else
        {
            packet_Header->number_Of_Sub_Packets = 0;
            packet_Header->total_Length = MakeInt(packet_Bits + bit_Pos, 15);
            bit_Pos += 15;
            
            STORE_PERM_DATA(packet_Header->sub_Packets, 100); // TODO FIX
            int bits_Used = 0;
            int current_Used = 0;
            while(packet_Header->total_Length > current_Used)
            {
                bits_Used = ReadPacketHeader(&packet_Header->sub_Packets[packet_Header->number_Of_Sub_Packets], packet_Bits + bit_Pos, bit_Length);
                bit_Pos += bits_Used;
                current_Used += bits_Used;
                ++packet_Header->number_Of_Sub_Packets;
                ASSERT(packet_Header->number_Of_Sub_Packets < 100);
            }
        }
    }

    switch(packet_Header->type_Id)
    {
        case 0:
        {
            packet_Header->literal_Value = packet_Header->sub_Packets[0].literal_Value;
            for(int i = 1; i < packet_Header->number_Of_Sub_Packets; ++i)
            {
                packet_Header->literal_Value += packet_Header->sub_Packets[i].literal_Value;
            }
        }break;
        case 1:
        {
            packet_Header->literal_Value = packet_Header->sub_Packets[0].literal_Value;
            for(int i = 1; i < packet_Header->number_Of_Sub_Packets; ++i)
            {
                packet_Header->literal_Value *= packet_Header->sub_Packets[i].literal_Value;
            }
        }break;
        case 2:
        {
            packet_Header->literal_Value = packet_Header->sub_Packets[0].literal_Value;
            for(int i = 1; i < packet_Header->number_Of_Sub_Packets; ++i)
            {
                if(packet_Header->literal_Value > packet_Header->sub_Packets[i].literal_Value)
                {
                    packet_Header->literal_Value = packet_Header->sub_Packets[i].literal_Value;
                }
            }
        }break;
        case 3:
        {
            packet_Header->literal_Value = packet_Header->sub_Packets[0].literal_Value;
            for(int i = 1; i < packet_Header->number_Of_Sub_Packets; ++i)
            {
                if(packet_Header->literal_Value < packet_Header->sub_Packets[i].literal_Value)
                {
                    packet_Header->literal_Value = packet_Header->sub_Packets[i].literal_Value;
                }
            }
        }break;
        case 5:
        {
            packet_Header->literal_Value = packet_Header->sub_Packets[0].literal_Value > packet_Header->sub_Packets[1].literal_Value;
        }break;
        case 6:
        {
            packet_Header->literal_Value = packet_Header->sub_Packets[0].literal_Value < packet_Header->sub_Packets[1].literal_Value;
        }break;
        case 7:
        {
            packet_Header->literal_Value = packet_Header->sub_Packets[0].literal_Value == packet_Header->sub_Packets[1].literal_Value;
        }break;
    };

    return bit_Pos;
}

void Advent_Of_Code_2021_16()
{
    int result1 = 0;
    int result2 = 0;

    //FILE *day16_File = fopen("C:\\Users\\brand\\Software\\GitHub\\cardEngine\\assets\\xmas\\day16_test_input.txt", "r");
    FILE *day16_File = fopen("C:\\Users\\brand\\Software\\GitHub\\cardEngine\\assets\\xmas\\day16_input.txt", "r");
    if(day16_File)
    {
        char hex_Value = 0;
        int bit_Length = 0;
        while(fscanf(day16_File, "%c", &hex_Value) != EOF)
        {
            if(hex_Value != '/n')
                bit_Length += 4;
        }

        char *packet_Bits = 0;
        STORE_TEMP_DATA(packet_Bits, bit_Length);
        
        fseek(day16_File, 0, SEEK_SET);

        int bit_Pos = 0;
        while(fscanf(day16_File, "%c", &hex_Value) != EOF)
        {
            if(hex_Value == '/n')
                continue;

            //printf("Hex = %d\n", hex_Value);

            int hex_Dec = 0;
            if(hex_Value >= '0' && hex_Value <= '9')
            {
                hex_Dec = hex_Value - '0';
            }
            else
            {
                hex_Dec = hex_Value - 'A' + 10;
            }
            //printf("Dec = %d\n", hex_Dec);

            for(int i = 3; i > -1; --i)
            {
                packet_Bits[bit_Pos * 4 + i] = hex_Dec & 1;
                hex_Dec = hex_Dec >> 1;
            }
            //printf("Bin = %d%d%d%d\n", packet_Bits[bit_Pos * 4], packet_Bits[bit_Pos * 4 + 1], packet_Bits[bit_Pos * 4 + 2], packet_Bits[bit_Pos * 4 + 3]);
            ++bit_Pos;
        }

        fclose(day16_File);

        bit_Pos = 0;

        Packet_Header packet_Header;
        ReadPacketHeader(&packet_Header, packet_Bits, bit_Length);

        result1 = GetVersionSum(&packet_Header);
        result2 = packet_Header.literal_Value;
        
        printf("The twenty first star answer is - %d\n", result1);
    }

    ASSERT(result1 == 886);
    printf("The twenty first star answer is - %d\n", result1);
    //ASSERT(result2 == 000);
    printf("The twenty second star answer is - %d\n", result2);
}
