#include "String.h"
#include <cstring>
#include <exception>
#include <iterator>
#include <iostream>

String::String() :
    m_length { 0 },
    m_capacity { 0 },
    m_data { nullptr }
{

}

String::String(const char* cstr)
{
    append(cstr);
}

String::String(const String& other)
{
    append(other);
}

String::String(String&& other) noexcept
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
    if (m_data != nullptr) {
        delete[] m_data;
    }
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
    m_capacity = 0;
    if (m_data != nullptr) {
        delete [] m_data;
        m_data = nullptr;
    }
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
        throw std::out_of_range("String: at() out of range");
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

String& String::append(const char* s)
{
    if (s == nullptr) {
        throw std::logic_error("String: Invalid argument append(c_str)");
    }

    const size_t s_len = std::strlen(s);
    for (size_t i = 0; i < s_len; ++i) {
        push_back(s[i]);
    }

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

const char* String::data() const noexcept
{
    return m_data;
}

char &String::operator[](const size_t pos) const
{
    return m_data[pos];
}

String& String::operator=(const String& other)
{
    if (m_data != nullptr) {
        delete [] m_data;
    }
    m_length = other.m_length;
    m_capacity = m_length + 1;
    m_data = new char[m_capacity];
    std::memcpy(m_data, other.m_data, m_length);
    m_data[m_length] = '\0';
    return *this;
}

String& String::operator+=(const String &other)
{
    for (auto c : other) {
        push_back(c);
    }
    return *this;
}

String &String::operator+=(const char *cstr)
{
    append(cstr);
    return *this;
}

bool String::operator<(const String &other) const
{
    const size_t cmp_len = std::min(m_length, other.m_length);
    return (std::strncmp(m_data, other.m_data, cmp_len) < 0);
}

String::iterator String::begin() noexcept
{
    return iterator_options(m_data, &m_length, 0);
}

String::iterator String::end() noexcept
{
    return iterator_options(m_data, &m_length, m_length);
}

String::const_iterator String::begin() const noexcept
{
    return iterator_options(m_data, &m_length, 0);
}

String::const_iterator String::end() const noexcept
{
    return iterator_options(m_data, &m_length, m_length);
}

String::const_iterator String::cbegin() const noexcept
{
    return iterator_options(m_data, &m_length, 0);
}

String::const_iterator String::cend() const noexcept
{
    return iterator_options(m_data, &m_length, m_length);
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
    const size_t llen = lstr.length();
    const size_t rlen = rstr.length();
    if (llen == 0 and rlen == 0) { // for empty strings
        return true;
    }
    if ((lstr.m_data == nullptr) or (rstr.m_data == nullptr)) {
        return false;
    }
    return !std::strncmp(lstr.m_data, rstr.m_data, std::min(llen, rlen));
}

std::istream& operator>>(std::istream &is, String &str)
{
    str.clear();
    do {
        const char c = is.get();
        if (not std::isgraph(c)) {
            break;
        }
        str.push_back(c);
    } while(true);
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
    str.m_length = lstr.length() + rstr.length();
    str.m_capacity = str.m_length + 1;
    str.m_data = new char[str.m_capacity];
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


void String::const_iterator::increment()
{
    if (current.pos > *current.size) {
        throw;
    }
    ++current.pos;
}

void String::const_iterator::decrement()
{
    if (current.pos <= 0) {
        throw;
    }
    --current.pos;
}

char &String::const_iterator::get() const
{
    return *(current.first + current.pos);
}

String::const_iterator::const_iterator()
{

}

String::const_iterator::const_iterator(String::iterator_options it) : current(it)
{

}

const char& String::const_iterator::operator*() const
{
    return get();
}

String::const_iterator& String::const_iterator::operator++()
{
    increment();
    return *this;
}

String::const_iterator &String::const_iterator::operator--()
{
    decrement();
    return *this;
}

String::const_iterator& String::const_iterator::operator++(int)
{
    increment();
    return *this;
}

String::const_iterator& String::const_iterator::operator--(int)
{
    decrement();
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

String::iterator_options::iterator_options(char *f, const size_t* s, size_t p)
    : first {f}, size {s}, pos{p}
{

}

String::iterator::iterator() : const_iterator()
{

}

String::iterator::iterator(String::iterator_options it) : const_iterator(it)
{

}

char &String::iterator::operator*()
{
    return const_iterator::get();
}

String::iterator &String::iterator::operator++()
{
    const_iterator::increment();
    return *this;
}

String::iterator &String::iterator::operator--()
{
    const_iterator::decrement();
    return *this;
}

String::iterator &String::iterator::operator++(int)
{
    const_iterator::increment();
    return *this;
}

String::iterator &String::iterator::operator--(int)
{
    const_iterator::decrement();
    return *this;
}

bool String::iterator::operator==(const String::const_iterator &rhs) const
{
    return const_iterator::operator==(rhs);
}

bool String::iterator::operator!=(const String::const_iterator &rhs) const
{
    return const_iterator::operator!=(rhs);
}
