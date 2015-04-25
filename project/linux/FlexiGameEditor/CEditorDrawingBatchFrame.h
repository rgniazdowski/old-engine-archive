#ifndef CEDITORDRAWINGBATCHFRAME_H
#define CEDITORDRAWINGBATCHFRAME_H

//(*Headers(CEditorDrawingBatchFrame)
#include <wx/frame.h>
//*)

class CEditorDrawingBatchFrame: public wxFrame
{
	public:

		CEditorDrawingBatchFrame(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~CEditorDrawingBatchFrame();

		//(*Declarations(CEditorDrawingBatchFrame)
		//*)

	protected:

		//(*Identifiers(CEditorDrawingBatchFrame)
		//*)

	private:

		//(*Handlers(CEditorDrawingBatchFrame)
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
