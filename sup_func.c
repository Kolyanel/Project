#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "func_arr.h"
#include "sup_func.h"

extern struct Prod *catalog;
extern int cnt_prod;
extern int quant_prod;

// создаем динамически расширяемый массив и вводим строку, потом подгоняем размер под строку
char *input_str(void)
{
	size_t init_len = NAME_LEN;
	size_t cnt_name = 0;
	int ch;
	char *str = (char*)malloc(init_len);
	if(!str){
		puts("Ошибка! Неудалось выделить память под наименование!");
		return NULL;
	}
	while((ch = getchar()) != '\n' && ch != EOF){
		if(cnt_name == init_len - 1){
			init_len += STEP;
			char *tmp = (char*) realloc(str, init_len);
			if(!tmp){
				puts("Ошибка! Память под наименование не увеличена!");
				free(str);
				return NULL;
			}
			str = tmp;
		}
		str[cnt_name++] = ch;
	}
	str[cnt_name] = '\0';
	char *tmp = (char*) realloc(str, cnt_name + 1);
	if(!tmp){
		puts("Упс! что то пошло не так!");
		return str;
	}
	str = tmp;
	return str;
}

// заполнение всех полей каталога
struct Prod *create_catalog(struct Prod *arr)
{
	int start = cnt_prod;
	int i = start;
	while(1){
		if(i == quant_prod)
			arr = resize(arr, cnt_prod, &quant_prod, STEP);
			
		arr[i].n_pp = i + 1;
		printf("Введите код товара: ");
		while(scanf("%d", &arr[i].code_prod) != 1){
			printf("Некоректный ввод кода товара. Попробуйте еще раз: ");
			CLEAN_BUF();
		}
		CLEAN_BUF();
		puts("Введите наименование товара:");
		arr[i].name_prod = input_str();
		if(!arr[i].name_prod){
			puts("Не удадось создать строку. Работа программы прервана!");
			break;
		}
		printf("Введите полученое количество товара или его вес: ");
		while(scanf("%lf", &arr[i].quant) != 1){
			printf("Некорректно введены данные. Попробуйте еще раз: ");
			CLEAN_BUF();
		}
		CLEAN_BUF();
		printf("Введите цену товара: ");
		while(scanf("%lf", &arr[i].price) != 1){
			printf("Некорректно введены данные. Попробуйте еще раз: ");
			CLEAN_BUF();
		}
		CLEAN_BUF();
		arr[i].all_price = arr[i].quant * arr[i].price;
		i++;
		
		printf("Добавить следующую строку 'Y' или завершить создание каталога 'N': ");
		int ch;
		while(1){
			ch = tolower((unsigned char) getchar());
			CLEAN_BUF();
			if(ch == 'y' || ch == 'n')
			    break;
			printf("Будьте благоразумны, делайте выбор правильно: ");
		}
		if(ch == 'n')
		    break;
	}
	cnt_prod = i;
	return arr;
}

// сортировка каталога пузырьком по алфавиту наименований
void sorted (struct Prod *arr, size_t len)
{
	if(!arr || len < 2){
		puts("Пока сортировать нечего!");
		return;
	}
	struct Prod tmp;
	for(size_t i = 0; i < len - 1; ++i){
		for(size_t j = i + 1; j < len; ++j){
			if(strcmp(arr[i].name_prod, arr[j].name_prod) > 0){
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
		}
	}
	for(size_t i = 0; i < len; ++i)
		arr[i].n_pp = i + 1;
}

// освобождение памяти и очистка каталога
void clear_cat(struct Prod *arr, size_t len)
{
	if(!arr) return;
	for(size_t i = 0; i < len; ++i)
		free(arr[i].name_prod);
	free(arr);
	quant_prod = INIT_PROD;
	cnt_prod = 0;
}

//поиск товара в каталоге и вывод его данных
void search_pos (struct Prod *arr, size_t len)
{
	if(!arr){
		puts("Каталога нет!");
		return;
	}
	
	while(1){
		printf("Выберите как осуществлять поиск, по коду товара 'C' или по наименованию'N'. Нажмите 'Q' для выхода: ");
		int ch = getchar();
		if(ch == EOF) return;
		ch = tolower((unsigned char) ch);
		CLEAN_BUF();
		if(ch == 'q') return;
		
		else if(ch == 'c'){
			int num;
			printf("Введите код товара: ");
			while(scanf("%d", &num) != 1){
				printf("Не корректный код. Попробуйте еще раз: ");
				CLEAN_BUF();
			}
			CLEAN_BUF();
			
			int found = 0;
			
			for(int i = 0; i < len; ++i){
				if(arr[i].code_prod == num){
					if(!found){
						puts("№      Код     Наименование   Количество   Цена    Цена     Сумма");
						puts("          товара                движения");
					}
					printf("%3d%4d %s %3.2f %8.2f %8.2f %8.2f\n", arr[i].n_pp, arr[i].code_prod, arr[i].name_prod, arr[i].quant, arr[i].price, arr[i].mode_price, arr[i].all_price);
					found = 1;
				}
			}
			if(!found){
				puts("Такой код не найден в каталоге!");
			}
		}
		
		else if(ch == 'n'){
			puts("Введите наименование товара:");
			char *tmp = input_str();
			if(!tmp){
				puts("Не удалось выделить память для поиска!");
				return;
			}
			int found = 0;
			for(int i = 0; i < len; ++i){
				if(strstr(arr[i].name_prod, tmp)){
					if(!found){
						puts("№      Код     Наименование   Количество   Цена    Цена     Сумма");
						puts("          товара                движения");
					}
					printf("%3d%4d %s %3.2f %8.2f %8.2f %8.2f\n", arr[i].n_pp, arr[i].code_prod, arr[i].name_prod, arr[i].quant, arr[i].price, arr[i].mode_price, arr[i].all_price);
					found = 1;
				}
			}
			if(!found)
				puts("Такое наименование не найдено в каталоге!");
				
			free(tmp);
		}
		else
			puts("Не коректный выбор. Пробуйте еще!");
	}
}

// печать всего каталога
void print_cat(struct Prod *arr)
{
	if(!arr || cnt_prod == 0){
		puts("Каталога нет!");
		return;
	}
	puts("№      Код     Наименование   Количество   Цена    Цена     Сумма");
	puts("          товара                движения");
	puts("_______________________________");
	for(int i = 0; i < cnt_prod; ++i){
		printf("%3d%4d %-20s %7.2f %8.2f %8.2f %8.2f\n", arr[i].n_pp, arr[i].code_prod, arr[i].name_prod, arr[i].quant, arr[i].price, arr[i].mode_price, arr[i].all_price);
	}
}

//  удаляем одну строку и подгоняем размер
void remove_pos(struct Prod **arr, int num)
{
	if(!*arr){
		puts("Каталога нет!");
		return;
	}
	if( num > 0 && num <= cnt_prod){
		for(int i = num - 1; i < cnt_prod - 1; ++i){
			(*arr)[i] = (*arr)[i + 1];
			(*arr)[i].n_pp = i + 1;
		}
		cnt_prod--;
	} else printf("В этом каталоге нет строки строки с номером «%d»\n", num);
	*arr = resize(*arr, cnt_prod, &quant_prod, STEP);
}

// подгоняем автоматически размер массива
struct Prod *resize(struct Prod *arr, int fact, int *init, int step)
{
	if(!arr || fact == 0){
		puts("Пустой каталог!");
		return NULL;
	}
	if(fact == *init){
		*init += step;
		struct Prod *tmp = (struct Prod*) realloc(arr, *init * sizeof(struct Prod));
		if(!tmp){
			puts("Не удалось увеличить каталог! Он остался прежним.");
			return arr;
		}
		arr = tmp;
	} else if(fact < (*init / 2) && *init > step){
		*init = fact + step;
		struct Prod *tmp = (struct Prod*) realloc(arr, *init * sizeof(struct Prod));
		if(!tmp){
			puts("Не удалось уменьшить каталог! Он остался прежним.");
			return arr;
		}
		arr = tmp;
	}
	return arr;
}

// редактирование каталога
void update_pos(struct Prod **arr)
{
	if(!arr || !*arr){
		puts("Каталог не существует!");
		return;
	}
	if(pos < 1 || pos > cnt_prod){
		puts("Нет такой позиции в каталоге!");
		return;
	}
	int i = pos - 1;
	puts("Вот, что Вы можете изменить:");
	do{
		puts("Код товара, нажмите - 'A'\n"
		     "Наменование, нажмите - 'B'\n"
		     "Количество, нажмите - 'C'\n"
		     "Цену, нажмите - 'D'\n"
		     "Для выхода, нажмите - 'Q'\n");
		printf("Сделайте выбор: ");
		int ch = getchar();
		if(ch == EOF) break;
		ch = tolower((unsigned char) ch);
		CLEAN_BUF();
		switch (ch){
			case 'a':
			printf("Введите новый код товара: ");
			while(scanf("%d", &(*arr)[i].code_prod) != 1){
				printf("Некорректный ввод. Попробуйте еще раз: ");
				CLEAN_BUF();
			}
			CLEAN_BUF();
			break;
			
			case 'b': {
				puts("Введите новое наименование товара:");
				char *tmp = input_str();
				if(!tmp){
					puts("Переименовать не удалось!");
					break;
				}
				if((*arr)[i].name_prod)
					free((*arr)[i].name_prod);
				(*arr)[i].name_prod = tmp;
				break;
			}
			case 'c': {
				double mode_quant = 0;
				printf("Используя '-' без пробела между числом (если убыло), введите количество/вес прибывших/убывших товаров, потом, через пробел, цену по которой происходило движение: ");
				while(scanf("%lf %lf", &mode_quant, &(*arr)[i].mode_price) != 2){
					printf("Некорректный ввод. Попробуйте снова: ");
					CLEAN_BUF();
				}
				CLEAN_BUF();
				(*arr)[i].all_price += (mode_quant * (*arr)[i].mode_price);
				(*arr)[i].quant += mode_quant;
				if((*arr)[i].quant < 0)
					puts("Вы пытаетесь списать больше, чем есть на складе!");
				break;
			}
			case 'd':
			puts("       ВНИМАНИЕ!!!\nИзменение цены в данном разделе приведет к перерасчету общей суммы этой позиции по измененной цене!!!");
			printf("Если передумали и хотите выйти, нажмите 'N' или любую клавишу для продолжения: ");
			ch = tolower((unsigned char) getchar());
			if(ch == 'n') break;
			CLEAN_BUF();
			printf("Введите новую цену товара: ");
			while(scanf("%lf", &(*arr)[i].price) != 1){
				printf("Некорректно введено значение! Попробуйте снова: ");
				CLEAN_BUF();
			}
			CLEAN_BUF();
			(*arr)[i].mode_price = 0;
			(*arr)[i].all_price = (*arr)[i].quant * (*arr)[i].price;
			break;
			case 'q':
			return;
			default:
			printf("Прочитайте внимательно еще раз меню и сделайте правильный выбор: ");
		}
	} while(1);
}