// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"
#include "labirinto.h"
#include "Pacman.generated.h"


UCLASS()
class PROGETTOCARDANO_API APacman : public APawn
{
	GENERATED_BODY()

		UPROPERTY() 
	Alabirinto* labirinto;
	const float BaseVelocity = 625.0f ;
	float CoefficenteVel = 0.8f ;
	float StandardVelocity = BaseVelocity* CoefficenteVel; //da migliorare
	int nextSpace;
	int currentSpace;
	int direzioneX;
	int direzioneY;
	int posX;
	int posY;
	bool P_hunter=false;
	bool stop = false;
	int Nlives=3;
	int Npill=240 ;

public:
	// Sets default values for this pawn's properties
	APacman();
	void MoveOnX(float val_x);
	void MoveOnY(float val_y);
	void die();
	int getScore();
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<APacman> Pacman;
	UPROPERTY(VisibleAnywhere,Category="Moviment")
		FVector2D currentVelocity;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	int32 getPunteggio();
	int getPosX()
	{
		return posX;
	}
	int getPosY()
	{
		return posY;
	}
	bool GhostHunterMode()
	{
		return !P_hunter;
	}
	int getDirezioneX() { return direzioneX; }
	int getDirezioneY() { return direzioneY; }
	int getNPill() { return Npill; }

	
	UFUNCTION(BlueprintCallable)
	int getLives()
	{
		const int L = Nlives;
		return  L;
	}

	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};

