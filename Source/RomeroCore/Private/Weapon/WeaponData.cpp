#include "Weapon/WeaponData.h"

#include "Weapon/Weapon.h"

UWeaponData::UWeaponData()
{
	ObjectClass = UWeapon::StaticClass();
	CanEquip = true;
}