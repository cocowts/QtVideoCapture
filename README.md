> 最近需要使用opencv，就简单写了一个测试示例并记录下来。
> 其中 QCamera 等相关的类同样可以实现当前功能。

![界面展示.png](/img/bVcO5ON)

![image.png](/img/bVcO5Xq)


[仓库](https://github.com/cocowts/QtVideoCapture)

### 功能
* 支持有线或IP摄像头连接
* 支持视频流播放
* 支持多分辨率设置
* 支持视频录制
* 支持拍照
* 视频抽帧、拍照、录制等由独单线程处理
---

测试可用的视频流
```
CCTV1  高清 http://ivi.bupt.edu.cn/hls/cctv1hd.m3u8
CCTV3  高清 http://ivi.bupt.edu.cn/hls/cctv3hd.m3u8
CCTV5+ 高清 http://ivi.bupt.edu.cn/hls/cctv5phd.m3u8
CCTV6  高清 http://ivi.bupt.edu.cn/hls/cctv6hd.m3u8
```
