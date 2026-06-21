#include "usb.hpp"
#include "windows.hpp"

namespace USB {
    Result Init(void) {
        return 0;
    }

    void Exit(void) {
    }

    bool Connected(void) {
        return false;
    }

    void Unmount(void) {
        devices_list.clear();
    }
}
