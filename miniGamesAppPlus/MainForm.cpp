#include "MainForm.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
void main(array<String^>^ arg) {
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

    miniGamesAppPlus::MainForm form;
    Application::Run(% form);
}

System::Void miniGamesAppPlus::MainForm::����������ToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
    MessageBox::Show("����� ������� ������ ���� ������� �� ��������������� ������. \n������� ������ ���� ����� ����� ������ ������ ����. \n������ �. ��-11.\n������ 2022.", "� ���������");
}

System::Void miniGamesAppPlus::MainForm::�����ToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
    Application::Exit();
}

System::Void miniGamesAppPlus::MainForm::Snake_Click(System::Object^ sender, System::EventArgs^ e)
{
    SnakeForm^ snf = gcnew SnakeForm();
    snf->Show();
}

System::Void miniGamesAppPlus::MainForm::Game_Click(System::Object^ sender, System::EventArgs^ e)
{
    GameForm^ gf = gcnew GameForm();
    gf->Show();
}

System::Void miniGamesAppPlus::MainForm::Sudoku_Click(System::Object^ sender, System::EventArgs^ e)
{
    SudokuForm^ sf = gcnew SudokuForm();
    sf->Show();
}
