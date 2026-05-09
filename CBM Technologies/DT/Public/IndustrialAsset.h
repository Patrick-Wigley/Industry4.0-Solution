// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "GameFramework/Actor.h"
#include "Components/TextRenderComponent.h"
#include "Components/WidgetComponent.h"
#include "MachineAssetnnotationWidget.h"

// HTTP client stuff 
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "HttpModule.h"

#include "IndustrialAsset.generated.h"

UCLASS()
class SCARYDAIRY3D_API AIndustrialAsset : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIndustrialAsset();

	UPROPERTY()
	USceneComponent* Root;
	
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	UMaterialInstanceDynamic* DynamicMaterial;

	UPROPERTY(EditAnywhere)
	FName VecParamName = FName("MachineAssetColour");
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UTextRenderComponent* AnnotationText;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UWidgetComponent* AnnotationWidget;

	UPROPERTY()
	UMachineAssetnnotationWidget* TypedWidget;
	
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* NameTextBlock;

private:
	FTimerHandle UpdateStatusTimer;
	const float DelayTimer = 5; //60.0f * 1;	// 1 minute
	void UpdateStatus();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
