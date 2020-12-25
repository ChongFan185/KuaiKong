#ifndef COMMANDTDP_H
#define COMMANDTDP_H

// struct UniformType{
//     enum Enum
//     {
// //        UNINULL,
//         INT1,  // used for samplers only
//         INT1V,
//         VEC3,  // 3float vector
//         VEC4,  // 4float vector
//         MAT3,  // 3x3 matrix
//         MAT4,  // 4x4 matrix
//         Count
//     };
// };
struct TdpanoCmd{
    enum ENUM{
        NULLCMD     = 1, //不能设置为0， 这样就跟NULL冲突， 设置为一的话， 这个枚举值可以跟NULL混用。 
        DOCK        = 0x1000,
        DOCK_DIS0,   //CAM0
        DOCK_DIS1,   //CAM1
        DOCK_DIS2,   //CAM2
        DOCK_DIS3,   //CAM3

        DOCK_DIS4,   //3d
        DOCK_DIS5,   //2D
        
        DOCK_DIS6,  //MIRROR

        DOCK_DIS7,  //FRONT-3CAM
        DOCK_DIS8,  //REAR-3CAM
        DOCK_DIS9,  //3D-FULL
        DOCK_DIS10, //MIRROR-FULL

        DOCK_DIS11, //FRONT-2CAM
        DOCK_DIS12, //REAR-2CAM

        DOCK_SYSRETURN,
        DOCK_SETTING    = 0x1100,
        
        P2_SET0 = 0x1200,
        P2_SET1,
        P2_SET2,
        P2_SET3,
        P2_RETURN,
        P2_VIEWPOINT0,
        P2_VIEWPOINT1,
        P2_VIEWPOINT2,
        P2_VIEWPOINT3,



        TUNE        = 0x2000,
        TUNE_CAM0,
        TUNE_CAM1,
        TUNE_CAM2,
        TUNE_CAM3,
        TUNE_ITEMNULL,
        TUNE_ITEMCENTER,
        TUNE_ITEMMARK,
        TUNE_ITEMCAMPOS,
        TUNE_ITEMCAMROT,
        TUNE_ITEMBLANKSIZE,
        TUNE_NEXTMARK,
        TUNE_NEXTCAM,
        TUNE_NEXTITEM,
        TUNE_DENSE,

        TUNE_XP,
        TUNE_XN,
        TUNE_YP,
        TUNE_YN,
        TUNE_ZP,
        TUNE_ZN,
        TUNE_SAVE,
        TUNE_LOAD,
        TUNE_RSV1,
        TUNE_RETURN,
        TUNE_CHANGEDIS,
        TUNE_NOOPER,
        TUNE_DONE,

        TUNE_WP3,
        TUNE_WP2,
        TUNE_WP1,
        TUNE_WP0,
        TUNE_HP3,
        TUNE_HP2,
        TUNE_HP1,
        TUNE_HP0,

        TUNE_MKWP3,
        TUNE_MKWP2,
        TUNE_MKWP1,
        TUNE_MKWP0,
        TUNE_MKHP3,
        TUNE_MKHP2,
        TUNE_MKHP1,
        TUNE_MKHP0,

        TUNE_RDP,
        TUNE_RDN,

        AUTO_DO,
        AUTO_SAVE,
        AUTO_RETURN,

        CONF_ORG_BUTTON_ON = 0x3001,
        CONF_ORG_BUTTON_OFF = 0x3002,
        CONF_3D_BUTTON_ON  = 0x3003,
        CONF_3D_BUTTON_OFF = 0x3004,
        CONF_MIRROR_BUTTON_ON = 0x3005,
        CONF_MIRROR_BUTTON_OFF = 0x3006,
        CONF_UI_ON    = 0x3007,
        CONF_UI_OFF    = 0x3008,
        CONF_SLIDE_MIRROR_ON = 0x3009,
        CONF_SLIDE_MIRROR_OFF = 0x3010,
        CONF_LINE_TRAIL_ON = 0x3011,
        CONF_LINE_TRAIL_OFF = 0x3012,
        CONF_LINE_REAR_ON = 0x3013,
        CONF_LINE_REAR_OFF = 0x3014,
        CONF_LINE_RADAR_ON = 0x3015,
        CONF_LINE_RADAR_OFF = 0x3016
    };
};
#endif // COMMANDTDP_H
