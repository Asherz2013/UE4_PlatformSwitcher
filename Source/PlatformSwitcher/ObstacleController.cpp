// Fill out your copyright notice in the Description page of Project Settings.

#include "ObstacleController.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MainGameMode.h"


// Sets default values
AObstacleController::AObstacleController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    RootBox = CreateDefaultSubobject<UBoxComponent>(TEXT("ROOT"));
    RootBox->bGenerateOverlapEvents = true;
    RootBox->OnComponentBeginOverlap.AddDynamic(this, &AObstacleController::OnOverlap);

    RootComponent = RootBox;
}

// Called when the game starts or when spawned
void AObstacleController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AObstacleController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AObstacleController::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor == (AActor*)UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
    {
        ((AMainGameMode*)GetWorld()->GetAuthGameMode())->OnGameOver(false);
    }
}

