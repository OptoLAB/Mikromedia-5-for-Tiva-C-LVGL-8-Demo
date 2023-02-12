/*
 * Author: J. Bajic, 2022.
 */

#include "gui/images/gears_anim.h"

LV_IMG_DECLARE(gears_01)
LV_IMG_DECLARE(gears_02)
LV_IMG_DECLARE(gears_03)
LV_IMG_DECLARE(gears_04)
LV_IMG_DECLARE(gears_05)

static const lv_img_dsc_t* anim_imgs[5] = {
    &gears_01,
    &gears_02,
    &gears_03,
    &gears_04,
    &gears_05,
};

lv_obj_t * lv_create_gears_anim(lv_obj_t *parent)
{
    lv_obj_t * animimg = lv_animimg_create(parent);
    lv_animimg_set_src(animimg, (lv_img_dsc_t**) anim_imgs, 5);
    lv_animimg_set_duration(animimg, 500);
    lv_animimg_set_repeat_count(animimg, LV_ANIM_REPEAT_INFINITE);
    lv_animimg_start(animimg);

    return animimg;
}

