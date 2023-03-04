/*

こんなに汚いソースコードは初めて見たでしょう

*/

// include
#include <stdio.h>
#include <string>
#include <iostream>
#include <math.h>
#include <array>
#include <future>

// マクロ

//定数
#define PROCESS_MAX 256
#define FILE_MAX 512

//関数
#define STRCHR(x) x.c_str()

// グローバル変数の宣言

//初期化
bool processManagerEnable = false;
bool VFSEnable = false;
bool VFSManagerEnable = false;

//プロセス管理変数
std::string processName[PROCESS_MAX];
int processAccesspermission[PROCESS_MAX];
std::string processPublisher[PROCESS_MAX];

//VFS管理変数
std::string filePath[FILE_MAX];
int filePermission[FILE_MAX];
bool fileIsDirectory[FILE_MAX];
std::string fileInside[FILE_MAX];

// 関数
int processAdd(std::string name, int permission, std::string publisher) { //プロセスの追加
    if (processManagerEnable == true) {
        int i = 0;
        while (processName[i] != "0") {
            i += 1;
            if (i > PROCESS_MAX) {
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
            if (i > FILE_MAX) {
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
            if (i > FILE_MAX) {
                return -1;
            }
        }
        filePath[i] = fileDirectory + "/" + filename;
        filePermission[i] = filepermissions;
        fileIsDirectory[i] = false;
        fileInside[i] = inside;
        while (true) {
            i += 1;
            if (i > FILE_MAX) {
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
            if (i > FILE_MAX) {
                return -1;
            }
        }
        fileInside[i] = inside;
        return 0;
    } else {
        return -1;
    }
}

// 処理メソッド
void initialize() { //初期化
    //グローバル変数の初期化
    for (auto i = 0; i < PROCESS_MAX; ++i) {
        processName[i] = "0";
    }
    for (auto i = 0; i < PROCESS_MAX; ++i) {
        processAccesspermission[i] = 0;
    }
    for (auto i = 0; i < PROCESS_MAX; ++i) {
        processPublisher[i] = "0";
    }

    for (auto i = 0; i < FILE_MAX; ++i) {
        filePath[i] = "0";
    }
    for (auto i = 0; i < FILE_MAX; ++i) {
        filePermission[i] = 0;
    }
    for (auto i = 0; i < FILE_MAX; ++i) {
        fileIsDirectory[i] = false;
    }

    processManagerEnable = true;
    VFSEnable = true;
    VFSManagerEnable = true;

    //各処理をプロセスとして登録 100番台はシステムに予約されています
    processsPecifiedAdd(101, "system/processManager", 10, "system/system_process");
    processsPecifiedAdd(102, "system/VFSManager", 10, "system/system_process");

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
    std::string inputCommandOption = "";
    std::string nowDirectory = "/";
    int cmdNum = 0;
    while (true) {
        std::cout << nowDirectory << ">";
        scanf("%s %s", &inputCommand, &inputCommandOption);

        if (inputCommand == "pst") {
            cmdNum = 1;
        }
        if (inputCommand == "ps") {
            cmdNum = 2;
        }
        if (inputCommand == "pkill") {
            cmdNum = 3;
        }
        if (inputCommand == "padd") {
            cmdNum = 4;
        }
        if (inputCommand == "pperu") {
            cmdNum = 5;
        }
        if (inputCommand == "pperd") {
            cmdNum = 6;
        }

        switch(cmdNum) {
            case 1:
                if (processManagerEnable == true) {
                    std::cout << "ProcessTable:" << std::endl;
                    for (auto i = 0; i < PROCESS_MAX; ++i) {
                        if (processName[i] != "0") {
                            std::cout << STRCHR(processName[i]) << "(" << i << ") : " << STRCHR(processPublisher[i]) << " | " << processAccesspermission[i] << std::endl;
                        }
                    }
                } else {
                    std::cout << "\033[31;100m E: ProcessManager isn't Enable. \033[m" << std::endl;
                }
                break;
            case 2:
                if (inputCommandOption == "-s") {
                    if (processManagerEnable == true) {
                        processManagerEnable = false;
                    } else {
                        processManagerEnable = true;
                    }
                    std::cout << "Switch successful\n" << "\"ps\" to check status" << std::endl;
                } else {
                    std::cout << "ProcessManager: " << (processManagerEnable ? "Enabled" : "Disabled") << std::endl;
                }
                break;
            case 3:
                if (processManagerEnable == true) {
                    processRemove(std::stoi(inputCommandOption));
                    std::cout << "Process kill successful\n" << "\"pst\" to check all process" << std::endl;
                } else {
                    std::cout << "\033[31;100m E: ProcessManager isn't Enable. \033[m" << std::endl;
                }
                break;
            case 4:
                if (processManagerEnable == true) {
                    processAdd(inputCommandOption, 5, "user/");
                    std::cout << "Process add successful (Permission: \"5\", Publisher: \"user/\")\n" << "\"pst\" to check all process" << std::endl;
                } else {
                    std::cout << "\033[31;100m E: ProcessManager isn't Enable. \033[m" << std::endl;
                }
            case 5:
                if (processManagerEnable == true) {
                    if (processAccesspermission[std::stoi(inputCommandOption)] >= 10) {
                        std::cout << "\033[31;100m E: Permissions are already maxed \033[m" << std::endl;
                    } else {
                        processAccesspermission[std::stoi(inputCommandOption)] += 1;
                        std::cout << "Process permission upgrade successful\n" << "\"pst\" to check all process" << std::endl;
                    }
                } else {
                    std::cout << "\033[31;100m E: ProcessManager isn't Enable. \033[m" << std::endl;
                }
            case 6:
                if (processManagerEnable == true) {
                    if (processAccesspermission[std::stoi(inputCommandOption)] >= 10) {
                        std::cout << "\033[31;100m E: Permissions are already minimaled \033[m" << std::endl;
                    } else {
                        processAccesspermission[std::stoi(inputCommandOption)] -= 1;
                        std::cout << "Process permission downgrade successful\n" << "\"pst\" to check all process" << std::endl;
                    }
                } else {
                    std::cout << "\033[31;100m E: ProcessManager isn't Enable. \033[m" << std::endl;
                }
            default:
                std::cout << "\033[31;100m Can't find this command. \033[m" << std::endl;
                break;
        }
        printf("\n");
    }
}

// メイン処理を実行
int main() {
    initialize();
    commandLine();
    return 0;
}
