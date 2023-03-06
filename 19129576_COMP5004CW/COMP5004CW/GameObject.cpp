//Sebastian St Johnston
//19129576
//Room MUD game Coursework

#include "GameObject.h"
#include "wordwrap.h"
#include "State.h"





/**
 * Game Object's default constructor.
 * @param _name Game Object's Short name.
 * @param _desc Game Object's description.
 */
GameObject::GameObject(const string *_name, const string *_desc, const string* _keyword)    :
            name(_name), description(_desc), keyword(_keyword) {}

/**
 * Remove destroyed game objects from the static list.
 */
GameObject::~GameObject() {

}




/**
 * Outputs the name and description of the game object
 * in standard format.
 */
void GameObject::describe() const {

    wrapOut(this->name);
    wrapEndPara();
    wrapOut(this->description);
    wrapEndPara();

}

void GameObject::nameItem() const{

    wrapOut(this->name);

}
