#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

// Базовый класс персонажа
class Character {
protected:
    string name;
    int health;
    int attackPower;
    int defense;

public:
    Character(const string& name, int health, int attackPower, int defense)
        : name(name), health(health), attackPower(attackPower), defense(defense) {
    }

    virtual void attack(Character& target) {
        int damage = attackPower - target.defense;
        damage = (damage > 0) ? damage : 1; // Минимальный урон — 1
        target.health -= damage;
        cout << name << " атакует " << target.getName() << " на " << damage << " урона!" << endl;
    }

    bool isAlive() const {
        return health > 0;
    }

    string getName() const {
        return name;
    }

    int getHealth() const {
        return health;
    }

    virtual void specialAbility(Character& target) = 0; // Чисто виртуальный метод
};

// Класс игрока
class Player : public Character {
private:
    int potions; // Количество зелий

public:
    Player(const string& name, int health, int attackPower, int defense)
        : Character(name, health, attackPower, defense), potions(3) {
    }

    void usePotion() {
        if (potions > 0) {
            health += 20;
            potions--;
            cout << name << " использовал зелье и восстановил 20 здоровья. Осталось зелий: " << potions << endl;
        }
        else {
            cout << "Зелий больше нет!" << endl;
        }
    }

    void specialAbility(Character& target) override {
        cout << name << " использует специальную способность! Урон увеличен вдвое." << endl;
        int originalAttackPower = attackPower;
        attackPower *= 2;
        attack(target);
        attackPower = originalAttackPower;
    }
};

// Класс врага
class Enemy : public Character {
public:
    Enemy(const string& name, int health, int attackPower, int defense)
        : Character(name, health, attackPower, defense) {
    }

    void specialAbility(Character& target) override {
        cout << name << " использует специальную способность! Урон увеличен вдвое." << endl;
        int originalAttackPower = attackPower;
        attackPower *= 2;
        attack(target);
        attackPower = originalAttackPower;
    }
};

// Функция битвы
void battle(Player& player, Enemy& enemy) {
    while (player.isAlive() && enemy.isAlive()) {
        cout << "\nВаше здоровье: " << player.getHealth() << endl;
        cout << "Здоровье врага (" << enemy.getName() << "): " << enemy.getHealth() << endl;
        cout << "1. Атаковать\n2. Использовать зелье\n3. Специальная способность\nВыберите действие: ";
        int choice;
        cin >> choice;

        switch (choice) {
        case 1:
            player.attack(enemy);
            break;
        case 2:
            player.usePotion();
            break;
        case 3:
            player.specialAbility(enemy);
            break;
        default:
            cout << "Некорректный выбор!" << endl;
            continue;
        }

        if (enemy.isAlive()) {
            enemy.specialAbility(player);
        }
    }

    if (player.isAlive()) {
        cout << "\nВы победили врага " << enemy.getName() << "!" << endl;
    }
    else {
        cout << "\nВы погибли в бою..." << endl;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    srand(time(0));

    cout << "Добро пожаловать в текстовую RPG!" << endl;
    cout << "Выберите класс персонажа:\n1. Воин (высокая защита)\n2. Маг (сильная атака)\n3. Лучник (сбалансированный персонаж)\nВаш выбор: ";
    int choice;
    cin >> choice;

    Player* player = nullptr;
    switch (choice) {
    case 1:
        player = new Player("Воин", 100, 15, 10);
        break;
    case 2:
        player = new Player("Маг", 80, 20, 5);
        break;
    case 3:
        player = new Player("Лучник", 90, 18, 8);
        break;
    default:
        cout << "Некорректный выбор! По умолчанию выбран Лучник." << endl;
        player = new Player("Лучник", 90, 18, 8);
        break;
    }

    Enemy enemy1("Гоблин", 50, 10, 3);
    Enemy enemy2("Орк", 80, 15, 5);
    Enemy enemy3("Дракон", 120, 20, 8);

    battle(*player, enemy1);
    if (player->isAlive()) battle(*player, enemy2);
    if (player->isAlive()) battle(*player, enemy3);

    if (player->isAlive()) {
        cout << "\nПоздравляем! Вы победили всех врагов и выиграли игру!" << endl;
    }
    else {
        cout << "\nИгра окончена. Попробуйте снова!" << endl;
    }

    delete player;
    return 0;
}
