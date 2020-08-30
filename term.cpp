#pragma once
#include "types.cpp"
#include "cursor.cpp"

void put(char* str)
{
    static uint16_t* VideoMemory = (uint16_t*)0xb8000;

    static uint8_t x=0,y=0;

    for(int i = 0; str[i] != '\0'; ++i)
    {
        switch(str[i])
        {
            case '\n':
                x = 0;
                y++;
                break;
            default:
                VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0xFF00) | str[i];
                x++;
                break;
        }

        if(x >= 80)
        {
            x = 0;
            y++;
        }

        if(y >= 25)
        {
            for(y = 0; y < 25; y++)
                for(x = 0; x < 80; x++)
                    VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0xFF00) | ' ';
            x = 0;
            y = 0;
        }
    }
    update_cursor(x,y);
}
void clear(){
static uint16_t* VideoMemory = (uint16_t*)0xb8000;
static uint8_t x=0,y=0;
            for(y = 0; y < 25; y++)
                for(x = 0; x < 80; x++)
                    VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0xFF00) | ' ';
            update_cursor(0,0);
}
void write_string( int colour, const char *string )
{
    volatile char *video = (volatile char*)0xB8000;
    while( *string != 0 )
    {
        *video++ = *string++;
        *video++ = colour;
    }
}
void hex(uint32_t num)
{
   char buffer[11];
   buffer[0] = '0';
   buffer[1] = 'x';
   for (int i = 7; i >= 0; i--)
   {
      buffer[i+2] = static_cast<char>(num % 16 < 10 ? '0' + num % 16 : 'A' - 10 + num % 16);
      num /= 16;
   }
   buffer[10]= '\0';         /* terminate string */
   write_string(9,buffer);     /* print it */
}
