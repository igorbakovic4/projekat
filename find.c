#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void help();
int check_file(char *path_to_file, FILE * reader);
void classic(char* string, char* path_to_file);
void count_lines(char* string, char* path_to_file);
void show_containing_lines(char* string, char* path_to_file);
void show_not_containing_lines(char* string, char* path_to_file);
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
        break;
    case 4:
        if(!strcmp(argv[1], "-c")) count_lines(argv[2], argv[3]);
        else if(!strcmp(argv[1], "-i")) classic_ignore_case(argv[2], argv[3]);
        else if(!strcmp(argv[1], "-v")) show_not_containing_lines(argv[2], argv[3]);
        else if(!strcmp(argv[1], "-n")) show_containing_lines(argv[2], argv[3]);
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
    printf("Koriscenje find funkcije: find <string> <file>\n");
    printf("\nTakodje mozete koristiti i dodatne funkcije kao sto su:\n");
    printf("\t-find -c <string> <file> --> ispisuje broj redova iz <file> u kojima se pojavljuje <string>\n");
    printf("\t-find -n <string> <file> --> ispisuje redove iz <file> u kojima se pojavljuje <string>\n");
    printf("\t-find -v <string> <file> --> ispisuje redove iz <file> u kojima se ne pojavljuje <string>\n");
    printf("\t-find -i <string> <file> --> klasicno pretrazivanje, samo sto nije case-sensitive\n");
    printf("\t-find -w <string> <file> --> pretrazuje <string> ali samo gde se pojavljuje kao jedna rec\n");
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
                putchar(c);
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

void count_lines(char* string, char* path_to_file){

     FILE * reader = fopen(path_to_file, "r");

    if(!check_file(path_to_file, reader))
        return;

    char line[500];
    int count = 0;

    while(fgets(line, 500, reader) != NULL){

        if(line[strlen(line) - 1] == '\n')
            line[strlen(line) - 1] = '\0';
        
        for(int i = 0; i < strlen(line) - strlen(string) + 1; i++){

            char test_string[strlen(string)];
            int fake_i = i;
            
            for(int j = 0; j < strlen(string); j++)
                test_string[j] = line[fake_i++];
            
            if(!strcmp(string,test_string)){
                count++;
                break;
            }
        }

    }

    printf("%d\n", count);

    fclose(reader);
}

void show_containing_lines(char* string, char* path_to_file){

    FILE * reader = fopen(path_to_file, "r");

    if(!check_file(path_to_file, reader))
        return;
    
    char line[500];
    int line_num = 0;

    while(fgets(line, 500, reader) != NULL){
        line_num++;
        int contains = 0;

        if(strlen(line) == 1)
            continue;

        if(line[strlen(line) - 1] == '\n')
            line[strlen(line) - 1] = '\0';
        
        for(int i = 0; i < strlen(line) - strlen(string) + 1; i++){

            char test_string[strlen(string)];
            int fake_i = i;
            
            for(int j = 0; j < strlen(string); j++)
                test_string[j] = line[fake_i++];
            
            if(!strcmp(string,test_string)){
                contains = 1;
                break;
            }
        }

        if(contains){
            printf("\033[0;32m%d\033[0m: ", line_num);

            FILE * writer = fopen("writer.txt", "w");

            fprintf(writer, "%s", line);

            fclose(writer);

            classic(string, "writer.txt");

            remove("writer.txt");
        }

    }

    fclose(reader);

}

void show_not_containing_lines(char* string, char* path_to_file){

    FILE * reader = fopen(path_to_file, "r");

    if(!check_file(path_to_file, reader))
        return;

    char line[500];
    int line_num = 0;

    while(fgets(line, 500, reader) != NULL){
        line_num++;
        int contains = 0;

        if(line[strlen(line) - 1] == '\n')
            line[strlen(line) - 1] = '\0';
        
        for(int i = 0; i < strlen(line) - strlen(string) + 1; i++){

            char test_string[strlen(string)];
            int fake_i = i;
            
            for(int j = 0; j < strlen(string); j++)
                test_string[j] = line[fake_i++];
            
            if(!strcmp(string,test_string)){
                contains = 1;
                break;
            }
        }

        if(!contains){
            printf("%s\n", line);
        }
    }

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
            printf("%c", c);

        else if(step_back == strlen(string)){
            printf("\033[0;31m%s\033[0m", string);
            if(c != EOF)
                putchar(c);
        }
        else {
            fseek(reader, -step_back - 1, SEEK_CUR);
            c = getc(reader);
            printf("%c", c);
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
            printf("%c", c);
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
                printf("%s", string);
            }
            if(c != EOF)
                printf("%c", c);
        }
        else {
            fseek(reader, -step_back - 1, SEEK_CUR);
            c = getc(reader);
            printf("%c", c);
        }
        first_word = 0;
    }

    printf("\n");
    fclose(reader);

}