#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int value;
    struct node *left;
    struct node *right;
} node_t;

node_t *new_node(int value);
node_t *init(int *arr, int size, node_t *root, int i);
void print_in_order(node_t *root);
void print_pre_order(node_t *root);

int main(int argc, char **argv)
{
    int size, *amulet_array;
    node_t *root;

    scanf("%d", &size);
    amulet_array = (int *)malloc(sizeof(int) * size);

    for (int i = 0; i < size; i++)
    {
        scanf("%d", &amulet_array[i]);
    }

    root = init(amulet_array, size, root, 0);

    print_pre_order(root);

    return 0;
}

node_t *new_node(int value)
{
    node_t *node = (node_t *)malloc(sizeof(node_t));
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

node_t *init(int *arr, int size, node_t *root, int i)
{
    if (i < size)
    {
        node_t *temp = new_node(arr[i]);
        root = temp;

        root->left = init(arr, size, root->left, 2 * i + 1);

        root->right = init(arr, size, root->right, 2 * i + 2);
    }

    return root;
}

void print_tree(node_t *node)
{
    if (node == NULL)
        return;
    else
    {
        printf("%d", node->value);
        print_tree(node->left);
        print_tree(node->right);
    }
}

void print_in_order(node_t *root)
{
    if (root != NULL)
    {
        print_in_order(root->left);
        printf("%d ", root->value);
        print_in_order(root->right);
    }
}

void print_pre_order(node_t *root)
{
    if (root != NULL)
    {
        printf("%d ", root->value);
        print_pre_order(root->left);
        print_pre_order(root->right);
    }
}
