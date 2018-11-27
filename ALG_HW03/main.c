#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  int index;
  int inorder;
  int value;
  bool visited;
  int depth;
  struct node *left;
  struct node *right;
  struct node *parent;
  struct node *next_max;
} node_t;

typedef struct maxSum {
  int sum;
  int min_depth;
  int min_inorder;
} maxSum_t;

maxSum_t maxSum;
int final_number = 0;
node_t *root_curr_max = NULL;
node_t *root_input_tree = NULL;
int inorder_counter = 1;
int nodes_visited = 0;
int number_of_nodes = 0;
int finished = false;

node_t *new_node(node_t *parent, int value, int depth, int idx);
node_t *init(int *arr, int size, node_t *root, node_t *parent, int idx,
             int depth);
int max_path_down(node_t *root);
int max_path(node_t *root);
void select_path_both(node_t *root);
void select_left(node_t *root);
void select_right(node_t *root);
void find(node_t *root);

int main(int argc, char **argv) {
  int *amulet_array, size;
  node_t *root = NULL;

  scanf("%d", &size);
  number_of_nodes = size;
  amulet_array = (int *)malloc(sizeof(int) * size);

  for (int i = 0; i < size; i++) {
    scanf("%d", &amulet_array[i]);
  }

  root = init(amulet_array, size, root, NULL, 0, 0);
  root_input_tree = root;

  // printf("%d\n", max_path_down(root));

  while (!finished) find(root_input_tree);

  // printf("%d\n", max_path_down(root));
  printf("%d\n", final_number);

  return 0;
}

node_t *new_node(node_t *parent, int value, int depth, int idx) {
  node_t *node = (node_t *)malloc(sizeof(node_t));
  node->index = idx;
  node->value = value;
  node->parent = parent;
  node->depth = depth;
  node->left = NULL;
  node->right = NULL;
  node->visited = false;
  node->next_max = NULL;
  return node;
}

node_t *init(int *arr, int size, node_t *root, node_t *parent, int idx,
             int depth) {
  if (idx < size) {
    node_t *temp = new_node(parent, arr[idx], depth, idx);
    root = temp;

    root->left = init(arr, size, root->left, root, 2 * idx + 1, depth + 1);

    root->inorder = inorder_counter++;

    root->right = init(arr, size, root->right, root, 2 * idx + 2, depth + 1);
  }

  return root;
}

int max_path_down(node_t *root) {
  if (root == NULL) return 0;

  if (root->visited) {
    max_path_down(root->right);
    max_path_down(root->left);
    return 0;
  }

  int left = max_path_down(root->left);
  int right = max_path_down(root->right);

  if ((left + right + root->value) > maxSum.sum) {
    maxSum.sum = left + right + root->value;
    maxSum.min_depth = root->depth;
    maxSum.min_inorder = root->inorder;
    root_curr_max = root;
  }

  int ret = left >= right ? left : right;

  return (ret + root->value);
}

int max_path(node_t *root) {
  if (root == NULL) return 0;

  int left = max_path(root->left);
  int right = max_path(root->right);

  int ret = left >= right ? left : right;

  return ret + root->value;
}

void select_path_both(node_t *root) {
  if (root == NULL) return;

  root->visited = true;
  nodes_visited++;
  select_left(root->left);
  select_right(root->right);
  if (nodes_visited >= number_of_nodes) finished = true;
}

void select_left(node_t *root) {
  if (root == NULL) return;

  if (root->visited) return;

  root->visited = true;
  nodes_visited++;

  // if (root->parent != NULL) {
  //   node_t *parent = root->parent;
  //   node_t *parent_left = root->parent->left;
  //   node_t *parent_right = root->parent->right;
  //   if (root == parent_left) {
  //     parent->left = NULL;
  //   } else {
  //     parent->right = NULL;
  //   }
  //   root->parent = NULL;
  // }

  int left = max_path(root->left);
  int right = max_path(root->right);

  if (left >= right) {
    root->next_max = root->left;
    find(root->right);
  } else {
    root->next_max = root->right;
    find(root->left);
  }
  select_left(root->next_max);
}

void select_right(node_t *root) {
  if (root == NULL) return;

  if (root->visited) return;

  root->visited = true;
  nodes_visited++;

  // if (root->parent != NULL) {
  //   node_t *parent = root->parent;
  //   node_t *parent_left = root->parent->left;
  //   node_t *parent_right = root->parent->right;
  //   if (root == parent_left) {
  //     parent->left = NULL;
  //   } else {
  //     parent->right = NULL;
  //   }
  //   root->parent = NULL;
  // }

  int left = max_path(root->left);
  int right = max_path(root->right);

  if (left > right) {
    root->next_max = root->left;
    find(root->right);
  } else {
    root->next_max = root->right;
    find(root->left);
  }
  select_right(root->next_max);
}

void find(node_t *root) {
  if (root == NULL) return;

  maxSum.sum = INT_MIN;
  maxSum.min_depth = 0;
  maxSum.min_inorder = 0;

  max_path_down(root);
  node_t *current_root = root_curr_max;

  // if (current_root->parent != NULL) {
  //   node_t *parent = current_root->parent;
  //   node_t *parent_left = current_root->parent->left;
  //   node_t *parent_right = current_root->parent->right;
  //   if (current_root == parent_left) {
  //     parent->left = NULL;
  //   } else {
  //     parent->right = NULL;
  //   }
  //   current_root->parent = NULL;
  // }

  select_path_both(current_root);
  final_number++;
}
