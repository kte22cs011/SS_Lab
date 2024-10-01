#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LABEL_SIZE 20
#define MAX_OPCODE_SIZE 10
#define MAX_OPERAND_SIZE 10
#define MAX_LINE_SIZE 80
#define MAX_OBJ_CODE_SIZE 10


typedef struct {
    char label[MAX_LABEL_SIZE];
    int address;
} SymTabEntry;

SymTabEntry symtab[100];
int symtab_count=0;

int search_symtab(char *label)
{
    for(int i=0;i<symtab_count;i++)
    {
        if(strcmp(symtab[i].label,label) == 0)
        {
            return i;
        }
    }
    return -1;
}

void insert_symtab(char *label,int address)
{
    strcpy(symtab[symtab_count].label, label);
    symtab[symtab_count].address=address;
    symtab_count++;
}

int search_optab(char *opcode,char *hex_code)
{
    FILE *optab=fopen("optab.txt","r");
    char code[MAX_OPCODE_SIZE],hex_value[3];
    if(!optab)
    {
        printf("Error opening optab.txt\n");
        exit(1);
    }
    while(fscanf(optab,"%s\t%s",code,hex_value)!=EOF)
    {
        if(strcmp(code,opcode)==0)
        {
            strcpy(hex_code,hex_value);
            fclose(optab);
            return 3;
        }
    }
    fclose(optab);
    return -1;
}

void convert_to_object_code(char *operand,char *object_code)
{
    int value=atoi(operand);
    sprintf(object_code,"%06X",value);
}
int main()
{
    FILE *input=fopen("input.txt","r");
    FILE *output=fopen("output.txt","w");
    char label[MAX_LABEL_SIZE],opcode[MAX_OPCODE_SIZE],operand[MAX_OPERAND_SIZE];
    int locctr=0,start_address=0;
    char line[MAX_LINE_SIZE],object_code[MAX_OBJ_CODE_SIZE];
    char hex_opcode[3];
    if(!input | !output)
    {
        printf("Error Opening file\n");
        return 1;
    }
    fgets(line,MAX_LINE_SIZE,input);
    sscanf(line,"%s\t%s\t%s",label,opcode,operand);
    if(strcmp(opcode,"START") == 0)
    {
        start_address=strtol(operand,NULL,16);
        locctr=start_address;
        fprintf(output,"H^%s^%06X^000000\n",label,start_address);
        fgets(line,MAX_LINE_SIZE,input);
    }
    while(strcmp(opcode,"END") != 0)
    {
        sscanf(line,"%s\t%s\t%s",label,opcode,operand);
        if(label[0] != '.')
        {
            if(strcmp(label,"*")!=0)
            {
                int sym_index=search_symtab(label);
                if(sym_index == -1)
                {
                    insert_symtab(label,locctr);
                }
            }
        }
        int instruction_length=search_optab(opcode,hex_opcode);
        if(instruction_length != -1)
        {
            int sym_index=search_symtab(operand);
            if(sym_index != -1 && symtab[sym_index].address != -1)
            {
                sprintf(object_code,"%s%04X",hex_opcode,symtab[sym_index].address);
            }
            else if(sym_index == 1)
            {
                insert_symtab(operand,-1);
                sprintf(object_code,"%s0000",hex_opcode);
            }
            fprintf(output,"T^%06X^%02X^%s\n",locctr,instruction_length,object_code);
            locctr+=instruction_length;
        }
        else if(strcmp(opcode,"WORD")==0)
        {
            convert_to_object_code(operand,object_code);
            fprintf(output,"T^%06X^03^%s\n",locctr,object_code);
            locctr+=3;
        }
        else if(strcmp(opcode,"RESW") == 0)
        {
            locctr+=3*atoi(operand);
        }
        else if(strcmp(opcode,"RESB") == 0)
        {
            locctr+=atoi(operand);
        }
        else if(strcmp(opcode,"BYTE") == 0)
        {
            int length=strlen(operand);
            locctr+=length;
            fprintf(output,"T^%06X^%02X^%s\n",locctr,length,operand);
        }
        fgets(line,MAX_LINE_SIZE,input);
        sscanf(line,"%s\t%s\t%s",label,opcode,operand);
    }
    fprintf(output,"E^%06X\n",start_address);
    fclose(input);
    fclose(output);
    printf("Assembly Completed\n");
    return 0;
}


