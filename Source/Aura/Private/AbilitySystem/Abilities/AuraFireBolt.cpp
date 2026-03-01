// Copyright Adam Thomas


#include "AbilitySystem/Abilities/AuraFireBolt.h"
#include "Aura/Public/AuraGameplayTags.h"

FString UAuraFireBolt::GetDescription(int32 Level)
{
    const int32 Damage = GetDamageByDamageType(Level, FAuraGameplayTags::Get().Damage_Fire);
    const float ManaCost = FMath::Abs(GetManaCost(Level));
    const float Cooldown = GetCooldown(Level);

    if (Level == 1)
    {
        return FString::Printf(TEXT(
                //Title
                "<Title>FIRE BOLT</>\n\n"

                //Level
                "<Small>Level: </><Level>%d</>\n"

                //ManaCost
                "<Small>Mana Cost: </><ManaCost>%.1f</>\n"

                //Cooldown
                "<Small>Cooldown: </><Cooldown>%.1f</>\n"

                //Description
                "<Default>Launches a bolt of fire, exploding on impact, dealing: </>"

                //Damage
                "<Damage>%d</><Default> fire damage with a chance to burn.</>\n\n"
            ), 
                //Values
                Level,
                ManaCost,
                Cooldown,
                Damage);
    }
    else
    {
        return FString::Printf(TEXT(
                "<Title>FIRE BOLT</>\n\n"
                
                "<Small>Level: </><Level>%d</>\n"

                "<Small>Mana Cost: </><ManaCost>%.1f</>\n"

                "<Small>Cooldown: </><Cooldown>%.1f</>\n"

                "<Default>Launches %d bolts of fire, exploding on impact dealing: </>"

                "<Damage>%d</><Default> fire damage with a chance to burn.</>\n\n"
            ),
                Level,
                ManaCost,
                Cooldown,
                FMath::Min(Level, NumProjectiles),
                Damage
            );
    }
}

FString UAuraFireBolt::GetNextLevelDescription(int32 Level)
{
    const int32 Damage = GetDamageByDamageType(Level, FAuraGameplayTags::Get().Damage_Fire);
    const float ManaCost = FMath::Abs(GetManaCost(Level));
    const float Cooldown = GetCooldown(Level);

    return FString::Printf(TEXT(
            "<Title>NEXT LEVEL</>\n\n"

            "<Small>Level: </><Level>%d</>\n"

            "<Small>Mana Cost: </><ManaCost>%.1f</>\n"

            "<Small>Cooldown: </><Cooldown>%.1f</>\n"

            "<Default>Launches %d bolts of fire, exploding on impact dealing: </>"

            "<Damage>%d</><Default> fire damage with a chance to burn.</>"
        ),
            Level,
            ManaCost,
            Cooldown,
            FMath::Min(Level, NumProjectiles),
            Damage
        );
}
