#pragma once
#include "GameForm.h"
#include "SudokuForm.h"
#include "SnakeForm.h"

namespace miniGamesAppPlus {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::MenuStrip^ menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^ оПрограммеToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ выходToolStripMenuItem;
	private: System::Windows::Forms::Button^ Snake;
	private: System::Windows::Forms::Button^ Game;
	private: System::Windows::Forms::Button^ Sudoku;


	protected:

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->оПрограммеToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->выходToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->Snake = (gcnew System::Windows::Forms::Button());
			this->Game = (gcnew System::Windows::Forms::Button());
			this->Sudoku = (gcnew System::Windows::Forms::Button());
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->оПрограммеToolStripMenuItem,
					this->выходToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(284, 24);
			this->menuStrip1->TabIndex = 0;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// оПрограммеToolStripMenuItem
			// 
			this->оПрограммеToolStripMenuItem->Name = L"оПрограммеToolStripMenuItem";
			this->оПрограммеToolStripMenuItem->Size = System::Drawing::Size(94, 20);
			this->оПрограммеToolStripMenuItem->Text = L"О программе";
			this->оПрограммеToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::оПрограммеToolStripMenuItem_Click);
			// 
			// выходToolStripMenuItem
			// 
			this->выходToolStripMenuItem->Name = L"выходToolStripMenuItem";
			this->выходToolStripMenuItem->Size = System::Drawing::Size(54, 20);
			this->выходToolStripMenuItem->Text = L"Выход";
			this->выходToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::выходToolStripMenuItem_Click);
			// 
			// Snake
			// 
			this->Snake->Location = System::Drawing::Point(12, 40);
			this->Snake->Name = L"Snake";
			this->Snake->Size = System::Drawing::Size(260, 61);
			this->Snake->TabIndex = 1;
			this->Snake->Text = L"Змейка";
			this->Snake->UseVisualStyleBackColor = true;
			this->Snake->Click += gcnew System::EventHandler(this, &MainForm::Snake_Click);
			// 
			// Game
			// 
			this->Game->Location = System::Drawing::Point(12, 107);
			this->Game->Name = L"Game";
			this->Game->Size = System::Drawing::Size(260, 61);
			this->Game->TabIndex = 2;
			this->Game->Text = L"2048";
			this->Game->UseVisualStyleBackColor = true;
			this->Game->Click += gcnew System::EventHandler(this, &MainForm::Game_Click);
			// 
			// Sudoku
			// 
			this->Sudoku->Location = System::Drawing::Point(12, 174);
			this->Sudoku->Name = L"Sudoku";
			this->Sudoku->Size = System::Drawing::Size(260, 61);
			this->Sudoku->TabIndex = 3;
			this->Sudoku->Text = L"Судоку";
			this->Sudoku->UseVisualStyleBackColor = true;
			this->Sudoku->Click += gcnew System::EventHandler(this, &MainForm::Sudoku_Click);
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 261);
			this->Controls->Add(this->Sudoku);
			this->Controls->Add(this->Game);
			this->Controls->Add(this->Snake);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->MaximizeBox = false;
			this->Name = L"MainForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Сборник мини игр";
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void оПрограммеToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void выходToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void Snake_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void Game_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void Sudoku_Click(System::Object^ sender, System::EventArgs^ e);
};
}
