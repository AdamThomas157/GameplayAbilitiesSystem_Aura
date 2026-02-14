// Copyright Adam Thomas


#include "UI/WidgetController/SpellMenuWidgetController.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/Data/AbilityInfo.h"
#include "Player/AuraPlayerState.h"

void USpellMenuWidgetController::BroadcastInitialValues()
{
    BroadcastAbilityInfo();
    SpellPointsChanged.Broadcast(GetAuraPS()->GetSpellPoints());
}

void USpellMenuWidgetController::BindCallbacksToDependencies()
{
    GetAuraASC()->AbilityStatusChanged.AddLambda([this](const FGameplayTag& AbilityTag, const FGameplayTag& StatusTag)
    {
        if (AbilityInfo)
        {
            FAuraAbilityInfo Info = AbilityInfo->FindAbilityInfoForTag(AbilityTag);
            Info.StatusTag = StatusTag;
            AbilityInfoDelegate.Broadcast(Info);
        }
    });

    GetAuraPS()->OnSpellPointsChangedDelegate.AddLambda([this](int32 SpellPoints)
    {
        SpellPointsChanged.Broadcast(SpellPoints);
    });
}

void USpellMenuWidgetController::SpellGlobeSelected(const FGameplayTag& AbilityTag)
{
    const FAuraGameplayTags GameplayTags = FAuraGameplayTags::Get();
    const int32 SpellPoints = GetAuraPS()->GetSpellPoints();
    FGameplayTag AbilityStatus;

    const bool bTagValid = AbilityTag.IsValid();
    const bool bTagNone = AbilityTag.MatchesTag(GameplayTags.Abilities_None);
    const FGameplayAbilitySpec* AbilitySpec = GetAuraASC()->GetSpecFromAbilityTag(AbilityTag);
    const bool bSpecValid = AbilitySpec != nullptr;

    /* check if Tag is not valid or Tag is None or Spec is not valid, 
     * if either of the three cases are true then make the ability status locked 
     * Otherwise make status be the status from spec on the ability system component
     */

    if (!bTagValid || bTagNone || !bSpecValid)
    {
        AbilityStatus = GameplayTags.Abilities_Status_Locked;
    }
    else
    {
        AbilityStatus = GetAuraASC()->GetStatusFromSpec(*AbilitySpec);
    }

    bool bEnableSpellPoints = false;
    bool bEnableEquip = false;
    ShouldEnableButtons(AbilityStatus, SpellPoints, bEnableSpellPoints, bEnableEquip);
    SpellGlobeSelectedDelegate.Broadcast(bEnableSpellPoints, bEnableEquip);
}

void USpellMenuWidgetController::ShouldEnableButtons(const FGameplayTag& AbilityStatus, int32 SpellPoints, bool& bShouldEnableSpendPointsButton, bool& bShouldEquipButtonEnabled)
{
    const FAuraGameplayTags GameplayTags = FAuraGameplayTags::Get();

    bShouldEnableSpendPointsButton = false;
    bShouldEquipButtonEnabled = false;

    /*
        Check all statuses individually with else if clauses:

        Status Equipped -> enable equip button and check if spell points are greater than 0, if also true enable spend points button
        Status Eligible -> if spell points are greater than 0 then enable spend points button
        Status Unlocked -> enable equip button and check if spell points are greater than 0, if also true enable spend points button
    */

    if (AbilityStatus.MatchesTagExact(GameplayTags.Abilities_Status_Equipped))
    {
        bShouldEquipButtonEnabled = true;
        
        if (SpellPoints > 0)
        {
            bShouldEnableSpendPointsButton = true;
        }
    }
    else if (AbilityStatus.MatchesTagExact(GameplayTags.Abilities_Status_Eligible))
    {
        if (SpellPoints > 0)
        {
            bShouldEnableSpendPointsButton = true;
        }
    }
    else if (AbilityStatus.MatchesTagExact(GameplayTags.Abilities_Status_Unlocked))
    {
        bShouldEquipButtonEnabled = true;

        if (SpellPoints > 0)
        {
            bShouldEnableSpendPointsButton = true;
        }
    }
}
