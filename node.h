#ifndef SPARSE_MATRIX_NODE_H
#define SPARSE_MATRIX_NODE_H

template <typename T>
class Matrix;

template <typename T>
class Node {
protected:
    T data;
    int posX, posY;
    Node<T> *right, *down;

public:
    explicit Node(int posX, int posY, T data){
        right = down = nullptr;
        this->data = data;
        this->posX = posX;
        this->posY = posY;
    };

    void genocidio() {
        if (right) right->genocidio();
        delete this;
    }

    friend class Matrix<T>;
};

#endif //SPARSE_MATRIX_NODE_H
