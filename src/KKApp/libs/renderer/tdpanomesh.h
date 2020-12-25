///

//#pragma once
#ifndef _TDPANOVS_H_
#define _TDPANOVS_H_

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


class ModelAvmesh
{
public:
    ModelAvmesh();
    ~ModelAvmesh();

    void defaultParam();

    bool updateAll();
    void updateMesh();
    void updateUv();

    ///
    /// \brief initial
    /// 为VB,IB分配内存
    ///
    bool initial();  // 会分配mesh所需的内存空间
    ///
    /// \brief createMesh ：Create 全景网格，和网格颜色
    /// 计算并生成网格，网格颜色
    ///
    void createMesh();
    ///
    /// \brief createUv： Create 4个摄像头的 贴图 UV
    /// 计算拼接关系，生成贴图UV
    ///
    void createUv();

    /// 根据当前的映射关系。
    /// 生成标准化的 markMdlBuf 点， 并计算出对应的 markOrgManual 点，用于手动调整使用。
    void recreateUvLever();
    ///
    ///
    /// \brief 创建白平衡区域的统计范围，外部需要根据这个范围去统计 org图像的 Y， r，g，b 均值，用以实现亮度和色彩均衡
    void createWbRegion();
    ///
    /// \brief createMesh： Create 全景网格， V3，矩形，椭圆模型均可实现，模型完全参数化
    ///
    void createMeshVtx();
    ///
    /// \brief createColor： Create 网格交叉处的透明度颜色，V3
    ///@ 目前的cornor slice 为8个，
    /// 函数里边暂时假设需要模糊融合的区域为4个，且这4个区域，从前后方看，尽量靠外
    /// 所以这样的话，cornor区域的9个vertex，的透明度就是
    /// Front (vtx0-vtx9) = 0  , 64,128,172,255,255,255,255,255
    /// Left  (vtx0-vtx9) = 255,171,127, 63,  0,  0,  0,  0,  0
    /// 如果融合区域的宽度需要修改，则这些值需要手工调整
    void createMeshColor();
    ///
    /// \brief bindCamTexture：将外部采集到的图像的纹理ID告诉3D对象
    ///
    void setCamTexture(GLuint cam0, GLuint cam1, GLuint cam2, GLuint cam3);
    ///
    /// \brief createOrgVbIb： Create用户绘制Org图像的VB,每次切换显示的Org图就需要更新，范围（0,0）～（mOrgw，mOrgH)
    /// \param camid
    /// \Param bRotate: 用来确定图像是否需要旋转到车头方向，如果 bRotate，则图像不旋转，保持原始图像
    void createOrgVbIb(int camid, bool bRotate = false);
    ///
    /// \brief createMarkVb： Create用户绘制Mark点调教的标记点，每次Mark点调整之后都需要更新, 范围（0,0）～（mOrgw，mOrgH)
    /// \param camid
    ///
    void createMarkVbIb(int camid);
    void createMarkCrossVbIb(int camid);
    ///
    /// \brief createCenterVb：Create用户绘制中心点调教的标记点，每次中心点调整之后都需要更新, 值范围（0,0）～（mOrgw，mOrgH)
    /// \param camid
    ///
    void createCenterTemplate();
    bool createCenterVbIb(int camid);

    void createBiaochi();



    void setOrgCenter(int camid, float x, float y);
//    void setOrgMark(int camid, ARR4V2 quadliter);
    void setOrgMark(int camid, const Vector2& vct0, const Vector2& vct1, const Vector2& vct2, const Vector2& vct3);
	void setCamPos(int camid, float x, float y, float z);
	void setCamRot(int camid, float x, float y, float z);
    void clampCamPos(int camid);

    ARR4V2 getOrgMark(int camid);

//    void setMarkCloth(int camid, ARR4V2 quadliter);
    void setMarkCloth(int camid, Vector3 vct0, Vector3 vct1, Vector3 vct2, Vector3 vct3);
//    void setMarkSize(int camid, Vector2 size);
//    void setMarkHand(int camid, ARR4V2 quali);
    void setMdlMark(int camid, const Vector3& vct0, const Vector3& vct1, const Vector3& vct2, const Vector3& vct3, const Vector3& offset=Vector3(0.0,0.0,0.0));

    void calcHandMark(float extension); //4个角摆放方块的mark点坐标
    void calcHandMark1(int camid); //长条布产生的mark点坐标
    void calcHandMark1(int camid, Vector2 size);
    void calcAutoMark();
    void copyMdlMark();
    ///
    /// \brief calcBarMark: 从Org Mark点坐标，Org center点，Brp参数，计算出Bar图 Mark点坐标
    ///
    void calcBarMark(int camid);
    //	void setMdlMarkV1();

    void getWbRegion(int camid, int which, ARR4V2& quali);
    ///
    /// \brief setBlankRegion: 设置地板黑色区域的长宽
    /// \param width
    /// \param height
    ///
    void setMeshBlank(float width, float height);
    void setMeshDense(int wslice, int hslice, int cslice, int nearrings, int farrings);
    void setMeshSize(float distance, float high);
    void setMeshAngle(float wangle, float hangle);

	//----adj----
	void adjOrgCenter(int camid, int direction, float delt);
	void adjOrgMark(int camid, int item, int direction, float delt);
	void adjCamPos(int camid, int direction, float delt);
	void adjCamRot(int camid, int direction, float delt);
	void adjMdlMark();
    void adjBlankRegion(int direction, float delt);
    void adjMarkSize(int camid, int direction, float delt);
    void adjValue(int pname, int camid, int markid, int direction);
	void adjValue(int direction);

    void adjTuneDense();

	//----save&load----
    bool saveScamData(const char* filename);
    bool loadScamData(const char* filename);
    bool saveMergerData(const char* filename);
    bool loadMergerData(const char* filename);
    bool loadAutoMergerData(const char* filename);
    bool saveMountData(const char* filename);
    bool loadMountData(const char* filename);
    bool loadBrp(const char* filename);

	//----Control--------
	void setChkItem(int item);
	void setChkCam(int cam);
	void setChkMark(int mark);

	void nextChkItem();
	void nextChkCam();
	void nextChkMark();

    //------get------------
	int getChkItem();
	int getChkCam();
	int getChkMark();

	float getBlankWidth();
	float getBlankHeight();

	void changeDis();

private:
    /// 计算单摄像头的模型师徒投影矩阵
    void calcCamMvp(int camid);
    /// 计算透视变换参数（8个参数，实际上也是一个3X3 的矩阵
    /// 1. 通过 MDL坐标的 Mark点位置，得到 CAM坐标下的 Mark点位置
    /// 2. 通过 CAM坐标下的Mark点位置 ，跟 Bar图的Mark点位置，来计算透视变换矩阵（这个矩阵完成的是点匹配的工作）
    void calcCamProjection(int camid);

//	//以下6个函数，是第二版模型，也就是使用单一的全局数组时，计算纹理坐标的函数，后续应该用不到了，第二版模型是直接生成顺序坐标地址
//	void vtxMdlToCvp(GLfloat *vtxin, GLfloat *vtxout, int vtxnum, Matrix4 *aCvpMat);
//	void vtxCvpToBar(GLfloat *vtxin, GLfloat *vtxout, int vtxnum, ProjectConverter *ProjPara);
//	void vtxMirOrgToOrg(GLfloat *vtxin, GLfloat *vtxout, int vtxnum);
//  void vtxBarToOrg(GLfloat *vtxin, GLfloat *vtxout, int vtxnum);
//	void vtxBarToNormOrg(GLfloat *vtxin, GLfloat *vtxout, int vtxnum);
//	void vtxTransBatch(int startstrip, int stripcnt, int camid);

	//以下6个函数，是第三版模型计算纹理坐标的函数，第三版不再使用顺序的坐标，而是使用索引数组，并且用Vector3替代了GLfloat
    void vctMdlToCvp(Vector3* vtxin, Vector3* vtxout, int vtxnum, Matrix4 *aCvpMat);
    void vctCvpToBar(Vector3* vtxin, Vector3* vtxout, int vtxnum, ProjectConverter *ProjPara);
    void vctOrgMirrorY(Vector3* vtxin, Vector3* vtxout, int vtxnum);
    void vctBarToOrg(Vector3* vtxin, Vector3* vtxout, int vtxnum);
    void vctMdlToOrg(Vector3* vtxin, int vtxnum, int camid);

    void vctMdlToOrgFast(Vector3* vtxin, Vector3* vtxout, int vtxnum, int camid);
    void vctMdlToOrgFast(Vector3* vtxin, Vector2* vtxout, int vtxnum, int camid);
    void vctMdlToOrgFast(Vector3* vtxin, int vtxnum, int camid);


	Vector2 orgMarkRotate(Vector2 s, int camid);  //camid =0,1,2,3分别对应旋转0,180,90,270度，也就是4个摄像头对应的方向

public:
    /// 使用adj函数时，可以通过设置 mChkItem 变量，来设置当前是对哪项内容进行调整，可以使用的值如下
    const int TUNING_ITEM_NULL = 0;
    const int TUNING_ITEM_CAMPOS = 1;
    const int TUNING_ITEM_CAMROT = 2;
    const int TUNING_ITEM_MARK = 3;
    const int TUNING_ITEM_CENTER = 4;
    const int TUNING_ITEM_BLANK = 5;

private:
    ///	需要外部传递值进行修改的部分
    int mChkItem;   //当前检测微调的项目名称
    int mChkCam;	//当前需要检测微调的摄像头IDs
	int mChkMark;	//当前需要检测微调的Mark ID（Org Mark项目）
    int mEnableGrid;
    bool mTuneDensity = false;

    unsigned int TCOLOR_BLUE = (255<<24) + (192<<16) + (64<<8) + 64;
    unsigned int TCOLOR_RED = (255<<24) + (64<<16) + (64<<8) + 192;
    unsigned int TCOLOR_GRAY = (255<<24) + (192<<16) + (192<<8) + 192;

    struct{
        int w;
        int h;
    }orgPara;

    //这个参数应该没有用了
    //GLuint mTextureId[4];
public:
    ///
    /// \brief The Anonymous:1 struct
    /// 用来计算摄像头纹理映射的数据
	struct{
        Vector3 CamPosCenter;
        Vector3 CamPos; //摄像头的安装位置
        Vector3 CamPosMin;
        Vector3 CamPosMax;
        Vector3 CamRot; //摄像头的安装角度，经过测试确认，原始摄像头的安装角度不会影响图像效果，因为摄像头的
		//旋转只会产生透视变化，而在摄像头mark点跟Bar图Mark点匹配的过程中
		//使用的是透视变化，这个透视变化就会隐含的消除摄像头的角度内参。
        Vector2	OrgCenter; //org图 中心点
        float OrgRadium;   //org图 半径（之所以设置这个值，完全是因为摄像头存在生产误差）

        Vector2 markSize;  //单目全景使用的参数， 用来标志拼接布尺寸
        ARR4V2 markOrg;    //org图,4个Mark点的坐标
        ARR4V2 markBar;    //bar图,4个Mark点的坐标
        //ARR4V2 markNormBar;//bar图，归一化的4个Mark点坐标
        ARR4V2 markCam;    //cam视角，4个Mark点的坐标
        ARR4V3 markMdl;    //mdl世界，4个Mark点的坐标

        ////org2bar，bar2org 是索引表 计算的，本质上有误差，数值 不可逆。 实际测量中，发现通过 org-mdl-org 存在接近 10pixels的误差。
        /// 因此，还是使用 原始识别的点（或手动，或自动）来进行 微调比较靠谱。
//        ARR4V2 markOrgManual;   //手动标定的标定点 markOrg
        ARR4V3 markMdlBuf;   //手动标定的标定点 markMdl ，这个mark点是固定的，便于 手动调整的位置

//        ARR4V3 markMdlAuto;     //自动标定的标定点摆放依赖画布图案

        //不需要外部传递值的部分
        Matrix4 MdlMvp;   //计算出来的mdl转cam的透视矩阵
        ProjectConverter	CamPara;//计算出来的cam转bar的透视矩阵

    }mrgr[4];//0~3 4个单路的摄像头

    struct{ // 四边形按照 zigzag 顺序保存
        //Below parameter were added to implement whitebalance.
        ARR4V2 rgn0Org;    //wbrgn0 Org图中左侧的方形融合区域
//        ARR4V2 rgn0Bar;
//        ARR4V2 rgn0Cam;
        ARR4V3 rgn0Mdl;

        ARR4V2 rgn1Org;   //wbrgn1 Org图中右侧的方形融合区域
//        ARR4V2 rgn1Bar;
//        ARR4V2 rgn1Cam;
        ARR4V3 rgn1Mdl;

    }camwb[4];
public:
    ///
    /// \brief The VsParameter struct
    /// 用来存储生成网格的参数
    struct {
        int W_SLICES;	// 车辆宽度方向，网格分割的片数
        int H_SLICES;	// 车辆长度方向，网格分割的片数
        int C_SLICES;	// 车辆4个角，网格分割的片数

        int N_RINGS;	// Near Rings 近处平面部分，网格分割的环数,
        int F_RINGS;	// Far Rings 远处上升部分网格分割的环数

        int W_VTS; // W_SLICES + 1
        int H_VTS; // H_SLICES + 1
        int C_VTS; // C_SLICES + 1
        int E_VTS; // Extension Vertices , NR+FR+1

        float HEIGHT;  // 模型边沿的高度
        float DIS;     // 模型边沿离车身的距离， 椭圆的长半径 =(DIS+H/2), 短半径 =(DIS+W/2)

		float RectWiAlf;
		float RectCoAlf;

        float W_ANGLE;  // 车辆宽度方向占用的角度
        float H_ANGLE;  // 车辆长度方向占用的角度
        float C_ANGLE;  // 车辆4个角占用的角度， 这三个角度之和为90度

        float W_BLANK;  // 车辆阴影宽度， 目前是默认等于车宽，实际上这两个参数不用保持一致
        float H_BLANK;  // 车辆阴影长度， 目前是默认等于车长，实际上这两个参数不用保持一致
    } meshPara;

public:

    Vector3 biaochi[24];
    VertexBlock vtxBiaochi;
    IndexBlock idxBiaochi;

    /// 保存摄像头畸变参数的类。
	BarrelConverter brp;
    Vector3 circle[146];
    bool centerTemplateOk = false;
    /// temple VB and IB for center tuning
    /// 圆环+中心点三角的 VB，IB，用来辅助微调中心点，中心点位置是旋转过的。
    VertexBlock tVbCircle;
    IndexBlock tIbCircle;

    /// temple VB and IB for Orignal Picture display
    /// 临时的VB，IB数据，用来绘制原始图像
    /// 一共4组
    /// 第一组 1/4 贴纸， 不变方向
    /// 第二组 1/4 贴纸， 后方镜像
    /// 第三组 1/4 贴纸， 左右后旋转或镜像
    /// 第四组 全幅贴纸
    const int VB_ORG_CNT = 16;
    VertexBlock tVbOrg[16];
    IndexBlock tIbOrg;

    ///temple VB and IB for Mark Point tuning
    /// 临时的VB，IB用来绘制 Mark标记点
    VertexBlock tVbMark;
    IndexBlock tIbMark;

    VertexBlock tVbMarkCross;
    IndexBlock tIbMarkCross;

    ///mMeshVb，是生成的网格数组，分别对应4个方向的4个扇形曲面，每个扇形曲面对应一个摄像头的拍摄范围
    /// mMeshMapVb, 是mMeshVb的 UV 坐标，作为Positon 生成的VB数据，这样，绘制 mMeshMapVb，就会显示出 mMeshVb 中 UV在纹理中的映射位置
    /// mMeshIb，上面两个VB都使用 mMeshIb来索引。
    VertexBlock* vtxblk[4];
    VertexBlock* vtxmapblk[4];
    IndexBlock*  idxblk[4];

    /// 这三组指针跟上边的三个指针数组是别名关系，以便于用数组和名字分别进行访问
    IndexBlock  *idxFront,    *idxBack,    *idxLeft,    *idxRight;
    VertexBlock *vtxMapFront, *vtxMapBack, *vtxMapLeft, *vtxMapRight;
    VertexBlock *vtxFront,    *vtxBack,    *vtxLeft,    *vtxRight;

};

void splite(std::string& line, std::vector<std::string> &words);

#endif

