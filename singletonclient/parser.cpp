#include <QString>
#include "parser.h"
#include <vector>

parser::parser(){};
// функция разбивает строку на слова по пробелам
QString parser::parse(QString line){
    if (line.size() <= 2) return "Too short to parse!";
    std::vector<QString> slova;
    slova.push_back("");
    for (int i = 0; i < line.size() - 2; i++){
        if (line[i] != ' ')
            slova[slova.size() - 1] += line[i];
        else{
            slova.push_back("");
        }
    }

    // выбор нужной функции:
    if (slova[0] == "")
        return "No command!";
    if (slova[0] == "login")
        return "User wants to login into system";
    if (slova[0] == "register")
        return "User wants to register new account";
    if (slova[0] == "joinroom")
        return "User wants to connect to a room";
    if(slova[0] == "leaveroom")
        return "User wants to leave the room";
    if(slova[0] == "logout")
        return "User wants to logout";
    if(slova[0] == "kick")
        return "user1 wants to kick user2";
    return "Unknown command!";
}
