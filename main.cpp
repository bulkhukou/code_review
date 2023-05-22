#include <iostream>
#include <fstream>
template <typename T>
class Matrix {
private:
    int rows, cols;
    T** data;
public:
    Matrix() : rows(0), cols(0), data(nullptr) {}
    Matrix(int rows_t, int cols_t, T** data2) {
        rows = rows_t;
        cols = cols_t;
        data = new T*[rows];
        for (int i = 0; i < rows; ++i) {
            data[i] = new T[cols];
            for (int j = 0; j < cols; ++j) {
                data[i][j] = data2[i][j];
            }
        }
    }
    Matrix(const Matrix& other)  {
        rows = other.rows;
        cols = other.cols;
        data = new T*[rows];
        for (int i = 0; i < rows; ++i) {
            data[i] = new T[cols];
            for (int j = 0; j < cols; ++j) {
                data[i][j] = other.data[i][j];
            }
        }
    }
    ~Matrix() {
        if (rows > 0){
            for (int i = 0; i < rows; ++i) {
                delete[] data[i];
            }
            delete[] data;
        }
    }

    Matrix& operator=(const Matrix& other) {
        if (&other == this) {
            return *this;
        }
        if (rows > 0){
            for (int i = 0; i < rows; ++i) {
                delete[] data[i];
            }
            delete[] data;
        }
        delete[] data;
        rows = other.rows;
        cols = other.cols;
        data = new T*[rows];
        for (int i = 0; i < rows; ++i) {
            data[i] = new T[cols];
            for (int j = 0; j < cols; ++j) {
                data[i][j] = other.data[i][j];
            }
        }
        return *this;
    }
    T* operator[](int row) {
        return data[row];
    }
    Matrix operator*(const Matrix& other) const {
        if (cols != other.rows) {
            throw std::invalid_argument("Matrices have incompatible dimensions");
        }
        T** temp_ar;
        temp_ar = new T*[rows];
        for (int i = 0; i < rows;++i){
            temp_ar[i] = new T[other.cols];
            for (int j = 0; j < other.cols;++j){
                temp_ar[i][j] = 0;
            }
        }
        Matrix result(rows, other.cols,temp_ar);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < other.cols; ++j) {
                T sum = T();
                for (int k = 0; k < cols; ++k) {
                    sum += data[i][k] * other.data[k][j];
                }
                result[i][j] = sum;
            }
        }
        return result;
        for (int i = 0; i < 2;++i){delete[] temp_ar[i];}
        delete[] temp_ar;
    }
    Matrix operator+(const Matrix& other) const {
        if (cols != other.cols || rows != other.cols) {
            throw std::invalid_argument("Matrices have incompatible dimensions");
        }
        T** temp_ar;
        temp_ar = new T*[rows];
        for (int i = 0; i < rows;++i){
            temp_ar[i] = new T[cols];
            for (int j = 0; j < cols;++j){
                temp_ar[i][j] = 0;
            }
        }
        Matrix result(rows,cols,temp_ar);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j){
                result[i][j] = data[i][j] + other.Getdata()[i][j];
            }
        }
        return result;
        for (int i = 0; i < 2;++i){delete[] temp_ar[i];}
        delete[] temp_ar;
    }
    Matrix operator-(const Matrix& other) const {
        if (cols != other.cols || rows != other.cols) {
            throw std::invalid_argument("Matrices have incompatible dimensions");
        }
        T** temp_ar;
        temp_ar = new T*[rows];
        for (int i = 0; i < rows;++i){
            temp_ar[i] = new T[cols];
            for (int j = 0; j < cols;++j){
                temp_ar[i][j] = 0;
            }
        }
        Matrix result(rows,cols,temp_ar);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j){
                result[i][j] = data[i][j] - other.Getdata()[i][j];
            }
        }
        return result;
        for (int i = 0; i < 2;++i){delete[] temp_ar[i];}
        delete[] temp_ar;
    }
    Matrix operator*(T scalar) const {
        T** temp_ar;
        temp_ar = new T*[rows];
        for (int i = 0; i < rows;++i){
            temp_ar[i] = new T[cols];
            for (int j = 0; j < cols;++j){
                temp_ar[i][j] = 0;
            }
        }
        Matrix result(rows, cols,temp_ar);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                result[i][j] = data[i][j] * scalar;
            }
        }
        return result;
        for (int i = 0; i < 2;++i){delete[] temp_ar[i];}
        delete[] temp_ar;
    }

    friend Matrix operator*(const T& scalar, const Matrix& matrix) {return matrix * scalar;}
    int Getrows() const{
        return rows;
    }
    int Getcols() const{
        return cols;
    }
    T** Getdata() const{return data;}
    void writeToFile(const std::string& filename) const { // метод записи данных в файл
        std::ofstream file(filename);
        if (file.is_open()) {
            file << rows << " " << cols << std::endl;
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < cols; ++j) {
                    file << data[i][j] << " ";
                }
                file << std::endl;
            }
            file.close();
        } else {
            throw std::runtime_error("Failed to open file");
        }
    }
    static Matrix ZeroCr(int rows,int cols){  //созд нулевой матрицы
        int r = rows;
        int c = cols;
        T** temp_ar_l;
        temp_ar_l = new T*[r];
        for (int i = 0; i < r;++i){
            temp_ar_l[i] = new T[c];
            for (int j = 0; j < c;++j){
                temp_ar_l[i][j] = 0;
            }
        }
        Matrix result_l(r, c,temp_ar_l);
        return result_l;
        for (int i = 0; i < 2;++i){delete[] temp_ar_l[i];}
        delete[] temp_ar_l;
    }
    static Matrix UnitCr(int rows,int cols)
    { // создание единичной
        int r = rows;
        int c = cols;
        T** temp_ar_l;
        temp_ar_l = new T*[r];
        for (int i = 0; i < r;++i)
        {
            temp_ar_l[i] = new T[c];
            for (int j = 0; j < c;++j)
            {
                if (i==j) {temp_ar_l[i][j] = 1;}
                else {temp_ar_l[i][j] = 0;}
            }
        }
        Matrix result_l(r, c,temp_ar_l);
        return result_l;
        for (int i = 0; i < 2;++i){delete[] temp_ar_l[i];}
        delete[] temp_ar_l;
    }
    bool operator==(const Matrix& other)
    {
        int c = 0;
        if ((rows != other.rows) || (cols != other.cols) ){c+=1;}
        else
        {
            for (int i = 0; i < rows; ++i )
            {
                for (int j = 0; j < cols;++j)
                {
                    if (data[i][j] != other.data[i][j])
                    {
                        c+=1;
                    }
                }
            }
        }
        if (c==0) {return true;}
        return false;
    }
    void readFromFile(const std::string& filename)
    { //метод чтения данных из файла
        std::ifstream file(filename);
        if (file.is_open())
        {
            int newRows, newCols;
            file >> newRows >> newCols;
            Matrix<T> newMatrix(newRows, newCols);
            file >> newMatrix;
            *this = newMatrix;
            file.close();
        } else
        {
            throw std::runtime_error("Failed to open file");
        }
    }
    friend std::ostream& operator<<(std::ostream &os,const Matrix& matr)
    {
        for (int i = 0; i < matr.Getrows();++i)
        {
            for (int j = 0; j < matr.Getcols();++j)
            {
                os << matr.Getdata()[i][j] << " ";
            }
            os << "\n";
        }
        return os;
    }
};
int main()
{

    int **data2;
    int **data3;

    int k = 23;
    int l = 6;
    data2 = new int*[2];
    for (int i = 0; i < 2; ++i)
    {
        data2[i] = new int[2];
        for (int j = 0; j < 2; ++j)
        {
            data2[i][j] = k;
            k++;
        }
    }

    data3 = new int*[2];
    for (int i = 0; i < 2; ++i)
    {
        data3[i] = new int[2];
        for (int j = 0; j < 2; ++j)
        {
            data3[i][j] = l;
            l++;
        }
    }


    Matrix<int> matritsa1(2,2,data2);
    Matrix<int> matritsa2(2,2,data3);
    std::cout <<"matritsa1 = " << "\n" <<  matritsa1 << std::endl;
    std::cout <<"matritsa2 = " << "\n" <<  matritsa2 << std::endl;
    std::cout <<"matritsa1 == matritsa2 (0 - no, 1 - yes) -> " <<  (matritsa1 == matritsa2) << std::endl;
    std::cout <<"matritsa2 * matritsa1 = " << "\n" <<  matritsa2*matritsa1 << std::endl;
    std::cout <<"matritsa2 + matritsa1 = " << "\n" <<  matritsa2+matritsa1 << std::endl;
    std::cout <<"matritsa2 - matritsa1 = " << "\n" <<  matritsa2-matritsa1 << std::endl;
    std::cout <<"matritsa2 * 5 =  " << "\n" <<  matritsa2*5 << std::endl;
    std::cout <<"Zero 3x3 matrix = \n" <<  Matrix<int>::ZeroCr(3,3) << std::endl;
    std::cout <<"The unit 3x3 matrix = \n" <<  Matrix<int>::UnitCr(3,3) << std::endl;
}