sources = link_stack.o test.o
DS_LINK_STACK : $(sources)
	gcc -o $@ $^
%.o : %.c
	gcc -c $< -o $@
	@echo "链接文件生成完毕"
.PHONY : clean
clean :
	@-rm -rf DS_LINK_STACK
	@-rm -rf $(sources)

