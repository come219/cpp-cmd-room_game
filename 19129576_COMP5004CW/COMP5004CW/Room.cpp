//
// Created by DrMark on 10/2/2017.
//
//Sebastian St Johnston
//19129576
//Room MUD game Coursework

#include "Room.h"
#include "wordwrap.h"


/**
 * Stores a static list of all rooms.
 */
std::list<Room*> Room::rooms;


/**
 *
 * Store a static list of all items in the room

std::list<GameObject*> Room::roomitems1;
std::list<GameObject*> Room::roomitems2;
std::list<GameObject*> Room::roomitems3;
 */


/**
 * Store an item into room 1
 *
 */
void Room::addItemToRoom1(GameObject* _gameObject)
{


    //std::cout <<  "test";
    roomitems1.push_back(_gameObject);

    //roomObject = _selectedRoom;

}

/**
 * Store an item into room 2
 *
 */
void Room::addItemToRoom2(GameObject* _gameObject)
{

    Room::roomitems2.push_back(_gameObject);

}

/**
 * Store an item into room 3
 *
 */
void Room::addItemToRoom3(GameObject* _gameObject)
{

    Room::roomitems3.push_back(_gameObject);

}

/**
 * Remove an item from room 1
 *
 */
void Room::removeItemRoom1()
{

    Room::roomitems1.pop_back();

}

/**
 * Remove an item from room 2
 *
 */
void Room::removeItemRoom2()
{

    Room::roomitems2.pop_back();

}

/**
 * Remove an item from room 3
 *
 */
void Room::removeItemRoom3()
{
    Room::roomitems3.pop_back();
}



/**
 * Function to name the room
 *
 */
void Room::nameRoom() const
{
    wrapOut(this->name);

}

/*
void Room::addGameObjectToRoom(GameObject* _gameObject)
{

    //this->roomObject->push_back(_gameObject);
}
*/



/**
 * Room default constructor.
 * @param _name Room's name.
 * @param _desc Room's description.
 */
Room::Room(const string* _name, const string *_desc) :
        name(_name), description(_desc), north(nullptr), south(nullptr), east(nullptr), west(nullptr)  {};



/**
 * Remove destroyed rooms from the static list.
 */
Room::~Room() {
    Room::rooms.remove(this);
}




/**
 * Prints the description of a room (the name and long description)
 */
void Room::describe() const {
    wrapOut(this->name);
    wrapEndPara();
    wrapOut(this->description);
    wrapEndPara();


    //describe room 1 list of gameobjects
    if(!this->name->compare(r1name))
    {

        if(!Room::roomitems1.empty())
        {
            std::cout << "A ";

            for (auto v : roomitems1)
                v->nameItem();

            wrapOut(&itemcheck);
            wrapEndPara();
        }
    }

    //describe room 2 list of gameobjects
    if(!this->name->compare(r2name))
    {

        if(!Room::roomitems2.empty())
        {
            std::cout << "A ";

            for (auto v : roomitems2)
                v->nameItem();

            wrapOut(&itemcheck);
            wrapEndPara();
        }
    }

    //describe room 3 list of gameobjects
    if(!this->name->compare(r3name))
    {

        if(!Room::roomitems3.empty())
        {
            std::cout << "A ";

            for (auto v : roomitems3)
                v->nameItem();

            wrapOut(&itemcheck);
            wrapEndPara();
        }
    }




}

/**
 * Statically creates a room and then adds it to the global list.
 * @param _name Name for the new room.
 * @param _desc Description for the new room.
 * @return A pointer to the newly created room.
 */
Room* Room::addRoom(const string* _name, const string *_desc) {
    auto *newRoom = new Room(_name, _desc);
    Room::rooms.push_back(newRoom);
    return newRoom;
}

/**
* Adds an existing room to the static list.
 * @param room Pointer to the room to add.
 * @return
 */
void Room::addRoom(Room* room) {
    Room::rooms.push_back(room);
}

/**
 * Gets the north exit of a room.
 * @return The room that is north of this one, or NULL if there is no exit.
 */
Room* Room::getNorth() const {
    return this->north;
}

/**
 * Sets the north exit of a room.
 * @param _north Pointer to the room to be north of this one.
 */
void Room::setNorth(Room* _north) {
    this->north = _north;
}


/**
 * Gets the south exit of a room.
 * @return The room that is south of this one, or NULL if there is no exit.
 */
Room *Room::getSouth() const {
    return this->south;
}

/**
 * Sets the south exit of a room.
 * @param _south Pointer to the room to be north of this one.
 */
void Room::setSouth(Room *_south) {
    this->south = _south;
}


/**
 * Gets the East exit of a room.
 * @return The room that is south of this one, or NULL if there is no exit.
 */
Room *Room::getEast() const {
    return this->east;
}

/**
 * Sets the East exit of a room.
 * @param _south Pointer to the room to be north of this one.
 */
void Room::setEast(Room *_east) {
    this->east = _east;
}


/**
 * Gets the West exit of a room.
 * @return The room that is south of this one, or NULL if there is no exit.
 */
Room *Room::getWest() const {
    return this-> west;
}

/**
 * Sets the West exit of a room.
 * @param _south Pointer to the room to be north of this one.
 */
void Room::setWest(Room * _west) {

    this->west = _west;

}

void Room::getRoomList() {



}

std::string Room::getRoomName() {

    return *this->name;
}






