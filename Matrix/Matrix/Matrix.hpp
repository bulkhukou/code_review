#ifndef MATRIX
#define MATRIX

#include<vector>

template <typename VecType>
class Matrix {
protected:
	unsigned int rows;
	unsigned int cols;
	std::vector<std::vector<VecType>> data;
public:
	Matrix();									//	Matrix ctor with std::cin
	Matrix(Matrix const& obj);					//	Matrix ctor copy
	Matrix(const char* file, int r, int c);		//	Matrix ctor with file

	Matrix operator+(Matrix const& obj);
	Matrix& operator+=(Matrix const& obj);

	Matrix operator-(Matrix const& obj);
	Matrix& operator-=(Matrix const& obj);

	Matrix operator*(Matrix const& obj);
	Matrix& operator*=(Matrix const& obj);

	bool Transpose();
	void Show();

	unsigned int GetRowSize() const;
	unsigned int GetColSize() const;
	std::vector<std::vector<VecType>> GetData() const;
};

#endif