#pragma once

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

		void SetType(FigureType Type);
		FigureType GetType();

		void SetCoordinates(Point* points);
		Point GetCoordinate(int index);
		
		float GetPerimeter();
		float GetSquare();
		void SetMinFramingRectangle(Figure figure);
	};

	class FigureArray {
	private:
		const static int capacity = 5;
		Figure figures[capacity];
		int count = 0;
	public:

		Figure operator[](const int index) const;
		int GetCount();

		void InsertFigureOnIndex(Figure figure, int index);
		Figure GetFigureOnIndex(int index);
		
		int AddFigure(Figure figure);
		void DeleteFigureOnIndex(int index);
		Figure GetMinSquareFigure();
	};
	
}
