#
CFLAG = -g -Wall
SOURCES = list.c list_test.c
INCLUDES = list.h

OBJECTS = $(SOURCES:.c=.o)
DEPENDS = $(SOURCES:.c=.d)

listTest: $(OBJECTS)
	$(CC) -o $@ $(CFLAG) $^ 

-include $(DEPENDS)

$(DEPENDS): %.d : %.c
	@set -e; rm -f $@;\
		$(CC) -MM $(CPPFLAGS) $< > $@.$$$$;\
		sed 's,\($*\)\.o[ :]*,\1.o $@ : , g' < $@.$$$$ > $@;\
		rm -r $@.$$$$

.PYTHON: run
run: listTest
	./listTest

.PYTHON: clean
clean:
	-rm $(OBJECTS)** $(DEPENDS) listTest

