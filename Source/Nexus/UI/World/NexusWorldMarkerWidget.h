// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"

#include "GameplayTagContainer.h"

#include "NexusWorldMarkerWidget.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(
    FOnMarkerStateTagChanged, FGameplayTag, Tag, bool, bAdded);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMarkerContextChanged);


UCLASS(Abstract, Blueprintable)
class NEXUS_API UNexusWorldMarkerWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "World Marker|Context")
    void SetContext(USceneComponent* InAnchor, AActor* InContextActor);
    
    UPROPERTY(BlueprintAssignable, Category = "World Marker|Context")
    FOnMarkerContextChanged OnContextChanged;
    
public:
    // Utility
    UFUNCTION(BlueprintPure, Category = "World Marker|Context")
    USceneComponent* GetAnchor() const { return Anchor.Get(); }

    UFUNCTION(BlueprintPure, Category = "World Marker|Context")
    AActor* GetContextActor() const { return ContextActor.Get(); }
    
    UFUNCTION(BlueprintPure, Category = "World Marker|Context")
    FVector GetWorldLocation() const;

public:
    // State
    UFUNCTION(BlueprintCallable, Category = "World Marker|State")
    void AddStateTag(const FGameplayTag Tag);
    
    UFUNCTION(BlueprintCallable, Category = "World Marker|State")
    void RemoveStateTag(const FGameplayTag Tag);
    
    UFUNCTION(BlueprintCallable, Category = "World Marker|State")
    void SetStateTags(const FGameplayTagContainer& NewTags);

    UFUNCTION(BlueprintPure, Category = "World Marker|State")
    bool HasStateTag(const FGameplayTag Tag) const { return StateTags.HasTag(Tag); }

    UFUNCTION(BlueprintPure, Category = "World Marker|State")
    bool HasAnyStateTags(const FGameplayTagContainer& Tags) const { return StateTags.HasAny(Tags); }

    UFUNCTION(BlueprintPure, Category = "World Marker|State")
    bool HasAllStateTags(const FGameplayTagContainer& Tags) const { return StateTags.HasAll(Tags); }

    UFUNCTION(BlueprintPure, Category = "World Marker|State")
    const FGameplayTagContainer& GetStateTags() const { return StateTags; }

public:
    // Delegates
    UPROPERTY(BlueprintAssignable, Category = "World Marker|State")
    FOnMarkerStateTagChanged OnStateTagChanged;

protected:
    /** BP hook for context changes — useful for one-time setup (e.g. caching references). */
    UFUNCTION(BlueprintImplementableEvent, Category = "World Marker|Context",
        meta = (DisplayName = "On Context Changed"))
    void K2_OnContextChanged();
    /**
     * Called after StateTags changes. Default impl broadcasts OnStateTagChanged
     * and fires the BP event. Override in C++ children if needed.
     */
    virtual void HandleStateTagChanged(const FGameplayTag Tag, const bool bAdded);

    /** BP hook for state changes. Fires after OnStateTagChanged broadcasts. */
    UFUNCTION(BlueprintImplementableEvent, Category = "World Marker|State",
        meta = (DisplayName = "On State Tag Changed"))
    void K2_OnStateTagChanged(FGameplayTag Tag, bool bAdded);

private:
    UPROPERTY(Transient)
    FGameplayTagContainer StateTags;

    UPROPERTY(Transient)
    TWeakObjectPtr<USceneComponent> Anchor;

    UPROPERTY(Transient)
    TWeakObjectPtr<AActor> ContextActor;
};