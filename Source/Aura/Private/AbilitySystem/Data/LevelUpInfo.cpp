// Copyright Adam Thomas


#include "AbilitySystem/Data/LevelUpInfo.h"

int32 ULevelUpInfo::FindLevelForXP(int32 XP)
{
    int32 Level = 1;

    bool bSearching = true;

    while(bSearching)
    {
        // If LevelUpInformation.Num() - 1 <= Level then just return current level as 1
        if(LevelUpInformation.Num() - 1 <= Level) return Level;

        /*
            If the player's XP exceeds the current LevelUpInformation for player position's 
            LevelUpRequirement then increment Level, otherwise stop searching and return either next level or current level
        */

        if(XP >= LevelUpInformation[Level].LevelUpRequirement)
        {
            ++Level;
        }
        else
        {
            bSearching = false;
        }
    }
    return Level;
}
