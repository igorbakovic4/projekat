#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void help();
int check_file(char *path_to_file, FILE * reader);
void classic(char* string, char* path_to_file);
void lines(char* string, char* path_to_file, char* option);
void find_exact_word(char* string, char* path_to_file);
void classic_ignore_case(char* string, char* path_to_file);

int main(int argc, char *argv[]){

    switch (argc)
    {
    case 2:
        if(!strcmp(argv[1], "-h"))
            help();
        else
            printf("Neispravan unos, pokusajte: find -h\n");
        break;
    case 3:
        classic(argv[1], argv[2]);
        putchar('\n');
        break;
    case 4:
        if(!strcmp(argv[1], "-c")) lines(argv[2], argv[3], argv[1]);
        else if(!strcmp(argv[1], "-i")) classic_ignore_case(argv[2], argv[3]);
        else if(!strcmp(argv[1], "-v")) lines(argv[2], argv[3], argv[1]);
        else if(!strcmp(argv[1], "-n")) lines(argv[2], argv[3], argv[1]);
        else if(!strcmp(argv[1], "-w")) find_exact_word(argv[2], argv[3]);
        else printf("Neispravan unos! Ako vam je potrebna pomoc, iskoristite komandu: find -h");
        break;
    default:
        printf("Neispravan unos, pokusajte: find -h");
        break;
    }
    

    return 0;
}

void help(){
    printf("Koriscenje find funkcije: \033[0;32mfind <string> <file>\033[0m\n");
    printf("\nTakodje mozete koristiti i dodatne funkcije kao sto su:\n");
    printf("\t-\033[0;32mfind -c <string> <file>\033[0m --> ispisuje broj redova iz <file> u kojima se pojavljuje <string>\n");
    printf("\t-\033[0;32mfind -n <string> <file>\033[0m --> ispisuje redove iz <file> u kojima se pojavljuje <string>\n");
    printf("\t-\033[0;32mfind -v <string> <file>\033[0m --> ispisuje redove iz <file> u kojima se ne pojavljuje <string>\n");
    printf("\t-\033[0;32mfind -i <string> <file>\033[0m --> klasicno pretrazivanje, samo sto nije case-sensitive\n");
    printf("\t-\033[0;32mfind -w <string> <file>\033[0m --> pretrazuje <string> ali samo gde se pojavljuje kao jedna rec\n");
}

int check_file(char *path_to_file, FILE * reader){

    if(reader == NULL) {
        printf("Datoteka: \033[0;31m%s\033[0m ne postoji ili nije odgovarajuca.\nZa pomoc pokusajte: find -h\n", path_to_file);
        return 0;
    }
    return 1;
}

void classic(char* string, char* path_to_file){

    FILE * reader = fopen(path_to_file, "r");

    if(!check_file(path_to_file, reader))
        return;

    char c;
    
    while((c = getc(reader)) != EOF){
        int index = 0, step_back = 0;

        while(c == string[index++]){
            step_back++;
            c = getc(reader);
        }
        
        if(step_back == 0) 
            putchar(c);

        else if(step_back == strlen(string)){
            printf("\033[0;31m%s\033[0m", string);
            if(c != EOF)
                fseek(reader, -1, SEEK_CUR);
        }
        else {
            fseek(reader, -step_back - 1, SEEK_CUR);
            c = getc(reader);
            putchar(c);
        }
    }

    fclose(reader);
}

void lines(char* string, char* path_to_file, char* option){

    FILE * reader = fopen(path_to_file, "r");

    if(!check_file(path_to_file, reader))
        return;
    
    char line[500];
    int line_num = 0, count = 0;

    while(fgets(line, 500, reader) != NULL){
        line_num++; 
        
        if(strstr(line, string) != NULL){
            count++;
            if(!strcmp(option, "-n")){
                printf("\033[0;32m%d\033[0m: ", line_num);

                FILE * writer = fopen("writer.txt", "w");

                fputs(line, writer);

                fclose(writer);

                classic(string, "writer.txt");

                remove("writer.txt");
            }
            
        }
        else if(!strcmp(option, "-v"))
            printf("%s", line);
        
    }

    if(!strcmp(option, "-c"))
        printf("%d\n", count);

    fclose(reader);

}

void classic_ignore_case(char* string, char* path_to_file){

    FILE * reader = fopen(path_to_file, "r");

    if(!check_file(path_to_file, reader))
        return;

    char c;
    
    while((c = getc(reader)) != EOF){
        int index = 0, step_back = 0;

        while(toupper(c) == toupper(string[index])){
            step_back++;
            string[index++] = c;
            c = getc(reader);
        }
        
        if(step_back == 0) 
            putchar(c);

        else if(step_back == strlen(string)){
            printf("\033[0;31m%s\033[0m", string);
            fseek(reader, -1, SEEK_CUR);
        }
        else {
            fseek(reader, -step_back - 1, SEEK_CUR);
            c = getc(reader);
            putchar(c);
        }
    }

    printf("\n");
    fclose(reader);

}

void find_exact_word(char* string, char* path_to_file){

    FILE * reader = fopen(path_to_file, "r");

    if(!check_file(path_to_file, reader))
        return;

    char c;
    int first_word = 1;
    
    while((c = getc(reader)) != EOF){
        int index = 0, step_back = 0;

        while(c == string[index++]){
            step_back++;
            c = getc(reader);
        }
        
        if(step_back == 0) 
            putchar(c);
        else if(step_back == strlen(string)){

            int isWord = 0;

            switch (c)
                {
                case ' ':
                case '\n':
                case '.':
                case '?':
                case '!':
                case ',':
                case EOF:
                    isWord = 1;
                    break;
                
                default:
                    break;
                }
           
            if(!first_word){
                fseek(reader, -step_back - 2, SEEK_CUR);
                switch (getc(reader))
                {
                case ' ':
                case '\n':
                    break;
                
                default:
                    isWord = 0;
                    break;
                }
            }

            fseek(reader, +step_back + 1, SEEK_CUR);

            if(isWord)
                printf("\033[0;31m%s\033[0m", string);
            else{
                puts(string);
            }
            fseek(reader, -1, SEEK_CUR);
        }
        else {
            fseek(reader, -step_back - 1, SEEK_CUR);
            c = getc(reader);
            putchar(c);
        }
        first_word = 0;
    }

    printf("\n");
    fclose(reader);

}