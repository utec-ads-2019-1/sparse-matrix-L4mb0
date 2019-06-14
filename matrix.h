#ifndef SPARSE_MATRIX_MATRIX_H
#define SPARSE_MATRIX_MATRIX_H

#include <stdexcept>
#include "node.h"

using namespace std;

template <typename T>
class Matrix {
private:
    Node<T> *root;

public:
    int totRows=0, totColumns=0;

    Matrix(unsigned rows, unsigned columns){
        totRows=rows;
        totColumns=columns;
        root = new Node<T>(-1,-1,-1);
        auto prev = root;
        int index=0;
        while(columns!=index){
            auto newNode = new Node<T>(-1, index, index);
            prev->right=newNode;
            prev=prev->right;
            index++;
        }

        prev = root;
        index=0;
        while(rows!=index){
            auto newNode = new Node<T>(index, -1, index);
            prev->down=newNode;
            prev=prev->down;
            index++;
        }


    };

    /*Matrix(const Matrix<T>& matrix){
        this->totRows = matrix.totRows;
        this->totColumns = matrix.totColumns;
        this()

        for (int i = 0; i < totRows; ++i) {
            for (int j = 0; j < totColumns; ++j) {
                (*this)
            }
        }
    }rows*/

    bool set(unsigned x, unsigned y, T dato){
        //find, check, insert/remove
        auto newNode = new Node<T>(x, y, dato);
        auto iteradorX = root;
        auto iteradorY = root;
        while (iteradorX->posX != x && iteradorX->down){
            iteradorX = iteradorX->down;
        }
        while ( iteradorY->posY != y && iteradorY->right){
            iteradorY = iteradorY->right;
        }

        ///caso1: no hay nada en ninguna de las 2 fila/columna
        if(!iteradorX->right && !iteradorY->down){
            iteradorX->right = newNode;
            iteradorY->down = newNode;
            return true;
        }

        ///caso2: hay algo en la fila/columna
        while(iteradorX->right && iteradorX->right->posY < y){
            iteradorX = iteradorX->right;
        }

        while(iteradorY->down && iteradorY->down->posX < x){
            iteradorY = iteradorY->down;
        }

        ///caso3: hay algo en la posicion que queremos
        if(iteradorX->right &&
            iteradorY->down &&
            iteradorX->right->posX == x &&
            iteradorX->right->posY == y &&
            iteradorY->down->posX == x &&
            iteradorY->down->posY == y)
        {
            auto sacrificio = iteradorX->right;
            if(dato != 0){
                sacrificio->data = dato;
                delete newNode;
                return true;
            }
            else{
                iteradorX->right=sacrificio->right;
                iteradorY->down=sacrificio->down;
                delete sacrificio;
                return true;
            }
        }
        else{
            newNode->down = iteradorY->down;
            newNode->right = iteradorX->right;
            iteradorX->right = iteradorY->down = newNode;
            return true;
        }


    };

    T operator()(unsigned x, unsigned y) const{
        auto iteradorX = root;
        while (iteradorX->down && iteradorX->posX != x){
            iteradorX = iteradorX->down;
        }
        while(iteradorX->right && iteradorX->right->posY < y){
            iteradorX = iteradorX->right;
        }
        if(iteradorX->right && iteradorX->right->posY == y){
            return iteradorX->right->data;
        }
        else {
            return 0;
        }

    };

    Matrix<T> operator*(T scalar) const{
        Matrix<T> result(totRows, totColumns);
        for (unsigned i = 0; i < totRows; ++i) {
            for (unsigned j = 0; j < totColumns; ++j) {
                result.set(i,j, operator()(i,j)*scalar);
            }
        }
        return result;
    };

    Matrix<T> operator*(Matrix<T> other) const{
        if(totColumns != other.totRows) throw out_of_range ("las matrices no coinciden");
        Matrix<T> result(totRows, totColumns);
        for (unsigned i = 0; i < totRows; ++i) {
            for (unsigned j = 0; j < other.totColumns; ++j) {
                for (unsigned k = 0; k < totColumns; ++k) {
                    result.set(i,j, operator()(i,k) * other.operator()(k,j));
                }
            }
        }
        return result;
    };

    const Matrix<T> operator+(Matrix<T> other) const{
        Matrix<T> result(totRows, totColumns);
        for (unsigned i = 0; i < totRows; ++i) {
            for (unsigned j = 0; j < totColumns; ++j) {
                result.set(i,j, operator()(i,j) + other.operator()(i,j));
            }
        }

        return result;
    };

    Matrix<T> operator-(Matrix<T> other) const{
        Matrix<T> result(totRows, totColumns);
        for (unsigned i = 0; i < totRows; ++i) {
            for (unsigned j = 0; j < totColumns; ++j) {
                result.set(i,j, operator()(i,j) - other.operator()(i,j));
            }
        }
        return result;
    };

    Matrix<T> transpose() const{
        Matrix<T> result(totRows, totColumns);
        for (unsigned i = 0; i < totRows; ++i) {
            for (unsigned j = 0; j < totColumns; ++j) {
                result.set(i,j, operator()(j,i));
            }
        }
        return result;
    };

    void print() const{
        for (unsigned i = 0; i < totRows; ++i) {
            for (unsigned j = 0; j < totColumns; ++j) {
                cout<< operator()(i,j)<<"\t";
            }
            cout<<"\n";
        }
        cout<<"\n";

    };


    ~Matrix(){ //genocidio
       /* if (root) {
            auto iterador = root;
            while(iterador) {
                auto sacrificio = iterador;
                iterador = iterador->down;
                sacrificio->genocidio();
            }
        }
        root = nullptr;*/
    };
};

#endif //SPARSE_MATRIX_MATRIX_H