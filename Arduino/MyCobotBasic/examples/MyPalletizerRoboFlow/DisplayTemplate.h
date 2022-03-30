#include <map>
#include <M5Stack.h>
#include <string>

#define GREY 0x5AEB

using namespace std;
class DisplayTemplate
{
public:
    DisplayTemplate();
    void Start();
    void MenuInit(int *num, const string *menu, int len);
    void MenuChoice();
    void DisplayPos(int display_pos);
    void DisplayState(int display_start_state);
private:
    std::map<int, string> menuMap;
public:
    int state = 0;
    int *y_pos;
    int *rect_pos1;
    int *rect_pos2;
    int display_start_state = 0;
    int display_pos = 0;
    unsigned long t_begin = 0;
    int menu_len = 0;
};
