.DEFAULT_GOAL = res
%.o : %.c
	gcc -c $^ -o $@
	echo "很没毛"
	@echo "有点没毛"
res : test.o dll.o 
	gcc -o res test.o dll.o
.PHONY : clean
clean:
	-@rm -f res
	-@rm -f test.o dll.o
