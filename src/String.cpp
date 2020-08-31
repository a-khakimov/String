#include "String.h"
#include <cstring>
#include <exception>
#include <iterator>
#include <iostream>

String::String() :
    m_length { 0 },
    m_capacity { 1 },
    m_data { new char[m_capacity] }
{
    m_data[m_length] = '\0';
}

String::String(const char* cstr)
{
    if (cstr == nullptr) {
        throw std::logic_error("String: Invalid construct argument");
    }

    m_length = std::strlen(cstr);
    m_capacity = m_length + 1;
    m_data = new char[m_capacity];
    std::memcpy(m_data, cstr, m_length);
    m_data[m_length] = '\0';
}

String::String(const String &other)
{
    m_length = other.m_length;
    m_capacity = m_length + 1;
    m_data = new char[m_capacity];
    std::memcpy(m_data, other.m_data, m_length);
    m_data[m_length] = '\0';
}

String::String(String &&other) noexcept
{
    m_data = other.m_data;
    m_length = other.m_length;
    m_capacity = other.m_capacity;
    other.m_data = nullptr;
    other.m_length = 0;
    other.m_capacity = 0;
}

String::~String()
{
    delete[] m_data;
}

void String::reserve(const size_t sz)
{
    if (m_capacity >= sz) {
        return;
    }

    m_capacity = sz;

    if (m_data == nullptr) {
        m_data = new char[m_capacity];
        return;
    }

    char* tmp = new char[m_capacity];
    std::memcpy(tmp, m_data, m_length + 1);
    delete [] m_data;
    m_data = tmp;
}

void String::clear() noexcept
{
    m_length = 0;
    delete [] m_data;
}

bool String::empty() const noexcept
{
    return m_length;
}

size_t String::length() const noexcept
{
    return m_length;
}

size_t String::size() const noexcept
{
    return m_capacity;
}

char &String::at(const size_t pos) const
{
    if (pos > m_length) {
        throw std::out_of_range("String::at()");
    }
    return m_data[pos];
}

String &String::append(const String& str)
{
    for (const auto c : str) {
        push_back(c);
    }
    return *this;
}

String &String::append(const char* s)
{
    append(String(std::move(s)));
    return *this;
}

void String::push_back(const char c)
{
    if (m_length >= m_capacity) {
        const size_t new_sz = (m_length == 0) ? (m_length + 1) : (m_length * 2);
        reserve(new_sz);
    }
    m_data[m_length] = c;
    m_length++;
    m_data[m_length] = '\0';
}

void String::pop_back()
{

}

const char* String::data() const noexcept
{
    return m_data;
}

char &String::operator[](const size_t pos) const
{
    return m_data[pos];
}

String::const_iterator String::begin() const
{
    return iterator_t(m_data, &m_length, 0);
}

String::const_iterator String::end() const
{
    return iterator_t(m_data, &m_length, m_length);
}

bool operator!=(const String &lstr, const String &rstr)
{
    return !(lstr == rstr);
}

bool operator==(const String& lstr, const char* rstr)
{
    return (lstr == String(rstr));
}

bool operator==(const String &lstr, const String &rstr)
{
    if ((lstr.m_data == nullptr) or (rstr.m_data == nullptr)) {
        return false;
    }
    return !std::strcmp(lstr.m_data, rstr.m_data);
}

std::istream& operator>>(std::istream &is, String &str)
{
    is.getline(str.m_data, sizeof(str.m_data));
    return is;
}

std::ostream& operator<<(std::ostream &os, const String &str)
{
    std::copy(str.m_data, str.m_data + str.m_length, std::ostream_iterator<char>(os));
    return os;
}

const String operator+(const String &lstr, const String &rstr)
{
    String str;
    str.m_length = lstr.length() + rstr.length() + 1;
    str.m_data = new char[str.m_length];
    std::memcpy(str.m_data, lstr.data(), lstr.length());
    std::memcpy(str.m_data + lstr.length(), rstr.data(), rstr.length());
    str.m_data[str.m_length] = '\0';
    return str;
}

const String operator+(const String &lstr, const char *rstr)
{
    return (lstr + String(rstr));
}

const String operator+(const char *lstr, const String &rstr)
{
    return (String(lstr) + rstr);
}


String::const_iterator::const_iterator()
{

}

String::const_iterator::const_iterator(String::iterator_t it) : current(it)
{

}

const char& String::const_iterator::operator*() const
{
    return *(current.first + current.pos);
}

String::const_iterator& String::const_iterator::operator++()
{
    if (current.pos > *current.size) {
        throw;
    }
    ++current.pos;
    return *this;
}

String::const_iterator &String::const_iterator::operator--()
{
    if (current.pos <= 0) {
        throw;
    }
    --current.pos;
    return *this;
}

String::const_iterator& String::const_iterator::operator++(int)
{
    if (current.pos > *current.size) {
        throw;
    }
    ++current.pos;
    return *this;
}

String::const_iterator& String::const_iterator::operator--(int)
{
    if (current.pos <= 0) {
        throw;
    }
    --current.pos;
    return *this;
}

bool String::const_iterator::operator==(const String::const_iterator &rhs) const
{
    return current.pos == rhs.current.pos;
}

bool String::const_iterator::operator!=(const String::const_iterator &rhs) const
{
    return current.pos != rhs.current.pos;
}

String::iterator_t::iterator_t(char *f, const size_t* s, size_t p)
    : first {f}, size {s}, pos{p}
{

}
