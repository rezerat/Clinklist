#ifndef TASK_SYSTEM_H
#define TASK_SYSTEM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    int priority; // Чем выше число, тем выше приоритет
    char description[100];
} Task;

typedef struct LogNode {
    char message[128];
    struct LogNode* next;
} LogNode;

typedef struct TaskQueueNode {
    Task data;
    struct TaskQueueNode* prev;
    struct TaskQueueNode* next;
} TaskQueueNode;

typedef struct PriorityTreeNode {
    Task data;
    struct PriorityTreeNode* left;
    struct PriorityTreeNode* right;
} PriorityTreeNode;


LogNode* log_add(LogNode* head, const char* message);
void log_print_all(LogNode* head);
void log_free_all(LogNode* head);

TaskQueueNode* queue_push(TaskQueueNode* head, Task task);
TaskQueueNode* queue_remove_by_id(TaskQueueNode* head, int task_id);
void queue_print(TaskQueueNode* head);
void queue_free(TaskQueueNode* head);

PriorityTreeNode* tree_insert(PriorityTreeNode* root, Task task);
PriorityTreeNode* tree_search(PriorityTreeNode* root, int priority);
void tree_free(PriorityTreeNode* root);

#endif