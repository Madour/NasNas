/**
* Created by Modar Nasser on 10/11/2020.
**/

#include "NasNas/data/Utils.hpp"

using namespace ns::utils;

auto path::getStem(const std::string& path) -> std::string {
    int beg = 0;
    int end = path.size();
    for (int i = path.size(); i > 0; --i) {
        if(path[i] == '.' && end == path.size())
            end = i;
        if (path[i] == '/') {
            beg = i+1;
            break;
        }
    }
    if (end == beg)
        end = path.size();
    return std::string(path.begin()+beg, path.begin()+end);
}

auto path::getFilename(const std::string& path) -> std::string {
    int beg = 0;
    for (int i = path.size(); i > 0; --i) {
        if (path[i] == '/') {
            beg = i+1;
            break;
        }
    }
    return std::string(path.begin()+beg, path.end());
}

auto path::getExtension(const std::string& path) -> std::string {
    int beg = 0;
    for (int i = path.size(); i > 0; --i) {
        if (path[i] == '.') {
            beg = i;
            break;
        }
    }
    if (beg == 0 || path[beg-1] == '/')
        beg = path.size();
    return std::string(path.begin()+beg, path.end());
}

