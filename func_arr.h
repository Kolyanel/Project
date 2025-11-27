#ifndef FUNC_ARR_H
#define FUNC_ARR_H

#include <stddef.h>

#define INIT_PROD 1024
#define NAME_LEN 64
#define STEP 32

#define CLEAN_BUF()\
do{\
	int c;\
	while((c = getchar()) != '\n' && c != EOF)\
	    continue;\
} while(0)

struct Prod{
	int n_pp; // номер по порядку
	int code_prod; // код продукта
	char *name_prod;
	double quant;
	double price;
	double mode_price;
	double all_price;
};

struct Prod *create_ar_struct(size_t init);

void print_menu(void);

void start_programm(unsigned char ch);

#endif //FUNC_ARR_H