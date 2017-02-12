#ifndef QIHOO_VECTOR_H_
#define QIHOO_VECTOR_H_

#include <stdio.h>
#include <assert.h>
#include <algorithm>

namespace qh
{
    template<class T>
    class vector {
    public:
        //ctor
        vector()
            : data_(NULL), size_(0), capacity_(0)
        {
        }

        explicit vector( size_t n, const T& value = T())
        {
            size_ = capacity_ = n;
            data_ = new T[n];
            for (size_t i = 0; i < n; i++)
            {
                data_[i] = value;
            }
        }

        vector( const vector<T>& rhs )
        {
            if(rhs.data_ == NULL || rhs.size_ == 0)
            {
                size_ = capacity_ = 0;
                data_ = NULL;
            }
            else
            {
                size_ = rhs.size_;
                capacity_ = rhs.capacity_;
                data_ = new T[capacity_];
                for (size_t i = 0; i < size_; i++)
                {
                    data_[i] = rhs.data_[i];
                }
            }
        }

        vector<T>& operator=(const vector<T>& rhs)
        {
            if(this == &rhs)
                return *this;

            vector<T> temp(rhs);
            std::swap(data_, temp.data_);
            std::swap(size_, temp.size_);
            std::swap(capacity_, temp.capacity_);

            return *this;
        }

        //dtor
        ~vector()
        {
            if (data_)
            {
                delete[] data_;
            }
        }

        //get
        size_t size() const
        {
            return size_;
        }
        size_t capacity() const
        {
            return capacity_;
        }

        // set & get
        T& operator[](size_t index);

        // set
        void push_back(const T& element);
        void pop_back(T& element);
        void resize(size_t size);
        void reserve(size_t capacity);
        void clear();
        bool empty() const;

    private:
        T*      data_;
        size_t  size_;
        size_t  capacity_;
    };

    template<class T>
    T& vector<T>::operator[](size_t index)
    {
        assert(index < size_);
        return *(data_ + index);
    }

    template<class T>
    void vector<T>::push_back(const T& element)
    {
        size_t old_size = size_;
        if(old_size == capacity_)
        {
            resize(old_size + 1);
        }
        else
        {
            ++size_;
        }
        data_[old_size] = element;
    }

    template<class T>
    void vector<T>::pop_back(T& element)
    {
        element = data_[--size_];
    }

    template<class T>
    void vector<T>::resize(size_t size)
    {
        size_t old_capacity = capacity_;
        if(old_capacity < size)
        {
            if(old_capacity == 0)
                old_capacity = 1;
            while(old_capacity < size)
                old_capacity *= 2;
            reserve(old_capacity);
        }
        size_ = size;
    }

    template<class T>
    void vector<T>::reserve(size_t capacity)
    {
        if(capacity_ == capacity)
            return;

        T* new_data = new T[capacity];
        capacity_ = capacity;
        if(size_ > capacity)
            size_ = capacity;
        for(size_t i = 0; i < size_; ++i)
        {
            new_data[i] = data_[i];
        }
        std::swap(new_data, data_);
        delete[] new_data;
    }

    template<class T>
    void vector<T>::clear()
    {
        //delete[] data_;
        //size_ = capacity_ = 0;
        size_ = 0;
    }

    template<class T>
    bool vector<T>::empty() const
    {
        return size_ == 0;
    }
}

#endif


