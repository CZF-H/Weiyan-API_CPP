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

#ifndef WEIYAN_TYPES_HPP
#define WEIYAN_TYPES_HPP

#include "json.hpp"
#include <ctime>
#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>

namespace Weiyan {
    class timestamp {
    public:
        using value_type = std::chrono::system_clock::time_point;
    private:
        value_type t;
    public:
        // ReSharper disable once CppNonExplicitConvertingConstructor
        timestamp(const value_type& t = {}) : t(t) {}

        template <typename... Args>
        static timestamp build(Args&&... args) {
            return {value_type(std::forward<Args>(args)...)};
        }

        const value_type& get() const {
            return t;
        }

        // ReSharper disable once CppNonExplicitConversionOperator
        operator value_type() const {
            return get();
        }

        std::string str(const std::string& fmt = {"%Y-%m-%d %H:%M:%S"}) const {
            const std::time_t c_t = std::chrono::system_clock::to_time_t(t);
            std::tm tm{};
            #ifdef _WIN32
            localtime_s(&tm, &c_t);
            #else
            localtime_r(&c_t, &tm);
            #endif
            std::ostringstream oss;
            oss << std::put_time(&tm, fmt.c_str());
            return oss.str();
        }

        explicit operator std::string() const {
            return str();
        }
    };

    class json_result {
        json j;
        bool v;
    public:
        // ReSharper disable once CppNonExplicitConvertingConstructor
        json_result(json j_ = {}) noexcept : j(std::move(j_)), v(!j.empty()) {}
        explicit json_result(const std::string& str_j) noexcept {
            try {
                j = json::parse(str_j.begin(), str_j.end());
                v = !j.empty();
            } catch (...) {}
        }

        const json& value() const {
            if (v) return j;
            throw std::logic_error("Value not found");
        }

        const json& value_or(const json& j_) noexcept {
            return v ? j : j_;
        }

        // ReSharper disable once CppNonExplicitConversionOperator
        operator bool() const noexcept {
            return v;
        }

        const json& operator*() const {
            return value();
        }

        json* operator->() noexcept {
            return &j;
        }
    };
    struct null_result {
        explicit operator json_result() const {
            return {};
        }
    };
}

#endif //WEIYAN_TYPES_HPP
