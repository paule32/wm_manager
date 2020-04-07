// --------------------------------------------------------------------------------
// MIT License
//
// Copyright (c) 2019 Jens Kallup
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
// --------------------------------------------------------------------------------
#ifndef WM_0001_H_
#define WM_0001_H_
#pragma once
# include "win0000.h"
# include "win0003.h"

// to avoid conflicts ...
namespace kallup
{
// supported implementations (style) ...
enum class Implementations {
    Simple = 1,             // simple window
    Windows95,              // windows style
    Text,                   // TurboVision
    HTML                    // HTML
};

// supported application's in this package ...
enum class Applications {
    ASM_Compiler = 1,       // assembler
    GCC_Compiler,           // gnu c
    PAS_Compiler,           // pascal
    FOR_Compiler            // fortran
}

template<typename T> class TWindowManager {
public:
    using Unknown = std::unique_ptr<TWindowManager>;
    virtual ~TWindowManager() = default;
    virtual int exec() = 0;
};

// factory
TWindowManager::Unknown Create_TWindowManager(Implementations impl);
TWindowManager::ptr Create_TWindowManager(Applications    impl);

}       // namespace: kallup
#endif  // WM_0001_H_
