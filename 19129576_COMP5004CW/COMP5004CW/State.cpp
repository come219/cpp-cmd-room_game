//
// Created by DrMark on 10/2/2017.
//
//Sebastian St Johnston
//19129576
//Room MUD game Coursework

#include "State.h"
#include <iostream>

/**
 * Current state of the game.
 */

/**
 * Display the description of the room the player is in. */

void State::announceLoc() const {
    this->currentRoom->describe();
}




/**
 *
 * Function to display inventory
 *
 */
void State::displayInventory()
{

    //empty inventory
    if(State::inventory.empty())
    {
        std::cout << "Your inventory is empty!";
    }

    //one inventory
    else if(State::inventory.size() == 1)
    {
        std::cout <<"You have " << State::inventory.size() << " item in your inventory." << std::endl;
        for (auto v : inventory)
            v->nameItem();

    }

    //more than one inventory
    else
    {
        std::cout <<"You have " << State::inventory.size() << " items in your inventory." << std::endl;

        for (auto v : inventory)
        {
            v->nameItem();

            if(v != inventory.back())
            {
                std::cout<<", ";
            }

        }


    }
    std::cout << std::endl;


}



/**
 * Function to add gameObject to Inventory list
 *
 */
void State::addInventory(GameObject *_gameObject)
{

    State::inventory.push_back(_gameObject);


}


/**
 * Function to remove gameObject from Inventory list
 */
void State::removeInventory(GameObject *_gameObject)
{

    State::inventory.remove(_gameObject);

}




/**
 * Constructor.
 * @param startRoom Pointer to the room to start in.
 */
State::State(Room *startRoom) : currentRoom(startRoom) {};

/**
 * Move to a specified room and print its description.
 * @param target Pointer to the room to move to.
 */
void State::goTo(Room *target) {
    this->currentRoom = target;
    this->announceLoc();
}

/**
 * Return a pointer to the current room.
 * @return Pointer to the current room.
 */
Room* State::getCurrentRoom() const {
    return this->currentRoom;
}

/**
 * Bug test function to show all rooms around
 *
 */
Room* State::bugAnnounceRoomList(){

    std::cout << this->currentRoom << std::endl;
    return 0;
}

std::string State::currentRoomText() {

    return this->currentRoom->getRoomName();

}

