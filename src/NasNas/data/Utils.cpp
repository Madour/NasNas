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
    return path.substr(beg, end-beg);
}

auto path::getFilename(const std::string& path) -> std::string {
    int beg = 0;
    for (int i = path.size(); i > 0; --i) {
        if (path[i] == '/') {
            beg = i+1;
            break;
        }
    }
    return path.substr(beg, path.size()-beg);
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
    return path.substr(beg, path.size()-beg);
}

auto path::getPath(const std::string& path) -> std::string {
    int end = path.size();
    for (int i = path.size(); i > 0; --i) {
        if (path[i] == '/') {
            end = i+1;
            break;
        }
    }
    if (end == path.size() && path == path::getFilename(path)) {
        end = 0;
    }
    return path.substr(0, end);
}

void path::removeFilename(std::string& path) {
    int end = path.size();
    for (int i = path.size(); i > 0; --i) {
        if (path[i] == '/') {
            end = i+1;
            break;
        }
    }
    if (end == path.size() && path == path::getFilename(path)) {
        path = "";
        return;
    }
    path = std::string(path.begin(), path.begin()+end);
}
