#pragma once

namespace Pinout 
{

    /*        I2C Mux Pinout          */
    namespace I2CMux
    {
        constexpr const int SDA = A4;
        constexpr const int SCL = A5;
    } // namespace IMU

    /*        IMU Pinout          */
    namespace IMU
    {
        constexpr const int AD0_VAL = 1;
    } // namespace IMU

    /*        SD Pinout          */
    namespace SD
    {
        constexpr const int MOSI = 11;
        constexpr const int MISO = 12;
        constexpr const int CLK = 13;
        constexpr const int CS = 4;
    } // namespace SD

    /*        EMG          */
    namespace EMG
    {
        constexpr const int Pin[3] = {A0, A1, A2};
    }
    

} // namespace Pinout