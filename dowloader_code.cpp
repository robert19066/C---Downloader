#include <windows.h>
#include <iostream>
using namespace std;


bool runInstaller(const wchar_t* exePath)
{
    STARTUPINFOW si;
    PROCESS_INFORMATION pi;  // this is always the correct struct


    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // Start the installer
    if (!CreateProcessW(
            exePath,               // Path to installer
            NULL,                  // Command line
            NULL, NULL, FALSE,
            0,                     // Creation flags
            NULL, NULL,
            &si, &pi))
    {
        std::cerr << "CreateProcess failed. Error code: " << GetLastError() << "\n";
        return false;
    }

    // Wait for installer to finish
    WaitForSingleObject(pi.hProcess, INFINITE);

    // Clean up
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return true;
}


int main() {
    cout << "Starting installer...\n";
    cout << "Welcome to the MINGW64(gcc, and many more c++/c/fortran toos) guided installer!\n";
    cout << "Step 1:Running the installer executable.\n";
    runInstaller(L"./msys2-x86_64-20250830.exe");

    cout << "Installer finished successfully.\n";
    cout << "Step 2: WARNING,THIS STEP IS MANUAL:" << endl;
    cout <<" Please follow the on-screen instructions to complete the installation.\n";
    cout << "The first step is to run the MSYS2 MINGW64 shell from the Start Menu.\n";
    cout << "Then, in the shell, execute the following command:\n";
    cout << "pacman -S mingw-w64-x86_64-gcc\n";
    cout << "Then close the console.\n";
    cout << "AND to add MINGW64 to your path, open the \"Edit the system environment variables\" dialog from the Start Menu.\n";
    cout << "Click on \"Environment Variables...\", then under \"System variables\", find and select the \"Path\" variable, and click \"Edit...\".\n";
    cout << "Click \"New\" and add the path: C:\\msys64\\mingw64\\bin\n";
    cout << "Click OK to close all dialogs.\n";
    cout << "now you have MINGW64 installed with gcc!\n";
    return 0;

}
