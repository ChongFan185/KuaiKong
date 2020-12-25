///

//#pragma once
#ifndef _MDOALLBS_H_
#define _MDOALLBS_H_

#include "leobase/imgbarrel.h"
#include "leobase/Matrices.h"
#include "leobase/Vectors.h"
#include "leobase/mdobject.h"

/*
 * 1.   Initial(BrpFile.brp)                ///初始化 ，同时加载BrpFile.brp 文件来初始化摄像头畸变数据
 *
 *      setChkItem(self.TUNING_ITEM_NULL)   ///设置调试选项为NULL
 *      setChkCam(0)                        ///设置调试摄像头编号0
 *
 *      loadMrgData()                       ///加载合并参数（Org长宽，Org中心点，OrgMark）
 *      loadMountData()                     ///加载摄像头参数（摄像头Position；另，Rotation无需修改）
 *      updateOrgMark()                     ///加载org参数后，更新bar mark点
 *
 *      bindCamTexture()                    ///将4个摄像头图像的纹理ID写入，以后就用这4个ID来贴图显示
 *      create()                            ///create Mesh, create Color
 *      createUv()                          ///计算 贴图 映射关系，生成UV坐标，这个函数也能同时生成显示UV的辅助 mMeshMapVb
 *      createWbrgn()                       ///计算 四路图像均衡所需的区域，这个区域的位置由 blank区域长宽决定
 *
 *
 */


class MdoAllbs
{
public:
    MdoAllbs();
    ~MdoAllbs();


    bool initial();  // 会分配mesh所需的内存空间
    void create(float blankw, float blankh);

    void insertCoord(const Vector3 &start, const Vector3 &end, int segment, Vector3* out);

    int distn;// = 5; //报警的距离

    int level;// = 6;  //报警的环数，也就是把报警距离分成几个等级
    int pixels;// = level + 1; //为了分割 n个带，需要n+1 个点

    int slice;// = 2 + 2 + 4 + 2 + 2 + 2 + 4 + 2; 
    int lines;// = slice + 1;  

    //int dotsall = (slice+1) * dotsps;

    Vector3* coord;//[lines][pixels]; 

    VertexBlock vb;
    IndexBlock ib;
};

#endif

