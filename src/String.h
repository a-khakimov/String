#ifndef __CUSTOM_STRING_H__
#define __CUSTOM_STRING_H__

#include <cstdlib>
#include <utility>
#include <ostream>

class String {
public:
    String ();
    String (const char*);
    String (const String&);
    String (String&&) noexcept;
    virtual ~String();

    void reserve (const size_t size);
    void clear() noexcept;
    bool empty() const noexcept;
    size_t length() const noexcept;
    size_t size() const noexcept;
    char& at(const size_t pos) const;
    String& append (const String& str);
    String& append (const char* s);
    void push_back (const char c);
    const char* data() const noexcept;

    char& operator[] (const size_t pos) const;
    String& operator= (const String& other);
    String& operator+= (const String& other);
    String& operator+= (const char* cstr);
    bool operator< (const String& other) const;

    friend const String operator+ (const String& lstr, const String& rstr);
    friend const String operator+ (const String& lstr, const char* rstr);
    friend const String operator+ (const char* lstr, const String& rstr);

    friend std::ostream& operator<< (std::ostream& os, const String& str);
    friend std::istream& operator>> (std::istream& is, String& str);

    friend bool operator== (const String& lstr, const String& rstr);
    friend bool operator== (const String& lstr, const char* rstr);
    friend bool operator!= (const String& lstr, const String& rstr);

private:
    struct iterator_options {
        char* first;
        const size_t* size;
        size_t pos;
        iterator_options(char* f = nullptr, const size_t* s = nullptr, size_t p = 0);
    };

public:
    class const_iterator {
        void increment();
        void decrement();
        char& get() const;
    public:
        const_iterator();
        const_iterator(iterator_options it);
        const char& operator* () const;
        const_iterator& operator++ ();
        const_iterator& operator-- ();
        const_iterator& operator++ (int);
        const_iterator& operator-- (int);
        bool operator== (const const_iterator& rhs) const;
        bool operator!= (const const_iterator& rhs) const;

    protected:
        iterator_options current;
        friend class String;
    };

    class iterator : public const_iterator {
    public:
        iterator();
        iterator(iterator_options it);
        char& operator* ();
        iterator& operator++ ();
        iterator& operator-- ();
        iterator& operator++ (int);
        iterator& operator-- (int);
        bool operator== (const const_iterator& rhs) const;
        bool operator!= (const const_iterator& rhs) const;
    };

    iterator begin() noexcept;
    iterator end() noexcept;
    const_iterator begin() const noexcept;
    const_iterator end() const noexcept;
    const_iterator cbegin() const noexcept;
    const_iterator cend() const noexcept;

private:
    size_t m_length = 0;
    size_t m_capacity = 0;
    char* m_data = nullptr;
};

#endif
