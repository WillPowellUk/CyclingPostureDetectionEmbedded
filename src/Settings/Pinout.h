#pragma once

namespace Pinout 
{
    /*        IMU Pinout          */
    namespace IMU
    {
        constexpr const int AD0_VAL = 1;
    } // namespace IMU

    /*        SD Pinout          */
    namespace SD
    {
        constexpr const int DATA1 = 4;
        constexpr const int DATA0 = 2;
        constexpr const int CLK = 14;
        constexpr const int CMD = 15;
        constexpr const int DATA3 = 13;
        constexpr const int DATA4 = 12;
    } // namespace SD
    

} // namespace Pinout