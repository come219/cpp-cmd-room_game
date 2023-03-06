//
// Created by DrMark on 10/2/2017.
//
//Sebastian St Johnston
//19129576
//Room MUD game Coursework


#ifndef TEXTADV_STATE_H
#define TEXTADV_STATE_H


#include "Room.h"
#include "GameObject.h"
#include <iostream>
#include <iterator>


class State {
    Room *currentRoom;





public:
    explicit State(Room *startRoom);
    void goTo(Room *target);
    void announceLoc() const;
    Room* getCurrentRoom() const;

    std::string currentRoomText();


    //bug test function to display all rooms around
    Room* bugAnnounceRoomList();




    /**
   * List storing all the gameobjects that have been registered via addGameObject.
   */
    std::list<GameObject*> inventory;


    //display the inventory items
    void displayInventory();


    //add item to inventory
    void addInventory(GameObject *_gameObject);


    //remove item from inventory
    void removeInventory(GameObject *_gameObject);



};


#endif //TEXTADV_STATE_H
