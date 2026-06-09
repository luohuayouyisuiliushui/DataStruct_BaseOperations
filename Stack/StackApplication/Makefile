DS_STACK_APP1 : link_stack.o app1.o
	gcc -o $@ $^
%.o : %.c
	gcc -c -o $@ $<
clean :
	rm -f *.o DS_STACK_APP1
.PHONY : clean