#include <iostream>
#include <functions/figure_functions.h>
#include <cstdlib>

using namespace std;
using namespace vlad;

int main() {
	char choice;
	FigureArray figure_arr;
	do {
		cout << "Enter your choice >>>\ni - Insert the element by index\n"
			"d - Delete the element by index\np - Print the list\nw - Work with elements\n0 - Exit the program\n";
		cin >> choice;
		system("cls");
		switch (choice) {
		case 'i': {
			
			Figure figure;
			Point cur_points[4];
			float points[8];
			char type;
			int index;
			int flag;

			do {

				index = 0;
				flag = 0;
				do {

					cout << "Input index between 0 and " << figure_arr.GetCount() << "\n";
					cin >> index;

				} while ((index < 0) || (index > figure_arr.GetCount()));
				do {
					type = 'c';
					cout << "Input type >>>\nc - circle\nt - triangle\nr - rectangle\n";
					cin >> type;
				} while ((type != 'c') && (type != 't') && (type != 'r'));

				switch (type) {

				case 'c': {
					cout << "Input coordinates of circle's center and end of radius>>>\n";
					for (int i = 0; i < 4; i++)
						cin >> points[i];
					if (!(*figure.CreateCircle(points)).CheckFigure()) {
						cout << "Incorrect figure, try again\n";
							break;
					}
					const auto ptr = figure.CreateCircle(points);
					figure_arr.InsertFigureOnIndex(ptr, index);
					flag = 1;
				} break;

				case 't': {
					cout << "Input triangle point's coordinates >>>\n";
					for (int i = 0; i < 6; i++)
						cin >> points[i];
					if (!(*figure.CreateTriangle(points)).CheckFigure()) {
						cout << "Incorrect figure, try again\n";
						break;
					}
					const auto ptr = figure.CreateTriangle(points);
					figure_arr.InsertFigureOnIndex(ptr, index);
					flag = 1;
				} break;

				case 'r': {
					cout << "Input rectangle's points coordinates >>>\n";
					for (int i = 0; i < 4; i++)
						cin >> points[i];
					if (!(*figure.CreateRectangle(points)).CheckFigure()) {
						cout << "Incorrect figure, try again\n";
						break;
					}
					const auto ptr = figure.CreateRectangle(points);
					figure_arr.InsertFigureOnIndex(ptr, index);
					flag = 1;
				} break;

				}
			} while (flag == 0);
		}

			break;
		case 'd': {
			if (figure_arr.GetCount() <= 0) {
				system("cls");
				cout << "Empty List" << "\n";
			}
			else {
				int index_2;
				do {
					cout << "Input index beetween 0 and " << figure_arr.GetCount()-1 << "\n";
					cin >> index_2;
				} while ((index_2 < 0) || (index_2 >= figure_arr.GetCount()));
				figure_arr.DeleteFigureOnIndex(index_2);
			}
		}
			break;
		case 'p': {
			if (figure_arr.GetCount() <= 0) {
				system("cls");
				cout << "Empty List" << "\n";
			}
			else {
	
				cout << figure_arr;
			}
		}
			break;
		case 'w': {
			if (figure_arr.GetCount() <= 0) {
				system("cls");
				cout << "Empty List" << "\n";
			}
			else {

				cout << figure_arr;
				cout << "\n";
				char choice_3;
				do {
					choice_3 = 'm';
					cout << "p - Calculate perimeter\ns - Calculate square\nf - Print min framing rectangle"
						"\nm - Search min square figure\n";
					cin >> choice_3;
				} while ((choice_3 != 'p') && (choice_3 != 's') && (choice_3 != 'f') && (choice_3 != 'm'));

				switch (choice_3) {
				case 'p': {
					int index;
					do {
						cout << "Input index beetween 0 and " << figure_arr.GetCount()-1 << "\n";
						cin >> index;
					} while ((index < 0) || (index >= figure_arr.GetCount()));
					cout << figure_arr.GetFigureOnIndex(index)->GetPerimeter() <<"\n";
				}
					  break;

				case 's': {
					int index;
					do {
						cout << "Input index beetween 0 and " << figure_arr.GetCount()-1 << "\n";
						cin >> index;
					} while ((index < 0) || (index >= figure_arr.GetCount()));
					cout << figure_arr.GetFigureOnIndex(index)->GetSquare() << "\n";
				}
					  break;

				case 'f': {
					int index;
					do {
						cout << "Input index beetween 0 and " << figure_arr.GetCount()-1 << "\n";
						cin >> index;
					} while ((index < 0) || (index >= figure_arr.GetCount()));
					Figure framing_rectangle;
					framing_rectangle.SetMinFramingRectangle(*(figure_arr.GetFigureOnIndex(index)));

					cout << framing_rectangle;
					cout << "\n";
				}
					  break;

				case 'm': {

					Figure min_square = figure_arr.GetMinSquareFigure();
					cout << min_square;
					cout << "\n";
				}
					  break;
				}
			}
		}
			  break;
		}
	} while (choice != 0);
}