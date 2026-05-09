// Fill out your copyright notice in the Description page of Project Settings.


#include "AutoencoderHandle.h"

// Sets default values
AAutoencoderHandle::AAutoencoderHandle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Calls MyFunction every 2 seconds, looping
	
	
}

// Called when the game starts or when spawned
void AAutoencoderHandle::BeginPlay()
{
	Super::BeginPlay();

	// if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
	// 	EnhancedInputComponent->BindAction(MyAction, ETriggerEvent::Started, this, &AAutoencoderHandle::RunHealthEstimation);
	// }
	//
	//GetWorldTimerManager().SetTimer(HealthEstimationTimer, this, &AAutoencoderHandle::RunHealthEstimation, Delay, true);
	this->RunHealthEstimation();
}

void AAutoencoderHandle::RunHealthEstimation()
{
	
	if (GEngine)
	{
		// GEngine->ClearOnScreenDebugMessages();
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Yellow, *FString::Printf(TEXT("Begin Estimate Health")));
	}
	
	FString ProjectDir = FPaths::ConvertRelativePathToFull(FPaths::ProjectDir());
	const FString python_location_suffix = ProjectDir + "/Autoencoder_python";
	

	const FString python_exe = python_location_suffix + "/v/Scripts/python.exe";
	const FString python_script = python_location_suffix + "/HealthEstimator.py";
	const FString params = FString::Printf(TEXT("-i \"%s\""), *python_script);
	
	const FString working_dir = python_location_suffix;

	FProcHandle Proc = FPlatformProcess::CreateProc(
		*python_exe, 
		*params, 
		true,   // Launch detached?
		true,  // Hidden?
		false,  // Priority?
		nullptr, 
		0, 
		*working_dir,
		nullptr
	);

	
}

// Called every frame
void AAutoencoderHandle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

