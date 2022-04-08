#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "entrant.h"

void usage()
{
    printf("Usage: program input_filename output_filename\n");
}

int read_entrant(FILE *in, entrant *p)
{
    return fscanf(in, "%[^\t]\t%[^\t]\t%[^\t]\t%d\t%[^\t]\t%d\t%d\t%[^\t]\n", p->surname, p->initials, p->sex, &p->school, p->medal, &p->math, &p->rus, p->essay) == 8;
}

int main(int argc, char *argv[])
{
    if (argc != 3) //если недостаточно аргументов
    {
        usage();
        return 1;
    }
    entrant p;                        //если удалось считать
    FILE *in = fopen(argv[1], "rb");  //задали входной файл
    FILE *out = fopen(argv[2], "wb"); //задали выходной файл
    if (!(out && in))                 //если хотя бы один из них не считался, то
    {
        perror("Can't open file");
        return 2;
    }
    while (read_entrant(in, &p)) //считываем данные абитуриентов из входного файла, записываем в выходной бинарный файл
    {
        fwrite(&p, sizeof(p), 1, out);
    }
    fclose(out);
    fclose(in);
    return 0;
}
