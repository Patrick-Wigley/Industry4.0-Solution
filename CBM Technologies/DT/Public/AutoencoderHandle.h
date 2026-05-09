// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AutoencoderHandle.generated.h"

UCLASS()
class SCARYDAIRY3D_API AAutoencoderHandle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAutoencoderHandle();


	UFUNCTION(BlueprintCallable, Category = "Actions")
	void RunHealthEstimation();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
private:
	int32 ReturnCode;
	FString OutStdOut;
	FString OutStdErr;


	FTimerHandle HealthEstimationTimer;
    float Delay = 30; //60 * 10;


	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
