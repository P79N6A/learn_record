#
#
#
#
target: test

.PYTHON :clean

test: test_xx.cpp
	@echo  build $@
	g++ $^ -o $@  -lgflags_nothreads #-lgflags -lpthread

clean:
	rm test -f
