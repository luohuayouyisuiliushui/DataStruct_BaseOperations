.DEFAULT_GOAL := DS_HTL
%.o : %.c
	@gcc -c $^ -o $@
DS_HTL : hash_table_linear.o test.o
	@gcc -o $@ $^ -lm
.PHONY : clean
clean :
	- rm -rf DS_HTL
	- rm -rf *.o
	echo 'SUCCEED!'