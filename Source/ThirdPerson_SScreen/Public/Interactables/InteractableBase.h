// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/WidgetComponent.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "InteractableBase.generated.h"

UCLASS()
class THIRDPERSON_SSCREEN_API AInteractableBase : public AActor
{
	GENERATED_BODY()
	friend class UInteractableManager;
	
public:	
	// Sets default values for this actor's properties
	AInteractableBase();
	UPROPERTY(EditAnywhere)
	USceneComponent* _sceneComponent;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* _mesh;
	UPROPERTY(EditAnywhere)
	UWidgetComponent* _widget3D;
	UPROPERTY(EditAnywhere)
	UBoxComponent* _interactArea;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void Interact(int playerId);
	virtual void Desinteract(int playerId);


	void EnableUI();
	void DisableUI();

private:
	int playersInteractingCount = 0;
	class ALevelManager* _levelManager;

	UFUNCTION()
	void OnTriggerOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnTriggerOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
