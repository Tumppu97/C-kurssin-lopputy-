#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <cstdlib>

// Struct to define the stats of the Character
struct Character {
    std::string name;
    int health;
    int baseHealth;
    int attack;
    int gold;
};
// Struct to define the monster
struct Monster {
    std::string name;
    int health;
    int attack;
};

// List of the monsters to be defeated in the game and their stats
std::vector<Monster> monsters = {
    {"Rat", 50, 5},
    {"Bear", 100, 10},
    {"Soldier", 150, 15},
    {"General", 200, 20},
    {"Devil", 250, 25}
};
// Generate random number to figure out if the player/monster actually hits
int getRandomNumber(int min, int max) {
    return min + rand() % (max - min + 1);
}

bool battle(Character& character, Monster& monster) {
    int playerDamage = 0;
    int monsterDamage = 0;

    for (int round = 1; round <= 10; round++) {
        // Simulate the player's attack
        int playerAttack = character.attack;
        int playerRoll = getRandomNumber(1, 20);
        if (playerRoll >= 10) {
            int damage = playerAttack;
            monster.health -= damage;
            playerDamage += damage; // Track player's dealt damage
            std::cout << "Round " << round << "\n";
            std::cout << character.name << " attacks " << monster.name << " and hits " << monster.name << " for " << damage << " damage." << std::endl;
        } else {
            std::cout << "Round " << round << "\n";
            std::cout << character.name << " attacks " << monster.name << " and misses." << std::endl;
        }

        if (monster.health <= 0) {
            std::cout << "You defeated " << monster.name << "!" << std::endl;
            character.gold += 10; // Award gold for defeating the monster
            return true; // Player wins
        }

        // Simulate the monster's attack
        int monsterAttack = monster.attack;
        int monsterRoll = getRandomNumber(1, 20);
        if (monsterRoll >= 10) {
            int damage = monsterAttack;
            character.health -= damage;
            monsterDamage += damage; // Track the monster's dealt damage
            std::cout << monster.name << " attacks " << character.name << " and hits " << character.name << " for " << damage << " damage." << std::endl;
        } else {
            std::cout << monster.name << " attacks " << character.name << " and misses." << std::endl;
        }

        if (character.health <= 0) {
            std::cout << "You were defeated by " << monster.name << "!" << std::endl;
            return false; // Player loses
        }
    }

    // Compare total damage dealt
    if (playerDamage > monsterDamage) {
        std::cout << "You dealt more damage to " << monster.name << " and won the battle!" << std::endl;
        character.gold += 10; // Award gold for defeating the monster
        return true; // Player wins in terms of damage dealt
    } else if (playerDamage < monsterDamage) {
        std::cout << monster.name << " dealt more damage to you, and you barely escaped with your life!" << std::endl;
        character.health = 1; // Player survives with 1 health
        return false; // Player loses in terms of damage dealt
    } else {
        std::cout << "It's a draw! " << monster.name << " flees, and you remain alive!" << std::endl;
        return true; // Draw, but player survives
    }

    // If player and monster are still alive, no need for a draw message.
    return true;
}


void trainStats(Character& character) {
    if (character.gold >= 10) {
        character.gold -= 10;
        character.baseHealth += 100; // Increase base health
        character.health = character.baseHealth; // Set current health to the updated base health
        character.attack += 4; // Train attack
        std::cout << "You've trained your stats! Health and attack have been increased!" << std::endl;
    } else { // The player doesn't have enough money to train stats
        std::cout << "You don't have enough gold to train your stats." << std::endl;
    }
}


int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    
    Character player;

    // Start the game and ask for their name
    std::cout << "Welcome, adventurer! What is your name?" << std::endl;
    std::cin >> player.name;

    // Initialize the character's stats
    player.health = 100;
    player.baseHealth = player.health; // Store base health
    player.attack = 10;
    player.gold = 0;

    // Set a time limit for the game
    const int gameDurationSeconds = 600; // 10 minutes
    std::time_t startTime = std::time(nullptr);

    bool inBattle = false; // Flag to track if the player is in battle

    int monsterIndex = 0; // Track the current monster

    while (monsterIndex < monsters.size()) {
        Monster currentMonster = monsters[monsterIndex];

        if (!inBattle) {
            std::cout << "Be prepared for battle, " << player.name << "!" << std::endl;
            std::cout << "Health: " << player.health << std::endl;
            std::cout << "Attack: " << player.attack << std::endl;
            std::cout << "Gold: " << player.gold << std::endl;

            char choice;
            std::cout << "Go to battle? (Y) Rest for Health (R) Train your stats (T): ";
            std::cin >> choice;

            if (choice == 'Y' || choice == 'y') {
                inBattle = true; // Go to battle
            } else if (choice == 'R' || choice == 'r') {
                player.health = player.baseHealth; // Rest for health
            } else if (choice == 'T' || choice == 't') {
                trainStats(player); // Train stats
            } else {
                std::cout << "Invalid choice. Please enter 'Y', 'N', or 'T'." << std::endl;
            }
        } else {
            bool playerWins = battle(player, currentMonster);

            if (playerWins) {
                std::cout << "You won the battle!" << std::endl;
                inBattle = false;
                monsterIndex++;
                if (monsterIndex == monsters.size()) {
                std::cout << "Congratulations! You have defeated the Devil. Game complete!" << std::endl;
                break;
            }
            } else {
                std::cout << "You lost the battle." << std::endl;

                char choice;
                std::cout << "Do you want to rest and try again? (Y/N): ";
                std::cin >> choice;

                if (choice == 'Y' || choice == 'y') {
                    player.health = player.baseHealth; // Reset health to base after losing
                    inBattle = false;
                } else {
                    break; // Exit the game if the player chooses not to rest
                }
            }
        }

        std::time_t currentTime = std::time(nullptr);
            
            //If the game takes longer than ten minutes end it
        if (currentTime - startTime >= gameDurationSeconds) {
            std::cout << "Game over. Time's up!" << std::endl;
            break;
        }
    }

    return 0;
}
