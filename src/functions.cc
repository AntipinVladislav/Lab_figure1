#include <functions/functions.h>

#include <cmath>

using namespace function;

void Figure::set_coordinates(Figure current_figure, float* points) {
	for(int i = 0; i < 6; i++)
	{
		current_figure.coordinates[i] = points[i];
	}
}

void Figure::get_coordinates(Figure current_figure, float* points) {
	for (int i = 0; i < 6; i++)
	{
		points[i] = current_figure.coordinates[i];
	}
}



float Figure::get_perimeter(Figure current_figure) {
	switch (current_figure.current_type)
	{
	case Circle:
		return 2 * 3.14 * current_figure.coordinates[0];
	}

}