//
//  CurlVersion.h
//  curlcpp
//
//  Created by Giuseppe Persico on 30/03/14.
//  Copyright (c) 2014 Giuseppe Persico. All rights reserved.
//

#ifndef __curlcpp__CurlVersion__
#define __curlcpp__CurlVersion__

#include <curl/curl.h>
#include <string>
#include <list>

using std::string;
using std::list;

namespace curl {
    class CurlVersion {
    public:
        CurlVersion(const curl_version_info_data *);
        const string getHost() const throw();
        const string getSSLVersion() const throw();
        const string getLibzVersion() const throw();
        const string getAres() const throw();
        const string getLibidn() const throw();
        const string getLibSSHVersion() const throw();
        const unsigned int getVersionNumber() const throw();
        const int getFeatures() const throw();
        const int getAresNumber() const throw();
        const int getIconvVersionNumber() const throw();
        const long getSSLVersionNumber() const throw();
        const list<string> getProtocols() const throw();
    private:
        const curl_version_info_data *version;
    };
}

#endif /* defined(__curlcpp__CurlVersion__) */