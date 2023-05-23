#include"Matrix.hpp"

#include<iostream>		// std::cout, std::cin
#include<fstream>		// std::fstream, 
#include<algorithm>		// std::copy

template class Matrix<int>;
template class Matrix<double>;

template<typename VecType>
Matrix<VecType>::Matrix(const char* file, int r, int c) :
	rows(r), cols(c),
	data(r, std::vector<VecType>(c, 0))
{
	std::fstream inFile(file);
	if (!inFile) {
		std::cerr << "Failed to read the input file" << std::endl;
		return;
	}

	std::vector<VecType> file_vec = { std::istream_iterator<VecType>(inFile), std::istream_iterator<VecType>() };
	typename std::vector<VecType>::iterator file_iter = file_vec.begin();
	
	typename std::vector< std::vector<VecType> >::iterator row;
	typename std::vector<VecType>::iterator col;

	for (row = data.begin(); row != data.end(); row++) {
		for (col = row->begin(); col != row->end(); col++) {
			if (file_iter == file_vec.end()) {
				std::cerr << "File doesn't have enough elements\n";
				return;
			}
			*col = *file_iter;

			file_iter++;
		}
	}
}


template<typename VecType>
Matrix<VecType>::Matrix() {
	std::cin >> this->rows >> this->cols;

	std::vector<std::vector<VecType>> temp_vec(this->rows, std::vector<VecType>(this->cols, 0));

	for (auto rw = temp_vec.begin(); rw < temp_vec.end(); rw++) {
		for (auto cl = rw->begin(); cl < rw->end(); cl++) {
			VecType temp;
			std::cin >> temp;
			
			*cl = temp;
		}
	}

	this->data = temp_vec;
}

template<typename VecType>
Matrix<VecType>::Matrix(Matrix const& obj)
{
	this->rows = obj.GetRowSize();
	this->cols = obj.GetColSize();
	this->data = obj.GetData();
}

template<typename VecType>
Matrix<VecType> Matrix<VecType>::operator+(Matrix<VecType> const& obj) {
	Matrix<VecType> rval(*this);

	if ((this->rows != obj.GetRowSize()) || (this->cols != obj.GetColSize())) {
		std::cerr << "Sum error! Unequal size of matrices.\n";
		return rval;
	}

	auto temp_vector = obj.GetData();
	for (unsigned int i = 0; i < this->rows; i++) {
		for (unsigned int j = 0; j < this->cols; j++) {
			rval.data[i][j] += temp_vector[i][j];
		}
	}

	return rval;
}

template<typename VecType>
Matrix<VecType>& Matrix<VecType>::operator+=(Matrix<VecType> const& obj)
{
	if ((this->rows != obj.GetRowSize()) || (this->cols != obj.GetColSize())) {
		std::cerr << "Sum error! Unequal size of matrices.\n";
		return *this;
	}

	auto temp_vector = obj.GetData();
	for (unsigned int i = 0; i < this->rows; i++) {
		for (unsigned int j = 0; j < this->cols; j++) {
			this->data[i][j] += temp_vector[i][j];
		}
	}

	return *this;
}

template<typename VecType>
Matrix<VecType> Matrix<VecType>::operator-(Matrix<VecType> const& obj)
{
	Matrix<VecType> rval(*this);

	if ((this->rows != obj.GetRowSize()) || (this->cols != obj.GetColSize())) {
		std::cerr << "Subtraction error! Unequal size of matrices.\n";
		return rval;
	}

	auto temp_vector = obj.GetData();
	for (unsigned int i = 0; i < this->rows; i++) {
		for (unsigned int j = 0; j < this->cols; j++) {
			rval.data[i][j] -= temp_vector[i][j];
		}
	}

	return rval;
}

template<typename VecType>
Matrix<VecType>& Matrix<VecType>::operator-=(Matrix<VecType> const& obj)
{
	if ((this->rows != obj.GetRowSize()) || (this->cols != obj.GetColSize())) {
		std::cerr << "Sum error! Unequal size of matrices.\n";
		return *this;
	}

	auto temp_vector = obj.GetData();
	for (unsigned int i = 0; i < this->rows; i++) {
		for (unsigned int j = 0; j < this->cols; j++) {
			this->data[i][j] -= temp_vector[i][j];
		}
	}

	return *this;
}

template<typename VecType>
Matrix<VecType> Matrix<VecType>::operator*(Matrix<VecType> const& obj)
{
	Matrix<VecType> rval(*this);

	if (this->cols != obj.GetRowSize()) {
		std::cerr << "Multiplication error! Unequal cols A and rows B.\n";
		return rval;
	}

	rval.data = std::vector<std::vector<VecType>>(this->rows, std::vector<VecType>(obj.GetColSize()));

	auto temp_vector = obj.GetData();
	for (unsigned int i = 0; i < this->rows; i++) {
		for (unsigned int j = 0; j < obj.GetColSize(); j++) {

			for (unsigned int index = 0; index < this->cols; index++) {
				rval.data[i][j] += this->data[i][index] * temp_vector[index][i];
			}

		}
	}

	return rval;
}

template<typename VecType>
Matrix<VecType>& Matrix<VecType>::operator*=(Matrix<VecType> const& obj)
{
	if (this->cols != obj.GetRowSize()) {
		std::cerr << "Multiplication error! Unequal cols A and rows B.\n";
		return *this;
	}

	std::vector<std::vector<VecType>> new_data(this->rows, std::vector<VecType>(obj.GetColSize(), 0));

	auto temp_vector = obj.GetData();
	for (unsigned int i = 0; i < this->rows; i++) {
		for (unsigned int j = 0; j < obj.GetColSize(); j++) {

			for (unsigned int index = 0; index < this->cols; index++) {
				new_data[i][j] += this->data[i][index] * temp_vector[index][i];
			}

		}
	}

	this->data = new_data;

	return *this;
}

template<typename VecType>
bool Matrix<VecType>::Transpose() {
	std::vector<std::vector<VecType>> transp_data(cols, std::vector<VecType>(rows));

	for (unsigned int i = 0; i < cols; i++) {
		for (unsigned int j = 0; j < rows; j++) {
			transp_data[i][j] = data[j][i];
		}
	}

	data = transp_data;

	return 0;
}

template<typename VecType>
void Matrix<VecType>::Show() {
	typename std::vector< std::vector<VecType> >::iterator row;
	typename std::vector<VecType>::iterator col;	

	for (row = data.begin(); row != data.end(); row++) {
		for (col = row->begin(); col != row->end(); col++) {
			std::cout << *col << "\t";
		}
		std::cout << std::endl;
	}
}

template<typename VecType>
unsigned int Matrix<VecType>::GetRowSize() const
{
	return this->rows;
}

template<typename VecType>
unsigned int Matrix<VecType>::GetColSize() const
{
	return this->cols;
}

template<typename VecType>
std::vector<std::vector<VecType>> Matrix<VecType>::GetData() const
{
	return this->data;
}
