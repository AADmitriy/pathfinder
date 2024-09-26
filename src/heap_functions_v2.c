#include "pathfinder.h"
#include "../libmx/inc/libmx.h"


MinHeapNode* newMinHeapNode(int id, int weight) {
    MinHeapNode* minHeapNode = (MinHeapNode*)malloc(sizeof(MinHeapNode));
    minHeapNode->id = id;
    minHeapNode->weight = weight;
    return minHeapNode;
}
 
MinHeap* createMinHeap(int capacity) {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    minHeap->pos = (int*)malloc(capacity * sizeof(int));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (MinHeapNode**)malloc(capacity * sizeof(MinHeapNode*));
    return minHeap;
}

void del_minHeap(MinHeap** minHeap) {
    for (int i = 0; i < (*minHeap)->capacity; i++) {
        free((*minHeap)->array[i]);
    }
    free((*minHeap)->pos);
    free(*minHeap);
}

void swapMinHeapNode(MinHeapNode** a, MinHeapNode** b) {
    MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

void minHeapify(MinHeap* minHeap, int i) {
    int smallest, left, right;
    smallest = i;
    left = 2 * i + 1;
    right = 2 * i + 2;
 
    if (left < minHeap->size &&
        minHeap->array[left]->weight < minHeap->array[smallest]->weight) {
        smallest = left;
    }
    if (right < minHeap->size &&
        minHeap->array[right]->weight < minHeap->array[smallest]->weight) {
        smallest = right;
    }
 
    if (smallest != i) {
        MinHeapNode *smallestNode = minHeap->array[smallest];
        MinHeapNode *idxNode =  minHeap->array[i];
 
        minHeap->pos[smallestNode->id] = i;
        minHeap->pos[idxNode->id] = smallest;
 
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[i]);
 
        minHeapify(minHeap, smallest);
    }
}
 
int isEmpty(MinHeap* minHeap) {
    return minHeap->size == 0;
}
 
MinHeapNode* extractMin(MinHeap* minHeap) {
    if (isEmpty(minHeap)) { return NULL; }
 
    MinHeapNode* root = minHeap->array[0];
 
    MinHeapNode* lastNode = minHeap->array[minHeap->size - 1];
    minHeap->array[0] = lastNode;
 
    minHeap->pos[root->id] = minHeap->size - 1;
    minHeap->pos[lastNode->id] = 0;
 
    --minHeap->size;
    minHeapify(minHeap, 0);
 
    return root;
}
 
void decreaseKey(MinHeap* minHeap, int id, int weight) {
    int i = minHeap->pos[id];
 
    minHeap->array[i]->weight = weight;
 
    while (i && minHeap->array[i]->weight < minHeap->array[(i - 1) / 2]->weight) {
        minHeap->pos[minHeap->array[i]->id] = (i-1)/2;
        minHeap->pos[minHeap->array[(i-1)/2]->id] = i;
        swapMinHeapNode(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);
 
        i = (i - 1) / 2;
    }
}

bool isInMinHeap(MinHeap *minHeap, int id) {
    if (minHeap->pos[id] < minHeap->size) {
        return true;
    }
    return false;
}


