// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

void ATower::BeginPlay()
{
    Super::BeginPlay();

    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

    GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);
}

void ATower::Tick(float Deltatime)
{
    Super::Tick(Deltatime);

    if(Tank){
        // 탱크까지의 거리 구하기
        float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
        // 탱크가 사정거리에 있는지 확인
        if(Distance <= FireRange){
            // 사정거리에 있으면 포탑을 탱크를 향해 회전
            RotateTurret(Tank->GetActorLocation());
        }
    }

}

void ATower::CheckFireCondition()
{
    float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
    if(Distance <= FireRange){
        Super::Fire();
    }
}