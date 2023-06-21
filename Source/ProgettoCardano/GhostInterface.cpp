 // Fill out your copyright notice in the Description page of Project Settings.


#include "GhostInterface.h"


void IGhostInterface::Move(int TargetX, int TargetY, bool G_hunter, Alabirinto* labirinto,bool stile)
{
	//distanza(posX,PosY,TargetX, TargetY)
	int DeltaX = TargetX - posX;
	int DeltaY = TargetY - posY;
	float Distanza[4];
	float minDistanza=9999;
	float maxDistanza = 0;
	int minDistanzaIndex = 0;
	int maxDistanzaIndex = 0;
	char space[4];
	bool walkable[4];
		UStaticMeshComponent* MainBody = Cast<UStaticMeshComponent>(Cast<AActor>(this)->GetDefaultSubobjectByName("MainCube"));
		UStaticMeshComponent* BlueBody = Cast<UStaticMeshComponent>(Cast<AActor>(this)->GetDefaultSubobjectByName("BlueCube"));

	if (stile) {

		if (eaten)
		{
			BlueBody->SetVisibility(false);
			MainBody->SetVisibility(false);
		}
		else
		{
			if (G_hunter || tempS)
			{
				BlueBody->SetVisibility(false);
				MainBody->SetVisibility(true);
			}
			else
			{
				BlueBody->SetVisibility(true);
				MainBody->SetVisibility(false);
			}

		}
	}

	// accedo alla mappa per ottenere le caselle vicine
	space[0] = labirinto->getMap(posX - 1, posY);
	space[1] = labirinto->getMap(posX + 1, posY);
	space[2] = labirinto->getMap(posX, posY - 1);
	space[3] = labirinto->getMap(posX, posY + 1);

	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString::Printf(TEXT("char X-1 = %c, char X+1 = %c ,char Y-1 = %c, char Y+1 = %c"), space[0], space[1], space[2], space[3]));

	// controllo se sono caselle camminabili
	for (int i = 0; i < 4; i++)
	{
		 walkable[i] = space[i] != 'W' && space[i] != 'h' && space[i] != 'H';
	}
	
	// calocolo la distanza dal target escludendo la direzione attuale
	if(walkable[0] && !(prevDirezioneX > 0))		//	sinistra
		Distanza[0] = FMath::Sqrt((DeltaX + 1) * (DeltaX + 1) + DeltaY * DeltaY);
	else {
		if (prevDirezioneX > 0)
			Distanza[0] = 9998;
		else
			Distanza[0] = 9999;
	}

	if (walkable[1] && !(prevDirezioneX < 0))		//	destra
		Distanza[1] = FMath::Sqrt((DeltaX - 1) * (DeltaX - 1) + DeltaY * DeltaY);
	else {
		if (prevDirezioneX < 0)
			Distanza[1] = 9998;
		else
			Distanza[1] = 9999;
	}

	if (walkable[2] && !(prevDirezioneY > 0))		//	giù
		Distanza[2] = FMath::Sqrt(DeltaX * DeltaX + (DeltaY + 1) * (DeltaY + 1));
	else
	{
		if (prevDirezioneY > 0)
			Distanza[2] = 9998;
		else
			Distanza[2] = 9999;
	}
	
	if (walkable[3] && !(prevDirezioneY <  0))		//	su
		Distanza[3] = FMath::Sqrt(DeltaX * DeltaX + (DeltaY - 1) * (DeltaY - 1));
	else
	{
		if (prevDirezioneY < 0)
			Distanza[3] = 9999;
		else
			Distanza[3] = 9998;
	}

	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString::Printf(TEXT("Distanza[0] = %f, Distanza[1] = %f ,Distanza[2] = %f, Distanza[3] = %f"), Distanza[0], Distanza[1], Distanza[2], Distanza[3]));


	// calcolo la distanza minima 
	for (int i = 0; i < 4; i++) 
	{
		if (minDistanza > Distanza[i])
		{
			minDistanza = Distanza[i];
			minDistanzaIndex = i;
		}
	}
	
	// setto la nuova direzione a seconda dello stato hunter
	if (G_hunter||eaten)	// si deve avvicinare al target
	{
		
		if (minDistanzaIndex > 1)
		{
			direzioneX = 0;
			if (minDistanzaIndex == 2)
				direzioneY = -1;
			else
				direzioneY = 1;
		}
		else
		{
			direzioneY = 0;
			if (minDistanzaIndex == 0)
				direzioneX = -1;
			else
				direzioneX = 1;
		}
	}
	else // deve scappare
	{
		int TargetX = rand() % 31+1;
		int TargetY = rand() % 27 + 1;
		Move(TargetX, TargetY, true, labirinto,false);
	}

	if (prevDirezioneX != direzioneX || prevDirezioneY != direzioneY)//correzione posizione al cambio di direzione
	{
		
			FVector NewLocation = FVector(posX * 100, posY * 100, 0);
			Cast<AActor>(this)->SetActorLocation(NewLocation, false, nullptr, ETeleportType::TeleportPhysics);

			prevDirezioneX = direzioneX;
			prevDirezioneY = direzioneY;
			
		

	}

	

	/*
	space[0] = labirinto->getMap(posX - 1, posY);
	space[1] = labirinto->getMap(posX + 1, posY);
	space[2] = labirinto->getMap(posX, posY - 1);
	space[3] = labirinto->getMap(posX, posY + 1);
	*/
}


void IGhostInterface::TickInterface(float DeltaTime, int TargetX, int TargetY, Alabirinto* labirinto, APacman* pacman)
{
	//abbiamo un problema con la currentVelocity
	int prevPosX = posX;
	int prevPosY = posY;
	posX = FMath::DivideAndRoundNearest((int)Cast<AActor>(this)->GetActorLocation().X, 100);
	posY = FMath::DivideAndRoundNearest((int)Cast<AActor>(this)->GetActorLocation().Y, 100);
	int NextPosX = FMath::DivideAndRoundNearest((int)Cast<AActor>(this)->GetActorLocation().X + direzioneX * 51, 100);//potrebbe servire 51
	int NextPosY = FMath::DivideAndRoundNearest((int)Cast<AActor>(this)->GetActorLocation().Y + direzioneY * 51, 100);//potrebbe servire 51
	
	
	

	nextSpace = labirinto->getMap(NextPosX, NextPosY);
	currentSpace = labirinto->getMap(posX, posY);

	//bool walkable = nextSpace != 'W' && nextSpace != 'h' && nextSpace != 'H';
	//bool inMap = NextPosX>= 0 && NextPosX < 30 && NextPosY>=0 && NextPosY < 28;
	
	if (eaten)
		CoefficenteVel = 1.0f;
	else if (currentSpace == 't')
	{
		if (nextSpace == 'T')
		{
			if (posY == 26)
			{
				posY = 1;
				FVector NewLocation = FVector(1400, 100, 0);
				Cast<AActor>(this)->SetActorLocation(NewLocation, false, nullptr, ETeleportType::TeleportPhysics);
			}
			else
			{
				posY = 26;
				FVector NewLocation = FVector(1400, 2600, 0);
				Cast<AActor>(this)->SetActorLocation(NewLocation, false, nullptr, ETeleportType::TeleportPhysics);
			}

		}
		CoefficenteVel = 0.4f;
	}
	else if (!pacman->GhostHunterMode())
	{ 
		CoefficenteVel = 0.5f;
	}
	else
		CoefficenteVel = 0.75f;

	if(prevPosX!= posX || prevPosY != posY)
		Move(TargetX, TargetY, pacman->GhostHunterMode(), labirinto,true);

	StandardVelocity = BaseVelocity * CoefficenteVel;

	currentVelocity.X = direzioneX * StandardVelocity;
	currentVelocity.Y = direzioneY * StandardVelocity;


	//GEngine->AddOnScreenDebugMessage(-1,15.0f,FColor::Blue,FString::Printf(TEXT("punteggio %d, posX %d, posY %d,NextPosX %d ,NextPosY %d,StandardVelocity % f, nextSpace % c"), /*labirinto->punteggio, posX, posY, NextPosX, NextPosY,*/ StandardVelocity, nextSpace));
	//GEngine->AddOnScreenDebugMessage(-1,15.0f,FColor::Blue,FString::Printf(TEXT("Ghost StandardVelocity %f,Ghost nextSpace % c"),  StandardVelocity, nextSpace));


	FVector NewLocation = Cast<AActor>(this)->GetActorLocation() + (FVector(currentVelocity.X, currentVelocity.Y, 0) * DeltaTime);
	Cast<AActor>(this)->SetActorLocation(NewLocation, false, nullptr, ETeleportType::TeleportPhysics);
}


void IGhostInterface::TargetPacman()
{
	Cast<AActor>(this)->GetWorldTimerManager().SetTimer(TimerPacman, [&]() { TargetAngolo(); }, 20.0f, false);
}

void IGhostInterface::TargetAngolo()
{
	Cast<AActor>(this)->GetWorldTimerManager().SetTimer(TimerAngolo, [&]() { TargetPacman(); }, 7.0f, false);
}

// Add default functionality here for any IGhostInterface functions that are not pure virtual.
