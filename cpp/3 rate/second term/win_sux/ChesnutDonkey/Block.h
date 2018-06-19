#pragma once

#define LEFT		1
#define UP			3
#define RIGHT		5
#define DOWN		7

#define HALF_LEFT	2
#define HALF_UP		4
#define HALF_RIGHT	6
#define HALF_DOWN	8

class CBlock
// Elementary block description
{
protected:

	CPoint		ptPosition;	//left top point of the block
	int			nWidth, nHeight;
	bool		fIsSelected;	//selection flag

	CBlock () {}


	
	bool IsPointLeft( int x, int y )	const
	{
		return ( ( ptPosition.x - nWidth < x && x < ptPosition.x ) && 
			( ptPosition.y < y && y < ptPosition.y + nHeight ) ); 
	}

	bool IsPointHalfLeft( int x, int y )	const
	{
		return ( ( ptPosition.x - nWidth/2 < x && x < ptPosition.x ) && 
			( ptPosition.y < y && y < ptPosition.y + nHeight ) ); 
	}

	bool IsPointUp( int x, int y )	const
	{
		return ( ( ptPosition.x < x && x < ptPosition.x + nWidth ) && 
			( ptPosition.y - nHeight < y && y < ptPosition.y ) );
	}

	bool IsPointHalfUp( int x, int y )	const
	{
		return ( ( ptPosition.x < x && x < ptPosition.x + nWidth ) && 
			( ptPosition.y - nHeight/2 < y && y < ptPosition.y ) );
	}

	bool IsPointRight( int x, int y )	const
	{
		return ( ( ptPosition.x + 2*nWidth > x && x > ptPosition.x ) && 
			( ptPosition.y < y && y < ptPosition.y + nHeight ) );
	}

	bool IsPointHalfRight( int x, int y )	const
	{
		return ( ( ptPosition.x + 3*nWidth/2 > x && x > ptPosition.x ) && 
			( ptPosition.y < y && y < ptPosition.y + nHeight ) );
	}

	bool IsPointDown( int x, int y )	const
	{
		return ( ( ptPosition.x < x && x < ptPosition.x + nWidth ) &&
			( ptPosition.y + 2*nHeight > y && y > ptPosition.y ) );
	}

	bool IsPointHalfDown( int x, int y )	const
	{
		return ( ( ptPosition.x < x && x < ptPosition.x + nWidth ) &&
			( ptPosition.y + 3*nHeight/2 > y && y > ptPosition.y ) );
	}

public:

//Place constructors & operators there
	CBlock ( const CPoint& _ptPosition, int _nWidth, int _nHeight )
	{
		ptPosition = _ptPosition;
		nWidth = _nWidth;
		nHeight = _nHeight;
		fIsSelected = false;
	}

	CBlock ( int nLeft, int nTop, int _nWidth, int _nHeight )
	{
		ptPosition.SetPoint(nLeft, nTop);
		nWidth = _nWidth;
		nHeight = _nHeight;
		fIsSelected = false;
	}

	CBlock ( const CBlock& _cBlock )
	{
		ptPosition = _cBlock.ptPosition;
		nWidth = _cBlock.nWidth;
		nHeight = _cBlock.nHeight;
		fIsSelected = _cBlock.fIsSelected;
	}

	virtual ~CBlock() {}

	CBlock& operator = ( const CBlock& _cBlock )
	{
		if( this != &_cBlock ) 
		{
			ptPosition = _cBlock.ptPosition;
			nWidth = _cBlock.nWidth;
			nHeight = _cBlock.nHeight;
			fIsSelected = _cBlock.fIsSelected;
		}
		return *this;
	}

//Place base methods there

	bool IsSelected ()	const
	{
		return fIsSelected;
	}

	bool IsIn ( int x, int y )	const	
	{
		return ( ptPosition.x < x && x < ptPosition.x + nWidth ) && 
			( ptPosition.y < y && y < ptPosition.y + nHeight);
	}

	bool IsIn ( CPoint pt )	const	
	{
		return IsIn(pt.x,pt.y);
	}

	int Side(int x, int y)
	{
		if( IsPointHalfLeft(x,y) ) return HALF_LEFT;
		if( IsPointLeft(x,y) ) return LEFT;
		
		if( IsPointHalfUp(x,y) ) return HALF_UP;
		if( IsPointUp(x,y) ) return UP;

		if( IsPointHalfRight(x,y) ) return HALF_RIGHT;
		if( IsPointRight(x,y) ) return RIGHT;

		if( IsPointHalfDown(x,y) ) return HALF_DOWN;
		if( IsPointDown(x,y) ) return DOWN;

		return 0;
	}

	
	void Select ()
	{
		fIsSelected = true;
	}

	void UnSelect ()
	{
		fIsSelected = false;
	}

	
	virtual void Draw ( CDC* pDC, COLORREF UsualColor, COLORREF SelectedColor, int number )	const
	{
		CPen newPen( PS_SOLID, 2,(COLORREF) 0 );

		CPen* oldPen = pDC->SelectObject(&newPen);

		CRect drawRect( ptPosition.x, ptPosition.y, ptPosition.x + nWidth-2, ptPosition.y + nHeight-2 );
		pDC->Rectangle(&drawRect);
		pDC->FillRect(&drawRect, &CBrush(UsualColor)); 
		
		if(fIsSelected)
			pDC->FillRect( &drawRect, &CBrush(SelectedColor) );

		CString c1;
		c1.Format(L"%d",number);
		pDC->SetBkMode(TRANSPARENT);
		pDC->TextOutW(ptPosition.x + nWidth/2, ptPosition.y + nHeight/2, c1, 2);

		pDC->SelectObject(oldPen);
	}
	void DrawPathLeft ( CDC* pDC, COLORREF color )	const
	{
		pDC->FillRect(&CRect( ptPosition.x - nWidth - 1 , ptPosition.y - 1, ptPosition.x - 1, ptPosition.y + nHeight - 1 ),
			&CBrush(HS_DIAGCROSS,color));
	}

	void DrawPathHalfLeft ( CDC* pDC, COLORREF color )	const
	{
		pDC->FillRect(&CRect( ptPosition.x - nWidth/2 - 1 , ptPosition.y - 1, ptPosition.x - 1, ptPosition.y + nHeight - 1 ),
			&CBrush(HS_DIAGCROSS,color));
	}

	void DrawPathUp ( CDC* pDC, COLORREF color )	const
	{
		pDC->FillRect(&CRect( ptPosition.x, ptPosition.y - nHeight + 1, ptPosition.x + nWidth - 1, ptPosition.y - 1 ),
			&CBrush(HS_DIAGCROSS,color));
	}

	void DrawPathHalfUp ( CDC* pDC, COLORREF color )	const
	{
		pDC->FillRect(&CRect( ptPosition.x, ptPosition.y - nHeight/2 + 1, ptPosition.x + nWidth - 1, ptPosition.y - 1 ),
			&CBrush(HS_DIAGCROSS,color));
	}

	void DrawPathRight ( CDC* pDC, COLORREF color )	const
	{
		pDC->FillRect(&CRect( ptPosition.x + nWidth - 1, ptPosition.y - 1, ptPosition.x + 2*nWidth, ptPosition.y + nHeight),
			&CBrush(HS_DIAGCROSS,color));
	}

	void DrawPathHalfRight ( CDC* pDC, COLORREF color )	const
	{
		pDC->FillRect(&CRect( ptPosition.x + nWidth - 1, ptPosition.y - 1, ptPosition.x + 3*nWidth/2, ptPosition.y + nHeight),
			&CBrush(HS_DIAGCROSS,color));
	}

	void DrawPathDown ( CDC* pDC, COLORREF color )	const
	{
		pDC->FillRect(&CRect( ptPosition.x - 1, ptPosition.y + nHeight - 1, ptPosition.x + nWidth - 1, ptPosition.y +2*nHeight - 1 ),
			&CBrush(HS_DIAGCROSS,color));
	}

	void DrawPathHalfDown ( CDC* pDC, COLORREF color )	const
	{
		pDC->FillRect(&CRect( ptPosition.x - 1, ptPosition.y + nHeight - 1, ptPosition.x + nWidth - 1, ptPosition.y +3*nHeight/2 - 1 ),
			&CBrush(HS_DIAGCROSS,color));
	}

	
	void Move ( int nLeft, int nTop ) 
	{
		if(fIsSelected)
			ptPosition.SetPoint( nLeft, nTop );
			
	}
	void Move ( const CPoint& pt )
	{
		if(fIsSelected)
			ptPosition = pt;
	}

	void MoveLeft ( bool fHalfMove )
	{
		if(!fHalfMove) Move( ptPosition.x - nWidth, ptPosition.y );
		else Move( ptPosition.x - nWidth/2, ptPosition.y );
	}

	void MoveUp ( bool fHalfMove )
	{
		if(!fHalfMove) Move( ptPosition.x, ptPosition.y - nHeight );
		else Move( ptPosition.x, ptPosition.y - nHeight/2 );
	}

	void MoveDown ( bool fHalfMove )
	{
		if(!fHalfMove) Move( ptPosition.x, ptPosition.y + nHeight );
		else Move( ptPosition.x, ptPosition.y + nHeight/2 );
	}

	void MoveRight ( bool fHalfMove )
	{
		if(!fHalfMove) Move( ptPosition.x + nWidth, ptPosition.y );
		else Move( ptPosition.x + nWidth/2, ptPosition.y );
	}

	void Resize ( const CPoint& _ptPosition, int _nWidth, int _nHeight )
	{
		ptPosition = _ptPosition;
		nWidth = _nWidth;
		nHeight = _nHeight;
	}

	
	CPoint State()	const
	{
		return ptPosition; 
	}
	int Width()	const
	{
		return nWidth;
	}
	int Height()	const
	{
		return nHeight;
	}
	
	virtual CBlock* Clone ()	const
	{
		return new CBlock(*this);
	}



};

class CTargetBlock : public CBlock
{
	CBitmap* pBmp;
	BITMAP bmpInfo;
	
protected:

	CTargetBlock () {}

public:

//Place constructors & operators there
	CTargetBlock ( const CPoint& _ptPosition, int _nWidth, int _nHeight ) 
		: CBlock( _ptPosition, _nWidth, _nHeight)
	{
		pBmp = new CBitmap();
		pBmp->LoadBitmapW(IDB_DONKEY);
		pBmp->GetBitmap(&bmpInfo);
	}

	CTargetBlock ( int nLeft, int nTop, int _nWidth, int _nHeight )
		: CBlock( nLeft, nTop, _nWidth, _nHeight )
	{
		pBmp = new CBitmap();
		pBmp->LoadBitmapW(IDB_DONKEY);
		pBmp->GetBitmap(&bmpInfo);
	}

	CTargetBlock ( const CTargetBlock& _ctBlock ) : CBlock ( _ctBlock )
	{
		pBmp = new CBitmap();
		pBmp->LoadBitmapW(IDB_DONKEY);
		pBmp->GetBitmap(&bmpInfo);
	}

	~CTargetBlock() 
	{
		delete pBmp;
	}

	CTargetBlock& operator = ( const CTargetBlock& _ctBlock )
	{
		if( this != &_ctBlock ) 
			(CBlock)(*this) = (CBlock) _ctBlock;
		return *this;
	}

	
	void Draw ( CDC* pDC, COLORREF UsualColor, COLORREF SelectedColor, int number)	const
	{
		CDC dc;
		dc.CreateCompatibleDC( pDC );
		CBitmap* pBmpOld = dc.SelectObject(pBmp);
		
		pDC->StretchBlt(ptPosition.x, ptPosition.y, nWidth - 2, nHeight - 2, &dc, 
			0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, SRCCOPY );

		dc.SelectObject(pBmpOld);
		dc.DeleteDC();
		
		if(fIsSelected)
		{
		}
	}
	
	CTargetBlock* Clone ()	const
	{
		return new CTargetBlock(*this);
	}
};
