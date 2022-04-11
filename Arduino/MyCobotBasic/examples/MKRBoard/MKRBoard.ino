#include <MyCobotBasic.h>
#include <vector>

#define SET_BASIC_OUT 0xa0
#define GET_BASIC_IN 0xa1

byte HEADER = 0xfe;
byte FOOTER = 0xfa;

using namespace std;
vector<int> client_data;
vector<int> temp_data;
vector<int> atom_data;
int count = -1, data = -1;
int t_begin;

void setup()
{
    Serial.begin(115200);
    /* If you use other boards, please check whether the serial port on the official website supports Serial1. 
     * For example, m5's Serial is Serial1 (so replace the following Serial1 with Serial1)*/
    Serial1.begin(
        1000000);  
    delay(100);

    MyCobotBasic myCobot;
    delay(500);

    myCobot.powerOn();
    delay(500);

    pinMode(15, OUTPUT); // 1
    pinMode(5, OUTPUT); // 2
    pinMode(2, OUTPUT); // 2
}

void loop()
{
    ClientDataToAtom();
    AtomDataToClient();
    OtherMsgToClient();
    ClearData();
}


/*
 * Function: Check whether the header of the serial port wifi or bluetooth return message is fe fe
 */
bool checkHeader(vector<int> &v_data)
{
    if (v_data[0] == HEADER && v_data[1] == HEADER)
        return true;
    return false;
}

bool HandleStickyPackets(vector<int> &v_data)
{
    //Get the length of the protocol to determine the terminator fa
    vector<int>::iterator it_vdata = v_data.begin() + 2 + v_data[2];
    int len = v_data.size();
    //First judge whether the length is less than 5, the instruction length is at least 5--> process the data
    if (len >= 5 && len <= (v_data[2] + 3)) {
        if (*it_vdata == FOOTER) {
            v_data.erase(it_vdata + 1, v_data.end());
            return true;
        }
    } 
    return false;
}

/*
 * Function:Handle some client messages that Atom doesn't handle
 */
bool HandleOtherMsg(vector<int> &v_data)
{
    bool flag = false;
    switch (v_data[2]) {
        case 4:
            switch (v_data[3]) {
                case SET_BASIC_OUT: {
                    //0xfe 0xfe 0x04 0xa0 pin_no pin_data 0xfa
                    byte pin_no = v_data[4];
                    pinMode(pin_no, OUTPUT);
                    delay(5);
                    bool pin_data = v_data[5];
                    digitalWrite(pin_no, pin_data);
                }
                break;
            }
            break;
        case 3:
            switch (v_data[3]) {
                case GET_BASIC_IN: {
                    byte pin_no = v_data[4];
                    pinMode(pin_no, INPUT);
                    delay(5);
                    bool pin_state = digitalRead(pin_no);
                    delay(5);
                    v_data[2] = 0x04;
                    v_data.insert(v_data.end() - 1, pin_state);
                    flag = true;
                }
                break;
            }
            break;
    }
    return flag;
}

/*
 * Function: Send the message returned by Atom to the user
 */
void SendDataToUser(vector<int> &v_data)
{
    if (checkHeader(v_data) && HandleStickyPackets(v_data)) {
        if (HandleOtherMsg(v_data)) {
            for (int i = 0; i < v_data.size(); i++) {
                Serial.write(v_data[i]);
            }
        }
        v_data.clear();
    }
    return;
}

void ClientDataToAtom()
{
    if (Serial.available() > 0) {
      count = 1; 
      while (Serial.available() > 0) {
          data = Serial.read();
          Serial1.write(data);
          client_data.push_back(data);
      }
      t_begin = millis();
    }
}

void AtomDataToClient()
{
    int temp;
    bool flag = false;
    if (Serial1.available() > 0) {
        count = 0;
        while (Serial1.available() > 0) {
            data = Serial1.read();
            if (data == HEADER && (temp = Serial1.read()) == HEADER) {
                Serial.write(temp);
                flag = true;
            }
            if (flag) {
                Serial.write(data);
            }
        }
    }
}

void OtherMsgToClient()
{
    if (count == 1 && ((millis() - t_begin) > 10)) {
        count = 0;
        for (int i = 0; i < client_data.size(); i++) {
            temp_data.push_back(client_data[i]);
        }
        SendDataToUser(temp_data); 
    }
}

void ClearData()
{
    if (count == 0){
        client_data.clear();
    }
}