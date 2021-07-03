#include <iostream>
#include <Windows.h>
#include <tlhelp32.h>

using std::cout;
using std::wcout;
using std::wstring;
using std::endl;



int main()
{
    HANDLE snapshandle;
    PROCESSENTRY32 pe32;

    pe32.dwSize = sizeof(PROCESSENTRY32);

    snapshandle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    Process32First(snapshandle, &pe32);

    wstring blacklist[] = { L"ida.exe", L"ida64.exe", L"x32dbg.exe", L"x64dbg.exe", L"ProcessHacker.exe" };

    int len = sizeof blacklist / sizeof blacklist[0];


    do
    {
        WCHAR* temp = pe32.szExeFile;

        for (int i = 0; i <= len; i++)
        {
            if (temp == blacklist[i]) {

                HANDLE process_handle = OpenProcess(PROCESS_ALL_ACCESS, TRUE, pe32.th32ProcessID);

                TerminateProcess(process_handle, 0);

                wcout << temp << " terminated" << endl;
            }
        }

    } while (Process32Next(snapshandle, &pe32));

    CloseHandle(snapshandle);
    
    getchar();

    return 0;
}
