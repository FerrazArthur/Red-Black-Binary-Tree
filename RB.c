#include "RB.h"
#define ABORT 0
#define HASNEWSON 1
#define RIGHTGRANDSON 2
#define LEFTGRANDSON 3
#define DOUBLEBLACK 4
#define RBBALANCED 5

void destroyNodeRBTree(Node* node)
{
    if(node != NULL)
        destroyInfo(node->info);
    free(node);
}

void destroyRBTree(Node* node)
{
    if(node != NULL)
    {
        destroyRBTree(node->leftRB);
        destroyRBTree(node->rightRB);
        destroyNodeRBTree(node);
    }
}

Node* createNodeRBTree(void* info)
{
    Node* ptr = (Node*) malloc(sizeof(Node));
    if(ptr != NULL)
    {
        ptr->info = info;
        ptr->color = Red;
        ptr->rightRB = NULL;
        ptr->leftRB = NULL;
    }
    return ptr;
}

void* getInfo(Node* node)
{
    if(node != NULL)
        return node->info;
    return NULL;
}

void changeColor(Node* node, enum Color newcolor)
{
    if(node != NULL)
        node->color = newcolor;
}

int isRed(Node* node)
{
    if (node != NULL)
        if (node->color == Red)
            return 1;
    return 0;
}

void printRBTree(Node* head, int level)
{
    if(head != NULL)
    {
        printRBTree(head->rightRB, level+1);
        for(int i = 0; i < level; i++)
            printf("    ");
        if(isRed(head))
            printf("\033[1;31m");
        printKey(head);
        if(isRed(head))
            printf("\033[0;0m\n");
        else
            printf("\n");
/*        if(isRed(head))
            printf(" (Vermelho)\n");
        else
            printf(" (Preto)\n");
            */
        printRBTree(head->leftRB, level+1);
    }
}

Node* findSmallestNodeRBTree(Node* head)
{
    if(head != NULL)
    {
        if(head->leftRB != NULL)
            return findSmallestNodeRBTree(head->leftRB);
    }
    return head;
}

Node* searchInfoRBTree(Node* head, void* info)
{
    return NULL;
}

void LRotation(Node** head)
{
    /*
    to all rotations: 
    *head = Axis of rotation
    son = subtree of *head
    grandSon = subtree of subtree of *head
    */
    Node* son = *head;
    *head = son->leftRB;
    son->leftRB = (*head)->rightRB;
    (*head)->rightRB = son;
}

void LRRotation(Node** head)
{
    Node* son = *head;
    Node* grandSon = son->leftRB;
    *head = grandSon->rightRB;
    son->leftRB = (*head)->rightRB;
    grandSon->rightRB = (*head)->leftRB;
    (*head)->leftRB = grandSon;
    (*head)->rightRB = son;
}

void RRotation(Node** head)
{
    Node* son = *head;
    *head = son->rightRB;
    son->rightRB = (*head)->leftRB;
    (*head)->leftRB = son;
}

void RLRotation(Node** head)
{
    Node* son = *head;
    Node* grandSon = son->rightRB;
    *head = grandSon->leftRB;
    son->rightRB = (*head)->leftRB;
    grandSon->leftRB = (*head)->rightRB;
    (*head)->rightRB = grandSon;
    (*head)->leftRB = son;
}

int insertNodeRBTree(Node** head, Node* root, Node* newNode)
{
    int aux = 0;
    if((*head) == NULL)
    {
        *head = newNode;
        if(root == NULL)//the tree is empty so newNode is going to be the root, needs to be Black
            changeColor(*head, Black);
        return HASNEWSON;
    }
    else if(compareInfo(getKey(*head), getKey(newNode)) == 0 || newNode == NULL)
        return 0;//doesnt suport repetition of info
    else if(compareInfo(getKey(*head), getKey(newNode)) < 0)
    {//newNode's info is bigger than current's
       if((aux = insertNodeRBTree(&(*head)->rightRB, root, newNode)) != ABORT)//recursive call passing rightRB
        {
            if(aux == HASNEWSON)// aux iquals 1 means that the node in this Node(head*) rightRB is Red
                return RIGHTGRANDSON;//tells previous recursive calls that a red Node is located in his rightRB pointer
            else if(aux == RIGHTGRANDSON || aux == LEFTGRANDSON)
            {
                if(isRed((*head)->rightRB))//if head*'s rightRB points to a Red Node, RB properties are being violated
                {
                    if((*head)->leftRB != NULL && (*head)->leftRB->color == Red)//if newNode uncle is also red
                    //this is the case where we need only to change colors in order to keep this tree with all it's RB properties
                    {
                        //paint it black(the father and the uncle of the new added node
                        changeColor((*head)->rightRB, Black);
                        changeColor((*head)->leftRB, Black);
                        if(*head != root)//if grandfather isnt root, paint it red
                            changeColor(*head, Red);
                        return HASNEWSON;
                    }
                    else//if uncle is Black: rotate
                    {
                        if(aux == RIGHTGRANDSON)//rotate Son to *head
                            RRotation(head);
                        else//rotate GrandSon to *head
                            RLRotation(head);
                        changeColor(*head, Black);
                        changeColor((*head)->rightRB, Red);
                        changeColor((*head)->leftRB, Red);
                    }
                }
                    return RBBALANCED;//tells recursive calls to do nothing
            }
            return RBBALANCED;
        }
    }
    else
    {//newNode's info is smaller than current's
            if((aux = insertNodeRBTree(&(*head)->leftRB, root, newNode)) != ABORT)//recursive call passing leftRB
            {
            if(aux == HASNEWSON)// aux iquals 1 means that the node in this Node(head*) leftRB is Red
                return LEFTGRANDSON;//tells previous recursive calls that a red Node is located in his leftRB pointer
            else if(aux == LEFTGRANDSON || aux == RIGHTGRANDSON)
            {
                if(isRed((*head)->leftRB))//if head*'s leftRB points to a Red Node, RB properties are being violated
                {
                    if((*head)->rightRB != NULL && isRed((*head)->rightRB))//if newNode uncle is also red
                    //this is the case where we need only to change colors to keep this tree with all it's RB properties
                    {
                        //paint it black(the father and the uncle of the new added node
                        changeColor((*head)->rightRB, Black);
                        changeColor((*head)->leftRB, Black);
                        if(*head != root)//if grandfather isnt root, paint it red
                            changeColor(*head, Red);
                        return HASNEWSON;
                    }
                    else//if uncle is Black: rotate
                    {
                        if(aux == LEFTGRANDSON)//rotate father to *head
                            LRotation(head);
                        else//rotate son to *head
                            LRRotation(head);
                        changeColor(*head, Black);
                        changeColor((*head)->leftRB, Red);
                        changeColor((*head)->rightRB, Red);
                    }
                }
                return RBBALANCED;//tells recursive calls to do nothing
            }
            return RBBALANCED;
        }
    }
    return aux;
}

int removeNodeRBTree(Node** head,Node* root, void* info)
{
    int answer = 0;
    Node* ptr = NULL;
    void* aux = NULL;
    if (*head == NULL)
        return 0;
    int compare = compareInfo(getKey(*head), info);
    if(compare == 0)
    {//remover *head
        if((*head)->leftRB == NULL || (*head)->rightRB == NULL)
        {
            ptr = *head;//this will be removed
            if(ptr->rightRB != NULL)//it has a right subtree 
            {
                *head = ptr->rightRB;//substitute ptr by it's rightRB subtree
                if(!isRed(ptr))//if the node to be removed is not Red (is Black)
                /*Hipotesis: Never you will remove, in a RBTree, a Red node that is not a leaf*/
                {
                    if(isRed(*head))//substitute node is red? 
                    {
                        changeColor(*head, Black);//paint it Black
                        answer = RBBALANCED;
                    }
                    else
                        answer = DOUBLEBLACK;
                }
            }
            else if(ptr->leftRB != NULL)//it has a left subtree
            {
                *head = ptr->leftRB;
                if(!isRed(ptr))//if it is Black
                {
                    if(isRed(*head))
                    {
                        changeColor(*head, Black);
                        answer = RBBALANCED;
                    }
                    else
                        answer = DOUBLEBLACK;
                }
            }
            else//has no subtree at all
            {
                *head = NULL;
                if(isRed(ptr) || ptr == root)//if it is Red of the root, the RBTree will remain balanced after it's deletion
                    answer = RBBALANCED;
                else//is Black? mark doubleBlack
                    answer = DOUBLEBLACK;
            }
            destroyNodeRBTree(ptr);
            return answer;
        }
        ptr = findSmallestNodeRBTree((*head)->rightRB);
        aux = (*head)->info;
        (*head)->info = ptr->info;
        ptr->info = aux;
        compare = -1;//This is necessary because we swap *head info that is located in his rightSubTree and need to find it again
    }
    if(compare < 0)
    {//*head is smaller than info
        if(answer == 0)
            answer = removeNodeRBTree(&(*head)->rightRB, root, info);
        if(answer == DOUBLEBLACK)
        {
            enum Color auxColor = (*head)->color;//no matter the *head initial color, we must* keep that after the rotations
            if(isRed((*head)->leftRB))//Rebalance for cases 1.1 and 1.2
            {//both it's children are not NULL and Black (they cant be red and have at least 1 Black height
                changeColor((*head)->leftRB, Black);//1.1a
                if((*head)->rightRB == NULL)//case 1.1 -- the Black height is 1
                    changeColor(*head, Red);//1.1b
                else
                    changeColor((*head)->leftRB->rightRB, Red);
                LRotation(head);
            }
            else
            {//case 2
                if((*head)->leftRB == NULL)
                    if(isRed(*head))
                        changeColor(*head, Black);
                    else
                        return DOUBLEBLACK;

                else if(!isRed((*head)->leftRB->rightRB) && !isRed((*head)->leftRB->leftRB))
                {//case 2.2.3
                    changeColor((*head)->leftRB, Red);
                    if(isRed(*head))//case 2.2.3.1
                        changeColor(*head, Black);
                    else//case 2.2.3.2
                        return DOUBLEBLACK;
                }
                else if(isRed((*head)->leftRB->rightRB))
                {//case 2.1, 2.2.2 and 2.2.4
                    changeColor(*head, Black);
                    LRRotation(head);
                    changeColor(*head, auxColor); 
                }
                else if(isRed((*head)->leftRB->leftRB))
                {//case 2.2.1
                    changeColor(*head, Black);
                    LRotation(head);
                    changeColor(*head, auxColor);
                    changeColor((*head)->leftRB, Black);
                }
            } 
            return RBBALANCED;
        }
    }
    else
    {//*head is bigger than info
        if(answer == 0)
            answer = removeNodeRBTree(&(*head)->leftRB, root, info);
        if(answer == DOUBLEBLACK)
        {
            enum Color auxColor = (*head)->color;//no matter the *head initial color, we must* keep that after the rotations
            if(isRed((*head)->rightRB))//Rebalance for cases 1.1 and 1.2
            {//both it's children are not NULL and Black (they cant be red and have at least 1 Black height
                changeColor((*head)->rightRB, Black);//1.1a
                if((*head)->leftRB == NULL)//case 1.1 -- the Black height is 1
                    changeColor(*head, Red);//1.1b
                else
                    changeColor((*head)->rightRB->leftRB, Red);
                RRotation(head);
            }
            else
            {//case 2
                if((*head)->rightRB == NULL)
                    if(isRed(*head))
                        changeColor(*head, Black);
                    else
                        return DOUBLEBLACK;

                else if(!isRed((*head)->rightRB->leftRB) && !isRed((*head)->rightRB->rightRB))
                {//case 2.2.3
                    changeColor((*head)->rightRB, Red);
                    if(isRed(*head))//case 2.2.3.1
                        changeColor(*head, Black);
                    else//case 2.2.3.2
                        return DOUBLEBLACK;
                }
                else if(isRed((*head)->rightRB->leftRB))
                {//case 2.1, 2.2.2 and 2.2.4
                    changeColor(*head, Black);
                    RLRotation(head);
                    changeColor(*head, auxColor); 
                }
                else if(isRed((*head)->rightRB->rightRB))
                {//case 2.2.1
                    changeColor(*head, Black);
                    RRotation(head);
                    changeColor(*head, auxColor);
                    changeColor((*head)->rightRB, Black);
                }
            }
            return RBBALANCED;
        }
    }
    return answer;
}
