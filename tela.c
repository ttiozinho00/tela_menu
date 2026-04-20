#include <stdio.h>
#include <stdlib.h>
#include "conio_v3.2.4.h"
#include "console_v1.5.5.h"

/**
 * Definições de Estilo e Layout
 */
#define LARGURA_JANELA 80
#define ALTURA_JANELA  25

// Cores baseadas no enum COLORS de conio_v3.2.4.h
#define COR_BORDA          LIGHTBLUE
#define COR_TEXTO_NORMAL   LIGHTGRAY
#define COR_TEXTO_DESTAQUE YELLOW
#define COR_SELECAO_FUNDO  GREEN
#define COR_SELECAO_TEXTO  WHITE

int opcaoMenuPrincipal = 1;
int opcaoSubMenu = 1;

/* Protótipos das funções */
void inicializarSistema(void);
void desenharInterfaceBase(const char* titulo);
void exibirMenuPrincipal(void);
void exibirSubMenu(void);
void navegarMenuPrincipal(void);
void navegarSubMenu(void);

/**
 * Configura o ambiente inicial usando console_v1.5.5
 */
void inicializarSistema(void) {
    setTituloConsole("Sistema de Gestao v1.0");
    setDimensaoJanela(LARGURA_JANELA, ALTURA_JANELA);
    setCursorStatus(DESLIGAR);
    textmode(C80);
}

/**
 * Desenha a moldura e fundo usando conio_v3.2.4
 */
void desenharInterfaceBase(const char* titulo) {
    int i;
    textbackground(BLACK);
    textcolor(COR_BORDA);
    clrscr();

    // Borda Superior e Inferior
    for (i = 1; i <= LARGURA_JANELA; i++) {
        gotoxy(i, 1); putch('*');
        gotoxy(i, ALTURA_JANELA); putch('*');
    }

    // Bordas Laterais
    for (i = 2; i < ALTURA_JANELA; i++) {
        gotoxy(1, i); putch('*');
        gotoxy(LARGURA_JANELA, i); putch('*');
    }

    // Título Centralizado
    textcolor(COR_TEXTO_DESTAQUE);
    gotoxy((LARGURA_JANELA / 2) - (10), 2);
    cputs(titulo);
}

/**
 * Exibe uma opção formatada com detecção de seleção
 */
void renderizarItem(int linha, int id, const char* rotulo, int selecionado) {
    gotoxy(10, linha);
    if (selecionado) {
        textbackground(COR_SELECAO_FUNDO);
        textcolor(COR_SELECAO_TEXTO);
    } else {
        textbackground(BLACK);
        textcolor(COR_TEXTO_NORMAL);
    }
    cprintf(" %02d. %-20s ", id, rotulo);
    textbackground(BLACK);
}

void exibirMenuPrincipal(void) {
    desenharInterfaceBase("MENU PRINCIPAL");
    renderizarItem(6, 1, "Cadastros", opcaoMenuPrincipal == 1);
    renderizarItem(7, 2, "Relatorios (SubMenu)", opcaoMenuPrincipal == 2);
    renderizarItem(8, 3, "Configuracoes", opcaoMenuPrincipal == 3);
    renderizarItem(9, 4, "Sair", opcaoMenuPrincipal == 4);
    
    textcolor(DARKGRAY);
    gotoxy(5, 22);
    cputs("Setas: Navegar | Enter: Confirmar");
}

void exibirSubMenu(void) {
    desenharInterfaceBase("RELATORIOS");
    renderizarItem(6, 1, "Vendas Mensais", opcaoSubMenu == 1);
    renderizarItem(7, 2, "Estoque Atual", opcaoSubMenu == 2);
    renderizarItem(8, 3, "Voltar", opcaoSubMenu == 3);
}

void navegarSubMenu(void) {
    int tecla;
    while (1) {
        exibirSubMenu();
        tecla = getch();

        if (tecla == 0 || tecla == 224) { // Teclas especiais
            tecla = getch();
            if (tecla == 72 && opcaoSubMenu > 1) opcaoSubMenu--; // Cima
            if (tecla == 80 && opcaoSubMenu < 3) opcaoSubMenu++; // Baixo
        } else if (tecla == 13) { // Enter
            if (opcaoSubMenu == 3) return;
            gotoxy(10, 12);
            cprintf("Gerando Relatorio %d...", opcaoSubMenu);
            getch();
        }
    }
}

void navegarMenuPrincipal(void) {
    int tecla;
    while (1) {
        exibirMenuPrincipal();
        tecla = getch();

        if (tecla == 0 || tecla == 224) {
            tecla = getch();
            if (tecla == 72 && opcaoMenuPrincipal > 1) opcaoMenuPrincipal--;
            if (tecla == 80 && opcaoMenuPrincipal < 4) opcaoMenuPrincipal++;
        } else if (tecla == 13) {
            switch (opcaoMenuPrincipal) {
                case 1: gotoxy(10, 15); cputs("Modulo de Cadastro..."); getch(); break;
                case 2: navegarSubMenu(); break;
                case 3: gotoxy(10, 15); cputs("Abrindo Configuracoes..."); getch(); break;
                case 4: clrscr(); exit(0);
            }
        }
    }
}

int main(void) {
    inicializarSistema();
    navegarMenuPrincipal();
    return 0;
}
