# TrackingCar
大家好，我是黄一

话不多说，先上图。

![image](https://raw.githubusercontent.com/Alexhuge1/TrackingCar/main/%E6%9C%BA%E6%A2%B0/%E5%AE%9E%E7%89%A9%E5%9B%BE%E7%89%87/IMG_20230423_152139.jpg)

比赛规则，沿着赛道循迹一圈冲过终点，其中道路有障碍物要做一定量的减震，并且要与树莓派通信实现识别红绿灯并在主板上点亮相对应的灯。

硬件方面：小车电流较小并且为了走线方便，采用将主控与电机驱动放一块板子上的方式，小车使用了STM32F103RCT6作为主控，A4950做电机驱动芯片，树莓派4B做视觉识别，MP2482转压芯片做12V转5V，AMS1117-3.3转压芯片做5V转3.3V，并加了一个急停开关便于调试

![image](https://raw.githubusercontent.com/Alexhuge1/TrackingCar/main/%E7%A1%AC%E4%BB%B6/IMG_20230420_205946.jpg)

机械方面：亚克力作为中间支撑，四周采用滑块做悬挂，并且训练使用麦克纳姆轮（其实没有必要，这次只用了差速转向）

![image](https://raw.githubusercontent.com/Alexhuge1/TrackingCar/blob/main/%E6%9C%BA%E6%A2%B0/1.24.jpg)

电控方面：对于循迹传感器做逻辑判断，并且使用双路PWM输出控制电机

视觉方面：采用了树莓派做边缘计算载体，调用opencv库识别红绿灯并且对环境光进行过滤

小车制作：机械主要靠3D打印和亚克力切割，电路板自行焊接，所有配件都基本为标准件，淘宝可以买到滑轨和联轴器麦轮这类。
