#include <ESP8266WiFi.h>
#include<stdio.h>
#define ssid "Texthome"//目标名称
#define password "WZP8460121"//密码
/*
测试文件2024/3.23/10:27
**********************************************************************************
dreamsky.0822.wuming
服务端调试测试am
**********************************************************************************
用于测试开发板的WIFI调试程序以及基础的框架程序测试
*/
////////////////////////////////////////////Test///////////////////
//建立服务端TCP监听接口
WiFiServer server(822);//监听接口为822
//////////////////////////////////////////////Test/////////////////
//注册WIFI连接成功事件处理程序
WiFiEventHandler STAconnect;
//注册WIFI连接断开事件处理程序
WiFiEventHandler STAdiconnect;
//服务端相应防火墙/AP点配置
IPAddress local_IP(192,168,2,1);//本身的IP地址
IPAddress getway(192,168,2,1);
IPAddress subnet(225,225,225,0);
//灯光闪烁函数(闪一次)
void lighthelper(int Num,int Sce){//Num为次数,sce为间隔时间（毫秒）
  for(int i = 0 ; i< Num ; i++){
    digitalWrite(D4,LOW);
    delay(Sce);
    digitalWrite(D4,HIGH);
    delay(Sce);
  }
}
//提示灯函数///
void lightLEDinf(int option){//传入1为正常情况快三闪，传入0为发生错误，多次慢四闪
  if(option == 1){
    lighthelper(3,100);
  }else if(option == 0){
    lighthelper(4,800);
  }
  else
    Serial.println("\nlightLEDinf(option)_err,传参错误，1为正常三闪，0为错误四闪，请查看参数是否合规");
}
//连接wifi函数
void linkserverFunction(){
  WiFi.begin(ssid,password);
  Serial.printf("\n正在连接至目标节点%s",ssid);
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.printf(".");
    //双闪表示连接
    lighthelper(2,100);
    delay(500);
  }
  Serial.printf("IP地址为：");
  Serial.println(WiFi.localIP());
}
//开启WIFI功能函数3
//APWIFI模式功能
class APWIFI{//默认情况下为隐藏式WIFI
  public :static void APopen(){//默认接入4台设备
    WiFi.softAPConfig(local_IP, getway, subnet);
    WiFi.softAP(ssid,password,1,1);//默认隐藏WIFI
  }
  public :static void APopen(int option){//设定option为0的时候为可搜索wifi
    WiFi.softAPConfig(local_IP, getway, subnet);
    WiFi.softAP(ssid,password,1,option);
  }
};
//注册网络设备接入连接事件处理程序1
WiFiEventHandler APlinkfunction;
//AP和STA模式切换函数//默认为STA模式
class switchTrans {
  //创建默认模式切换方法
  public :static void switchMode(){
    //默认开启STA模式
    WiFi.mode(WIFI_STA);
    Serial.printf("\nSTA模式\n目标WIFI名称：%s,密码：%s",ssid,password);
    ///////////////////////////////////////////////////连接wifi///////////////////////////////////////////////////////////
    linkserverFunction();
  }
  public :static void switchMode(int option){//如果option为0则为STA。 为1则为AP模式
    if(option == 0){
      WiFi.mode(WIFI_STA);
      Serial.println("\nSTA");
    }
    else if(option == 1){
      //开启AP的wifi信号//默认隐藏式网络
      APWIFI::APopen();
      WiFi.mode(WIFI_AP);
      Serial.println("\nAP(常规工作模式)");
    }
    else
      Serial.println("switchMode(option)_err，option传参错误\n0为STA，1为AP模式，请检查设置");
  }
  public :static void switchMode(int option,int optionWIFI){//如果传参为两个参数，则后面参数决定是否为隐藏式网络 optionWIFI为0是可搜索WIFI optionWIFI为1为隐藏式WIFI
    if(option == 0){
      Serial.println("\nswitchMode(option,optionWIFI)_err,option传参错误，在此函数下，模式参数必须为为1(开启AP模式)");
    }else if(option == 1){
      if(optionWIFI == 0){//开启可搜索WIFI模式
        APWIFI::APopen(optionWIFI);
        Serial.printf("\nWIFI可搜索模式已开启(调试模式)\nWIFI名称: %s 密码: %s",ssid,password);
      }else if(optionWIFI == 1){
        APWIFI::APopen(optionWIFI);
        Serial.printf("\n隐藏式网络(工作模式)\nWIFI名称: %s 密码: %s",ssid,password);
      }else
        Serial.println("switchMode(option,optionWIFI)_err,optionWIFI参数传参错误,1为隐藏式网络，0为可搜索网络，检查传参参数是否正确");
    }else{
      Serial.println("switchMode(option,optionWIFI)_err,option参数传参错误,option参数必须传参为1(开启AP模式)");
    }
  }
};

//串口程序函数4
//目标设备丢失事件处理程序（需要通过MAC地址判断是否为目标设备）

void setup() {
  pinMode(D4,OUTPUT);
  digitalWrite(D4,HIGH);
  //设定通信串口为115200
  Serial.begin(115200);
  STAconnect = WiFi.onStationModeConnected(connectHelper);//connectHelper为连接到wifi后的回调函数
  STAdiconnect = WiFi.onStationModeDisconnected(disconnectHelper);//disconnectHelper为断开WIFI后的回调函数
  APlinkfunction = WiFi.onSoftAPModeStationConnected(APlinkHelper);//APlinkHelper为有新的客户端接入后的调用函数
  //test
  //AP模式开启
  switchTrans::switchMode(1,1);
  //test
  //switchTrans::switchMode(1,1);
  //test
  
  //lightLEDinf(1);
  //delay(10000);
  //lightLEDinf(0);
  //lightLEDinf(3);
}
//报告IP函数
void IPfunction(){
  Serial.printf("\n目前ip地址为： ");
  Serial.println(WiFi.localIP());
}
void loop() {
  //////////////////////与客户端进行TCP握手连接////////////////////////////////////////
  WiFiClient client = server.available();//监听客户端连接
  if(client){//如果有客户端连接
    Serial.println("new connected!");
    String transfer = "";//接收数据包变量
    Serial.printf("h");
    if(client.available()){
      transfer = client.read();
      Serial.println(transfer);
      transfer = "";
    }
  }
}
//STA连接wifi回调函数
void connectHelper(const WiFiEventStationModeConnected &event){
  Serial.printf("\n\n已连接至 %s ！\n",ssid);
  digitalWrite(D4,HIGH);
}
//STA断开wifi回调函数
void disconnectHelper(const WiFiEventStationModeDisconnected &event){
  //报告状况
  Serial.printf("\nWIFI目前已断开！\n正在重新连接\n正在连接到%s",ssid);
  digitalWrite(D4,LOW);
  //linkserverFunction();
}
//ap模式有新的设备加入
void APlinkHelper(const WiFiEventSoftAPModeStationConnected& event){
  //报告状况
  Serial.printf("\n有设备加入！，设备的的IP地址为 ");
  Serial.println(WiFi.softAPIP());
}
