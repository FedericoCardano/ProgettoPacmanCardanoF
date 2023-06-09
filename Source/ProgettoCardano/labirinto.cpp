// Fill out your copyright notice in the Description page of Project Settings.


#include "labirinto.h"

// Sets default values
Alabirinto::Alabirinto()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	

}

// Called when the game starts or when spawned
void Alabirinto::BeginPlay()
{
	Super::BeginPlay();

	

	for (int i = 0; i < 32; i++) {
		for (int j = 0; j < 28; j++) {
			FVector pos = FVector(i, j, 0) * 100;
			switch (map[i][j]) {

			case 'W':
				GetWorld()->SpawnActor(Wall, &pos);
				break;

			case 'o':
				GetWorld()->SpawnActor(Pill, &pos);
				break;

			case 'Q':
				GetWorld()->SpawnActor(SuperPill, &pos);
				break;

			default:
				GetWorld()->SpawnActor(Space, &pos);
				break;
			}
			
		}
	}

}

// Called every frame
void Alabirinto::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

