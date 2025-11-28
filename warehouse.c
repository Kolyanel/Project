#include <stdio.h>
#include <ctype.h>
#include "func_arr.h"

extern struct Prod *catalog;

int main(void)
{
	catalog = create_ar_struct(INIT_PROD);
	if(!catalog){
		puts("На вашем устройстве слишком мало памяти для создания каталога и запуска программы. До свидания.");
		return 1;
	}
	puts("          Здравствуйте!");
	puts("Вас приветствует программа учета материальных средств на Вашем складе!");
	puts("\nНу-с, чем займемся?\n");
	
	while(1){
		print_menu();
		int ch = getchar();
		if(ch == EOF) break;
		ch = tolower((unsigned char) ch);
		CLEAN_BUF();
		start_programm(ch);
		if(ch == 'q') break;
	}
	puts("\n       Всего доброго!!!");
	clear_cat(catalog, cnt_prod);
	catalog = NULL;
	return 0;
}