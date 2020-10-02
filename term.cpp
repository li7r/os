#pragma once
#include "types.cpp"
#include "cursor.cpp"
//#include "key.cpp"


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
            case '`':
            	if(true){
                x--;
                VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0xFF00) | ' ';}
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
            x = 0;
            y = 0;
                    
//put("XENON>");
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
   char buffer[5];
   buffer[0] = '0';
   buffer[1] = 'x';
   for (int i = 2; i >= 0; i--)
   {
      buffer[i+2] = static_cast<char>(num % 16 < 10 ? '0' + num % 16 : 'A' - 10 + num % 16);
      num /= 16;
   }
   buffer[5]= '\0';
   put(buffer);
   /*char* b[2];
   if(buffer[3]=='1'&buffer[4]=='E'){put("A");b[0]="A";}
   else if(buffer[3]=='3'&buffer[4]=='0'){put("B");b[0]="B";}
   else if(buffer[3]=='2'&buffer[4]=='E'){put("C");b[0]="C";}
   else if(buffer[3]=='2'&buffer[4]=='0'){put("D");b[0]="D";}
   else if(buffer[3]=='1'&buffer[4]=='2'){put("E");b[0]="E";}
   else if(buffer[3]=='2'&buffer[4]=='1'){put("F");b[0]="F";}
   else if(buffer[3]=='2'&buffer[4]=='2'){put("G");b[0]="G";}
   else if(buffer[3]=='2'&buffer[4]=='3'){put("H");b[0]="H";}
   else if(buffer[3]=='1'&buffer[4]=='7'){put("I");b[0]="I";}
   else if(buffer[3]=='2'&buffer[4]=='4'){put("J");b[0]="J";}
   else if(buffer[3]=='2'&buffer[4]=='5'){put("K");b[0]="K";}
   else if(buffer[3]=='2'&buffer[4]=='6'){put("L");b[0]="L";}
   else if(buffer[3]=='3'&buffer[4]=='2'){put("M");b[0]="M";}
   else if(buffer[3]=='3'&buffer[4]=='1'){put("N");b[0]="N";}
   else if(buffer[3]=='1'&buffer[4]=='8'){put("O");b[0]="O";}
   else if(buffer[3]=='1'&buffer[4]=='9'){put("P");b[0]="P";}
   else if(buffer[3]=='1'&buffer[4]=='0'){put("Q");b[0]="Q";}
   else if(buffer[3]=='1'&buffer[4]=='3'){put("R");b[0]="R";}
   else if(buffer[3]=='1'&buffer[4]=='F'){put("S");b[0]="S";}
   else if(buffer[3]=='1'&buffer[4]=='4'){put("T");b[0]="T";}
   else if(buffer[3]=='1'&buffer[4]=='6'){put("U");b[0]="U";}
   else if(buffer[3]=='2'&buffer[4]=='F'){put("V");b[0]="V";}
   else if(buffer[3]=='1'&buffer[4]=='1'){put("W");b[0]="W";}
   else if(buffer[3]=='2'&buffer[4]=='D'){put("X");b[0]="X";}
   else if(buffer[3]=='1'&buffer[4]=='5'){put("Y");b[0]="Y";}
   else if(buffer[3]=='2'&buffer[4]=='C'){put("Z");b[0]="Z";}
   else if(buffer[3]=='3'&buffer[4]=='9'){put(" ");}
   else if(buffer[3]=='1'&buffer[4]=='C'){
   put("\n");put("XENON>");
   if(b[0]=="C"){clear();b[0]="";}
   }
   else if(buffer[3]=='0'&buffer[4]=='E'){put("`");}
   else{
   //put(buffer);
   }*/
}
