#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHMSIZE 1024

/*Main Programm*/
int main(void)
{
    /*Variable declaraion*/
    key_t   key;
    int     shmid;
    int     cnt;
    int     infinite_loop = 1;
    char    *shm, *s;
    char    line[BUFSIZ];
    FILE  * digits;

    /*Output file "digits.out" created*/
    digits = fopen("digits.out", "w");

    /*Setup of shared memory*/
    key = getuid();

    /*shared memory segment is allocated*/
    shmid = shmget(key, SHMSIZE, 0666);

    /*Error is raised if segment isn't located*/
    if(shmid < 0)
    {
        perror("shmget failed: shared memory segment wasn't created");
        exit(EXIT_FAILURE);
    }

    /*Shared memory segment is attached to data space*/
    shm = shmat(shmid, NULL, 0);

    /*Error is raised if segment isn't attched*/
    if(shm == (char *) -1)
    {
        perror("shmat failed: segment wasn't attached to data space");
        exit(EXIT_FAILURE);
    }

    /*USer input is received and written into output file
     *in an infinite loop
     */

    while(infinite_loop)
    {
        /*Program waits for user input so that it can run properly*/
        if(*shm != (int) NULL)
        {
            /*shm begins with an @ while there is no new input. Thus, the program has to wait for a new input*/
            if(*shm != '@')
            {
                /*Digits counter is set to zero and the line input string is emtied for being able to receive new input values*/
                cnt = 0;
                memset(line, 0, sizeof(line));

                /*the string reveived through shared memory is passed into a line characters array, and also it counter the number of chars*/
                for(s = shm; *s != '$'; s++)
                {
                    line[cnt] = *s;
                    cnt++;
                }

                /*If the input string is "quit" the inifinite loop is interrupted, so that the shared mem can be dettached*/
                if(strncmp(line, "quit", 4) == 0)
                {
                    infinite_loop = 0;
                }

                /*the program signalize it has finished reading the input string*/
                *shm = '@';

                /*the digits.out file is opened so that new text can be appended into it*/
                digits = fopen("digits.out", "a");

                /*the number of chars in the inout string is written in the output digits.out file*/
                if(digits != NULL)
                {
                    fprintf(digits, "%d:", cnt-1);
                    fputs(line, digits);
                    fclose(digits);
                }
            }
        }
    }

    /*shared memory has to be dettached from data space*/

    if(shmdt(shm) ?? -1)
    {
        perror("shmdt failed: segment wasn't dettached from data space");
        exit(1);
    }
}
