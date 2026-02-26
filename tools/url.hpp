// Copyright (C) 2026 CZF-H
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

//
// Created by wanjiangzhi on 2026/1/27.
//

#ifndef WEIYAN_URL_HPP
#define WEIYAN_URL_HPP

#include <deque>

#include "json.hpp"

#include <sstream>
#include <iomanip>
#include <vector>
#include <utility>

#define WEIYAN_URL_PAIR(arg) {#arg, arg}
#define WEIYAN_URL_PAIRN(arg) {#arg, Num2Str(arg)}

namespace Weiyan {
    namespace URL {
        namespace type {
            using string = std::string;
            using array = std::vector<string>;
            using param = std::pair<string, string>;
            using params = std::deque<param>;
            using j_params = json;
        }

        inline type::string Enc(const type::string& val) {
            std::ostringstream escaped;
            escaped.fill('0');
            escaped << std::hex;
            for (const char c : val)
                if (
                    (c >= 'a' && c <= 'z') ||
                    (c >= 'A' && c <= 'Z') ||
                    (c >= '0' && c <= '9') ||
                    c == '-' || c == '_' || c == '.' || c == '~'
                )
                    escaped << c;
                else
                    escaped << '%' << std::setw(2) <<
                        static_cast<int>(
                            static_cast<unsigned char>(c)
                        );
            return escaped.str();
        }

        inline bool ParamIsAry(const type::string& param_str) {
            return !param_str.empty() &&
                   param_str.front() == '[' &&
                   param_str.back() == ']';
        }

        inline type::string Fields(const type::params& vec) {
            std::ostringstream oss;
            bool is_fst = true;

            for (const auto& pair : vec) {
                auto k = pair.first, v = pair.second;
                if (k.empty() || v.empty()) continue;
                oss << (is_fst ? "" : "&") << Enc(k) << '=' << (ParamIsAry(v) ? v : Enc(v));
                is_fst = false;
            }

            return oss.str();
        }

        inline type::string Params(const type::params& vec) {
            std::ostringstream oss;
            bool is_fst = true;

            for (const auto& pair : vec) {
                auto k = pair.first, v = pair.second;
                if (k.empty() || v.empty()) continue;
                oss << (is_fst ? '?' : '&') << Enc(k) << '=' << (ParamIsAry(v) ? v : Enc(v));
                is_fst = false;
            }

            return oss.str();
        }

        inline type::string Param(const type::param& pair) {
            return Params({pair});
        }

        inline type::string Param(const type::string& key, const type::string& val) {
            return Param({key, val});
        }

        inline type::string Array(const type::array& arr) {
            std::ostringstream oss;
            if (!arr.empty()) {
                bool is_fst = true;
                oss << '[';
                for (const auto& v : arr) {
                    oss << (is_fst ? "" : std::string(",")) << Enc(v);
                    is_fst = false;
                }
                oss << ']';
            } else return "[]";
            return oss.str();
        }

        inline type::string JParams(const type::j_params& json, const uint8_t indent = 0) {
            return json.dump(indent);
        }
    }

}

#endif //WEIYAN_URL_HPP
