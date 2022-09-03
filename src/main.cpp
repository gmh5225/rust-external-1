#include "includes.hpp"

bool cheat_ready = false; /* hang me */

void init_cheat()
{
    check_game_loaded();
    
    cheat_ready = true;
    return;
}

DWORD WINAPI cheat_thread()
{
    // cheats for gamers go here
    if(!cheat_ready)
    {
        std::cout << "Cheat not ready... Shutting down...\r\n";
        exit(-1);
    }
    
    while(1) {
        draw_esp_players(1000); // max_dist
        draw_esp_tc(350); // max_dist: higher = more lag
        
        // You must hold down RMB for this to work.
        move_to_nearest_head();
    }
}

int main()
{
    std::cout << "Checking for rust...\r\n";
    
    while(get_pid("Rust.exe") == 0)
        std::cout << "[err] launch rust\r\n";
    
    uint32_t proc_id = get_pid("Rust.exe"); //get_pid(const char* proc_name);
    init_cheat(proc_id);
    
    HANDLE hThread = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)cheat_thread, NULL, NULL, 0);
}
