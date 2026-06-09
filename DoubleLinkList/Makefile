.DEFAULT_GOAL = DS_DLL
%.o : %.c
	gcc -c $^ -o $@
	echo "很没毛"
	@echo "有点没毛"
DS_DLL : test.o dll.o 
	gcc -o DS_DLL test.o dll.o
.PHONY : clean
clean:
	-@rm -f DS_DLL
	-@rm -f test.o dll.o
