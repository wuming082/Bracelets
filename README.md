# Bracelets
##视障者辅助穿戴设备起稿

2024/3.25/19:16log 增添UDP握手代码，进行MAC认证，为后续的设备认证配对做准备。

2024/3.25/23:26log 增添断链提醒，双端任意一方断开都可以进行重新UDP链接

2024/3.27/18:30log 增加测试客户端是否连接函数，判断客户端在情况(server) 
判断服务端是否发起测试请求并回复(client) ，配对模式(测试)记录客户端IP以及MAC地址

2024/3.28/9:49log 封装UDP认证测试包 封装超时测试连接函数

2024/3.29/21:02log <strong style="color: #DC143C">测试</strong> 封装UDP超时检测包封装类(增加两种UDP超时两种类型，直接影响系统进程方法/与其他方法搭配的超时检测方法)，封装UDP震动指令主类/UDP震动包发送方法，UDP数据包发送/接收类(可以自定义目标以及message，以及检测接受包超时报错机制)
