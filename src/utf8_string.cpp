

/*
*
*	Copyright (C) 2016 Luxon Jean-Pierre
*	gumichan01.olympe.in
*
*
*	Luxon Jean-Pierre (Gumichan01)
*	luxon.jean.pierre@gmail.com
*
*/

#include "utf8_string.hpp"


UTF8string::UTF8string() : utf8length(0){}

UTF8string::UTF8string(const std::string &str)
 : UTF8string()
{
    for(auto c : str)
    {
        utf8data.push_back(c);
    }

    /// @todo Check if the utf-8 string is valid
    utf8length = utf8_length_();
}


UTF8string::UTF8string(const UTF8string &u8str)
{
    utf8data = u8str.utf8data;
    utf8length = u8str.utf8length;
}


const UTF8string& UTF8string::operator =(const char * str)
{
    utf8data = str;
    utf8length = utf8_length_();
    return *this;
}


const UTF8string& UTF8string::operator =(const std::string str)
{
    for(auto c : str)
    {
        utf8data.push_back(c);
    }

    /// @todo Check if the utf-8 string is valid
    utf8length = utf8_length_();
    return *this;
}


const UTF8string& UTF8string::operator =(const UTF8string u8str)
{
    utf8data = u8str.utf8data;
    utf8length = u8str.utf8length;
    return *this;
}


const UTF8string& UTF8string::operator +=(const std::string str)
{
    utf8data += str;
    utf8length = utf8_length_();
    return *this;
}


const UTF8string& UTF8string::operator +=(const UTF8string u8str)
{
    for(auto c : u8str.utf8data)
    {
        utf8data.push_back(c);
    }

    utf8length = utf8_length_();
    return *this;
}


void UTF8string::clear()
{
    utf8data.clear();
    utf8length = 0;
}

bool UTF8string::empty()
{
    return utf8length == 0;
}

/// @bug The substring is not correct
UTF8string UTF8string::substr(size_t pos,size_t len)
{
    if(pos > utf8length)
        return std::string();

    const size_t n = (len == static_cast<size_t>(-1)
                      || len > utf8length) ? (utf8length - pos) : (len - pos);
    std::string s;

    for(auto j = pos; j < n; j++)
    {
        const utf8_len_t cplen = utf8_codepoint_len(j);
        auto i = j;

        while(i < (j+cplen))
        {
            s.push_back(utf8data[i++]);
        }
    }

    return s;
}


utf8_len_t UTF8string::utf8_codepoint_len(size_t j)
{
    if (0xf0 == (0xf8 & utf8data[j]))
    {
        return 4;
    }
    else if (0xe0 == (0xf0 & utf8data[j]))
    {
        return 3;
    }
    else if (0xc0 == (0xe0 & utf8data[j]))
    {
        return 2;
    }
    else
        return 1;
}


utf8_len_t UTF8string::utf8_size()
{
    return utf8data.size();
}


bool UTF8string::utf8_is_valid_()
{
    auto end_data = utf8data.end();
    auto it = utf8data.begin();

    while(it != end_data)
    {
        /// @todo check the validity
        it++;
    }

    return true;
}


utf8_len_t UTF8string::utf8_length_()
{
    auto end_data = utf8data.end();
    auto it = utf8data.begin();
    utf8_len_t len = 0;

    while(it != end_data)
    {
        byte_t byte = *it;

        if (0xf0 == (0xf8 & byte))
        {
            // 4-byte utf8 character
            // (0b11110xxx 0bxxxxxxxx 0bxxxxxxxx 0bxxxxxxxx)
            it += 4;
        }
        else if (0xe0 == (0xf0 & byte))
        {
            // 3-byte utf8 code point (0b110xxxxx 0bxxxxxxxx 0bxxxxxxxx)
            it += 3;
        }
        else if (0xc0 == (0xe0 & byte))
        {
            // 2-byte utf8 code point (0b110xxxxx 0bxxxxxxxx)
            it += 2;
        }
        else
        {
            // 1-byte utf8 code point (0b0xxxxxxx)
            it += 1;
        }

        // We want the number of characters (utf-8 code point)
        len += 1;
    }

    return len;
}

utf8_len_t UTF8string::utf8_length()
{
    return utf8length;
}

const char * UTF8string::utf8_str() const
{
    std::string str;

    for(auto c : utf8data)
    {
        str += c;
    }

    return str.c_str();
}

/// @bug Th function fails when the length of the string is greater then than 19
bool operator ==(const UTF8string &str1, const UTF8string &str2)
{
    const std::string s1 = str1.utf8_str();
    const std::string s2 = str2.utf8_str();

    return s1 == s2;
}

bool operator !=(const UTF8string &str1, const UTF8string &str2)
{
    return !(str1 == str2);
}



