// Fill out your copyright notice in the Description page of Project Settings.

#define  StartX 23
#define  StartY 13
#include "Pacman.h"




// Sets default values
APacman::APacman()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void APacman:: die() {
	Nlives--;

	FVector NewLocation = FVector(23, 13, 0) * 100;
	SetActorLocation(NewLocation, false, nullptr, ETeleportType::TeleportPhysics);

	direzioneX = 0;
	direzioneY = 1;

	currentVelocity.X = direzioneX * StandardVelocity;
	currentVelocity.Y = direzioneY * StandardVelocity;
}

void APacman::MoveOnX(float val_x)
{
	nextSpace  = labirinto->getMap(posX+ val_x, posY);
	currentSpace = labirinto->getMap(posX, posY);
	bool walkable = nextSpace != 'W' && nextSpace != 'h' && nextSpace != 'H';

	if (currentSpace == 't')
		StandardVelocity = 350;
	else
		StandardVelocity = 500;
	if (walkable && val_x!=0)
	{
		currentVelocity.X = StandardVelocity * val_x; // velocità standard * direzione
		currentVelocity.Y = 0;

		FVector NewLocation = FVector(GetActorLocation().X, posY * 100, 0);
		SetActorLocation(NewLocation, false, nullptr, ETeleportType::TeleportPhysics);
	}

}

void APacman::MoveOnY(float val_y)
{
	
	nextSpace = labirinto->getMap(posX , posY + val_y);
	currentSpace = labirinto->getMap(posX, posY);
	bool walkable = nextSpace != 'W' && nextSpace != 'h' && nextSpace != 'H';

	if (currentSpace == 't')
		StandardVelocity = 350;
	else
		StandardVelocity = 500;
	if (walkable && val_y != 0)
	{
		currentVelocity.X = 0;
		currentVelocity.Y = StandardVelocity * val_y; // velocità standard * direzione

		FVector NewLocation = FVector(posX * 100, GetActorLocation().Y, 0);
		SetActorLocation(NewLocation, false, nullptr, ETeleportType::TeleportPhysics);
	}


	
}

// Called when the game starts or when spawned
void APacman::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*>temp;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), Alabirinto::StaticClass(), temp);
	//Nlives = 4;
	Nlives = 7;
	Npill = 240;
	if (temp.IsValidIndex(0))
		labirinto = Cast<Alabirinto>(temp[0]);
	
		
	else {
		UE_LOG(LogTemp, Warning, TEXT("PPacman: ERROR: Missing Alabirinto"));
		return;
	}

	currentSpace = labirinto->getMap(StartX, StartY);
	
	 direzioneX=0;
	 direzioneY=1;

	 currentVelocity.X = direzioneX * StandardVelocity;
	 currentVelocity.Y = direzioneY * StandardVelocity;
}

// Called every frame
void APacman::Tick(float DeltaTime)
{
	//abbiamo un problema con la currentVelocity

	Super::Tick(DeltaTime);
	if (Npill <= 0)
	{
		//You Win
		if (!stop) {
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString::Printf(TEXT("You Win Lives= %d Npil %d"), Nlives, Npill));
			FVector NewLocation = FVector(23, 13, 0) * 100;
			SetActorLocation(NewLocation, false, nullptr, ETeleportType::TeleportPhysics);
			labirinto->win();
			stop = true;
		}

		currentVelocity.X = 0;
		currentVelocity.Y = 0;
	}
	else if (Nlives < 1)
	{
		//GAME OVER
		if (!stop) {
			GEngine->AddOnScreenDebugMessage(-1,15.0f,FColor::Blue,FString::Printf(TEXT("GAME OVER Lives= %d Npil %d"),Nlives,Npill));
			labirinto->lose();
			FVector NewLocation = FVector(23, 13, 0) * 100;
			SetActorLocation(NewLocation, false, nullptr, ETeleportType::TeleportPhysics);
			stop = true;
		}

		currentVelocity.X = 0;
		currentVelocity.Y = 0;
	}
	else
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString::Printf(TEXT("Lives= %d Npil %d"), Nlives, Npill));

	if (currentVelocity.X / StandardVelocity > 0)
		direzioneX = 1;
	else if (currentVelocity.X / StandardVelocity < 0)
		direzioneX = -1;
	else
		direzioneX = 0;

	if (currentVelocity.Y / StandardVelocity > 0)
		direzioneY = 1;
	else if (currentVelocity.Y / StandardVelocity < 0)
		direzioneY = -1;
	else
		direzioneY = 0;

	 posX = FMath::DivideAndRoundNearest((int)GetActorLocation().X, 100);
	 posY = FMath::DivideAndRoundNearest((int)GetActorLocation().Y, 100);
	int NextPosX = FMath::DivideAndRoundNearest((int)GetActorLocation().X+ direzioneX * 51, 100);//potrebbe servire 51
	int NextPosY = FMath::DivideAndRoundNearest((int)GetActorLocation().Y+ direzioneY * 51, 100);//potrebbe servire 51

	nextSpace = labirinto->getMap(NextPosX,NextPosY);
	currentSpace = labirinto->getMap(posX, posY);

	//bool walkable = nextSpace != 'W' && nextSpace != 'h' && nextSpace != 'H';
	//bool inMap = NextPosX>= 0 && NextPosX < 30 && NextPosY>=0 && NextPosY < 28;
	
	
	if (currentSpace == 'o')
	{
		labirinto->setMap(posX, posY, ' ');
		labirinto->punteggio+=10;
		Npill--;
	}
	if (currentSpace == 'Q')
	{
		labirinto->setMap(posX, posY, ' ');
		labirinto->punteggio += 50;
		P_hunter = true;
		CoefficenteVel = 0.9f;
		//effetto super pill
		FTimerHandle Timer;
		
		GetWorldTimerManager().SetTimer(Timer, [&]() { P_hunter = false; CoefficenteVel =0.8f; }, 5.0f, false);
	}
	else if (currentSpace == 't')
	{
		if (nextSpace == 'T')
		{
			if (posY == 26)
			{
				posY = 1;
				FVector NewLocation =   FVector(1400,100, 0);
				SetActorLocation(NewLocation, false, nullptr, ETeleportType::TeleportPhysics);
			}
			else
			{
				posY = 26;
				FVector NewLocation = FVector(1400, 2600, 0);
				SetActorLocation(NewLocation, false, nullptr, ETeleportType::TeleportPhysics);
			}

		}
	}
	else if(P_hunter)
		CoefficenteVel = 0.9f;
	else
		CoefficenteVel = 0.8f;
	
	StandardVelocity = BaseVelocity * CoefficenteVel;


	bool walkable = nextSpace != 'W' && nextSpace != 'h' && nextSpace != 'H';

	currentVelocity.X = direzioneX * StandardVelocity;
	currentVelocity.Y = direzioneY * StandardVelocity;

	if (!walkable)
	{
		currentVelocity.X = 0;
		currentVelocity.Y = 0;
	}



	//GEngine->AddOnScreenDebugMessage(-1,15.0f,FColor::Blue,FString::Printf(TEXT("punteggio %d, posX %d, posY %d,NextPosX %d ,NextPosY %d,StandardVelocity % f, nextSpace % c"), /*labirinto->punteggio, posX, posY, NextPosX, NextPosY,*/ StandardVelocity, nextSpace));
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString::Printf(TEXT("posX %d, posY %d, direzioneX %d,direzioneY %d ,StandardVelocity % f, nextSpace % c"), posX, posY, direzioneX, direzioneY, StandardVelocity, nextSpace));
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString::Printf(TEXT("StandardVelocity %f, nextSpace % c"), StandardVelocity, nextSpace));



	FVector NewLocation = GetActorLocation() + (FVector(currentVelocity.X, currentVelocity.Y, 0) * DeltaTime);
	SetActorLocation(NewLocation, false, nullptr, ETeleportType::TeleportPhysics);
}



// Called to bind functionality to input
void APacman::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	
	InputComponent->BindAxis("x", this, &APacman::MoveOnX);
	InputComponent->BindAxis("y", this, &APacman::MoveOnY);
}

UFUNCTION(BlueprintCallable)
int32 APacman::getPunteggio()
{
	return labirinto -> punteggio;
}

