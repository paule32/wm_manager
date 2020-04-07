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
#include "win0001.h"         // factory
#include "win0001_impl.h"    // impl

// to avoid overlaps ...
namespace kallup {

TWindowManager::Unknown Create_TWindowManager(Implementations impl)
{
    switch (impl) {
    case Implementations::Text:
         return std::make_unique<Text_TWindowManager>();
         
    case Implementations::Simple:
         return std::make_unique<Simple_TWindowManager>();
    
    case Implementations::Windows95:
         return std::make_unique<Windows95_TWindowManager>();

    default:
        return nullptr;
    }
}

TWindowApplication::Unknown Create_TWindowApplication(Application impl)
{
    switch (impl) {
    case Application::
    }
}

}   // namespace: kallup

