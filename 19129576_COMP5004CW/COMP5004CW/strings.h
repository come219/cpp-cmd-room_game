//
// Created by DrMark on 10/4/2017.
//
//Sebastian St Johnston
//19129576
//Room MUD game Coursework

#ifndef TEXTADV_STRINGS_H
#define TEXTADV_STRINGS_H


#include <string>

const std::string r1name = "Room 1";
const std::string r1desc = "You are in room 1. It's really quite boring, but then, it's just for testing really. There's a passage to the north.";

const std::string r2name = "Blue Room";
const std::string r2desc = "You are in the blue room. You know because it's blue. That's about all though. There's a passage to the south and east.";

const std::string r3name = "Spooky Room";
const std::string r3desc = "You are in the Spooky room. You want to get out of here... There is a passage to the west.";

const std::string rivername = "River";
const std::string riverPath = "You cannot cross the river";

const std::string badExit = "You can't go that way.";
const std::string badCommand = "I don't understand that.";


const std::string quitCommand = " & (Q)uit\n";

const std::string saveText = "You have saved the game!";





const std::string cursor = "> ";





const std::string badItem = "That item does not exist.";


const std::string itemcheck = " is in this room!";
const std::string examineText = "You examine: ";



const std::string itemInRoom = "There is an item already in this room!";
const std::string itemInInventory = "That item is already in your inventory!";
const std::string missingItem = "That item is not in this room!";



const std::string droppart1 = "You have dropped ";
const std::string droppart2 = " to ";
const std::string droppart3 = ".\n";

const std::string pickpart1 = "You have picked up the ";
const std::string pickpart2 = " from ";
const std::string pickpart3 = ".\n";


const std::string outOfRange = "Please type in the item after the verb.";
const std::string spellingError = "Please type in the full item name.";

const std::string stickname = "Stick";
const std::string stickdesc = "A long wooden stick.";
const std::string stickkw = "stick";

const std::string mapname = "Map";
const std::string mapdesc = "North of Room 1 is the Blue Room and that's it really...";
const std::string mapkw = "map";

const std::string keyname = "Key";
const std::string keydesc = "A rusty key, probably for one of these rooms.";
const std::string keykw = "key";


const std::string gametitle = "\nRooms: \n The Epic MUD game";
const std::string titlemenu = "\nAvailable Title Menu Commands: \n(L)oad a save, start a (F)resh game";
const std::string badInput = "Please input a proper command.";


const std::string loadText = "\nYou have loaded a game save.";
const std::string freshText = "\nEnjoy and have fun!";

const std::string quitText = "Thank you for playing!";


const std::string MenuInventoryTitle = "Available INVENTORY commands: ";
const std::string MenuInventoryText = "(D)rop, E(x)amine, (R)eturn to the Mainmenu ";


const std::string MenuMoveTitle = "Available MOVEMENT commands: ";
const std::string MenuMoveText = "(N)orth, (S)outh, (E)ast, (W)est, (R)eturn to the Mainmenu ";

const std::string Menu1Title = "Available MAIN MENU commands: ";
const std::string Menu1Text = "(M)ove, (I)nventory, (G)et, Des(c)ribe, S(a)ve ";


#endif //TEXTADV_STRINGS_H
