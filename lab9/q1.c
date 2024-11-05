#include <stdio.h>

struct Nod {
    int dat;
    struct Nod* lft;
    struct Nod* ryt;
};

struct Nod* createNod(int dat) {
    struct Nod* newNod = (struct Nod*)malloc(sizeof(struct Nod));
    newNod->dat = dat;
    newNod->lft = newNod->ryt = NULL;
    return newNod;
}

struct Nod* insert(struct Nod* root, int dat) {
    if (root == NULL) {
        return createNod(dat);
    }
    if (dat < root->dat) {
        root->lft = insert(root->lft, dat);
    } else if (dat > root->dat) {
        root->ryt = insert(root->ryt, dat);
    }
    return root;
}

struct Nod* deletNod(struct Nod* root, int dat) {
    if (root == NULL) return root;
    if (dat < root->dat) {
        root->lft = deletNod(root->lft, dat);
    } else if (dat > root->dat) {
        root->ryt = deletNod(root->ryt, dat);
    } else {
        if (root->lft == NULL) {
            struct Nod* temp = root->ryt;
            free(root);
            return temp;
        } else if (root->ryt == NULL) {
            struct Nod* temp = root->lft;
            free(root);
            return temp;
        }
        struct Nod* succPrnt = root;
        struct Nod* succ = root->ryt;

        while (succ->lft != NULL) {
            succPrnt = succ;
            succ = succ->lft;
        }
        root->dat = succ->dat;

        if (succPrnt != root) {
            succPrnt->lft = deletNod(succPrnt->lft, succ->dat);
        } else {
            succPrnt->ryt = deletNod(succPrnt->ryt, succ->dat);
        }
    }
    return root;
}

void inorder(struct Nod* root) {
    if (root != NULL) {
        inorder(root->lft);
        printf("%d ", root->dat);
        inorder(root->ryt);
    }
}

int main() {
    struct Nod* root = NULL;
    int choic, val;
    while (1) {
        printf("\n1. Insert node");
        printf("\n2. Delet node");
        printf("\n3. Dispaly tree (Inorder)");
        printf("\n4. Ext");
        printf("\nEntr choice: ");
        scanf("%d", &choic);
        switch (choic) {
            case 1: {
                int n;
                printf("Numbr of nodes: ");
                scanf("%d", &n);              
                for (int i = 0; i < n; i++) {
                    printf("Val %d: ", i + 1);
                    scanf("%d", &val);
                    root = insert(root, val);
                }
                break;
            }
            case 2:
                printf("Val to delte: ");
                scanf("%d", &val);
                root = deletNod(root, val);
                break;
            case 3:
                printf("Inorder tree: ");
                inorder(root);
                printf("\n");
                break;
            case 4:
                return 0;
            default:
                printf("Invld chice!\n");
        }
    }
}