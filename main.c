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
    int *temp = calloc(new_capacity, sizeof(int));
    memcpy(temp, root->data, capacity * sizeof(int));

    root->data = calloc(new_capacity, sizeof(int));
    memcpy(root->data, temp, new_capacity * sizeof(int));
    
    root->capacity = new_capacity;
    free(temp);
  }
}

// Basic swap function
void swap(int *array, int i, int j) {
  int temp = array[i];
  array[i] = array[j];
  array[j] = temp;
}

// Turn our tree in a heap
void heapify(MinHeap *root, int index) {
  int key = root->data[index];
  int parent_index = (index - 1) / 2;
  int parent = root->data[parent_index];

  if (key < parent) {
    swap(root->data, index, parent_index);
    heapify(root, parent_index);
  }
}

// Insert an element in our heap
void insert(MinHeap *root, int new_key) {
  ensure_space(root);

  root->data[root->size] = new_key;
  root->size++;

  heapify(root, (root->size - 1));
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

  if(h == NULL)
    return 1;
  
  do {
    printf("Input: ");
    scanf("%d", &input);
    if(input > 0) {
      insert(h, input);
      print_array(h->data, h->size);
    }
  } while(input > 0);

  return 0;
}
