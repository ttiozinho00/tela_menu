#ifndef _CONSOLE
#define _CONSOLE

#include <windows.h>
/* -> Estrutura COORD:
      typedef struct _COORD{
              SHORT X;   -> inteiro curto
              SHORT Y;   -> inteiro curto
              } COORD;
   -> Tipos WORD, DWORD e LPSTR
*/

/****************************************************************************************************************/
/*                                  INÍCIO DAS DECLARAÇÕES DE DEFINES E CONSTANTES                              */
/****************************************************************************************************************/


/* key_codes */
	#define F1 112
	#define F2 113
	#define F3 114
	#define F4 115
	#define F5 116
	#define F6 117
	#define F7 118
	#define F8 119
	#define F9 120
	#define F10 121
	#define F11 122
	#define F12 123

	#define ESC 27
	#define ENTER 13
	#define BACKSPACE 8
	#define ESPACO 32
	#define TAB 9

	/* Enhanced keys */
		#define INSERT 45
		#define DEL 46
		#define PAGE_UP 33
		#define PAGE_DOWN 34
		#define END 35
		#define HOME 36
		#define SETA_PARA_ESQUERDA 37
		#define SETA_PARA_CIMA 38
		#define SETA_PARA_DIREITA 39
		#define SETA_PARA_BAIXO 40

	/* Teclas de status */
		#define SHIFT_ESQUERDO_PRESSIONADO 0x0200  /* (constante definida por mim = 0x200 = shift esquerdo pressionado) + (0x010 = shift pressionado) = 0x210. Valor definido com base em uma extensão dos valores contidos na tabela: http://msdn.microsoft.com/pt-br/library/windows/desktop/ms684166%28v=vs.85%29.aspx */
		#define SHIFT_DIREITO_PRESSIONADO 0x0400  /* (constante definida por mim = 0x400 = shift direito pressionado) + (0x010 = shift pressionado) = 0x410. Valor definido com base em uma extensão dos valores contidos na tabela: http://msdn.microsoft.com/pt-br/library/windows/desktop/ms684166%28v=vs.85%29.aspx */

/*--------------------*/


/* constantes definidas para identificar a liberação de um determinado botão do mouse */
#define FROM_LEFT_1ST_BUTTON_RELEASED FROM_LEFT_1ST_BUTTON_PRESSED
#define FROM_LEFT_2ND_BUTTON_RELEASED FROM_LEFT_2ND_BUTTON_PRESSED
#define FROM_LEFT_3RD_BUTTON_RELEASED FROM_LEFT_3RD_BUTTON_PRESSED
#define FROM_LEFT_4TH_BUTTON_RELEASED FROM_LEFT_4TH_BUTTON_PRESSED
#define RIGHTMOST_BUTTON_RELEASED RIGHTMOST_BUTTON_PRESSED

/* dar a opção ao programador de usar constantes em português, caso queira */
#define BOTAO_ESQUERDO_PRESSIONADO FROM_LEFT_1ST_BUTTON_PRESSED
#define BOTAO_ESQUERDO_LIBERADO FROM_LEFT_1ST_BUTTON_RELEASED
#define BOTAO_DIREITO_PRESSIONADO RIGHTMOST_BUTTON_RELEASED
#define BOTAO_DIREITO_LIBERADO RIGHTMOST_BUTTON_RELEASED

/* constantes utilizadas pela função IdentificarEvento() para definir o nivel
   de detalhamento das informações a serem coletadas de um evento */
#define MINIMO 1
#define MAXIMO 2

#define BIT_SHORT_MAIS_SIGNIFICATIVO 0x80  /* (0x80) na base hexadecimal = (128) na base 10 = (1000 0000) na base 2 */
#define TECLA_PRESSIONADA 0x80
/****************************************************************************************************************/
/*                                  FIM DAS DECLARAÇÕES DE DEFINES E CONSTANTES                              */
/****************************************************************************************************************/




/****************************************************************************************************************/
/*                                   DECLARAÇÕES DE ESTRUTURAS E ENUMERAÇÕES                                    */
/****************************************************************************************************************/

 /* estrutura para o armazenamento das cores da janela de console */
    typedef struct{
                  int CorTexto;      /* cor do texto da janela de prompt atual */
		          int CorFundo;      /* cor de fundo da janela de prompt atual */
                  }CORES;


 /* tipo STATUS contendo os valores para ligar e desligar o cursor do mouse da tela */
    typedef enum{DESLIGAR, LIGAR} STATUS;


 /* tipo VISIBILIDADE */
    typedef enum{INVISIVEL, VISIVEL} VISIBILIDADE;


 /* tipo que permite identificar que tipo de evento deve ser verificada a existência no buffer de eventos */
    typedef enum{KEYBOARD_HIT, MOUSE_HIT, ALL} TYPE_HIT;


 /* Detalhes desta estrutura, ver link:
    http://msdn.microsoft.com/en-us/library/windows/desktop/ms684166%28v=vs.85%29.aspx */
    enum T_STATUS_TECLA{LIBERADA, PRESSIONADA};
    typedef struct T_TECLADO{
                            enum T_STATUS_TECLA status_tecla; /* LIBERADA ou PRESSIONADA */
		 				    WORD key_code; /* código numérico que identifica uma tecla independente do tipo do teclado */
							WORD scan_code; /* código numérico que identifica uma tecla de acordo com o valor gerado pelo hardware de teclado (é dependente do tipo do teclado) */
							CHAR ascii_code; /* tradução do valor key_code para o caracter correspondente, considerando o estado do teclado (shift, caps-lock, etc., pressionadas). Faz a tradução considerando a linguagem atual e o layout do teclado físico */
							WORD repeat_count; /* Número que indica que uma tecla está sendo segurada pressionada */
                            DWORD status_teclas_controle; /* CAPSLOCK_ON, ENHANCED_KEY (insert, delete, home, end, pg up, pg downl,
						                                   setas de direção, etc), LEFT_ALT_PRESSED, LEFT_CTRL_PRESSED,
						                                   NUMLOCK_ON, RIGHT_ALT_PRESSED, RIGHT_CTRL_PRESSED, SCROLLLOCK_ON,
								 						   SHIFT_PRESSED */
                            } TECLADO;

 /* Detalhes desta estrutura, ver link:
    http://msdn.microsoft.com/en-us/library/windows/desktop/ms684239%28v=vs.85%29.aspx */
    typedef struct T_MOUSE{
                          DWORD botao_pressionado; /* FROM_LEFT_1ST_BUTTON_PRESSED, FROM_LEFT_2ND_BUTTON_PRESSED, FROM_LEFT_3RD_BUTTON_PRESSED,
                                                      FROM_LEFT_4TH_BUTTON_PRESSED, RIGHTMOST_BUTTON_PRESSED */
		 				  DWORD botao_clicou;      /* se o botão tiver sido liberado, após ter sido pressionado */
                          COORD posicao; /* coordenadas (em forma de células de caracteres e não de pixels) do cursor do
						                    mouse em termos do tamanho (em linhas e colunas) do buffer
							 			    de console que estiver definido para a janela */
                          DWORD status_teclas_controle; /* CAPSLOCK_ON, ENHANCED_KEY (insert, delete, home, end, pg up, pg downl,
						                                   setas de direção, etc), LEFT_ALT_PRESSED, LEFT_CTRL_PRESSED,
						                                   NUMLOCK_ON, RIGHT_ALT_PRESSED, RIGHT_CTRL_PRESSED, SCROLLLOCK_ON,
							 							   SHIFT_PRESSED */
						  DWORD flags_qual_evento_mouse; /* DOUBLE_CLICK, MOUSE_HWHEELED, MOUSE_MOVED, MOUSE_WHEELED */
                          } MOUSE;

 /* Evento que pode ter acontecido e que é identificado pela função Evento() */
    typedef struct T_EVENTO{
                           WORD tipo_evento; /* pode ser MOUSE_EVENT ou KEY_EVENT */
		  				   TECLADO teclado; /* caso tenha ocorrido um KEY_EVENT, então esta estrutura será prenchida
						                    com os dados correspondentes */
						   MOUSE mouse;    /* caso tenha ocorrido um MOUSE_EVENT, então esta estrutura será prenchida
						                    com os dados correspondentes */
                           }EVENTO;


 void ErrorExit (LPSTR);
 EVENTO Evento(void);


 CORES getCoresJanela(void);


 COORD getPosicaoJanela(void);
 


 COORD getResolucaoMonitor(void);



 COORD getTamanhoFonteConsole(void);

 char *getTituloConsole(void);


 int hit(TYPE_HIT);


 void IdentificarEvento(EVENTO, int);

 COORD MaxDimensaoJanela(void);


 void setCursorStatus(STATUS);


 void setDimensaoJanela(int largura, int altura);


 void setEstadoBarraTarefas(VISIBILIDADE);


 void setPosicaoJanela(int top, int left);

 void setTituloConsole(char *);


 COORD tamanhoJanelaConsole(void);


#endif
