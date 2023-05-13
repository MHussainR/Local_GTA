#include "MainCharacter.hpp"
#include "TextureManager.hpp"
// #include <iostream>

MainCharacter::MainCharacter(const char *textursheet, SDL_Renderer *ren, int x, int y) : Characters(textursheet, ren, x, y),
                                                                                         lFrame(0), rFrame(0), uFrame(0), dFrame(0), reloadFrameAR(0), reloadFrameHG(0), reloadFrameSG(0),
                                                                                         reloadAR(false), reloadHG(false), reloadSG(false), reloading(false),
                                                                                         previous_direction('i'),
                                                                                         reference(5), in_car(false), gunType("AR"),
                                                                                         firing(false), fireRateAR(75), lastFireTimeAR(0), bullets_ar(30), firingFrame(1),
                                                                                         lastFireTimeHG(0), fireRateHG(500), bullets_hg(15)

{
    srcRect = {0, 409, 177, 105};
    moverRect = {600, 400, srcRect.w / 2, srcRect.h / 2};
    foot1 = TextureManager::LoadTexture("assets/Player_sprites.png", renderer);
    foot2 = TextureManager::LoadTexture("assets/Player_sprites_ver.png", renderer);
    t1 = TextureManager::LoadTexture("assets/Player_sprites.png", renderer);
    t2 = TextureManager::LoadTexture("assets/Player_sprites_ver.png", renderer);
    srcRectFoot = {4333, 82, 98, 114};
    moverRectFoot = {((moverRect.x + moverRect.w) / 2) - ((srcRectFoot.x + (srcRectFoot.w / 2)) / 2), ((moverRect.y + moverRect.h) / 2) - ((srcRectFoot.y + (srcRectFoot.h / 3)) / 2), srcRectFoot.w / 3, srcRectFoot.h / 3};
}

void MainCharacter::setGuntype(std::string type)
{
    this->gunType = type;
}

void MainCharacter::Animator(char direction)
{
    if (direction == 'n' || direction == 'i')
    {
        if (this->previous_direction == 'r')
        {
            if (gunType == "AR")
                srcRect = {0, 409, 177, 105};
            else if (gunType == "SG")
                srcRect = {1, 2061, 180, 105};
            else if (gunType == "HG")
                srcRect = {33, 3610, 178, 131};
            srcRectFoot = {4333, 82, 100, 114};
        }
        else if (this->previous_direction == 'l')
        {
            if (gunType == "AR")
                srcRect = {4298, 1350, 180, 105};
            else if (gunType == "SG")
                srcRect = {4305, 3252, 180, 105};
            else if (gunType == "HG")
                srcRect = {4285, 5141, 178, 131};
            srcRectFoot = {43, 1668, 98, 114};
        }
        else if (this->previous_direction == 'u')
        {
            if (gunType == "AR")
                srcRect = {3819, 4301, 105, 181};
            else if (gunType == "SG")
                srcRect = {1917, 4309, 105, 180};
            else if (gunType == "HG")
                srcRect = {2, 4289, 131, 178};
            srcRectFoot = {3492, 47, 114, 98};
        }
        else if (this->previous_direction == 'd')
        {
            if (gunType == "AR")
                srcRect = {4760, 0, 106, 180};
            else if (gunType == "SG")
                srcRect = {3108, 5, 105, 180};
            else if (gunType == "HG")
                srcRect = {1533, 37, 131, 178};
            srcRectFoot = {5078, 4337, 114, 98};
        }
        else
        {
            if (gunType == "AR")
                srcRect = {0, 409, 177, 105};
            else if (gunType == "SG")
                srcRect = {1, 2061, 180, 105};
            else if (gunType == "HG")
                srcRect = {33, 3610, 178, 131};
            srcRectFoot = {4333, 82, 100, 114};
        }
        lFrame = 0;
        rFrame = 0;
        uFrame = 0;
        dFrame = 0;
    }

    else if (direction == 'r')
    {
        lFrame = 0;
        uFrame = 0;
        dFrame = 0;
        if (rFrame == 0)
        {
            if (gunType == "AR")
                srcRect = {222, 409, 177, 105};
            else if (gunType == "SG")
                srcRect = {226, 2061, 180, 105};
            else if (gunType == "HG")
                srcRect = {258, 3610, 178, 131};
            srcRectFoot = {232, 1513, 176, 100};
            rFrame++;
        }
        else if (rFrame == reference)
        {
            if (gunType == "AR")
                srcRect.x = 444;
            else if (gunType == "SG")
                srcRect.x = 448;
            else if (gunType == "HG")
                srcRect.x = 483;
            srcRectFoot.x = 451;
            rFrame++;
        }
        else if (rFrame == reference * 2)
        {
            if (gunType == "AR")
                srcRect.x = 669;
            else if (gunType == "SG")
                srcRect.x = 674;
            else if (gunType == "HG")
                srcRect.x = 708;
            srcRectFoot.x = 663;
            rFrame++;
        }
        else if (rFrame == reference * 3)
        {
            if (gunType == "AR")
                srcRect.x = 894;
            else if (gunType == "SG")
                srcRect.x = 899;
            else if (gunType == "HG")
                srcRect.x = 933;
            srcRectFoot.x = 881;
            rFrame++;
        }
        else if (rFrame == reference * 4)
        {
            if (gunType == "AR")
                srcRect.x = 1120;
            else if (gunType == "SG")
                srcRect.x = 1124;
            else if (gunType == "HG")
                srcRect.x = 1158;
            srcRectFoot.x = 1104;
            rFrame++;
        }
        else if (rFrame == reference * 5)
        {
            if (gunType == "AR")
                srcRect.x = 1345;
            else if (gunType == "SG")
                srcRect.x = 1350;
            else if (gunType == "HG")
                srcRect.x = 1383;
            srcRectFoot.x = 1329;
            rFrame = 0;
        }
        else
        {
            rFrame++;
        }
    }

    else if (direction == 'l')
    {
        dFrame = 0;
        rFrame = 0;
        uFrame = 0;
        if (lFrame == 0)
        {
            if (gunType == "AR")
                srcRect = {4073, 1350, 180, 105};
            else if (gunType == "SG")
                srcRect = {4080, 3252, 180, 105};
            else if (gunType == "HG")
                srcRect = {4060, 5141, 178, 131};
            srcRectFoot = {3473, 62, 146, 100};
            lFrame++;
        }
        else if (lFrame == reference)
        {
            if (gunType == "AR")
                srcRect.x = 3853;
            else if (gunType == "SG")
                srcRect.x = 3859;
            else if (gunType == "HG")
                srcRect.x = 3835;
            srcRectFoot.x = 3294;
            lFrame++;
        }
        else if (lFrame == reference * 2)
        {
            if (gunType == "AR")
                srcRect.x = 3627;
            else if (gunType == "SG")
                srcRect.x = 3634;
            else if (gunType == "HG")
                srcRect.x = 3610;
            srcRectFoot.x = 3108;
            lFrame++;
        }
        else if (lFrame == reference * 3)
        {
            if (gunType == "AR")
                srcRect.x = 3402;
            else if (gunType == "SG")
                srcRect.x = 3409;
            else if (gunType == "HG")
                srcRect.x = 3385;
            srcRectFoot.x = 2929;
            lFrame++;
        }
        else if (lFrame == reference * 4)
        {
            if (gunType == "AR")
                srcRect.x = 3177;
            else if (gunType == "SG")
                srcRect.x = 3183;
            else if (gunType == "HG")
                srcRect.x = 3160;
            srcRectFoot.x = 2753;
            lFrame++;
        }
        else if (lFrame == reference * 5)
        {
            if (gunType == "AR")
                srcRect.x = 2951;
            else if (gunType == "SG")
                srcRect.x = 2957;
            else if (gunType == "HG")
                srcRect.x = 2935;
            srcRectFoot.x = 2580;
            lFrame = 0;
        }
        else
        {
            lFrame++;
        }
    }

    else if (direction == 'u')
    {
        rFrame = 0;
        dFrame = 0;
        lFrame = 0;
        if (uFrame == 0)
        {
            if (gunType == "AR")
                srcRect = {3818, 4077, 106, 180};
            else if (gunType == "SG")
                srcRect = {1916, 4084, 106, 180};
            else if (gunType == "HG")
                srcRect = {2, 4064, 130, 178};
            srcRectFoot = {4923, 4070, 100, 176};
            uFrame++;
        }
        else if (uFrame == reference)
        {
            if (gunType == "AR")
                srcRect.y = 3856;
            else if (gunType == "SG")
                srcRect.y = 3863;
            else if (gunType == "HG")
                srcRect.y = 3839;
            srcRectFoot.y = 3860;
            uFrame++;
        }
        else if (uFrame == reference * 2)
        {
            if (gunType == "AR")
                srcRect.y = 3631;
            else if (gunType == "SG")
                srcRect.y = 3638;
            else if (gunType == "HG")
                srcRect.y = 3614;
            srcRectFoot.y = 3639;
            uFrame++;
        }
        else if (uFrame == reference * 3)
        {
            if (gunType == "AR")
                srcRect.y = 3406;
            else if (gunType == "SG")
                srcRect.y = 3413;
            else if (gunType == "HG")
                srcRect.y = 3389;
            srcRectFoot.y = 3429;
            uFrame++;
        }
        else if (uFrame == reference * 4)
        {
            if (gunType == "AR")
                srcRect.y = 3180;
            else if (gunType == "SG")
                srcRect.y = 3187;
            else if (gunType == "HG")
                srcRect.y = 3164;
            srcRectFoot.y = 3225;
            uFrame++;
        }
        else if (uFrame == reference * 5)
        {
            if (gunType == "AR")
                srcRect.y = 2954;
            else if (gunType == "SG")
                srcRect.y = 2961;
            else if (gunType == "HG")
                srcRect.y = 2939;
            srcRectFoot.y = 3023;
            uFrame = 0;
        }
        else
        {
            uFrame++;
        }
    }

    else if (direction == 'd')
    {
        uFrame = 0;
        rFrame = 0;
        lFrame = 0;
        if (dFrame == 0)
        {
            if (gunType == "AR")
                srcRect = {4760, 225, 107, 180};
            else if (gunType == "SG")
                srcRect = {3108, 230, 106, 180};
            else if (gunType == "HG")
                srcRect = {1534, 262, 130, 178};
            srcRectFoot = {3661, 236, 100, 176};
            dFrame++;
        }
        else if (dFrame == reference)
        {
            if (gunType == "AR")
                srcRect.y = 447;
            else if (gunType == "SG")
                srcRect.y = 452;
            else if (gunType == "HG")
                srcRect.y = 487;
            srcRectFoot.y = 455;
            dFrame++;
        }
        else if (dFrame == reference * 2)
        {
            if (gunType == "AR")
                srcRect.y = 673;
            else if (gunType == "SG")
                srcRect.y = 678;
            else if (gunType == "HG")
                srcRect.y = 712;
            srcRectFoot.y = 667;
            dFrame++;
        }
        else if (dFrame == reference * 3)
        {
            if (gunType == "AR")
                srcRect.y = 898;
            else if (gunType == "SG")
                srcRect.y = 903;
            else if (gunType == "HG")
                srcRect.y = 937;
            srcRectFoot.y = 885;
            dFrame++;
        }
        else if (dFrame == reference * 4)
        {
            if (gunType == "AR")
                srcRect.y = 1123;
            else if (gunType == "SG")
                srcRect.y = 1128;
            else if (gunType == "HG")
                srcRect.y = 1162;
            srcRectFoot.y = 1108;
            dFrame++;
        }
        else if (dFrame == reference * 5)
        {
            if (gunType == "AR")
                srcRect.y = 1349;
            else if (gunType == "SG")
                srcRect.y = 1354;
            else if (gunType == "HG")
                srcRect.y = 1387;
            srcRectFoot.y = 1333;
            dFrame = 0;
        }
        else
        {
            dFrame++;
        }
    }
}

void MainCharacter::Update()
{
    moverRect = {x_pos, y_pos, srcRect.w / 2, srcRect.h / 2};
    if (firingFrame == 2)
    {
        moverRect.x -= 2;
    }
    else if (firingFrame == 1)
    {
        moverRect.x += 2;
    }
    if (direction == 'i')
    {
        moverRectFoot = {x_pos + ((moverRect.w / 2) - ((srcRectFoot.w / 2)) / 2), y_pos + ((moverRect.h / 2) - ((srcRectFoot.h / 3) / 2)), srcRectFoot.w / 3, srcRectFoot.h / 3};
    }
    else if (direction == 'r')
    {
        moverRectFoot = {x_pos + ((moverRect.w / 2) - ((srcRectFoot.w / 2)) / 2), y_pos + ((moverRect.h / 2) - ((srcRectFoot.h / 3) / 2)), srcRectFoot.w / 3, srcRectFoot.h / 3};
        if (gunType == "HG")
            moverRectFoot.x += 10;
        else if (gunType == "SG")
            moverRectFoot.y += 3;
    }
    else if (direction == 'l')
    {
        moverRectFoot = {x_pos + ((moverRect.w / 2) - ((srcRectFoot.w / 2)) / 4), y_pos + ((moverRect.h / 2) - ((srcRectFoot.h / 3) / 2)), srcRectFoot.w / 3, srcRectFoot.h / 3};
        if (gunType == "SG")
            moverRectFoot.x += 10;
        else if (gunType == "AR")
            moverRectFoot.x += 10;
    }
    else if (direction == 'u')
    {
        moverRectFoot = {x_pos + ((moverRect.w / 2) - ((srcRectFoot.w / 2)) / 4), y_pos + ((moverRect.h / 2) - ((srcRectFoot.h / 3) / 2)), srcRectFoot.w / 3, srcRectFoot.h / 3};
        if (gunType == "SG")
            moverRectFoot.y += 10;
        else if (gunType == "AR")
            moverRectFoot.y += 10;
    }
    else if (direction == 'd')
    {
        moverRectFoot = {x_pos + ((moverRect.w / 2) - ((srcRectFoot.w / 2)) / 3), y_pos + ((moverRect.h / 2) - (srcRectFoot.h / 7)), srcRectFoot.w / 3, srcRectFoot.h / 3};
        if (gunType == "HG")
            moverRectFoot.x -= 4;
        else if (gunType == "SG")
        {
            moverRectFoot.y -= 10;
            moverRectFoot.x -= 3;
        }
        else if (gunType == "AR")
            moverRectFoot.y -= 10;
    }
    else
    {
        if (previous_direction == 'r' || previous_direction == 'n')
            moverRectFoot = {x_pos + ((moverRect.w / 2) - ((srcRectFoot.w / 2)) / 2), y_pos + ((moverRect.h / 2) - ((srcRectFoot.h / 3) / 2)) + 2, srcRectFoot.w / 3, srcRectFoot.h / 3};
        else if (previous_direction == 'l')
            moverRectFoot = {x_pos + ((moverRect.w / 2) - ((srcRectFoot.w / 2)) / 4), y_pos + ((moverRect.h / 2) - ((srcRectFoot.h / 3) / 2)), srcRectFoot.w / 3, srcRectFoot.h / 3};
        else if (previous_direction == 'u')
            moverRectFoot = {x_pos + ((moverRect.w / 2) - ((srcRectFoot.w / 2)) / 4), y_pos + ((moverRect.h / 2) - ((srcRectFoot.h / 3) / 2)), srcRectFoot.w / 3, srcRectFoot.h / 3};
        else if (previous_direction == 'd')
            moverRectFoot = {x_pos + ((moverRect.w / 2) - ((srcRectFoot.w / 2)) / 3) - 2, y_pos + ((moverRect.h / 2) - (srcRectFoot.h / 7)) + 2, srcRectFoot.w / 3, srcRectFoot.h / 3};
    }

    // moverRectFoot = {((moverRect.x + moverRect.w) / 2) - ((srcRectFoot.x + srcRectFoot.w) / 2), y_pos + ((moverRect.y + moverRect.h) / 2) - ((srcRectFoot.y + srcRectFoot.h) / 2), srcRectFoot.w / 3, srcRectFoot.h / 3};
}

void MainCharacter::Animator_reloading()
{
    if (gunType == "AR" && reloadAR)
    {
        reloadFrameHG = 0;
        reloadFrameSG = 0;
        if (previous_direction == 'r' || previous_direction == 'n')
        {
            if (reloadFrameAR == 0)
            {
                srcRect = {2726, 610, 177, 106};
                srcRectFoot = {4333, 82, 100, 114};
                reloadFrameAR++;
            }
            else if (reloadFrameAR == 11)
            {
                srcRect = {3173, 611, 181, 108};
                reloadFrameAR++;
            }
            else if (reloadFrameAR == 11 * 2)
            {
                srcRect = {3398, 611, 181, 109};
                reloadFrameAR++;
            }
            else if (reloadFrameAR == 11 * 3)
            {
                srcRect = {3848, 611, 180, 108};
                reloadFrameAR++;
            }
            else if (reloadFrameAR == 11 * 4)
            {
                srcRect = {4074, 611, 179, 108};
                reloadFrameAR++;
            }
            else if (reloadFrameAR == 11 * 5)
            {
                srcRect = {4299, 611, 179, 107};
                reloadFrameAR++;
            }
            else if (reloadFrameAR == 11 * 6)
            {
                srcRect = {252, 610, 176, 105};
                reloadFrameAR = 0;
                reloadAR = false;
                reloading = false;
                bullets_ar = 30;
            }
            else
            {
                reloadFrameAR++;
            }
        }

        else if (previous_direction == 'l')
        {
            if (reloadFrameAR == 0)
            {
                srcRect = {1571, 1148, 177, 106};
                srcRectFoot = {43, 1668, 98, 114};
                reloadFrameAR++;
            }
            else if (reloadFrameAR == 11)
            {
                srcRect = {1346, 1146, 179, 107};
                reloadFrameAR++;
            }
            else if (reloadFrameAR == 11 * 2)
            {
                srcRect = {1120, 1145, 181, 108};
                reloadFrameAR++;
            }
            else if (reloadFrameAR == 11 * 3)
            {
                srcRect = {895, 1144, 181, 109};
                reloadFrameAR++;
            }
            else if (reloadFrameAR == 11 * 4)
            {
                srcRect = {446, 1145, 180, 108};
                reloadFrameAR++;
            }
            else if (reloadFrameAR == 11 * 5)
            {
                srcRect = {221, 1145, 179, 108};
                reloadFrameAR++;
            }
            else if (reloadFrameAR == 11 * 6)
            {
                srcRect = {4271, 1150, 175, 104};
                reloadFrameAR = 0;
                reloadAR = false;
                reloading = false;
                bullets_ar = 30;
            }
            else
            {
                reloadFrameAR++;
            }
        }

        else if (previous_direction == 'u')
        {
            if (reloadFrameAR == 0)
            {
                srcRect = {4020, 1575, 106, 177};
                srcRectFoot = {3492, 47, 114, 98};
                reloadFrameAR++;
            }
            else if (reloadFrameAR == 11)
            {
                srcRect = {4021, 1349, 107, 180};
                reloadFrameAR++;
            }
            else if (reloadFrameAR == 11 * 2)
            {
                srcRect = {4021, 1124, 108, 181};
                reloadFrameAR++;
            }
            else if (reloadFrameAR == 11 * 3)
            {
                srcRect = {4021, 899, 109, 181};
                reloadFrameAR++;
            }
            else if (reloadFrameAR == 11 * 4)
            {
                srcRect = {4021, 450, 108, 180};
                reloadFrameAR++;
            }
            else if (reloadFrameAR == 11 * 5)
            {
                srcRect = {4021, 225, 108, 179};
                reloadFrameAR++;
            }
            else if (reloadFrameAR == 11 * 6)
            {
                srcRect = {4020, 4275, 104, 175};
                reloadFrameAR = 0;
                reloadAR = false;
                reloading = false;
                bullets_ar = 30;
            }
            else
            {
                reloadFrameAR++;
            }
        }

        else if (previous_direction == 'd')
        {
            if (reloadFrameAR == 0)
            {
                srcRect = {4558, 2730, 106, 177};
                srcRectFoot = {5078, 4337, 114, 98};
                reloadFrameAR++;
            }
            else if (reloadFrameAR == 11)
            {
                srcRect = {4556, 2953, 107, 180};
                reloadFrameAR++;
            }
            else if (reloadFrameAR == 11 * 2)
            {
                srcRect = {4555, 3177, 108, 181};
                reloadFrameAR++;
            }
            else if (reloadFrameAR == 11 * 3)
            {
                srcRect = {4554, 3402, 109, 181};
                reloadFrameAR++;
            }
            else if (reloadFrameAR == 11 * 4)
            {
                srcRect = {4555, 3852, 108, 180};
                reloadFrameAR++;
            }
            else if (reloadFrameAR == 11 * 5)
            {
                srcRect = {4555, 4078, 108, 179};
                reloadFrameAR++;
            }
            else if (reloadFrameAR == 11 * 6)
            {
                srcRect = {4560, 32, 104, 175};
                reloadFrameAR = 0;
                reloadAR = false;
                reloading = false;
                bullets_ar = 30;
            }
            else
            {
                reloadFrameAR++;
            }
        }
    }

    else if (gunType == "SG" && reloadSG)
    {
        reloadFrameHG = 0;
        reloadFrameAR = 0;
        if (previous_direction == 'r' || previous_direction == 'n')
        {
            if (reloadFrameSG == 0)
            {
                srcRect = {2726, 2525, 177, 106};
                srcRectFoot = {4333, 82, 100, 114};
                reloadFrameSG++;
            }
            else if (reloadFrameSG == 11)
            {
                srcRect = {2949, 2526, 181, 108};
                reloadFrameSG++;
            }
            else if (reloadFrameSG == 11 * 2)
            {
                srcRect = {3173, 2526, 181, 109};
                reloadFrameSG++;
            }
            else if (reloadFrameSG == 11 * 3)
            {
                srcRect = {3398, 2526, 181, 109};
                reloadFrameSG++;
            }
            else if (reloadFrameSG == 11 * 4)
            {
                srcRect = {3848, 2526, 180, 108};
                reloadFrameSG++;
            }
            else if (reloadFrameSG == 11 * 5)
            {
                srcRect = {4074, 2526, 179, 108};
                reloadFrameSG++;
            }
            else if (reloadFrameSG == 11 * 6)
            {
                srcRect = {28, 2525, 175, 104};
                reloadFrameSG = 0;
                reloadSG = false;
                reloading = false;
            }
            else
            {
                reloadFrameSG++;
            }
        }

        else if (previous_direction == 'l')
        {
            if (reloadFrameSG == 0)
            {
                srcRect = {1583, 2787, 177, 106};
                srcRectFoot = {43, 1668, 98, 114};
                reloadFrameSG++;
            }
            else if (reloadFrameSG == 11)
            {
                srcRect = {1357, 2785, 180, 107};
                reloadFrameSG++;
            }
            else if (reloadFrameSG == 11 * 2)
            {
                srcRect = {1132, 2784, 181, 108};
                reloadFrameSG++;
            }
            else if (reloadFrameSG == 11 * 3)
            {
                srcRect = {907, 2783, 181, 109};
                reloadFrameSG++;
            }
            else if (reloadFrameSG == 11 * 4)
            {
                srcRect = {682, 2784, 181, 108};
                reloadFrameSG++;
            }
            else if (reloadFrameSG == 11 * 5)
            {
                srcRect = {458, 2784, 180, 108};
                reloadFrameSG++;
            }
            else if (reloadFrameSG == 11 * 6)
            {
                srcRect = {4283, 2789, 175, 104};
                reloadFrameSG = 0;
                reloadSG = false;
                reloading = false;
            }
            else
            {
                reloadFrameSG++;
            }
        }

        else if (previous_direction == 'u')
        {
            if (reloadFrameSG == 0)
            {
                srcRect = {2381, 1587, 106, 177};
                srcRectFoot = {3492, 47, 114, 98};
                reloadFrameSG++;
            }
            else if (reloadFrameSG == 11)
            {
                srcRect = {2382, 1361, 107, 180};
                reloadFrameSG++;
            }
            else if (reloadFrameSG == 11 * 2)
            {
                srcRect = {2382, 1136, 108, 181};
                reloadFrameSG++;
            }
            else if (reloadFrameSG == 11 * 3)
            {
                srcRect = {2382, 911, 109, 181};
                reloadFrameSG++;
            }
            else if (reloadFrameSG == 11 * 4)
            {
                srcRect = {2382, 462, 108, 180};
                reloadFrameSG++;
            }
            else if (reloadFrameSG == 11 * 5)
            {
                srcRect = {2382, 237, 108, 179};
                reloadFrameSG++;
            }
            else if (reloadFrameSG == 11 * 6)
            {
                srcRect = {2381, 4287, 104, 175};
                reloadFrameSG = 0;
                reloadSG = false;
                reloading = false;
            }
            else
            {
                reloadFrameSG++;
            }
        }

        else if (previous_direction == 'd')
        {
            if (reloadFrameSG == 0)
            {
                srcRect = {2643, 2730, 106, 177};
                srcRectFoot = {5078, 4337, 114, 98};
                reloadFrameSG++;
            }
            else if (reloadFrameSG == 11)
            {
                srcRect = {2641, 2953, 108, 180};
                reloadFrameSG++;
            }
            else if (reloadFrameSG == 11 * 2)
            {
                srcRect = {2640, 3177, 109, 181};
                reloadFrameSG++;
            }
            else if (reloadFrameSG == 11 * 3)
            {
                srcRect = {2639, 3402, 110, 181};
                reloadFrameSG++;
            }
            else if (reloadFrameSG == 11 * 4)
            {
                srcRect = {2640, 3852, 109, 180};
                reloadFrameSG++;
            }
            else if (reloadFrameSG == 11 * 5)
            {
                srcRect = {2640, 4078, 109, 179};
                reloadFrameSG++;
            }
            else if (reloadFrameSG == 11 * 6)
            {
                srcRect = {2646, 32, 103, 175};
                reloadFrameSG = 0;
                reloadSG = false;
                reloading = false;
            }
            else
            {
                reloadFrameSG++;
            }
        }
    }

    else if (gunType == "HG" && reloadHG)
    {
        reloadFrameAR = 0;
        reloadFrameSG = 0;
        if (previous_direction == 'r' || previous_direction == 'n')
        {
            if (reloadFrameHG == 0)
            {
                srcRect = {1651, 4067, 180, 133};
                srcRectFoot = {4333, 82, 100, 114};
                reloadFrameHG++;
            }
            else if (reloadFrameHG == 11)
            {
                srcRect = {1883, 4067, 180, 135};
                reloadFrameHG++;
            }
            else if (reloadFrameHG == 11 * 2)
            {
                srcRect = {2345, 4068, 182, 139};
                reloadFrameHG++;
            }
            else if (reloadFrameHG == 11 * 3)
            {
                srcRect = {495, 4067, 177, 140};
                reloadFrameHG++;
            }
            else if (reloadFrameHG == 11 * 4)
            {
                srcRect = {727, 4066, 177, 138};
                reloadFrameHG++;
            }
            else if (reloadFrameHG == 11 * 5)
            {
                srcRect = {958, 4066, 178, 134};
                reloadFrameHG++;
            }
            else if (reloadFrameHG == 11 * 6)
            {
                srcRect = {1189, 4066, 179, 132};
                reloadFrameHG = 0;
                bullets_hg = 15;
                reloadHG = false;
                reloading = false;
            }
            else
            {
                reloadFrameHG++;
            }
        }

        else if (previous_direction == 'l')
        {
            if (reloadFrameHG == 0)
            {
                srcRect = {2665, 4682, 180, 133};
                srcRectFoot = {43, 1668, 98, 114};
                reloadFrameHG++;
            }
            else if (reloadFrameHG == 11)
            {
                srcRect = {2433, 4680, 180, 135};
                reloadFrameHG++;
            }
            else if (reloadFrameHG == 11 * 2)
            {
                srcRect = {1969, 4675, 182, 139};
                reloadFrameHG++;
            }
            else if (reloadFrameHG == 11 * 3)
            {
                srcRect = {3824, 4675, 177, 140};
                reloadFrameHG++;
            }
            else if (reloadFrameHG == 11 * 4)
            {
                srcRect = {3592, 4678, 177, 138};
                reloadFrameHG++;
            }
            else if (reloadFrameHG == 11 * 5)
            {
                srcRect = {3360, 4682, 178, 134};
                reloadFrameHG++;
            }
            else if (reloadFrameHG == 11 * 6)
            {
                srcRect = {3128, 4684, 179, 132};
                reloadFrameHG = 0;
                bullets_hg = 15;
                reloadHG = false;
                reloading = false;
            }
            else
            {
                reloadFrameHG++;
            }
        }

        else if (previous_direction == 'u')
        {
            if (reloadFrameHG == 0)
            {
                srcRect = {459, 2669, 133, 180};
                srcRectFoot = {3492, 47, 114, 98};
                reloadFrameHG++;
            }
            else if (reloadFrameHG == 11)
            {
                srcRect = {459, 2437, 135, 180};
                reloadFrameHG++;
            }
            else if (reloadFrameHG == 11 * 2)
            {
                srcRect = {460, 1973, 139, 182};
                reloadFrameHG++;
            }
            else if (reloadFrameHG == 11 * 3)
            {
                srcRect = {459, 3828, 140, 177};
                reloadFrameHG++;
            }
            else if (reloadFrameHG == 11 * 4)
            {
                srcRect = {458, 3596, 138, 178};
                reloadFrameHG++;
            }
            else if (reloadFrameHG == 11 * 5)
            {
                srcRect = {458, 3364, 134, 178};
                reloadFrameHG++;
            }
            else if (reloadFrameHG == 11 * 6)
            {
                srcRect = {458, 3132, 132, 179};
                reloadFrameHG = 0;
                bullets_hg = 15;
                reloadHG = false;
                reloading = false;
            }
            else
            {
                reloadFrameHG++;
            }
        }

        else if (previous_direction == 'd')
        {
            if (reloadFrameHG == 0)
            {
                srcRect = {1074, 1655, 133, 180};
                srcRectFoot = {5078, 4337, 114, 98};
                reloadFrameHG++;
            }
            else if (reloadFrameHG == 11)
            {
                srcRect = {1072, 1887, 135, 180};
                reloadFrameHG++;
            }
            else if (reloadFrameHG == 11 * 2)
            {
                srcRect = {1067, 2349, 139, 182};
                reloadFrameHG++;
            }
            else if (reloadFrameHG == 11 * 3)
            {
                srcRect = {1067, 499, 140, 177};
                reloadFrameHG++;
            }
            else if (reloadFrameHG == 11 * 4)
            {
                srcRect = {1070, 730, 138, 178};
                reloadFrameHG++;
            }
            else if (reloadFrameHG == 11 * 5)
            {
                srcRect = {1074, 962, 134, 178};
                reloadFrameHG++;
            }
            else if (reloadFrameHG == 11 * 6)
            {
                srcRect = {1076, 1193, 132, 179};
                reloadFrameHG = 0;
                reloadHG = false;
                bullets_hg = 15;
                reloading = false;
            }
            else
            {
                reloadFrameHG++;
            }
        }
    }
}

void MainCharacter::Update(char direction, int x, int y)
{
    if (this->previous_direction == 'i')
    {
        this->previous_direction = direction;
    }

    else if (direction != 'n')
    {
        previous_direction = direction;
    }
    this->direction = direction;

    if (firing)
        firingFrame = 2;
    else
        firingFrame = 1;

    if (reloading)
        Animator_reloading();
    else
        Animator(direction);

    if (x <= 0)
    {
        if (x_pos <= 600)
        {
            inside_box_x = true;
        }
        else
        {
            if (direction == 'l')
            {
                x_pos -= 5;
                inside_box_x = true;
            }
            inside_box_x = false;
        }
    }

    if (x >= 4800)
    {
        if (x_pos >= 600)
        {
            inside_box_x = true;
        }
        else
        {
            if (direction == 'r')
            {
                x_pos += 5;
                inside_box_x = true;
            }
            inside_box_x = false;
        }
    }

    if (y <= 0)
    {
        if (y_pos <= 400)
        {
            inside_box_y = true;
        }
        else
        {
            if (direction == 'u')
            {
                y_pos -= 5;
                inside_box_y = true;
            }
            inside_box_y = false;
        }
    }

    if (y >= 3200)
    {
        if (y_pos >= 400)
        {
            inside_box_y = true;
        }
        else
        {
            if (direction == 'd')
            {
                y_pos += 5;
                inside_box_y = true;
            }
            inside_box_y = false;
        }
    }

    if (inside_box_y)
    {
        if (direction == 'u')
        {
            if (y_pos != 400)
                y_pos -= 5;
            // std::cout << moverRect.y << std::endl;
        }
        else if (direction == 'd')
        {
            if (y_pos != 3600)
                y_pos += 5;
        }
    }

    if (inside_box_x)
    {
        if (direction == 'l')
        {
            if (x_pos != 600)
                x_pos -= 5;
        }
        else if (direction == 'r')
        {
            if (x_pos <= 600)
                x_pos += 5;
        }
    }

    Update();
}

void MainCharacter::Update(char direction, int x, int y, int speedx, int speedy)
{
    Update(direction, x, y);
    if (!this->bullets.empty())
    {
        for (Bullets *bullet : bullets)
        {
            bullet->Update(previous_direction, speedx, speedy);
        }
    }
}

void MainCharacter::Render()
{
    if (direction == 'l' || direction == 'r' || direction == 'i')
    {
        SDL_RenderCopy(renderer, foot1, &srcRectFoot, &moverRectFoot);
        SDL_RenderCopy(renderer, t1, &srcRect, &moverRect);
    }
    else if (direction == 'n')
    {
        if (this->previous_direction == 'r' || this->previous_direction == 'l' || this->previous_direction == 'n')
        {
            SDL_RenderCopy(renderer, foot1, &srcRectFoot, &moverRectFoot);
            SDL_RenderCopy(renderer, t1, &srcRect, &moverRect);
        }
        else
        {
            SDL_RenderCopy(renderer, foot2, &srcRectFoot, &moverRectFoot);
            SDL_RenderCopy(renderer, t2, &srcRect, &moverRect);
        }
    }
    else
    {
        SDL_RenderCopy(renderer, foot2, &srcRectFoot, &moverRectFoot);
        SDL_RenderCopy(renderer, t2, &srcRect, &moverRect);
    }
    if (!this->bullets.empty())
    {
        for (Bullets *bullet : bullets)
        {
            bullet->Render();
        }
    }
    if (firingFrame == 2)
        firingFrame = 1;
}

void MainCharacter::Run(bool runs)
{
    if (runs)
    {
        reference = 4;
    }
    else
    {
        reference = 7;
    }
}

SDL_Rect *MainCharacter::getMoverRect()
{
    return &moverRect;
}

void MainCharacter::Fire()
{
    if (gunType == "AR")
    {
        Uint32 currentTime = SDL_GetTicks();
        if ((bullets_ar > 0) && (!reloading) && (currentTime - lastFireTimeAR >= fireRateAR))
        {
            lastFireTimeAR = currentTime;
            if (this->previous_direction == 'r' || this->previous_direction == 'n')
                bullets.push_back(new ARBullets("assets/bullets.png", renderer, x_pos + moverRect.w, y_pos + moverRect.h - 17, this->previous_direction));
            else if (this->previous_direction == 'l')
                bullets.push_back(new ARBullets("assets/bullets.png", renderer, x_pos - 9, y_pos + 8, this->previous_direction));
            else if (this->previous_direction == 'u')
                bullets.push_back(new ARBullets("assets/bullets.png", renderer, x_pos + moverRect.w - 17, y_pos - 9, this->previous_direction));
            else if (this->previous_direction == 'd')
                bullets.push_back(new ARBullets("assets/bullets.png", renderer, x_pos + 9, y_pos + moverRect.h, this->previous_direction));
            bullets_ar--;
        }
        else if (bullets_ar == 0)
        {
            reloadAR = true;
            reloading = true;
        }
    }
    else if (gunType == "SG")
    {
        if (this->previous_direction == 'r' || this->previous_direction == 'n')
            bullets.push_back(new ShotgunBullets("assets/bullets.png", renderer, x_pos + moverRect.w, y_pos + moverRect.h - 17, this->previous_direction));
        else if (this->previous_direction == 'l')
            bullets.push_back(new ShotgunBullets("assets/bullets.png", renderer, x_pos - 9, y_pos + 8, this->previous_direction));
        else if (this->previous_direction == 'u')
            bullets.push_back(new ShotgunBullets("assets/bullets.png", renderer, x_pos + moverRect.w - 17, y_pos - 9, this->previous_direction));
        else if (this->previous_direction == 'd')
            bullets.push_back(new ShotgunBullets("assets/bullets.png", renderer, x_pos + 9, y_pos + moverRect.h, this->previous_direction));
    }
    else if (gunType == "HG")
    {
        Uint32 currentTime = SDL_GetTicks();
        if ((bullets_hg > 0) && (!reloading) && (currentTime - lastFireTimeHG >= fireRateHG))
        {
            lastFireTimeHG = currentTime;
            if (this->previous_direction == 'r' || this->previous_direction == 'n')
                bullets.push_back(new HandGunBullets("assets/bullets.png", renderer, x_pos + moverRect.w, y_pos + moverRect.h - 17, this->previous_direction));
            else if (this->previous_direction == 'l')
                bullets.push_back(new HandGunBullets("assets/bullets.png", renderer, x_pos - 9, y_pos + 8, this->previous_direction));
            else if (this->previous_direction == 'u')
                bullets.push_back(new HandGunBullets("assets/bullets.png", renderer, x_pos + moverRect.w - 17, y_pos - 9, this->previous_direction));
            else if (this->previous_direction == 'd')
                bullets.push_back(new HandGunBullets("assets/bullets.png", renderer, x_pos + 9, y_pos + moverRect.h, this->previous_direction));
            bullets_hg--;
        }
        else if (bullets_hg == 0)
        {
            reloadHG = true;
            reloading = true;
        }
    }
}

void MainCharacter::setReload()
{
    reloading = true;
    if (gunType == "AR")
    {
        reloadAR = true;
    }
    else if (gunType == "HG")
    {
        reloadHG = true;
    }
    else if (gunType == "SG")
    {
        reloadSG = true;
    }
}