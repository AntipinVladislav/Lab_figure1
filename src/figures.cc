#include <functions/figure_functions.h>

#include <cmath>
#include<stdexcept>
#include<iostream>

using namespace vlad;
using namespace std;


Point Figure::MinPoint(Point* coordinates) {
	float min_x = coordinates[0].x;
	float min_y = coordinates[0].y;
	for (int i = 1; i < 3; i++) {
		if (coordinates[i].x < min_x)
			min_x = coordinates[i].x;
		if (coordinates[i].y < min_y)
			min_y = coordinates[i].y;
	}
	Point result = { min_x, min_y };
	return result;
}

Point Figure::MaxPoint(Point* coordinates) {
	float max_x = coordinates[0].x;
	float max_y = coordinates[0].y;
	for (int i = 1; i < 3; i++) {
		if (coordinates[i].x > max_x)
			max_x = coordinates[i].x;
		if (coordinates[i].x > max_y)
			max_y = coordinates[i].x;
	}
	Point result = { max_x, max_y };
	return result;
}





float Point::LenOfPoints(Point point) {
	return(sqrt(pow(point.x - this->x, 2) + pow(point.y - this->y, 2)));
}


Figure::Figure() {
	this->type = rectangle;
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
	for (int i = 0; i < 3; i++) {
		if ((this->coordinates[i].x != figure.coordinates[i].x) || (this->coordinates[i].y != figure.coordinates[i].y))
			return false;
	}
	return true;
}


FigureType Figure::GetType() {
	return this->type;
}




float* Figure::GetCoordinate(int index) {
	float point[2];
	point[0] = this->coordinates[index].x;
	point[1] = this->coordinates[index].y;
	return point;
}



float Figure::GetPerimeter() {
	float perimeter = 0;
	switch (this->type) {
	case circle:
		perimeter = 2 * 3.14 * this->coordinates[0].LenOfPoints(this->coordinates[1]);
		return perimeter;
	case triangle:
		for (int i = 0; i < 3; i++) {
			perimeter += this->coordinates[i].LenOfPoints(this->coordinates[(i + 1) % 3]);
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
	if (figure.type == rectangle) {
		this->coordinates[0].x = figure.coordinates[0].x;
		this->coordinates[0].y = figure.coordinates[0].y;
		this->coordinates[1].x = figure.coordinates[1].x;
		this->coordinates[1].y = figure.coordinates[1].y;

		this->coordinates[2].x = figure.coordinates[2].x;
		this->coordinates[2].y = figure.coordinates[2].y;

		this->coordinates[3].x = figure.coordinates[2].x;
		this->coordinates[3].y = figure.coordinates[0].y;
	}
	else if(figure.type == triangle) {
		this->coordinates[0] = MaxPoint(figure.coordinates);
		this->coordinates[2] = MinPoint(figure.coordinates);

		this->coordinates[1].x = this->coordinates[0].x;
		this->coordinates[1].y = this->coordinates[2].y;

		this->coordinates[3].x = this->coordinates[2].x;
		this->coordinates[3].y = this->coordinates[0].y;
	}
	else {
		this->coordinates[0] = MaxPoint(figure.coordinates);

		this->coordinates[2].x = (-1) * this->coordinates[0].x;
		this->coordinates[2].y = (-1) * this->coordinates[0].y;

		this->coordinates[1].x = this->coordinates[0].x;
		this->coordinates[1].y = this->coordinates[2].y;
		this->coordinates[3].x = this->coordinates[2].x;
		this->coordinates[3].y = this->coordinates[0].y;
	}
}


Figure* FigureArray::operator[](const int index) const {
	if ((index < 0) || (count <= index)) {
		throw out_of_range("[FigureArray::operator[]] Index is out of range.");
	}
	return figures[index];
}


int FigureArray::GetCount() {
	return count;
}


void FigureArray::InsertFigureOnIndex(Figure* figure, int index) {
	if ((index < 0) || (count < index)) {
		throw out_of_range("[FigureList::operator[]] Index is out of range.");
	}
	auto copy = new Figure * [count + 1];
	for (int i = 0; i < count; i++) {
		if (i < index)
			copy[i] = figures[i];
		else
			copy[i + 1] = figures[i];
	}
	copy[index] = figure;
	delete[] figures;
	figures = copy;
	this->count++;
}


Figure* FigureArray::GetFigureOnIndex(int index) {
	if ((index < 0) || (count <= index)) {
		throw 0;
	}
	return this->figures[index];
}



void FigureArray::AddFigure(Figure* figure) {
	auto copy = new Figure * [count + 1];
	for (int i = 0; i < count; ++i) {
		copy[i] = figures[i];
	}
	copy[count] = figure;
	delete[] figures;
	figures = copy;
	this->count++;
}


void FigureArray::DeleteFigureOnIndex(int index) {
	if ((index < 0) || (index > count)) {
		throw runtime_error("Runtime_error");
	}
	auto copy = new Figure * [count - 1];
	for (int i = 0; i < count - 1; ++i) {
		if (index > i)
			copy[i] = figures[i];
		else
			copy[i] = figures[i + 1];
	}
	delete[] figures;
	figures = copy;
	this->count--;
}


Figure FigureArray::GetMinSquareFigure() {
	if (count == 0) {
		throw 0;
	}
	Figure result_figure(*figures[0]);
	int count = 0;

	for (int i = 1; i < count; i++) {
		if (result_figure.GetSquare() > (*figures[i]).GetSquare()) {
			result_figure = *figures[i];
			count++;
		}
	}
	return result_figure;
}

FigureArray:: ~FigureArray() {
	for (int i = 0; i < count; ++i) {
		delete figures[i];
	}
	delete[] figures;
}

FigureArray::FigureArray() {
	figures = new Figure * [0];
	count = 0;
}


void FigureArray::Print() {
	for (int i = 0; i < count; i++) {
		cout << i << ". ";
		switch (figures[i]->GetType()) {
			
		case 0: {
			cout << "Circle" << " ";
			for (int j = 0; j < 4; j++) {
				cout << figures[i]->GetCoordinate(j)[0] << " " << figures[i]->GetCoordinate(j)[1] << "  ";
			}
		}break;

		case 1: {
			cout << "Triangle" << " ";
			for (int j = 0; j < 3; j++) {
				cout << figures[i]->GetCoordinate(j)[0] << " " << figures[i]->GetCoordinate(j)[1] << "  ";
			}
		}break;
		case 2: {
			cout << "Rectangle" << " ";
			for (int j = 0; j < 4; j++) {
				cout << figures[i]->GetCoordinate(j)[0] << " " << figures[i]->GetCoordinate(j)[1] << "  ";
			}
		}break;
		}

		
		cout << "\n";
	}
}

Figure* Figure::Create(FigureType type, Point* points) {
	return new Figure(type, points);
}


void Figure::Print() {
	switch (type) {
	case 0: cout << "Circle" << " ";
		break;
	case 1: cout << "Triangle" << " ";
		break;
	case 2: cout << "Rectangle" << " ";
		break;
	}
	for (int j = 0; j < 4; ++j) {
		cout << coordinates[j].x << " " << coordinates[j].y << "   ";
	}
	cout << "\n";
}

FigureArray::FigureArray(FigureArray& arr) {
	Figure figure;
	Point points[4];

	for (int i = 0; i < arr.count; i++) {
		for (int j = 0; j < 4; j++) {
			points[j].x = arr.figures[i]->GetCoordinate(i)[0];
			points[j].y = arr.figures[i]->GetCoordinate(i)[1];
		}
		AddFigure(figure.Create(arr.figures[i]->GetType(), points));
	}
}

void FigureArray::Swap(FigureArray& arr)noexcept {
	std::swap(count, arr.count);
	std::swap(figures, arr.figures);
}

FigureArray& FigureArray::operator=(FigureArray& arr) {
	FigureArray copy(arr);
	Swap(copy);
	return *this;


}


bool Figure::CheckFigure() {
	bool flag = false;
	switch (type) {
	case circle: {
		Print();
		if ((coordinates[0].x == coordinates[2].x)
			&& (coordinates[1].y == coordinates[3].y)
			&& (coordinates[0].x < coordinates[1].x)
			&& (coordinates[0].x > coordinates[3].x)
			&& (coordinates[1].y < coordinates[0].y)
			&& (coordinates[1].y > coordinates[2].y))
			flag = true;
	}break;

	case triangle: {
		Print();
		if ((coordinates[0].x == coordinates[1].x) && (coordinates[0].y == coordinates[1].y))
			flag = false;
		if ((coordinates[1].x == coordinates[2].x) && (coordinates[1].y == coordinates[2].y))
			flag = false;
		if ((coordinates[0].x == coordinates[2].x) && (coordinates[0].y == coordinates[2].y))
			flag = false;
		flag = true;
	}break;

	case rectangle: {
		Print();
		for (int i = 1; i < 3; i++)
			if ((coordinates[0].x == coordinates[i].x) && (coordinates[0].y == coordinates[i].y))
				flag = false;

		if ((coordinates[1].x == coordinates[2].x) && (coordinates[1].y == coordinates[2].y))
			flag = false;
		if ((coordinates[1].x == coordinates[3].x) && (coordinates[1].y == coordinates[3].y))
			flag = false;

		if ((coordinates[2].x == coordinates[3].x) && (coordinates[2].y == coordinates[3].y))
			flag = false;

		flag = true;
	}break;
	}
	return flag;
}

Figure* Figure::CreateCircle(float* circle_points) {
	type = circle;
	float radius_x = circle_points[2] - circle_points[0];
	float radius_y = circle_points[3] - circle_points[1];

	coordinates[0].x = circle_points[0];
	coordinates[0].y = circle_points[1] + radius_y;

	coordinates[1].x = circle_points[0] + radius_x;
	coordinates[1].y = circle_points[1];

	coordinates[2].x = circle_points[0];
	coordinates[2].y = circle_points[1] - radius_y;

	coordinates[3].x = circle_points[0] - radius_x;
	coordinates[3].y = circle_points[1];
	return new Figure(type, coordinates);
}
Figure* Figure::CreateTriangle(float* triangle_points) {
	type = triangle;
	int j = 0;
	for (int i = 0; i < 3; ++i) {
		coordinates[i].x = triangle_points[j];
		coordinates[i].y = triangle_points[j+1];
		j += 2;
	}
	return new Figure(type, coordinates);
}
Figure* Figure::CreateRectangle(float* rectangle_points) {
	type = rectangle;
	coordinates[0].x = rectangle_points[0];
	coordinates[0].y = rectangle_points[1];

	coordinates[1].x = rectangle_points[0];
	coordinates[1].y = rectangle_points[3];

	coordinates[2].x = rectangle_points[2];
	coordinates[2].y = rectangle_points[3];

	coordinates[3].x = rectangle_points[2];
	coordinates[3].y = rectangle_points[1];
	return new Figure(type, coordinates);
}
