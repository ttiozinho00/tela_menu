/*
*
* metodo de compilar o codigo: gcc -o tela tela.c -Wall -pedantic -Wextra -Werror -std=c99
*/

#include <stdio.h>   /* printf(), getchar(), putchar() */
#include <stdlib.h>  /* system(), exit() */
#include <conio.h>   /* getch() */
#include <windows.h> /* GetStdHandle(), GetConsoleWindow(), GetWindowRect(), AdjustWindowRectEx(), SetWindowPos(), COORD() */
#include <string.h>  /* strlen() */

/**
 * DefiniÃ§Ã£o das cores e constantes
 */
#define COR_FUNDO_MENU_PRINCIPAL 0
#define COR_LETRA_MENU_PRINCIPAL 7
#define COR_FUNDO_SELECIONADO_MENU_PRINCIPAL 2
#define COR_LETRA_SELECIONADO_MENU_PRINCIPAL 15
#define COR_FUNDO_SUBMENU 7
#define COR_LETRA_SUBMENU 7
#define COR_FUNDO_SELECIONADO_SUBMENU 2
#define COR_LETRA_SELECIONADO_SUBMENU 15
#define COR_BORDA_JANELA_PRINCIPAL 157
#define COR_FUNDO_BORDA_JANELA_PRINCIPAL 161
#define COR_FUNDO_JANELA_PRINCIPAL 131

#define ALTURA_JANELA 25
#define LARGURA_JANELA 80

/**
 * variaveis para controlar a navegação no menu
 */
int opcaoMenuPrincipalSelecionada = 1;
int opcaoSubMenuSelecionada = 0;

/**
 * protótipo das funções
 */
void definirCorTexto(int cor);
void limparTela();
void definirTamanhoPosicaoJanelaPrincipal();
void definirCoresJanelaPrincipal();
void exibirBarraMenuPrincipal();
void exibirOpcaoMenuPrincipal(char *texto, int opcao, int selecionado);
void exibirMenuPrincipal();
void exibirSubMenu();
void navegarSubMenu();
void executarOpcao1();
void executarOpcao2();
void executarOpcao3();
void navegarMenuPrincipal();
void exibirMenu();

/**
 * função para definir as cores do texto
 * @param cor CÃ³digo da cor
 */
void definirCorTexto(int cor) 
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, cor);
}

/**
 * função para limpar a tela
 */
void limparTela() 
{
    system("cls");
}

/**
 * função para definir o tamanho e posiÃ§Ã£o da janela principal
 */
void definirTamanhoPosicaoJanelaPrincipal() 
{
    HWND hWnd = GetConsoleWindow();
    RECT rect;

    GetWindowRect(hWnd, &rect);
    rect.left = 50;
    rect.top = 50;
    rect.right = rect.left + LARGURA_JANELA * 12;
    rect.bottom = rect.top + ALTURA_JANELA * 2;

    AdjustWindowRectEx(&rect, WS_EX_CLIENTEDGE, 0, WS_EX_TOOLWINDOW);

    SetWindowPos(hWnd, HWND_TOP, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, SWP_SHOWWINDOW);
}

/**
 * função para definir as cores da janela principal
 */
void definirCoresJanelaPrincipal() 
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int i;

    /* Definir cor da borda */
    SetConsoleTextAttribute(hConsole, COR_BORDA_JANELA_PRINCIPAL);
    printf("********************************************************************\n");
    SetConsoleTextAttribute(hConsole, COR_FUNDO_BORDA_JANELA_PRINCIPAL);

    /* Definir cor do fundo */
    for (i = 1; i < ALTURA_JANELA - 1; i++)
    {
        printf("*                                                                  *\n");
    }

    /* Definir cor da borda inferior */
    SetConsoleTextAttribute(hConsole, COR_BORDA_JANELA_PRINCIPAL);
    printf("********************************************************************\n");
}

/**
 * função para exibir a barra do menu principal
 */
void exibirBarraMenuPrincipal() 
{
    definirCorTexto(COR_FUNDO_MENU_PRINCIPAL | (COR_LETRA_MENU_PRINCIPAL << 4));
    printf("********************************************************************\n");
    definirCorTexto(COR_LETRA_MENU_PRINCIPAL | (COR_FUNDO_MENU_PRINCIPAL << 4));
    printf("*                                                                  *\n");
    definirCorTexto(COR_FUNDO_MENU_PRINCIPAL | (COR_LETRA_MENU_PRINCIPAL << 4));
    printf("********************************************************************\n");
}

/**
 * função para exibir a opção do menu principal
 * @param texto Texto da opção do menu
 * @param opcao numero da opção
 * @param selecionado Indica se a opção está selecionada
 */
void exibirOpcaoMenuPrincipal(char *texto, int opcao, int selecionado) 
{
    definirCorTexto(selecionado ? COR_FUNDO_SELECIONADO_MENU_PRINCIPAL | (COR_LETRA_SELECIONADO_MENU_PRINCIPAL << 4) : COR_FUNDO_MENU_PRINCIPAL | (COR_LETRA_MENU_PRINCIPAL << 4));
    printf("* ");

    if (opcao < 10) 
    {
        printf("0");
    }

    printf("%d - %s", opcao, texto);

    if (selecionado) 
    {
        printf(" (**)");
    } 

    else 
    {
        printf("   ");
    }

    printf("                                                    *\n");
}

/**
 * função para exibir o menu principal
 */
void exibirMenuPrincipal() 
{
    limparTela();
    definirCoresJanelaPrincipal();
    exibirBarraMenuPrincipal();

    /* Exibir opções do menu principal */
    exibirOpcaoMenuPrincipal("Opcao 1", 1, opcaoMenuPrincipalSelecionada == 1);
    exibirOpcaoMenuPrincipal("Opcao 2", 2, opcaoMenuPrincipalSelecionada == 2);
    exibirOpcaoMenuPrincipal("Opcao 3", 3, opcaoMenuPrincipalSelecionada == 3);
    exibirOpcaoMenuPrincipal("Sair", 4, opcaoMenuPrincipalSelecionada == 4);

    /* Exibir rodapé do menu principal */
    definirCorTexto(COR_FUNDO_MENU_PRINCIPAL | (COR_LETRA_MENU_PRINCIPAL << 4));
    printf("********************************************************************\n");
}

/**
 * função para exibir o submenu
 */
void exibirSubMenu() 
{
    limparTela();
    definirCoresJanelaPrincipal();
    exibirBarraMenuPrincipal();

    /* Exibir opções do submenu */
    exibirOpcaoMenuPrincipal("SubOpcao 1", 1, opcaoSubMenuSelecionada == 1);
    exibirOpcaoMenuPrincipal("SubOpcao 2", 2, opcaoSubMenuSelecionada == 2);
    exibirOpcaoMenuPrincipal("Voltar", 3, opcaoSubMenuSelecionada == 3);

    /* Exibir rodapé do submenu */
    definirCorTexto(COR_FUNDO_MENU_PRINCIPAL | (COR_LETRA_MENU_PRINCIPAL << 4));
    printf("********************************************************************\n");
}

/**
 * função para navegar no submenu
 */
void navegarSubMenu() 
{
    int tecla;
    while (1) 
    {
        tecla = getch();
        if (tecla == 224) {  /* Detecta as setas */
            switch (getch()) 
            {
                case 72:  /* Seta para cima */
                    if (opcaoSubMenuSelecionada > 1) 
                    {
                        opcaoSubMenuSelecionada--;
                    }
                    break;
                case 80:  /* Seta para baixo */
                    if (opcaoSubMenuSelecionada < 3) 
                    {
                        opcaoSubMenuSelecionada++;
                    }
                    break;
            }
        } 

        else if (tecla == 13) 
        {  /* Enter */
            if (opcaoSubMenuSelecionada == 3) 
            {
                exibirMenuPrincipal();
                navegarMenuPrincipal();
            }
            break;
        }
        exibirSubMenu();
    }
}

/**
 * função para executar a opção 1
 */
void executarOpcao1() 
{
    printf("Executando Opcao 1...\n");
    system("pause");
}

/**
 * função para executar a opção 2
 */
void executarOpcao2() 
{
    exibirSubMenu();
    navegarSubMenu();
}

/**
 * função para executar a opção 3
 */
void executarOpcao3() 
{
    printf("Executando Opcao 3...\n");
    system("pause");
}

/**
 * função para navegar no menu principal
 */
void navegarMenuPrincipal() 
{
    int tecla;
    while (1) 
    {
        tecla = getch();
        if (tecla == 224) {  /* Detecta as setas */
            switch (getch()) 
            {
                case 72:  /* Seta para cima */
                    if (opcaoMenuPrincipalSelecionada > 1) 
                    {
                        opcaoMenuPrincipalSelecionada--;
                    }
                    break;
                case 80:  /* Seta para baixo */
                    if (opcaoMenuPrincipalSelecionada < 4) 
                    {
                        opcaoMenuPrincipalSelecionada++;
                    }
                    break;
            }
        } 

        else if (tecla == 13) 
        {  /* Enter */
            switch (opcaoMenuPrincipalSelecionada) 
            {
                case 1:
                    executarOpcao1();
                    break;
                case 2:
                    executarOpcao2();
                    break;
                case 3:
                    executarOpcao3();
                    break;
                case 4:
                    exit(0);
                    break;
            }
            exibirMenuPrincipal();
        }

        else if (tecla == 'M' || tecla == 'm')  /* Tecla 'M' para exibir o menu de opções */
        {
            exibirMenu();
        }

        exibirMenuPrincipal();
    }
}

/**
 * função para exibir o menu de opções
 */
void exibirMenu()
{
    limparTela();
    definirCoresJanelaPrincipal();
    exibirBarraMenuPrincipal();

    definirCorTexto(COR_LETRA_MENU_PRINCIPAL | (COR_FUNDO_MENU_PRINCIPAL << 4));
    printf("* Menu de opções                                                    *\n");

    definirCorTexto(COR_FUNDO_MENU_PRINCIPAL | (COR_LETRA_MENU_PRINCIPAL << 4));
    printf("********************************************************************\n");

    printf("\n");
    printf("  Use as setas para navegar e 'Enter' para selecionar uma opcao.\n");
    printf("\n");

    printf("  1. Executar Opcao 1\n");
    printf("  2. Executar Opcao 2\n");
    printf("  3. Executar Opcao 3\n");
    printf("  4. Voltar para o Menu Principal\n");

    printf("\n");
    printf("********************************************************************\n");

    int escolha;
    while (1)
    {
        escolha = getch();
        if (escolha == 13) /* Enter */
        {
            limparTela();
            switch (opcaoMenuPrincipalSelecionada) 
            {
                case 1:
                    executarOpcao1();
                    break;
                case 2:
                    executarOpcao2();
                    break;
                case 3:
                    executarOpcao3();
                    break;
                case 4:
                    exibirMenuPrincipal();
                    break;
            }
            break;
        }
    }
}

/**
 * função principal
 */
int main(int argc, char const *argv[])
{
    argv = argv;
    argc = argc;
    
    definirTamanhoPosicaoJanelaPrincipal();
    definirCoresJanelaPrincipal();
    exibirMenuPrincipal();
    navegarMenuPrincipal();
    return 0;
}
