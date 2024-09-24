#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CMiku.generated.h"

class UMaterialInstanceConstant;

UENUM(BlueprintType)
enum class EMaterialElemntType : uint8
{
	Skin,Hair,HariShadow,HariBackSpace,ClothBlack,
	ClothSpecular,Cloth,Cloth2,Cloth3,ClothNoEdge,
	ClothNoEdge2,Face, SkinNoEdge, Eye, SkinNoEdge2,
	Max
};

UCLASS()
class MISC_API ACMiku : public ACharacter
{
	GENERATED_BODY()

public:
	ACMiku();


public:	
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void OnConstruction(const FTransform& Transform);

protected:
	UPROPERTY(EditAnywhere, Category = "Materials")
	UMaterialInstanceConstant* Materials[(int32)EMaterialElemntType::Max];


};
