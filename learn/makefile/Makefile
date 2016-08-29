# Makefile learn by lcd
PROG = edit
SRCS = main.c
SRCS += command.c
SRCS += display.c
SRCS += files.c
SRCS += insert.c
SRCS += kbd.c
SRCS += search.c
SRCS += utils.c

# 语法替换
OBJS = $(SRCS:.c=.o)
DEPS = $(SRCS:.c=.d)

# 第一个目标，终极目标
all : $(PROG)

$(PROG) : $(OBJS) 
	$(CC) -o edit $(OBJS)

# 触发下面的 DEPS 依赖
-include $(DEPS)
$(DEPS) : %.d : %.c
	@set -e; rm -f $@;\
		$(CC) -MM $(CPPFLAGS) $< > $@.$$$$;\
		sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@;\
		rm -f $@.$$$$

.PHONY : clean
clean :
	@-rm edit $(OBJS) $(DEPS)
	@echo clean done !

