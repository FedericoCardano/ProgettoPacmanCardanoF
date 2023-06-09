// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"//forse non serve
#include "Kismet/GameplayStatics.h"
#include "labirinto.h"
#include "Pacman.h"
#include "UObject/Interface.h"
#include "GhostInterface.generated.h"






// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UGhostInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROGETTOCARDANO_API IGhostInterface
{
	GENERATED_BODY()

	const float BaseVelocity = 625.0f;
	float CoefficenteVel = 0.75f;
	float StandardVelocity = BaseVelocity * CoefficenteVel; //da migliorare
	
	int nextSpace;
	int currentSpace;
	int direzioneX;
	int direzioneY;
	int prevDirezioneX;
	int prevDirezioneY;
	int posX;
	int posY;

	

	
	void Move(int TargetX, int TargetY, bool hunter, Alabirinto* labirinto,bool stile);
public:
	// Sets default values for this pawn's properties
	//UPROPERTY(VisibleAnywhere, Category = "Moviment")
	FVector2D currentVelocity;
	
	
	FTimerHandle TimerAngolo;
	FTimerHandle TimerPacman;
	

	void TickInterface(float DeltaTime,int TargetX, int TargetY, Alabirinto* labirinto, APacman* pacman);
	void TargetPacman();
	void TargetAngolo();
	int getPosY()
	{
		return posY;
	}
	int getPosX()
	{
		return posX;
	}
	bool eaten = false;
	bool tempS = false;
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
};
