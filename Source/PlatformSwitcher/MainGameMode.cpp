// Fill out your copyright notice in the Description page of Project Settings.

#include "MainGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "GameWidget.h"


void AMainGameMode::BeginPlay()
{
    Super::BeginPlay();

    ChangeMenuWidget(StartingWidgetClass);

    ((UGameWidget*)CurrentWidget)->Load();

    GetWorld()->GetFirstPlayerController()->InputComponent->BindAction("Switch", IE_Pressed, this, &AMainGameMode::OnSwitch);
    GetWorld()->GetFirstPlayerController()->InputComponent->BindAction("Restart", IE_Pressed, this, &AMainGameMode::OnRestart).bExecuteWhenPaused = true;
}

void AMainGameMode::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AMainGameMode::OnSwitch()
{
    // Layer 1 (X=1200)
    // Layer 2 (X=410)

    FVector NewLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
    if (Switched)
    {
        NewLocation.X = 1200.0f;
    }
    else
    {
        NewLocation.X = 410.0f;
    }
    GetWorld()->GetFirstPlayerController()->GetPawn()->SetActorLocation(NewLocation);

    Switched = !Switched;
}

void AMainGameMode::OnRestart()
{
    UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}

void AMainGameMode::OnGameOver(bool win)
{
    ((UGameWidget*)CurrentWidget)->OnGameOver(win);

    UGameplayStatics::SetGamePaused(GetWorld(), true);
}

void AMainGameMode::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWIdgetClass)
{
    if (CurrentWidget)
    {
        CurrentWidget->RemoveFromViewport();
        CurrentWidget = nullptr;
    }

    if (NewWIdgetClass)
    {
        CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), NewWIdgetClass);
        if (CurrentWidget)
        {
            CurrentWidget->AddToViewport();
        }
    }
}
