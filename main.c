#include <stdio.h>
#include <stdlib.h>
#include <time.h>   // Required for rand() and time()

// --- GLOBAL CHARACTER ATTRIBUTES ---
// These variables are globally defined so all functions can access and modify them.
#include <stdio.h>
#include <stdlib.h>
#include <time.h>   // Required for rand() and time()

// --- GLOBAL CHARACTER ATTRIBUTES ---
// These variables are globally defined so all functions can access and modify them.
int health;    // Health (0-100)
int energy;    // Energy (0-100)
int inventory; // Inventory (Food, Count)
char command;  // Player's command input

// --- FUNCTION PROTOTYPES ---
void initializeGame(); 
void showStats();      
void handleHunt();     
void handleShelter();  
void handleRest();     
void handleDanger();   
void handleSecret();   


int main(int argc, char *argv[]) {
    
    // Initialize the random number generator
    srand(time(NULL));

    // Start the game and set initial values
    initializeGame();
    printf("--- Survival Simulator Started ---\n");
    showStats();

    // --- MAIN GAME LOOP (DO-WHILE mandatory) ---
    do {
        printf("\nEnter Command\nA (Hunt)\nS (Hide)\nE (inventory)\nR (Rest)\nF (perceive the danger)\nP (sneaky walk)\nX (exit)\n ");
        
        // Read the user command
        if (scanf(" %c", &command) != 1) { 
            printf("Invalid input. Please try again.\n");
            while (getchar() != '\n'); // Clear the input buffer
            continue;
        }

        // Convert command to uppercase for case-insensitivity
        if (command >= 'a' && command <= 'z') {
            command = command - ('a' - 'A');
        }

        // --- COMMAND SYSTEM (SWITCH-CASE mandatory) ---
        switch (command) {
            case 'A': // Hunt
                handleHunt();
                break;
            case 'S': // Find Shelter
                handleShelter();
                break;
            case 'E': // View Inventory (Stats)
                showStats();
                break;
            case 'R': // Rest
                handleRest();
                break;
            case 'F': // Simulate Area Danger Series
                handleDanger();
                break;
            case 'P': // Encrypted Progression
                handleSecret();
                break;
            case 'X': // Exit
                printf("Simulation Ended. Goodbye!\n");
                break;
            default:
                printf("Invalid command. Please enter a valid command.\n");
                break;
        }
        
        // Check character's death condition
        if (health <= 0) {
            printf("\n!!! YOU DIED. Health: %d !!!\n", health);
            command = 'X'; // End the game loop
        }

    } while (command != 'X'); // Continue until Exit command is given

    return 0;
}

// =================================================================
// --- FUNCTION IMPLEMENTATIONS ---
// =================================================================

void initializeGame() {
    health = 100;
    energy = 100;
    inventory = 0; 
}

void showStats() {
    printf("\n--- STATUS ---\n");
    printf("Health: %d/100\n", health);
    printf("Energy: %d/100\n", energy);
    printf("Inventory (Food): %d units\n", inventory);
    printf("--------------\n");
}

void handleHunt() {
    // ARITHMETIC OPERATORS: Energy Loss
    int energyCost = (rand() % 10) + 10; 
    energy = energy - energyCost; 
    
    printf("You went hunting. Lost %d energy. Remaining energy: %d\n", energyCost, energy);

    if (energy < 10) {
        printf("You are too tired. Continuing to hunt is difficult.\n");
    }

    // LOGICAL OPERATORS: Chance of Finding Food OR Getting Injured
    int successChance = rand() % 100; 

    // Success: Energy MUST be high AND chance MUST be sufficient (&& operator)
    if ((energy > 30) && (successChance > 40)) { 
        int foodGained = (rand() % 3) + 1;
        inventory = inventory + foodGained;
        printf("Success! You found %d units of food.\n", foodGained);
    } 
    // Failure/Injury: Energy MUST be low OR chance MUST be very low (|| operator)
    else if ((energy <= 30) || (successChance < 10)) { 
        int damage = (rand() % 5) + 5;
        health = health - damage;
        printf("You were injured or found nothing while hunting. Health -%d. Remaining health: %d\n", damage, health);
    }
    else {
        printf("Luck was not on your side this time, you found nothing.\n");
    }
}

void handleShelter() {
    // IF-ELSE STRUCTURES: Evaluate success chance
    int chance = rand() % 100;

    if (chance > 50) {
        // LOGICAL OPERATORS: Check for good shelter (&& operator)
        if ((energy > 70) && (inventory > 0)) { 
             printf("You found an excellent shelter and you are safe!\n");
             energy = energy + (rand() % 5) + 5;
             if (energy > 100) energy = 100;
        } else {
             printf("Shelter found, but it's not very safe.\n");
        }
    } else { // IF-ELSE mandatory
        printf("You couldn't find shelter, you have to spend the night outside.\n");
        health = health - 5; 
    }
}

void handleRest() {
    // ARITHMETIC OPERATIONS: Health and Energy increase during rest
    int energyBoost = (rand() % 15) + 5;
    int healthBoost = 0;
    
    // Rest better if you have food (IF-ELSE mandatory)
    if (inventory > 0) {
        healthBoost = 10;
        inventory = inventory - 1; // Consume 1 food
        printf("You rested after eating some food.\n");
    } else {
        healthBoost = 5;
        printf("You rested without food, fatigue persists.\n");
    }

    energy = energy + energyBoost;
    health = health + healthBoost;

    // Boundary check
    if (energy > 100) energy = 100;
    if (health > 100) health = 100;

    printf("Rested. Energy +%d, Health +%d. Remaining food: %d\n", energyBoost, healthBoost, inventory);
}

void handleDanger() {
    printf("!!! Area Danger Series Begins !!!\n");
    
    int cycles = (rand() % 3) + 3; // 3 to 5 cycles
    int totalDamage = 0;
    
    // Variable must be defined outside the loop in C89/C90 standard
    int i; 

    // FOR LOOP mandatory
    for (i = 1; i <= cycles; i++) {
        int damage = (rand() % 5) + 1; 
        totalDamage = totalDamage + damage;
        printf("Danger %d/%d: Took %d damage.\n", i, cycles, damage);
    }
    
    // ARITHMETIC OPERATION
    health = health - totalDamage;
    printf("Danger series ended. Total damage taken: %d. Remaining health: %d\n", totalDamage, health);
}

void handleSecret() {
    int secretCode = 1234;
    int inputCode;
    
    printf("Encrypted Progression: Enter the progression code.(1234))\n");

    // DO-WHILE VALIDATION LOOP mandatory
    do {
        printf("Code: ");
        if (scanf("%d", &inputCode) != 1) {
            printf("Invalid input. Please enter only numbers.\n");
            while (getchar() != '\n'); 
            continue; 
        }
        
        if (inputCode != secretCode) {
            printf("Wrong code! Try again.\n");
            // Small penalty for incorrect entry
            energy = energy - 1; 
            if (energy < 0) energy = 0;
            printf("Energy -1. Remaining: %d\n", energy);
        }

    } while (inputCode != secretCode);

    printf("Code correct! You progressed successfully. Gained +10 Health.\n");
    health = health + 10;
    if (health > 100) health = 100;
}
