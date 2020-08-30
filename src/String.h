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

    void clear() noexcept;
    bool empty() const noexcept;
    size_t length() const noexcept;
    size_t size() const noexcept;
    char& at(const size_t pos) const;
    String& append (const String& str);
    String& append (const char* s);
    void push_back (const char c);
    void pop_back();
    const char* c_str() const noexcept;
    const char* data() const noexcept;

    char& operator[] (const size_t pos) const;

    friend const String operator+ (const String& lstr, const String& rstr);
    friend const String operator+ (const String& lstr, const char* rstr);
    friend const String operator+ (const char* lstr, const String& rstr);

    friend std::ostream& operator<< (std::ostream& os, const String& str);
    friend std::istream& operator>> (std::istream& is, String& str);

    friend bool operator== (const String& lstr, const String& rstr);
    friend bool operator== (const String& lstr, const char* rstr);
    friend bool operator!= (const String& lstr, const String& rstr);

private:
    size_t m_length = 0;
    char* m_data = nullptr;
};

#endif
