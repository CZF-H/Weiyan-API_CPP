# 介绍 / Introduction

## - 中文总览
此项目是为了帮助 C++ 初学者更好对接 app.llua.cn 微验 的库文件。

**感谢以下（开源）项目（不分先后顺序）：**
+ https://github.com/nlohmann/json
+ https://github.com/curl/curl
+ https://github.com/openssl/openssl

### 项目遵循GPL-3.0协议，详见 LICENSE

**特点：**

1. **现代化**：采用工厂式，通过 Create 构建上下文并共享，设计合理；
2. **轻量化**：Header-only，只需一个 include；
3. **开源免费**：无偿分发并允许在遵守许可证的情况下进行二次创作。

**示例：**

创建对象：
```cpp
#include <iostream>
#include <windows.h>
#include "weiyan/weiyan.hpp"

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    Weiyan::Context Ctx = Weiyan::Create("QWERTYUIOP", "10000", "ASDFGHJKL");
    Weiyan::Login LoginObj(Ctx);
    Weiyan::Unbind UnbindObj(Ctx);
    Weiyan::Notice Notice(Ctx);
    
    LoginObj("ZXCVBNM1234567890");
    std::cout << LoginObj.data.dump(2) << std::endl;

    UnbindObj("ZXCVBNM1234567890");
    std::cout << UnbindObj.data.dump(2) << std::endl;

    Notice.Get();
    std::cout << Notice.data.dump(2) << std::endl;

    return 0;
}
```
