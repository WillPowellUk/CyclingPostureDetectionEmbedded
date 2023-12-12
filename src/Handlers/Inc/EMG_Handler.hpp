#pragma once
#include "../../utils/inc/commonParams.hpp"
#include <vector>

class EMGHandler {
public:
    EMGHandler();
    void init();

    std::vector<Common::EMGPackage> getPackets();

private:
};