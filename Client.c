/*
Autor: Arthur Ferraz
*/
#include"RB.h"
#include <string.h>

typedef struct coluna
{
    char* linha1;
    char* linha2;
    char* linha3;
}Coluna;

Coluna* getColuna(Node* node)//return pointer to Coluna type
{
    if(node != NULL)
        return (Coluna*) node->info;
    return NULL;
}

//*************************************************************functions needed by the RB library 

void* getKey(Node* node)
{
    if(node != NULL)
        return getColuna(node)->linha1;
    return NULL;
}

int compareInfo(void* info1, void* info2)//comparing strings
{
    int aux = strcmp((char*)info1, (char*)info2);
    if(aux == 0)
        return 0;
    else if (aux < 0)
        return -1;
    else 
        return 1;
}

void destroyInfo(void* info)
{
    if(info != NULL)
    {
        free(((Coluna*)info)->linha1);
        free(((Coluna*)info)->linha2);
        free(((Coluna*)info)->linha3);
    }
    free((Coluna*)info);
}

void printKey(Node* ptr)
{
    if(ptr != NULL)
        printf("%s", getColuna(ptr)->linha1);
}

//*************************************************************END

void fillColuna(Coluna* ptr)
{//get information from input and store inside Coluna respective members
    printf("Conteúdo da linha 1: ");
    scanf("%s", ptr->linha1);
/*    printf("\nConteúdo da linha 2: ");
    scanf("%s", ptr->linha2);
    printf("\nConteúdo da linha 3: ");
    scanf("%s", ptr->linha3);*/
}

void printColuna(Coluna* ptr)
{
    printf("linha 1: %s\n", ptr->linha1);
    printf("linha 2: %s\n", ptr->linha2);
    printf("linha 3: %s\n", ptr->linha3);
}

Coluna* createColuna()
{
    Coluna* ptr = (Coluna*) malloc(sizeof(Coluna));
    if(ptr != NULL)
    {
        ptr->linha1 = malloc(sizeof(char)*100);//no word bigger than 100 characters is going to be processed
        ptr->linha2 = malloc(sizeof(char)*100);
        ptr->linha3 = malloc(sizeof(char)*100);
        fillColuna(ptr);//call the input to fill it's contents
    }
    return ptr;
}

Node* addColuna(Node* RB)
{
    Node* newPtr = createNodeRBTree(createColuna());//gets Coluna content from input, allocate and fill a Coluna for those content and allocate and fill a Node with that Coluna
    if(insertNodeRBTree(&RB, RB, newPtr))
        printf("Adição foi um sucesso.\n");
    else//if it doesnt add to the AVL, we have to free this new Node we created to release memory
    {
        printf("Adição foi um fracasso.\n");
        destroyNodeRBTree(newPtr);//this does free to Coluna and Node
    }
    return RB; 
}

void menuTxt()
{
    printf("I : inserir coluna\n");
    printf("R : remover coluna\n");
    printf("P : pesquisar coluna\n");
    printf("M : mostrar keys\n");
    printf("Q : Sair\n");
}

void menu()
{
    char option = '0';
    char* key = (char*) malloc(sizeof(char));//for search porpouse
    if(key == NULL)//something went wrong while allocating? stops the execution
        return;
    Node* RB = NULL;//where we store the AVL
    Node* ptr = NULL;//auxiliary
    do{
        menuTxt();//print the menu
        printf("Escolha uma opção:\n>");
        scanf("%c", &option);
        switch(option)
        {
            case 'i':
            case 'I':
                RB= addColuna(RB); 
                break;
            case 'r':
            case 'R':
                printf("Digite a key que deseja remover\n>");
                scanf("%s", key);
                if(removeNodeRBTree(&RB, RB, key))
                {
                    printf("remoção foi um sucesso.\n");
                    printRBTree(RB, 0);
                }
                else
                    printf("remoção foi um fracasso.\n");
                break;
            case 'p':
            case 'P':
                printf("Digite a key que deseja pesquisar\n>");
                scanf("%s", key);
                ptr = searchInfoRBTree(RB, key);//also show the keys it needed to pass by to reach or to know it doest exist
                if(ptr != NULL)
                    printf("linha 1: %s\nlinha 2: %s\nlinha 3: %s\n", getColuna(ptr)->linha1, getColuna(ptr)->linha2, getColuna(ptr)->linha3);//print Coluna content
                else
                    printf("key não está registrada\n");
                break;
           case 'm':
           case 'M':
                printRBTree(RB, 0);
                break;
           default:
                break;
        }
        setbuf(stdin, NULL);//removes \n from buffer
        printf("\n\n");
    }while(option != 'q' && option != 'Q');
    destroyRBTree(RB);
}
int main()
{
    menu();
}
