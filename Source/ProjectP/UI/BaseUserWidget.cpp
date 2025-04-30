// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseUserWidget.h"
#include "UIManager.h"

UBaseUserWidget::UBaseUserWidget(const FObjectInitializer& ObjectInitializer)
	:UUserWidget(ObjectInitializer)
{
}

void UBaseUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

    CUIManager::GetInstance()->AddWidget(GetName(), this);

    UE_LOG(ProjectP, Warning, TEXT("widgetName : %s"), *GetName());
}

void UBaseUserWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UBaseUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UBaseUserWidget::NativeDestruct()
{
	Super::NativeDestruct();
    CUIManager::GetInstance()->DeleteWidget(GetName());
}

void UBaseUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (dragEnable)
	{
		FVector2D MousePos = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());

		FVector2d MouseDelta = MousePos - dragOffset;

		dragPrevPos += MouseDelta;
		dragOffset = MousePos;

		UCanvasPanelSlot* PanelSlot = Cast<UCanvasPanelSlot>(Slot);
		if (IsValid(PanelSlot))
		{
			PanelSlot->SetPosition(dragPrevPos);
		}
	}
}

int32 UBaseUserWidget::NativePaint(const FPaintArgs& Args,
    const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect,
    FSlateWindowElementList& OutDrawElements, int32 LayerId,
    const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
    int32 result = Super::NativePaint(Args, AllottedGeometry, MyCullingRect,
        OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);

    return result;
}

FReply UBaseUserWidget::NativeOnFocusReceived(const FGeometry& InGeometry,
    const FFocusEvent& InFocusEvent)
{
    FReply result = Super::NativeOnFocusReceived(InGeometry, InFocusEvent);

    return result;
}

void UBaseUserWidget::NativeOnFocusLost(const FFocusEvent& InFocusEvent)
{
    Super::NativeOnFocusLost(InFocusEvent);
}

void UBaseUserWidget::NativeOnFocusChanging(
    const FWeakWidgetPath& PreviousFocusPath, const FWidgetPath& NewWidgetPath,
    const FFocusEvent& InFocusEvent)
{
    Super::NativeOnFocusChanging(PreviousFocusPath, NewWidgetPath, InFocusEvent);
}

void UBaseUserWidget::NativeOnAddedToFocusPath(const FFocusEvent& InFocusEvent)
{
    Super::NativeOnAddedToFocusPath(InFocusEvent);
}

void UBaseUserWidget::NativeOnRemovedFromFocusPath(const FFocusEvent& InFocusEvent)
{
    Super::NativeOnRemovedFromFocusPath(InFocusEvent);
}

FNavigationReply UBaseUserWidget::NativeOnNavigation(const FGeometry& MyGeometry,
    const FNavigationEvent& InNavigationEvent,
    const FNavigationReply& InDefaultReply)
{
    FNavigationReply result = Super::NativeOnNavigation(MyGeometry,
        InNavigationEvent, InDefaultReply);

    return result;
}

FReply UBaseUserWidget::NativeOnKeyChar(const FGeometry& InGeometry,
    const FCharacterEvent& InCharEvent)
{
    FReply result = Super::NativeOnKeyChar(InGeometry, InCharEvent);

    return result;
}

FReply UBaseUserWidget::NativeOnPreviewKeyDown(const FGeometry& InGeometry,
    const FKeyEvent& InKeyEvent)
{
    FReply result = Super::NativeOnPreviewKeyDown(InGeometry, InKeyEvent);

    return result;
}

FReply UBaseUserWidget::NativeOnKeyDown(const FGeometry& InGeometry,
    const FKeyEvent& InKeyEvent)
{
    FReply result = Super::NativeOnKeyDown(InGeometry, InKeyEvent);

    return result;
}

FReply UBaseUserWidget::NativeOnKeyUp(const FGeometry& InGeometry,
    const FKeyEvent& InKeyEvent)
{
    FReply result = Super::NativeOnKeyUp(InGeometry, InKeyEvent);

    return result;
}

FReply UBaseUserWidget::NativeOnAnalogValueChanged(const FGeometry& InGeometry,
    const FAnalogInputEvent& InAnalogEvent)
{
    FReply result = Super::NativeOnAnalogValueChanged(InGeometry, InAnalogEvent);

    return result;
}

FReply UBaseUserWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry,
    const FPointerEvent& InMouseEvent)
{
    FReply result = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

    return FReply::Handled();
}

FReply UBaseUserWidget::NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry,
    const FPointerEvent& InMouseEvent)
{
    FReply result = Super::NativeOnPreviewMouseButtonDown(InGeometry, InMouseEvent);

    return result;
}

FReply UBaseUserWidget::NativeOnMouseButtonUp(const FGeometry& InGeometry,
    const FPointerEvent& InMouseEvent)
{
    FReply result = Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);

    return result;
}

FReply UBaseUserWidget::NativeOnMouseMove(const FGeometry& InGeometry,
    const FPointerEvent& InMouseEvent)
{
    FReply result = Super::NativeOnMouseMove(InGeometry, InMouseEvent);

    return result;
}

void UBaseUserWidget::NativeOnMouseEnter(const FGeometry& InGeometry,
    const FPointerEvent& InMouseEvent)
{
    Super::NativeOnMouseEnter(InGeometry, InMouseEvent);
}

void UBaseUserWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
    Super::NativeOnMouseLeave(InMouseEvent);
}

FReply UBaseUserWidget::NativeOnMouseWheel(const FGeometry& InGeometry,
    const FPointerEvent& InMouseEvent)
{
    FReply result = Super::NativeOnMouseWheel(InGeometry, InMouseEvent);
    
    return result;
}

FReply UBaseUserWidget::NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry,
    const FPointerEvent& InMouseEvent)
{
    FReply result = Super::NativeOnMouseButtonDoubleClick(InGeometry, InMouseEvent);

    return FReply::Handled();
}

void UBaseUserWidget::NativeOnDragDetected(const FGeometry& InGeometry,
    const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
    Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
}

void UBaseUserWidget::NativeOnDragEnter(const FGeometry& InGeometry,
    const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
    Super::NativeOnDragEnter(InGeometry, InDragDropEvent, InOperation);
}

void UBaseUserWidget::NativeOnDragLeave(const FDragDropEvent& InDragDropEvent,
    UDragDropOperation* InOperation)
{
    Super::NativeOnDragLeave(InDragDropEvent, InOperation);
}

bool UBaseUserWidget::NativeOnDragOver(const FGeometry& InGeometry,
    const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
    bool result = Super::NativeOnDragOver(InGeometry, InDragDropEvent, InOperation);

    return result;
}

bool UBaseUserWidget::NativeOnDrop(const FGeometry& InGeometry,
    const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
    bool result = Super::NativeOnDragOver(InGeometry, InDragDropEvent, InOperation);

    return result;
}

void UBaseUserWidget::NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent,
    UDragDropOperation* InOperation)
{
    Super::NativeOnDragCancelled(InDragDropEvent, InOperation);
}

FReply UBaseUserWidget::NativeOnTouchGesture(const FGeometry& InGeometry,
    const FPointerEvent& InGestureEvent)
{
    FReply result = Super::NativeOnTouchGesture(InGeometry, InGestureEvent);

    return result;
}

FReply UBaseUserWidget::NativeOnTouchStarted(const FGeometry& InGeometry,
    const FPointerEvent& InGestureEvent)
{
    FReply result = Super::NativeOnTouchStarted(InGeometry, InGestureEvent);

    return result;
}

FReply UBaseUserWidget::NativeOnTouchMoved(const FGeometry& InGeometry,
    const FPointerEvent& InGestureEvent)
{
    FReply result = Super::NativeOnTouchMoved(InGeometry, InGestureEvent);

    return result;
}

FReply UBaseUserWidget::NativeOnTouchEnded(const FGeometry& InGeometry,
    const FPointerEvent& InGestureEvent)
{
    FReply result = Super::NativeOnTouchEnded(InGeometry, InGestureEvent);

    return result;
}

FReply UBaseUserWidget::NativeOnMotionDetected(const FGeometry& InGeometry,
    const FMotionEvent& InMotionEvent)
{
    FReply result = Super::NativeOnMotionDetected(InGeometry, InMotionEvent);

    return result;
}

FReply UBaseUserWidget::NativeOnTouchForceChanged(const FGeometry& MyGeometry,
    const FPointerEvent& TouchEvent)
{
    FReply result = Super::NativeOnTouchForceChanged(MyGeometry, TouchEvent);

    return result;
}

FCursorReply UBaseUserWidget::NativeOnCursorQuery(const FGeometry& InGeometry,
    const FPointerEvent& InCursorEvent)
{
    FCursorReply result = Super::NativeOnCursorQuery(InGeometry, InCursorEvent);

    return result;
}

FNavigationReply UBaseUserWidget::NativeOnNavigation(const FGeometry& InGeometry,
    const FNavigationEvent& InNavigationEvent)
{
    FNavigationReply result = Super::NativeOnNavigation(InGeometry, InNavigationEvent);

    return result;
}

void UBaseUserWidget::NativeOnMouseCaptureLost(
    const FCaptureLostEvent& CaptureLostEvent)
{
    Super::NativeOnMouseCaptureLost(CaptureLostEvent);
}
