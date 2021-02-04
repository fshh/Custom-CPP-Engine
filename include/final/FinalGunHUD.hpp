#ifndef INCLUDE_FINAL_FINALGUNHUD_HPP_
#define INCLUDE_FINAL_FINALGUNHUD_HPP_

#include "base/GameObject.hpp"
#include "base/Resource.hpp"
#include "final/FinalGunManagerComponent.hpp"

class FinalGunHUD: public GameObject {
public:
	FinalGunHUD(float x, float y, float w, float h, int tag, SDLTextureResource* sprite, std::shared_ptr<GunManagerComponent> gunManager);
};

#endif /* INCLUDE_FINAL_FINALGUNHUD_HPP_ */
