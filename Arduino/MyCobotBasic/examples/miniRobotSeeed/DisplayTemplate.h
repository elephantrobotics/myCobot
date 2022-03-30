#include <map>
#include <TFT_eSPI.h>
#include <string>
class DisplayTemplate
{
public:
    DisplayTemplate();
    void Start();
    void MenuInit(int *num, const String *menu, int len);
    void MenuChoice();
    void DisplayPos(int display_pos);
    void DisplayState(int display_start_state);
private:
    TFT_eSPI tft;
    std::map<int, String> menuMap;
public:
    int state = 0;
    int *y_pos;
    int *rect_pos1;
    int *rect_pos2;
    int display_start_state = 0;
    int display_pos = 0;
    unsigned long t_begin = 0;
};
