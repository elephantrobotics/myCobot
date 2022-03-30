#include "DisplayTemplate.h"

DisplayTemplate::DisplayTemplate()
{

}

void DisplayTemplate::Start()
{
  DisplayState(display_start_state);
  DisplayPos(display_pos);
}

void DisplayTemplate::MenuInit(int* num, const string* menu, int len)
{
  menuMap.clear();
  for (int i = 0; i < len; i++) {
    menuMap.insert(std::make_pair(num[i], menu[i]));
  }
  menu_len = menuMap.size();
}

void DisplayTemplate::MenuInit(std::map<int, string> menu)
{
  menuMap.clear();
  menuMap = menu;
  menu_len = menuMap.size();
  Serial.print("menu len==");
  Serial.println(menu_len);
}

void DisplayTemplate::MenuChoice()
{    
  int len = menu_len - 1;
  Serial.print("len===");
  Serial.println(len);
  int temp_start_state = display_start_state;
  int temp_pos = display_pos;
  if (state < 0){
    state = len;
    display_start_state = state - len;
    display_pos = len;
  }
  if (state > len){
    state = 0;
    display_start_state = 0;
    display_pos = 0;
  }

  if (display_pos == len && (state - display_start_state) > len ) {
    display_start_state = state - len;
  }
  if (display_pos == 0 && (state - display_start_state) < 0) {
    display_start_state = state;
  }
  if ((state - display_start_state) <= len) {
    display_pos = state - display_start_state;
  }

  if (temp_start_state != display_start_state) {
    DisplayState(display_start_state);
  }

  if (temp_pos != display_pos) {
    DisplayPos(display_pos);
  }

}
void DisplayTemplate::DisplayPos(int display_pos) {
  Serial.print("pos == ");
  Serial.println(display_pos);
  board->FillRect(rect_pos1[0], rect_pos1[1], rect_pos1[2], rect_pos1[3], Board_BLACK);
  board->SetTextSize(2);
  board->SetCursor(0,y_pos[display_pos]);
  board->SetTextColor(Board_WHITE);
  board->Print(" >");
}

void DisplayTemplate::DisplayState(int display_start_state) {
  Serial.print("display_start_state === ");
  Serial.println(display_start_state);
  if (display_start_state > menuMap.size() - 4) {
    return;
  }
  board->FillRect(rect_pos2[0], rect_pos2[1], rect_pos2[2], rect_pos2[3], Board_BLACK);
  for(int i = 0; i < menu_len; i++) {
      board->SetTextSize(2);
      board->SetCursor(30,y_pos[i]);
      board->SetTextColor(Board_WHITE);
      board->Print(menuMap[display_start_state + i].c_str());
  }
  board->DrawButtonLine();
}
