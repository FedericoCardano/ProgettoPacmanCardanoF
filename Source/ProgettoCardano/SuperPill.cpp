// Fill out your copyright notice in the Description page of Project Settings.


#include "SuperPill.h"
#include <Kismet/GameplayStatics.h>
#include "labirinto.h"

// Sets default values
ASuperPill::ASuperPill()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASuperPill::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<AActor*>temp;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), Alabirinto::StaticClass(), temp);
	if (temp.IsValidIndex(0))
		labirinto = (temp[0]);


	else {
		UE_LOG(LogTemp, Warning, TEXT("PPacman: ERROR: Missing Alabirinto"));
		return;
	}

	posX = FMath::DivideAndRoundNearest((int)GetActorLocation().X, 100);
	posY = FMath::DivideAndRoundNearest((int)GetActorLocation().Y, 100);
}

// Called every frame
void ASuperPill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Super::Tick(DeltaTime);
	if (Cast<Alabirinto>(labirinto)->getMap(posX, posY) != 'Q')
	{
		Cast<UStaticMeshComponent>(this->GetDefaultSubobjectByName("Cylinder"))->SetVisibility(false);
	}
}

