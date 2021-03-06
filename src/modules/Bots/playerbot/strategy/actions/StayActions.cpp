#include "botpch.h"
#include "../../playerbot.h"
#include "StayActions.h"
#include "../values/LastMovementValue.h"

using namespace ai;

void StayActionBase::Stay()
{
    AI_VALUE(LastMovement&, "last movement").Set(NULL);

    MotionMaster &mm = *bot->GetMotionMaster();
    if (mm.GetCurrentMovementGeneratorType() == FLIGHT_MOTION_TYPE || bot->IsFlying())
        return;

    mm.Clear();
    bot->InterruptMoving();
	bot->clearUnitState(UNIT_STAT_CHASE);
	bot->clearUnitState(UNIT_STAT_FOLLOW);

    if (!bot->IsStandState())
        bot->SetStandState(UNIT_STAND_STATE_STAND);
}

bool StayAction::Execute(Event event)
{
    Stay();

    return true;
}

bool StayAction::isUseful()
{
    return !AI_VALUE2(bool, "moving", "self target");
}
