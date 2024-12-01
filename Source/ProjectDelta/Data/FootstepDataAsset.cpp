// Copyright Lede Studios. All Rights Reserved.


#include "FootstepDataAsset.h"

FFootstepSound UFootstepDataAsset::GetFootstepSoundByType(const UPhysicalMaterial* InType)
{
	for (FFootstepSound Data : FootstepSounds)
	{
		if (InType == Data.PhysicalMaterial)
		{
			return Data;
		}
	}
	return FFootstepSound();
}
