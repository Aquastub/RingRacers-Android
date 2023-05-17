#include "../doomdef.h"
#include "../info.h"
#include "../k_objects.h"
#include "../p_local.h"

void Obj_InstaWhipThink (mobj_t *whip)
{
    if (P_MobjWasRemoved(whip->target))
    {
        P_RemoveMobj(whip);
    }
    else
    {
        whip->flags &= ~(MF_NOCLIPTHING);
		P_MoveOrigin(whip, whip->target->x, whip->target->y, whip->target->z + whip->target->height/2);
		whip->flags |= MF_NOCLIPTHING;

        whip->angle = whip->target->angle + (ANG30 * 2 * whip->fuse);

        whip->renderflags |= RF_NOSPLATBILLBOARD;

        if (whip->renderflags & RF_DONTDRAW)
            whip->renderflags &= ~RF_DONTDRAW;
        else
            whip->renderflags |= RF_DONTDRAW;

        P_SetScale(whip, whip->target->scale);
    }
}