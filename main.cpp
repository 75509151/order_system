#include "main.h"
#include "CUsr_Form.h"
int main()
{
	initscr();
	refresh();
	if (has_colors()==false)
	{
		printf("��֧����ɫ");
		endwin();
	//	exit(1);
	}
	start_color();
	init_pair(1,COLOR_RED,COLOR_WHITE);
	init_pair(2,COLOR_WHITE,COLOR_BLUE);
	init_pair(3,COLOR_RED,COLOR_GREEN);
	init_pair(4,COLOR_WHITE,COLOR_WHITE);
	wbkgd(stdscr,COLOR_PAIR(4));
	refresh();
	CLoginForm *pCLogin=new CLoginForm(NULL);
	//CUsr_Form *pCLogin=new CUsr_Form(NULL);
//	attron(COLOR_PAIR(2));
	noecho();
	cbreak();//�ر��л���
	pCLogin->Show();
	pCLogin->KeyListener();

	refresh();

	endwin();
	return 0;
}
