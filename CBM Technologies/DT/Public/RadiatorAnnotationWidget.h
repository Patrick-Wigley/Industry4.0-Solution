// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "MachineAssetAnnotationWidget.generated.h"

/**
 * 
 */
UCLASS()
class SCARYDAIRY3D_API UMachineAssetAnnotationWidget : public UUserWidget
{
	GENERATED_BODY()


public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* AnnotationText;

	UFUNCTION(BlueprintCallable)
	void SetAnnotation(const FString& NewText)
	{
		if (AnnotationText)
		{
			AnnotationText->SetText(FText::FromString(NewText));
			
		}
	}
};
