#include "Header.h"

tree* addTreeElement(tree *p, flat tmp) {
    if (p == NULL) {
        p = (tree*)malloc(sizeof(tree));
        p->flat = tmp;
        p->right = p->left = NULL;
    }
    else if (strcmp(tmp.name, p->flat.name) < 0) {
        p->left = addTreeElement(p->left, tmp);
    }
    else {
        p->right = addTreeElement(p->right, tmp);
    }
    return p;
}

tree* treeFromArray(flat *arr, unsigned int n) {
    tree *p = NULL;
    if (arr == NULL) return NULL;
    for (unsigned int i = 0; i < n; i++) {
        p = addTreeElement(p, arr[i]);
    }
    return p;
}

tree* searchEl(tree *root, char *v) {
    if (root == NULL || !strcmp(root->flat.name, v)) {
        return root;
    }
    if (strcmp(v, root->flat.name) < 0) {
        return searchEl(root->left, v);
    }
    else {
        return searchEl(root->right, v);
    }
}

void searchTree(tree * root, char *val) {
    tree *cur = NULL,
    *tmp = root;
    do {
        cur = searchEl(tmp, val);
        if (!cur) break;
        printFlat(cur->flat);
        tmp = cur -> right;
    } while(tmp);
}

void freeTree(tree *p) {
    if(p != NULL) {
        freeTree(p->left);
        freeTree(p->right);
        free(p);
    }
}

