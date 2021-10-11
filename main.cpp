/*
Бутырев М8О-206Б-20
16 var: 8-угольник Треугольник Квадрат
Разработать классы согласно варианту задания, классы должны наследоваться от базового класса Figure.

Все классы должны поддерживать набор общих методов:
Вычисление геометрического центра фигуры.
Вывод в стандартный поток вывода std::cout координат вершин фигуры;
Вычисление площади фигуры.

Программа должна иметь следующие возможности:
вводить из стандартного ввода std::cin фигуры, согласно варианту задания.
сохранять созданные фигуры в динамический массив std::vector<Figure*>.
вызывать для всего массива общие функции (1-3 см. выше),
т.е. распечатывать для каждой фигуры в массиве геометрический центр, координаты вершин и площадь.
вычислять общую площадь фигур в массиве.
удалять из массива фигуру по индексу.
*/
#include <iostream>
#include "Square.cpp"
#include "Octagon.cpp"
#include "Figure.cpp"
#include "Triangle.cpp"
#include "Read_input.cpp"
#include <cstdio>
#include <set>
int main(){ // можно вынести названия команд как константы
	char a[] = "You can use\n\
--put (triangle|square|octagon): p [t,s,o] [(point) n times, n(triangle)=3; n(square)=4; n(octagon)=8]\n\
--center (figure number): cen (number of figure)\n\
--coordinates (figure number): coor (number of figure)\n\
--area (figure number): area (number of figure)\n\
--area summ: ars\n\
--delete (figure number): d (number of figure)\n\
--exit\n";
	std::vector<Figure*> figures;
	char ch(' ');
	char command[20];
	std::set<std::string> valid_commands = {"p", "cen", "coor", "area", "ars", "d", "exit"};
	std::set<std::string> valid_figures = {"t", "s", "o"};
	std::cout << a;
	do {
	beginning_of_the_entire_input:
		bool exit_if_successful_input = false;
		do{
			read_return_t answer = get_command(valid_commands, command);
			switch(answer) {
				case END_OF_FILE: return 0;
				case END_OF_LINE: continue;
				case VALID_INPUT: exit_if_successful_input = true; break;
				case INVALID_INPUT:
					do ch=getchar(); while((ch != EOF) && (ch != '\n'));
					std::cout << "wrong input" << std::endl;
					if(ch == EOF) return 0;
					else break;
			}
		} while(!exit_if_successful_input);
		std::string&& command_string = static_cast<std::string>(command);
		if(command_string == "exit") return 0;
		if(command_string == "p") {
			char type_of_figure[10];
			read_return_t answer = get_command(valid_figures, type_of_figure);
			switch(answer) {
				case END_OF_FILE: return 0;
				case END_OF_LINE: continue;
				case VALID_INPUT: break;
				case INVALID_INPUT:
					do ch=getchar(); while((ch != EOF) && (ch != '\n'));
					std::cout << "wrong input" << std::endl;
					if(ch == EOF) return 0;
					else goto beginning_of_the_entire_input;
			}
			std::string&& figure_type_string = static_cast<std::string>(type_of_figure);
			int num_of_verteces(0);
			std::pair<double, double> vertex;
			if(figure_type_string == "t") {
				num_of_verteces = 3; //можно лучше сделать - объявить константами
				figures.push_back(new Triangle);
			} else if(figure_type_string == "s") {
				num_of_verteces = 4;
				figures.push_back(new Square);
			} else if(figure_type_string == "o") {
				num_of_verteces = 8;
				figures.push_back(new Octagon);
			}
			for(int i = 0; i < num_of_verteces; i++) { //add usage of \n?
				if((get_value<double>(vertex.first) != VALID_INPUT) || (get_value<double>(vertex.second) != VALID_INPUT)) {
					do ch=getchar(); while((ch != EOF) && (ch != '\n'));
					std::cout << "wrong input" << std::endl;
					figures.pop_back();
					if(ch == EOF) return 0;
					else goto beginning_of_the_entire_input;
				}
				figures[figures.size()-1]->verteces.push_back(vertex);
			}
			std::cout << "You've added " << figure_type_string << " with this verteces: ";
			figures[figures.size()-1]->coordinates();
		} else if(command_string == "ars") {
			long double area(0);
			for(long unsigned int i = 0; i< figures.size(); i++) area+=figures[i]->area();
			std::cout << "the whole area is " << area;
		} else {
			unsigned int input_figure_number(0);
			if((get_value<unsigned int>(input_figure_number) != VALID_INPUT) || (input_figure_number >= figures.size())) {
				do ch=getchar(); while((ch != EOF) && (ch != '\n'));
				std::cout << "wrong input" << std::endl;
				if(ch == EOF) return 0;
				else continue;
			} else if(command_string == "cen") {
				auto center = figures[input_figure_number]->center();
				std::cout << input_figure_number << " center is: x = " << center.first << ", y = " << center.second;
			} else if(command_string == "coor") {
				std::cout << input_figure_number << " coordinates are ";
				figures[input_figure_number]->coordinates();
			} else if(command_string == "area") {
				std::cout << input_figure_number << " area is " << figures[input_figure_number]->area();
			} else if(command_string == "d") {
				figures.erase(figures.begin()+input_figure_number);
				std::cout << "You've deleted figure #" << input_figure_number;
			}
		}
		do ch = getchar(); while((ch != '\n') && (ch != EOF));
		std::cout << std::endl;
		if(ch == EOF) return 0;
	} while(true);
	return 0;
}

