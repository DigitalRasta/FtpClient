/* 
 * File:   CurlPair.h
 * Author: Giuseppe
 *
 * Created on March 25, 2014, 10:39 PM
 */

#ifndef CURLPAIR_H
#define	CURLPAIR_H

#include "CurlHttpPost.h"
#include <string>

using curl::CurlHttpPost;
using std::string;

namespace curl {
    template<class T, class K> class CurlPair {
    public:
        CurlPair(const T option, const K value) : option(option), value(value) {};
        inline const T first() const throw() { return this->option; }
        inline const K second() const throw() { return this->value; }
    private:
        const T option;
        const K value;
    };
    
    // Template specialization for strings
    template<class T> class CurlPair<T,string> {
    public:
        CurlPair(const T option, const string value) : option(option), value(value) {};
        inline const T first() const throw() { return this->option; }
        inline const char *second() const throw() { return this->value.c_str(); }
    private:
        const T option;
        const string value;
    };
    
    // Template specialization for CurlHttpPost type
    template<class T> class CurlPair<T,CurlHttpPost> {
    public:
        CurlPair(const T option, const CurlHttpPost value) : option(option), value(value) {}
        inline const T first() const throw() { return this->option; }
        inline const curl_httppost *second() const throw() { return this->value.getFormPost(); }
    private:
        const T option;
        const CurlHttpPost value;
    };
}

#endif	/* CURLPAIR_H */