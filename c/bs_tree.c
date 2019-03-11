#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>
#include<string.h>



typedef struct _tree_node_t {
    int         key;
    int         child_count;        // including self node
    struct _tree_node_t  *l_child;
    struct _tree_node_t  *r_child;
    struct _tree_node_t  *parent;
} tree_node_t;


tree_node_t *create(int key)
{
    tree_node_t *root = (tree_node_t*)malloc(sizeof(tree_node_t));
    if (root == NULL) {
        fprintf(stderr, "malloc memrory failed \n");
        return NULL;
    }
    root->key = key;
    return root;
}


//bool insert(const tree_node_t *root, int key) 
bool insert(tree_node_t *root, int key) 
{
    if (root == NULL) {
        fprintf(stderr, "root is null\n");
        return false;
    }

    tree_node_t *p = root;
    while (true) {
        if (key > p->key) {
            if (p->r_child) p = p->r_child;
            else break;
        }
        else if (key < p->key) {
           if (p->l_child) p = p->l_child;
           else break;
        }
        else {
            return false;       // insert failed: key duplicate 
        }
    }

    tree_node_t *tmp_node = (tree_node_t *)malloc(sizeof(tree_node_t));
    if (tmp_node == NULL) {
        fprintf(stderr, "alloc new node failed\n");
        return false;
    }
    tmp_node->key = key;
    tmp_node->parent = p;
    if (p->l_child == NULL) p->l_child = tmp_node;
    else p->r_child = tmp_node;
    return true;
}

void travel(tree_node_t *p)
{
    if (p == NULL) return;
    travel(p->l_child);
    printf("%d ", p->key);
    travel(p->r_child);
}

bool search(const tree_node_t *root, int key)
{
  
    return true;
}


int count(const tree_node_t *root, int key)
{

    return 0;
}


int main() {
    int a[10] = {0};
    int len = 10;
    time_t t;

    /* Intializes random number generator */
    srand((unsigned) time(&t));
    printf("source:\n");
    for (int i = 0; i < len; ++i) {
        a[i] = (int32_t)rand() % 100;
        printf("%d ", a[i]);
    }
    printf("\n");


    /* insert */
    tree_node_t *root = NULL;
    for (int i = 0; i < len; ++i) {
        if (root == NULL) {
            root = create(a[i]);
            if (root == NULL) {
                fprintf(stderr, "create tree failed\n");
                return -1;
            }
        }
        else {
            if (!insert(root, a[i])) {
                fprintf(stderr, "insert %d failed \n", a[i]);
                return -1;
            }
        }
    }

    /* travel */
    printf("bs_tree is: ");
    travel(root);
    printf("\n ");

    return 0;

}
