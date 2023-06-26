// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Kismet/GameplayStatics.h>
#include "labirinto.h"
#include "iClass.generated.h"

UCLASS()
class PROGETTOCARDANO_API AiClass : public AActor
{
	GENERATED_BODY()
		Alabirinto* labirinto;
public:	
	// Sets default values for this actor's properties
	AiClass();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
