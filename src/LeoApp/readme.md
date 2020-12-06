#### pro

工程目录中有数个pro，请使用  tdpanovs-8m.pro





### 接口说明



main -- opengwidget--render

360全景的画图代码都在 render 中， openglwidget 初始化了 render对象， 然后 持续 通过 update（**）刷新图像数据就能显示连续画面。



upate有两种接口

```
mrender.update(capI420.data, 1920, 1080, sa_angle);
输入4个图像是拼接在一个buf中，以2x2的方式分割画面，通过一个 buf 就把4个画面输入了， 后面的数字是 4个画面总共的宽高

mrender.update(capIm0.data, capIm0.data, capIm1.data, capIm1.data,1280, 720, sa_angle);
输入4个图像是分开的，通过4个 buf 把4个画面输入， 后面的数字是 单个画面总共的宽高

这两种输入方式，都要求 输入图像格式是 I420
(注：I420，比如图像是 宽640，高480， 那么 图像数据总长是 640*480*1.5 ，  其中 Y数据为640*480， U数据为320*240， V数据为320*240， Y,U,V 连续存放，且不交织)

因此前端 采集图像设备要确保 update前的图像已经 转换为 I420 格式。
```



###main( ) 几个地方：

main中设置 4个 rtsp流的地址（测试代码只试过两路）



### openglwidget代码中的 readframe（）

readframe( )中 通过 cap* >> capIm* ; 获得图像数据，确保 rtsp 管道中已经将数据转为 I420了。 我现在测试 用的 imx8m-mini 没有 IPU跟，只有G2D，不支持 I420，因此 抓到图像后 软件转了一下。

测试过程中， 可以 一路 两路 四路 依次测试。 在 update( ) 函数中， 4个buf可以输入同样的 内容，运行不会有问题，是指 画面重复而已。



#### render的几个设置

    mrender.ctrl.enButton =true;  //开关按键，如果 UI另外设计了，可以关闭 render 的 UI
    mrender.ctrl.enAllbs = true;  //这个是一个 render中实现的 盲区报警 的代码， 还未实现完成
    mrender.ctrl.enAvm2d = true;  //这个可以打开关闭 右侧的 图像，关闭后 后侧可以用来 放其他UI
