// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Wall.h"
#include "Pill.h"
#include "SuperPill.h"


#include "labirinto.generated.h"

UCLASS()
class PROGETTOCARDANO_API Alabirinto : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	Alabirinto();
	
	void win();
	void lose();
	bool loser = false;
	bool winner = false;
	int punteggio=0;

	int getMap(int x, int y)
	{
		x = FMath::Clamp(x, 0, 31);
		y = FMath::Clamp(y, 0, 27);
		return map[x][y];
	}
	void setMap(int x, int y,int value)
	{
		x = FMath::Clamp(x, 0, 31);
		y = FMath::Clamp(y, 0, 27);
		map[x][y] = value;
		
	}

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AWall> Wall;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<APill> Pill;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<ASuperPill> SuperPill;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AActor> Space;




private:

	int map[33][28] = {
	{'W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W'},	//	0
	{'W','o','o','o','o','o','o','o','o','o','o','o','o','W','W','o','o','o','o','o','o','o','o','o','o','o','o','W'},	//	1 • 
	{'W','o','W','W','W','W','o','W','W','W','W','W','o','W','W','o','W','W','W','W','W','o','W','W','W','W','o','W'},	//	2 ○
	{'W','Q','W','W','W','W','o','W','W','W','W','W','o','W','W','o','W','W','W','W','W','o','W','W','W','W','Q','W'},	//	3
	{'W','o','W','W','W','W','o','W','W','W','W','W','o','W','W','o','W','W','W','W','W','o','W','W','W','W','o','W'},	//	4
	{'W','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','W'},	//	5
	{'W','o','W','W','W','W','o','W','W','o','W','W','W','W','W','W','W','W','o','W','W','o','W','W','W','W','o','W'},	//	6
	{'W','o','W','W','W','W','o','W','W','o','W','W','W','W','W','W','W','W','o','W','W','o','W','W','W','W','o','W'},	//	7
	{'W','o','o','o','o','o','o','W','W','o','o','o','o','W','W','o','o','o','o','W','W','o','o','o','o','o','o','W'},	//	8
	{'W','W','W','W','W','W','o','W','W','W','W','W',' ','W','W',' ','W','W','W','W','W','o','W','W','W','W','W','W'},	//	9
	{'W','W','W','W','W','W','o','W','W','W','W','W',' ','W','W',' ','W','W','W','W','W','o','W','W','W','W','W','W'},	//	10
	{'W','W','W','W','W','W','o','W','W',' ',' ',' ',' ',' ','g',' ',' ',' ',' ','W','W','o','W','W','W','W','W','W'},	//	11
	{'W','W','W','W','W','W','o','W','W',' ','W','W','W','h','h','W','W','W',' ','W','W','o','W','W','W','W','W','W'},	//	12
	{'W','W','W','W','W','W','o','W','W',' ','W','H','H','H','H','H','H','W',' ','W','W','o','W','W','W','W','W','W'},	//	13
	{'T','t','t','t','t','t','o',' ',' ',' ','W','H','H','H','H','H','H','W',' ',' ',' ','o','t','t','t','t','t','T'},	//	14
	{'W','W','W','W','W','W','o','W','W',' ','W','g','H','H','H','g','g','W',' ','W','W','o','W','W','W','W','W','W'},	//	15
	{'W','W','W','W','W','W','o','W','W',' ','W','W','W','W','W','W','W','W',' ','W','W','o','W','W','W','W','W','W'},	//	16
	{'W','W','W','W','W','W','o','W','W',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','W','W','o','W','W','W','W','W','W'},	//	17
	{'W','W','W','W','W','W','o','W','W',' ','W','W','W','W','W','W','W','W',' ','W','W','o','W','W','W','W','W','W'},	//	18
	{'W','W','W','W','W','W','o','W','W',' ','W','W','W','W','W','W','W','W',' ','W','W','o','W','W','W','W','W','W'},	//	19
	{'W','o','o','o','o','o','o','o','o','o','o','o','o','W','W','o','o','o','o','o','o','o','o','o','o','o','o','W'},	//	20
	{'W','o','W','W','W','W','o','W','W','W','W','W','o','W','W','o','W','W','W','W','W','o','W','W','W','W','o','W'},	//	21
	{'W','o','W','W','W','W','o','W','W','W','W','W','o','W','W','o','W','W','W','W','W','o','W','W','W','W','o','W'},	//	22
	{'W','Q','o','o','W','W','o','o','o','o','o','o','o','S',' ','o','o','o','o','o','o','o','W','W','o','o','Q','W'},	//	23
	{'W','W','W','o','W','W','o','W','W','o','W','W','W','W','W','W','W','W','o','W','W','o','W','W','o','W','W','W'},	//	24
	{'W','W','W','o','W','W','o','W','W','o','W','W','W','W','W','W','W','W','o','W','W','o','W','W','o','W','W','W'},	//	25
	{'W','o','o','o','o','o','o','W','W','o','o','o','o','W','W','o','o','o','o','W','W','o','o','o','o','o','o','W'},	//	26
	{'W','o','W','W','W','W','W','W','W','W','W','W','o','W','W','o','W','W','W','W','W','W','W','W','W','W','o','W'},	//	27
	{'W','o','W','W','W','W','W','W','W','W','W','W','o','W','W','o','W','W','W','W','W','W','W','W','W','W','o','W'},	//	28
	{'W','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','W'},	//	29
	{'W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W'},	//	30
	{'W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W'},	//	31
	{'W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W'}	//	32
	};


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


};
