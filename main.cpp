#include<iostream>
#include<windows.h>
#include<tlhelp32.h>

int main() {
    using namespace std;

    // Input Time
    int minutes;
    {
input:
        cout << "How many minutes (0-120) do you want to play?" << endl;
        cin >> minutes;

        if (minutes < 0) {
            cerr << "Input must be positive!" << endl << endl;
            goto input;
        }

        if (minutes > 120) {
            clog << "ARE YOU SURE TO PLAY SUCH LONG?" << endl;
            clog << "All right, then. You decide yourself. " << endl << endl;
        }
    }

    // Count Down
    cout << "Counting down...." << endl << endl;
    {
        for (auto i=0; i<minutes; ++i) {
            // message Beeps
            if (i<=25) {
                // beep once if 0<t<=25
                MessageBeep(MB_ICONASTERISK);
            } else {
                // multiple beeps if 25<t<30
                for (auto i=0; i<10; Sleep(1000), ++i) {
                    MessageBeep(MB_ICONASTERISK);
                }
            }

            cout << (minutes-i) << " minute(s) left." << endl;
            for (auto j=0; j<60; ++j) Sleep(1000);
        }
    }

    // Kill Civilization V!
    cout << "Now killing Civilization V!" << endl;
    {
        auto hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        if (hProcessSnap == INVALID_HANDLE_VALUE) {
            cout << "Failed to create a snapshot of all processes!" << endl;
            return 0;
        }

        PROCESSENTRY32 pe32;
        pe32.dwSize = sizeof(PROCESSENTRY32);

        if (!Process32First(hProcessSnap, &pe32)) {
            cout << "Failed to fetch the first process of snapshot!" << endl;
            CloseHandle(hProcessSnap);
        }

        do {
            if (lstrcmpi(pe32.szExeFile, "civilizationv.exe") == 0) {
                HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, false, pe32.th32ProcessID);
                if (hProcess == INVALID_HANDLE_VALUE) {
                    cout << "OpenProcess failed." << endl;
                } else {
                    TerminateProcess(hProcess, 0);
                    CloseHandle(hProcess);
                }

                return 0;
            }

        } while (Process32Next(hProcessSnap, &pe32));

        CloseHandle(hProcessSnap);
    }

    // Ends
    return 0;
}
