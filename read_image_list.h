//
// Created by chenzhenxiong on 4/22/20.
//

#ifndef VEGACUDA_READ_IMAGE_LIST_H
#define VEGACUDA_READ_IMAGE_LIST_H
#include <vector>
#include <fstream>
#include <algorithm>
#include <boost/algorithm/string.hpp>
    class ReadImageList {
    public:
        ReadImageList() {};

        virtual ~ReadImageList() {};
    private:
        static std::string &ltrim(std::string &str) {
            auto it2 = std::find_if(str.begin(), str.end(),
                                    [](char ch) { return !std::isspace<char>(ch, std::locale::classic()); });
            str.erase(str.begin(), it2);
            return str;
        }

        static std::string &rtrim(std::string &str) {
            auto it1 = std::find_if(str.rbegin(), str.rend(),
                                    [](char ch) { return !std::isspace<char>(ch, std::locale::classic()); });
            str.erase(it1.base(), str.end());
            return str;
        }

       static  std::string &trim(std::string &str) {
            return ltrim(rtrim(str));
        }

        static bool endwith(const std::string &str, const std::string &substr) {
            if (str.length() < substr.length()) return false;

            return str.substr(str.length() - substr.length()) == substr;
        }

    public:
        static void read_list(std::vector<std::string> &vlist, const std::string &vdpath) {

            std::ifstream fp(vdpath);
            std::cout<< "Image list open : " << vdpath<<std::endl;
            std::string line;

            while (std::getline(fp, line)) {
                trim(line);
                if (line.empty() || line[0] == '#') {
                    continue;
                }

                bool esc = false;
                if (line[0] == '"') {
                    auto p = line.find('"', 1);
                    if(p !=line.npos)
                        std::cout<< "line start with \" but not end with it: " << line<<std::endl;
                    for (int i = 1; i < (int) p; i++) {
                        if (line[i] == ',') line[i] = '?';
                    }
                    esc = true;
                }
                std::vector<std::string> vec;
                boost::split(vec, line, boost::is_any_of(","));

                for (auto &s : vec) {
                    trim(s);
                }

                if(vec.empty()){
                   std::cout<<"vec is empty"<<std::endl;
                }

                if (esc) {
                    for (auto &c : vec[0]) {
                        if (c == '?') c = ',';
                    }
                    for (auto it = vec[0].begin(); it != vec[0].end();) {
                        if (*it == '"') {
                            it = vec[0].erase(it);
                        } else {
                            it++;
                        }
                    }
                }
                vlist.push_back(vec[0]);
            }
        }
    };
#endif //VEGACUDA_READ_IMAGE_LIST_H
