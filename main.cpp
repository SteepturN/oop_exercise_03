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
		bool exit = false;
		do{
			read_return_t answer = get_command(valid_commands, command);
			switch(answer) {
				case END_OF_FILE: return 0;
				case END_OF_LINE: continue;
				case VALID_INPUT: exit = true; break;
				case INVALID_INPUT:
					do ch=getchar(); while((ch != EOF) && (ch != '\n'));
					std::cout << "wrong input" << std::endl;
					if(ch == EOF) return 0;
					else break;
			}
		} while(!exit);
		if(static_cast<std::string>(command) == "exit") return 0;
		if(static_cast<std::string>(command) == "p") {
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
			int num_of_verteces(0);
			std::pair<double, double> vertex;
			if(static_cast<std::string>(type_of_figure) == "t") {
				num_of_verteces = 3; //можно лучше сделать - объявить константами
				figures.push_back(new Triangle);
			} else if(static_cast<std::string>(type_of_figure) == "s") {
				num_of_verteces = 4;
				figures.push_back(new Square);
			} else if(static_cast<std::string>(type_of_figure) == "o") {
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
		} else if(static_cast<std::string>(command) == "ars") {
			long area(0);
			for(long unsigned int i = 0; i< figures.size(); i++) area+=figures[i]->area();
			std::cout << "the whole area is " << area;
		} else {
			unsigned int input_figure_number(0);
			if((get_value<unsigned int>(input_figure_number) != VALID_INPUT) || (input_figure_number >= figures.size())) {
				do ch=getchar(); while((ch != EOF) && (ch != '\n'));
				std::cout << "wrong input" << std::endl;
				if(ch == EOF) return 0;
				else continue;
			} else if(static_cast<std::string>(command) == "cen") {
				auto center = figures[input_figure_number]->center();
				std::cout << "x = " << center.first << ", y = " << center.second;
			} else if(static_cast<std::string>(command) == "coor") {
				figures[input_figure_number]->coordinates();
			} else if(static_cast<std::string>(command) == "area") {
				std::cout << "area = " << figures[input_figure_number]->area();
			} else if(static_cast<std::string>(command) == "d") {
				figures.erase(figures.begin()+input_figure_number);
			}
		}
		do ch = getchar(); while((ch != '\n') && (ch != EOF));
		if((static_cast<std::string>(command) != "d") &&(static_cast<std::string>(command) != "p")) std::cout << std::endl;
		if(ch == EOF) return 0;
	} while(true);
	return 0;
}

