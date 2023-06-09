// Fill out your copyright notice in the Description page of Project Settings.


#include "RedGhost.h"

// Sets default values
ARedGhost::ARedGhost()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ARedGhost::BeginPlay()
{
	Super::BeginPlay();
	Spawn.X = 1100;
	Spawn.Y = 1400;
	Spawn.Z = 11;
	

	TArray<AActor*> temp;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), Alabirinto::StaticClass(), temp);
	if (temp.IsValidIndex(0))
		labirinto = Cast<Alabirinto>(temp[0]);


	else {
		UE_LOG(LogTemp, Warning, TEXT("ARedGhost: ERROR: Missing Alabirinto"));
		return;
	}

	TArray<AActor*> temp1;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APacman::StaticClass(), temp1);
	if (temp1.IsValidIndex(0))
		pacman = Cast<APacman>(temp1[0]);


	else {
		UE_LOG(LogTemp, Warning, TEXT("ARedGhost: ERROR: Missing APacman"));
		return;
	}

	TargetAngolo();
}


// Called every frame
void ARedGhost::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (pacmanLifes != pacman->getLives())
	{
		pacmanLifes = pacman->getLives();

		Cast<AActor>(this)->SetActorLocation(Spawn, false, nullptr, ETeleportType::TeleportPhysics);
	}
	if (pacman->GhostHunterMode())
		tempS = false;
	if (getPosX() == pacman->getPosX() && getPosY() == pacman->getPosY())
	{
		if (pacman->GhostHunterMode() && !eaten || tempS)
		{
			//pacman muore
			pacman->die();
			FVector NewLocation = FVector(11, 14, 0) * 100;
			SetActorLocation(NewLocation, false, nullptr, ETeleportType::TeleportPhysics);
		}
		else
		{
			TickInterface(DeltaTime, 11, 14, labirinto, pacman);//il fantasma torna casa
			eaten = true;

		}
	}
	else {
		if (eaten)
		{
			if (getPosX() == 11 && getPosY() == 14)
			{
				eaten = false;
				tempS = true;
			}
			TickInterface(DeltaTime, 11, 14, labirinto, pacman);//il fantasma torna casa
		}
		else if (GetWorldTimerManager().IsTimerActive(TimerAngolo) && pacman->GhostHunterMode())
		{
			TickInterface(DeltaTime, TargetAngoloX, TargetAngoloY, labirinto, pacman);
		}
		else
		{
			TickInterface(DeltaTime, pacman->getPosX(), pacman->getPosY(), labirinto, pacman);
		}
	}

	//gestire uscita di fantasma dalla casa
	
}

