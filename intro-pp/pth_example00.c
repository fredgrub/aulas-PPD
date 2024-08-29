#include <stdio.h>
#define NUM_MSG 8

char *messages[NUM_MSG];

int main(int argc, char *argv[])
{
    int t;

    messages[0] = "English: Hello World!";
    messages[1] = "French: Bonjour, le monde!";
    messages[2] = "Spanish: Hola al mundo";
    messages[3] = "Klingon: Nuq neH!";
    messages[4] = "German: Guten Tag, Welt!"; 
    messages[5] = "Russian: Zdravstvuy, mir!";
    messages[6] = "Japan: Sekai e konnichiwa!";
    messages[7] = "Latin: Orbis, te saluto!";
    
    for(t=0;t<NUM_MSG;t++)
    {
        printf("%s\n", messages[t]);
    }
}