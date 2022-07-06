#include <iostream>
#include <string>
#include <cstdio>
#include <vector>
#include <regex>

//ʵ�������ŵ��ۣ������Ҳ�Ǹ��ֿ��ơ����İɣ�Ҳ����ͣ�������ְɡ�дһ�´���
//Version 1.0_220705
//�Զ�ж�ذ�׿�ֻ�Ӧ�û������ĵ�����ѡ��
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
    cout << "ϵͳ���ڼ���豸����״̬....." << endl;
    if (!Test_adb()) {
        cout << "û�з��ֿ��õ��豸,��ȷ����װ�������ߴ򿪿�����ģʽ������" << endl;
        system("pause");
        Run();
    }
    cout << "�ѳɹ����ӵ��豸,����ֻ���Ӧ�����ϵͳ���ý���." << endl;
    cout << "---һ��Ҫͣ���ڵ�ǰ�����ϵͳ���ý���,��ò�ҪϢ��,������ֵ����鷢��." << endl;
    string input_num;
    for (;;) {
        cout << "##########################################################" << endl;
        cout << "## 0. �鿴�Ѿ���װ�����" << endl;
        cout << "## 1. ��ѯ��ǰ�ֻ��򿪵����" << endl;
        cout << "## 2. ж�ص�ǰ�ֻ��򿪵����,����״̬���п����޷���ȡ����,���޷�ж��" << endl;
        cout << "## 99. �˳����" << endl;
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
        cout << "## By: �ܲ��ܿɰ�" << endl;
        cout << "## Version: V1.0_220705" << endl;
        cout << "## �н�������������΢�����:zhangch_" << endl;
        cout << "## ���˼�ְ����,�����Ҫ���ƻ�����Ҫ���๦��." << endl;
        cout << "## ��ϵ��΢��:zhangch_" << endl;
        cout << "##########################################################" << endl;
        cout << "�������Ӧ���:";
        cin >> input_num;
        if (input_num == "99") {
            exit(0);
        } else if (input_num == "0") {
            for (const auto& i: command("adb shell pm list packages")) {
                cout << i << endl;
            }
            system("pause");
        } else if (input_num == "1") {
            cout << "������: " << App_Name() << endl;
            cout << "�������״̬���п��ܻ�ȡ���ǿհ�" << endl;
            system("pause");
        } else if (input_num == "2") {
            cout << "����ж��: " << App_Name() << endl;
            cout << "������Ϊrootԭ��,��������������޷�ж��,����'y'ȷ��,'n'ȡ��:";
            cin >> input_num;
            if (input_num == "y") {
                string remove = "adb shell pm uninstall --user 0 " + App_Name();
                char *c = (char*) remove.data();
                command(c);
                cout << "ж�����" << endl;
                system("pause");
            } else if (input_num == "n") {
                cout << "ȡ��ж�ط����ϲ�˵�" << endl;
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
