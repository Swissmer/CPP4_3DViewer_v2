CC           = g++
CPPFLAGS     = -Wall -Wextra -Werror -std=c++17
OS           = $(shell uname)
TARGET       = 3DViewer
MODEL        = ./$(TARGET)/model/*.cc
PATTERN      = ./$(TARGET)/pattern/pattern_command.cc ./$(TARGET)/pattern/pattern_strategy.cc
TESTFILE     = ./$(TARGET)/tests/test_core.cc

ifeq ($(OS), Linux)
	CHECK_FLAGS = -lgtest -lstdc++
	MEM_CHECK = valgrind --tool=memcheck --trace-children=yes --track-origins=yes --leak-check=full
else
	CHECK_FLAGS = -lgtest -lstdc++
	MEM_CHECK = leaks --atExit --
endif

all: clean install

install: uninstall
	qmake -o App/Makefile $(TARGET)/$(TARGET).pro
	cd App && make && make clean && open $(TARGET).app

uninstall:
	rm -rf App

dist: install
	tar -czf 3DViewer.tgz src

dvi:
	open description.txt

test:clean
	$(CC) $(CPPFLAGS) $(TESTFILE) $(MODEL) $(PATTERN) $(CHECK_FLAGS) -lm -pedantic -o test
	./test

gcov_report: clean
	$(CC) $(CPPFLAGS) --coverage $(TESTFILE) $(MODEL) $(PATTERN) $(CHECK_FLAGS) -o gcov_report  -lgtest
	chmod +x *
	./gcov_report
	lcov -t "gcov_report" -o gcov_report.info --no-external --ignore-errors mismatch -c -d .
	genhtml -o report/ gcov_report.info
	open ./report/index.html

change_style:
	find . \( -name '*.h' -o -name '*.cc' \) -print0 | xargs -0 clang-format -i -style=Google

style:
	find . \( -name '*.h' -o -name '*.cc' \) -print0 | xargs -0 clang-format -n -style=Google

leaks: test
	CK_FORK=no $(MEM_CHECK) ./test -pedantic
	make clean

clean:
	rm -rf *.o *.a *.gcda *gcno gcov_report *.info report *.tgz ./3DViewer/tests/test test

rebuild:
	make clean
	make all
