#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CSlicableMesh.generated.h"

class UProceduralMeshComponent;

UCLASS()
class MISC_API ACSlicableMesh : public AActor
{
	GENERATED_BODY()
	
public:	
	ACSlicableMesh();

	FORCEINLINE UMaterial* GetCapMaterial() { return CapMaterial; }

protected:
	virtual void OnConstruction(const FTransform& Transform) override;

protected:
	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	USceneComponent* RootComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UProceduralMeshComponent* ProcMeshComp;

	UPROPERTY(EditAnywhere, Category = "Slice")
	UMaterial* CapMaterial;
};
