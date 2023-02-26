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
	float square = 1000000;
	float halfperimeter = this->GetPerimeter() / 2;
	switch (this->type) {
	case circle:
		square = 3.14 * pow(this->coordinates[0].LenOfPoints(this->coordinates[1]), 2);
		return square;
	case triangle:
		square = 1;
		for (int i = 0; i < 3; i++) {
			square *= halfperimeter - this->coordinates[i].LenOfPoints(this->coordinates[(i + 1) % 3]);
		}
		square = sqrt(square * halfperimeter);
		return square;
	case rectangle:
		square = (this->coordinates[0].LenOfPoints(this->coordinates[1]) * this->coordinates[1].LenOfPoints(this->coordinates[2]));
		return square;
	}
	return square;
}

void Figure::SetMinFramingRectangle(Figure figure) {
	this->type = rectangle;
	float radius = figure.coordinates[0].LenOfPoints(figure.coordinates[1]);
	switch (figure.type) {
	case circle:
		//float radius = figure.coordinates[0].LenOfPoints(figure.coordinates[1]);
		this->coordinates[0] = { figure.coordinates[0].x + radius, figure.coordinates[0].y + radius };
		this->coordinates[1] = { figure.coordinates[0].x + radius, figure.coordinates[0].y - radius };
		this->coordinates[2] = { figure.coordinates[0].x - radius, figure.coordinates[0].y - radius };
		this->coordinates[3] = { figure.coordinates[0].x - radius, figure.coordinates[0].y + radius };
		break;
	case triangle:
		// Треугольник задается отрезком, паралелльным оси х, и точкой, не лежащей на этом отрезке
		if (figure.coordinates[2].x < figure.coordinates[0].x) {
			this->coordinates[0] = { figure.coordinates[2].x, figure.coordinates[0].y};
			this->coordinates[1] = { figure.coordinates[1].x, figure.coordinates[1].y};
			this->coordinates[2] = { figure.coordinates[1].x, figure.coordinates[2].y};
			this->coordinates[3] = { figure.coordinates[2].x, figure.coordinates[2].y};
		}
		else if (figure.coordinates[2].x > figure.coordinates[1].x) {
			this->coordinates[0] = { figure.coordinates[0].x, figure.coordinates[0].y };
			this->coordinates[1] = { figure.coordinates[1].x, figure.coordinates[1].y };
			this->coordinates[2] = { figure.coordinates[2].x, figure.coordinates[2].y };
			this->coordinates[3] = { figure.coordinates[0].x, figure.coordinates[2].y };
		}
		else {
			this->coordinates[0] = { figure.coordinates[0].x, figure.coordinates[0].y };
			this->coordinates[1] = { figure.coordinates[1].x, figure.coordinates[1].y };
			this->coordinates[2] = { figure.coordinates[1].x, figure.coordinates[2].y };
			this->coordinates[3] = { figure.coordinates[0].x, figure.coordinates[2].y };
		}
		break;
	case rectangle:
		for (int i = 0; i < 4; i++)
			this->coordinates[i] = figure.coordinates[i];
		break;
	}
}

Figure FigureArray::operator[](const int index) const {
	if ((index < 0) || (capacity <= index)) {
		throw out_of_range("[FigureArray::operator[]] Index is out of range.");
	}
	return figures[index];
}

int FigureArray::GetCount() {
	return count;
}

void FigureArray::SetFigureOnIndex(Figure figure, int index) {
	if ((index < 0) || (capacity <= index)) {
		throw out_of_range("[FigureArray::operator[]] Index is out of range.");
	}
	Figure empty_figure;
	if (this->figures[index] == empty_figure) {
		this->count++;
	}
	this->figures[index] = figure;
}

Figure FigureArray::GetFigureOnIndex(int index) {
	if ((index < 0) || (capacity <= index)) {
		throw out_of_range("[FigureArray::operator[]] Index is out of range.");
	}
	return this->figures[index];
}



int FigureArray::AddFigure(Figure figure) {
	if (this->GetCount() == capacity) {
		throw out_of_range("Cannot add figure: FigureArray is full");
	}
	else {
		this->figures[this->GetCount()] = figure;
		count++;
	}
}

void FigureArray::DeleteFigureOnIndex(int index) {
	if ((index < 0) || (capacity <= index)) {
		throw out_of_range("[FigureArray::operator[]] Index is out of range.");
	}
	Figure empty_figure;
	this->figures[index] = empty_figure;
	this->count--;
}

Figure FigureArray::GetMinSquareFigure() {
	if (count == 0) {
		throw out_of_range("FigureArray is empty");
	}
	Figure result_figure = this->figures[0];
	for (int i = 1; i < count; i++) {
		if (this->figures[i].GetSquare() < result_figure.GetSquare())
			result_figure = this->figures[i];
	}
	return result_figure;
}