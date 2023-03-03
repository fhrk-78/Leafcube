// include
#include <stdio.h>
#include <string>
#include <iostream>
#include <math.h>
#include <array>

#include "macro.h"

// グローバル変数の宣言

//プロセス管理変数
std::string processName[1024];
int processAccesspermission[1024];
std::string processPublisher[1024];

//関数
int processAdd(std::string name, int permission, std::string publisher) { //プロセスの追加
    int i = 0;
    while (processName[i] != "0") {
        i += 1;
        if (i > 1024) {
            return -1;
        }
    }
    processName[i] = name;
    processAccesspermission[i] = permission;
    processPublisher[i] = publisher;
    return 0;
}

int processsPecifiedAdd(int numloc, std::string name, int permission, std::string publisher) { //プロセスの追加
    processName[numloc] = name;
    processAccesspermission[numloc] = permission;
    processPublisher[numloc] = publisher;
    return 0;
}

//処理メソッド
void initialize() { //初期化
    //グローバル変数の初期化
    for (auto i = 0; i < 1024; ++i) {
        processName[i] = "0";
    }
    for (auto i = 0; i < 1024; ++i) {
        processAccesspermission[i] = 0;
    }
    for (auto i = 0; i < 1024; ++i) {
        processPublisher[i] = "0";
    }

    //各処理をプロセスとして登録
    processsPecifiedAdd(1001, SYS_PM, PER_SYSTEM, SYS_PUB);
}

void processManager() { //ProcessManagerの処理
    return;
}

//メイン処理
int main() {
    initialize();
    return 0;
}
