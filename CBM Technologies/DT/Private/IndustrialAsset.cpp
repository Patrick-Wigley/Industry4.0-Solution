// Fill out your copyright notice in the Description page of Project Settings.


#include "IndustrialAsset.h"
#include "Serialization/JsonSerializer.h"
#include "Dom/JsonObject.h"


// Sets default values
AIndustrialAsset::AIndustrialAsset()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
	//Mesh->AttachToComponent(Root);
	
	AnnotationWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("ActorWidgetAnnotation"));
	AnnotationWidget->SetupAttachment(RootComponent);
	AnnotationWidget->SetWidgetSpace(EWidgetSpace::Screen);
	static ConstructorHelpers::FClassFinder<UUserWidget> WidgetAsset(TEXT("/Game/Mine/MachineAsset/Annotations/W_MachineAssetAnnotation")); 
	if (WidgetAsset.Succeeded())
	{
		AnnotationWidget->SetWidgetClass(WidgetAsset.Class);
	}
	
	AnnotationWidget->SetRelativeLocation(FVector(0.f, 0.f, 75.f)); // Position above the actor
	AnnotationWidget->SetDrawSize(FVector2D(100.f, 100.f)); // Size on screen/in world
}



// Called when the game starts or when spawned
void AIndustrialAsset::BeginPlay()
{
	Super::BeginPlay();
	if (Mesh != nullptr)
	{
		UMaterialInterface* Material = Mesh->GetMaterial(0);

		if (Material != nullptr)
		{
			DynamicMaterial = UMaterialInstanceDynamic::Create(Material, Mesh);

			if (DynamicMaterial != nullptr)
			{
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Set Dynamic Material!"));	
				Mesh->SetMaterial(0, DynamicMaterial);
			}
		}
	}

	GetWorldTimerManager().SetTimer(UpdateStatusTimer, this, &AIndustrialAsset::UpdateStatus, DelayTimer, true);
	UpdateStatus();
}


// Remove comment from below method: I am doing this here to avoid asynchronous issues in AMachineAsset::HandleRealTimeVisualisations()

/*
 * Read HI, Timestamp & Status information from JSON file outputted by Machine Learning Component
 * Then dynamically update this machines-actor instances state in world-space 
 */
void AIndustrialAsset::UpdateStatus()
{
	// Pull Outputted JSON file contents into fileStr
	const FString ProjectDir = FPaths::ConvertRelativePathToFull(FPaths::ProjectDir());
	const FString JSONPath = ProjectDir + "/Autoencoder_python/asset_status.json";
	FString FileStr = "";
	FFileHelper::LoadFileToString(FileStr, *JSONPath);
	
	// Deserialize JSON object outputted by Machine Learning Component
	TSharedPtr<FJsonObject> JsonObj;
	FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(FileStr), JsonObj);
	// Read variables	
	FString HealthIndex = JsonObj->GetStringField("HI");
	FString LastUpdate = JsonObj->GetStringField("time");
	FString ModelStatus = JsonObj->GetStringField("ModelStatus");
	
	// Set Annotation (asset label in game world-space) with informative variables from JSON  
	UE_LOG(LogTemp, Error, TEXT("AnnotationWidget pointer: %p"), AnnotationWidget);
	if (UUserWidget* UserWidget = AnnotationWidget->GetUserWidgetObject())
	{
		TypedWidget = Cast<UMachineAssetAnnotationWidget>(UserWidget);
		if (TypedWidget)
			TypedWidget->SetAnnotation(
				FString("HI: ") + FString(HealthIndex) +
				FString("; Last Updated: ") + FString(LastUpdate) +
				FString("; Status: ") + FString(ModelStatus));
		else
			UE_LOG(LogTemp, Error, TEXT("Cast to UMachineAssetAnnotationWidget FAILED!"));
	}
	// Dynamically Update Material - Change conditional colouring of machine based on Health Index score  
	const float HI_Factor = FCString::Atof(*HealthIndex);
	const FVector HI_Colour = FVector(1, HI_Factor, HI_Factor);
	DynamicMaterial->SetVectorParameterValue(VecParamName, HI_Colour);
}

// Called every frame
void AIndustrialAsset::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	
}

