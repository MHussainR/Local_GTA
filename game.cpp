#include "game.hpp"
#include "TextureManager.hpp"
#include "MusicManager.hpp"
#include "GameObject.hpp"
#include "mapobject.hpp"
#include "CarObject.hpp"
#include "MainCharacter.hpp"
#include "AmbulanceMission.hpp"
#include "TaxiMission.hpp"
#include "SmallMapObject.hpp"
#include "stacked_sprites.hpp"
#include "cheat_codes.hpp"
#include <list>
// using std::list;
#include "NonPlayerCharacters.hpp"
#include "Health.hpp"
#include "Money.hpp"
#include "CircularMenu.hpp"
#include "Physics.hpp"
#include "Police.hpp"
#include "RayCaster.hpp"
#include "Guns.hpp"

// Game::Game(){}
// Game::~Game(){}
SDL_Event Game::event;

MusicManager *loading_music;
MusicManager *game_start;
MusicManager *death;
// NonPlayerCharacters *npc;
std::list<NonPlayerCharacters *> npcArray;
MainCharacter *human;
AmbulanceMission *aMission;
TaxiMission *tMission;
// CarObject *aMission;
// CarObject *car1;
MapObject *map;
SmallMapObject *smallMap;
MapObject *screen;
MapObject *instruction;
MapObject *loader;
MapObject *controls;
MapObject *death_screen;
Stacked_Sprites *box;
Stacked_Sprites *flats;
Stacked_Sprites *box_3d2;
Stacked_Sprites *police_st;
Stacked_Sprites *farm;
Stacked_Sprites *hospital;
Stacked_Sprites *park;
Stacked_Sprites *park1;
Stacked_Sprites *house1;
Stacked_Sprites *house2;
Stacked_Sprites *parking;
Stacked_Sprites *big_house;
Stacked_Sprites *shop1;
Stacked_Sprites *shop2;
Stacked_Sprites *gunshop;
Stacked_Sprites *car_mod;
RayCaster *RayCast;
Health *health;
Money *money;
CircularMenu *menu;
// Police *police;
Cheat_codes *c_codes;
CarObject *temp_car;
std::list<CarObject *> cars;
Guns *guns;

void Game::init(const char *title, int x_pos, int y_pos, int height, int width, bool fullscreen)
{
    int flags = 0;
    if (fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        // std::cout << "Subsystems initialized" << std::endl;
        window = SDL_CreateWindow(title, x_pos, y_pos, width, height, flags);
        if (window)
        {
            // std::cout << "Window Created" << std::endl;
        }
        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer)
        {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            // std::cout << "Renderer Created" << std::endl;
        }
        isRunning = true;
    }
    else
    {
        isRunning = false;
    }

    loading_music = new MusicManager("Music/title_music.wav");
    game_start = new MusicManager("Music/game_start.wav");
    death = new MusicManager("Music/wasted_sound.wav");
    // loading_music->Load("Music/loader.wav");
    // SDL_Surface* tmpSurface = IMG_Load("Trees.png");
    // block = SDL_CreateTextureFromSurface(renderer, tmpSurface);
    // SDL_FreeSurface(tmpSurface);
    // for (int i = 0; i < 2;i++)
    // {
    // NonPlayerCharacters *NPC = new NonPlayerCharacters("assets/npcs.png", renderer, 900, 700);
    map = new MapObject("assets/map6.png", renderer, 200, 800);
    Co_Ordinate_System = CoOrdinateSystem::getInstance(map->getXpos(), map->getYpos());

    // npcArray.push_back(new NonPlayerCharacters("assets/hackers.png", renderer, Co_Ordinate_System->setGlobalCoOrdinatex(1120), Co_Ordinate_System->setGlobalCoOrdinatey(400), 'r'));
    npcArray.push_back(new NonPlayerCharacters("assets/hackers.png", renderer, Co_Ordinate_System->setGlobalCoOrdinatex(1120), Co_Ordinate_System->setGlobalCoOrdinatey(1000), 'r'));
    // npcArray.push_back(new NonPlayerCharacters("assets/hackers.png", renderer, Co_Ordinate_System->setGlobalCoOrdinatex(1120), Co_Ordinate_System->setGlobalCoOrdinatey(500), 'd'));

    // police = new Police(Co_Ordinate_System, renderer);

    human = new MainCharacter("assets/Player_sprites.png", renderer, 600, 400);
    cars.push_back(new CarObject("assets/cars.png", renderer, Co_Ordinate_System->setGlobalCoOrdinatex(1200), Co_Ordinate_System->setGlobalCoOrdinatey(800), "Normal"));
    cars.push_back(new CarObject("assets/cars.png", renderer, Co_Ordinate_System->setGlobalCoOrdinatex(2850), Co_Ordinate_System->setGlobalCoOrdinatey(2050), "Taxi"));

    smallMap = new SmallMapObject("assets/map6.png", renderer, 0, 0);
    screen = new MapObject("assets/title_screen.png", renderer, 0, 0);
    instruction = new MapObject("assets/ins2.png", renderer, 0, 0);
    loader = new MapObject("assets/loader.png", renderer, 0, 0);
    controls = new MapObject("assets/controls.png", renderer, 0, 0);
    death_screen = new MapObject("assets/wasted_screen.png", renderer, 0, 0);
    aMission = new AmbulanceMission(renderer, map->getXpos(), map->getYpos());
    tMission = new TaxiMission(renderer, map->getXpos(), map->getYpos());
    // box = new Stacked_Sprites("assets/block_stack.png", renderer, Co_Ordinate_System->setGlobalCoOrdinatex(1000), Co_Ordinate_System->setGlobalCoOrdinatey(1100), 0, 100, 100, 100, 0, 25, 1, 1, 1);
    flats = new Stacked_Sprites("assets/flats_stack.png", renderer, Co_Ordinate_System->setGlobalCoOrdinatex(1400), Co_Ordinate_System->setGlobalCoOrdinatey(300), 0, 100, 200, 100, 180, 20, 1, 5, 7);
    box_3d2 = new Stacked_Sprites("assets/building_4_stack.png", renderer, Co_Ordinate_System->setGlobalCoOrdinatex(4800), Co_Ordinate_System->setGlobalCoOrdinatey(1300), 0, 200, 240, 200, 180, 20, 1, 5, 3);
    police_st = new Stacked_Sprites("assets/police_station_stack.png", renderer, Co_Ordinate_System->setGlobalCoOrdinatex(1400), Co_Ordinate_System->setGlobalCoOrdinatey(2900), 0, 100, 175, 100, 180, 20, 1, 7, 8);
    farm = new Stacked_Sprites("assets/farm_type_stack.png", renderer, Co_Ordinate_System->setGlobalCoOrdinatex(3100), Co_Ordinate_System->setGlobalCoOrdinatey(2900), 0, 100, 175, 100, 180, 20, 1, 5, 8);
    hospital = new Stacked_Sprites("assets/hospital_stack.png", renderer, Co_Ordinate_System->setGlobalCoOrdinatex(4800), Co_Ordinate_System->setGlobalCoOrdinatey(200), 0, 160, 180, 160, 0, 20, 1, 5, 5);
    park = new Stacked_Sprites("assets/park_stack.png", renderer, Co_Ordinate_System->setGlobalCoOrdinatex(3100), Co_Ordinate_System->setGlobalCoOrdinatey(300), 0, 100, 200, 100, 180, 20, 1, 5, 7);
    park1 = new Stacked_Sprites("assets/park_2_stack.png", renderer, Co_Ordinate_System->setGlobalCoOrdinatex(400), Co_Ordinate_System->setGlobalCoOrdinatey(1300), 0, 150, 175, 150, 180, 20, 1, 3, 4);

    health = new Health(renderer);
    money = new Money(renderer);
    menu = new CircularMenu(renderer, (width / 2) + (human->getMoverRect()->w / 2), (height / 2) + (human->getMoverRect()->h / 2));
    house1 = new Stacked_Sprites("assets/building_5_stack.png", renderer, Co_Ordinate_System->setGlobalCoOrdinatex(2200), Co_Ordinate_System->setGlobalCoOrdinatey(1300), 0, 200, 200, 200, 270, 20, 1, 3, 3);
    house2 = new Stacked_Sprites("assets/house_2_stack.png", renderer, Co_Ordinate_System->setGlobalCoOrdinatex(3900), Co_Ordinate_System->setGlobalCoOrdinatey(1300), 0, 200, 200, 200, 270, 20, 1, 3, 3);
    big_house = new Stacked_Sprites("assets/big_house_stack.png", renderer, Co_Ordinate_System->setGlobalCoOrdinatex(3100), Co_Ordinate_System->setGlobalCoOrdinatey(2100), 0, 125, 170, 125, 180, 20, 1, 3, 4);
    parking = new Stacked_Sprites("assets/parking_stack.png", renderer, Co_Ordinate_System->setGlobalCoOrdinatex(300), Co_Ordinate_System->setGlobalCoOrdinatey(200), 0, 200, 200, 200, 0, 20, 1, 3, 4);
    shop1 = new Stacked_Sprites("assets/shop_1_stack.png", renderer, Co_Ordinate_System->setGlobalCoOrdinatex(2200), Co_Ordinate_System->setGlobalCoOrdinatey(2100), 0, 125, 150, 125, 0, 20, 1, 3, 4);
    shop2 = new Stacked_Sprites("assets/shop_2_stack.png", renderer, Co_Ordinate_System->setGlobalCoOrdinatex(3900), Co_Ordinate_System->setGlobalCoOrdinatey(2100), 0, 125, 150, 125, 0, 20, 1, 3, 4);
    gunshop = new Stacked_Sprites("assets/gun_shop_stack.png", renderer, Co_Ordinate_System->setGlobalCoOrdinatex(4950), Co_Ordinate_System->setGlobalCoOrdinatey(1950), 0, 200, 125, 200, 90, 20, 1, 4, 4);
    car_mod = new Stacked_Sprites("assets/car_mod_stack.png", renderer, Co_Ordinate_System->setGlobalCoOrdinatex(1400), Co_Ordinate_System->setGlobalCoOrdinatey(1300), 0, 150, 175, 150, 0, 20, 1, 4, 4);

    RayCast = new RayCaster(renderer);
    c_codes = new Cheat_codes();

    guns = new Guns("assets/AR.png", renderer, human->getMoverRect()->x, human->getMoverRect()->y, Game::direction);
}

void Game::handleEvents()
{
    // SDL_PollEvent (&event);
    // switch (event.type){
    //     case SDL_QUIT:
    //         isRunning = false;
    //         break;
    //     // case SDLK_u:
    //     //     move+=100;
    //     //     break;
    //     default:
    //         break;
    // }
}

void Game::update()
{

    SDL_PollEvent(&event);
    // switch (event.type){
    //     case SDL_QUIT:
    //         isRunning = false;
    //         break;
    //     // case SDLK_u:
    //     //     move+=100;
    //     //     break;
    //     default:
    //         break;
    // }
    if (loading)
    {
        if (Game::event.type == SDL_QUIT)
        {
            isRunning = false;
        }
        if (loader->frame == 720)
        {
            loading = false;
            title = true;
            // loading_music->Stop();
            // loading_music->~MusicManager();
            // delete loading_music;
            // loading_music = nullptr;
        }
        loader->load();
        if (!loading_music->IsPlaying())
        {
            loading_music->Play();
        }
    }

    else if (title)
    {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        if (Game::event.type == SDL_QUIT)
        {
            isRunning = false;
        }

        if (Game::event.type == SDL_MOUSEBUTTONDOWN)
        {
            int xMouse, yMouse;
            SDL_GetMouseState(&xMouse, &yMouse);
            std::cout << xMouse << " " << yMouse << std::endl;
            if (xMouse >= 49 && xMouse <= 194 && yMouse >= 337 && yMouse <= 378)
            {
                title = false;
                loading_music->Stop();
            }
            if (xMouse >= 50 && xMouse <= 495 && yMouse >= 508 && yMouse <= 548)
            {
                title = false;
                instructions = true;
            }
            if (xMouse >= 41 && xMouse <= 366 && yMouse >= 411 && yMouse <= 471)
            {
                title = false;
                control = true;
            }
        }

        screen->Update();
    }

    else if (control)
    {
        if (Game::event.type == SDL_QUIT)
        {
            isRunning = false;
        }
        if (Game::event.type == SDL_KEYDOWN)
        {
            if (Game::event.key.keysym.sym == SDLK_r)
            {
                control = false;
                title = true;
            }
        }
        controls->Update();
    }

    else if (instructions)
    {
        if (Game::event.type == SDL_QUIT)
        {
            isRunning = false;
        }
        if (Game::event.type == SDL_KEYDOWN)
        {
            if (Game::event.key.keysym.sym == SDLK_r)
            {
                instructions = false;
                title = true;
            }
        }
        instruction->Update();
    }

    else if (RayCast->getState())
    {
        if (Game::event.type == SDL_QUIT)
        {
            isRunning = false;
        }
        RayCast->Update2(map->getMapAllowance(((human->getXpos() + map->getXpos()) / 100), (human->getYpos() + map->getYpos()) / 100));
    }

    else if (car_mod_var)
    {
        if (Game::event.type == SDL_QUIT)
        {
            isRunning = false;
        }
        if (!temp_car->get_modification_state())
        {
            car_mod_var = false;
        }
        temp_car->modification(money);
        // controls->Update();
    }

    else
    {
        if (game_start_music)
        {
            if (!game_start->IsPlaying())
                game_start->Play(1);
            else
                game_start_music = false;
        }
        if (Game::event.type == SDL_QUIT)
        {
            isRunning = false;
        }

        const Uint8 *state = SDL_GetKeyboardState(NULL);
        Uint32 mouseState = SDL_GetMouseState(&mouseX, &mouseY);

        if (human->firing)
        {
            human->firing = false;
        }

        if (state[SDL_SCANCODE_LSHIFT] && state[SDL_SCANCODE_UP])
        {
            if (state[SDL_SCANCODE_SPACE])
            {
                human->firing = true;
                human->Fire();
            }
            Game::dy = -5;
            Game::dx = 0;
            Game::direction = 'u';
        }

        else if (state[SDL_SCANCODE_LSHIFT] && state[SDL_SCANCODE_DOWN])
        {
            if (state[SDL_SCANCODE_SPACE])
            {
                human->firing = true;
                human->Fire();
            }
            Game::dy = 5;
            Game::dx = 0;
            Game::direction = 'd';
        }

        else if (state[SDL_SCANCODE_LSHIFT] && state[SDL_SCANCODE_RIGHT])
        {
            if (state[SDL_SCANCODE_SPACE])
            {
                human->firing = true;
                human->Fire();
            }
            Game::dy = 0;
            Game::dx = 5;
            Game::direction = 'r';
        }

        else if (state[SDL_SCANCODE_LSHIFT] && state[SDL_SCANCODE_LEFT])
        {
            if (state[SDL_SCANCODE_SPACE])
            {
                human->firing = true;
                human->Fire();
            }
            Game::dy = 0;
            Game::dx = -5;
            Game::direction = 'l';
        }

        else if (state[SDL_SCANCODE_LEFT])
        {
            if (state[SDL_SCANCODE_SPACE])
            {
                human->firing = true;
                human->Fire();
            }
            Game::dy = 0;
            Game::dx = -2;
            Game::direction = 'l';
            health->setHealth(health->getHealth() + 1);
            // money->setMoney(money->getMoney() + 10000000);
        }

        else if (state[SDL_SCANCODE_UP])
        {
            if (state[SDL_SCANCODE_SPACE])
            {
                human->firing = true;
                human->Fire();
            }
            Game::dx = 0;
            Game::dy = -2;
            Game::direction = 'u';
        }

        else if (state[SDL_SCANCODE_RIGHT])
        {
            if (state[SDL_SCANCODE_SPACE])
            {
                human->firing = true;
                human->Fire();
            }
            Game::dx = 2;
            Game::dy = 0;
            Game::direction = 'r';
            health->setHealth(health->getHealth() - 1);
            // money->setMoney(money->getMoney() - 10000);
        }

        else if (state[SDL_SCANCODE_DOWN])
        {
            if (state[SDL_SCANCODE_SPACE])
            {
                human->firing = true;
                human->Fire();
            }
            Game::dx = 0;
            Game::dy = 2;
            Game::direction = 'd';
        }

        else if (state[SDL_SCANCODE_R])
        {
            title = true;
            map->Reset();
            smallMap->Reset();
            // aMission->Reset();
            // car1->Reset();
            for (CarObject *c : cars)
            {
                c->Reset();
            }
        }

        else if (state[SDL_SCANCODE_Q])
        {
            human->setReload();
        }

        else if (state[SDL_SCANCODE_SPACE])
        {
            human->firing = true;
            human->Fire();
        }
        else
        {
            Game::dx = 0;
            Game::dy = 0;
            Game::direction = 'n';
        }

        if (Game::event.type == SDL_MOUSEBUTTONDOWN)
        {
            if (menu->getState())
            {
                human->setGuntype(menu->getGun(atan2(mouseY - (800 / 2), mouseX - (1200 / 2)) * 180 / M_PI, sqrt(pow((mouseX - (1200 / 2)), 2) + pow(mouseY - (800 / 2), 2))));
                menu->setState(false);
            }
        }
        bool flag = false;
        if (Game::event.type == SDL_KEYDOWN)
        {
            switch (Game::event.key.keysym.sym)
            {
            case SDLK_a:
                c_codes->check('a', health, money);
                break;
            case SDLK_b:
                c_codes->check('b', health, money);
                break;
            case SDLK_c:
                c_codes->check('c', health, money);
                break;
            case SDLK_d:
                c_codes->check('d', health, money);
                break;
            case SDLK_e:
                c_codes->check('e', health, money);
                break;
            case SDLK_f:
                c_codes->check('f', health, money);
                for (CarObject *c : cars)
                {
                    c->setStatus(human->getXpos(), human->getYpos());
                    if (c->getStatus())
                    {
                        if (flag == false)
                        {
                            flag = true;
                        }
                    }
                }
                if (flag)
                {
                    human->in_car = true;
                }
                else
                {
                    human->in_car = false;
                }
                aMission->setStatus(human->getXpos(), human->getYpos());
                tMission->setStatus(human->getXpos(), human->getYpos());
                break;
            case SDLK_g:
                c_codes->check('g', health, money);
                break;
            case SDLK_h:
                c_codes->check('h', health, money);
                break;
            case SDLK_i:
                c_codes->check('i', health, money);
                break;
            case SDLK_j:
                c_codes->check('j', health, money);
                break;
            case SDLK_k:
                c_codes->check('k', health, money);
                break;
            case SDLK_l:
                c_codes->check('l', health, money);
                break;
            case SDLK_m:
                c_codes->check('m', health, money);
                if (menu->getState())
                {
                    menu->setState(false);
                }
                else
                {
                    menu->setState(true);
                }
                break;
            case SDLK_n:
                c_codes->check('n', health, money);
                break;
            case SDLK_o:
                c_codes->check('o', health, money);
                break;
            case SDLK_p:
                c_codes->check('p', health, money);
                break;
            case SDLK_q:
                c_codes->check('q', health, money);
                break;
            case SDLK_r:
                c_codes->check('r', health, money);
                break;
            case SDLK_s:
                c_codes->check('s', health, money);
                break;
            case SDLK_t:
                c_codes->check('t', health, money);
                break;
            case SDLK_u:
                c_codes->check('u', health, money);
                break;
            case SDLK_v:
                c_codes->check('v', health, money);
                break;
            case SDLK_w:
                c_codes->check('w', health, money);
                break;
            case SDLK_x:
                c_codes->check('x', health, money);
                break;
            case SDLK_y:
                c_codes->check('y', health, money);
                break;
            case SDLK_z:
                c_codes->check('z', health, money);
                break;
            default:
                break;
            }
        }

        if (human->inside_box_x)
        {
            Game::dx = 0;
        }

        if (human->inside_box_y)
        {
            Game::dy = 0;
        }

        if (aMission->getStatus() && aMission->getState())
        {
            human->in_car = true;
        }

        if (tMission->getStatus() && tMission->getState())
        {
            human->in_car = true;
        }

        if (human->in_car)
        {
            if (Game::dx > 0)
            {
                Game::dx = 7;
                Game::dy = 0;
            }
            else if (Game::dx < 0)
            {
                Game::dx = -7;
                Game::dy = 0;
            }
            else if (Game::dy > 0)
            {
                Game::dy = 7;
                Game::dx = 0;
            }
            else if (Game::dy < 0)
            {
                Game::dy = -7;
                Game::dx = 0;
            }
            else
            {
                Game::dy = 0;
                Game::dx = 0;
            }
        }

        if (Implement.collisionHandler(human, npcArray, Game::dx, Game::dy))
        {
            Game::direction = 'n';
            Game::dx = 0;
            Game::dy = 0;
        }

        if (Implement.collisionHandler(human, cars, map, Game::dx, Game::dy))
        {
            Game::direction = 'n';
            Game::dx = 0;
            Game::dy = 0;
        }

        Implement.collisionHandler(npcArray, Game::dx, Game::dy);

        (Implement.collisionHandler(npcArray, map));

        if (Implement.collisionHandler(human, map, Game::dx, Game::dy))
        {
            Game::direction = 'n';
            Game::dx = 0;
            Game::dy = 0;
        }
        if (death_var)
        {

            if (!death->IsPlaying())
            {
                death->Play(1);
            }
            Game::dx = 0;
            Game::dy = 0;
            Game::direction = 'n';
        }

        map->Update(Game::direction, human->inside_box_x, human->inside_box_y, Game::dx, Game::dy);
        smallMap->Update(Game::direction, human->inside_box_x, human->inside_box_y, Game::dx, Game::dy);
        human->Update(Game::direction, map->getXpos(), map->getYpos(), Game::dx, Game::dy);
        guns->Update(Game::direction, Game::dx, Game::dy);
        for (NonPlayerCharacters *npc : npcArray)
        {
            npc->Update(Game::dx, Game::dy);
        }

        // police->followPath(map);
        // police->Update(Game::dx, Game::dy);
        static int temp = 0;
        for (CarObject *c : cars)
        {
            c->Update(Game::dx, Game::dy);
            if (temp == 0)
            {
                if (c->getStatus() && map->getMapAllowance(((human->getXpos() + map->getXpos()) / 100), (human->getYpos() + map->getYpos()) / 100) == -2)
                {
                    temp_car = c;
                    car_mod_var = true;
                    temp_car->set_modification_state(true);
                }
            }
            if (map->getMapAllowance(((human->getXpos() + map->getXpos()) / 100), (human->getYpos() + map->getYpos()) / 100) == -2)
                temp = 1;
            else
                temp = 0;
        }
        aMission->Update(Game::dx, Game::dy);
        tMission->Update(Game::dx, Game::dy);

        if (aMission->getState())
            aMission->Running(map->getXpos(), map->getYpos(), money);
        else
            aMission->check();

        if (tMission->getState())
            tMission->Running(map->getXpos(), map->getYpos(), money);
        else
            tMission->check();

        if (map->getMapAllowance(((human->getXpos() + map->getXpos()) / 100), (human->getYpos() + map->getYpos()) / 100) == -1)
        {
            death_var = true;
            death_screen->death();
            if (death_screen->get_death_state())
                isRunning = false;
            // std::cout << "death" << '\n';
        }
        // else

        // box->Update(Game::dx, Game::dy, human->getXpos(), human->getYpos());
        flats->Update(Game::dx, Game::dy, human->getXpos(), human->getYpos());
        box_3d2->Update(Game::dx, Game::dy, human->getXpos(), human->getYpos());
        RayCast->Update(map->getMapAllowance(((human->getXpos() + map->getXpos()) / 100), (human->getYpos() + map->getYpos()) / 100));
        police_st->Update(Game::dx, Game::dy, human->getXpos(), human->getYpos());
        farm->Update(Game::dx, Game::dy, human->getXpos(), human->getYpos());
        hospital->Update(Game::dx, Game::dy, human->getXpos(), human->getYpos());
        park->Update(Game::dx, Game::dy, human->getXpos(), human->getYpos());
        park1->Update(Game::dx, Game::dy, human->getXpos(), human->getYpos());
        house1->Update(Game::dx, Game::dy, human->getXpos(), human->getYpos());
        house2->Update(Game::dx, Game::dy, human->getXpos(), human->getYpos());
        big_house->Update(Game::dx, Game::dy, human->getXpos(), human->getYpos());
        parking->Update(Game::dx, Game::dy, human->getXpos(), human->getYpos());
        shop1->Update(Game::dx, Game::dy, human->getXpos(), human->getYpos());
        shop2->Update(Game::dx, Game::dy, human->getXpos(), human->getYpos());
        gunshop->Update(Game::dx, Game::dy, human->getXpos(), human->getYpos());
        car_mod->Update(Game::dx, Game::dy, human->getXpos(), human->getYpos());
    }
}

void Game::render()
{
    SDL_RenderClear(renderer);
    if (loading)
    {
        loader->Render();
    }
    else if (title)
    {
        screen->Render();
    }
    else if (control)
    {
        controls->Render();
    }
    else if (instructions)
    {
        instruction->Render();
    }
    else if (RayCast->getState())
    {
        RayCast->Render();
        // if (death_var)
        //     death_screen->Render();
    }
    // else if (death_var){
    //     death_screen->Render();
    // }
    else
    {
        map->Render();
        // aMission->Render(map->getXpos(), map->getYpos());

        flats->Render(human->getXpos(), human->getYpos());
        box_3d2->Render(human->getXpos(), human->getYpos());
        police_st->Render(human->getXpos(), human->getYpos());
        farm->Render(human->getXpos(), human->getYpos());
        // hospital->Render(human->getXpos(), human->getYpos());
        park->Render(human->getXpos(), human->getYpos());
        park1->Render(human->getXpos(), human->getYpos());
        house1->Render(human->getXpos(), human->getYpos());
        house2->Render(human->getXpos(), human->getYpos());
        parking->Render(human->getXpos(), human->getYpos());
        big_house->Render(human->getXpos(), human->getYpos());
        shop1->Render(human->getXpos(), human->getYpos());
        shop2->Render(human->getXpos(), human->getYpos());
        gunshop->Render(human->getXpos(), human->getYpos());
        car_mod->Render(human->getXpos(), human->getYpos());

        // box->Render(human->getXpos(), human->getYpos());
        aMission->Render(map->getXpos(), map->getYpos());
        tMission->Render(map->getXpos(), map->getYpos(), Game::dx, Game::dy);

        // aMission->Render();
        // car1->Render();
        for (NonPlayerCharacters *npc : npcArray)
        {
            npc->Render();
        }
        // if (!aMission->getStatus() && !car1->getStatus())

        //     human->Render();
        // }

        // if (!car1->getStatus()){
        //     human->Render();
        // }
        int i = 0;
        for (CarObject *c : cars)
        {
            c->Render(map->getXpos(), map->getYpos());
            if (c->getStatus())
            {
                i = 1;
            }
        }
        if (aMission->getStatus())
            i = 1;
        else if (tMission->getStatus())
            i = 1;

        if (i == 0)
        {
            human->Render();
            // guns->Render();
        }
        hospital->Render(human->getXpos(), human->getYpos());
        smallMap->Render();
        health->Render();
        money->Render();
        menu->Render(atan2(mouseY - (800 / 2), mouseX - (1200 / 2)) * 180 / M_PI, sqrt(pow((mouseX - (1200 / 2)), 2) + pow(mouseY - (800 / 2), 2)));
        // police->Render();
        if (death_var)
            death_screen->Render();
        if (car_mod_var)
            temp_car->modification_render();
    }
    SDL_RenderPresent(renderer);
}

void Game::clean()
{

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game Cleaned" << std::endl;
}

Game::~Game()
{
    delete human;
    human = nullptr;
    delete aMission;
    aMission = nullptr;
    delete map;
    map = nullptr;
    delete smallMap;
    smallMap = nullptr;
    delete screen;
    screen = nullptr;
    delete instruction;
    instruction = nullptr;
    delete loader;
    loader = nullptr;
    delete box;
    box = nullptr;
    delete flats;
    flats = nullptr;
    delete box_3d2;
    box_3d2 = nullptr;
    delete police_st;
    police_st = nullptr;
    delete farm;
    farm = nullptr;
    delete hospital;
    hospital = nullptr;
    delete park;
    park = nullptr;
    delete house1;
    house1 = nullptr;
    delete house2;
    house2 = nullptr;
    delete parking;
    parking = nullptr;
    delete RayCast;
    RayCast = nullptr;
    delete health;
    health = nullptr;
    delete money;
    money = nullptr;
    delete menu;
    menu = nullptr;
    // delete police;
    // police = nullptr;
    delete Co_Ordinate_System;
    // Co_Ordinate_System = nullptr;
    for (CarObject *t : cars)
    {
        delete t;
        t = nullptr;
    }
    for (NonPlayerCharacters *n : npcArray)
    {
        delete n;
        n = nullptr;
    }
    cars.clear();
    npcArray.clear();
}
