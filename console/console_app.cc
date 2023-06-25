#include <iostream>
#include <functions/figure_functions.h>
#include <cstdlib>

using namespace std;
using namespace vlad;

void CreateCircle(float* circle_points, Point* points) {
	points[0].x = circle_points[0];
	points[0].y = circle_points[3];

	points[1].x = circle_points[2];
	points[1].y = circle_points[1];

	points[2].x = circle_points[0];
	points[2].y = (-1) * circle_points[3];

	points[3].x = (-1) * circle_points[2];
	points[3].y = circle_points[1];

}

void CreateTriangle(float* triangle_points, Point* points) {
	for (int i = 0, j = 0; i < 3; i++) {
		points[i].x = triangle_points[j];
		points[i].y = triangle_points[j + 1];
		j += 2;
	}
}

void CreateRectangle(float* rectangle_points, Point* points) {
	points[0].x = rectangle_points[0];
	points[0].y = rectangle_points[1];

	points[2].x = rectangle_points[2];
	points[2].y = rectangle_points[3];

	points[3].x = points[2].x;
	points[3].y = points[0].y;
	points[1].x = points[0].x;
	points[1].y = points[2].y;
}



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
			Point actual_points[4];
			float points[8];
			char type;
			int index;
			int flag;

			do {

				index = 0;
				flag = 0;
				do {

					cout << "Input index between 0 and " << figure_arr.Size() << "\n";
					cin >> index;

				} while ((index < 0) || (index > figure_arr.Size()));
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
					CreateCircle(points, actual_points);
					Circle circle(actual_points);
					if (!circle.CheckFigure()) {
						cout << "Incorrect figure, try again\n";
						break;
					}
					figure_arr.Insert(make_shared<Circle>(actual_points), index);
					flag = 1;
				} break;

				case 't': {
					cout << "Input triangle point's coordinates >>>\n";
					for (int i = 0; i < 6; i++)
						cin >> points[i];
					CreateTriangle(points, actual_points);
					Triangle triangle(actual_points);
					if (!triangle.CheckFigure()) {
						cout << "Incorrect figure, try again\n";
						break;
					}
					figure_arr.Insert(make_shared<Triangle>(actual_points), index);
					flag = 1;
				} break;

				case 'r': {
					cout << "Input rectangle's upper left and lower right points coordinates >>>\n";
					for (int i = 0; i < 4; i++)
						cin >> points[i];
					CreateRectangle(points, actual_points);
					Rectangle rectangle(actual_points);
					if (!rectangle.CheckFigure()) {
						cout << "Incorrect figure, try again\n";
						break;
					}
					figure_arr.Insert(make_shared<Rectangle>(actual_points), index);
					flag = 1;
				} break;

				}
			} while (flag == 0);
		}

				break;
		case 'd': {
			if (figure_arr.Size() <= 0) {
				system("cls");
				cout << "Empty List" << "\n";
			}
			else {
				int index_2;
				do {
					cout << "Input index beetween 0 and " << figure_arr.Size() - 1 << "\n";
					cin >> index_2;
				} while ((index_2 < 0) || (index_2 >= figure_arr.Size()));
				figure_arr.DeleteFigure(index_2);
			}
		}
				break;
		case 'p': {
			if (figure_arr.Size() <= 0) {
				system("cls");
				cout << "Empty List" << "\n";
			}
			else {

				figure_arr.Print();
			}
		}
				break;
		case 'w': {
			if (figure_arr.Size() <= 0) {
				system("cls");
				cout << "Empty List" << "\n";
			}
			else {

				figure_arr.Print();
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
						cout << "Input index beetween 0 and " << figure_arr.Size() - 1 << "\n";
						cin >> index;
					} while ((index < 0) || (index >= figure_arr.Size()));
					cout << figure_arr[index]->GetPerimeter() << "\n";
				}
						break;

				case 's': {
					int index;
					do {
						cout << "Input index beetween 0 and " << figure_arr.Size() - 1 << "\n";
						cin >> index;
					} while ((index < 0) || (index >= figure_arr.Size()));
					cout << figure_arr[index]->GetSquare() << "\n";
				}
						break;

				case 'f': {
					int index;
					do {
						cout << "Input index beetween 0 and " << figure_arr.Size() - 1 << "\n";
						cin >> index;
					} while ((index < 0) || (index >= figure_arr.Size()));
					Point framing_points[4];
					figure_arr[index]->SetMinFramingRectangle(framing_points);
					Rectangle framing_rectangle(framing_points);
					framing_rectangle.Print();

					cout << "\n";
				}
						break;

				case 'm': {
					figure_arr.MinSquareSearch().Print();


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