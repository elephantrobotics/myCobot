#include "MyCobotSaver.h"
#if defined MyCobot_M5
MyCobotSaver::MyCobotSaver()
{

}


void MyCobotSaver::listDir(fs::FS &fs, const char *dirname, uint8_t levels)
{
    Serial.printf("Listing directory: %s\r\n", dirname);

    File root = fs.open(dirname);
    if (!root) {
        Serial.println("- failed to open directory");
        return;
    }
    if (!root.isDirectory()) {
        Serial.println(" - not a directory");
        return;
    }

    File file = root.openNextFile();  //less 8 coloumns
    while (file) {
        if (file.isDirectory()) {
            Serial.print("  DIR : ");
            Serial.println(file.name());
            if (levels) {
                listDir(fs, file.name(), levels - 1);
            }
        } else {
            Serial.print("  FILE: ");
            Serial.print(file.name());
            Serial.print("\tSIZE: ");
            Serial.println(file.size());
        }
        file = root.openNextFile();
    }
}


void MyCobotSaver::writeFile(fs::FS &fs, const char *path, const char *message)
{
    Serial.printf("Writing file: %s\r\n", path);

    File file = fs.open(path, FILE_WRITE);
    if (!file) {
        Serial.println("- failed to open file for writing");
        return;
    }
    if (file.print(message)) {
        Serial.println("- file written");
    } else {
        Serial.println("- frite failed");
    }
}

void MyCobotSaver::appendFile(fs::FS &fs, const char *path, const char *message)
{

    File file = fs.open(path, FILE_APPEND);
    if (!file) {
        return;
    }
    file.print(message);
}

void MyCobotSaver::deleteFile(fs::FS &fs, const char *path)
{
    Serial.printf("Deleting file: %s\r\n", path);
    if (fs.remove(path)) {
        Serial.println("- file deleted");
    } else {
        Serial.println("- delete failed");
    }
}

void MyCobotSaver::readFile(fs::FS &fs, const char *path)
{

    File file = fs.open(path);
    if (!file || file.isDirectory()) {
        Serial.println("- failed to open file for reading");
        return;
    }

    String this_line = "";

    while (file.available()) {
        char this_char = char(file.read());
        this_line += this_char;
        if (this_char == '\n') {
            saver_angles_enc jae_this;
            jae_this = processStringIntoInts(this_line);

            this_line = "";
        }

    }

}
void MyCobotSaver::MyPalletizerreadFile(fs::FS &fs, const char *path)
{

    File file = fs.open(path);
    if (!file || file.isDirectory()) {
        Serial.println("- failed to open file for reading");
        return;
    }

    String this_line = "";

    while (file.available()) {
        char this_char = char(file.read());
        this_line += this_char;
        if (this_char == '\n') {
            saver_MyPalletizer_angles_enc jae_this;
            jae_this = MyPalletizerprocessStringIntoInts(this_line);

            this_line = "";
        }

    }

}


MyCobotSaver::saver_angles_enc MyCobotSaver::processStringIntoInts(
    String string_input)
{
    saver_angles_enc sae;
    int data_index = 0;
    String data_angle_string = "";
    for (int i = 0; string_input[i] != '\n'; i++) {

        if (string_input[i] == ',') {
            if ((data_index < 6) && (i > 1)) {
                sae.joint_angle[data_index] = data_angle_string.toInt();
            } else {
                break;
            }
            data_angle_string = "";
            data_index ++;
            continue;
        } else {
            data_angle_string += string_input[i];
        }
    }
    return sae;
}


MyCobotSaver::saver_MyPalletizer_angles_enc
MyCobotSaver::MyPalletizerprocessStringIntoInts(String string_input)
{
    saver_MyPalletizer_angles_enc sae;
    int data_index = 0;
    String data_angle_string = "";
    for (int i = 0; string_input[i] != '\n'; i++) {

        if (string_input[i] == ',') {
            if ((data_index < 4) && (i > 1)) {
                sae.joint_angle[data_index] = data_angle_string.toInt();
            } else {
                break;
            }
            data_angle_string = "";
            data_index ++;
            continue;
        } else {
            data_angle_string += string_input[i];
        }
    }
    return sae;
}
#endif