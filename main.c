#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>


#define INITIAL 3


typedef struct {
  int capacity;
  int size;
  int *data;
} MinHeap;


// Generate an empty heap
// Returns NULL if there was an error allocating space
MinHeap *new_heap() {
  MinHeap *h = malloc(sizeof(MinHeap));

  if(h == NULL)
    return NULL;
  
  h->capacity = INITIAL;
  h->size = 0;

  h->data = malloc(INITIAL * sizeof(int));
  if(h->data == NULL) {
    free(h);
    return NULL;
  }

  return h;
}

// Assigns more space if the heap is full
void ensure_space(MinHeap *root) {
  int capacity = root->capacity;
  
  if(root->size >= capacity) {
    int new_capacity = (capacity * 2);
    root->data = realloc(root->data, new_capacity * sizeof(int));
    root->capacity = new_capacity;
  }
}

// Basic swap function
void swap(int *array, int i, int j) {
  int temp = array[i];
  array[i] = array[j];
  array[j] = temp;
}

// Turn our tree in a heap
void heapify_up(MinHeap *root, int index) {
  int key = root->data[index];
  int parent_index = (index - 1) / 2;
  int parent = root->data[parent_index];

  if (key < parent) {
    swap(root->data, index, parent_index);
    heapify_up(root, parent_index);
  }
}

void heapify_down(MinHeap *root, int index) {
  int smallest = index;
  int l = (index * 2) + 1;
  int r = (index * 2) + 2;

  int size = root->size - 1;

  if(l < size && root->data[l] < root->data[smallest]) {
    smallest = l;
  }

  if(r < size && root->data[r] < root->data[smallest]) {
    smallest = r;
  }

  if(smallest != index) {
    swap(root->data, index, smallest);
    heapify_down(root, smallest);
  }
}

// Insert an element in our heap
void insert(MinHeap *root, int new_key) {
  ensure_space(root);

  root->data[root->size] = new_key;
  root->size++;

  heapify_up(root, (root->size - 1));
}

// Searches for a key in the heap
// Returns the index, or -1 if nothing was found
// todo: make it O(n/2) instead of O(n)
int find(MinHeap *root, int key) {
  int index = 0;

  while(index < root->size && root->data[index] != key) {
    index++;
  }

  if(index >= root->size) {
    return -1;
  }

  return index;
}


// Delete an element from the heap
void delete(MinHeap *root, int key) {
  int index = find(root, key);
  int last = root->size - 1;

  swap(root->data, index, last);

  // Delete the last element
  root->data[last] = 0;
  root->size--;

  if(index == last)
    return;

  int parent = index / 2;

  if(root->data[index] < root->data[parent]) {
    heapify_up(root, index);
  } else {
    heapify_down(root, index);
  }
}

// Print the array in a nice way
void print_array(int *data, int size) {
  printf("[ ");
  for(int i = 0; i < size; i++) {
    printf("%d ", data[i]);
  }
  printf("]\n");
}


// Testing
int main() {
  MinHeap *h = new_heap();
  int input;
  char cmd;

  if(h == NULL)
    return EXIT_FAILURE;
  
  do {
    printf("Command: ");
    scanf("%c", &cmd);

    if(cmd == 'q')
      break;

    printf("Value: ");
    scanf("%d", &input);

    switch(cmd) {
      case 'i':
        insert(h, input);
        break;
      case 'd':
        delete(h, input);
        break;
    }

    print_array(h->data, h->size);
  } while(cmd != 'q');

  return EXIT_SUCCESS;
}
