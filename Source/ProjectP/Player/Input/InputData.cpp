// Fill out your copyright notice in the Description page of Project Settings.


#include "InputData.h"

UInputData::UInputData()
{
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> inputContext(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Inputs/IMC_Default.IMC_Default'"));

	if (inputContext.Succeeded())
		context = inputContext.Object;
	
	static ConstructorHelpers::FObjectFinder<UInputAction> iaMove(TEXT("/Script/EnhancedInput.InputAction'/Game/Inputs/IA_Move.IA_Move'"));

	if (iaMove.Succeeded())
		move = iaMove.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction> iaAttack(TEXT("/Script/EnhancedInput.InputAction'/Game/Inputs/IA_Attack.IA_Attack'"));

	if (iaAttack.Succeeded())
		attack = iaAttack.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction> iaSkillActive1(TEXT("/Script/EnhancedInput.InputAction'/Game/Inputs/IA_SkillActive1.IA_SkillActive1'"));

	if (iaSkillActive1.Succeeded())
		skillActive1 = iaSkillActive1.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction> iaSkillActive2(TEXT("/Script/EnhancedInput.InputAction'/Game/Inputs/IA_SkillActive2.IA_SkillActive2'"));

	if (iaSkillActive2.Succeeded())
		skillActive2 = iaSkillActive2.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction> iaSkillActive3(TEXT("/Script/EnhancedInput.InputAction'/Game/Inputs/IA_SkillActive3.IA_SkillActive3'"));

	if (iaSkillActive3.Succeeded())
		skillActive3 = iaSkillActive3.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction> iaSkillActive4(TEXT("/Script/EnhancedInput.InputAction'/Game/Inputs/IA_SkillActive4.IA_SkillActive4'"));

	if (iaSkillActive4.Succeeded())
		skillActive4 = iaSkillActive4.Object;


	static ConstructorHelpers::FObjectFinder<UInputAction> iaRoation(TEXT("/Script/EnhancedInput.InputAction'/Game/Inputs/IA_Rotation.IA_Rotation'"));

	if (iaRoation.Succeeded())
		rotation = iaRoation.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction> iaInventoryWidget(TEXT("/Script/EnhancedInput.InputAction'/Game/Inputs/IA_InventoryWidget.IA_InventoryWidget'"));

	if (iaInventoryWidget.Succeeded())
		inventoryWidget = iaInventoryWidget.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction> iaSkillWidget(TEXT("/Script/EnhancedInput.InputAction'/Game/Inputs/IA_SkillWidget.IA_SkillWidget'"));

	if (iaSkillWidget.Succeeded())
		skillWidget = iaSkillWidget.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction> iaStatusWidget(TEXT("/Script/EnhancedInput.InputAction'/Game/Inputs/IA_StatusWidget.IA_StatusWidget'"));

	if (iaStatusWidget.Succeeded())
		statusWidget = iaStatusWidget.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction> iaItemAction(TEXT("/Script/EnhancedInput.InputAction'/Game/Inputs/IA_ItemAction.IA_ItemAction'"));

	if (iaItemAction.Succeeded())
		itemAction = iaItemAction.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction> iaRun(TEXT("/Script/EnhancedInput.InputAction'/Game/Inputs/IA_Run.IA_Run'"));

	if (iaRun.Succeeded())
		run = iaRun.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction> iaDodge(TEXT("/Script/EnhancedInput.InputAction'/Game/Inputs/IA_Dodge.IA_Dodge'"));

	if (iaDodge.Succeeded())
		dodge = iaDodge.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction>
		iaUseQuicItem(TEXT("/Script/EnhancedInput.InputAction'/Game/Inputs/IA_UseQuickItem.IA_UseQuickItem'"));

	if (iaUseQuicItem.Succeeded())
		useQuickItem = iaUseQuicItem.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction>
		iaBlock(TEXT("/Script/EnhancedInput.InputAction'/Game/Inputs/IA_Block.IA_Block'"));

	if (iaBlock.Succeeded())
		block = iaBlock.Object;
}
