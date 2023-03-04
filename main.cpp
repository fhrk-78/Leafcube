// include
#include <stdio.h>
#include <string>
#include <iostream>
#include <math.h>
#include <array>

// グローバル変数の宣言

//初期化
bool processManagerEnable = false;
bool VFSEnable = false;
bool VFSManagerEnable = false;

//プロセス管理変数
std::string processName[512];
int processAccesspermission[512];
std::string processPublisher[512];

//VFS管理変数
std::string filePath[256];
int filePermission[256];
bool fileIsDirectory[256];
std::string fileInside[256];

//関数
int processAdd(std::string name, int permission, std::string publisher) { //プロセスの追加
    if (processManagerEnable == true) {
        int i = 0;
        while (processName[i] != "0") {
            i += 1;
            if (i > 512) {
                return -1;
            }
        }
        processName[i] = name;
        processAccesspermission[i] = permission;
        processPublisher[i] = publisher;
        return 0;
    } else {
        return -1;
    }
}

int processsPecifiedAdd(int numloc, std::string name, int permission, std::string publisher) { //プロセスの追加 (番号指定)
    if (processManagerEnable == true) {
        processName[numloc] = name;
        processAccesspermission[numloc] = permission;
        processPublisher[numloc] = publisher;
        return 0;
    } else {
        return -1;
    }
}

int processRemove(int numloc) { //プロセスの正常削除
    if (processManagerEnable == true) {
        processName[numloc] = "0";
        processAccesspermission[numloc] = 0;
        processPublisher[numloc] = "0";
        return 0;
    } else {
        return -1;
    }
}

int mkdir(std::string filename, int filepermissions) { //ディレクトリの作成
    if (VFSEnable == true && VFSManagerEnable == true) {
        int i = 0;
        while (filePath[i] != "0") {
            i += 1;
            if (i > 256) {
                return -1;
            }
        }
        filePath[i] = filename;
        filePermission[i] = filepermissions;
        fileIsDirectory[i] = true;
        fileInside[i] = "";
        return 0;
    } else {
        return -1;
    }
}

int mkfile(std::string fileDirectory, std::string filename, int filepermissions, std::string inside) { //ファイルの作成(&書き込み)
    if (VFSEnable == true && VFSManagerEnable == true) {
        int i = 0;
        while (filePath[i] != "0") {
            i += 1;
            if (i > 256) {
                return -1;
            }
        }
        filePath[i] = fileDirectory + "/" + filename;
        filePermission[i] = filepermissions;
        fileIsDirectory[i] = false;
        fileInside[i] = inside;
        while (true) {
            i += 1;
            if (i > 256) {
                return -1;
            }
            if (filePath[i] == fileDirectory && fileIsDirectory[i] == true) {
                fileInside[i] += filename + "\n";
                break;
            }
        }
        return 0;
    } else {
        return -1;
    }
}

int writefile(std::string paths, std::string inside) {
    if (VFSEnable == true && VFSManagerEnable == true) {
        int i = 0;
        while (filePath[i] != paths) {
            i += 1;
            if (i > 256) {
                return -1;
            }
        }
        fileInside[i] = inside;
        return 0;
    } else {
        return -1;
    }
}

//処理メソッド
void initialize() { //初期化
    //グローバル変数の初期化
    for (auto i = 0; i < 512; ++i) {
        processName[i] = "0";
    }
    for (auto i = 0; i < 512; ++i) {
        processAccesspermission[i] = 0;
    }
    for (auto i = 0; i < 512; ++i) {
        processPublisher[i] = "0";
    }

    for (auto i = 0; i < 256; ++i) {
        filePath[i] = "0";
    }
    for (auto i = 0; i < 256; ++i) {
        filePermission[i] = 0;
    }
    for (auto i = 0; i < 256; ++i) {
        fileIsDirectory[i] = false;
    }

    processManagerEnable = true;
    VFSEnable = true;
    VFSManagerEnable = true;

    //各処理をプロセスとして登録
    processsPecifiedAdd(501, "system/processManager", 10, "system/system_process");
    processsPecifiedAdd(502, "system/VFSManager", 10, "system/system_process");

    //システムファイルの作成
    mkdir("/system", 10);
}

void processManager() { //ProcessManagerの処理
    return;
}

void VFSManager() { //VFSManagerの処理
    return;
}

void commandLine() { //コマンド入力の待機
    std::string inputCommand = "";
    std::string nowDirectory = "/";
    while (true) {
        printf("%s", nowDirectory);
        printf(">");
        scanf("%s", &inputCommand);
        printf("\n");
    }
}

//メイン処理を実行
int main() {
    initialize();
    return 0;
}
