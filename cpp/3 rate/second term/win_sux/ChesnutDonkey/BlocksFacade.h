#pragma once

#include "Block.h"
#include <vector>
using namespace std;

#define BLOCK_QUANTITY		10 

struct MOVE
{
	int blockCount;
	int direction;

	MOVE()
	{
		blockCount = direction = 0;
	}

	MOVE(int nBlock, int nDir)
	{
		blockCount = nBlock;
		direction = nDir;
	}

	CString ToString()
	{
		
		CString c1,c2;
		if(blockCount) c1.Format(L"%d", blockCount);
		c2.LoadStringW(direction + 300);
		c1.Append(c2);
		//TCHAR *first = new TCHAR[20], *second = new TCHAR[20];
		//LoadString(AfxGetInstanceHandle(), blockCount + 101, first, 20);
		//LoadString(AfxGetInstanceHandle(), direction + 300, second, 20);
		//_tcscat(first,second);
		return c1;
	}
};

struct CBlocksFactoryState
{
	int BlockPositions[BLOCK_QUANTITY]; // number of field cell which contains chip left upper corner 

	CBlocksFactoryState()
	{
		BlockPositions[0] = 0;
		BlockPositions[1] = 1;
		BlockPositions[2] = 3;

		BlockPositions[3] = 8;
		BlockPositions[4] = 9;
		BlockPositions[5] = 11;

		BlockPositions[6] = 13;
		BlockPositions[7] = 14;
		BlockPositions[8] = 16;
		BlockPositions[9] = 19;
	}
};


class CBlocksFactory
{
	#define WIDTH_UNITS			4
	#define HEIGHT_UNITS		5

	vector <CBlock*> Container;			// array of blocks
	int nFieldWidth, nFieldHeight;		// field dimensions
	CPoint ptPos;

	int blockUnitWidth, blockUnitHeight;

	bool needDrawPaths;

	CPoint ConvertStateToPosition(int nCellNumber)
	{
		CPoint res;
		
		res.x = ptPos.x + (nCellNumber % WIDTH_UNITS) * blockUnitWidth;
		res.y = ptPos.y + (int)(nCellNumber / WIDTH_UNITS) * blockUnitHeight;

		return res;
	}
	int ConvertPositionToState(int nBlock)
	{
		return (WIDTH_UNITS * (Container[nBlock]->State().y - ptPos.y) / blockUnitHeight + (Container[nBlock]->State().x - ptPos.x) / blockUnitWidth);
	}


public:
		
	CBlocksFactory (CPoint pt, int _nFieldWidth, int _nFieldHeight )
	{
		nFieldHeight = _nFieldHeight;
		nFieldWidth = _nFieldWidth;
		ptPos = pt;

		needDrawPaths = false;
		
		blockUnitWidth = (int) _nFieldWidth / WIDTH_UNITS;
		blockUnitHeight = (int) _nFieldHeight / HEIGHT_UNITS;

		Container.resize( BLOCK_QUANTITY );
		
		//1
		Container[0] = new CBlock( 0 + pt.x, 0 + pt.y, blockUnitWidth, 2*blockUnitHeight);;

		//2 target
		Container[1] = new CTargetBlock( blockUnitWidth + pt.x, 0 + pt.y, 2*blockUnitWidth, 2*blockUnitHeight);

		//3
		Container[2] = new CBlock( 3 * blockUnitWidth + pt.x, 0 + pt.y, blockUnitWidth, 2*blockUnitHeight);

		///////////////////////////////////////////////////////////////////////////////////////
		//4
		Container[3] = new CBlock( 0 + pt.x, 2*blockUnitHeight + pt.y, blockUnitWidth, 2*blockUnitHeight);

		//5
		Container[4] = new CBlock( blockUnitWidth + pt.x, 2*blockUnitHeight + pt.y, 2*blockUnitWidth, blockUnitHeight);

		//6
		Container[5] = new CBlock( 3 * blockUnitWidth + pt.x, 2*blockUnitHeight + pt.y, blockUnitWidth, 2 * blockUnitHeight);

		///////////////////////////////////////////////////////////////////////////////////////
		//7
		Container[6] = new CBlock( blockUnitWidth + pt.x, 3*blockUnitHeight + pt.y, blockUnitWidth, blockUnitHeight);

		//8 
		Container[7] = new CBlock( 2*blockUnitWidth + pt.x, 3*blockUnitHeight + pt.y, blockUnitWidth, blockUnitHeight);

		///////////////////////////////////////////////////////////////////////////////////////
		//9
		Container[8] = new CBlock( 0 + pt.x, 4*blockUnitHeight + pt.y, blockUnitWidth, blockUnitHeight);

		//10	
		Container[9] = new CBlock( 3*blockUnitWidth + pt.x, 4*blockUnitHeight + pt.y, blockUnitWidth, blockUnitHeight);
	}

	CBlocksFactory (const CBlocksFactoryState& cbfs, CPoint pt, int _nFieldWidth, int _nFieldHeight)
	{
		nFieldHeight = _nFieldHeight;
		nFieldWidth = _nFieldWidth;
		ptPos = pt;

		blockUnitWidth = (int) _nFieldWidth / WIDTH_UNITS;
		blockUnitHeight = (int) _nFieldHeight / HEIGHT_UNITS;

		Container.resize( BLOCK_QUANTITY );

		//1
		Container[0] = new CBlock( ConvertStateToPosition(cbfs.BlockPositions[0]), blockUnitWidth, 2*blockUnitHeight);

		//2 target
		Container[1] = new CTargetBlock( ConvertStateToPosition(cbfs.BlockPositions[1]), 2*blockUnitWidth, 2*blockUnitHeight);

		//3
		Container[2] = new CBlock( ConvertStateToPosition(cbfs.BlockPositions[2]), blockUnitWidth, 2*blockUnitHeight);

		//4
		Container[3] = new CBlock( ConvertStateToPosition(cbfs.BlockPositions[3]), blockUnitWidth, 2*blockUnitHeight);

		//5
		Container[4] = new CBlock( ConvertStateToPosition(cbfs.BlockPositions[4]), 2*blockUnitWidth, blockUnitHeight);

		//6
		Container[5] = new CBlock( ConvertStateToPosition(cbfs.BlockPositions[5]), blockUnitWidth, 2 * blockUnitHeight);

		//7
		Container[6] = new CBlock( ConvertStateToPosition(cbfs.BlockPositions[6]), blockUnitWidth, blockUnitHeight);

		//8 
		Container[7] = new CBlock( ConvertStateToPosition(cbfs.BlockPositions[7]), blockUnitWidth, blockUnitHeight);

		//9
		Container[8] = new CBlock( ConvertStateToPosition(cbfs.BlockPositions[8]), blockUnitWidth, blockUnitHeight);

		//10	
		Container[9] = new CBlock( ConvertStateToPosition(cbfs.BlockPositions[9]), blockUnitWidth, blockUnitHeight);

		needDrawPaths = false;
	}

	
	CBlocksFactory ( const CBlocksFactory& bf )
	{
		nFieldHeight = bf.nFieldHeight;
		nFieldWidth = bf.nFieldWidth;
		ptPos = bf.ptPos;

		Container.resize( BLOCK_QUANTITY );

		for( int i = 0; i < BLOCK_QUANTITY; ++i)
			Container[i] = bf.Container[i]->Clone();

		needDrawPaths = false;
	}

	~CBlocksFactory ()
	{
		for(int i = 0; i < Container.size(); ++i)
		{
			delete Container[i];
		}
	}
	
	int FindSelected ()	const
	{
		for( int i = 0; i < BLOCK_QUANTITY; ++i )
			if ( Container[i]->IsSelected() )
				return i;
		return -1;
	}
protected:

	CBlocksFactory () {}

	void UnSelect()
	{
		for(int i = 0; i < BLOCK_QUANTITY; ++i )
			Container[i]->UnSelect();
		needDrawPaths = false;
	}

	int FindPathLeft( int nSelectedInd ) const			//stable
	{
		CPoint ptPosition = Container[nSelectedInd]->State();
		int nWidth = Container[nSelectedInd]->Width(), 
			nHeight = Container[nSelectedInd]->Height(); 

		CPoint ptLT( (ptPosition.x - nWidth - 1) + blockUnitWidth / 4, ptPosition.y + blockUnitHeight / 4 ),
			ptLB( (ptPosition.x - nWidth - 1) + blockUnitWidth / 4, (ptPosition.y + nHeight + 1) - blockUnitHeight / 4 ),
			ptRT( (ptPosition.x - 1) - blockUnitWidth / 4, ptPosition.y + blockUnitHeight / 4 ),
			ptRB( (ptPosition.x - 1) - blockUnitWidth / 4, (ptPosition.y + nHeight + 1) - blockUnitHeight / 4 );

		if( ptRT.x < ptPos.x ) return ptPos.x - 1;		
		
		int q = 0;
		for(int i = 0; i < BLOCK_QUANTITY; ++i)
		{
			if( i != nSelectedInd )
			{
				if ( !Container[i]->IsIn(ptLT) && !Container[i]->IsIn(ptLB) &&
					!Container[i]->IsIn(ptRT) && !Container[i]->IsIn(ptRB) )
					q++;
			}
		}
		if( q == 9 )
			return ptPosition.x - nWidth;
		else return ptPos.x - 1;
	}


	int FindPathHalfLeft( int nSelectedInd ) const		//unstable
	{
		int nWidth, nHeight;

		if( nWidth = Container[nSelectedInd]->Width() == blockUnitWidth )
			return FindPathLeft( nSelectedInd );

		CPoint ptPosition = Container[nSelectedInd]->State();
		nHeight = Container[nSelectedInd]->Height();

		CPoint ptRT( (ptPosition.x - 1) - blockUnitWidth / 4, ptPosition.y + blockUnitHeight / 4 ),
			ptRB( (ptPosition.x - 1) - blockUnitWidth / 4, (ptPosition.y + nHeight + 1) - blockUnitHeight / 4 );

		if( ptRT.x < ptPos.x ) return ptPos.x - 1;		
		
		int q = 0;
		for(int i = 0; i < BLOCK_QUANTITY; ++i)
		{
			if( i != nSelectedInd )
			{
				if ( !Container[i]->IsIn(ptRT) && !Container[i]->IsIn(ptRB) )
					q++;
			}
		}
		if( q == 9 )
			return ptPosition.x - nWidth;
		else return ptPos.x - 1;
	}

	int FindPathRight( int nSelectedInd ) const		//stable
	{
		CPoint ptPosition = Container[nSelectedInd]->State();
		int nWidth = Container[nSelectedInd]->Width(), 
			nHeight = Container[nSelectedInd]->Height();

		CPoint ptLT( (ptPosition.x + nWidth + 1) + blockUnitWidth / 4, ptPosition.y + blockUnitWidth / 4 ),
			ptLB( (ptPosition.x + nWidth + 1) + blockUnitWidth / 4, ( ptPosition.y + nHeight ) - blockUnitHeight / 4 ),
			ptRT( ( ptPosition.x + 2*nWidth + 1) - blockUnitWidth / 4, ptPosition.y + blockUnitWidth / 4 ),
			ptRB( ( ptPosition.x + 2*nWidth + 1) - blockUnitWidth / 4, ( ptPosition.y + nHeight ) - blockUnitHeight / 4 );

		if( ptRT.x > ptPos.x + nFieldWidth ) return ptPos.x + nFieldWidth + 1; 
		
		int q = 0;
		for(int i = 0; i < BLOCK_QUANTITY; ++i)
		{
			if( i != nSelectedInd )
			{
				if ( !Container[i]->IsIn(ptLT) && !Container[i]->IsIn(ptLB) &&
					!Container[i]->IsIn(ptRT) && !Container[i]->IsIn(ptRB) )
					q++;
			}
		}
		if( q == 9 )
			return ptPosition.x + nWidth;
		else return ptPos.x + nFieldWidth+1;
	}

	int FindPathHalfRight( int nSelectedInd ) const		//unstable
	{
		int nWidth = Container[nSelectedInd]->Width(), 
			nHeight = Container[nSelectedInd]->Height();

		if( nWidth == blockUnitWidth )
			return FindPathRight(nSelectedInd);
		
		CPoint ptPosition = Container[nSelectedInd]->State();
		
		CPoint ptLT( (ptPosition.x + nWidth + 1) + blockUnitWidth / 4, ptPosition.y + blockUnitWidth / 4 ),
			ptLB( (ptPosition.x + nWidth + 1) + blockUnitWidth / 4, ( ptPosition.y + nHeight ) - blockUnitHeight / 4 );

		if( ptLT.x > ptPos.x + nFieldWidth ) return ptPos.x + nFieldWidth + 1; 
		
		int q = 0;
		for(int i = 0; i < BLOCK_QUANTITY; ++i)
		{
			if( i != nSelectedInd )
			{
				if ( !Container[i]->IsIn(ptLT) && !Container[i]->IsIn(ptLB) )
					q++;
			}
		}
		if( q == 9 )
			return ptPosition.x + nWidth/2;
		else return ptPos.x + nFieldWidth+1;
	}

	int FindPathDown( int nSelectedInd ) const		//stable
	{
		CPoint ptPosition = Container[nSelectedInd]->State();
		int nWidth = Container[nSelectedInd]->Width(), 
			nHeight = Container[nSelectedInd]->Height();

		CPoint ptLT( ptPosition.x + blockUnitWidth / 4, (ptPosition.y + nHeight + 1) + blockUnitHeight / 4 ),
			ptLB( ptPosition.x + blockUnitWidth / 4, (ptPosition.y + 2*nHeight + 1) - blockUnitHeight / 4 ),
			ptRT( ( ptPosition.x + nWidth ) - blockUnitWidth / 4 , (ptPosition.y + nHeight + 1) + blockUnitHeight / 4 ),
			ptRB( ( ptPosition.x + nWidth ) - blockUnitWidth / 4, (ptPosition.y + 2*nHeight + 1) - blockUnitHeight / 4 );

		if( ptLB.y > ptPos.y + nFieldHeight ) return ptPos.y + nFieldHeight + 1;

		int q = 0;
		for(int i = 0; i < BLOCK_QUANTITY; ++i)
		{
			if( i != nSelectedInd )
			{
				if ( !Container[i]->IsIn(ptLT) && !Container[i]->IsIn(ptLB) &&
					!Container[i]->IsIn(ptRT) && !Container[i]->IsIn(ptRB) )
					q++;
			}
		}
		if( q == 9 )
			return ptPosition.y + nHeight;
		else return ptPos.y + nFieldHeight + 1;
	}

	int FindPathHalfDown( int nSelectedInd ) const		//unstable
	{
		int nWidth = Container[nSelectedInd]->Width(), 
			nHeight = Container[nSelectedInd]->Height();	
		
		if( nHeight == blockUnitHeight )
			return FindPathDown(nSelectedInd);

		CPoint ptPosition = Container[nSelectedInd]->State();
		
		CPoint ptLT( ptPosition.x + blockUnitWidth / 4, (ptPosition.y + nHeight + 1) + blockUnitHeight / 4 ),
			ptRT( ( ptPosition.x + nWidth ) - blockUnitWidth / 4 , (ptPosition.y + nHeight + 1) + blockUnitHeight / 4 );

		if( ptLT.y > ptPos.y + nFieldHeight ) return ptPos.y + nFieldHeight + 1;

		int q = 0;
		for(int i = 0; i < BLOCK_QUANTITY; ++i)
		{
			if( i != nSelectedInd )
			{
				if ( !Container[i]->IsIn(ptLT) && !Container[i]->IsIn(ptRT) )
					q++;
			}
		}
		if( q == 9 )
			return ptPosition.y + nHeight/2;
		else return ptPos.y + nFieldHeight + 1;
	}

	int FindPathUp( int nSelectedInd ) const		//stable
	{
		CPoint ptPosition = Container[nSelectedInd]->State();
		int nWidth = Container[nSelectedInd]->Width(), 
			nHeight = Container[nSelectedInd]->Height(); 

		CPoint ptLT( ptPosition.x + blockUnitWidth / 4, (ptPosition.y - nHeight - 1) + blockUnitHeight / 4 ),
			ptLB( ptPosition.x + blockUnitWidth / 4, (ptPosition.y - 1) - blockUnitHeight / 4 ),
			ptRT( ( ptPosition.x + nWidth ) - blockUnitWidth / 4, (ptPosition.y - nHeight - 1) + blockUnitHeight / 4 ),
			ptRB( ( ptPosition.x + nWidth ) - blockUnitWidth / 4, (ptPosition.y - 1) - blockUnitHeight / 4 );

		if( ptLT.y < ptPos.y ) return ptPos.y - 1;

		int q = 0;
		for(int i = 0; i < BLOCK_QUANTITY; ++i)
		{
			if( i != nSelectedInd )
			{
				if ( !Container[i]->IsIn(ptLT) && !Container[i]->IsIn(ptLB) &&
					!Container[i]->IsIn(ptRT) && !Container[i]->IsIn(ptRB) )
					q++;
			}
		}
		if( q == 9 )
			return ptPosition.y - nHeight;
		else return ptPos.y - 1;
	}

	int FindPathHalfUp( int nSelectedInd ) const		//unstable
	{
		int nWidth = Container[nSelectedInd]->Width(), 
			nHeight = Container[nSelectedInd]->Height(); 

		if( nHeight == blockUnitHeight )
			return FindPathUp(nSelectedInd);

		CPoint ptPosition = Container[nSelectedInd]->State();

		CPoint ptLB( ptPosition.x + blockUnitWidth / 4, (ptPosition.y - 1) - blockUnitHeight / 4 ),
			ptRB( ( ptPosition.x + nWidth ) - blockUnitWidth / 4, (ptPosition.y - 1) - blockUnitHeight / 4 );

		if( ptLB.y < ptPos.y ) return ptPos.y - 1;

		int q = 0;
		for(int i = 0; i < BLOCK_QUANTITY; ++i)
		{
			if( i != nSelectedInd )
			{
				if ( !Container[i]->IsIn(ptLB) && !Container[i]->IsIn(ptRB) )
					q++;
			}
		}
		if( q == 9 )
			return ptPosition.y - nHeight/2;
		else return ptPos.y - 1;
	}

	void DrawPaths ( CDC* pDC, COLORREF selColor )	const
	{
		int nIndSelected = FindSelected();
		
		if( nIndSelected != -1 )
		{
			if( FindPathHalfLeft( nIndSelected ) > ptPos.x - 1 )
			{
				Container[nIndSelected]->DrawPathHalfLeft( pDC, selColor );
			}
			if( FindPathLeft( nIndSelected ) > ptPos.x - 1 )
			{
				Container[nIndSelected]->DrawPathLeft( pDC, selColor );
			}

			if( FindPathHalfUp( nIndSelected ) > ptPos.y - 1 )
			{
				Container[nIndSelected]->DrawPathHalfUp( pDC, selColor );
			}
			if( FindPathUp( nIndSelected ) > ptPos.y - 1 )
			{
				Container[nIndSelected]->DrawPathUp( pDC, selColor );
			}
			
			if( FindPathHalfRight( nIndSelected ) < ptPos.x + nFieldWidth + 1 )
			{
				Container[nIndSelected]->DrawPathHalfRight( pDC, selColor );
			}
			if( FindPathRight( nIndSelected ) < ptPos.x + nFieldWidth + 1 )
			{
				Container[nIndSelected]->DrawPathRight( pDC, selColor );
			}

			if( FindPathHalfDown( nIndSelected ) < ptPos.y + nFieldHeight + 1 )
			{
				Container[nIndSelected]->DrawPathHalfDown( pDC, selColor );
			}
			if( FindPathDown( nIndSelected ) < ptPos.y + nFieldHeight + 1 )
			{
				Container[nIndSelected]->DrawPathDown( pDC, selColor );
			}

		}
	}
///////////////////////////////////////////////////////////////////////////////////////////////

public:

	void Draw ( CDC* pDC, COLORREF UsualColor, COLORREF SelectedColor, COLORREF TargetColor, COLORREF Background)	const
	{
		CPen* pold = pDC->SelectObject( &CPen(PS_SOLID,2,RGB(0,0,0)) );
		pDC->Rectangle( &CRect(ptPos.x,ptPos.y,ptPos.x + nFieldWidth,ptPos.y + nFieldHeight) );
		pDC->FillRect( &CRect(ptPos.x, ptPos.y, ptPos.x + nFieldWidth - 1, ptPos.y + nFieldHeight - 1), &CBrush(Background) );
		
		for (int i = 0; i < BLOCK_QUANTITY; ++i )
			Container[i]->Draw(pDC, UsualColor, SelectedColor, i+1);

		if (needDrawPaths) DrawPaths(pDC, TargetColor);
		pDC->SelectObject(pold);
	}

	void Select ( const CPoint& pt )
	{
		Select(pt.x, pt.y);
	}

	void Select ( int x, int y )
	{
		for(int i = 0; i < BLOCK_QUANTITY; ++i )
			if ( Container[i]->IsIn(x,y) )
				Container[i]->Select();
		needDrawPaths = true;
	}
	
	MOVE* Move (const CPoint& pt)
	{
		return Move (pt.x, pt.y);
	}

	MOVE* Move ( int x, int y )
	{
		int nNumber = FindSelected();
		int nWidth = Container[nNumber]->Width(), 
			nHeight = Container[nNumber]->Height();

		switch( Container[nNumber]->Side(x,y) )
		{
		case LEFT:
			if( FindPathLeft(nNumber) > ptPos.x - 1 )
			{
				Container[nNumber]->MoveLeft(false);
				Container[nNumber]->UnSelect();
				return new MOVE(nNumber + 1, LEFT);
			}
			break;
		case HALF_LEFT:
			if( FindPathHalfLeft(nNumber) > ptPos.x - 1 )
			{
				Container[nNumber]->MoveLeft(nWidth != blockUnitWidth);
				Container[nNumber]->UnSelect();
				return new MOVE(nNumber + 1, (nWidth != blockUnitWidth) ? HALF_LEFT : LEFT);
			}
			break;

		case UP:
			if( FindPathUp(nNumber) > ptPos.y - 1 )
			{
				Container[nNumber]->MoveUp(false);
				Container[nNumber]->UnSelect();
				return new MOVE(nNumber + 1,UP);
			}
			break;
		case HALF_UP:
			if( FindPathHalfUp(nNumber) > ptPos.y - 1 )
			{
				Container[nNumber]->MoveUp(nHeight != blockUnitHeight);
				Container[nNumber]->UnSelect();
				return new MOVE(nNumber + 1, (nHeight != blockUnitHeight) ? HALF_UP : UP);
			}
			break;

		case RIGHT:
			if( FindPathRight(nNumber) < ptPos.x + nFieldWidth + 1 )
			{
				Container[nNumber]->MoveRight(false);
				Container[nNumber]->UnSelect();
				return new MOVE(nNumber + 1,RIGHT);
			}
			break;
		case HALF_RIGHT:
			if( FindPathHalfRight(nNumber) < ptPos.x + nFieldWidth + 1 )
			{
				Container[nNumber]->MoveRight(nWidth != blockUnitWidth);
				Container[nNumber]->UnSelect();
				return new MOVE(nNumber + 1, (nWidth != blockUnitWidth) ? HALF_RIGHT : RIGHT);
			}
			break;

		case DOWN:
			if( FindPathDown(nNumber) < ptPos.y + nFieldHeight + 1 )
			{
				Container[nNumber]->MoveDown(false);
				Container[nNumber]->UnSelect();
				return new MOVE(nNumber + 1,DOWN);
			}
			break;
		case HALF_DOWN:
			if( FindPathHalfDown(nNumber) < ptPos.y + nFieldHeight + 1 )
			{
				Container[nNumber]->MoveDown(nHeight != blockUnitHeight );
				Container[nNumber]->UnSelect();
				return new MOVE(nNumber + 1, (nHeight != blockUnitHeight ) ? HALF_DOWN : DOWN);
			}
			break;
		}
		return 0;
	}

	MOVE* OnMouseClick (CPoint pt)
	{
		if (FindSelected() == -1)
		{
			Select(pt);
			return 0;
		}

		for (int i = 0; i < BLOCK_QUANTITY; ++i)
		{
			if (Container[i]->IsIn(pt))
			{
				UnSelect();
				Select(pt);
				return 0;
			}
		}

		return Move(pt);
	}

	CBlocksFactoryState FactoryState()
	{
		CBlocksFactoryState cbfs;

		for (int i = 0; i < BLOCK_QUANTITY; ++i)
			cbfs.BlockPositions[i] = ConvertPositionToState(i);

		return cbfs;
	}
};