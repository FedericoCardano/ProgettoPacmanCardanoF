// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "labirinto.h"
#include "oLoseClass.generated.h"

UCLASS()
class PROGETTOCARDANO_API AoLoseClass : public AActor
{
	GENERATED_BODY()
	
		Alabirinto* labirinto;
public:	
	// Sets default values for this actor's properties
	AoLoseClass();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
