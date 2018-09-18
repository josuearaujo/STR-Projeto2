#include <signal.h> 
#include <unistd.h>
#include <stdlib.h> // system()
#include <iostream>
#include <string>
#include <sys/resource.h>
#include <sched.h>

using namespace std;


int main(){
	int opcao;
	int prioridade;
	bool temFiltro;
	pid_t processo;
	string filtro;
	string comando;
	cpu_set_t mask;
	int cpu;


	while(true){
		cout << "Escolha a opcao desejada:" << endl;
		cout << "MENU:" << endl;
		cout << "(0) Limpar a tela;" << endl;
		cout << "(1) Ver/atualizar lista de processos;" << endl;
		cout << "(2) Filtrar;" << endl;
		cout << "(3) Retirar filtro;" << endl;
		cout << "(4) Pausar processo;" << endl;
		cout << "(5) Continuar processo;" << endl;
		cout << "(6) Alarmar processo;" << endl;
		cout << "(7) Matar processo;" << endl;
		cout << "(8) Alterar prioridade;" << endl;
		cout << "(9) Escolher CPU;" << endl;
		cout << "Escolher uma opcao invalida encerra o programa." << endl;

		cin >> opcao;

		switch(opcao){
			case 0:
				system("clear");
				break;
			case 1:
				if(temFiltro == false){
					system("ps -e -o pid,pri,psr,cmd");
				}
				else{
					comando = "ps -e -o pid,pri,psr,cmd | grep " + filtro;
					system(comando.c_str());
				}
				break;
			case 2:
				temFiltro = true;
				cout << "Digite o filtro: " << endl;
				cin >> filtro;
				break;
			case 3:
				temFiltro = false;
				break;
			case 4:
				cout << "Digite o pid do processo a ser pausado: " << endl;
				cin >> processo;
				kill(processo, SIGSTOP);
				break;
			case 5:
				cout << "Digite o pid do processo a ser continuado: " << endl;
				cin >> processo;
				kill(processo, SIGCONT);
				break;
			case 6:
				cout << "Digite o pid do processo a ser alarmado: " << endl;
				cin >> processo;
				kill(processo, SIGALRM);
				break;
			case 7:
				cout << "Digite o pid do processo a ser encerrado: " << endl;
				cin >> processo;
				kill(processo, SIGKILL);
				break;
			case 8:
				cout << "Digite o pid do processo cuja prioridade será encerrada: " << endl;
				cin >> processo;
				cout << "Insira a nova prioridade do processo:" << endl;
				cin >> prioridade;
				setpriority(PRIO_PROCESS, processo, prioridade);
				break;
			case 9:
				cout << "Digite o pid do processo cuja cpu sera alterada: " << endl;
				cin >> processo;
				cout << "Em qual CPU esse processo deve ser executado?" << endl;
				cin >> cpu;
				CPU_ZERO(&mask);
				CPU_SET(cpu, &mask);
				sched_setaffinity(processo, sizeof(mask), &mask);
				break;
			default:
				cout << "Adeus!" << endl;
				exit(0);
				break;
		}
		cout << endl << endl;
	}
}