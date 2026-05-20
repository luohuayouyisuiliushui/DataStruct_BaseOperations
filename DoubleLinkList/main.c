#include"dl.h"
int main(){ 
		DL L = DL_init();
		DL_insert(L, 1);
		DL_insert(L, 2);
		DL_insert(L, 3);
		DL_insert(L, 4);
		DL_insert(L, 5);
		DL_printf(L);
		DL_delete(L, 2);
		DL_printf(L);
		DL_reverse(L);
		DL_printf(L);
		DL_destroy(L);
		system("pause"); 
		return 0;
	}
