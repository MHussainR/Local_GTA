#pragma once
#include "Physics.hpp"
#include "MainCharacter.hpp"
#include "NonPlayerCharacters.hpp"
#include "CarObject.hpp"
#include "mapobject.hpp"
#include "game.hpp"

bool Physics::collisionHandler(MainCharacter *main_character, NonPlayerCharacters *NPC, int speedx, int speedy)
{
    std::list<Bullets *>::iterator current_index;
    for (current_index = main_character->bullets.begin(); current_index != main_character->bullets.end(); current_index++)
    {
        if (SDL_HasIntersection(((*current_index)->getMoverRect()), &(NPC->moverRect)))
        {
            if ((*current_index)->getDirection() == 'u')
            {
                if (((*current_index)->getMoverRect()->y + (*current_index)->getMoverRect()->h) >= (NPC->moverRect.y + NPC->moverRect.h - ((*current_index)->getBulletSpeed() * 2) - NPC->dy))
                {
                    delete (*current_index);
                    (*current_index) = NULL;
                    current_index = main_character->bullets.erase(current_index);
                }
            }
            else if ((*current_index)->getDirection() == 'd')
            {
                if (((*current_index)->getMoverRect()->y + (*current_index)->getMoverRect()->h) <= (NPC->moverRect.y + NPC->moverRect.h + ((*current_index)->getBulletSpeed() * 2) - NPC->dy))
                {
                    delete (*current_index);
                    (*current_index) = NULL;
                    current_index = main_character->bullets.erase(current_index);
                }
            }
            else if ((*current_index)->getDirection() == 'r')
            {
                if (((*current_index)->getMoverRect()->x + (*current_index)->getMoverRect()->w) <= (NPC->moverRect.x + NPC->moverRect.w + ((*current_index)->getBulletSpeed() * 2) - NPC->dx))
                {
                    delete (*current_index);
                    (*current_index) = NULL;
                    current_index = main_character->bullets.erase(current_index);
                }
            }
            else if ((*current_index)->getDirection() == 'l')
            {
                if (((*current_index)->getMoverRect()->x + (*current_index)->getMoverRect()->w) >= (NPC->moverRect.x + ((*current_index)->getBulletSpeed() * 2) - NPC->dx))
                {
                    delete (*current_index);
                    (*current_index) = NULL;
                    current_index = main_character->bullets.erase(current_index);
                }
            }
        }
    }

    if (SDL_HasIntersection(&(main_character->moverRect), &(NPC->moverRect)))
    {
        if (NPC->direction == 'n')
        {
            if (speedx > 0)
            {
                if ((main_character->moverRect.x) <= (NPC->moverRect.x))
                {
                    return true;
                }
                return false;
            }
            else if (speedx < 0)
            {
                if (main_character->moverRect.x >= NPC->moverRect.x)
                {
                    return true;
                }
                return false;
            }
            else if (speedy > 0)
            {
                if (main_character->moverRect.y <= NPC->moverRect.y)
                {
                    return true;
                }
                return false;
            }
            else if (speedy < 0)
            {
                if (main_character->moverRect.y >= NPC->moverRect.y)
                {
                    return true;
                }
                return false;
            }
            return false;
        }

        else if (NPC->direction == 'r')
        {
            if ((NPC->moverRect.x + NPC->moverRect.w - NPC->dx + speedx * 2) <= main_character->moverRect.x)
            {
                NPC->dx = 0;
                NPC->dy = 0;
                NPC->previous_direction = NPC->direction;
                NPC->direction = 'n';
                return false;
            }
            return true;
        }

        else if (NPC->direction == 'l')
        {
            if (NPC->moverRect.x - NPC->dx + speedx * 2 >= (main_character->moverRect.x + main_character->moverRect.w))
            {
                NPC->dx = 0;
                NPC->dy = 0;
                NPC->previous_direction = NPC->direction;
                NPC->direction = 'n';
                return false;
            }
            return true;
        }

        else if (NPC->direction == 'u')
        {
            if (NPC->moverRect.y - NPC->dy + speedy * 2 >= (main_character->moverRect.y + main_character->moverRect.h))
            {
                NPC->dx = 0;
                NPC->dy = 0;
                NPC->previous_direction = NPC->direction;
                NPC->direction = 'n';
                return false;
            }
            return true;
        }

        else if (NPC->direction == 'd')
        {
            if (NPC->moverRect.y - NPC->dy + speedy * 2 <= (main_character->moverRect.y))
            {
                NPC->dx = 0;
                NPC->dy = 0;
                NPC->previous_direction = NPC->direction;
                NPC->direction = 'n';
                return false;
            }
            return true;
        }
    }

    else
    {
        NPC->dx = NPC->initial_dx;
        NPC->dy = NPC->initial_dy;
        NPC->previous_direction = 'n';
        NPC->direction = NPC->initial_direction;
        return false;
    }
}

bool Physics::collisionHandler(MainCharacter *main_character, std::list<NonPlayerCharacters *> npcList, int speedx, int speedy)
{
    std::list<NonPlayerCharacters *>::iterator i;
    bool flag = false;
    for (i = npcList.begin(); i != npcList.end(); i++)
    {
        if (collisionHandler(main_character, *i, speedx, speedy) && (flag == false))
        {
            flag = true;
        }
    }
    return flag;
}

void Physics::collisionHandler(std::list<NonPlayerCharacters *> npcList, int speedx, int speedy)
{
    std::list<NonPlayerCharacters *>::iterator i;
    for (i = npcList.begin(); i != npcList.end(); i++)
    {
        std::list<NonPlayerCharacters *>::iterator j;
        for (j = npcList.begin(); j != npcList.end(); j++)
        {
            if (j != i)
            {
                if (SDL_HasIntersection(&((*i)->moverRect), &((*j)->moverRect)))
                {
                    // std::cout << "collision" << std::endl;
                    if ((*i)->dx > 0)
                    {
                        // std::cout << (*i)->moverRect.x + (*i)->moverRect.w << " " <<  (*j)->moverRect.x << std::endl;
                        if (((*i)->moverRect.x + (*i)->moverRect.w - (*i)->dx * 2 - abs(speedx * 2)) <= ((*j)->moverRect.x))
                        {
                            // std::cout << 't';
                            (*i)->dx = 0;
                            (*i)->dy = 0;
                            (*i)->previous_direction = (*i)->direction;
                            (*i)->direction = 'n';
                        }
                    }

                    else if ((*i)->dx < 0)
                    {
                        if (((*i)->moverRect.x - (*i)->dx * 2 + abs(speedx * 2)) >= ((*j)->moverRect.x + (*j)->moverRect.w))
                        {
                            (*i)->dx = 0;
                            (*i)->dy = 0;
                            (*i)->previous_direction = (*i)->direction;
                            (*i)->direction = 'n';
                        }
                    }

                    else if ((*i)->dy > 0)
                    {
                        if (((*i)->moverRect.y + (*i)->moverRect.h - (*i)->dy * 2 - abs(speedy * 2)) <= (*j)->moverRect.y)
                        {
                            (*i)->dx = 0;
                            (*i)->dy = 0;
                            (*i)->previous_direction = (*i)->direction;
                            (*i)->direction = 'n';
                        }
                    }

                    else if ((*i)->dy < 0)
                    {
                        if ((*i)->moverRect.y - (*i)->dy * 2 + abs(speedy * 2) >= ((*j)->moverRect.y + (*j)->moverRect.h))
                        {
                            (*i)->dx = 0;
                            (*i)->dy = 0;
                            (*i)->previous_direction = (*i)->direction;
                            (*i)->direction = 'n';
                        }
                    }
                }
            }
        }
    }
}

bool Physics::collisionHandler(MainCharacter *main_character, MapObject *map, int speedx, int speedy)
{
    if (!main_character->in_car) 
    {
        std::list<Bullets *>::iterator current_index;
        for (current_index = main_character->bullets.begin(); current_index != main_character->bullets.end(); current_index++)
        {
            if ((*current_index)->getDirection() == 'u')
            {
                if (map->getMapAllowance((map->getXpos() + (*current_index)->getMoverRect()->x) / 100, (map->getYpos() + (*current_index)->getMoverRect()->y) / 100) == 0)
                {
                    delete (*current_index);
                    (*current_index) = NULL;
                    current_index = main_character->bullets.erase(current_index);
                }
                else if (map->getMapAllowance((map->getXpos() + (*current_index)->getMoverRect()->x + (*current_index)->getMoverRect()->w) / 100, (map->getYpos() + (*current_index)->getMoverRect()->y) / 100) == 0)
                {
                    delete (*current_index);
                    (*current_index) = NULL;
                    current_index = main_character->bullets.erase(current_index);
                }
            }
            else if ((*current_index)->getDirection() == 'd')
            {
                if (map->getMapAllowance((map->getXpos() + (*current_index)->getMoverRect()->x) / 100, (map->getYpos() + (*current_index)->getMoverRect()->y + (*current_index)->getMoverRect()->h) / 100) == 0)
                {
                    delete (*current_index);
                    (*current_index) = NULL;
                    current_index = main_character->bullets.erase(current_index);
                }
                else if (map->getMapAllowance((map->getXpos() + (*current_index)->getMoverRect()->x + (*current_index)->getMoverRect()->w) / 100, (map->getYpos() + (*current_index)->getMoverRect()->y + (*current_index)->getMoverRect()->h) / 100) == 0)
                {
                    delete (*current_index);
                    (*current_index) = NULL;
                    current_index = main_character->bullets.erase(current_index);
                }
            }
            else if ((*current_index)->getDirection() == 'r')
            {
                if (map->getMapAllowance((map->getXpos() + (*current_index)->getMoverRect()->x + (*current_index)->getMoverRect()->w) / 100, (map->getYpos() + (*current_index)->getMoverRect()->y) / 100) == 0)
                {
                    delete (*current_index);
                    (*current_index) = NULL;
                    current_index = main_character->bullets.erase(current_index);
                }
                else if (map->getMapAllowance((map->getXpos() + (*current_index)->getMoverRect()->x + (*current_index)->getMoverRect()->w) / 100, (map->getYpos() + (*current_index)->getMoverRect()->y + (*current_index)->getMoverRect()->h) / 100) == 0)
                {
                    delete (*current_index);
                    (*current_index) = NULL;
                    current_index = main_character->bullets.erase(current_index);
                }
            }
            else if ((*current_index)->getDirection() == 'l')
            {
                if (map->getMapAllowance((map->getXpos() + (*current_index)->getMoverRect()->x) / 100, (map->getYpos() + (*current_index)->getMoverRect()->y) / 100) == 0)
                {
                    delete (*current_index);
                    (*current_index) = NULL;
                    current_index = main_character->bullets.erase(current_index);
                }
                else if (map->getMapAllowance((map->getXpos() + (*current_index)->getMoverRect()->x) / 100, (map->getYpos() + (*current_index)->getMoverRect()->y + (*current_index)->getMoverRect()->h) / 100) == 0)
                {
                    delete (*current_index);
                    (*current_index) = NULL;
                    current_index = main_character->bullets.erase(current_index);
                }
            }
        }

        if (speedx > 0)
        {
            if (map->getMapAllowance((map->getXpos() + main_character->moverRect.x + main_character->moverRect.w) / 100, (map->getYpos() + main_character->moverRect.y) / 100) == 0)
            {
                return true;
            }
            else if (map->getMapAllowance((map->getXpos() + main_character->moverRect.x + main_character->moverRect.w) / 100, (map->getYpos() + main_character->moverRect.y + main_character->moverRect.h) / 100) == 0)
            {
                return true;
            }
        }
        else if (speedx < 0)
        {
            if (map->getMapAllowance((map->getXpos() + main_character->moverRect.x) / 100, (map->getYpos() + main_character->moverRect.y) / 100) == 0)
            {
                return true;
            }
            else if (map->getMapAllowance((map->getXpos() + main_character->moverRect.x) / 100, (map->getYpos() + main_character->moverRect.y + main_character->moverRect.h) / 100) == 0)
            {
                return true;
            }
        }
        else if (speedy > 0)
        {
            if (map->getMapAllowance((map->getXpos() + main_character->moverRect.x) / 100, (map->getYpos() + main_character->moverRect.y + main_character->moverRect.h) / 100) == 0)
            {
                return true;
            }
            else if (map->getMapAllowance((map->getXpos() + main_character->moverRect.x + main_character->moverRect.w) / 100, (map->getYpos() + main_character->moverRect.y + main_character->moverRect.h) / 100) == 0)
            {
                return true;
            }
        }
        else if (speedy < 0)
        {
            if (map->getMapAllowance((map->getXpos() + main_character->moverRect.x) / 100, (map->getYpos() + main_character->moverRect.y) / 100) == 0)
            {
                return true;
            }
            else if (map->getMapAllowance((map->getXpos() + main_character->moverRect.x + main_character->moverRect.w) / 100, (map->getYpos() + main_character->moverRect.y) / 100) == 0)
            {
                return true;
            }
        }
        return false;
    }
}

void Physics::collisionHandler(NonPlayerCharacters *npc, MapObject *map)
{
    // std::cout << map->getXpos() + npc->moverRect.x << " " << map->getYpos() + npc->moverRect.y << std::endl;
    if (npc->dx > 0)
    {
        if (map->getMapAllowance((map->getXpos() + npc->moverRect.x + npc->moverRect.w) / 100, (map->getYpos() + npc->moverRect.y) / 100) == 0)
        {
            npc->dx = 0;
            npc->dy = 0;
            npc->previous_direction = npc->direction;
            npc->direction = 'n';
        }
        else if (map->getMapAllowance((map->getXpos() + npc->moverRect.x + npc->moverRect.w) / 100, (map->getYpos() + npc->moverRect.y + npc->moverRect.h) / 100) == 0)
        {
            npc->dx = 0;
            npc->dy = 0;
            npc->previous_direction = npc->direction;
            npc->direction = 'n';
        }
    }
    else if (npc->dx < 0)
    {
        if (map->getMapAllowance((map->getXpos() + npc->moverRect.x) / 100, (map->getYpos() + npc->moverRect.y) / 100) == 0)
        {
            npc->dx = 0;
            npc->dy = 0;
            npc->previous_direction = npc->direction;
            npc->direction = 'n';
        }
        else if (map->getMapAllowance((map->getXpos() + npc->moverRect.x) / 100, (map->getYpos() + npc->moverRect.y + npc->moverRect.h) / 100) == 0)
        {
            npc->dx = 0;
            npc->dy = 0;
            npc->previous_direction = npc->direction;
            npc->direction = 'n';
        }
    }
    else if (npc->dy > 0)
    {
        if (map->getMapAllowance((map->getXpos() + npc->moverRect.x) / 100, (map->getYpos() + npc->moverRect.y + npc->moverRect.h) / 100) == 0)
        {
            npc->dx = 0;
            npc->dy = 0;
            npc->previous_direction = npc->direction;
            npc->direction = 'n';
        }
        else if (map->getMapAllowance((map->getXpos() + npc->moverRect.x + npc->moverRect.w) / 100, (map->getYpos() + npc->moverRect.y + npc->moverRect.h) / 100) == 0)
        {
            npc->dx = 0;
            npc->dy = 0;
            npc->previous_direction = npc->direction;
            npc->direction = 'n';
        }
    }
    else if (npc->dy < 0)
    {
        if (map->getMapAllowance((map->getXpos() + npc->moverRect.x) / 100, (map->getYpos() + npc->moverRect.y) / 100) == 0)
        {
            npc->dx = 0;
            npc->dy = 0;
            npc->previous_direction = npc->direction;
            npc->direction = 'n';
        }
        else if (map->getMapAllowance((map->getXpos() + npc->moverRect.x + npc->moverRect.w) / 100, (map->getYpos() + npc->moverRect.y) / 100) == 0)
        {
            npc->dx = 0;
            npc->dy = 0;
            npc->previous_direction = npc->direction;
            npc->direction = 'n';
        }
    }
}

void Physics::collisionHandler(std::list<NonPlayerCharacters *> npcList, MapObject *map)
{
    std::list<NonPlayerCharacters *>::iterator i;
    for (i = npcList.begin(); i != npcList.end(); i++)
    {
        collisionHandler(*i, map);
    }
}

bool Physics::collisionHandler(MainCharacter *main_character, CarObject *car, MapObject *map, int speedx, int speedy)
{
    if (main_character->in_car == false)
    {
        if (SDL_HasIntersection(&(main_character->moverRect), &(car->moverRect)))
        {
            if (car->direction == 'n')
            {
                if (speedx > 0)
                {
                    if ((map->getXpos() + main_character->moverRect.x) <= (map->getXpos() + car->moverRect.x))
                    {
                        return true;
                    }
                }

                else if (speedx < 0)
                {
                    if ((map->getXpos() + main_character->moverRect.x + main_character->moverRect.w) >= (map->getXpos() + car->moverRect.x + car->moverRect.w))
                    {
                        return true;
                    }
                }

                else if (speedy > 0)
                {
                    if ((map->getYpos() + main_character->moverRect.y) <= (map->getYpos() + car->moverRect.y))
                    {
                        return true;
                    }
                }

                else if (speedy < 0)
                {
                    if ((map->getYpos() + main_character->moverRect.y + main_character->moverRect.h) >= (map->getYpos() + car->moverRect.y + car->moverRect.h))
                    {
                        return true;
                    }
                }

                return false;
            }
            return false;
        }
        return false;
    }
    return false;
}

bool Physics::collisionHandler(MainCharacter *main_character, std::list<CarObject *> cars, MapObject *map, int speedx, int speedy)
{
    std::list<CarObject *>::iterator i;
    bool flag = false;
    for (i = cars.begin(); i != cars.end(); i++)
    {
        if (collisionHandler(main_character, *i, map, speedx, speedy) && (flag == false))
        {
            flag = true;
        }
    }
    return flag;
}
