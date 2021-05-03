/**
 * @file main.c
 * @brief SimpleLang Interpreter(SL)
 * @author Syoch
 * @date 2020/10/9(JPN)
*/
/*Include*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Macro definetion*/
#define SIZE(x) ((sizeof(x)) / (sizeof(x[0])))
#define char2int_a(c, p)       \
    int p##A = char2int(c[0]); \
    int p##B = char2int(c[1]); \
    int p##C = char2int(c[2]);

/**
 * @def
 * i32 -> (long int)
 * 32bit integerter
 */
#define i32 long int
/**
 * @def
 * MEMTYPE_I32 ->1
 * memory type int 32
 */
#define MEMTYPE_I32 ((char)1)
//! memorys (void pointer three array)
void *mems[59][59][59] = {NULL};
//! memorys use table (char three array)
char usemems[59][59][59] = {0};
//! memorys type table (char thee array)
char typmems[59][59][59] = {0};
//! Convert table using by char2int
char convtable[] = "_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

/**
 * @fn
 * _ a-z A-Z 0-9 To 0-58 Converting function
 * @brief Converter
 * @param c Convert from
 * @return 0-58 value
 */
int char2int(char c)
{
    int l, i;
    for (l = 0; l < SIZE(convtable); l++)
    {
        if (convtable[l] == c)
        {
            i = l;
            break;
        }
    }
    return l;
}
void error()
{
    printf("Error\n");
    exit(1);
}
void mem_def(char c[3], char d[3])
{
    printf("%d %d %d\n", char2int(c[0]), char2int(c[1]), char2int(c[2]));
    char2int_a(c, mem);
    if (!strcmp(d, "i32"))
    {
        typmems[memA][memB][memC] = MEMTYPE_I32;
        usemems[memA][memB][memC] = 1;
        mems[memA][memB][memC] = (i32 *)malloc(sizeof(i32) * 1);
    }
    else
    {
        printf("Unknown Memory type\n");
        error();
    }
}
void mem_set(char c[3], char d[3])
{
    printf("%d %d %d\n", char2int(c[0]), char2int(c[1]), char2int(c[2]));
    char2int_a(c, mem);
    if (typmems[memA][memB][memC] == MEMTYPE_I32)
    {
        *((i32 *)mems[memA][memB][memC]) = (i32)atoi(d);
    }
}
void mem_add(char b[3], char c[3], char d[3])
{

    char2int_a(b, memB);
    char2int_a(c, memC);
    char2int_a(d, memD);
    if (typmems[memBA][memBB][memBC] == MEMTYPE_I32 &&
        typmems[memCA][memCB][memCC] == MEMTYPE_I32 &&
        typmems[memDA][memDB][memDC] == MEMTYPE_I32)
    {
        (i32) * mems[memDA][memDB][memDC] =
            (i32)*mems[memBA][memBB][memBC] +
            (i32)*mems[memCA][memCB][memCC];
    }
    else
    {
        printf("Invalid Memory type\n");
        error();
    }
}
void run()
{
    FILE *fp = fopen("src.txt", "r");
    char line[512];
    char a[4] = {0};
    char b[4] = {0};
    char c[4] = {0};
    char d[4] = {0};
    while (fgets(line, 512, fp) != NULL)
    {
        a[0] = line[0];
        a[1] = line[1];
        a[2] = line[2];
        b[0] = line[4];
        b[1] = line[5];
        b[2] = line[6];
        c[0] = line[8];
        c[1] = line[9];
        c[2] = line[10];
        d[0] = line[12];
        d[1] = line[13];
        d[2] = line[14];
        printf("%s %s %s %s ", a, b, c, d);
        if (!strcmp(a, "mem"))
        {
            if (!strcmp(b, "def"))
                mem_def(c, d);
            if (!strcmp(b, "set"))
                mem_set(c, d);
        }
        if (!strcmp(a, "add"))
        {
            mem_add(b, c, d);
        }
    }
}
/**
 * @fn
 * @brief Memory Free
 * @param None
 * @return None
 */
void free_mems()
{
    printf("\nCleanuping Memorys\n");
    int i, j, k;
    for (i = 0; i < SIZE(mems); i++)
    {
        for (j = 0; j < SIZE(mems); j++)
        {
            for (k = 0; k < SIZE(mems); k++)
            {
                if (usemems[i][j][k] == 1)
                {
                    printf("free [%d,%d,%d](%d)\n", i, j, k, *((i32 *)mems[i][j][k]));
                    free(mems[i][j][k]);
                }
            }
        }
    }
}
/**
 * @fn
 * Program entry pointer function
 * @brief Entrypoint
 * @param argc Program Argument Length
 * @param argv Program Argument array(String)
 * @return int(0)
 */
int main(int argc, char const *argv[])
{
    run();
    free_mems();
    return 0;
}
