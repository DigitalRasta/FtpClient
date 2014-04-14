//
//  CurlVersion.cpp
//  curlcpp
//
//  Created by Giuseppe Persico on 30/03/14.
//  Copyright (c) 2014 Giuseppe Persico. All rights reserved.
//

#include "CurlVersion.h"

using curl::CurlVersion;

// Implementation of constructor
CurlVersion::CurlVersion(const curl_version_info_data *version) {
    this->version = version;
}

// Implementation of getHost method
const string CurlVersion::getHost() const throw() {
    return string(this->version->host);
}

// Implementation of getSSLVersion method
const string CurlVersion::getSSLVersion() const throw() {
    return string(this->version->ssl_version);
}

// Implementation of getLibzVersion method
const string CurlVersion::getLibzVersion() const throw() {
    return string(this->version->libz_version);
}

// Implementation of getAres method
const string CurlVersion::getAres() const throw() {
    return string(this->version->ares);
}

// Implementation of getLibidn method
const string CurlVersion::getLibidn() const throw() {
    return string(this->version->libidn);
}

// Implementation of getLibSSHVersion
const string CurlVersion::getLibSSHVersion() const throw() {
    return string(this->version->libssh_version);
}

// Implementation of getVersionNumber
const unsigned int CurlVersion::getVersionNumber() const throw() {
    return this->version->version_num;
}

// Implementation of getFeatures
const int CurlVersion::getFeatures() const throw() {
    return this->version->features;
}

// Implementation of getAresNumber
const int CurlVersion::getAresNumber() const throw() {
    return this->version->ares_num;
}

// Implementation getIconvVersionNumber
const int CurlVersion::getIconvVersionNumber() const throw() {
    return this->version->iconv_ver_num;
}

// Implementation of getSSLVersionNumber
const long CurlVersion::getSSLVersionNumber() const throw() {
    return this->version->ssl_version_num;
}

// Implementation of getProtocols
const list<string> CurlVersion::getProtocols() const throw() {
    list<string> l;
    return l;
}

