#pragma once

#include"base_matrix.h"

#include<iostream>
#include<type_traits>
#include<stdexcept>


template<typename T = int, typename = void>
class Matrix;

// ======================= Matrix for arithmetic types types (SFINAE) =======================

template<typename T>
class Matrix<T, std::enable_if_t<std::is_arithmetic_v<T>>> : public base_matrix<T>
{
private:
    friend void throw_if_not_equal_in_size(const Matrix& lhs, const Matrix& rhs)
    {
        if (!lhs.equal_in_size(rhs))
            throw std::runtime_error("Matrices aren't equal in size");
    }

    using base_matrix<T>::buffer;

public:
    using value_type = typename base_matrix<T>::value_type;
    using size_type = typename base_matrix<T>::size_type;
    using reference = typename base_matrix<T>::reference;
    using const_reference = typename base_matrix<T>::const_reference;

    using base_matrix<T>::base_matrix;
    Matrix() = default;

    friend Matrix operator+(const Matrix& lhs, const Matrix& rhs)
    {
        throw_if_not_equal_in_size(lhs, rhs);

        Matrix result(lhs.rows(), lhs.cols());

        for (size_type i = 0; i < lhs.rows(); ++i)
            for (size_type j = 0; j < lhs.cols(); ++j)
                result(i, j) = lhs(i, j) + rhs(i, j);
        return result;
    }

    friend Matrix operator+(const Matrix& lhs, Matrix&& rhs)
    {
        throw_if_not_equal_in_size(lhs, rhs);

        for (size_type i = 0; i < lhs.rows(); ++i)
            for (size_type j = 0; j < lhs.cols(); ++j)
                rhs(i, j) += lhs(i, j);
        return std::move(rhs);
    }

    friend Matrix operator+(Matrix&& lhs, const Matrix& rhs)
    {
        throw_if_not_equal_in_size(lhs, rhs);

        for (size_type i = 0; i < lhs.rows(); ++i)
            for (size_type j = 0; j < lhs.cols(); ++j)
                lhs(i, j) += rhs(i, j);
        return std::move(lhs);
    }

    friend Matrix operator+(Matrix&& lhs, Matrix&& rhs)
    {
        throw_if_not_equal_in_size(lhs, rhs);

        for (size_type i = 0; i < lhs.rows(); ++i)
            for (size_type j = 0; j < lhs.cols(); ++j)
                lhs(i, j) += std::move(rhs(i, j));
        return std::move(lhs);
    }

    Matrix& operator+=(const Matrix& other)
    {
        throw_if_not_equal_in_size(*this, other);

        for (size_type i = 0; i < other.rows(); ++i)
            for (size_type j = 0; j < other.cols(); ++j)
                this->buffer[i][j] += other(i, j);
        return *this;
    }

    Matrix& operator+=(Matrix&& other)
    {
        throw_if_not_equal_in_size(*this, other);

        for (size_type i = 0; i < other.rows(); ++i)
            for (size_type j = 0; j< other.cols(); ++j)
                this->buffer[i][j] += std::move(other(i, j));
        return *this;
    }


    friend Matrix operator-(const Matrix& lhs, const Matrix& rhs)
    {
        throw_if_not_equal_in_size(lhs, rhs);

        Matrix result(lhs.rows(), lhs.cols());

        for (size_type i = 0; i < lhs.rows(); ++i)
            for (size_type j = 0; j < lhs.cols(); ++j)
                result(i, j) = lhs(i, j) - rhs(i, j);
        return result;
    }

    friend Matrix operator-(const Matrix& lhs, Matrix&& rhs)
    {
        throw_if_not_equal_in_size(lhs, rhs);

        for (size_type i = 0; i < lhs.rows(); ++i)
            for (size_type j = 0; j < lhs.cols(); ++j)
                rhs(i, j) = lhs(i, j) - rhs(i, j);
        return std::move(rhs);
    }

    friend Matrix operator-(Matrix&& lhs, const Matrix& rhs)
    {
        throw_if_not_equal_in_size(lhs, rhs);

        for (size_type i = 0; i < lhs.rows(); ++i)
            for (size_type j = 0; j < lhs.cols(); ++j)
                lhs(i, j) -= rhs(i, j);
        return std::move(lhs);
    }

    friend Matrix operator-(Matrix&& lhs, Matrix&& rhs)
    {
        throw_if_not_equal_in_size(lhs, rhs);

        for (size_type i = 0; i < lhs.rows(); ++i)
            for (size_type j = 0; j < lhs.cols(); ++j)
                lhs(i, j) -= std::move(rhs(i, j));
        return std::move(lhs);
    }

    Matrix& operator-=(const Matrix& other)
    {
        throw_if_not_equal_in_size(*this, other);

        for (size_type i = 0; i < other.rows(); ++i)
            for (size_type j = 0; j < other.cols(); ++j)
                this->buffer[i][j] -= other(i, j);
        return *this;
    }

    Matrix& operator-=(Matrix&& other)
    {
        throw_if_not_equal_in_size(*this, other);

        for (size_type i = 0; i < other.rows(); ++i)
            for (size_type j = 0; j < other.cols(); ++j)
                this->buffer[i][j] -= std::move(other(i, j));
        return *this;
    }


    friend Matrix operator*(const Matrix& matrix, const long number)
    {
        Matrix result(matrix);
        for (size_type i = 0; i < result.rows(); ++i)
            for (size_type j = 0; j < result.cols(); ++j)
                result(i, j) *= number;
        return result;
    }

    friend Matrix operator*(Matrix&& matrix, const long number)
    {
        for (size_type i = 0; i < matrix.rows(); ++i)
            for (size_type j = 0; j < matrix.cols(); ++j)
                matrix(i, j) *= number;
        return std::move(matrix);
    }

    friend Matrix operator*(const long number, const Matrix& matrix)
    {
        return matrix * number;
    }
    
    friend Matrix operator*(const long number, Matrix&& matrix)
    {
        return std::move(matrix) * number;
    }

    Matrix& operator-()
    {
        for (size_type i = 0; i < base_matrix<T>::rows(); ++i)
            for (size_type j = 0; j < base_matrix<T>::cols(); ++j)
                buffer[i][j] *= -1;
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& out, const Matrix& matrix)
    {
        for (size_type i = 0; i < matrix.rows(); ++i)
        {
            for (size_type j = 0; j < matrix.cols() - 1; ++j)
                out << matrix(i, j) << "\t;\t";
            out << matrix(i, matrix.cols() - 1) << "\n";
        }
        return out;
    }

};



// ======================= Matrix for non-arithmetic types types (SFINAE) =======================

template<typename T>
class Matrix<T, std::enable_if_t<!std::is_arithmetic_v<T>>> : public base_matrix<T>
{
public:
    using value_type = typename base_matrix<T>::value_type;
    using size_type = typename base_matrix<T>::size_type;
    using reference = typename base_matrix<T>::reference;
    using const_reference = typename base_matrix<T>::const_reference;

    using base_matrix<T>::base_matrix;
    Matrix() = default;

    friend std::ostream& operator<<(std::ostream& out, const Matrix& matrix)
    {
        for (size_type i = 0; i < matrix.rows(); ++i)
        {
            for (size_type j = 0; j < matrix.cols() - 1; ++j)
                out << matrix(i, j) << "\t|\t";
            out << matrix(i, matrix.cols() - 1) << "\n";
        }
        return out;
    }
};



// ======================= Matrix for chars (using std::string) =======================

template<>
class Matrix<char>
{
public:
    using value_type = std::string::value_type;
    using size_type = std::string::size_type;
    using reference = std::string::reference;
    using const_reference = std::string::const_reference;

    Matrix();
    Matrix(const size_type rows, const size_type cols, const value_type value = value_type{});
    Matrix(const std::initializer_list<const std::string>& il);

    void resize_rows(const size_type rows, const value_type value = value_type{});
    void resize_cols(const size_type cols, const value_type value = value_type{});
    void resize(const size_type rows, const size_type cols, const value_type value = value_type{});

    reference operator()(const size_type row, const size_type col);
    value_type operator()(const size_type row, const size_type col) const;
    reference at(const size_type row, const size_type col);
    value_type at(const size_type row, const size_type col) const;

    size_type rows() const;
    size_type cols() const;
    size_type size() const;

    void sort_rows(const std::function<bool(const_reference, const_reference)>& comp = std::less<value_type>());
    void sort_cols(const std::function<bool(const_reference, const_reference)>& comp = std::less<value_type>());

    bool equal_in_size(const Matrix& other) const;

private:
    std::vector<std::string> buffer;
};

Matrix<char>::Matrix() = default;

Matrix<char>::Matrix(const size_type rows, const size_type cols, const value_type value)
    : buffer(rows, std::string(cols, value)) {}

Matrix<char>::Matrix(const std::initializer_list<const std::string>& il)
    : buffer(il.begin(), il.end()) {}

void Matrix<char>::resize_rows(const size_type rows, const value_type value)
{
    buffer.resize(rows, std::string(cols(), value));
}
void Matrix<char>::resize_cols(const size_type cols, const value_type value)
{
    for (auto &line : buffer)
        line.resize(cols, value);
}
void Matrix<char>::resize(const size_type rows, const size_type cols, const value_type value)
{
    resize_rows(rows, value);
    resize_cols(cols, value);
}

inline auto Matrix<char>::operator()(const size_type row, const size_type col) -> reference
{
    return buffer[row][col];
}
inline auto Matrix<char>::operator()(const size_type row, const size_type col) const -> value_type
{
    return buffer[row][col];
}
inline auto Matrix<char>::at(const size_type row, const size_type col) -> reference
{
    return buffer.at(row).at(col);
}
inline auto Matrix<char>::at(const size_type row, const size_type col) const -> value_type
{
    return buffer.at(row).at(col);
}

inline auto Matrix<char>::rows() const -> size_type { return buffer.size(); }
inline auto Matrix<char>::cols() const -> size_type { return buffer.front().size(); }
inline auto Matrix<char>::size() const -> size_type { return rows() * cols(); }

void Matrix<char>::sort_rows(const std::function<bool(const_reference, const_reference)>& comp)
{
    for (auto& line : buffer)
        std::sort(line.begin(), line.end(), comp);
}

void Matrix<char>::sort_cols(const std::function<bool(const_reference, const_reference)>& comp)
{
    for (size_type col = 0; col < cols(); ++col)
    {
        size_type min = 0;
        for (size_type i = 0; i < rows() - 1; ++i)
        {
            min = i;
            for (size_type j = i + 1; j < rows(); ++j)
            {
                if (buffer[j][col] < buffer[min][col])
                    min = j;
            }
            std::swap(buffer[i][col], buffer[min][col]);
        }
    }
}

bool Matrix<char>::equal_in_size(const Matrix& other) const
{
    return this->rows() == other.rows() && this->cols() == other.cols();
}

std::ostream& operator<<(std::ostream& out, const Matrix<char>& matrix)
{
    for (Matrix<char>::size_type i = 0; i < matrix.rows(); ++i)
    {
        for (Matrix<char>::size_type j = 0; j < matrix.cols() - 1; ++j)
            out << matrix(i, j) << "\t|\t";
        out << matrix(i, matrix.cols() - 1) << "\n";
    }
    return out;
}
