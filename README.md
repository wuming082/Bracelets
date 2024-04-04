# Bracelets
## 视障者辅助穿戴设备起稿

2024/3.25/19:16log 增添UDP握手代码，进行MAC认证，为后续的设备认证配对做准备。

2024/3.25/23:26log 增添断链提醒，双端任意一方断开都可以进行重新UDP链接

2024/3.27/18:30log 增加测试客户端是否连接函数，判断客户端在情况(server) 
判断服务端是否发起测试请求并回复(client) ，配对模式(测试)记录客户端IP以及MAC地址

2024/3.28/9:49log 封装UDP认证测试包 封装超时测试连接函数

2024/3.29/21:02log <strong style="color: #DC143C">测试版本beta</strong> 封装UDP超时检测包封装类(增加两种UDP超时两种类型，直接影响系统进程方法/与其他方法搭配的超时检测方法)，封装UDP震动指令主类/UDP震动包发送方法，UDP数据包发送/接收类(可以自定义目标以及message，以及检测接受包超时报错机制)

2024/3.30/18:13log 优化检测包封装类，增加客户端根据不同数据包长度进入相应模式的函数，增加震动指令发送函数<strong>丢包率30% 待修复</strong>,优化超时检测机制<strong>BETA</strong>

2024/3.31/12:40log 优化震动指令发送函数，以及客户端接收震动函数(延迟减小到2秒之内) ,预计再次优化引入通讯协议<strong>ESP NOW</strong>来最大化减小延迟和功耗

2024/3.31/17:11log 添加ESP_NOW协议，大幅度降低延迟功耗 <strong>BETA</strong>

2024/4.2/17:17log 将espnow融合到开发版本当中，增加控制马达震动函数，以及控制震动时长最小单位

2024/4.3/22:22log <strong>增添注册设备框架，增加处理MAC数据包方法</strong>进行开头的UDP认证和链接，如果设备认证通过，才可进入相应功能环节

2024/4.4/11:43log 增加eeprom库，测试在内存当中保存MAC地址以及设备历史信息
