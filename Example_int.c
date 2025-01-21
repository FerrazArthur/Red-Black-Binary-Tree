/*
Autor: Arthur Ferraz
*/
#include"RB.h"
#include <string.h>

typedef struct artigo
{
    int id;
}Artigo;

Artigo* getArtigo(Node* node)//return pointer to Artigo type
{
    if(node != NULL)
        return (Artigo*) node->info;
    return NULL;
}

//*************************************************************functions needed by the RB library 

void* getKey(Node* node)
{
    if(node != NULL)
        return &getArtigo(node)->id;
    return 0;
}

int compareInfo(void* info1, void* info2)//comparing integers
{
    if(*(int*)info1 == *(int*)info2){
        return 0;
    }
    else if(*(int*)info1 < *(int*)info2){
        return -1;
    }
    else 
        return 1;
}


void destroyInfo(void* info)
{
    free(info);
}

void printKey(Node* ptr)
{
    if(ptr != NULL)
        printf("%d", getArtigo(ptr)->id);
}

//*************************************************************END

/*void fillArtigo(Artigo* ptr)
{//get information from input and store inside Artigo respective members
    printf("Conteúdo da linha 1: ");
    scanf("%s", ptr->linha1);
    printf("\nConteúdo da linha 2: ");
    scanf("%s", ptr->linha2);
    printf("\nConteúdo da linha 3: ");
    scanf("%s", ptr->linha3);
}*/

void printArtigo(Artigo* ptr)
{
    printf("ID: %d\n", ptr->id);
}

Artigo* createArtigo()
{
    Artigo* ptr = (Artigo*) malloc(sizeof(Artigo));
    if(ptr != NULL)
    {
        printf("Digite o ID: ");
        scanf("%d", &ptr->id);
    }
    return ptr;
}

Node* addArtigo(Node* RB)
{
    Node* newPtr = createNodeRBTree(createArtigo());//gets Artigo content from input, allocate and fill a Artigo for those content and allocate and fill a Node with that Artigo
    int answer = insertNodeRBTree(&RB, RB, newPtr);
    if(answer == 0 && answer == 2)//2 was used to indicate that it found the node to be already in the Tree and did not inserted
    {//if it doesnt add to the AVL, we have to free this new Node we created to release memory
        printf("Adição fracassou. Tente adicionar outro iD\n");
        destroyNodeRBTree(newPtr);//this does free to Artigo and Node
    }
    else
        printf("Adição foi um sucesso.\n");
    return RB; 
}

void menuTxt()
{
    printf("I : inserir inteiro\n");
    printf("R : remover inteiro\n");
    printf("M : Listar ID's\n");
    printf("Q : Sair\n");
}

void menu()
{
    char option = '0';
    int key;
    Node* RB = NULL;//where we store the RB Tree
    Node* ptr = NULL;//auxiliary
    do{
        menuTxt();//print the menu
        printf("Escolha uma opção:\n>");
        scanf(" %c", &option);
        printf("\n");
        switch(option)
        {
            case 'i':
            case 'I':
                RB= addArtigo(RB); 
                break;
            case 'r':
            case 'R':
                printf("Digite a key que deseja remover\n>");
                scanf("%d",&key);
                if(removeNodeRBTree(&RB, RB, &key))
                    printf("remoção foi um sucesso.\n");
                else
                    printf("remoção fracassou.\n");
                break;
            case 'p':
            case 'P':
                printf("Digite a key que deseja pesquisar\n>");
                scanf("%d", &key);
                ptr = searchInfoRBTree(RB, &key);//also show the keys it needed to pass by to reach or to know it doest exist
                if(ptr != NULL)
                    printArtigo(getArtigo(ptr));
                else
                    printf("key não está registrada\n");
                break;
            case 'm':
            case 'M':
                printRBTree(RB,printKey, 0);
                break;
           default:
                break;
        }
        printf("\n\n");
    }while(option != 'q' && option != 'Q');
    destroyRBTree(&RB);
}
int main()
{
    menu();
}
