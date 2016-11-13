#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define N 25
/*
#define DEBUG
*/

typedef struct block_s {
    int no;
    struct block_s *prev;
} block_t;


block_t *top[N];
int map[N]; /* where each block is*/

/* Declaration */
void pileAoverB(int a, int b, int n);
void validate(int n);


void moveToInitial(int a, int n){
    block_t *bTop = top[map[a]];
    top[map[a]] = bTop->prev;

    map[a] = bTop->no;
    bTop->prev = NULL;
    top[bTop->no] = bTop;

#ifdef DEBUG
    validate(n);
#endif
}

void moveAboveToInitial(int a, int n){
    block_t *bTop;
    
    bTop = top[map[a]];
    while (bTop->no != a){
        moveToInitial(bTop->no, n);
        bTop = top[map[a]];
    }
}

void moveAontoB(int a, int b, int n){
    moveAboveToInitial(a, n);
#ifdef DEBUG
    validate(n);
#endif
    moveAboveToInitial(b, n);
#ifdef DEBUG
    validate(n);
#endif
    pileAoverB(a, b, n);
}

void moveAoverB(int a, int b, int n){
    moveAboveToInitial(a, n);
#ifdef DEBUG
    validate(n);
#endif
    pileAoverB(a, b, n);
}

void pileAontoB(int a, int b, int n){
    moveAboveToInitial(b, n);
#ifdef DEBUG
    validate(n);
#endif
    pileAoverB(a, b, n);
}

void pileAoverB(int a, int b, int n){
    int oldLocA = map[a];
    block_t *otop = top[oldLocA];
    
    /* find A and move stack*/
    block_t *p = top[map[a]];
    while (p->no!=a){
        map[p->no] = map[b];
        p = p->prev;
    }
    map[p->no] = map[b];

    /* Update top */
    top[oldLocA] = p->prev;
    p->prev = top[map[b]];
    top[map[b]] = otop;

#ifdef DEBUG
    validate(n);
#endif
}

void printBottom(block_t *b){
    if (b==NULL) return;
    printBottom(b->prev);
    printf(" %d", b->no);
}

void printResult(int n){
    

    int i;
    for ( i = 0; i < n; i++){
        printf("%d:", i);
        block_t* ptr = top[i];
        printBottom(ptr);
        printf("\n");
    }

#ifdef DEBUG
    printf("Map: ");
    for (i = 0; i < n; i++){
        printf("%d ", map[i]);
    }
    printf("\n");
#endif
}


block_t* findInStack(int a){
    block_t *pa = top[map[a]];
    while (pa->no != a && pa!=NULL){
        pa = pa->prev;
    }
#ifdef DEBUG
    printf("findInStack a(%d): %d\n", a, pa->no);
#endif
    return pa;
}

void validate(int n){
    int i, j; 
    for ( i = 0; i < n; i++){
        j = 0;
        block_t *b = top[i];
        while (b!=NULL){
            assert( i == map[b->no]);
            assert( j++ < n);
            b = b->prev;
        }
    }

    for (i = 0; i < n; i++){
        assert(findInStack(i)!=NULL);
    }
}

int main(){

    bzero(top, sizeof(top));
    memset(map, -1, sizeof(map));

    int count=0;
    int n, a, b, i;
    scanf("%d", &n);

    for (i = 0; i < n; i++){
        top[i] = malloc(sizeof(block_t));
        top[i]->no = i;
        top[i]->prev = NULL;
        map[i] = i;
    }
    
    char cmd1[5], cmd2[5];

    while (1){
        scanf("%s", cmd1);
        if (strcmp("quit", cmd1)==0) break;

        scanf("%d", &a);
        scanf("%s", cmd2);
        scanf("%d", &b);

#ifdef DEBUG
        printf("CMD(%d): '%s' %d '%s' %d\n", count++, cmd1, a, cmd2, b);
#endif

        /* Check for illegal commands */
        if (map[a] == map[b]){
            continue;
        }
        
        if (strcmp("move", cmd1)==0){

            if (strcmp("onto", cmd2)==0){
                moveAontoB(a, b, n);
            }
            else if (strcmp("over", cmd2)==0){
                moveAoverB(a, b, n);
            }
            else {
                printf("Error\n");
            }
        }
        
        else if (strcmp("pile", cmd1)==0){
            if (strcmp("onto", cmd2)==0){
                pileAontoB(a, b, n);
            }
            else if (strcmp("over", cmd2)==0){
                pileAoverB(a, b, n);
            }
            else {
                printf("Error\n");
            }

        }
        else {
            printf("Error\n");
        }
#ifdef DEBUG
        printResult(n);
#endif
    }
    printResult(n);

    return 0;

}
