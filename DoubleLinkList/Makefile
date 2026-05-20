sources = dl.o main.o
a : $(sources)
	gcc  $(sources) -o a
%.o : %.c
	gcc -c $^ -o $@
.PHONY : clean
clean:
	rm a.exe
	rm -rf $(sources)