/*
Autor: Arthur Ferraz
*/
#include"RB.h"
#include <string.h>

typedef struct artigo
{
    int id;
    int ano;
    char autor[200];
    char titulo[200];
    char revista[200];
    char DOI[20];
    char palavraChave[200];
}Artigo;

Artigo* getArtigo(Node* node)//return pointer to Artigo type
{
    if(node != NULL)
        return (Artigo*) node->info;
    return NULL;
}

//*************************************************************functions needed by the RB library 

int getKey(Node* node)
{
    if(node != NULL)
        return getArtigo(node)->id;
    return 0;
}

int compareInfo(int info1, int info2)//comparing strings
{
    if(info1==info2){
        return 0;
    }
    else if(info1<info2){
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
void printKey2(Node* ptr)
{
    if(ptr != NULL)
        printf("\n%d\t%s", getArtigo(ptr)->id,getArtigo(ptr)->titulo);
}
void printTitle(Node* ptr)
{
    if(ptr != NULL)
        printf("%s", getArtigo(ptr)->titulo);
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
    printf("ANO: %d\n", ptr->ano);
    printf("AUTOR: %s\n", ptr->autor);
    printf("TITULO: %s\n", ptr->titulo);
    printf("REVISTA: %s\n", ptr->revista);
    printf("DOI: %s\n", ptr->DOI);
    printf("PALAVRA CHAVE: %s\n", ptr->palavraChave);
}

Artigo* createArtigo()
{
    Artigo* ptr = (Artigo*) malloc(sizeof(Artigo));
    if(ptr != NULL)
    {
        printf("Digite o ID: ");
        scanf("%d", &ptr->id);
        printf("Digite o ano: ");
        scanf("%d", &ptr->ano);
        setbuf(stdin, NULL);
        printf("Nome do Autor: ");
        fgets(ptr->autor, 200, stdin);
        printf("Titulo: ");
        fgets(ptr->titulo, 200, stdin);
        printf("Revista: ");
        fgets(ptr->revista, 200, stdin);
        printf("DOI: ");
        fgets(ptr->DOI, 20, stdin);
        printf("Palavra Chave: ");
        fgets(ptr->palavraChave, 200, stdin);
    }
    return ptr;
}

Node* addArtigo(Node* RB)
{
    Node* newPtr = createNodeRBTree(createArtigo());//gets Artigo content from input, allocate and fill a Artigo for those content and allocate and fill a Node with that Artigo
    if(insertNodeRBTree(&RB, RB, newPtr))
        printf("Adição foi um sucesso.\n");
    else//if it doesnt add to the AVL, we have to free this new Node we created to release memory
    {
        printf("Adição fracassou. Tente adicionar outro iD\n");
        destroyNodeRBTree(newPtr);//this does free to Artigo and Node
    }
    return RB; 
}

void menuTxt()
{
    printf("I : inserir artigo\n");
    printf("R : remover artigo\n");
    printf("P : pesquisar artigo\n");
    printf("M : Listar ID's\n");
    printf("L : Listar ID's acompanhadas pelos respectivos titulos\n");
    printf("Q : Sair\n");
}

void menu()
{
    char option = '0';
    int key;
    Node* RB = NULL;//where we store the AVL
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
                if(removeNodeRBTree(&RB, RB, key))
                    printf("remoção foi um sucesso.\n");
                else
                    printf("remoção fracassou.\n");
                break;
            case 'p':
            case 'P':
                printf("Digite a key que deseja pesquisar\n>");
                scanf("%d",&key);
                ptr = searchInfoRBTree(RB,key);//also show the keys it needed to pass by to reach or to know it doest exist
                if(ptr != NULL)
                    printArtigo(getArtigo(ptr));
                else
                    printf("key não está registrada\n");
                break;
            case 'm':
            case 'M':
                printRBTree(RB, 0);
                break;
            case 'l':
            case 'L':
                printIDTitle(RB);
                break;
            
           default:
                break;
        }
        printf("\n\n");
    }while(option != 'q' && option != 'Q');
    destroyRBTree(RB);
}
int main()
{
    menu();
}

