#include"Jogo.h"
#include <cstdlib>
#include <ctime>

int main() {
	srand(time(NULL));
	Jogo jogo;
	jogo.executar();
	return 0;
}
