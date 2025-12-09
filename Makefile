
CXX = g++

CXXFLAGS = -Wall -Wextra -std=c++11

EXECUTABLE = rpn_calculator

SOURCE = main.cpp

all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCE)
	$(CXX) $(CXXFLAGS) $(SOURCE) -o $(EXECUTABLE)

run: $(EXECUTABLE)
	./$(EXECUTABLE)

test_input:
	@echo "Создание"
	@echo "3 4 +" > input.txt
	@echo "5 2 * 8 +" >> input.txt
	@echo "10 5 /" >> input.txt
	@echo "7 2 -" >> input.txt
	@echo "2 3 4 * +" >> input.txt
	@echo "1 2 + 3 *" >> input.txt
	@echo "Готово!"

show_input:
	@echo "=== Содержимое input.txt ==="
	@if [ -f input.txt ]; then cat input.txt; else echo "Файл input.txt не найден"; fi

show_output:
	@echo "=== Результаты в output.txt ==="
	@if [ -f output.txt ]; then cat output.txt; else echo "Файл output.txt не найден"; fi

quick_test: clean test_input all run show_output

clean:
	rm -f $(EXECUTABLE) output.txt

clean_all: clean
	rm -f input.txt

help:
	@echo "Помощь по Makefile"
	@echo "make              - скомпилировать программу"
	@echo "make run          - запустить программу"
	@echo "make test_input   - создать тестовый input.txt"
	@echo "make show_input   - показать input.txt"
	@echo "make show_output  - показать output.txt"
	@echo "make quick_test   - сделать всё: очистить, создать тест, скомпилировать, запустить"
	@echo "make clean        - удалить исполняемый файл и output.txt"
	@echo "make clean_all    - удалить все созданные файлы"
	@echo "make help         - показать эту справку"

.PHONY: all run test_input show_input show_output quick_test clean clean_all help
