#include <iostream>
#include <memory>
#include <vector>
#include <stdexcept> 
#include "character.h"
#include "logger.h"
using namespace std;

void equip_test1(shared_ptr<Character> c1) {
    try {
        shared_ptr<Character> decorated = c1;
        decorated = make_shared<Armor>(decorated);
        decorated = make_shared<Boots>(decorated);
        decorated = make_shared<Sword>(decorated);
        cout << decorated->getDescription()
            << " | Attack: " << decorated->getAttack()
            << " | Speed: " << decorated->getSpeed()
            << " | Defense: " << decorated->getDefense() << endl;
    } catch (const invalid_argument& e) {
        
        cout << "Invalid equip: " << e.what() << endl;
       
        Logger::getInstance()->log("[Fail to Equip] ");
    }
}

void equip_test2(shared_ptr<Character> c1) {
    try {
        shared_ptr<Character> decorated = c1; 
        decorated = make_shared<Armor>(decorated);
        decorated = make_shared<Bow>(decorated);
        cout << decorated->getDescription()
            << " | Attack: " << decorated->getAttack()
            << " | Speed: " << decorated->getSpeed()
            << " | Defense: " << decorated->getDefense() << endl;
    } catch (const invalid_argument& e) {
       
        cout << "Invalid equip: " << e.what() << endl;
       
        Logger::getInstance()->log("[Fail to Equip] ");
    }
}

void equip_test3(shared_ptr<Character> c1) {
    try {
        shared_ptr<Character> decorated = c1; 
        decorated = make_shared<Boots>(decorated);
        decorated = make_shared<Staff>(decorated);
        cout << decorated->getDescription()
            << " | Attack: " << decorated->getAttack()
            << " | Speed: " << decorated->getSpeed()
            << " | Defense: " << decorated->getDefense() << endl;
    } catch (const invalid_argument& e) {
        
        cout << "Invalid equip: " << e.what() << endl;
        
        Logger::getInstance()->log("[Fail to Equip] ");
    }
}

void doTest() {
    vector<shared_ptr<Character>> players;
    players.push_back(make_shared<Knight>());
    players.push_back(make_shared<Wizard>());
    players.push_back(make_shared<Archer>());

    for(auto player: players){
        cout << "-------------------------------------------------------------" << endl;
        equip_test1(player); 
        equip_test2(player);
        equip_test3(player);
    }
    cout << "-------------------------------------------------------------" << endl;

}

struct Student{
    string name;
    Student(string name): name(name) {};
    Student() = delete;
    ~Student() { cout << "Delete Student " << name << endl; }
};


int main(int argc, const char *argv[]) {
    doTest();
    return 0;
}