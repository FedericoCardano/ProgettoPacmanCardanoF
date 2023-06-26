// Fill out your copyright notice in the Description page of Project Settings.


#include "eClass.h"

// Sets default values
AeClass::AeClass()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AeClass::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*>temp;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), Alabirinto::StaticClass(), temp);
	if (temp.IsValidIndex(0))
		labirinto = Cast<Alabirinto>(temp[0]);
	else {
		UE_LOG(LogTemp, Warning, TEXT("PPacman: ERROR: Missing Alabirinto"));
		return;
	}
}

// Called every frame
void AeClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (labirinto->loser)
	{
		FVector NewLocation = FVector(GetActorLocation().X, GetActorLocation().Y, 1);
		SetActorLocation(NewLocation, false, nullptr, ETeleportType::TeleportPhysics);
	}
}

