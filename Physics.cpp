#pragma once
#include "Physics.hpp"
#include "MainCharacter.hpp"
#include "NonPlayerCharacters.hpp"
#include "mapobject.hpp"
#include "game.hpp"

bool Physics::collisionHandler(MainCharacter *main_character, NonPlayerCharacters *NPC, int speedx, int speedy)
{
    static int previous_speed_x = (NPC->dx);
    static int previous_speed_y = (NPC->dy);
    static char previous_direction = (NPC->direction);

    if (SDL_HasIntersection(&(main_character->moverRect), &(NPC->moverRect)))
    {
        if (NPC->direction == 'n')
        {
            //     // std::cout << "gg" << std::endl;
            //     if (speedx != 0)
            //     {
            //         SDL_Rect newt = {NPC->moverRect.x - speedx , NPC->moverRect.y, NPC->moverRect.w, NPC->moverRect.h};
            //         if (SDL_HasIntersection( &(main_character->moverRect) , &(newt) ))
            //         {
            //             return true;
            //         }
            //         return false;
            //     }
            if (speedx > 0)
            {
                // std::cout << main_character->moverRect.x << " " << NPC->moverRect.x  << std::endl;
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

            // else if (speedx < 0)
            // {
            //     if (main_character->moverRect.x >= (NPC->moverRect.x + NPC->moverRect.w + speedx))
            //     {
            //         return true;
            //     }
            // if (speedx>0)
            //     return true;
            // return false;
            // }

            // else if (speedy > 0)
            // {
            //     if ((main_character->moverRect.y+main_character->moverRect.h) <= (NPC->moverRect.y + speedy))
            //     {
            //         return true;
            //     }
            //     return false;
            // }

            // else if (speedy < 0)
            // {
            //     if (main_character->moverRect.y >= (NPC->moverRect.y + NPC->moverRect.h + speedy))
            //     {
            //         return true;
            //     }
            //     return false;
            // }

            // return false;
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
            std::cout << main_character->moverRect.x + main_character->moverRect.w << NPC->moverRect.x << std::endl;
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
        // std::cout << NPC->moverRect.x << "  "<< main_character->moverRect.x << std::endl;
        NPC->dx = previous_speed_x;
        NPC->dy = previous_speed_y;
        NPC->previous_direction = 'n';
        NPC->direction = previous_direction;
        return false;
    }
}

void Physics::collisionHandler(std::list<NonPlayerCharacters *> npcList, int speedx, int speedy)
{
    std::list<NonPlayerCharacters *>::iterator i;
    for (i = npcList.begin(); i!=npcList.end(); i++)
    {
        std::list<NonPlayerCharacters *>::iterator j;
        for (j = npcList.begin(); j != npcList.end(); j++)
        {
            if (j!=i)
            {
                if (SDL_HasIntersection( &((*i)->moverRect) , &((*j)->moverRect) ))
                {
                    // std::cout << "collision" << std::endl;
                    if ( (*i)->dx > 0)
                    {
                        // std::cout << (*i)->moverRect.x + (*i)->moverRect.w << " " <<  (*j)->moverRect.x << std::endl;
                        if ( ( (*i)->moverRect.x + (*i)->moverRect.w - (*i)->dx*2 - abs(speedx*2) ) <= ( (*j)->moverRect.x ) )
                        {
                            // std::cout << 't';
                            (*i)->dx = 0;
                            (*i)->dy = 0;
                            (*i)->direction = 'n';
                        }
                    }

                    else if ( (*i)->dx < 0)
                    {
                        if ( ( (*i)->moverRect.x - (*i)->dx*2 + abs(speedx*2) ) >= ( (*j)->moverRect.x + (*j)->moverRect.w ) )
                        {
                            (*i)->dx = 0;
                            (*i)->dy = 0;
                            (*i)->direction = 'n';
                        }
                    }

                    else if ( (*i)->dy > 0)
                    {
                        if ( ( (*i)->moverRect.y + (*i)->moverRect.h - (*i)->dy*2 - abs(speedy*2) ) <=  (*j)->moverRect.y )
                        {
                            (*i)->dx = 0;
                            (*i)->dy = 0;
                            (*i)->direction = 'n';
                        }
                    }

                    else if ( (*i)->dy < 0)
                    {
                        if ( (*i)->moverRect.y - (*i)->dy*2 + abs(speedy*2) >= ( (*j)->moverRect.y + (*j)->moverRect.h) )
                        {
                            (*i)->dx = 0;
                            (*i)->dy = 0;
                            (*i)->direction = 'n';
                        }
                    }
                }
            }
        }
    }
}

bool Physics::collisionHandler(MainCharacter *main_character, MapObject* map, int speedx, int speedy)
{
    if (speedx > 0)
    {
        if (map->getMapAllowance((map->getXpos() + main_character->moverRect.x + main_character->moverRect.w ) / 100, (map->getYpos() + main_character->moverRect.y ) / 100) == 0)
        {
            return true;
            
        }
        else if (map->getMapAllowance((map->getXpos() + main_character->moverRect.x + main_character->moverRect.w ) / 100, (map->getYpos() + main_character->moverRect.y + main_character->moverRect.h ) / 100) == 0)
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

void Physics::collisionHandler(NonPlayerCharacters *npc, MapObject *map)
{
    if (npc->dx > 0)
    {
        if (map->getMapAllowance((npc->moverRect.x + npc->moverRect.w) / 100, (npc->moverRect.y) / 100) == 0)
        {
            npc->dx = 0;
            npc->dy = 0;
            npc->direction = 'n';
        }
        else if (map->getMapAllowance((npc->moverRect.x + npc->moverRect.w) / 100, (npc->moverRect.y + npc->moverRect.h) / 100) == 0)
        {
            npc->dx = 0;
            npc->dy = 0;
            npc->direction = 'n';
        }   
    }
    else if (npc->dx < 0)
    {
        if (map->getMapAllowance((npc->moverRect.x) / 100, (npc->moverRect.y) / 100) == 0)
        {
            npc->dx = 0;
            npc->dy = 0;
            npc->direction = 'n';
        }
        else if (map->getMapAllowance((npc->moverRect.x ) / 100, (npc->moverRect.y + npc->moverRect.h) / 100) == 0) 
        {
            npc->dx = 0;
            npc->dy = 0;
            npc->direction = 'n';
        }
    }
    else if (npc->dy > 0)
    {
        std::cout << npc->moverRect.x << " " << npc->moverRect.y << std::endl;
        if (map->getMapAllowance((npc->moverRect.x) / 100, (npc->moverRect.y + npc->moverRect.h) / 100) == 0)
        {
            npc->dx = 0;
            npc->dy = 0;
            npc->direction = 'n';
        }
        else if (map->getMapAllowance((npc->moverRect.x + npc->moverRect.w) / 100, (npc->moverRect.y + npc->moverRect.h) / 100) == 0)
        {
            npc->dx = 0;
            npc->dy = 0;
            npc->direction = 'n';
        }
    }
    else if (npc->dy < 0)
    {
        if (map->getMapAllowance((npc->moverRect.x) / 100, (npc->moverRect.y) / 100) == 0)
        {
            npc->dx = 0;
            npc->dy = 0;
            npc->direction = 'n';
        }
        else if (map->getMapAllowance((npc->moverRect.x + npc->moverRect.w) / 100, (npc->moverRect.y) / 100) == 0)
        {
            npc->dx = 0;
            npc->dy = 0;
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






