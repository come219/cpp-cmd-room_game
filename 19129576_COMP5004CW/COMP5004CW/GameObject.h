//Sebastian St Johnston
//19129576
//Room MUD game Coursework

#ifndef TEXTADV_GAMEOBJECT_H
#define TEXTADV_GAMEOBJECT_H

#include <string>
#include <list>



using std::string;

class GameObject {

    /**
   * Short name of the game object
   */
    const string* name;

    /**
     * Full description of the game object
     */
    const string* description;

    /**
     * Key word of the game object
     */
    const string* keyword;

    //A Game Object called stick
    //GameObject *stick;


    //Room *chosenroom;


public:

    //GameObject Constructor
    GameObject(const string* _name, const string* _desc, const string* _keyword);


    //GameObject deconstructor
    ~GameObject();

    /**
    * Outputs the name and description of the game object
    * in standard format.
    */
    void describe() const;

    void nameItem() const;





    /**
     * Creates a new gameObject with the given parameters and register it with the static list.
     * @param _name Name of the room.
     * @param _desc Description of the room.
     */
    static GameObject* addGameObject(const string* _name, const string* _desc);


};


#endif //TEXTADV_GAMEOBJECT_H
