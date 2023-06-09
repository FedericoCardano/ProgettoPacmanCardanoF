// Fill out your copyright notice in the Description page of Project Settings.


#include "Home.h"

// Sets default values
AHome::AHome()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHome::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHome::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

