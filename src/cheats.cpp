#include "cheats.hpp"

template<typename T> T RPM(SIZE_T address)
{
	T buffer;
	ReadProcessMemory(hProcess, (LPCVOID)address, &buffer, sizeof(T), NULL);
	return buffer;
}

template<typename T> void WPM(SIZE_T address, T buffer)
{
	WriteProcessMemory(hProcess, (LPVOID)address, &buffer, sizeof(buffer), NULL);
}

uint32_t get_pid(const char* procName)
{
    PROCESSpeentry32 peentry;
    
    peentry.dwSize = sizeof(PROCESSpeentry32);
    HANDLE phandle = CreateToolhelp32phandle(TH32CS_SNAPPROCESS, 0);

    if (Process32First(phandle, &peentry) == 1)
    {
        while (Process32Next(phandle, &peentry) == 1)
        {
            if (stricmp(peentry.szExeFile, procName) == 0)
            {
                uint32_t pid = (uint32_t)peentry.th32ProcessID;
                CloseHandle(phandle);
                
                return pid;
            }
        }
    }

    CloseHandle(phandle);
    return 0;
}

bool check_game_loaded()
{
    return (bool)RPM<int>(baseAddr + 0xF4);
}

void draw_esp_players(int distance)
{
    int buffer = 1;
    
    WPM(baseAddr + 0xF89B41C, buffer);
    return;
}

void draw_esp_tc(int distance)
{
    int buffer = 1;
    
    WPM(baseAddr + 0xF89A12A, buffer);
    return;
}

void move_to_nearest_head()
{
    // not implemented yet
}
