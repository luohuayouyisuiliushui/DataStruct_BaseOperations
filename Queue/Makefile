.DEFAULT_GOAL = DS_QUEUE
%.o : %.c
	gcc -c $< -o $@
sources = queue_op.o test.o
DS_QUEUE: $(sources)
	gcc $(sources) -o DS_QUEUE
clean:
	@-rm -f *.o DS_QUEUE
.PHONY: clean