#include "../p_local.h"
#include "../k_objects.h"

#define ARKARROW_SCALE (2<<FRACBITS)
#define ARKARROW_ZOFFSET (19<<FRACBITS)
#define ARKARROW_BOBRANGE (64<<FRACBITS)
#define ARKARROW_BOBSPEED (5<<FRACBITS)
#define ARKARROW_OPTIONS 42

void Obj_ArkArrowSpawn(mobj_t *mobj)
{
	mobj->extravalue1 = mobj->z;
	mobj->extravalue2 = FixedMul(mobj->x + mobj->y, mapobjectscale);
}

void Obj_ArkArrowSetup(mobj_t *mobj, mapthing_t *mthing)
{
	const fixed_t oldHeight = mobj->height;
	statenum_t stateNum = mobj->info->spawnstate + mthing->args[0];

	if (stateNum - mobj->info->spawnstate >= ARKARROW_OPTIONS)
	{
		CONS_Alert(CONS_WARNING, "Ark Arrow with symbol ID %d is larger than maximum symbol ID (%d)!\n", stateNum, ARKARROW_OPTIONS - 1);
		stateNum = mobj->info->spawnstate;
	}

	mobj->angle += ANGLE_90;
	P_SetScale(mobj, mobj->destscale = 4 * FixedMul(mobj->scale, ARKARROW_SCALE));
	mobj->z += 4 * FixedMul(mapobjectscale, ARKARROW_ZOFFSET) * P_MobjFlip(mobj);

	if (mthing->options & MTF_OBJECTFLIP)
	{
		mobj->z += oldHeight - mobj->height;
	}

	mobj->extravalue1 = mobj->old_z = mobj->z;
	P_SetMobjState(mobj, stateNum);
}

void Obj_ArkArrowThink(mobj_t *mobj)
{
	fixed_t offset = FixedMul(mapobjectscale,
		FixedMul(ARKARROW_BOBRANGE,
			FixedMul(FINESINE(FixedAngle(leveltime * ARKARROW_BOBSPEED + mobj->extravalue2) >> ANGLETOFINESHIFT) + FRACUNIT, FRACUNIT >> 1)
		)
	);

	mobj->z = mobj->extravalue1 + P_MobjFlip(mobj) * offset;
}