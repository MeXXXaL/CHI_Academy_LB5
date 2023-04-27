#include<iostream>
#include"matrix.h"

template class Matrix<long>; // explicit instantiation


struct Test {};

std::ostream& operator<<(std::ostream& out, const Test& test)
{
    return out << "Test";
}

int main()
{
    Matrix<long> m1
    {
        {1, 2, 4},
        {3, 0, -4},
        {2, 1, 11}
    };

    Matrix<long> sum = Matrix<long>{{1, 1, 1}, {1, 1, 1}, {1, 1, 1}} + m1;

    Matrix<long> m2 = sum;

    m2 += m1;

    Matrix<long> m3 = 2 * (m2 - Matrix<long>{{1, 3, 5}, {8, 1, 0}, {8, -2, 7}});

    std::cout << m3;



    Matrix<Test> test(3, 4); // implicit insantiation

    std::cout << "\n" << test;


    Matrix<char> str_m {"Hello", "World"};

    std::cout << "\n" << str_m;

    return 0;
}