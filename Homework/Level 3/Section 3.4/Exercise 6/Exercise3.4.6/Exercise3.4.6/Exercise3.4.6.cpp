#include "BuiltIn.h"
#include "VectorFunction.h"
#include "MatrixFunction.h"


int main() {
	//test built-in type and lightweight functions
	std::cout << "Built-in type with lightweight functions:\n";
	double doublea = 1.1;
	double result;
	//check single thread implementation
	std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
	result=singleThreadBuiltIn<double>(doublea);
	std::chrono::system_clock::time_point end = std::chrono::system_clock::now();
	std::chrono::duration<double> Duration = end - start;
	std::cout << "For single thread:it takes " << Duration.count() << " seconds to get " << result << std::endl;
	//check async and future implementation
	start = std::chrono::system_clock::now();
	result = asyncfutureBuiltIn<double>(doublea);
	end = std::chrono::system_clock::now();
	Duration = end - start;
	std::cout << "For async and future implementation: it takes " << Duration.count() << " seconds to get " << result << std::endl;
	//check promise implementation
	start = std::chrono::system_clock::now();
	result = promiseBuiltIn<double>(doublea);
	end = std::chrono::system_clock::now();
	Duration = end - start;
	std::cout << "For promise implementation: it takes " << Duration.count() << " seconds to get " << result << std::endl;
	//check packaged tast implementation
	start = std::chrono::system_clock::now();
	result = packagedtaskBuiltIn<double>(doublea);
	end = std::chrono::system_clock::now();
	std::cout << "For packaged task implementation: it takes " << Duration.count() << " seconds to get " << result << std::endl;
	
	//test vector and associated functions
	std::cout << "\nVector with associated functions:\n";
	std::vector<double> avector;
	double val = 1.01;
	for (int i = 0; i < 700; ++i)
		avector.push_back(val);
	std::vector<double> vectorResult;
	//check single thread implementation
	start = std::chrono::system_clock::now();
	vectorResult =singleThreadVector<double>(avector);
	end = std::chrono::system_clock::now();
	Duration = end - start;
	std::cout << "For single thread:it takes " << Duration.count() << " seconds to get vector starting with " << vectorResult[0] << std::endl;
	//check async and future implementation
	start = std::chrono::system_clock::now();
	vectorResult = asyncfutureVector<double>(avector);
	end = std::chrono::system_clock::now();
	Duration = end - start;
	std::cout << "For async and future implementation: it takes " << Duration.count() << " seconds to get vector starting with " << vectorResult[0] << std::endl;
	//check promise implementation
	start = std::chrono::system_clock::now();
	vectorResult = promiseVector<double>(avector);
	end = std::chrono::system_clock::now();
	Duration = end - start;
	std::cout << "For promise implementation: it takes " << Duration.count() << " seconds to get vector starting with " << vectorResult[0] << std::endl;
	//check packaged tast implementation
	start = std::chrono::system_clock::now();
	vectorResult = packagedVector<double>(avector);
	end = std::chrono::system_clock::now();
	std::cout << "For packaged task implementation: it takes " << Duration.count() << " seconds to get vector starting with " << vectorResult[0] << std::endl;

	//test matrix and associated functions
	std::cout << "\nMatrix with associated functions:\n";
	int cols = 200;
	int rows = 100;
	double startval = 4.5;
	//give input
	Matrix<double> amatrix(rows,cols,startval);
	Matrix<double> matrixResult;
	//check single thread implementation
	start = std::chrono::system_clock::now();
	matrixResult = SingleThreadMatrix<double>(amatrix);
	end = std::chrono::system_clock::now();
	Duration = end - start;
	std::cout << "For single thread:it takes " << Duration.count() << " seconds to get matrix with val " << matrixResult.GetVal() << std::endl;
	//check async and future implementation
	start = std::chrono::system_clock::now();
	matrixResult = asyncfutureMatrix<double>(amatrix);
	end = std::chrono::system_clock::now();
	Duration = end - start;
	std::cout << "For async and future implementation: it takes " << Duration.count() << " seconds to get matrix with val " << matrixResult.GetVal() << std::endl;
	//check promise implementation
	start = std::chrono::system_clock::now();
	matrixResult = promiseMatrix<double>(amatrix);
	end = std::chrono::system_clock::now();
	Duration = end - start;
	std::cout << "For promise implementation: it takes " << Duration.count() << " seconds to get matrix with val " << matrixResult.GetVal() << std::endl;
	//check packaged tast implementation
	start = std::chrono::system_clock::now();
	matrixResult = packagedtaskMatrix<double>(amatrix);
	end = std::chrono::system_clock::now();
	std::cout << "For packaged task implementation: it takes " << Duration.count() << " seconds to get matrix with val " << matrixResult.GetVal() << std::endl;
	return 0;
}