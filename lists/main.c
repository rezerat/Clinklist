#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "task_system.h"

void print_test_section(const char* title) {
    printf("\n=================================================\n");
    printf(" ТЕСТ: %s\n", title);
    printf("=================================================\n");
}

int main() {
    LogNode* logs = NULL;
    TaskQueueNode* task_queue = NULL;
    PriorityTreeNode* task_tree = NULL;

    // Создаем набор тестовых задач
    Task t1 = {1, 5, "Задача 1 (Обычная)"};
    Task t2 = {2, 10, "Задача 2 (Критическая)"};
    Task t3 = {3, 2, "Задача 3 (Фоновая)"};
    Task t4 = {4, 7, "Задача 4 (Важная)"};

    print_test_section("1. Односвязный список (Система логов)");
    
    logs = log_add(logs, "Инициализация системы.");
    logs = log_add(logs, "Подключение к базе данных.");
    logs = log_add(logs, "Запуск планировщика.");
    
    log_print_all(logs);


    print_test_section("Двусвязный список");
    
    // 2.1 Наполнение очереди
    task_queue = queue_push(task_queue, t1);
    task_queue = queue_push(task_queue, t2);
    task_queue = queue_push(task_queue, t3);
    task_queue = queue_push(task_queue, t4);
    printf("\n[Исходная очередь из 4 элементов]\n");
    queue_print(task_queue);

    // 2.2 Удаление с конца (Хвост)
    printf("\n[ТЕСТ] Удаление с конца (ID: 4)\n");
    task_queue = queue_remove_by_id(task_queue, 4);
    queue_print(task_queue);

    // 2.3 Удаление с начала (Голова)
    printf("\n[ТЕСТ] Удаление с начала (ID: 1)...\n");
    task_queue = queue_remove_by_id(task_queue, 1);
    queue_print(task_queue);

    // 2.4 Удаление из середины
    printf("\n[ТЕСТ] Удаление из середины (ID: 2)...\n");
    task_queue = queue_remove_by_id(task_queue, 2);
    queue_print(task_queue);

    // 2.5 Попытка удаления несуществующего элемента
    printf("\n[ТЕСТ] Удаление несуществующего элемента\n");
    task_queue = queue_remove_by_id(task_queue, 999);
    printf("[OK] Падения не произошло.\n");


    print_test_section("3. Бинарное дерево поиска");

    task_tree = tree_insert(task_tree, t1);
    task_tree = tree_insert(task_tree, t2);
    task_tree = tree_insert(task_tree, t3);
    task_tree = tree_insert(task_tree, t4);
    printf("[OK] Дерево из 4 задач успешно построено.\n");

    // 3.2 Успешный поиск
    printf("\n[ТЕСТ] Поиск существующей задачи (Приоритет: 10)...\n");
    PriorityTreeNode* found = tree_search(task_tree, 10);
    if (found) {
        printf("[+] Найдено: %s (ID: %d)\n", found->data.description, found->data.id);
    } else {
        printf("[-] Ошибка: задача не найдена.\n");
    }

    printf("\n[ТЕСТ] Поиск несуществующего приоритета (Приоритет: 99)...\n");
    PriorityTreeNode* not_found = tree_search(task_tree, 99);
    if (!not_found) {
        printf("[+] Ожидаемый результат: NULL (задача не найдена).\n");
    } else {
        printf("[-] Ошибка: найдена несуществующая задача!\n");
    }


    print_test_section("4. Очистка памяти (Memory Management)");

    printf("[ТЕСТ] Освобождение памяти структур...\n");
    log_free_all(logs);
    queue_free(task_queue);
    tree_free(task_tree);
    printf("Рекомендуется запуск через Valgrind для подтверждения.\n");

    return 0;
}