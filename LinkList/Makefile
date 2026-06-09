.DEFAULT_GOAL = DS_LL 
sources = LinkList.o test.o
target = DS_LL
%.o : %.c
	gcc -c $<  
DS_LL : $(sources)
	gcc $(sources) -o $@
.PHONY: clean
clean:
	- rm  $(target)
	- rm -rf $(sources)