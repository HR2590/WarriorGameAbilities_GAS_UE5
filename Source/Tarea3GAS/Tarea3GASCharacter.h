// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CoreAttributeSet.h"
#include "GASDataComponent.h"

#include "GameFramework/Character.h"
#include "Tarea3GASCharacter.generated.h"

class UBoxComponent;
class UUTHUB_ASC;

UCLASS(Blueprintable)
class ATarea3GASCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ATarea3GASCharacter();
	UFUNCTION(BlueprintCallable, Category="Attribute Delegates",meta=(AllowPrivateAccess=true))
	void OnHealthChanged(float OldHealth, float NewHealth);
	UFUNCTION(BlueprintCallable, Category="Attribute Delegates",meta=(AllowPrivateAccess=true))
	void OnSpeedChanged(float OldSpeed, float NewSpeed);

	virtual void BeginPlay() override;
	
	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FGameplayTagContainer GameplayStates; 
private:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=CoreAttributes,meta=(AllowPrivateAccess=true))
	UCoreAttributeSet* CoreAttributeSet;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category=Gameplay,meta=(AllowPrivateAccess=true))
	UGASDataComponent* GASDataComponent;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category=Gameplay,meta=(AllowPrivateAccess=true))
	UUTHUB_ASC* ASC;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Gameplay,meta=(AllowPrivateAccess=true))
	TSubclassOf<UGameplayEffect> SampleEffect;
	
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	

};

