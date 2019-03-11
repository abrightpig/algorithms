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
    root->l_child = root->r_child = NULL;
    return root;
}


tree_node_t *insert(tree_node_t *root, int key) 
{
    //printf("inserting: key=%d\n", key);
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

tree_node_t *insert_r(tree_node_t *root, int key)
{
    if (root == NULL) return NULL;

    tree_node_t *tmp = NULL;
    if (key < root->key) tmp = insert_r(root->l_child, key);
    else if (key > root->key) tmp = insert_r(root->r_child, key);
    else return root;

    if (tmp == NULL) {
        tree_node_t *tmp_node = (tree_node_t *)malloc(sizeof(tree_node_t));
        if (tmp_node == NULL) {
            fprintf(stderr, "alloc new node failed\n");
            return NULL;
        }
        tmp_node->key = key;
        tmp_node->parent = root;
        tmp_node->l_child = tmp_node->r_child = NULL;
        if (key < root->key) root->l_child = tmp_node;
        else root->r_child = tmp_node;
    }
    return root;
}

tree_node_t *insert_r2(tree_node_t *p, int key)
{
    if (p == NULL) {
        p = (tree_node_t *)malloc(sizeof(tree_node_t));
        if (p == NULL) {
            fprintf(stderr, "alloc new node failed\n");
            return NULL;
        }
        p->key = key;
        p->l_child = p->r_child = NULL;
    }
    else if (key < p->key) {
        p->l_child = insert_r2(p->l_child, key);
    }
    else if (key > p->key) {
        p->r_child = insert_r2(p->r_child, key);
    }
    /* if key == p->key : do nothing*/

    return p;
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


tree_node_t *insert_nodes(int *arr, int len)
{
    tree_node_t *root = NULL;
    for (int i = 0; i < len; ++i) {
        tree_node_t *result = insert(root, arr[i]);
        if (result == NULL) {
            fprintf(stderr, "create tree failed\n");
            return NULL;
        }
        root = result;
    }
    return root;
}


tree_node_t *insert_nodes_r(int *arr, int len)
{
    tree_node_t *root = NULL;
    for (int i = 0; i < len; ++i) {
        /*
        if (root == NULL) {
            root = create(arr[i]);
        }
        else {
            //root = insert_r(root, arr[i]);
        }
        */
        root = insert_r2(root, arr[i]);
        if (root == NULL) {
            fprintf(stderr, "create tree failed\n");
            return NULL;
        }
    }
    return root;
}


#define ARRAY_SIZE  10
#define RAND_RANGE  100

int main() {
    int a[ARRAY_SIZE] = {0};
    int len = ARRAY_SIZE;
    time_t t;

    /* generate random source data */
    srand((unsigned) time(&t));
    printf("source:\n");
    for (int i = 0; i < len; ++i) {
        a[i] = (int32_t)rand() % RAND_RANGE;
        printf("%d ", a[i]);
    }
    printf("\n");


    /* insert */
    //tree_node_t *root = insert_nodes(a, len);
    tree_node_t *root = insert_nodes_r(a, len);
    if (root == NULL) {
        fprintf(stderr, "create tree failed\n");
        return -1;
    }

    /* travel */
    printf("bs_tree is: \n");
    travel(root);
    printf("\n ");

    return 0;

}
