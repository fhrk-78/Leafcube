/*

こんなに汚いソースコードは初めて見たでしょう
(ﾟ∀ﾟ)ｱﾋｬﾋｬﾋｬﾋｬﾋｬﾋｬﾋｬﾋｬﾋｬﾋｬﾋｬﾋｬﾋｬﾋｬﾋｬﾋｬﾋｬﾋｬ

*/

// include
#include "header/all.h"

// グローバル変数の宣言

//初期化
bool quitNow = false;
bool processManagerEnable = false;
bool OVFSEnable = false;
bool OVFSManagerEnable = false;

//プロセス管理変数
std::string processName[PROCESS_MAX];
int processAccesspermission[PROCESS_MAX];
std::string processPublisher[PROCESS_MAX];

//OVFS管理変数
std::string OVFSver = "1.0.0";
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
    if (OVFSEnable == true && OVFSManagerEnable == true) {
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
    if (OVFSEnable == true && OVFSManagerEnable == true) {
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
    if (OVFSEnable == true && OVFSManagerEnable == true) {
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
    OVFSEnable = true;
    OVFSManagerEnable = true;

    //各処理をプロセスとして登録 100番台はシステムに予約されています
    processsPecifiedAdd(101, "system/processManager", 10, "system/system_process");
    processsPecifiedAdd(102, "system/OVFSManager", 10, "system/system_process");

    //システムファイルの作成
    mkdir("/system", 10);
}

void processManager() { //ProcessManagerの処理
    return;
}

void OVFSManager() { //OVFSManagerの処理
    return;
}

int commandLine() { //コマンド入力の待機
    std::string inputCommandBefore = "";
    std::string inputCommand = "";
    std::string inputCommandOption[10];
    std::string nowDirectory = "/";
    int cmdNum = 0;

    while (true) {
        if (quitNow == true) {
            break;
        }
        for (auto i = 0; i < 10; ++i) {
            inputCommandOption[i] = "";
        }
        std::cout << "\033[90m" << nowDirectory << ">";
        std::getline(std::cin, inputCommandBefore);

        int j = 0;
        std::string k = "";
        for (auto i = 0;i < inputCommandBefore.length(); ++i) {
            if (inputCommandBefore.substr(i, 1) == " ") {
                inputCommandOption[j] = k;
                k = "";
                j += 1;
            } else {
                k += inputCommandBefore.substr(i, 1);
            }
        }
        inputCommandOption[j] = k;

        inputCommand = inputCommandOption[0];

        if (inputCommand == "pst") {
            cmdNum = 1;
        } else
        if (inputCommand == "ps") {
            cmdNum = 2;
        } else
        if (inputCommand == "pkill") {
            cmdNum = 3;
        } else
        if (inputCommand == "padd") {
            cmdNum = 4;
        } else
        if (inputCommand == "pperu") {
            cmdNum = 5;
        } else
        if (inputCommand == "pperd") {
            cmdNum = 6;
        } else
        if (inputCommand == "plf") {
            cmdNum = 7;
        } else
        if (inputCommand == "ovfss") {
            cmdNum = 8;
        }else
        if (inputCommand == "quit") {
            cmdNum = 9;
        } else
        if (inputCommand == "mkf") {
            cmdNum = 10;
        } else
        if (inputCommand == "say") {
            cmdNum = 11;
        } else
        if (inputCommand == "clr") {
            cmdNum = 12;
        } else
        {
            cmdNum = -1;
        }
        std::cout << "\033[m";

        switch(cmdNum) {
            case 0:
                std::cout << "\033[31;100m Can't run this command.\nThis command is obsolete \033[m \n DEBUG: " << inputCommandOption[0] << " " << inputCommandOption[1] << "" << inputCommandOption[2] << " " << inputCommandOption[3] << std::endl;
                break;
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
                if (inputCommandOption[1] == "-s") {
                    if (processManagerEnable == true) {
                        processManagerEnable = false;
                    } else {
                        processManagerEnable = true;
                    }
                    std::cout << "Switch successful\n" << "\"ps\" to check status" << std::endl;
                } else {
                    std::cout << "ProcessManager:" << (processManagerEnable ? "\033[32m Enabled" : "\033[31m Disabled") << "\033[m" << std::endl;
                }
                break;
            case 3:
                if (processManagerEnable == true) {
                    processRemove(std::stoi(inputCommandOption[1]));
                    std::cout << "Process kill successful\n" << "\"pst\" to check all process" << std::endl;
                } else {
                    std::cout << "\033[31;100m E: ProcessManager isn't Enable. \033[m" << std::endl;
                }
                break;
            case 4:
                if (processManagerEnable == true) {
                    processAdd(inputCommandOption[1], std::stoi(inputCommandOption[2]), "user/" + inputCommandOption[3]);
                    std::cout << "Process add successful (Permission: " << inputCommandOption[2] << ", Publisher: " << inputCommandOption[3] << ")\n" << "\"pst\" to check all process" << std::endl;
                } else {
                    std::cout << "\033[31;100m E: ProcessManager isn't Enable. \033[m" << std::endl;
                }
                break;
            case 5:
                if (processManagerEnable == true) {
                    if (processAccesspermission[std::stoi(inputCommandOption[1])] >= 10) {
                        std::cout << "\033[31;100m E: Permissions are already maxed \033[m" << std::endl;
                    } else {
                        processAccesspermission[std::stoi(inputCommandOption[1])] += 1;
                        std::cout << "Process permission upgrade successful\n" << "\"pst\" to check all process" << std::endl;
                    }
                } else {
                    std::cout << "\033[31;100m E: ProcessManager isn't Enable. \033[m" << std::endl;
                }
                break;
            case 6:
                if (processManagerEnable == true) {
                    if (processAccesspermission[std::stoi(inputCommandOption[1])] >= 10) {
                        std::cout << "\033[31;100m E: Permissions are already minimaled \033[m" << std::endl;
                    } else {
                        processAccesspermission[std::stoi(inputCommandOption[1])] -= 1;
                        std::cout << "Process permission downgrade successful\n" << "\"pst\" to check all process" << std::endl;
                    }
                } else {
                    std::cout << "\033[31;100m E: ProcessManager isn't Enable. \033[m" << std::endl;
                }
                break;
            case 7:
                if (processManagerEnable == true) {
                    std::cout << "FindProcess:" << std::endl;
                    for (auto i = 0; i < PROCESS_MAX; ++i) {
                        if (processName[i] == inputCommandOption[1] || processAccesspermission[i] == std::stoi(inputCommandOption[1]) || processPublisher[i] == inputCommandOption[1]) {
                            std::cout << STRCHR(processName[i]) << "(" << i << ") : " << STRCHR(processPublisher[i]) << " | " << processAccesspermission[i] << std::endl;
                        }
                    }
                } else {
                    std::cout << "\033[31;100m E: ProcessManager isn't Enable. \033[m" << std::endl;
                }
                break;
            case 8:
                if (inputCommandOption[1] == "-v") {
                    if (OVFSEnable == true) {
                        OVFSEnable = false;
                    } else {
                        OVFSEnable = true;
                    }
                    std::cout << "Switch successful\n" << "\"ovfss\" to check status" << std::endl;
                } else if (inputCommandOption[1] == "-m") {
                    if (OVFSManagerEnable == true) {
                        OVFSManagerEnable = false;
                    } else {
                        OVFSManagerEnable = true;
                    }
                    std::cout << "Switch successful\n" << "\"ovfss\" to check status" << std::endl;
                } else {
                    std::cout << "OVFSManager:" << (OVFSManagerEnable ? "\033[32m Enabled" : "\033[31m Disabled") << "\033[m" << std::endl;
                    std::cout << "OnVirtualenvironmentFileSystem:" << (OVFSEnable ? "\033[32m Enabled" : "\033[31m Disabled") << "\033[m" << std::endl;
                }
                break;
            case 9:
                quitNow = true;
                break;
            case 10:
                if (OVFSEnable == true && OVFSManagerEnable == true) {
                    mkfile(inputCommandOption[1], inputCommandOption[2], std::stoi(inputCommandOption[3]), "");
                    std::cout << "Make complete" << std::endl;
                }
                break;
            case 11:
                if (inputCommandOption[1].substr(0,1) == "%") {
                    std::cout << "\e[1A" << inputCommandOption[1].substr(1) << "       " << std::endl;
                } else {
                std::cout << inputCommandOption[1] << std::endl;
                }
                break;
            case 12:
                system("cls");
                break;
            default:
                std::cout << "\033[31;100m Can't find this command. \033[m" << std::endl;
                break;
        }
        printf("\n");
    }
    return 0;
}

// メイン処理を実行する
int main() {
    initialize();
    return commandLine();
}
