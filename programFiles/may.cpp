#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<sstream>
#include<cmath>
double cRound(double number){
	if(fmod(number,10)>=5)return (((int)number/1)+1);
	else return ((int)number/1);
}
//N-число строк M-число столбцов
class matrix{
		int Nsize;
		int Msize;
		std::vector<std::vector<double>> matrixData;
	public:
		//Конструкторы. 1) Создание пустой (нулевой) матрицы NxM 2) Считывание матрицы из файла
		matrix(int N,int M){
			Nsize = N;
			Msize = M;
			std::vector<std::vector<double>> temp(N, std::vector<double> (M,0));
			matrixData = temp;
		}
		matrix(std::string filename){
			std::ifstream file(filename);
			if(file.is_open()){
				std::string input;
				int array[2] = {0,0};
				for(int i=0;i<2;i++){
					if(i==0)std::getline(file,input,' ');
					if(i==1)std::getline(file,input,'\n');
					array[i] = stod(input);
				}
				input.clear();
				
				Nsize = array[0];
				Msize = array[1];
				
				std::string check;
				while(!file.eof()){std::getline(file,check);input=input + check;check.clear();}

				std::stringstream str(input);
				
				std::vector<std::vector<double>> temp(array[0], std::vector<double> (array[1],0));

				
				matrixData = temp;
				
				for(int i=0;i<matrixData.size();i++){
					std::string tempNumber;
					for(int j=0;j<matrixData[i].size();j++){
						
						str >> tempNumber;
						matrixData[i][j] = stod(tempNumber);
						tempNumber.clear();

					}

				}
			}
			file.close();
		}
		//
		
		//Создание нулевой, либо единичной матрицы NxM
		void static makeMatrix(matrix obj,int N,int M,char F){
			obj.Nsize = N;
			obj.Msize = M;
			if (F=='E'){
				std::vector<std::vector<double>> temp(N, std::vector<double> (M,0));
				for(int i = 0;i<temp.size();i++){
					for(int j = 0;j<temp[i].size();j++){
						if(i==j) 	temp[i][j] = 1;
					}
				}
				obj.matrixData = temp;
			}
			if (F=='O'){
				std::vector<std::vector<double>> temp(N, std::vector<double> (M,0));
				obj.matrixData = temp;
			}
		}
		//
		
		//Запись матрицы в файл
		void matrixToFile(std::string filename){
			std::ofstream file(filename);
			if(file.is_open()){
				file << Nsize  <<' '<<Msize<<'\n';
				for(int i=0;i<Nsize;i++){
					for(int j=0;j<Msize;j++){
						file << matrixData[i][j] <<' ';
					}
				}
			}
			file.close();
		} 
		//
		
		//Перегрузка операторов +,-,*(на число и на матрицу)
		matrix operator+(matrix r){
			if((this->Nsize==r.Nsize)&&(this->Msize==r.Msize)){
				matrix temp(this->Nsize,this->Msize);
				for(int i=0;i<Nsize;i++){
					for(int j=0;j<Msize;j++){
						temp.matrixData[i][j]=this->matrixData[i][j]+r.matrixData[i][j];
					}
				}
				return temp;
			}
			else std::cout<<"Error, can't make a sum of matrix";
		}
		matrix operator-(matrix r){
			if((this->Nsize==r.Nsize)&&(this->Msize==r.Msize)){
				matrix temp(this->Nsize,this->Msize);
				for(int i=0;i<Nsize;i++){
					for(int j=0;j<Msize;j++){
						temp.matrixData[i][j]=this->matrixData[i][j]-r.matrixData[i][j];
					}
				}
				return temp;
			}
			else std::cout<<"Error, can't make a sum of matrix";
		}
		/*matrix operator*(matrix r){
			if((this->Msize==r.Nsize)){
				matrix temp(this->Nsize,r.Msize);
				for(int i=0;i<this->Nsize;i++){
					for(int j=0;j<r.Msize;j++){
						int tempSum=0;
						for(int k=0;k<r.Nsize;k++){
							tempSum += (this->matrixData[i][k]*r.matrixData[k][j]);
						}
						temp.matrixData[i][j]=tempSum;
					}
				}
				return temp;
			}
			else std::cout<<"Error, can't make a sum of matrix";
		}*/
		matrix operator*(matrix r){
			if(this->Msize==r.Nsize){
				matrix temp(this->Nsize,r.Msize);
				for(int i=0;i<this->Nsize;i++){
					for(int j=0;j<r.Msize;j++){
						double sum = 0;
						for(int k=0;k<this->Msize;k++){
							sum += (this->matrixData[i][k]*r.matrixData[k][j]);
						}
						temp.matrixData[i][j]=cRound(sum);
					}
				}
				return temp;
			}
			else std::cout<<"Error, can't make a sum of matrix";
		}
		matrix operator*(int number){
			matrix temp(this->Nsize,this->Msize);
			for(int i=0;i<Nsize;i++){
				for(int j=0;j<Msize;j++){
					temp.matrixData[i][j]=this->matrixData[i][j]*number;
				}
			}
			return temp;
		}
		matrix operator*(double number){
			matrix temp(this->Nsize,this->Msize);
			for(int i=0;i<Nsize;i++){
				for(int j=0;j<Msize;j++){
					temp.matrixData[i][j]=this->matrixData[i][j]*number;
				}
			}
			return temp;
		}
		//
		
		//Перегрузка операторов сравнения
		friend bool operator==(matrix const A, matrix const B);
		friend bool operator!=(matrix const A, matrix const B);
		//
		
		//Перегрузка оператора присваивания
		matrix operator=(matrix A){
			for(int i=0;i<A.Nsize;i++){
				for(int j=0;j<A.Msize;j++){
					this->matrixData[i][j] = A.matrixData[i][j];
				}
			}
			return *this;
		}
		//
		
		//Перегрузка оператора логического отрицания(вычисление обратной матрицы)
		matrix operator!(){
			if(this->Nsize==this->Msize){
				matrix A(this->Nsize,this->Msize);
				int determinant = 0;
				determinant = calcAnyDet(*this,determinant);
				if(determinant==0){
					throw "No reverse matrix"; std::cerr << "determinant=0"<<std::endl;
				}
				else {
					A = calcADop(*this);
					double c = (double)1/(double)determinant;
					A = transpose(A)*c;
					return A;
				}
			}
			else {throw "No reverse matrix";std::cerr<<"matrix should be n lines n colums"<<std::endl;}
		}
		//
		//
		
		//Вывод матрицы в консоль
		friend void printMatrix(matrix M);
		//
		
		/*Функции вычисления 1) матрица без i-oй строки,j-ого столбца
							 2) определитель матрицы 2x2
							 3) определитель любой квадратной матрицы
							 4) вычисление матрицы алгебраических дополнений
							 5) транспонирование матрицы
		*/
		friend matrix calcTempMatrix(matrix A,int iX,int jX);
		friend int calcDet2x2(matrix A);
		friend int calcAnyDet(matrix A,int det);
		friend matrix calcADop(matrix A);
		friend matrix transpose(matrix A);
		//
};

bool operator==(matrix const A, matrix const B){
	if((A.Nsize==B.Nsize)&&(A.Msize==B.Msize)){
		for(int i=0;i<A.Nsize;i++){
			for(int j=0;j<A.Msize;j++){
				if(A.matrixData[i][j]!=B.matrixData[i][j]){return false;}
			}
		}
		return true;
	}
	else {std::cout << "Matrix are different" << std::endl;}
}

bool operator!=(matrix const A, matrix const B){
	if((A.Nsize==B.Nsize)&&(A.Msize==B.Msize)){
		for(int i=0;i<A.Nsize;i++){
			for(int j=0;j<A.Msize;j++){
				if(A.matrixData[i][j]!=B.matrixData[i][j]){return true;}
			}
		}
		return false;
	}
	else std::cout << "Matrix are different" << std::endl;
}

void printMatrix(matrix M){
	std::vector<std::vector<double>> data = M.matrixData;
	for(auto i:data){
		std::cout << "| ";
		for(auto j:i){
			std::cout <<j<<' ';
		}
		std::cout << '|'<<std::endl;
	}
}

matrix calcTempMatrix(matrix A,int iX,int jX){
	matrix tempMatrix(A.Nsize-1,A.Msize-1);
	int jOffset=0;int iOffset=0;
	for(int i=0;i<A.Nsize;i++){
		jOffset=0;
		if(i==iX){if(iOffset==0)iOffset++;continue;}
		for(int j=0;j<A.Msize;j++){
			if(j==jX){jOffset++;continue;}
			tempMatrix.matrixData[i-iOffset][j-jOffset]=A.matrixData[i][j];
		}
	}
	return tempMatrix;
}

int calcDet2x2(matrix A){
	int determinant = A.matrixData[0][0]*A.matrixData[1][1]-(A.matrixData[0][1]*A.matrixData[1][0]);
	return determinant;
}

int calcAnyDet(matrix A,int det){
	if(A.Nsize==A.Msize){
		bool check=false;int tempDet=0;
		if(A.Msize==2){tempDet=calcDet2x2(A);det+=tempDet;check=true;}
		for(int j=0;j<A.Msize;j++){
			if (check){return tempDet;}
			else  det+=(pow(-1,j)*A.matrixData[0][j]*calcAnyDet(calcTempMatrix(A,0,j),det));
		}
		
		return det;
	}
	else  {throw "No determinant for this matrix";std::cerr << "Can't calculate the determinant" << std::endl;}
}
matrix transpose(matrix A){
	matrix B(A.Nsize,A.Msize);
	for(int i=0;i<A.Nsize;i++){
		for(int j=0;j<A.Msize;j++){
			if(i==j){B.matrixData[i][j]=A.matrixData[i][j];continue;}
			else{double temp = A.matrixData[i][j];B.matrixData[i][j]=A.matrixData[j][i];B.matrixData[j][i]=temp;}
		}
	}
	return B;
}
matrix calcADop(matrix A){
	matrix B(A.Nsize,A.Msize);
	for(int i=0;i<A.Nsize;i++){
		for(int j=0;j<A.Msize;j++){
			int det =0;
			B.matrixData[i][j]=pow(-1,i+j)*calcAnyDet(calcTempMatrix(A,i,j),det);
		}
	
	}
	return B;
}

int main(){
	std::string filename = "test.txt";
	matrix A(filename);
	printMatrix(A*!A);
	std::cout << round(-0.3);
	return 0;
}