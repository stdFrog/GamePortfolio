#pragma once

COLORREF SysColor[] = {
	(COLORREF)INVALID_HANDLE_VALUE,
	RGB(0,0,0),
	RGB(255,0,0),
	RGB(0,255,0),
	RGB(0,0,255),
	RGB(255,255,0),
	RGB(0,255,255),
	RGB(255,0,255),
	RGB(255,255,255),
	RGB(64,64,64),
	RGB(128,128,128)
};

enum class EditTool {
	ET_SELECT,
	ET_LINE,
	ET_ELLIPSE,
	ET_RECTANGLE,
	ET_TEXT,
	ET_BITMAP,
	ET_METAFILE,
	ET_PAINT,
	EDIT_TOOL_LAST
};

enum class EditMode {
	EM_NONE,
	EM_DRAW,
	EM_MOVE,
	EM_SIZE
};

class EditObject {
public:
	EditObject(EditTool _Type = EditTool::ET_SELECT) :
		Type(_Type), Rect(0,0,0,0), LineWidth(0), LineColor(RGB(0,0,0)),
		PlaneColor(RGB(0,0,0)), Length(0), FontSize(0), FontColor(RGB(0,0,0)),
		FontName(L"굴림"), Text(NULL)
	{ 
	}

public:
	EditTool Type;
	RECT Rect;

	int LineWidth;
	COLORREF LineColor;
	COLORREF PlaneColor;

	// TEXT
	int Length;
	int FontSize;
	COLORREF FontColor;
	TCHAR FontName[32];

	union {
		TCHAR* Text;
		BYTE* Bitmap;
		BYTE* MetaFile;
	};
};

class EditScene : public BaseScene
{
private:
	// Pen, Brush, Background, TextBk, ... Append Color Ref
	std::vector<std::vector<EditObject>> _Objects;
	std::vector<std::pair<POINT, POINT>> _Lines;

	EditMode _CommonMode;
	EditObject _CommonObject;

	RECT _crt, wrt;
	BOOL _bOrigin, _bPaint;
	POINT _LastPosition, _StartPoint;

public:
	EditScene();
	virtual ~EditScene();

public:
	virtual void Update(float);
	virtual void Render(HDC);
	virtual BOOL Initialize();
	void Fill(HDC, int, int, COLORREF, COLORREF);
	void Fill(HDC, POINT, COLORREF, COLORREF);
};

