/* 
 * File:   CurlMessage.h
 * Author: Giuseppe
 *
 * Created on March 25, 2014, 11:08 PM
 */

#ifndef CURLMESSAGE_H
#define	CURLMESSAGE_H

#include "CurlMulti.h"

using curl::CurlMulti;

namespace curl {
    class CurlMulti::CurlMessage {
    public:
        CurlMessage(CURLMSG message, CurlEasy curl, void *whatever, CURLcode result) : message(message), curl(curl), whatever(whatever), result(result) {};
        const CURLMSG getMessage() const throw();
        const CURLcode getResult() const throw();
        const CurlEasy getCurl() const throw();
        const void *getWhatever() const throw();
    private:
        CURLMSG message;
        CurlEasy curl;
        void *whatever;
        CURLcode result;
    };
}

#endif	/* CURLMESSAGE_H */