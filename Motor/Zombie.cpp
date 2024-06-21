#include "Zombie.h"
#include "Human.h"
#include <random>
#include <ctime>
#include<glm/gtx/rotate_vector.hpp>

Zombie::Zombie()
{
}

Zombie::~Zombie()
{
}

void Zombie::init(float speed, glm::vec2 position)
{
    this->speed = speed; 
    color.set(0, 185, 0, 255); 
    this->position = position;
	
}

void Zombie::update(vector<string>& levelData, vector<Human*>& humans, vector<Zombie*>& zombies, Player* player)
{
    std::mt19937 randomEngine(time(nullptr));
    std::uniform_real_distribution<float>randRotate(-40.0f, 40.0f);
   
    Human* cercano = nullptr;
    float maxi = std::numeric_limits<float>::max();

    for (auto& human : humans) {
        float dist = glm::length(human->getPosition() - position);
        if (dist < maxi) {
            maxi = dist;
            cercano = human;
        }
    }

    // Si existe iremos a los humanos
    if (cercano) {
        glm::vec2 direction = glm::normalize(cercano->getPosition() - position);
        position += direction * speed;
    }
    else { // Si no hay humanos, persigue al jugador
        glm::vec2 direction = glm::normalize(player->getPosition() - position);
        position += direction * speed;
    }
  
    if (collideWithLevel(levelData)) {
        direction = glm::rotate(direction, randRotate(randomEngine));
    }
}
