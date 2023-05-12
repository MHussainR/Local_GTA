#include "Characters.hpp"
#include "ARBullets.hpp"
#include "ShotgunBullets.hpp"
#include "HandGunBullets.hpp"

class Physics;

class MainCharacter : public Characters
{
    public:
        MainCharacter(const char *, SDL_Renderer *, int, int);
        void Update() override;
        void Update(char, int, int) override;
        void Update(char, int, int, int, int) override;
        void Render() override;
        void Animator_reloading();
        void Animator(char);
        void Run(bool) override;
        void Fire();
        void setReload();
        SDL_Rect *getMoverRect();
        SDL_Texture *foot1;
        SDL_Texture *foot2;
        SDL_Texture *t1;
        SDL_Texture *t2;
        SDL_Rect srcRectFoot;
        SDL_Rect moverRectFoot;
        std::string gunType;
        bool in_car;
        bool firing;
        std::list<Bullets *> bullets;
        void setGuntype(std::string);

        friend class Physics;

    private:
        int lFrame, rFrame, uFrame, dFrame, reloadFrameAR, reloadFrameHG, reloadFrameSG, firingFrame;
        int bullets_ar, magazine_ar, capacity_ar;
        int bullets_hg, magazine_hg, capacity_hg;
        int bullets_sg, magazine_sg, capacity_sg;
        bool reloadSG, reloadHG, reloadAR, reloading;
        char previous_direction;
        char direction;
        int reference;
        const Uint32 fireRateAR;
        const Uint32 fireRateHG;
        Uint32 lastFireTimeAR;
        Uint32 lastFireTimeHG;
};