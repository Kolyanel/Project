#ifndef SUP_FUNC_H
#define SUP_FUNC_H

// ввод динамически расширяемой строки
char *input_str(void);

// заполнение всех полей каталога
struct Prod *create_catalog(struct Prod *arr);

// сортировка каталого пузырьком по имени по алфавиту
void sorted (struct Prod *arr, size_t len);

// освобождение памяти и очистка каталога
void clear_cat(struct Prod *arr, size_t len);

//поиск товара в каталоге и вывод его данных
void search_pos (struct Prod *arr, size_t len);

// печать всего каталога
void print_cat(struct Prod *arr);

//  удаляем одну строку и подгоняем размер
void remove_pos(struct Prod **arr, int num);

// подгоняем автомаьически размер массива
struct Prod *resize(struct Prod *arr, int fact, int *init, int step);

// редактирование каталога
void update_pos(struct Prod **arr);

#endif //SUP_FUNC_H