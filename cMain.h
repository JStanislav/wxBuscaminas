#pragma once

#include <wx/wx.h>

class cMain: public wxFrame
{
public:
	cMain();
	~cMain();


public:
	/*wxButton* m_btn1 = nullptr;
	wxTextCtrl* m_txt1 = nullptr;
	wxListBox* m_list1 = nullptr;*/

	int nFieldWidth = 10;
	int nFieldHeight = 10;
	wxButton** btn;
	int* nField = nullptr;
	bool bFirstClick = true;
	
	wxColour bBackGroundColor_default = wxColour(255, 255, 255);
	wxColour bBackGroundColor_mined = wxColour(50, 50, 50);

	void OnButtonClicked(wxCommandEvent& evt);
	void OnButtonRightClicked(wxMouseEvent& evt);

	wxDECLARE_EVENT_TABLE();
};

