#include "task_system.h"

// ==========================================
// ОДНОСВЯЗНЫЙ СПИСОК (Логи)
// ==========================================

// 1. Добавление лога
LogNode* log_add(LogNode* head, const char* message) {
    LogNode* new_node = (LogNode*)malloc(sizeof(LogNode));
    if (!new_node) return head;
    strncpy(new_node->message, message, 127);
    new_node->message[127] = '\0';
    new_node->next = head; // Вставляем в начало
    return new_node;
}

// 2. Печать логов
void log_print_all(LogNode* head) {
    printf("=== Системные логи ===\n");
    LogNode* curr = head;
    while (curr) {
        printf("[LOG]: %s\n", curr->message);
        curr = curr->next;
    }
}

// 3. Очистка логов
void log_free_all(LogNode* head) {
    LogNode* curr = head;
    while (curr) {
        LogNode* temp = curr;
        curr = curr->next;
        free(temp);
    }
}

// ==========================================
// ДВУСВЯЗНЫЙ СПИСОК (Очередь задач)
// ==========================================

// 4. Добавление задачи (в конец)
TaskQueueNode* queue_push(TaskQueueNode* head, Task task) {
    TaskQueueNode* new_node = (TaskQueueNode*)malloc(sizeof(TaskQueueNode));
    if (!new_node) return head;
    new_node->data = task;
    new_node->next = NULL;

    if (!head) {
        new_node->prev = NULL;
        return new_node;
    }

    TaskQueueNode* curr = head;
    while (curr->next) {
        curr = curr->next;
    }
    curr->next = new_node;
    new_node->prev = curr;
    return head;
}

// 5. Удаление задачи (удаление из середины)
TaskQueueNode* queue_remove_by_id(TaskQueueNode* head, int task_id) {
    TaskQueueNode* curr = head;
    while (curr) {
        if (curr->data.id == task_id) {
            if (curr->prev) curr->prev->next = curr->next;
            if (curr->next) curr->next->prev = curr->prev;
            
            TaskQueueNode* new_head = head;
            if (curr == head) new_head = curr->next; // Если удаляем голову
            
            free(curr);
            return new_head;
        }
        curr = curr->next;
    }
    return head; // Задача не найдена
}

// 6. Вывод очереди
void queue_print(TaskQueueNode* head) {
    printf("=== Очередь активных задач ===\n");
    TaskQueueNode* curr = head;
    while (curr) {
        printf("ID: %d | Приоритет: %d | Описание: %s\n", 
               curr->data.id, curr->data.priority, curr->data.description);
        curr = curr->next;
    }
}

// 7. Очистка очереди
void queue_free(TaskQueueNode* head) {
    TaskQueueNode* curr = head;
    while (curr) {
        TaskQueueNode* temp = curr;
        curr = curr->next;
        free(temp);
    }
}

// ==========================================
// БИНАРНОЕ ДЕРЕВО (Индекс приоритетов)
// ==========================================

// 8. Вставка по приоритету (классическое BST)
PriorityTreeNode* tree_insert(PriorityTreeNode* root, Task task) {
    if (!root) {
        PriorityTreeNode* new_node = (PriorityTreeNode*)malloc(sizeof(PriorityTreeNode));
        new_node->data = task;
        new_node->left = NULL;
        new_node->right = NULL;
        return new_node;
    }

    if (task.priority < root->data.priority) {
        root->left = tree_insert(root->left, task);
    } else {
        root->right = tree_insert(root->right, task);
    }
    return root;
}

// 9. Поиск по приоритету
PriorityTreeNode* tree_search(PriorityTreeNode* root, int priority) {
    if (!root || root->data.priority == priority) {
        return root;
    }
    if (priority < root->data.priority) {
        return tree_search(root->left, priority);
    }
    return tree_search(root->right, priority);
}

// 10. Очистка дерева (Post-order traversal)
void tree_free(PriorityTreeNode* root) {
    if (root) {
        tree_free(root->left);
        tree_free(root->right);
        free(root);
    }
}