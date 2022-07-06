#include <iostream>
#include <string>
#include <cstdio>
#include <vector>
#include <regex>

//实在是闲着蛋疼，最近我也是各种苦闷。无聊吧，也不能停，动动手吧。写一下代码
//Version 1.0_220705
//自动卸载安卓手机应用或者无聊的设置选项
using namespace std;
vector<string> tmp;
vector<string> command(const char *cmd) {
    FILE *fp;
    vector<string> vc;
    char buf[1024];
    fp = popen(cmd, "r");
    while (feof(fp) == 0) {
        fgets(buf, sizeof(buf), fp);
        vc.emplace_back(buf);
    }
    return vc;
}

bool Test_adb() {
    vector<string> adb = command("adb devices");
    if (adb.size() == 4) {
        return true;
    } else {
        return false;
    }
}

string App_Name() {
    tmp.clear();
    tmp = command("adb shell dumpsys activity activities");
    int num = 0;
    string name;
    for (const string& str: tmp) {
        if (num == 6) {
            name = str;
            break;
        }
        num = num + 1;
    }
    smatch res;
    regex pattern("u0 (.*)/");
    regex_search(name,res, pattern);
    return res[1].str();
}

void Run(){
    cout << "系统正在检测设备连接状态....." << endl;
    if (!Test_adb()) {
        cout << "没有发现可用的设备,请确定安装驱动或者打开开发者模式后再试" << endl;
        system("pause");
        Run();
    }
    cout << "已成功连接到设备,请打开手机相应软件或系统设置界面." << endl;
    cout << "---一定要停留在当前软件或系统设置界面,最好不要息屏,避免奇怪的事情发生." << endl;
    string input_num;
    for (;;) {
        cout << "##########################################################" << endl;
        cout << "## 0. 查看已经安装的软件" << endl;
        cout << "## 1. 查询当前手机打开的软件" << endl;
        cout << "## 2. 卸载当前手机打开的软件,锁屏状态下有可能无法获取包名,而无法卸载" << endl;
        cout << "## 99. 退出软件" << endl;
        cout << "##" << endl;
        cout << "##" << endl;
        cout << "##" << endl;
        cout << "##" << endl;
        cout << "##" << endl;
        cout << "##" << endl;
        cout << "##" << endl;
        cout << "##" << endl;
        cout << "##" << endl;
        cout << "##" << endl;
        cout << "##" << endl;
        cout << "##" << endl;
        cout << "##" << endl;
        cout << "## By: 萝卜很可爱" << endl;
        cout << "## Version: V1.0_220705" << endl;
        cout << "## 有建议或商务合作请微信添加:zhangch_" << endl;
        cout << "## 本人兼职开发,如果需要定制或者需要更多功能." << endl;
        cout << "## 联系我微信:zhangch_" << endl;
        cout << "##########################################################" << endl;
        cout << "输入相对应序号:";
        cin >> input_num;
        if (input_num == "99") {
            exit(0);
        } else if (input_num == "0") {
            for (const auto& i: command("adb shell pm list packages")) {
                cout << i << endl;
            }
            system("pause");
        } else if (input_num == "1") {
            cout << "包名是: " << App_Name() << endl;
            cout << "如果锁屏状态下有可能获取的是空白" << endl;
            system("pause");
        } else if (input_num == "2") {
            cout << "即将卸载: " << App_Name() << endl;
            cout << "可能因为root原因,部分软件或设置无法卸载,输入'y'确定,'n'取消:";
            cin >> input_num;
            if (input_num == "y") {
                string remove = "adb shell pm uninstall --user 0 " + App_Name();
                char *c = (char*) remove.data();
                command(c);
                cout << "卸载完成" << endl;
                system("pause");
            } else if (input_num == "n") {
                cout << "取消卸载返回上层菜单" << endl;
                system("pause");
                Run();
            }
        }
    }
}

int main() {
    system("title Android_App_Remove");
    Run();
}
