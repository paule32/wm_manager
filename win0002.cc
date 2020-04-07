#include "win0002.h"

// to avoid overlaps ...
namespace kallup {

int TWindowController::number = 1;

TWindowController::TWindowController()
    : status("on") {
    std::cout << "create controller: " << std::dec << number << std::endl;
    number++;
}

TWindowController::~TWindowController()
{
    --number;
    std::cout << "destroy controller: " << std::dec << number << std::endl;
}

void TWindowController::get_status() const
{
    for_each(window.begin(), window.end(), [](std::weak_ptr<TWindowController> wp) {
        auto p = wp.lock();
        if (p) {
            std::cout << "status of " << p->number-1 << " = " << p->status <<
            std::endl;
        }
        else {
            std::cout << "ct" << std::endl;
        }
    });
}

void RunTest()
{
    std::vector<std::shared_ptr< TWindowController > > v{
        std::make_shared< TWindowController > (),
        std::make_shared< TWindowController > (),
        std::make_shared< TWindowController > (),
        std::make_shared< TWindowController > (),
        std::make_shared< TWindowController > (),
    };

    // Each controller depends on all others not being deleted.
    // Give each controller a pointer to all the others.
    for (int i = 0; i < v.size(); ++i)
    {
        for_each(v.begin(), v.end(), [&v, i](std::shared_ptr< TWindowController > p) {
            if (p->number != i)
            {
                v[i]->window.push_back(std::weak_ptr< TWindowController >(p));
                std::cout << "push_back to v[" << i << "]: " << p->number-1 <<
                std::endl;
            }
        });
    }
    
    for_each(v.begin(), v.end(), [](std::shared_ptr< TWindowController > &p) {
        std::cout << "use_count = " << p.use_count() <<
        std::endl;
        p->get_status();
    });    
}

}   // namespace: kallup
