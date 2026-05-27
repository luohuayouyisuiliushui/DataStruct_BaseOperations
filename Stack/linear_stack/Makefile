.DEFAULT_GOAL = DS_LS
%.o : %.c
	gcc -c $< -o $@
sources = linear_stack.o test.o
DS_LS : $(sources)
	gcc -o $@ $(sources)
.PHONY : clean
clean:
	- rm -rf ./DS_LS
	- rm -rf $(sources)

