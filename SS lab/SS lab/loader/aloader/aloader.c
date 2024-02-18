// An absolute loader is a type of program that loads a program into memory for execution. It is called "absolute" because it loads a program directly into a predefined memory location without any relocation. The loader interprets the object code and transfers it to the specified memory locations, ensuring that the program can execute correctly.

#include <stdio.h>
#include <string.h>
char input[10], label[10], ch1, ch2;
int addr, w = 0, start, ptaddr, l, length = 0, end, count = 0, k, taddr, address, i = 0;
FILE *fp1, *fp2;
void check();
void main()
{
    fp1 = fopen("input.txt", "r");
    fp2 = fopen("output.txt", "w");
    fscanf(fp1, "%s", input);
    printf("\n\nABSOLUTE LOADER\n");
    fprintf(fp2, "\n-------------------------------------------------------\n");
    fprintf(fp2, "MEMORY ADDRESS\t\t\tCONTENTS");
    fprintf(fp2, "\n-------------------------------------------------------\n");

    // run the loop untill we find End record
    while (strcmp(input, "E") != 0)
    {
        // For a header record, it reads the program label, starting address, ending address, and the next input string.
        if (strcmp(input, "H") == 0)
        {
            fscanf(fp1, "%s %x %x %s", label, &start, &end, input);
            address = start;
        }

        //  For a text record, it reads the starting address, length, and the input string.
        // It fills any gaps in memory with "xx" and writes the content to the output file.
        else if (strcmp(input, "T") == 0)
        {
            l = length;
            ptaddr = addr;
            fscanf(fp1, "%x %x %s", &taddr, &length, input);
            addr = taddr;
            if (w == 0)
            {
                ptaddr = address;
                w = 1;
            }
            for (k = 0; k < (taddr - (ptaddr + l)); k++)
            {
                address = address + 1;
                fprintf(fp2, "xx");
                count++;
                if (count == 4)
                {
                    fprintf(fp2, "  ");
                    i++;
                    if (i == 4)
                    {
                        fprintf(fp2, "\n\n%x\t\t", address);
                        i = 0;
                    }
                    count = 0;
                }
            }
            if (taddr == start)
                fprintf(fp2, "\n\n%x\t\t", taddr);
            fprintf(fp2, "%c%c", input[0], input[1]);
            check();
            fprintf(fp2, "%c%c", input[2], input[3]);
            check();
            fprintf(fp2, "%c%c", input[4], input[5]);
            check();
            fscanf(fp1, "%s", input);
        }
        else
        {
            fprintf(fp2, "%c%c", input[0], input[1]);
            check();
            fprintf(fp2, "%c%c", input[2], input[3]);
            check();
            fprintf(fp2, "%c%c", input[4], input[5]);
            check();
            fscanf(fp1, "%s", input);
        }
    }
    fprintf(fp2, "\n-------------------------------------------------------\n");
    fclose(fp1);
    fclose(fp2);
    printf("\n\n The contents of output file:\n");
    fp2 = fopen("output.txt", "r");
    ch2 = fgetc(fp2);
    while (ch2 != EOF)
    {
        printf("%c", ch2);
        ch2 = fgetc(fp2);
    }
    fclose(fp2);
}
void check()
{
    count++;
    address++;
    taddr = taddr + 1;
    if (count == 4)
    {
        fprintf(fp2, "  ");
        i++;
        if (i == 4)
        {
            fprintf(fp2, "\n\n%x\t\t", taddr);
            i = 0;
        }
        count = 0;
    }
}