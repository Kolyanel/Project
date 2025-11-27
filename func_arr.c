#include <stdio.h>
#include <stdlib.h>

#include "func_arr.h"
#include "sup_func.h"

int quant_prod = INIT_PROD; // начальный размер массива структур
int cnt_prod; // фактических позиций в каталоге
static int pos; // для сохранения найденых позиций в каталоге
struct Prod *catalog; // каталог склада

// выделение динамической памяти для каталога
struct Prod *create_ar_struct(size_t init)
{
	struct Prod *s = (struct Prod*) malloc(init * sizeof(struct Prod));
	if(!s){
		puts("Ошибка выделения памяти!");
		return NULL;
	}
	return s;
}

// вывод меню на экран
void print_menu(void)
{
		puts("Меню программы:");
		puts("'N' - создать новый каталог;\n"
		"'A' - добавить позицию;\n"
		"'S' - найти позицию;\n"
		"'U' - изменить позицию;\n"
		"'R' - удалить позицию;\n"
		"'P' - показать весь каталог;\n"
		"'C' - удалить весь каталог;\n"
		"'Q' - для выхода.");
		printf("Сделайте свой выбор: ");
}

void start_programm(unsigned char ch)
{
	switch(tolower(ch)){
		case 'n':
		puts("Создаем новый каталог");
		clear_cat(catalog, cnt_prod);
		catalog = NULL;
		catalog = create_catalog(catalog);
		if(!catalog){
			puts("Не удалось создать новый каталог!");
			break;
		}
		sorted(catalog, cnt_prod);
		break;
		case 'a':
		catalog = create_catalog(catalog);
		if(!catalog){
			puts("Не удалось добавить строки!");
			break;
		}
		sorted(catalog, cnt_prod);
		break;
		case 's':
		if(!catalog){
			puts("Каталог не существует!");
			break;
		}
		search_pos(catalog, cnt_prod);
		break;
		case 'u':
		if(!catalog){
			puts("Каталог не существует!");
			break;
		}
		puts("Выберите строку для редактирования.");
		printf("Укажите номер строки для редактирования: ");
		while(scanf("%d", &pos) != 1){
			printf("Некорректно введен номер. Попробуйте снова: ");
			CLEAN_BUF();
		}
		update_pos(&catalog);
		sorted(catalog, cnt_prod);
		break;
		case 'r':
		if(!catalog){
			puts("Каталог не существует!");
			break;
		}
		puts("Выберите строку, которую необходимо удалить.");
		search_pos(catalog, cnt_prod);
		printf("Укажите номер удаляемой строки: ");
		while(scanf("%d", &pos) != 1){
			printf("Некорректно введен номер. Попробуйте снова: ");
			CLEAN_BUF();
		}
		printf("Вы уверены, что хотите удадить строку под № «%d»? ('Y'/'N')", pos);
		while(1){
			int ch = getchar();
			if(ch == EOF) break;
			ch = tolower((unsigned char) ch);
			CLEAN_BUF();
			if(ch == 'n') break;
			else if(ch == 'y'){
				remove_pos(&catalog, pos);
				puts("Строка удалена!");
				} else
					printf("Некорректный выбор. Попробуйте снова: ");
		}
		break;
		case 'p':
		if(!catalog){
			puts("Каталог не существует!");
			break;
		}
		print_cat(catalog);
		break;
		case 'c':
		clear_cat(catalog, cnt_prod);
		catalog = NULL;
		break;
		case 'q':
		if(cnt_prod > 0)
			save_cat(catalog);
		break;
		default:
		puts("Некорректный выбор. Попробуйте еще раз.");
	}
}