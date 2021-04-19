// Fill out your copyright notice in the Description page of Project Settings.

#include "OrbController.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MainGameMode.h"

// Sets default values
AOrbController::AOrbController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    RootBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Root"));
    RootBox->bGenerateOverlapEvents = true;
    RootBox->OnComponentBeginOverlap.AddDynamic(this, &AOrbController::OnOverlap);
}

// Called when the game starts or when spawned
void AOrbController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AOrbController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AOrbController::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor == (AActor*)UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
    {
        ((AMainGameMode*)GetWorld()->GetAuthGameMode())->OnGameOver(true);
    }
}

