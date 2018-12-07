#include <iostream>
#include <fstream>
#include "AOSCOO.hpp"
#include "Vector.hpp"
#include "Matrix.hpp"

void zeroize2(Vector &v) {
    for (int i = 0; i < v.numRows(); ++i) {
        v(i) = 0.0;
    }
}

void matvec_denseMat(const Matrix &A, const Vector &x, Vector &y) {
    assert(A.numCols() == x.numRows());
    for (int j = 0; j < A.numRows(); ++j) {
        for (int i = 0; i < A.numCols(); ++i) {
            y(j) += A(j, i) * x(i);
        }
    }
}


int main(int argc, char *argv[]) {
    if (argc < 2 || argc > 4) {
        std::cout << "Usage: " << argv[0] << " matrixFile [ vectorInputFile ] [ vectorOutputFile ] " << std::endl;
        return 0;
    }
    //input matrix
    std::ifstream readMatrixFile(argv[1]);
    std::string matrix_input_text;
    getline(readMatrixFile, matrix_input_text);
    // std::cout << matrix_input_text << std::endl;
    if (matrix_input_text == "AMATH 583 MATRIX DENSE") {

        std::getline(readMatrixFile, matrix_input_text);
        int matInputRows = std::stoi(matrix_input_text);

        std::getline(readMatrixFile, matrix_input_text);
        int matInputCols = std::stoi(matrix_input_text);

        Matrix inputMatrix(matInputRows, matInputCols);

        for (int i = 0; i < matInputRows; ++i) {
            for (int j = 0; j < matInputCols; ++j) {
                readMatrixFile >> inputMatrix(i, j);
            }
        }
        std::getline(readMatrixFile, matrix_input_text); //for new line
        std::getline(readMatrixFile, matrix_input_text);
        // std::cout << matrix_input_text << std::endl;
        if (matrix_input_text != "THIS IS THE END") {
            std::cout << "incorrect input Matrix trailer" << std::endl;
            exit(-2);
        }
        //input vector
        if (argc == 2) {
            std::string vector_input_text;
            std::getline(std::cin, vector_input_text);
            if (vector_input_text != "AMATH 583 VECTOR") {
                std::cout << "incorrect input Vector header" << std::endl;
                exit(-1);
            }

            std::getline(std::cin, vector_input_text);
            int vecInputRows = std::stoi(vector_input_text);

            if (vecInputRows != matInputCols) {
                std::cout << "cannot multiply due to a mismatch in matrix/vector dimensions" << std::endl;
                exit(-1);
            }
            Vector inputVector(vecInputRows);

            for (int i = 0; i < vecInputRows; ++i) {
                std::cin >> inputVector(i);
            }
            std::getline(std::cin, vector_input_text); //for new line
            std::getline(std::cin, vector_input_text);
            if (vector_input_text != "THIS IS THE END") {
                std::cout << "incorrect input Vector trailer" << std::endl;
                exit(-1);
            }

            Vector y(vecInputRows);
            zeroize2(y);
            matvec_denseMat(inputMatrix, inputVector, y);

            std::cout << "AMATH 583 OUTPUT VECTOR" << std::endl;
            for (int i = 0; i < matInputRows; ++i) {
                std::cout << y(i) << std::endl;
            }
            std::cout << "THIS IS THE END" << std::endl;
        }
        if (argc > 2) {
            std::ifstream readVectorFile(argv[2]);
            std::string vector_input_text;
            std::getline(readVectorFile, vector_input_text);

            if (vector_input_text != "AMATH 583 VECTOR") {
                std::cout << "incorrect input Vector header" << std::endl;
                exit(-1);
            }

            std::getline(readVectorFile, vector_input_text);
            int vecInputRows = std::stoi(vector_input_text);

            if (vecInputRows != matInputCols) {
                std::cout << "cannot multiply due to a mismatch in matrix/vector dimensions" << std::endl;
                exit(-1);
            }
            Vector inputVector(vecInputRows);

            for (int i = 0; i < vecInputRows; ++i) {
                readVectorFile >> inputVector(i);
            }
            std::getline(readVectorFile, vector_input_text); //for new line
            std::getline(readVectorFile, vector_input_text);
            if (vector_input_text != "THIS IS THE END") {
                std::cout << "incorrect input Vector trailer" << std::endl;
                exit(-1);
            }

            Vector y(vecInputRows);
            zeroize2(y);
            matvec_denseMat(inputMatrix, inputVector, y);

            if (argc == 3) {
                std::cout << "AMATH 583 OUTPUT VECTOR" << std::endl;
                for (int i = 0; i < matInputRows; ++i) {
                    std::cout << y(i) << std::endl;
                }
                std::cout << "THIS IS THE END" << std::endl;
            }
            if (argc == 4) {
                std::ofstream outputFile(argv[3]);
                outputFile << "AMATH 583 OUTPUT VECTOR" << std::endl;
                for (int i = 0; i < matInputRows; ++i) {
                    outputFile << y(i) << std::endl;
                }
                outputFile << "THIS IS THE END" << std::endl;
            }
        }
    } else if (matrix_input_text == "AMATH 583 MATRIX SPARSE") {
        std::getline(readMatrixFile, matrix_input_text);
        int matInputRows = std::stoi(matrix_input_text);

        std::getline(readMatrixFile, matrix_input_text);
        int matInputCols = std::stoi(matrix_input_text);

        std::getline(readMatrixFile, matrix_input_text);
        int sparseNumNonZeros = std::stoi(matrix_input_text);

        AOSMatrix inputMatrix(matInputRows, matInputCols);
        int iIn;
        int jIn;
        double valIn;
        for (int i = 0; i < sparseNumNonZeros; ++i) {
            std::getline(readMatrixFile, matrix_input_text);
            iIn = std::stoi(matrix_input_text);
            std::getline(readMatrixFile, matrix_input_text);
            jIn = std::stoi(matrix_input_text);
            std::getline(readMatrixFile, matrix_input_text);
            valIn = std::stod(matrix_input_text);
            inputMatrix.push_back(iIn, jIn, valIn);
        }

        std::getline(readMatrixFile, matrix_input_text); //for new line
        std::getline(readMatrixFile, matrix_input_text);
        if (matrix_input_text != "THIS IS THE END") {
            std::cout << "incorrect input Sparse Matrix trailer" << std::endl;
            exit(-1);
        }
        if (argc == 2) {
            std::string vector_input_text;
            std::getline(std::cin, vector_input_text);
            if (vector_input_text != "AMATH 583 VECTOR") {
                std::cout << "incorrect input Vector header" << std::endl;
                exit(-1);
            }
            std::getline(std::cin, vector_input_text);
            int vecInputRows = std::stoi(vector_input_text);

            if (vecInputRows != matInputCols) {
                std::cout << "cannot multiply due to a mismatch in matrix/vector dimensions" << std::endl;
                exit(-1);
            }
            Vector inputVector(vecInputRows);

            for (int i = 0; i < vecInputRows; ++i) {
                std::cin >> inputVector(i);
            }
            std::getline(std::cin, vector_input_text); //for new line
            std::getline(std::cin, vector_input_text);
            if (vector_input_text != "THIS IS THE END") {
                std::cout << "incorrect input Vector trailer" << std::endl;
                exit(-1);
            }

            Vector y(vecInputRows);
            inputMatrix.matvec(inputVector, y);

            std::cout << "AMATH 583 OUTPUT VECTOR" << std::endl;
            for (int i = 0; i < matInputRows; ++i) {
                std::cout << y(i) << std::endl;
            }
            std::cout << "THIS IS THE END" << std::endl;
        }
        if (argc > 2) {
            std::ifstream readVectorFile(argv[2]);
            std::string vector_input_text;
            std::getline(readVectorFile, vector_input_text);

            if (vector_input_text != "AMATH 583 VECTOR") {
                std::cout << "incorrect input Vector header" << std::endl;
                exit(-1);
            }

            std::getline(readVectorFile, vector_input_text);
            int vecInputRows = std::stoi(vector_input_text);

            if (vecInputRows != matInputCols) {
                std::cout << "cannot multiply due to a mismatch in matrix/vector dimensions" << std::endl;
                exit(-1);
            }
            Vector inputVector(vecInputRows);

            for (int i = 0; i < vecInputRows; ++i) {
                readVectorFile >> inputVector(i);
            }
            std::getline(readVectorFile, vector_input_text); //for new line
            std::getline(readVectorFile, vector_input_text);
            if (vector_input_text != "THIS IS THE END") {
                std::cout << "incorrect input Vector trailer" << std::endl;
                exit(-1);
            }

            if (argc == 3) {
                Vector y(vecInputRows);

                inputMatrix.matvec(inputVector, y);

                std::cout << "AMATH 583 OUTPUT VECTOR" << std::endl;
                for (int i = 0; i < matInputRows; ++i) {
                    std::cout << y(i) << std::endl;
                }
                std::cout << "THIS IS THE END" << std::endl;
            }
            if (argc == 4) {
                Vector y(vecInputRows);

                inputMatrix.matvec(inputVector, y);

                std::ofstream outputFile(argv[3]);
                outputFile << "AMATH 583 OUTPUT VECTOR" << std::endl;
                for (int i = 0; i < matInputRows; ++i) {
                    outputFile << y(i) << std::endl;
                }
                outputFile << "THIS IS THE END" << std::endl;
            }
        }
    } else {
        std::cout << "incorrect input Matrix header" << std::endl;
        exit(-1);
    }


    return 0;
}
