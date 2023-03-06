//Sebastian St Johnston
//19129576
//Room MUD game Coursework

/*
 *!!!!!!!!!!!!! Back Log!!!!!!!!!!!!!
 *
 *          Immediate/ High priority
 *
 * ?? add room river which causes user to be unable to move into the room
 *
 * ?? Find a way of displaying available rooms for debugging
 *
 * ?? Switch statement looks for keyword instead of searching through the commandBuffer for the object
 *
 * ?? gameObject list in room constructor
 *
 * !!Encrypting and decrypting save file
 *
 *
 *
 *
 *-----------------------------------------------------------------------------------------------------------
 *
 *          Exercise 1 (20% of the mark)
 *
 [DONE] Add properties to the Room class for storing east, south, and west exits. These
properties will need accessor methods. (5%)

 [DONE] Add code to the gameLoop method to understand the commands east, south, and
west (and the abbreviations e, s and w) and to handle them in a similar way to
north. (5%)

 [DONE] Modify initRooms to create more rooms using the new exits in order to test your
code. (5%)

 [DONE] Find a more elegant way of implementing these exits which does not repeat code.
[Hint: Traversing through map structures/strings, etc can be considered.] (5%)
 *
 *
 *
 *
 *
 *          Exercise 2 (40% of the mark)
 [DONE] Create an GameObject class. It should contain at least a short name, a long
description, and a keyword (for the player to use when typing commands). (5%)

 [DONE] Modify the Room class so that each Room includes a list of GameObjects in the
room. (2%)

 [DONE] Modify the State class to include a representation of a list of GameObjects the
player is carrying, called inventory. (3%)

 [DONE] Modify the Room::describe() method to also print out the short names of all the
objects in the room, formatted as nicely as possible. (5%)

 [DONE] Modify the gameLoop method to pay attention to the second word of the command
the player enters, if there is one. (5%)

 [DONE] Modify the gameLoop command to search through a) objects in the current room,
and b) objects in the inventory, for an object with a keyword matching the second
word of the command the player typed. (5%)

 [DONE] Implement the player command get which, when typed with an object keyword, will
move that object from the current room list into the inventory. It should display
appropriate errors if the object is not in the room or the object is already in the
inventory or the object does not exist. (5%)

 [DONE] Implement the player command drop which, when typed with an object keyword,
will move that object from the inventory into the current room list. It should display
appropriate errors if the object is not in the inventory or already in the room, or does
not exist, etc. (5%)

 [DONE] Implement the player command inventory which will print out the short names of
all the objects in the inventory. (2%)

 [DONE] Implement the player command examine which, when typed with an object
keyword, will print out the long description of that object. (3%)

 [DONE] Modify initRooms to create some GameObjects and put them in the rooms. Use
this to test your program. (No marks are assigned specifically for this task, but
without it the ones above cannot be demonstrated.)
 *
 *
 *
 *

 *          Exercise 3 (40% of the mark)
 *
 Since most players will not want to play an entire game at one sitting, most games
include save and load (or restore) commands. Implement these commands. They
should ask the user for a filename and then write or read the current game state, to or
from that file.
Note that the layout and descriptions of rooms, and the list and descriptions of objects,
are not part of the game state because they do not change during the game. These
should not be included in the save file and saving them will lose marks.


 A simple file open, load, and save does not guarantee full marks and may not
guarantee “a good mark.”

To this end, some important points to consider:
 The “game state” may also include the locations of objects the player has dropped in
rooms. Would it be a good idea to restructure how object locations are stored?

  The State object stores the current room, and objects, using pointers. Pointers
cannot safely be written to disk since addresses may be different when the program
is reloaded. How can you enable this data to be safely saved and reloaded?

  It is worth ensuring to some degree that the user cannot readily cheat, or spoil the
game, by reading or changing a save file. While it is not necessary to implement
actual authentication or encryption but at the same time, the file does not have to be
just a text dump. This actually makes it harder to parse when loaded. So, for
example, saving the required indexes into a static array of strings maybe be a better
way than saving the strings themselves.
 *
 *
 *
 * */




#include <iostream>
#include <iomanip>
#include <memory>
#include <iterator>
#include <vector>
#include <forward_list>
#include "Room.h"
#include "wordwrap.h"
#include "State.h"
#include "strings.h"
#include "GameObject.h"
#include <algorithm>
#include <fstream>
#include <sstream>



//Global Variables and Using statements
using std::string;
using std::unique_ptr;

//strings to help cut and hold the inputs
string commandBuffer;
string saveandloadmenuCommandBuffer;
State *currentState;

//integers that determine which menu is being displayed
int Menu1, MenuMove, MenuInventory, MenuTitle;

//buffer for input to put into the switch statement
char charchoice;
char charchoice2;

//integers to control statements
uint8_t sizeoffirstverb;
int i_rangeTest;
int i_appendTest;


//Defining and declaring global items
auto * stick = new GameObject(&stickname, &stickdesc, &stickkw);
auto * map = new GameObject(&mapname, &mapdesc, &mapkw);
auto * key = new GameObject(&keyname, &keydesc, &keykw);


//Defining and declaring global rooms
auto * r1 = new Room(&r1name, &r1desc);
auto * r2 = new Room(&r2name, &r2desc);
auto * r3 = new Room(&r3name, &r3desc);

//set the inputs into choice buffer
string verbChoice;
string appendChoice;

//boolean variable to check if the user wanted to load the game
bool loadcheck = false;


/**
 * Function to encrypt the string
 *
 */
std::string encrypt(std::string msg, std::string key)
{

    // Make sure the key is at least as long as the message
    std::string tmp(key);
    while (key.size() < msg.size())
        key += tmp;

    // And now for the encryption part
    for (std::string::size_type i = 0; i < msg.size(); ++i)
        msg[i] ^= key[i];
    return msg;

}


/**
 * Function to decrypt the string
 *
 */
std::string decrypt(std::string msg, std::string key)
{


    return msg;
}


/**
 * Function save to the game file collecting all the data from inventory, rooms and current room
 *
 */
void saveGame() {


    //std::cout << state->currentRoomText();

    std::ofstream MyFile("save_file.txt");


            MyFile << "Inventory: ";

            for (auto v : currentState->inventory)
            {

                if(v == map)
                {
                    MyFile << "map";
                }
                if(v == stick)
                {
                    MyFile << "stick";
                }
                if(v == key)
                {
                    MyFile << "key";
                }

            }

            MyFile << "#";



            MyFile << "\nRoom 1: ";


            for (auto v : r1->roomitems1)
            {

                if(v == map)
                {
                    MyFile << "map";
                }
                if(v == stick)
                {
                    MyFile << "stick";
                }
                if(v == key)
                {
                    MyFile << "key";
                }

            }
            MyFile << "!";

            MyFile << "\nRoom 2: ";

            for (auto v : r2->roomitems2)
            {

                if(v == map)
                {
                    MyFile << "map";
                }
                if(v == stick)
                {
                    MyFile << "stick";
                }
                if(v == key)
                {
                    MyFile << "key";
                }

            }

            MyFile << "@";

            MyFile << "\nRoom 3: ";

            for (auto v : r3->roomitems3)
            {

                if(v == map)
                {
                    MyFile << "map";
                }
                if(v == stick)
                {
                    MyFile << "stick";
                }
                if(v == key)
                {
                    MyFile << "key";
                }

            }

            MyFile << "%";


            MyFile << "\nState current room: ";

            if(currentState->getCurrentRoom() == r1)
            {
                MyFile << "1";

            }

            if(currentState->getCurrentRoom() == r2)
            {

                MyFile << "2";
            }

            if(currentState->getCurrentRoom() == r3)
            {
                MyFile << "3";
            }

            MyFile << ";";


    encrypt("myfile string", "bigkey");


    MyFile.close();



}

/**
 * Function to search for a string and find the if the searched string is present and return a boolean value
 *
 */
bool searchStr(std::string search, std::string contained) {



    int found = -1;


    found = search.find(contained);




    if(found != -1)
    {

        //std::cout << "true";
        return true;

    }
    else
    {

        return false;

    }

}


/**
 * Function to read the save file data and load into the game
 *
 */
/*
    Inventory: s#
    Room 1: m!
    Room 2: k@
    Room 3: %
    State current room: 1;
 */
void loadGame() {


        std::string save_data;

        std::ifstream MyReadFile("save_file.txt");

        std::stringstream filebuffer;



        filebuffer << MyReadFile.rdbuf();

        decrypt(filebuffer.str(), "bigkey");


        //std::cout << filebuffer.str();

        //append the string into groups


        std::string inventoryString;
        std::string room1String;
        std::string room2String;
        std::string room3String;
        std::string currentroomString;



        std::string tempbuffer = filebuffer.str();
        //std::cout << tempbuffer;



        //inventory string
        int hash = static_cast<uint8_t>(tempbuffer.find('\n'));
        inventoryString = tempbuffer.erase(hash, tempbuffer.size());
        //std::cout << inventoryString;



        //Room 1 String

        tempbuffer = filebuffer.str().erase(0,inventoryString.size());
        //std::cout << tempbuffer;

        int emark = static_cast<uint8_t>(tempbuffer.find('!'));
        room1String = tempbuffer.erase(emark, tempbuffer.size());
        //std::cout << room1String;




        //Room 2 String

        tempbuffer = filebuffer.str().erase(0,room1String.size() + inventoryString.size() + 1);
        //std::cout << tempbuffer;

        int atsymbol = static_cast<uint8_t>(tempbuffer.find('@'));
        room2String = tempbuffer.erase(atsymbol, tempbuffer.size());
        //std::cout << room2String;




        //Room 3 String

        tempbuffer = filebuffer.str().erase(0,room2String.size() + room1String.size() + inventoryString.size() + 2);
        //std::cout << tempbuffer;

        int percent = static_cast<uint8_t>(tempbuffer.find('%'));
        room3String = tempbuffer.erase(percent, tempbuffer.size());
        //std::cout << room3String;




        //current room String

        tempbuffer = filebuffer.str().erase(0,room3String.size() + room2String.size() + room1String.size() + inventoryString.size() + 3);
        //std::cout << tempbuffer;

        int terminate = static_cast<uint8_t>(tempbuffer.find(';'));
        currentroomString = tempbuffer.erase(terminate, tempbuffer.size());
        //std::cout << currentroomString;




        //inventory check and add
        if(searchStr(inventoryString, "map"))
        {
            //std::cout << "1";
            currentState->addInventory(map);
        }

        if(searchStr(inventoryString, "key"))
        {
            //std::cout << "2";
            currentState->addInventory(key);
        }

        if(searchStr(inventoryString, "stick"))
        {
            //std::cout << "3";
            currentState->addInventory(stick);
        }



        //room 1 check and add
        if(searchStr(room1String, "map"))
        {
            //std::cout << "4";
            r1->addItemToRoom1(map);
        }

        if(searchStr(room1String, "key"))
        {
            //std::cout << "5";
            r1->addItemToRoom1(key);
        }

        if(searchStr(room1String, "stick"))
        {
            //std::cout << "6";
            r1->addItemToRoom1(stick);
        }




        //room 2 check and add
        if(searchStr(room2String, "map"))
        {
            //std::cout << "7";
            r2->addItemToRoom2(map);
        }

        if(searchStr(room2String, "key"))
        {
            //std::cout << "8";
            r2->addItemToRoom2(key);
        }

        if(searchStr(room2String, "stick"))
        {
            //std::cout << "9";
            r2->addItemToRoom2(stick);
        }



        //room 3 check and add
        if(searchStr(room3String, "map"))
        {
            //std::cout << "10";
            r3->addItemToRoom3(map);
        }

        if(searchStr(room3String, "key"))
        {
            //std::cout << "11";
            r3->addItemToRoom3(key);
        }

        if(searchStr(room3String, "stick"))
        {
            //std::cout << "12";
            r3->addItemToRoom3(stick);
        }



        if(searchStr(currentroomString, "1"))
        {
            //std::cout << "13";
            currentState->goTo(r1);
        }

        if(searchStr(currentroomString, "2"))
        {
            //std::cout << "14";
            currentState->goTo(r2);
        }

        if(searchStr(currentroomString, "3"))
        {
            //std::cout << "15";
            currentState->goTo(r3);
        }




    MyReadFile.close();


}






/**
 * Print out the command prompt then read a command into the provided string buffer.
 * @param buffer Pointer to the string buffer to use.
 */
void inputCommand(string *buffer) {
    buffer->clear();


    if(MenuTitle)
    {

        //title menu
        //wrapOut(&titlemenu);

        std::cout << "Available Title Menu Commands: " << std::endl;
        std::cout << "(L)oad a save, start a (F)resh game";

    }


    //Basic commands
    if(Menu1)
    {
        //wrapOut(&Menu1Title);
        //wrapEndPara();
        //wrapOut(&Menu1Text);

        std::cout << std::endl << "Available MAIN MENU commands: " << std::endl;
        std::cout << "(M)ove, (I)nventory, (G)et, Des(c)ribe, S(a)ve ";
    }


    //Move commands
    if(MenuMove)
    {

        //wrapOut(&MenuMoveTitle);
        //wrapEndPara();
        //wrapOut(&MenuMoveText);


        std::cout << std::endl << "Available MOVEMENT commands: " << std::endl;
        std::cout<< "(N)orth, (S)outh, (E)ast, (W)est, (R)eturn to the Mainmenu ";
    }


    //Inventory commands
    if(MenuInventory)
    {

        //wrapOut(&MenuInventoryTitle);
        //wrapEndPara();
        //wrapOut(&MenuInventoryText);

        std::cout << std::endl << "Available INVENTORY commands: " << std::endl;
        std::cout << "(D)rop, E(x)amine, (R)eturn to the Mainmenu ";
    }

    //bool found = (std::find(currentState->inventory.begin(), currentState->inventory.end(), map) != currentState->inventory.end());
    //bool found2 = (std::find(currentState->inventory.begin(), currentState->inventory.end(), stick) != currentState->inventory.end());
    //bool found3 = (std::find(currentState->inventory.begin(), currentState->inventory.end(), key) != currentState->inventory.end());


    wrapOut(&quitCommand);

    wrapOut(&cursor);
    std::getline(std::cin, *buffer);
}



/**
 * Automatic room adding and exit adding
 *
 */
void addRoomsandExits(Room *selectedroom, Room *northexit, Room *southexit, Room *eastexit, Room *westexit)
{
    Room::addRoom(selectedroom);

    selectedroom->setNorth(northexit);
    selectedroom->setSouth(southexit);
    selectedroom->setEast(eastexit);
    selectedroom->setWest(westexit);

}





/**
 * Sets up the map.
 */
void initRooms() {

    auto * river = new Room(&rivername, &riverPath);

    addRoomsandExits(r1, r2, nullptr, nullptr, nullptr);
    addRoomsandExits(r2, nullptr, r1, r3, nullptr);
    addRoomsandExits(r3, nullptr, nullptr, nullptr, r2);


    //Room::addRoom(river);

    //auto * stick = new GameObject(&stickname, &stickdesc);
    //stick->setStickRoom(r2);


}

/**
 * Sets up the game state.
 */
void initState() {

    currentState = new State(Room::rooms.front());
}



/**
 * function to initialize items and their locations
 *
 */
void initItems()
{
    //std::cout <<  "test";


    //add a stick immediately to the inventory
    currentState->addInventory(stick);

    //r2->addItemToRoom2(stick);
    //currentState->getCurrentRoom()->addItemToRoom1(map);

    //add a map to room 1
    r1->addItemToRoom1(map);
    //r1->addGameObjectToRoom(map);

    //add a key to room 2
    r2->addItemToRoom2(key);

}


/**
 * function to change which menu is active
 *
 */
void changeMenu(int menuchoice)
{


    //Main Menu
    if(menuchoice == 0)
    {
        Menu1 = true;
        MenuMove = false;
        MenuInventory = false;


    }

    //Movement Menu
    if(menuchoice == 1)
    {
        Menu1 = false;
        MenuMove = true;
        MenuInventory = false;


    }

    //Inventory Menu
    if(menuchoice == 2)
    {
        Menu1 = false;
        MenuMove = false;
        MenuInventory = true;

        currentState->displayInventory();

    }

}


/**
 *
 * Set up function that calls all the setup functions
 *
 */
void initAll()
{

    MenuTitle = true;


    initWordWrap();
    initRooms();
    initState();
    initItems();

}


/**
 * Function to Get gameObject item from the room to the inventory
 *
 */
void getItem(Room* _room, GameObject* _gameObject)
{

    //boolean to check if gameObject is inside the room
    bool found;

    //boolean to check if item is inside the inventory
    bool found2;

    if(_room == r1)
    {
        found = (std::find(_room->roomitems1.begin(), _room->roomitems1.end(), _gameObject) != _room->roomitems1.end());

    }
    if(_room == r2)
    {
        found = (std::find(_room->roomitems2.begin(), _room->roomitems2.end(), _gameObject) != _room->roomitems2.end());

    }
    if(_room == r3)
    {
        found = (std::find(_room->roomitems3.begin(), _room->roomitems3.end(), _gameObject) != _room->roomitems3.end());

    }

    found2 = (std::find(currentState->inventory.begin(), currentState->inventory.end(), _gameObject) != currentState->inventory.end());

    if(found2)
    {
        //The item is already in your inventory
        wrapOut(&itemInInventory);
    }

    else if(!found)
    {
        //The item is not in this room
        wrapOut(&missingItem);

    }

    else{

        //pick up text
        wrapOut(&pickpart1);
        _gameObject->nameItem();
        wrapOut(&pickpart2);
        _room->nameRoom();
        wrapOut(&pickpart3);



        if(_room == r1)
        {
            _room->removeItemRoom1();
        }
        if(_room == r2)
        {
            _room->removeItemRoom2();
        }
        if(_room == r3)
        {
            _room->removeItemRoom3();
        }


        currentState->addInventory(_gameObject);

    }

}

/**
 * Function to drop GameObject item from the Inventory to the room
 *
 */
 void dropItem(Room* _room, GameObject* _gameObject)
{

    if((!_room->roomitems1.empty()) && _room == r1)
    {
        wrapOut(&itemInRoom);
    }
    else if((!_room->roomitems2.empty())  && _room == r2)
    {
        wrapOut(&itemInRoom);
    }
    else if((!_room->roomitems3.empty())  && _room == r3)
    {
        wrapOut(&itemInRoom);
    }

    else
    {

        //drop item text
        wrapOut(&droppart1);
        _gameObject->nameItem();
        wrapOut(&droppart2);
        _room->nameRoom();
        wrapOut(&droppart3);

        if(_room == r1)
        {
            _room->addItemToRoom1(_gameObject);
        }
        if(_room == r2)
        {
            _room->addItemToRoom2(_gameObject);
        }
        if(_room == r3)
        {
            _room->addItemToRoom3(_gameObject);
        }


        currentState->removeInventory(_gameObject);


    }




}


/**
 * REDUNDANT/LEGACY CODE
 * Code to understand game input commands and its logic
 */
void inputCommands()
{

    bool gameOver=false;
    while (!gameOver) {
        /* Ask for a command. */
        bool commandOk = false;
        inputCommand(&commandBuffer);

        /* The first word of a command would normally be the verb. The first word is the text before the first
         * space, or if there is no space, the whole string. */
        auto endOfVerb = static_cast<uint8_t>(commandBuffer.find(' '));

        /* We could copy the verb to another string but there's no reason to, we'll just compare it in place. */
        /* Command to go north. */
        if ((commandBuffer.compare(0,endOfVerb,"north") == 0) || (commandBuffer.compare(0,endOfVerb,"n") == 0)
            || (commandBuffer.compare(0,endOfVerb,"North") == 0) || (commandBuffer.compare(0,endOfVerb,"N") == 0)) {
            commandOk = true; /* Confirm command has been handled */
            /* See if there's a north exit */
            Room *northRoom = currentState->getCurrentRoom()->getNorth();

            if (northRoom == nullptr) { /* there isn't */
                wrapOut(&badExit);      /* Output the "can't go there" message */
                wrapEndPara();
            } else {                    /* There is */
                currentState->goTo(northRoom); /* Update state to that room - this will also describe it */
            }
        }


        //Command to go south
        if ((commandBuffer.compare(0,endOfVerb,"south") == 0) || (commandBuffer.compare(0,endOfVerb,"s") == 0)
            || (commandBuffer.compare(0,endOfVerb,"South") == 0) || (commandBuffer.compare(0,endOfVerb,"S") == 0)) {
            commandOk = true; /* Confirm command has been handled */
            /* See if there's a south exit */
            Room *southRoom = currentState->getCurrentRoom()->getSouth();
            if (southRoom == nullptr) { /* there isn't */
                wrapOut(&badExit);      /* Output the "can't go there" message */
                wrapEndPara();
            }
            else {                    /* There is */
                currentState->goTo(southRoom); /* Update state to that room - this will also describe it */
            }
        }

        //Command to go east
        if ((commandBuffer.compare(0,endOfVerb,"east") == 0) || (commandBuffer.compare(0,endOfVerb,"e") == 0)
            || (commandBuffer.compare(0,endOfVerb,"East") == 0) || (commandBuffer.compare(0,endOfVerb,"E") == 0)) {
            commandOk = true; /* Confirm command has been handled */
            /* See if there's a east exit */
            Room *eastRoom = currentState->getCurrentRoom()->getEast();
            if (eastRoom == nullptr) { /* there isn't */
                wrapOut(&badExit);      /* Output the "can't go there" message */
                wrapEndPara();
            } else {                    /* There is */
                currentState->goTo(eastRoom); /* Update state to that room - this will also describe it */
            }
        }

        //Command to go west
        if ((commandBuffer.compare(0,endOfVerb,"west") == 0) || (commandBuffer.compare(0,endOfVerb,"w") == 0)
            || (commandBuffer.compare(0,endOfVerb,"West") == 0) || (commandBuffer.compare(0,endOfVerb,"W") == 0)) {
            commandOk = true; /* Confirm command has been handled */
            /* See if there's a west exit */
            Room *westRoom = currentState->getCurrentRoom()->getWest();
            if (westRoom == nullptr) { /* there isn't */
                wrapOut(&badExit);      /* Output the "can't go there" message */
                wrapEndPara();
            }

            else {                    /* There is */
                currentState->goTo(westRoom); /* Update state to that room - this will also describe it */
            }
        }


        /* Quit command */
        if ((commandBuffer.compare(0,endOfVerb,"quit") == 0) || (commandBuffer.compare(0,endOfVerb,"Quit") == 0)) {
            commandOk = true;
            gameOver = true;
        }

        /* bug list command */
        if ((commandBuffer.compare(0,endOfVerb,"lsrooms") == 0)) {
            //Room *this = currentState->BugannouceRoomList();
            commandOk = true;
        }

        /* If commandOk hasn't been set, command wasn't understood, display error message */
        if(!commandOk) {
            wrapOut(&badCommand);
            wrapEndPara();
        }
    }

}



/**
 * Function to determine the char input for the switch statement
 *
 */
void inputchoice()
{


    inputCommand(&commandBuffer);

    /* The first word of a command would normally be the verb. The first word is the text before the first
     * space, or if there is no space, the whole string. */
    auto endOfVerb = static_cast<uint8_t>(commandBuffer.find(' '));


    verbChoice = commandBuffer;


    charchoice = '\0';

    //once choice is determined, apply it into a char as strings are not supported by c++ switch statements
    //North commands
    if(((commandBuffer.compare(0,endOfVerb,"north") == 0) || (commandBuffer.compare(0,endOfVerb,"n") == 0)
        || (commandBuffer.compare(0,endOfVerb,"North") == 0) || (commandBuffer.compare(0,endOfVerb,"N") == 0)) && MenuMove == true)
    {
        charchoice = 'n';
    }
    //South commands
    if(((commandBuffer.compare(0,endOfVerb,"south") == 0) || (commandBuffer.compare(0,endOfVerb,"s") == 0)
        || (commandBuffer.compare(0,endOfVerb,"South") == 0) || (commandBuffer.compare(0,endOfVerb,"S") == 0)) && MenuMove == true)
    {
        charchoice = 's';
    }
    //East commands
    if(((commandBuffer.compare(0,endOfVerb,"east") == 0) || (commandBuffer.compare(0,endOfVerb,"e") == 0)
        || (commandBuffer.compare(0,endOfVerb,"East") == 0) || (commandBuffer.compare(0,endOfVerb,"E") == 0)) && MenuMove == true)
    {
        charchoice = 'e';
    }
    //West commands
    if(((commandBuffer.compare(0,endOfVerb,"west") == 0) || (commandBuffer.compare(0,endOfVerb,"w") == 0)
        || (commandBuffer.compare(0,endOfVerb,"West") == 0) || (commandBuffer.compare(0,endOfVerb,"W") == 0)) && MenuMove == true)
    {
        charchoice = 'w';
    }
    //Quit commands
    //everything
    if((commandBuffer.compare(0,endOfVerb,"quit") == 0) || (commandBuffer.compare(0,endOfVerb,"q") == 0)
       || (commandBuffer.compare(0,endOfVerb,"Quit") == 0) || (commandBuffer.compare(0,endOfVerb,"Q") == 0))
    {
        charchoice = 'q';
    }
    //list rooms commands
    //everything
    if((commandBuffer.compare(0,endOfVerb,"lsroom") == 0) || (commandBuffer.compare(0,endOfVerb,"p") == 0))
    {
        charchoice = 'p';
    }
    //Drop commands
    //inventory
    if(((commandBuffer.compare(0,endOfVerb,"Drop") == 0) || (commandBuffer.compare(0,endOfVerb,"drop") == 0)
        || (commandBuffer.compare(0,endOfVerb,"d") == 0) || (commandBuffer.compare(0,endOfVerb,"D") == 0)) && MenuInventory == true)
    {
        charchoice = 'd';
    }
    //Get commands
    //main
    if(((commandBuffer.compare(0,endOfVerb,"Get") == 0) || (commandBuffer.compare(0,endOfVerb,"get") == 0)
        || (commandBuffer.compare(0,endOfVerb,"g") == 0) || (commandBuffer.compare(0,endOfVerb,"G") == 0)) && Menu1 == true)
    {
        charchoice = 'g';
    }
    //Inventory commands
    //main
    if(((commandBuffer.compare(0,endOfVerb,"Inventory") == 0) || (commandBuffer.compare(0,endOfVerb,"inventory") == 0)
        || (commandBuffer.compare(0,endOfVerb,"i") == 0) || (commandBuffer.compare(0,endOfVerb,"I") == 0)) && Menu1 == true)
    {
        charchoice = 'i';
    }

    //Move commands to get to the North, south, east, west commands
    //main
    if(((commandBuffer.compare(0,endOfVerb,"Move") == 0) || (commandBuffer.compare(0,endOfVerb,"move") == 0)
        || (commandBuffer.compare(0,endOfVerb,"m") == 0) || (commandBuffer.compare(0,endOfVerb,"M") == 0)) && Menu1 == true)
    {
        charchoice = 'm';
    }

    //Return command to get to the previous menu
    //move and inventory
    if(((commandBuffer.compare(0,endOfVerb,"Return") == 0) || (commandBuffer.compare(0,endOfVerb,"return") == 0)
        || (commandBuffer.compare(0,endOfVerb,"r") == 0) || (commandBuffer.compare(0,endOfVerb,"R") == 0)) && (MenuInventory || MenuMove) == true)
    {
        charchoice = 'r';
    }

    //Examine command to see the description of the game object
    //inventory
    if(((commandBuffer.compare(0,endOfVerb,"Examine") == 0) || (commandBuffer.compare(0,endOfVerb,"examine") == 0)
        || (commandBuffer.compare(0,endOfVerb,"x") == 0) || (commandBuffer.compare(0,endOfVerb,"X") == 0)) && MenuInventory == true)
    {
        charchoice = 'x';
    }

    //reannounce rooms
    //everything
    if(((commandBuffer.compare(0,endOfVerb,"Describe") == 0) || (commandBuffer.compare(0,endOfVerb,"describe") == 0)
       || (commandBuffer.compare(0,endOfVerb,"c") == 0) || (commandBuffer.compare(0,endOfVerb,"C") == 0)) && Menu1 == true)
    {
        charchoice = 'c';
    }


    //save game
    //main
    if(((commandBuffer.compare(0,endOfVerb,"Save") == 0) || (commandBuffer.compare(0,endOfVerb,"save") == 0)
        || (commandBuffer.compare(0,endOfVerb,"a") == 0) || (commandBuffer.compare(0,endOfVerb,"A") == 0)) && Menu1 == true)
    {
        charchoice = 'a';
    }





    //Integer declarations for control and testing


    sizeoffirstverb = endOfVerb;


    //appendChoice = verbChoice.substr((unsigned)sizeoffirstverb, (unsigned)commandBuffer.size());

    int a = verbChoice.size();

    int b = verbChoice.find(" ");

    int c = commandBuffer.size();

    i_rangeTest = (a - b);

    i_appendTest = (c - i_rangeTest);


    //std::cout << "Full string: " << a << ",  String space position: " << b << ", String size to space: " << i_rangeTest << ", String new size: " << i_appendTest <<std::endl;


    appendChoice.assign(commandBuffer);

    //std::cout << "new string: " << appendChoice;

    appendChoice.erase(0,  (endOfVerb + 1));

    //std::cout << " new string: aaa" << appendChoice << "a";



}


/**
 * Function to determine the char choice for gameObject switch statement
 *
 */
void gameObjectInputChoice()
{

    //after the verb
    //auto afterVerb = static_cast<uint8_t>(commandBuffer.find(' '));

    int afterVerb = (appendChoice.size());

    charchoice2 = '\0';


    //std::cout << " new string: aaa" << appendChoice << "a";

    //std::cout << i_rangeTest << std::endl;



    bool rangecheck = false;

    //test whether there is a second word
    if(i_rangeTest <= 2)
    {
        wrapOut(&outOfRange);
        wrapEndPara();
        rangecheck = true;


    }

    //char choice for items selection

    //map
    if((appendChoice.compare(0,afterVerb,"Map") == 0) || (appendChoice.compare(0,afterVerb,"map") == 0))
    {

        //std::cout<< "hi";
        charchoice2 = '1';
    }

    //stick
    if((appendChoice.compare(0,afterVerb,"Stick") == 0) || (appendChoice.compare(0,afterVerb,"stick") == 0))
    {
        charchoice2 = '2';
    }

    //key
    if((appendChoice.compare(0,afterVerb,"Key") == 0) || (appendChoice.compare(0,afterVerb,"key") == 0))
    {
        charchoice2 = '3';
    }

    //redundant code to test if there is an error
    if(rangecheck = false)
    {

        wrapOut(&spellingError);
        wrapEndPara();


    }




}



/**
 * Code to understand game input commands through switch statements and its logic
 *
 */
void switchinputcommands()
{

    bool gameOver=false;
    while (!gameOver) {

        /* Ask for a command. */
        bool commandOk = false;



        //determine which charchoice is chosen
            inputchoice();

            //switch statement to act on choice
            switch(charchoice)
            {

                    //North Command: movemenu
                    case 'n':
                    {
                        commandOk = true;
                        /* See if there's a west exit */
                        Room *northRoom = currentState->getCurrentRoom()->getNorth();

                        if (northRoom == nullptr) { /* there isn't */
                            wrapOut(&badExit);      /* Output the "can't go there" message */
                            wrapEndPara();
                        } else {                    /* There is */
                            currentState->goTo(northRoom); /* Update state to that room - this will also describe it */
                        }

                        changeMenu(0);

                        break;
                    }


                    //South Command: movemenu
                    case 's':
                    {
                        commandOk = true;
                        /* See if there's a west exit */
                        Room *southRoom = currentState->getCurrentRoom()->getSouth();
                        if (southRoom == nullptr) { /* there isn't */
                            wrapOut(&badExit);      /* Output the "can't go there" message */
                            wrapEndPara();
                        }
                        else {                    /* There is */
                            currentState->goTo(southRoom); /* Update state to that room - this will also describe it */
                        }


                        changeMenu(0);

                        break;
                    }

                    //East Command: movemenu
                    case 'e':
                    {
                        commandOk = true;
                        /* See if there's a west exit */
                        Room *eastRoom = currentState->getCurrentRoom()->getEast();
                        if (eastRoom == nullptr) { /* there isn't */
                            wrapOut(&badExit);      /* Output the "can't go there" message */
                            wrapEndPara();
                        } else {                    /* There is */
                            currentState->goTo(eastRoom); /* Update state to that room - this will also describe it */
                        }

                        changeMenu(0);

                        break;
                    }

                    //West Command: movemenu
                    case 'w':
                    {

                        commandOk = true;
                        /* See if there's a west exit */
                        Room *westRoom = currentState->getCurrentRoom()->getWest();
                        if (westRoom == nullptr) { /* there isn't */
                            wrapOut(&badExit);      /* Output the "can't go there" message */
                            wrapEndPara();
                        }

                        else {                    /* There is */
                            currentState->goTo(westRoom); /* Update state to that room - this will also describe it */
                        }

                        changeMenu(0);

                        break;
                    }


                    //Get Command: menu1
                    case 'g':
                    {
                        commandOk = true;

                        gameObjectInputChoice();

                        switch(charchoice2)
                        {

                            //get map
                            case '1':
                            {

                                getItem(currentState->getCurrentRoom(), map);
                                break;
                            }

                            //get stick
                            case '2':
                            {
                                getItem(currentState->getCurrentRoom(), stick);
                                break;
                            }

                            //get key
                            case '3':
                            {
                                getItem(currentState->getCurrentRoom(), key);
                                break;
                            }


                            default:
                            {

                                    wrapOut(&badItem);
                                    wrapEndPara();


                            }


                        }


                        changeMenu(0);

                        break;
                    }

                    //Examine Command: inventory
                    case 'x':
                    {
                        commandOk = true;

                        gameObjectInputChoice();

                        switch(charchoice2)
                        {

                            //get map
                            case '1':
                            {

                                wrapOut(&examineText);

                                map->describe();

                                break;
                            }

                                //get stick
                            case '2':
                            {
                                wrapOut(&examineText);

                                stick->describe();

                                break;
                            }

                                //get key
                            case '3':
                            {
                                wrapOut(&examineText);

                                key->describe();

                                break;
                            }


                            default:
                            {

                                    wrapOut(&badItem);
                                    wrapEndPara();
                            }


                        }

                        changeMenu(0);
                        break;
                    }

                    //Inventory Command: menu1
                    case 'i':
                    {
                        commandOk = true;
                        changeMenu(2);


                        break;
                    }


                    //move command: menu1
                    case 'm':
                    {
                        commandOk = true;
                        changeMenu(1);
                        break;
                    }



                    //Drop Command: inventory menu
                    case 'd':
                    {

                        commandOk = true;

                        gameObjectInputChoice();

                        switch(charchoice2)
                        {

                            //drop map
                            case '1':
                            {
                                dropItem(currentState->getCurrentRoom(), map);
                                break;
                            }

                            //drop stick
                            case '2':
                            {
                                dropItem(currentState->getCurrentRoom(), stick);
                                break;
                            }

                            //drop key
                            case '3':
                            {
                                dropItem(currentState->getCurrentRoom(), key);
                                break;
                            }

                            default:
                            {
                                    wrapOut(&badItem);
                                    wrapEndPara();

                            }

                        }

                        changeMenu(0);

                        break;
                    }




                //return to the main menu: movemenu and inventory menu
                case 'r':
                {
                    commandOk = true;
                    changeMenu(0);
                    break;
                }


                //Quit Command
                case 'q':
                {


                    wrapOut(&quitText);
                    wrapEndPara();

                    /* Quit command */
                        commandOk = true;
                        gameOver = true;


                    break;
                }


                //Debugger command, list Room
                case 'p':
                {
                    commandOk = true;

                    Room *northRoom = currentState->bugAnnounceRoomList();
                    Room *westRoom =  currentState->bugAnnounceRoomList();
                    Room *eastRoom =  currentState->bugAnnounceRoomList();
                    Room *southRoom = currentState->bugAnnounceRoomList();

                    changeMenu(0);

                    break;
                }

                //reannounce current state and room describe
                case 'c':
                {
                    commandOk = true;
                    currentState->announceLoc();

                    break;
                }

                //save the current game state
                case 'a':
                {
                    commandOk = true;


                    wrapOut(&saveText);
                    wrapEndPara();


                    //std::cout << "test";

                    //save the game
                    saveGame();

                    break;
                }


                //if there is no proper selection or input was done incorrectly
                default:
                {

                    /* If commandOk hasn't been set, command wasn't understood, display error message */
                        wrapOut(&badCommand);
                        wrapEndPara();
                }


            }


        }


}




/**
 * Function to create a save and load menu
 *
 */
void saveandloadMenu()
{


    //game title
    wrapOut(&gametitle);
    wrapEndPara();

    //understand the input command to enter the game
    bool slMenuCheck=false;
    while (!slMenuCheck) {

        /* Ask for a command. */
        bool commandOk = false;
        inputCommand(&saveandloadmenuCommandBuffer);

        /* The first word of a command would normally be the verb. The first word is the text before the first
         * space, or if there is no space, the whole string. */
        auto endOfVerb = static_cast<uint8_t>(saveandloadmenuCommandBuffer.find(' '));



        /* Command to load a save. */
        if ((saveandloadmenuCommandBuffer.compare(0,endOfVerb,"load") == 0) || (saveandloadmenuCommandBuffer.compare(0,endOfVerb,"l") == 0)
            || (saveandloadmenuCommandBuffer.compare(0,endOfVerb,"Load") == 0) || (saveandloadmenuCommandBuffer.compare(0,endOfVerb,"L") == 0)) {
            commandOk = true; /* Confirm command has been handled */


            //read and open load file
            slMenuCheck = true;
            MenuTitle = false;


            wrapOut(&loadText);
            wrapEndPara();

            //load game
            loadGame();

            loadcheck= true;

            changeMenu(0);

        }


        //Command to go open a fresh game
        else if ((saveandloadmenuCommandBuffer.compare(0,endOfVerb,"fresh") == 0) || (saveandloadmenuCommandBuffer.compare(0,endOfVerb,"f") == 0)
            || (saveandloadmenuCommandBuffer.compare(0,endOfVerb,"Fresh") == 0) || (saveandloadmenuCommandBuffer.compare(0,endOfVerb,"F") == 0)) {
            commandOk = true; /* Confirm command has been handled */


            //open game without loading
            slMenuCheck = true;
            MenuTitle = false;

            wrapOut(&freshText);
            wrapEndPara();

            changeMenu(0);

        }

        else if((saveandloadmenuCommandBuffer.compare(0,endOfVerb,"quit") == 0) || (saveandloadmenuCommandBuffer.compare(0,endOfVerb,"q") == 0)
           || (saveandloadmenuCommandBuffer.compare(0,endOfVerb,"Quit") == 0) || (saveandloadmenuCommandBuffer.compare(0,endOfVerb,"Q") == 0))
        {
            slMenuCheck = true;
            MenuTitle = false;

            wrapOut(&quitText);
            wrapEndPara();

            /* Quit command */
            commandOk = true;


            exit(0);

        }


        //no proper input
        else
        {
            wrapOut(&badInput);    //bad input
            wrapEndPara();


        }


    }


}





/**
 * The main game loop.
 */
void gameLoop() {

    //inputCommands();  //legacy code

    switchinputcommands();


    /* //incorporated into the switch input commands
    if(true)
    {
        gameObjectInputChoice();
    }
    */

}




/************************************************
 *                                              *
 *                    main                      *
 *                                              *
 ************************************************/
int main() {




    //Initialize all init functions
    //initAll();



    MenuTitle = true;

    initWordWrap();
    initRooms();
    initState();



    //start the title menu
    saveandloadMenu();


    //check if load was selected
    if(loadcheck == false)
    {
        initItems();

        //Initialize and start the game, announce where the user is
        currentState->announceLoc();
    }


    //start the gameloop
    gameLoop();


    return 0;
}