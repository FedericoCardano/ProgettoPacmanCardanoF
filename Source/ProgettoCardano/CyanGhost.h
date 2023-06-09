// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GhostInterface.h"
#include "GameFramework/Actor.h"
#include "CyanGhost.generated.h"

UCLASS()
class PROGETTOCARDANO_API ACyanGhost : public AActor, public IGhostInterface
{
	GENERATED_BODY()

		UPROPERTY()
		Alabirinto* labirinto;
	UPROPERTY()
		APacman* pacman;
	int huntStyle = 0;
	int TargetAngoloX = 29;
	int TargetAngoloY = 1;
	int pacmanLifes = 3;
	FTimerHandle TimerCyanStyle;
	FVector Spawn;
public:
	// Sets default values for this actor's properties
	ACyanGhost();
	void setTarget();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame

	virtual void Tick(float DeltaTime) override;

};
