#include <functions/functions.h>

#include <cmath>
#include <stdexcept>
#include <iostream>

using namespace vlad;
using namespace std;


float Point::LenOfPoints(Point point) {
	return(sqrt(pow(point.x - this->x, 2) + pow(point.y - this->y, 2)));
}

Figure::Figure() {
	this->type = circle;
	for (int i = 0; i < 4; i++) {
		this->coordinates[i] = { 0,0 };
	}
}

Figure::Figure(FigureType type, Point* points) {
	this->type = type;
	for (int i = 0; i < 4; i++) {
		this->coordinates[i] = points[i];
	}
}

bool Figure::operator== (Figure figure) const {
	if (this->type != figure.type)
		return false;
	for (int i = 0; i < 4; i++) {
		if ((this->coordinates[i].x != figure.coordinates[i].x) || (this->coordinates[i].y != figure.coordinates[i].y))
			return false;
	}
	return true;
}

void Figure::SetType(FigureType type) {
	this->type = type;
}
FigureType Figure::GetType() {
	return this->type;
}

void Figure::SetCoordinates(Point* points) {
	for (int i = 0; i < 4; i++) {
		this->coordinates[i] = points[i];
	}
}


Point Figure::GetCoordinate(int index) {
	return this->coordinates[index];
}



float Figure::GetPerimeter() {
	float perimeter = 0;
	switch (this->type) {
	case circle:
		perimeter = 2 * 3.14 * this->coordinates[0].LenOfPoints(this->coordinates[1]);
		return perimeter;
	case triangle:
		for (int i = 0; i < 3; i++) {
			perimeter+= this->coordinates[i].LenOfPoints(this->coordinates[(i + 1) % 3]);
		}
		return perimeter;
	case rectangle:
		perimeter = 2 * (this->coordinates[0].LenOfPoints(this->coordinates[1]) + this->coordinates[1].LenOfPoints(this->coordinates[2]));
		return perimeter;
	}
}

float Figure::GetSquare() {
	float square = 1;
	switch (this->type) {
	case circle:
		square = 3.14 * pow(this->coordinates[0].LenOfPoints(this->coordinates[1]), 2);
		return square;
	case triangle:
		float halfperimeter = this->GetPerimeter() / 2;
		for (int i = 0; i < 3; i++) {
			square *= halfperimeter - this->coordinates[i].LenOfPoints(this->coordinates[(i + 1) % 3]);
		}
		square = sqrt(square);
		return square;
	case rectangle:
		square = (this->coordinates[0].LenOfPoints(this->coordinates[1]) * this->coordinates[1].LenOfPoints(this->coordinates[2]));
		return square;
	}
}

void Figure::SetMinFramingRectangle(Figure figure) {
	this->type = rectangle;
	switch (figure.type) {
	case circle:
		float radius = figure.coordinates[0].LenOfPoints(figure.coordinates[1]);
		this->apex[0] = { figure.coordinates[0].x + radius, figure.coordinates[0].y + radius };
		this->apex[1] = { figure.coordinates[0].x + radius, figure.coordinates[0].y - radius };
		this->apex[2] = { figure.coordinates[0].x - radius, figure.coordinates[0].y - radius };
		this->apex[3] = { figure.coordinates[0].x - radius, figure.coordinates[0].y + radius };
		break;
	case triangle:
		// Треугольник задается отрезком, паралелльным оси х, и точкой, не лежащей на этом отрезке
		if (figure.coordinates[2].x < figure.coordinates[0].x) {
			this->apex[0] = { figure.coordinates[2].x, figure.coordinates[0].y};
			this->apex[1] = { figure.coordinates[1].x, figure.coordinates[1].y};
			this->apex[2] = { figure.coordinates[1].x, figure.coordinates[2].y};
			this->apex[3] = { figure.coordinates[2].x, figure.coordinates[2].y};
		}
		else if (figure.coordinates[2].x > figure.coordinates[1].x) {
			this->apex[0] = { figure.coordinates[0].x, figure.coordinates[0].y };
			this->apex[1] = { figure.coordinates[1].x, figure.coordinates[1].y };
			this->apex[2] = { figure.coordinates[2].x, figure.coordinates[2].y };
			this->apex[3] = { figure.coordinates[0].x, figure.coordinates[2].y };
		}
		else {
			this->apex[0] = { figure.coordinates[0].x, figure.coordinates[0].y };
			this->apex[1] = { figure.coordinates[1].x, figure.coordinates[1].y };
			this->apex[2] = { figure.coordinates[1].x, figure.coordinates[2].y };
			this->apex[3] = { figure.coordinates[0].x, figure.coordinates[2].y };
		}
		break;
	case rectangle:
		for (int i = 0; i < 4; i++)
			this->coordinates[i] = figure.coordinates[i];
		break;
	}
}
