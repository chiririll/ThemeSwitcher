#include <ctime>
#include <iostream>

using namespace std;

int char_to_int(char* str) 
{
    int num = 0;
    for (int i = 0; i < 2; i++) 
    {
        if (str[i] == 0) break;
        num *= 10;
        num += (str[i] - '0') % 10;
    }
    return num;
}

int main(int argc, char* argv[]) 
{
    ::ShowWindow(::GetConsoleWindow(), SW_HIDE);

    int beg_h = 20, beg_m = 0;
    int end_h = 7, end_m = 0;
    
    for (int i = 1; i < argc - 1; i++) 
    {
        if (argv[i][0] != '-')
            continue;
        
        switch (argv[i][1])
        {
            // Dark start hour
            case 'H':
                beg_h = char_to_int(argv[i+1]);
                break;
            // Dark start minute
            case 'M':
                beg_m = char_to_int(argv[i+1]);
                break;
            // Light start hour
            case 'h':
                end_h = char_to_int(argv[i+1]);
                break;
            // Light start minute
            case 'm':
                end_m = char_to_int(argv[i+1]);
                break;
        }
    }

    time_t now = time(NULL);
    struct tm *tm_struct = localtime(&now);
    int Hour = tm_struct->tm_hour, Minute = tm_struct->tm_min;

    // Checking hour
    bool isDark = false;
    if (beg_h <= end_h) 
        isDark = Hour > beg_h && Hour < end_h;
    else
        isDark = Hour > beg_h || Hour < end_h;
    
    // Checking minutes
    isDark = isDark || Hour == beg_h && Minute >= beg_m || Hour == end_h && Minute < end_m;
    
    // cout << Hour << ':' << Minute << " \t" << (isDark ? "Dark" : "Light") << endl;
    if (isDark)
        system("%SystemRoot%\\system32\\WindowsPowerShell\\v1.0\\powershell.exe New-ItemProperty -Path HKCU:\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize -Name AppsUseLightTheme -Value 0 -Type Dword -Force");
    else
        system("%SystemRoot%\\system32\\WindowsPowerShell\\v1.0\\powershell.exe New-ItemProperty -Path HKCU:\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize -Name AppsUseLightTheme -Value 1 -Type Dword -Force");
    return 0;
}