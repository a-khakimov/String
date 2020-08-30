#include "String.h"
#include <cstring>
#include <exception>
#include <iterator>

String::String() :
    m_length { 0 },
    m_data { new char[m_length + 1] }
{
    m_data[m_length] = '\0';
}

String::String(const char* cstr)
{
    if (cstr == nullptr) {
        throw std::logic_error("String: Invalid construct argument");
    }

    m_length = std::strlen(cstr);
    m_data = new char[m_length + 1];
    std::memcpy(m_data, cstr, m_length);
    m_data[m_length] = '\0';
}

String::String(const String &other)
{
    m_length = other.m_length;
    m_data = new char[m_length + 1];
    std::memcpy(m_data, other.m_data, m_length);
    m_data[m_length] = '\0';
}

String::String(String &&other) noexcept
{
    m_data = other.m_data;
    m_length = other.m_length;
    other.m_data = nullptr;
    other.m_length = 0;
}

String::~String()
{
    delete[] m_data;
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
    return m_length;
}

char &String::at(const size_t pos) const
{
    if (pos > m_length) {
        throw std::out_of_range("String::at()");
    }
    return m_data[pos];
}

const char* String::data() const noexcept
{
    return m_data;
}

char &String::operator[](const size_t pos) const
{
    return m_data[pos];
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

