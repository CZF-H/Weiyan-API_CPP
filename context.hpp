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

#ifndef WEIYAN_CONTEXT_HPP
#define WEIYAN_CONTEXT_HPP

#include <string>
#include <memory>
#include "tools/encrypt.hpp"

namespace Weiyan {
    auto defaultServer = "http://wy.llua.cn/api";

    class CtxObj {
        std::string mAppKey;
        std::string mAPPID;
        std::string mEncKey;
        std::string mServer;
    public:
        using Context = std::shared_ptr<CtxObj>;

        RC4 RC4;

        explicit CtxObj(
            std::string appKey,
            std::string appID,
            std::string encKey = {},
            std::string server = defaultServer
        ) : mAppKey(std::move(appKey)),
            mAPPID(std::move(appID)),
            mEncKey(std::move(encKey)),
            mServer(std::move(server)),
            RC4(mEncKey)
        {}

        std::string API(const std::string& endpoint = {}) const {
            std::string server = mServer;
            if (!server.empty() && server.back() != '/')
                server += '/';
            return server + endpoint;
        }

        std::string& appKey() {return mAppKey;}

        std::string& appID() { return mAPPID; }

        std::string& encKey() { return mEncKey; }

        std::string& server() { return mServer; }

        CtxObj* self() { return this; }
    };

    using Context = CtxObj::Context;

    /**
     * 函数式创建上下文
     * @param appKey 微验APPKEY
     * @param appID 微验APPID
     * @param encKey 微验RC4密钥
     * @param server 微验API服务器（一般不设置）
     * @return 共享智能指针包装类
     */
    inline Context Create(
        std::string appKey,
        std::string appID,
        std::string encKey = {},
        std::string server = defaultServer
    ) {
        return std::make_shared<CtxObj>(
                std::move(appKey),
                std::move(appID),
                std::move(encKey),
                std::move(server)
        );
    }
}

#endif //WEIYAN_CONTEXT_HPP
