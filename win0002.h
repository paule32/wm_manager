#ifndef WM_0002_H_
#define WM_0002_H_
#pragma once
#include "win0000.h"

// to avoid overlaps ...
namespace kallup {

class TWindowController
{
public:
    static int number;
    std::string status;
    std::vector<std::weak_ptr<TWindowController>> window;

    explicit TWindowController();
    ~TWindowController();
    
    // Demonstrates how to test whether the
    // pointed-to memory still exists or not.
    void get_status() const;
};

}       // namespace: kallup
#endif  // WM_0002_H_
