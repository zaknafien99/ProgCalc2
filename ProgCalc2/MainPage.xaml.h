//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"

namespace ProgCalc2
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	 
	int ConvertTextToInt(Platform::String^ str);
	unsigned long FromBinary(std::wstring s);
	Platform::String^ ToBinary(int n);
	

	enum class ArithOp
	{
		PLUS, MINUS, TIMES, DIVIDE, NONE
	};

	enum class Base
	{
		DEC, HEX, BIN
	};
		
	public ref class MainPage sealed
	{
	public:
		MainPage();
		
	


	private:
		void NumberButtons_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void ArithmeticButtons_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void btnClear_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);

		int ConvertTextToInt(Platform::String^ str);

		int leftOperand;
		
		void btnEquals_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Reset();

		ArithOp currentOp;
		bool clearOnNextKey;

		Base base;

		void BaseButtons_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);

		void EnableHexButtons(bool enable);
		void EnableDecimalButtons(bool enable);
		void EnableBinaryButtons();

		Platform::String^ ConvertOutputString(int val);

		

	};
}
