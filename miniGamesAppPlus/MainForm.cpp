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

System::Void miniGamesAppPlus::MainForm::îÏðîãðàììåToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
    MessageBox::Show("×òîáû îòêðûòü íóæíóþ èãðó íàæìèòå íà ñîîòâåòñòâóþùóþ êíîïêó. \nÏðàâèëà êàæäîé èãðû ìîæíî áóäåò óçíàòü âíóòðè èãðû. \nßêèìîâ À. ÏÈ-11.\nÀëòÃÒÓ 2022.", "Î ïðîãðàììå");
}

System::Void miniGamesAppPlus::MainForm::âûõîäToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
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
