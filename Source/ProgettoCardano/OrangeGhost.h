// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GhostInterface.h"
#include "GameFramework/Actor.h"
#include "OrangeGhost.generated.h"

UCLASS()
class PROGETTOCARDANO_API AOrangeGhost : public AActor, public IGhostInterface
{
	GENERATED_BODY()

		UPROPERTY()
		Alabirinto* labirinto;
	UPROPERTY()
		APacman* pacman;

	int TargetAngoloX = 29;
	int TargetAngoloY = 26;
	FVector Spawn;
	int pacmanLifes = 3;
public:
	// Sets default values for this actor's properties
	AOrangeGhost();
	void setTarget();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame

	virtual void Tick(float DeltaTime) override;

};
