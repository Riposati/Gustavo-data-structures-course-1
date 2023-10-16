#include<stdlib.h>
#include<stdio.h>
#include<time.h>

struct linkedList{
    int key;
    struct linkedList *next;
    struct linkedList *before;
}typedef LinkedList;

LinkedList *createNode(int key){
    LinkedList *aux = malloc(sizeof(LinkedList));
    aux->key = key;
    aux->next = aux;
    aux->before = aux;
    return aux;
}

LinkedList *insertNode(LinkedList *firstNode, int key){
    LinkedList *aux = createNode(key);

    if(firstNode==NULL)
        firstNode = aux;
    else{
        firstNode->before->next = aux;
        aux->next = firstNode;
        aux->before = firstNode->before;
        firstNode->before = aux;
    }
    return firstNode;
}

LinkedList *deleteNode(LinkedList *firstNode, int key){
    LinkedList *aux = firstNode;

    printf("key to be deleted from list -> (%d)\n",key);

    if(aux!=NULL){
        if(firstNode->key==key){ // first node
        
        aux = firstNode->next;
        aux->before = firstNode->before;
        firstNode->before->next=aux;
        
        if(firstNode->next==firstNode && firstNode->before==firstNode){ // if the list has only one node
            free(firstNode);
            firstNode = NULL;

        }else{
            free(firstNode);
            firstNode = aux;
        }

    }else if(aux->next!=firstNode && aux->key!=key){

            while(aux->key!=key && aux->next!=firstNode){
                aux = aux->next;
            }

            if(aux->next!=firstNode && aux->key==key){ // node in the middle

                LinkedList *aux2 = aux->before;
                aux2->next=aux->next;
                aux2->next->before=aux2;
                free(aux);

            }else if(aux->next==firstNode && aux->key==key){ // node in the end

                LinkedList *aux2 = aux->before;
                aux2->next = firstNode;
                firstNode->before = aux2;
                free(aux);
            }
        }
    }
    return firstNode;
}

void showList(LinkedList *firstNode){
    LinkedList *aux = firstNode;

    if(aux==NULL)
        printf("Empty List\n");
    else{
        printf("List going:\n");
        while(aux->next != firstNode){
            printf("%d -> ",aux->key);
            aux = aux->next;
        }

        printf("%d\n",aux->key);
    }
}

void showListInverse(LinkedList *firstNode){
    LinkedList *aux = firstNode;

    if(aux==NULL)
        printf("Empty List\n");
    else{
        printf("List going back:\n");
        while(aux->before != firstNode){
            printf("%d -> ",aux->before->key);
            aux = aux->before;
        }

        printf("%d\n",aux->before->key);
    }
}

int main(){
    LinkedList *first = NULL;
    srand(time(0));
    int numberOfRandoms = 5;
    int arrayOfRandoms[numberOfRandoms];
    int random;

    for(int i=0;i<numberOfRandoms;i++){ // generate n random numbers
        random = rand()%10000;
        first = insertNode(first,random);
        arrayOfRandoms[i] = random;
    }

    showList(first);
    showListInverse(first);

    for(int i=0;i<rand()%numberOfRandoms;i++){
        first = deleteNode(first, arrayOfRandoms[rand()%numberOfRandoms]);
    }

    showList(first);
    showListInverse(first);

    return 0;
}