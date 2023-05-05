#pragma once

#include<vector>
#include<functional>

template<typename T>
class base_matrix
{
public:
    using value_type = typename std::vector<T>::value_type;
    using size_type = typename std::vector<T>::size_type;
    using reference = typename std::vector<T>::reference;
    using const_reference = typename std::vector<T>::const_reference;

    // ----------------------- ctors -----------------------

    base_matrix();
    base_matrix(const size_type rows, const size_type cols, const_reference value = value_type{});
    base_matrix(const std::initializer_list<const std::initializer_list<value_type>>& il);


    // ----------------------- random access read/write -----------------------

    reference operator()(const size_type row, const size_type col) { return buffer[row][col]; }
    const_reference operator()(const size_type row, const size_type col) const { return buffer[row][col]; }
    reference at(const size_type row, const size_type col) { return buffer.at(row).at(col); }
    const_reference at(const size_type row, const size_type col) const { return buffer.at(row).at(col); }


    // ----------------------- getters -----------------------

    size_type rows() const { return buffer.size(); }
    size_type cols() const { return buffer.front().size(); }
    size_type size() const { return rows() * cols(); }


    // ----------------------- resize -----------------------

    void resize_rows(const size_type rows, const_reference value = value_type{});
    void resize_cols(const size_type cols, const_reference value = value_type{});
    void resize(const size_type rows, const size_type cols, const_reference value = value_type{});


    // ----------------------- sort -----------------------

    void sort_rows(const std::function<bool(const_reference, const_reference)>& comp = std::less<value_type>());
    void sort_cols(const std::function<bool(const_reference, const_reference)>& comp = std::less<value_type>());


    // ----------------------- check -----------------------

    bool equal_in_size(const base_matrix& other) const;

protected:
    std::vector<std::vector<value_type>> buffer;
};


template<typename T>
base_matrix<T>::base_matrix() = default;

template<typename T>
base_matrix<T>::base_matrix(const size_type rows, const size_type cols, const_reference value)
    : buffer(rows, std::vector<value_type>(cols, value)) {}

template<typename T>
base_matrix<T>::base_matrix(const std::initializer_list<const std::initializer_list<value_type>>& il)
    : buffer(il.begin(), il.end()) {}


// ----------------------- resize -----------------------

template<typename T>
void base_matrix<T>::resize_rows(const size_type rows, const_reference value)
{
    buffer.resize(rows, std::vector<value_type>(cols(), value));
}

template<typename T>
void base_matrix<T>::resize_cols(const size_type cols, const_reference value)
{
    for (auto& line : buffer)
        line.resize(cols, value);
}

template<typename T>
void base_matrix<T>::resize(const size_type rows, const size_type cols, const_reference value)
{
    resize_rows(rows, value);
    resize_cols(cols, value);
}



// ----------------------- sort -----------------------

template<typename T>
void base_matrix<T>::sort_rows(const std::function<bool(const_reference, const_reference)>& comp)
{
    for (auto& row : buffer)
        std::sort(row.begin(), row.end(), comp);
}

template<typename T>
void base_matrix<T>::sort_cols(const std::function<bool(const_reference, const_reference)>& comp)
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



// ----------------------- check -----------------------

template<typename T>
inline bool base_matrix<T>::equal_in_size(const base_matrix& other) const
{
    return this->rows() == other.rows() && this->cols() == other.cols();
}

