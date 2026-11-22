#include"Jogo.h"
#include <cstdlib>
#include <ctime>

int main() {
	srand(time(0));
	Jogo jogo;
	jogo.executar();
	return 0;
}
