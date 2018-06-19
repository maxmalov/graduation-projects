#include <windows.h>
#include <stdio.h>

int main()
{
	HANDLE hConOut, hConIn;
	INPUT_RECORD ir;

	hConOut = GetStdHandle( STD_OUTPUT_HANDLE );
	hConIn = GetStdHandle( STD_INPUT_HANDLE );

	DWORD dwInputEvents = 0;
	bool fEsc = false;

	COORD cPos = {1,1};
	SetConsoleCursorPosition(hConOut, cPos);
	SetConsoleMode(hConIn,ENABLE_MOUSE_INPUT);
	while( !fEsc )
	{
		ReadConsoleInput( hConIn, &ir, 1, &dwInputEvents);
		if( ir.EventType == KEY_EVENT)
		{
			if(ir.Event.KeyEvent.bKeyDown)
			{	
				switch(ir.Event.KeyEvent.wVirtualKeyCode)
				{
				case VK_LEFT:
					{
						SetConsoleTextAttribute( hConOut, FOREGROUND_BLUE | FOREGROUND_INTENSITY );
						cPos.X = max( 1, cPos.X--);
						printf("l");
						break;
					}
				case VK_RIGHT:
					{
						SetConsoleTextAttribute( hConOut, FOREGROUND_RED | FOREGROUND_INTENSITY);
						cPos.X = min( 78, cPos.X + 1);
						printf("r");
						break;
					}
				case VK_UP:
					{
						SetConsoleTextAttribute( hConOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
						cPos.Y = max ( 1, cPos.Y--);
						printf("u");
						break;
					}
				case VK_DOWN:
					{
						SetConsoleTextAttribute( hConOut, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
						cPos.Y = min ( 298, cPos.Y++);
						printf("d");
						break;
					}
				case VK_ESCAPE:
					fEsc = true;
					break;
				}
				SetConsoleCursorPosition(hConOut, cPos);
			}
		}
		if(ir.EventType == MOUSE_EVENT)
		{
			if(ir.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED )
			{
				DWORD dw;
				SetConsoleCursorPosition(hConOut, ir.Event.MouseEvent.dwMousePosition);
				//WriteConsole(hConOut,"*",1,&dw,NULL);
				printf("*");
			}
		}
	}
 
}