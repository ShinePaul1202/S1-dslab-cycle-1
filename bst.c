#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* left;
    struct node* right;
};

struct node *root = NULL;

void cernode(int x) {
    struct node *newnode = (struct node*)malloc(sizeof(struct node));
    newnode->data = x;
    newnode->left = NULL;
    newnode->right = NULL;
    if (root == NULL) {
        root = newnode;
        printf("Created root node: %d\n", root->data);
    } else {
        printf("Node created: %d\n", newnode->data);
    }
}

void ins(int item) {
    if (root == NULL) {
        cernode(item);
        return;
    }
    struct node *cur = root;
    struct node *par = NULL;
    while (1) {
        par = cur;
        if (item < cur->data) {
            cur = cur->left;
            if (cur == NULL) {
                par->left = (struct node*)malloc(sizeof(struct node));
                par->left->data = item;
                par->left->left = par->left->right = NULL;
                printf("Inserted %d to the left of %d\n", item, par->data);
                return;
            }
        } else {
            cur = cur->right;
            if (cur == NULL) {
                par->right = (struct node*)malloc(sizeof(struct node));
                par->right->data = item;
                par->right->left = par->right->right = NULL;
                printf("Inserted %d to the right of %d\n", item, par->data);
                return;
            }
        }
    }
}

struct node* minValueNode(struct node* node) {
    struct node* current = node;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

struct node* del(struct node* root, int item) {
    if (root == NULL) return root;

    if (item < root->data)
        root->left = del(root->left, item);
    else if (item > root->data)
        root->right = del(root->right, item);
    else {
        if (root->left == NULL) {
            struct node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct node* temp = root->left;
            free(root);
            return temp;
        }

        struct node* temp = minValueNode(root->right);
        root->data = temp->data;
        root->right = del(root->right, temp->data);
    }
    return root;
}

void ser(int item) {
    struct node *cur = root;
    while (cur != NULL) {
        if (cur->data == item) {
            printf("Node %d found\n", item);
            return;
        }
        cur = (item < cur->data) ? cur->left : cur->right;
    }
    printf("Node %d not found\n", item);
}

void inorderTraversal(struct node *root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d  ", root->data);
        inorderTraversal(root->right);
    }
}

void preorderTraversal(struct node *root) {
    if (root != NULL) {
        printf("%d  ", root->data);
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }
}

void postorderTraversal(struct node *root) {
    if (root != NULL) {
        postorderTraversal(root->left);
        postorderTraversal(root->right);
        printf("%d  ", root->data);
    }
}

int main() {
    while (1) {
        int ch;
	    printf("\n-------BINARY SEARCH TREE OPERATIONS-------\n");
        printf("\n1.Create node\n2.Insert node\n3.Delete node\n4.Search node\n5.Inorder traversal\n6.Preorder traversal\n7.Postorder traversal\n8.Exit\n\nEnter your choice: ");
        scanf("%d", &ch);
        switch (ch) {
            case 1: {
                int x;
                printf("Enter the element of Node: ");
                scanf("%d", &x);
                cernode(x);
                break;
            }
            case 2: {
                int x1;
                printf("\nEnter the key to be inserted: ");
                scanf("%d", &x1);
                ins(x1);
                break;
            }
            case 3: {
                int x2;
                printf("\nEnter the key to be deleted: ");
                scanf("%d", &x2);
                root = del(root, x2);
                break;
            }
            case 4: {
                int x3;
                printf("\nEnter the key to be searched: ");
                scanf("%d", &x3);
                ser(x3);
                break;
            }
            case 5:
                printf("Inorder Traversal: ");
                inorderTraversal(root);
                printf("\n");
                break;
            case 6:
                printf("Preorder Traversal: ");
                preorderTraversal(root);
                printf("\n");
                break;
            case 7:
                printf("Postorder Traversal: ");
                postorderTraversal(root);
                printf("\n");
                break;
            case 8:
                printf("\nExiting.....\n");
                exit(0);
            default:
                printf("INVALID CHOICE\n");
        }
    }
    return 0;
}

