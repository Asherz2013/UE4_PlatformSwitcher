// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PLATFORMSWITCHER_API AMainGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:

    virtual void BeginPlay() override;

    virtual void Tick(float DeltaTime) override;
	
    bool Switched;

    void OnSwitch();

    void OnRestart();

    void OnGameOver(bool win);

    UFUNCTION(BlueprintCallable, Category = "UMG Game")
    void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWIdgetClass);

protected:

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
    TSubclassOf<UUserWidget> StartingWidgetClass;

    UPROPERTY()
    UUserWidget* CurrentWidget;
};
