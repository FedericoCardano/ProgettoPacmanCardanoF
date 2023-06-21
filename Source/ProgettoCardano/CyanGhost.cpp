// Fill out your copyright notice in the Description page of Project Settings.


#include "CyanGhost.h"

// Sets default values
ACyanGhost::ACyanGhost()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACyanGhost::BeginPlay()
{
	Super::BeginPlay();
	Spawn.X = 1100;
	Spawn.Y = 1200;
	Spawn.Z = 11;

	TArray<AActor*> temp;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), Alabirinto::StaticClass(), temp);
	if (temp.IsValidIndex(0))
		labirinto = Cast<Alabirinto>(temp[0]);


	else {
		UE_LOG(LogTemp, Warning, TEXT("ACyanGhost: ERROR: Missing Alabirinto"));
		return;
	}

	TArray<AActor*> temp1;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APacman::StaticClass(), temp1);
	if (temp1.IsValidIndex(0))
		pacman = Cast<APacman>(temp1[0]);


	else {
		UE_LOG(LogTemp, Warning, TEXT("ACyanGhost: ERROR: Missing APacman"));
		return;
	}

	TargetAngolo();
}


// Called every frame
void ACyanGhost::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (pacman->getNPill() <= 0 || pacman->getLives() < 1)
	{
		
		Cast<AActor>(this)->SetActorLocation(Spawn, false, nullptr, ETeleportType::TeleportPhysics);

		currentVelocity.X = 0;
		currentVelocity.Y = 0;

	}
	else {
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

				GetWorldTimerManager().SetTimer(TimerCyanStyle, [&]() { huntStyle = rand() % 3; }, 10.0f, false);
				if (huntStyle == 0)
				{
					TickInterface(DeltaTime, pacman->getPosX(), pacman->getPosY(), labirinto, pacman);
				}
				else if (huntStyle == 1)
				{
					int targetX = pacman->getPosX() + pacman->getDirezioneX() * 4;
					int targetY = pacman->getPosY() + pacman->getDirezioneY() * 4;
					TickInterface(DeltaTime, targetX, targetY, labirinto, pacman);
				}
				else
				{
					float distanza = FMath::Sqrt((pacman->getPosX() - getPosX()) * (pacman->getPosX() - getPosX()) + (pacman->getPosY() - getPosY()) * (pacman->getPosY() - getPosY()));
					if (distanza >= 8)
						TickInterface(DeltaTime, pacman->getPosX(), pacman->getPosY(), labirinto, pacman);
					else
						TickInterface(DeltaTime, TargetAngoloX, TargetAngoloY, labirinto, pacman);
				}


			}
		}

	}

}

