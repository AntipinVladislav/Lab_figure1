#pragma once
#include <iostream>

namespace vlad {
	enum FigureType {
		circle,
		triangle,
		rectangle
	};


	struct Point {
		float x;
		float y;
		float LenOfPoints(Point point);
	};



	class Figure {
	private:
		FigureType type;
		Point coordinates[4];

	public:
		Figure();
		Figure(FigureType type, Point* coordinates);

		bool operator== (const Figure figure) const;


		FigureType GetType();


		float* GetCoordinate(int index);

		float GetPerimeter();
		float GetSquare();
		bool CheckFigure();
		void SetMinFramingRectangle(Figure figure);

		Point MinPoint(Point* coordinates);
		Point MaxPoint(Point* coordinates);

		Figure* Create(FigureType type, Point* points);
		Figure* CreateCircle(float* circle_points);
		Figure* CreateTriangle(float* triangle_points);
		Figure* CreateRectangle(float* rectangle_points);

		void Print();
		friend std::ostream& operator<< (std::ostream& out, Figure& list);
	};

	std::ostream& operator<< (std::ostream& out, Figure& fig) {
		fig.Print();
		return out;
	}



	class FigureArray {
	private:
		Figure** figures;
		int count = 0;

	public:
		~FigureArray();
		FigureArray();
		FigureArray(FigureArray& arr);

		Figure* operator[](const int index) const;
		FigureArray& operator=(FigureArray& arr);

		int GetCount();
		void AddFigure(Figure* figure);
		Figure* GetFigureOnIndex(int index);

		void InsertFigureOnIndex(Figure* figure, int index);
		void DeleteFigureOnIndex(int index);

		Figure GetMinSquareFigure();

		void Swap(FigureArray& rhs)noexcept;
		void Print();
		friend std::ostream& operator<< (std::ostream& out, FigureArray& arr);
	};
	std::ostream& operator<< (std::ostream& out, FigureArray& arr) {
		arr.Print();
		return out;
	}
}

