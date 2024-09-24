#include "CMiku.h"
#include "Engine.h"
#include "Materials/MaterialInstanceConstant.h"

ACMiku::ACMiku()
{
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Game/AMiku/Mesh/Appearance_Miku"));
	if (MeshAsset.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);
	}

	GetMesh()->SetRelativeLocation(FVector(0,0,-88));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
}

void ACMiku::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	for (int32 i = 0; i < (int32)EMaterialElemntType::Max; i++)
	{
		if (Materials[i])
		{
		GetMesh()->SetMaterial(i, Materials[i]);
		}
	}

}


void ACMiku::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

