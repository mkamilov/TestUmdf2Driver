// DriverClientApp.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#include <iostream>

#include <Windows.h>
#include <winioctl.h>
#include <winsvc.h>
#include <string>

void DriverInstall();
void DriverUnInstall();

int main()
{
    std::cout << "Hello World!\n"; 

    DriverInstall();

    DriverUnInstall();
}

void DriverInstall()
{
    std::wstring pDeviceName(L"TestUmdf2Driver");

    WCHAR strPath[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, strPath);
    std::wstring binaryPath(strPath);
    binaryPath += L"\\" + pDeviceName + L".dll";

    std::string logPath(binaryPath.begin(), binaryPath.end());

    SC_HANDLE hManager, hService;
    hManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
    if (!hManager) {
        DWORD err = GetLastError();
        if (err == ERROR_ACCESS_DENIED) {
            printf("OPenSCManager Access denied - run administration access");
        }
        else {
            printf("OPenSCManager Error : %d", err);
        }
        return;
    }

    printf("CreateService");
    hService = CreateService(hManager, pDeviceName.c_str(), pDeviceName.c_str(), SERVICE_ALL_ACCESS, SERVICE_KERNEL_DRIVER, SERVICE_AUTO_START,
        SERVICE_ERROR_IGNORE, binaryPath.c_str(), NULL, NULL, NULL, NULL, NULL);
    if (!hService) {
        printf("Imsdriver is already created");

        hService = OpenService(hManager, pDeviceName.c_str(), SERVICE_ALL_ACCESS);
        if (!hService) {
            printf("CreateService Error");
            CloseServiceHandle(hManager);
            return;
        }
    }

    printf("StartService");
    if (!StartService(hService, 0, NULL)) {
        DWORD err = GetLastError();
        printf("StartService Error : %d", err);
        if (err == ERROR_SERVICE_ALREADY_RUNNING) {
            printf("Already running");
        }
    }

    CloseServiceHandle(hManager);
    CloseServiceHandle(hService);

    printf("Install OK");
}


void DriverUnInstall()
{
    std::wstring pDeviceName(L"TestUmdf2Driver");
    SC_HANDLE hManager, hService;
    hManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
    if (!hManager) {
        printf("OPenSCManager Error : %d", GetLastError());
        return;
    }

    hService = OpenService(hManager, pDeviceName.c_str(), SERVICE_ALL_ACCESS);

    DeleteService(hService);
    if (hService) {
        CloseServiceHandle(hService);
    }
    printf("Uninstall OK");
}
