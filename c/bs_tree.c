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


tree_node_t *insert(tree_node_t *root, int key) 
{
    printf("inserting: key=%d\n", key);
    if (root == NULL) {
        return create(key);
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
            return root;       // insert failed: key duplicate 
        }
    }

    tree_node_t *tmp_node = (tree_node_t *)malloc(sizeof(tree_node_t));
    if (tmp_node == NULL) {
        fprintf(stderr, "alloc new node failed\n");
        return NULL;
    }
    tmp_node->key = key;
    tmp_node->parent = p;
    if (key < p->key) p->l_child = tmp_node;
    else p->r_child = tmp_node;
    return root;
}


tree_node_t *insert_r(tree_node_t *root, int )
{

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

    /* generate random source data */
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
        tree_node_t *result = insert(root, a[i]);
        if (result == NULL) {
            fprintf(stderr, "create tree failed\n");
            return -1;
        }
        root = result;
    }

    /* travel */
    printf("bs_tree is: \n");
    travel(root);
    printf("\n ");

    return 0;

}
