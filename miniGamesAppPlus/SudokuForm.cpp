#include "SudokuForm.h"

miniGamesAppPlus::SudokuForm::SudokuForm(void)
{
    InitializeComponent();
    GenerateMap();
}

System::Void miniGamesAppPlus::SudokuForm::правилаToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
    MessageBox::Show("Правила игры: \n1. Игровое поле представляет собой квадрат размером 9х9, разделённый на меньшие квадраты со стороной в 3 клетки. Таким образом, всё игровое поле состоит из 81 клетки.\n2. В них уже в начале игры стоят некоторые числа (от 1 до 9), называемые подсказками.\n3. От игрока требуется заполнить свободные клетки цифрами от 1 до 9 так, чтобы в каждой строке, в каждом столбце и в каждом малом квадрате 3х3 каждая цифра встречалась бы только один раз.", "Информация о игре");
    return System::Void();
}

System::Void miniGamesAppPlus::SudokuForm::выходToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
    this->Hide();
}

void miniGamesAppPlus::SudokuForm::GenerateMap()
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            map[i, j] = (i * 3 + i / 3 + j) % (9) + 1;
            buttons[i, j] = gcnew Button();
        }
    }
    Random^ r = gcnew Random();
    for (int i = 0; i < 40; i++)
    {
        ShuffleMap(r->Next(0, 5));
    }

    CreateMap();
    HideCells();
}

void miniGamesAppPlus::SudokuForm::HideCells()
{
    int N = 30;
    Random^ r = gcnew Random();
    while (N > 0)
    {
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                if (!String::IsNullOrEmpty(buttons[i, j]->Text)) {
                    int a = r->Next(0, 3);
                    buttons[i, j]->Text = a == 0 ? "" : buttons[i, j]->Text;
                    buttons[i, j]->Enabled = a == 0 ? true : false;

                    if (a == 0)
                        N--;
                    if (N <= 0)
                        break;
                }
            }
            if (N <= 0)
                break;
        }
    }
}

void miniGamesAppPlus::SudokuForm::ShuffleMap(int i)
{
    {
        switch (i)
        {
        case 0:
            MatrixTransposition();
            break;
        case 1:
            SwapRowsInBlock();
            break;
        case 2:
            SwapColumnsInBlock();
            break;
        case 3:
            SwapBlocksInRow();
            break;
        case 4:
            SwapBlocksInColumn();
            break;
        default:
            MatrixTransposition();
            break;
        }
    }
}

void miniGamesAppPlus::SudokuForm::SwapBlocksInColumn()
{
    {
        Random^ r = gcnew Random();
        Int32 block1 = r->Next(0, 3);
        Int32 block2 = r->Next(0, 3);
        while (block1 == block2)
            block2 = r->Next(0, 3);
        block1 *= 3;
        block2 *= 3;
        for (int i = 0; i < 9; i++)
        {
            Int32 k = block2;
            for (int j = block1; j < block1 + 3; j++)
            {
                Int32 temp = map[i, j];
                map[i, j] = map[i, k];
                map[i, k] = temp;
                k++;
            }
        }
    }
}

void miniGamesAppPlus::SudokuForm::SwapBlocksInRow()
{
    {
        Random^ r = gcnew Random();
        Int32 block1 = r->Next(0, 3);
        Int32 block2 = r->Next(0, 3);
        while (block1 == block2)
            block2 = r->Next(0, 3);
        block1 *= 3;
        block2 *= 3;
        for (int i = 0; i < 9; i++)
        {
            Int32 k = block2;
            for (int j = block1; j < block1 + 3; j++)
            {
                Int32 temp = map[j, i];
                map[j, i] = map[k, i];
                map[k, i] = temp;
                k++;
            }
        }
    }
}

void miniGamesAppPlus::SudokuForm::SwapRowsInBlock()
{
    Random^ r = gcnew Random();
    Int32 block = r->Next(0, 3);
    Int32 row1 = r->Next(0, 3);
    Int32 line1 = block * 3 + row1;
    Int32 row2 = r->Next(0, 3);
    while (row1 == row2)
        row2 = r->Next(0, 3);
    Int32 line2 = block * 3 + row2;
    for (int i = 0; i < 9; i++)
    {
        Int32 temp = map[line1, i];
        map[line1, i] = map[line2, i];
        map[line2, i] = temp;
    }
}

void miniGamesAppPlus::SudokuForm::SwapColumnsInBlock()
{
    {
        Random^ r = gcnew Random();
        Int32 block = r->Next(0, 3);
        Int32 row1 = r->Next(0, 3);
        Int32 line1 = block * 3 + row1;
        Int32 row2 = r->Next(0, 3);
        while (row1 == row2)
            row2 = r->Next(0, 3);
        Int32 line2 = block * 3 + row2;
        for (int i = 0; i < 9; i++)
        {
            Int32 temp = map[i, line1];
            map[i, line1] = map[i, line2];
            map[i, line2] = temp;
        }
    }
}

void miniGamesAppPlus::SudokuForm::MatrixTransposition()
{
    array<Int32, 2>^ tMap = gcnew array<Int32, 2>(9, 9);
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            tMap[i, j] = map[j, i];
        }
    }
    map = tMap;
}

void miniGamesAppPlus::SudokuForm::CreateMap()
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            Button^ button = gcnew Button();
            buttons[i, j] = button;
            button->Size = System::Drawing::Size(50, 50);
            button->Text = map[i, j].ToString();
            button->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &miniGamesAppPlus::SudokuForm::OnCellPressed);
            button->Location = Point(j * 50, 26 + i * 50);
            this->Controls->Add(button);
        }
    }
}

void miniGamesAppPlus::SudokuForm::OnCellPressed(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e)
{
    {
        Button^ pressedButton = (Button^)sender;
        String^ buttonText = pressedButton->Text;
        if (String::IsNullOrEmpty(buttonText))
        {
            pressedButton->Text = "1";
        }
        else
        {
            Int64 num = Convert::ToInt64(buttonText);
            num++;
            if (num == 10)
                num = 1;
            pressedButton->Text = num.ToString();
        }

    }
}

System::Void miniGamesAppPlus::SudokuForm::button1_Click(System::Object^ sender, System::EventArgs^ e)
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            String^ btnText = buttons[i, j]->Text;
            if (btnText != map[i, j].ToString())
            {
                MessageBox::Show("Неверно!");
                return;
            }
        }
    }
    MessageBox::Show("Верно!");
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            this->Controls->Remove(buttons[i, j]);
        }
    }
    GenerateMap();
}
