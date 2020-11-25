#include "cMain.h"
#include <stdlib.h>
#include <time.h>


wxBEGIN_EVENT_TABLE(cMain, wxFrame) 
	//EVT_BUTTON(10001, OnButtonClicked)
wxEND_EVENT_TABLE()

cMain::cMain() : wxFrame(nullptr, wxID_ANY, "wxWidget first app example - Stanislav") {
	/*m_btn1 = new wxButton(this, 10001, "Cliqueame", wxPoint(10, 10), wxSize(150, 50));
	m_txt1 = new wxTextCtrl(this, wxID_ANY, "", wxPoint(10, 70), wxSize(300, 30));
	m_list1 = new wxListBox(this, wxID_ANY, wxPoint(10, 110), wxSize(300, 300));*/

	btn = new wxButton * [nFieldHeight * nFieldWidth];
	wxGridSizer* grid = new wxGridSizer(nFieldWidth, nFieldHeight, 0, 0);
	
	nField = new int[nFieldHeight * nFieldWidth];

	wxFont font(24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false);

	for (int x = 0; x < nFieldWidth; x++) {
		for (int y = 0; y < nFieldHeight; y++) {
			btn[y * nFieldWidth + x] = new wxButton(this, 10000 + (y * nFieldWidth + x));
			btn[y * nFieldWidth + x]->SetFont(font);
			grid->Add(btn[y * nFieldWidth + x], 1, wxEXPAND | wxALL);
			btn[y * nFieldWidth + x]->Bind(wxEVT_BUTTON, &cMain::OnButtonClicked, this);
			btn[y * nFieldWidth + x]->Connect(wxEVT_RIGHT_UP, wxMouseEventHandler(cMain::OnButtonRightClicked), NULL, this);
			btn[y * nFieldWidth + x]->SetBackgroundColour(bBackGroundColor_default);
			nField[y * nFieldWidth + x] = 0;
		}
	}
	this->SetSizer(grid);
	grid->Layout();
}

cMain::~cMain() {
	delete[] btn;
}

void cMain::OnButtonRightClicked(wxMouseEvent& evt) {
	int x = (evt.GetId() - 10000) % nFieldWidth;
	int y = (evt.GetId() - 10000) / nFieldWidth;
	//btn[y * nFieldWidth + x]->Enable(false);


	if (btn[y * nFieldWidth + x]->GetBackgroundColour() != bBackGroundColor_default)
		btn[y * nFieldWidth + x]->SetBackgroundColour(bBackGroundColor_default);
	else
		btn[y * nFieldWidth + x]->SetBackgroundColour(bBackGroundColor_mined);
	evt.Skip();

}

void cMain::OnButtonClicked(wxCommandEvent& evt) {
	//m_list1->AppendString(m_txt1->GetValue());


	//obtener las coordenadas de los botones 
	int x = (evt.GetId() - 10000) % nFieldWidth;
	int y = (evt.GetId() - 10000) / nFieldWidth;

	if (bFirstClick) {
		int mines = 30;

		srand(time(NULL));
		while (mines) {
			int rx = rand() % nFieldWidth;
			int ry = rand() % nFieldHeight;

			if (nField[ry * nFieldWidth + rx] == 0 && rx != x && ry != y) {
				nField[ry * nFieldWidth + rx] = -1;
				mines--;
			}
		}
		bFirstClick = false;


	}
	btn[y * nFieldWidth + x]->Enable(false);

	if (nField[y * nFieldWidth + x] == -1) {
		for (int x = 0; x < nFieldWidth; x++)
			for (int y = 0; y < nFieldHeight; y++) {
				if(nField[y*nFieldWidth+x] == -1)
					btn[y * nFieldWidth + x]->SetLabel("X");
			}

			
		wxMessageBox("BOOOM");
		bFirstClick = true;
		for (int x = 0; x < nFieldWidth; x++) 
			for (int y = 0; y < nFieldHeight; y++) {
				nField[y * nFieldWidth + x] = 0;
				btn[y * nFieldWidth + x]->SetLabel("");
				btn[y * nFieldWidth + x]->Enable(true);
				btn[y * nFieldWidth + x]->SetBackgroundColour(bBackGroundColor_default);
			}
		
	}
	else {
		int mine_count = 0;
		for(int i = -1; i<2; i++)
			for (int j = -1; j < 2; j++) {
				if (x + i >= 0 && x + i < nFieldWidth && y + j >= 0 && y + j < nFieldHeight)
					if (nField[(y + j) * nFieldWidth + (x + i)] == -1)
						mine_count++;
			}
		if (mine_count > 0) {
			btn[y * nFieldWidth + x]->SetLabel(std::to_string(mine_count));
		}
		else
		{
			btn[y * nFieldWidth + x]->SetBackgroundColour(wxColour(130, 130, 130, 130));
		}
	}
	evt.Skip();
}