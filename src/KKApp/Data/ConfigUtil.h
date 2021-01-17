#ifndef CONFIGUTIL_H
#define CONFIGUTIL_H

#define CarTest

class ConfigUtil
{
public:
#ifdef CarTest
    //car data
    constexpr static float CarHead_X = 3;
    constexpr static float CarHead_Y = 3;
    constexpr static float CarHead_Z = 3;
    constexpr static float CarHead_Blind_X = 3;
    constexpr static float CarHead_Blind_Y = 3;
    constexpr static float CarHead_Blind_Z = 3;
    constexpr static float CarHead_Blind_Angle = 90;

    constexpr static float CarBody_X = 3;
    constexpr static float CarBody_Y = 10;
    constexpr static float CarBody_Z = 3;
    constexpr static float CarBody_Blind_X = 3;
    constexpr static float CarBody_Blind_Y = 10;
    constexpr static float CarBody_Blind_Z = 3;

    constexpr static float CarTail_Blind_X = 3;
    constexpr static float CarTail_Blind_Y = 10;
    constexpr static float CarTail_Blind_Z = 3;
    constexpr static float CarTail_Blind_Angle = 90;

    constexpr static float Detect_Range = 100;
    constexpr static float InstallAngle = 37.5;

    //UI data
    constexpr static float Part_Range = 5;
    constexpr static float Part_Num = 6;

    constexpr static float Point_X = 0;
    constexpr static float Point_Y = 0;
    constexpr static float Start_Angle = -30;
    constexpr static float End_Angle = 210;
#endif

};


#endif // CONFIGUTIL_H
