//
// Created by DrMark on 10/2/2017.
//
//Sebastian St Johnston
//19129576
//Room MUD game Coursework

#ifndef TEXTADV_ROOM_H
#define TEXTADV_ROOM_H

#include <string>
#include <forward_list>
#include <list>
#include "GameObject.h"
#include "strings.h"
#include <iostream>

using std::string;

/**
 * Represents a room (accessible location in the game).
 */
class Room {
    /**
     * Short name used as a header.
     */
    const string* name;

    /**
     * Full description of the room.
     */
    const string* description;
    /**
     * Pointer to room that is north of this one.
     */
    Room* north;

    /**
     * Pointer to room that is south of this one.
     */
    Room* south;

    /**
     * Pointer to room that is east of this one.
     */
    Room* east;

    /**
     * Pointer to room that is west of this one.
     */
    Room* west;

    //Room* roomObject;




public:
    /**
     * Constructs a new Room.
     * @param _name Name of the room.
     * @param _desc Description of the room.
     */
    Room(const string *_name, const string *_desc);


    //void addGameObjectToRoom(GameObject* _gameObject);

    /**
     * Removes a destroyed room from the global list if it's there.
     */
    ~Room();

    /**
     * Outputs the name and description of the room
     * in standard format.
     */
    void describe() const;
    void nameRoom() const;


    /**
     * List storing all rooms that have been registered via addRoom().
     */
    static std::list<Room*> rooms;


    //list of each gameobject in each room
    std::list<GameObject*> roomitems1;
    std::list<GameObject*> roomitems2;
    std::list<GameObject*> roomitems3;

    //std::list<GameObject*> *roomObject;


    //functions to add gameobject to each list for the room
    void addItemToRoom1(GameObject* _gameObject);
    void addItemToRoom2(GameObject* _gameObject);
    void addItemToRoom3(GameObject* _gameObject);


    //functions to remove gameobject from each list of the room
    void removeItemRoom1();
    void removeItemRoom2();
    void removeItemRoom3();


    //get and set
    void getRoomList();



    //get room name
    std::string getRoomName();




    /**
     * Creates a new Room with the given parameters and register it with the static list.
     * @param _name Name of the room.
     * @param _desc Description of the room.
     */
    static Room* addRoom(const string* _name, const string* _desc);
    static void addRoom(Room* room);

    //Function to know and do about north
    Room* getNorth() const;
    void setNorth(Room* _north);

    //Function to know and do about south
    Room* getSouth() const;
    void setSouth(Room* _south);


    //Function to know and do about east
    Room* getEast() const;
    void setEast(Room* _east);

    //Function to know and doabout east
    Room *getWest() const;
    void setWest(Room* _west);



};

#endif //TEXTADV_ROOM_H
