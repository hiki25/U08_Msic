#include "CSlicableMesh.h"
#include "ProceduralMeshComponent.h"
#include "Engine.h"
#include "KismetProceduralMeshLibrary.h"


ACSlicableMesh::ACSlicableMesh()
{
	RootComp = CreateDefaultSubobject<USceneComponent>("Root");
	RootComponent = RootComp;

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComp");
	StaticMeshComp->SetupAttachment(RootComp);

	ProcMeshComp = CreateDefaultSubobject<UProceduralMeshComponent>("ProcMeshComp");
	ProcMeshComp->SetupAttachment(RootComp);

	ConstructorHelpers::FObjectFinder<UStaticMesh> StateMeshAsset(TEXT("/Game/Geometry/Meshes/1M_Cube"));
	if (StateMeshAsset.Succeeded())
	{
		StaticMeshComp->SetStaticMesh(StateMeshAsset.Object);
	}

	StaticMeshComp->SetVisibility(false);
	StaticMeshComp->SetCollisionProfileName("NoCollision");

	ProcMeshComp->SetSimulatePhysics(true);
	ProcMeshComp->bUseComplexAsSimpleCollision = false;

	bRunConstructionScriptOnDrag = false;
}

void ACSlicableMesh::OnConstruction(FTransform& Transform)
{
	Super::OnConstruction(Transform);

	UKismetProceduralMeshLibrary::CopyProceduralMeshFromStaticMeshComponent(StaticMeshComp, 0, );
}
