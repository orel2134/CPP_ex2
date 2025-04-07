#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Node & List Data Structures
typedef struct _node {
    char *_data;          // Pointer to the string data
    struct _node *_next;  // Pointer to the next node in the list
} Node;

typedef struct _StrList {
    Node *_head;          // Pointer to the head (first node) of the list
    size_t _size;         // Number of nodes in the list
} StrList;

//------------------------------------------------
// Node implementation
//------------------------------------------------

/**
 * Allocates a new node with the given data and next pointer.
 * 
 * @param data The string data to be stored in the node.
 * @param next Pointer to the next node in the list.
 * @return Pointer to the newly allocated node, or NULL if allocation fails.
 */
Node* Node_alloc(const char* data, Node* next) {
    Node* p = (Node*)malloc(sizeof(Node));
    if (p == NULL) {
        return NULL;  // If malloc fails, return NULL
    }
    p->_data = strdup(data);  // Duplicate the string to store in the node
    if (p->_data == NULL) {
        free(p);
        return NULL;
    }
    p->_next = next;
    return p;
}

/**
 * Frees the memory allocated for a given node.
 * 
 * @param node Pointer to the node to be freed.
 */
void Node_free(Node *node) {
    if (node != NULL) {
        free(node->_data);  // Free the string data
        free(node);         // Free the node itself
    }
}

//------------------------------------------------
// List implementation
//------------------------------------------------

/**
 * Allocates a new empty StrList.
 * 
 * @return Pointer to the newly allocated StrList, or NULL if allocation fails.
 */
StrList *StrList_alloc() {
    // Allocate memory for the list
    StrList *p = (StrList *)malloc(sizeof(StrList));
    if (p == NULL) {
        return NULL;  // If malloc fails, return NULL
    }
    p->_head = NULL;
    p->_size = 0;
    return p;
}

/**
 * Frees the memory allocated for a given StrList, including all its nodes.
 * 
 * @param list Pointer to the StrList to be freed.
 */
void StrList_free(StrList *list) {
    if (list == NULL) return;
    Node *p1 = list->_head;  // Point to the first node
    Node *p2;                // Helper pointer to free the nodes

    // Free all the nodes in the list
    while (p1) {
        p2 = p1;         // Point to the current node
        p1 = p1->_next;  // Point to the next node
        Node_free(p2);   // Free the current node (p2 points to the current node)
    }

    // After freeing all the nodes, free the list
    free(list);
}

/**
 * Returns the number of nodes in the list.
 * 
 * @param list Pointer to the StrList.
 * @return The number of nodes in the list.
 */
size_t StrList_size(const StrList *list) {
    return list->_size;
}

/**
 * Inserts a new node with the given data at the end of the list.
 * 
 * @param list Pointer to the StrList.
 * @param data The string data to be inserted.
 */
void StrList_insertLast(StrList *list, const char *data) {
    // Allocate a new node
    Node* newNode = Node_alloc(data, NULL);
    if (newNode == NULL) {
        return;  // Handle memory allocation failure if needed
    }

    // If the list is empty, set the new node as the head
    if (list->_head == NULL) {
        list->_head = newNode;
    } else {
        // Traverse to the end of the list
        Node* tempNode = list->_head;
        while (tempNode->_next != NULL) {
            tempNode = tempNode->_next;
        }
        // Set the next of the last node to the new node
        tempNode->_next = newNode;
    }
    // Increment the size of the list
    list->_size++;
}

/**
 * Inserts an element at the given index.
 */
void StrList_insertAt(StrList* list, const char* data, int index) {
    if (index < 0 || index > list->_size) {
        printf("Invalid index\n");
        return;
    }

    // Allocate a new node
    Node* newNode = Node_alloc(data, NULL);
    if (newNode == NULL) {
        return;  // Handle memory allocation failure if needed
    }

    // If the index is the size of the list, the new node is inserted at the end
    if (index == list->_size) {
        StrList_insertLast(list, data);
        return;
    }

    // If the index is 0, insert at the head
    if (index == 0) {
        newNode->_next = list->_head;
        list->_head = newNode;
    } else {
        Node* tempNode = list->_head;
        for (int i = 0; i < index - 1; i++) {
            tempNode = tempNode->_next;
        }
        newNode->_next = tempNode->_next;
        tempNode->_next = newNode;
    }

    list->_size++;  // Increment the size of the list
}

/**
 * Returns the data of the first node in the list.
 * 
 * @param list Pointer to the StrList.
 * @return The string data of the first node, or NULL if the list is empty.
 */
char *StrList_firstData(const StrList *list) {
    if (list->_head == NULL) {
        return NULL;  // If the list is empty
    }
    return list->_head->_data;  // If the list is not empty
}

/**
 * Prints all the data in the list.
 * 
 * @param list Pointer to the StrList.
 */
void StrList_print(const StrList* list) {
    if (list->_head == NULL) {
        printf("NULL\n");
        return;
    }

    Node* currentNode = list->_head;

    while (currentNode != NULL) {
        printf("%s ", currentNode->_data);
        currentNode = currentNode->_next;
    }

    printf("\n");
}

/**
 * Prints the data at the given index.
 * 
 * @param list Pointer to the StrList.
 * @param index The index of the node whose data is to be printed.
 */
void StrList_printAt(const StrList* list, int index) {
    if (list->_head == NULL) {
        printf("NULL\n");
        return;
    }
    
    if (index < 0 || index >= list->_size) {
        printf("Invalid index\n");
        return;
    }

    Node* currentNode = list->_head;
    for (int i = 0; i < index; i++) {
        currentNode = currentNode->_next;
    }
    printf("The StrList at index %d is: %s\n", index, currentNode->_data);
}

/**
 * Returns the total number of characters in all the strings in the list.
 * 
 * @param list Pointer to the StrList.
 * @return The total number of characters.
 */
int StrList_printLen(const StrList* list) {
    if (list->_head == NULL) {
        printf("NULL\n");
        return 0;
    }
    
    int ans = 0;
    Node* currentNode = list->_head;
    while (currentNode != NULL) {
        ans += strlen(currentNode->_data);
        currentNode = currentNode->_next;
    }
    
    return ans;
}

/**
 * Returns the number of times a given string appears in the list.
 * 
 * @param list Pointer to the StrList.
 * @param data The string to be counted.
 * @return The number of times the string appears in the list.
 */
int StrList_count(const StrList* list, const char* data) {
    if (list == NULL || list->_head == NULL) {
        return 0;
    }

    int count = 0;
    Node *temp = list->_head;
    while (temp != NULL) {
        if (strcmp(data, temp->_data) == 0) {
            count++;
        }
        temp = temp->_next;
    }
    return count;
}

/**
 * Removes all occurrences of a string from the list.
 * 
 * @param list Pointer to the StrList.
 * @param data The string to be removed.
 */
void StrList_remove(StrList *list, const char *data) {
    if (!list || !list->_head) return;

    // Remove all leading nodes that match the data
    Node *current = list->_head;
    while (current != NULL && strcmp(current->_data, data) == 0) {
        list->_head = current->_next;
        Node_free(current);
        current = list->_head;
        list->_size--;
    }

    // Remove matching nodes in the middle or end of the list
    Node *prev = NULL;
    while (current != NULL) {
        if (strcmp(current->_data, data) == 0) {
            prev->_next = current->_next;
            Node_free(current);
            current = prev->_next;
            list->_size--;
        } else {
            prev = current;
            current = current->_next;
        }
    }
}