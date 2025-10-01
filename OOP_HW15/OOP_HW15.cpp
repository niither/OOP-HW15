#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Ability {
public:
    virtual ~Ability() {}
    virtual string getName() const = 0;
    virtual bool isFly() const {
        return false;
    }
};

class Flyable : public Ability {
public:
    bool isFly() const override {
        return true;
    }
    virtual void fly() const = 0;
};

class SuperStrength : public Ability {
public:
    virtual void fight() const = 0;
};

class JetpackFlyable : public Flyable {
public:
    string getName() const override { 
        return "Jetpack Flight"; 
    }
    void fly() const override { 
        cout << "Flies with jetpack\n"; 
    }
};

class ForceFlight : public Flyable {
public:
    string getName() const override { 
        return "Force Flight"; 
    }
    void fly() const override { 
        cout << "Flies with their force\n"; 
    }
};

class ChuBaccaStrength : public SuperStrength {
public:
    string getName() const override { return "ChuBacca superStrength"; }
    void fight() const override { cout << "Chubacca uses his super strenght\n"; }
};

class Character {
protected:
    string name;
    string race;
    bool goodOrEvil;
    vector<Ability*> abilities;
public:
    Character(string name, string race, bool goodOrEvil) : name(name), race(race), goodOrEvil(goodOrEvil) {}
    virtual ~Character() {}

    void addAbility(Ability* ability) {
        abilities.push_back(ability);
    }
    string getName() const {
        return name; }
    string getRace() const {
        return race; 
    }
    bool isGood() const {
        return goodOrEvil; 
    }

    void showAbilities() const {
        if (abilities.empty()) cout << "  (немає здібностей)\n";
        for (auto ability : abilities) {
            cout << " - " << ability->getName() << "\n";
        }
    }

    bool canFly() const {
        for (auto ability : abilities) {
            if (ability->isFly()) {
                return true;
            }
        }
        return false;
    }
};

class LukeSkywalker : public Character {
public:
    LukeSkywalker() : Character("Luke Skywalker", "Human", true) {
        addAbility(new ForceFlight());
    }
};

class DarthVader : public Character {
public:
    DarthVader() : Character("Darth Vader", "Human (Sith)", false) {
        addAbility(new ForceFlight());
    }
};

class Yoda : public Character {
public:
    Yoda() : Character("Yoda", "Something green", true) {
        addAbility(new ForceFlight());
    }
};

class BobaFett : public Character {
public:
    BobaFett() : Character("Boba Fett", "Human", false) {
        addAbility(new JetpackFlyable());
    }
};

class Chubacca : public Character {
public:
    Chubacca() : Character("Chubacca", "Something with hair", true) {
        addAbility(new ChuBaccaStrength());
    }
};

int main() {
    vector<Character*> characters;
    characters.push_back(new LukeSkywalker());
    characters.push_back(new DarthVader());
    characters.push_back(new Yoda());
    characters.push_back(new BobaFett());
    characters.push_back(new Chubacca());

    cout << "All characters: \n";
    for (auto character : characters) {
        cout << character->getName() << ", "
            << character->getRace() << ", "
            << (character->isGood() ? "Good" : "Evil") << "\n";
        cout << "Their Abilities:\n";
        character->showAbilities();
    }
    cout << "Characters who can fly:\n";
    for (auto character : characters) {
        if (character->canFly()) {
            cout << character->getName() << " can fly\n";
        }
    }

    for (auto character : characters) delete character;
}
