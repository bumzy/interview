#include "qh_string.h"
#include <assert.h>
#include <string.h>

namespace qh
{
    // TODO ½«ÔÚÕâÀïÐ´ÊµÏÖ´úÂë

    string::string()
        //: data_(NULL), len_(0)
    {
        len_ = 0;
        data_ = new char[1];
        data_[0] = '\0';
    }

    string::string( const char* s )
    {
        if(s == NULL)
        {
            len_ = 0;
            data_ = new char[1];
            data_[0] = '\0';
        }
        else
        {
            len_ = strlen(s);
            data_ = new char[len_ + 1];
            strncpy(data_, s, len_);
            data_[len_] = '\0';
        }
    }

    string::string( const char* s, size_t len )
    {
        if(s == NULL)
        {
            len_ = 0;
            data_ = new char[1];
            data_[0] = '\0';
        }
        else
        {
            size_t sLen = strlen(s);
            len_ = len < sLen ? len : sLen;
            data_ = new char[len_ + 1];
            strncpy(data_, s, len_);
            data_[len_] = '\0';
        }
    }

    string::string( const string& rhs )
    {
        if(rhs.data_ == NULL)
        {
            len_ = 0;
            data_ = new char[1];
            data_[0] = '\0';
        }
        else
        {
            len_ = rhs.len_;
            data_ = new char[len_+1];
            strncpy(data_, rhs.data_, len_);
            data_[len_] = '\0';
        }
    }

    string& string::operator=( const string& rhs )
    {
        if(this == &rhs)
            return *this;

        string temp(rhs);

        size_t tLen = len_;
        len_ = temp.len_;
        temp.len_ = tLen;

        char * tData = data_;
        data_ = temp.data_;
        temp.data_ = tData;

        return *this;
    }

    string::~string()
    {
        delete[] data_;
    }

    size_t string::size() const
    {
        return len_;
    }

    const char* string::data() const
    {
        return data_;
    }

    const char* string::c_str() const
    {
        return data_;
    }

    char& string::operator[]( size_t index )
    {
        //assert(index < len_);
        return *(data_ + index);
    }
}
