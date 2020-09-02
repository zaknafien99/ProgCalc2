//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace ProgCalc2;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

//Constructor
MainPage::MainPage()
{
	InitializeComponent();

	currentOp = ArithOp::NONE;
}


void ProgCalc2::MainPage::NumberButtons_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (clearOnNextKey == true)
	{
		textOutput->Text = " ";
		clearOnNextKey = false;
	} 
	else {

		Button^ btn = (Button^)sender;	//cast the sender handle to a button
		String^ digit = (String^)btn->Content; // cast the content to a string
		textOutput->Text += digit;

	}
}



void ProgCalc2::MainPage::btnClear_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{	
	textOutput->Text = " ";	
}


// This function is not converting properly
int ProgCalc2::MainPage::ConvertTextToInt(Platform::String^ s)
{
	int n;

	if (base == Base::HEX)
		swscanf_s(s->Data(), L"%x", &n);
	else if (base == Base::DEC)
		swscanf_s(s->Data(), L"%d", &n);
	else if (base == Base::BIN)
		n = FromBinary(s->Data());

	return n;
}


void ProgCalc2::MainPage::ArithmeticButtons_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	String^ txt = textOutput->Text;
	int val;
	swscanf_s(txt->Data(), L"%d", &val);
	leftOperand = val;

	Button^ btn = (Button^)sender;
	if (btn == btnPlus) currentOp = ArithOp::PLUS;
	else if (btn == btnMinus) currentOp = ArithOp::MINUS;
	else if (btn == btnTimes) currentOp = ArithOp::TIMES;
	else if (btn == btnDivide) currentOp = ArithOp::DIVIDE;
	
	textOutput->Text = " ";
}



void ProgCalc2::MainPage::btnEquals_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	//int leftOperand = 0;
	int rightOperand = 0;
	int result = 0;
	// Check if there is anything to do
	if (currentOp == ArithOp::NONE)
		return;
	if (textOutput->Text->Length() == 0)
		return;
		
	// Get the string from the display and convert it to a number
	Button^ btn = (Button^)sender;
	
	rightOperand = ConvertTextToInt(textOutput->Text);


	switch (currentOp)
	{
	case ArithOp::PLUS:
		result = leftOperand + rightOperand;
		break;
	case ArithOp::MINUS:
		result = leftOperand - rightOperand;
		break;
	case ArithOp::TIMES:
		result = leftOperand * rightOperand;
		break;
	case ArithOp::DIVIDE:
		if (rightOperand == 0) {
			textOutput->Text = "Divide by Zero";
			Reset();
			return;
		}
		result = leftOperand / rightOperand;
		
		break;

	default:
		break;
	} 

	// Turn the result into a string and put it back in the display. Swprintf takes a value and converts it to a string, needs an array of wchar_t,
	// which you need to convert to a Platform::String object in order to use it with the TextBlock
	textOutput->Text = ConvertOutputString(result);
	clearOnNextKey = true;

}

void ProgCalc2::MainPage::Reset()
{
	currentOp = ArithOp::NONE;
	base = Base::DEC;
	txtBase->Text = "dec";
	leftOperand = 0;
	clearOnNextKey = true;
	EnableDecimalButtons(true);
	EnableHexButtons(false);
}

void ProgCalc2::MainPage::BaseButtons_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	// Get the value from the display
	int val = 0;

	if (textOutput->Text->Length() > 0)
		val = ConvertTextToInt(textOutput->Text);
		

	// Get the button that was pressed
	Button^ btn = (Button^)sender;

	if (btn == btnDecimal)
	{
		// Enable the decimal buttons
		EnableDecimalButtons(true);
		EnableHexButtons(false);
		base = Base::DEC;
		txtBase->Text = "dec";
		
	}
	else if (btn == btnHex)
	{
		// Enable the hex buttons
		EnableDecimalButtons(true);
		EnableHexButtons(true);
		base = Base::HEX;
		txtBase->Text = "hex";
	}
	else if (btn == btnBinary)
	{
		// Enable the binary buttons
		EnableBinaryButtons();
		base = Base::BIN;
		txtBase->Text = "bin";
	}

	// update the display
	textOutput->Text = ConvertOutputString(val);
	clearOnNextKey = true;
}

void ProgCalc2::MainPage::EnableHexButtons(bool enable)
{
	btnHexA->IsEnabled = enable;
	btnHexB->IsEnabled = enable;
	btnHexC->IsEnabled = enable;
	btnHexD->IsEnabled = enable;
	btnHexE->IsEnabled = enable;
	btnHexF->IsEnabled = enable;
}

void ProgCalc2::MainPage::EnableBinaryButtons()
{
	EnableHexButtons(false);
	EnableDecimalButtons(false);
	btnZero->IsEnabled = true;
	btnOne->IsEnabled = true;
}

void ProgCalc2::MainPage::EnableDecimalButtons(bool enable)
{
	btnZero->IsEnabled = enable;
	btnOne->IsEnabled = enable;
	btnTwo->IsEnabled = enable;
	btnThree->IsEnabled = enable;
	btnFour->IsEnabled = enable;
	btnFive->IsEnabled = enable;
	btnSix->IsEnabled = enable;
	btnSeven->IsEnabled = enable;
	btnEight->IsEnabled = enable;
	btnNine->IsEnabled = enable;
}

unsigned long ProgCalc2::FromBinary(std::wstring s)
{
	wchar_t* stop;
	long l = wcstol(s.c_str(), &stop, 2);

	return l;

	// This function uses the wcstol (Wide Character String To Long) function for the conversion, which will cope with input strings in binary.
}

Platform::String^ ProgCalc2::MainPage::ConvertOutputString(int val)
{
	wchar_t buff[80];
	if (base == Base::HEX)
		swprintf(buff, 80, L"%x", val);
	else if (base == Base::DEC)
		swprintf(buff, 80, L"%d", val);
	else if (base == Base::BIN)
	{
		String^ bf = ToBinary(val);
		return bf;
	}
	return ref new String(buff);
}

Platform::String^ ProgCalc2::ToBinary(int n)
{
	String^ s = ref new String();

	do {
		s += (n & 1) ? L'1' : L'0';
	} while (n >>= 1);

	std::wstring result(s->Data());
	std::reverse(result.begin(), result.end());

	s = ref new String(result.c_str());
	return s;
}