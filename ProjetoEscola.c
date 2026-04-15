//Danilo Rosário dos Santos
#include <stdio.h>
#include <string.h>
#define LimiteDisciplina 10
#define LimiteAlunos 100
#define LimiteProfessores 100
#define LimiteDisciplinas 100
//estruturas de dados, como classes
struct Data {
    int dia;
    int mes;
    int ano;
};
struct Pessoa {
    char nome[100];
    char cpf[12];
    char sexo;
    int matricula;
    struct Data data;
};
struct Aluno {
    struct Pessoa pessoa;
    int qtdDisciplinas;
    char codDisciplinas[LimiteDisciplina][20];
};
struct Disciplina{
  char nome[10];
  char codigo [20];
  int matriculaProf;
  int qtdAlunos;
  int semestre;
  
};
struct Professor {
    struct Pessoa pessoa;
};
//variaveis de contagem das listas
int i = 0; // indice dos alunos
int tamProfessor = 0;// indice e contador de professores
int tamDisciplinas = 0;//indice e contador de disciplinas
//listas para guardar os dados do tipo das estruturas
struct Aluno alunos[LimiteAlunos];
struct Professor professores[LimiteProfessores];
struct Disciplina disciplinas[LimiteDisciplinas];
int cpfExiste(char cpf[]){
    for(int j = 0; j < i; j++){
        if(strcmp(alunos[j].pessoa.cpf, cpf) == 0){
            return 1;
        }
    }
    for(int j = 0; j < tamProfessor; j++){
        if(strcmp(professores[j].pessoa.cpf, cpf) == 0){
            return 1;
        }
    }

    return 0;
}
void imprimirProfessores(){
    if(tamProfessor == 0){
        printf("\nNenhum professor cadastrado\n");
        return;
    }

    for(int j = 0; j < tamProfessor; j++){
        printf("\n--- professor %d ---\n", j+1);
        printf("Matricula: %d\n", professores[j].pessoa.matricula);
        printf("CPF: %s\n", professores[j].pessoa.cpf);
        printf("Nome: %s\n", professores[j].pessoa.nome);
        printf("Sexo: %c\n", professores[j].pessoa.sexo);
        printf("Nascimento: %02d/%02d/%d\n",
            professores[j].pessoa.data.dia,
            professores[j].pessoa.data.mes,
            professores[j].pessoa.data.ano
        );
    }
}
int buscarprofessorMatricula(int matricula){
    for(int j = 0; j < tamProfessor; j++){
        if(professores[j].pessoa.matricula == matricula){
            return j;
        }
    }
    return -1;
}
int compararData(struct Data a, struct Data b){
    if(a.ano != b.ano) return a.ano - b.ano;
    if(a.mes != b.mes) return a.mes - b.mes;
    return a.dia - b.dia;
}
void limparEnter(char *str){
    str[strcspn(str, "\n")] = '\0';
}
int validarCPF(char cpf[]){
    if(strlen(cpf) != 11){
        return 0;
    }

    // opcional: só números
    for(int i = 0; cpf[i] != '\0'; i++){
        if(cpf[i] < '0' || cpf[i] > '9'){
            return 0;
        }
    }

    // verifica duplicidade
    if(cpfExiste(cpf)){
        return 0;
    }

    return 1;
}
int validarData(int d, int m, int a){
    if(d < 1 || d > 31) return 0;
    if(m < 1 || m > 12) return 0;
    if(a < 1900 || a > 2100) return 0;
    return 1;
}
int matriculaAlunoExiste(int mat){
    for(int j=0;j<i;j++){
        if(alunos[j].pessoa.matricula == mat) return 1;
    }
    return 0;
}
int matriculaProfessorExiste(int mat){
    for(int j=0;j<tamProfessor;j++){
        if(professores[j].pessoa.matricula == mat) return 1;
    }
    return 0;
}
void removerAlunoDeTodasDisciplinas(int posAluno){
    for(int d = 0; d < tamDisciplinas; d++){
        for(int a = 0; a < alunos[posAluno].qtdDisciplinas; a++){
            if(strcmp(disciplinas[d].codigo, alunos[posAluno].codDisciplinas[a]) == 0){
                disciplinas[d].qtdAlunos--;
            }
        }
    }
}
int BuscarDisciplinaCod(char codigo[]){
    for(int i = 0; i<tamDisciplinas; i++){
        if(strcmp(disciplinas[i].codigo, codigo) == 0){
            return i;
        }
    }
    return -1;

}
//crud e funçõa dos professores 
void TrocaString(char recebida[], char Normal[]){
    int j = 0;
    while(recebida[j] != '\0'){
        Normal[j] = recebida[j];
        j++;
    }
    
    Normal[j] = '\0';
}
void ordenarProfessoresPorNome() {
    struct Professor temp;

    for(int j = 0; j < tamProfessor - 1; j++){
        for(int k = j + 1; k < tamProfessor; k++){
            if(strcmp(professores[j].pessoa.nome, professores[k].pessoa.nome) > 0){
                temp = professores[j];
                professores[j] = professores[k];
                professores[k] = temp;
            }
        }
    }

    printf("\n--- PROFESSORES POR NOME ---\n");
    imprimirProfessores();
}
void ordenarProfessoresPorData() {
    struct Professor temp;

    for(int j = 0; j < tamProfessor - 1; j++){
        for(int k = j + 1; k < tamProfessor; k++){
            if(compararData(professores[j].pessoa.data, professores[k].pessoa.data) > 0){
                temp = professores[j];
                professores[j] = professores[k];
                professores[k] = temp;
            }
        }
    }

    printf("\n--- PROFESSORES POR DATA ---\n");
    imprimirProfessores();
}
void cadastrarProfessor(){
    if(tamProfessor >= LimiteProfessores){
        printf("Limite de professores atingido\n");
        return;
    }

    int matricula;
    char cpf[12];
    char nome[100];
    char sexo;
    int d, m, a;
    printf("Matricula: ");
    scanf("%d", &matricula);
    if(matriculaProfessorExiste(matricula)){
        printf("Matricula ja existe!\n");
        return;
    }
    printf("CPF: ");
    scanf("%s", cpf);
    if(!validarCPF(cpf)){
        printf("CPF invalido!\n");
        return;
    }
    printf("Nome: ");
    scanf(" %[^\n]", nome);
    printf("Sexo: ");
    scanf(" %c", &sexo);
    if(sexo != 'M' && sexo != 'F' && sexo != 'm' && sexo != 'f'){
        printf("Sexo invalido\n");
        return;
    }
    printf("Nascimento (dd mm aaaa): ");
    scanf("%d %d %d", &d, &m, &a);
    if(!validarData(d, m, a)){
        printf("Data invalida!\n");
        return;
    }
    professores[tamProfessor].pessoa.matricula = matricula;
    TrocaString(cpf, professores[tamProfessor].pessoa.cpf);
    TrocaString(nome, professores[tamProfessor].pessoa.nome);
    professores[tamProfessor].pessoa.sexo = sexo;
    professores[tamProfessor].pessoa.data.dia = d;
    professores[tamProfessor].pessoa.data.mes = m;
    professores[tamProfessor].pessoa.data.ano = a;
    tamProfessor++;
}
void ExcluirProfessor(int pos){
    for(int j = pos; j < tamProfessor - 1; j++){
        professores[j] = professores[j + 1];
    }
    tamProfessor--;
}
void AtualizarProfessor(){
    int mudanca;
    int matricula;
    int posicao;
    printf("1-Nome | 2-CPF | 3-Sexo | 4-Data| matricula\n");
    scanf("%d", &mudanca);
    printf("Matricula do professor: ");
    scanf("%d", &matricula);
    posicao = buscarprofessorMatricula(matricula);
    if(posicao == -1){
        printf("Professor nao encontrado\n");
        return;
    }
    char nome[100];
    char cpf[12];
    char sexo;
    int d,m,a;
    switch(mudanca){
        case 1:
            printf("Novo nome: ");
            scanf(" %[^\n]", nome);
            TrocaString(nome, professores[posicao].pessoa.nome);
            break;
        case 2:
            printf("Novo CPF: ");
            scanf("%s", cpf);
            if(!validarCPF(cpf)){
                printf("CPF invalido!\n");
                return;
            }
            TrocaString(cpf, professores[posicao].pessoa.cpf);
            break;
        case 3:
            printf("Novo sexo: ");
            scanf(" %c", &sexo);
            if(sexo != 'M' && sexo != 'F' && sexo != 'm' && sexo != 'f'){
                printf("Sexo invalido\n");
                return;
            }
            else{
                professores[posicao].pessoa.sexo = sexo;
            }
            break;
        case 4:
            printf("Nova data (dd mm aaaa): ");
            scanf("%d %d %d", &d, &m, &a);
            if(!validarData(d,m,a)){
                printf("Data invalida!\n");
                return;
            }
            professores[posicao].pessoa.data.dia = d;
            professores[posicao].pessoa.data.mes = m;
            professores[posicao].pessoa.data.ano = a;
            break;
        case 5:
            printf("Nova matricula");
            scanf("%i", &matricula);
            if(matriculaProfessorExiste(matricula)){
                printf("essa matricula ja existe");
                return;
            }else{
                professores[posicao].pessoa.matricula = matricula;
            }
            break;
        default:
            printf("Opcao invalida\n");
    }}
int listarProfessoresPorSexo(char sexoReq){
    int encontrou = 0;
    for(int j = 0; j<tamProfessor; j++){
        if(professores[j].pessoa.sexo == sexoReq || professores[j].pessoa.sexo == sexoReq - 32){
            printf("\n--- Professor %d ---\n", j+1);
            printf("Matricula: %d\n", professores[j].pessoa.matricula);
            printf("CPF: %s\n", professores[j].pessoa.cpf);
            printf("Nome: %s\n", professores[j].pessoa.nome);
            printf("Sexo: %c\n", professores[j].pessoa.sexo);
            encontrou = 1;
        }
    }    
    if(encontrou == 0){
        printf("nenhum professor desse sexo foi encontrado");
        return -1;
    }
    return encontrou;
}
//crud e função dos alunos
void cadastrarAluno(){
    if(i >= LimiteAlunos){
        printf("Limite de alunos atingido\n");
        return;
    }
    int matricula;
    char cpf[12];
    char nome[100];
    char sexo;
    int d,m,a;
    printf("Matricula: ");
    scanf("%d", &matricula);
    if(matriculaAlunoExiste(matricula)){
        printf("Matricula ja existe!\n");
        return;
    }
    printf("CPF: ");
    scanf("%s", cpf);
    if(!validarCPF(cpf)){
        printf("CPF invalido!\n");
        return;
    }
    printf("Nome: ");
    scanf(" %[^\n]", nome);
    printf("Sexo: ");
    scanf(" %c", &sexo);
    if(sexo != 'M' && sexo != 'F' && sexo != 'm' && sexo != 'f'){
        printf("Sexo invalido\n");
        return;
    }
    printf("Nascimento (dd mm aaaa): ");
    scanf("%d %d %d", &d, &m, &a);
    if(!validarData(d,m,a)){
        printf("Data invalida!\n");
        return;
    }
    alunos[i].pessoa.matricula = matricula;
    TrocaString(cpf, alunos[i].pessoa.cpf);
    TrocaString(nome, alunos[i].pessoa.nome);
    alunos[i].pessoa.sexo = sexo;
    alunos[i].pessoa.data.dia = d;
    alunos[i].pessoa.data.mes = m;
    alunos[i].pessoa.data.ano = a;
    alunos[i].qtdDisciplinas = 0;
    i++;

}
int buscarAlunoMatricula(int matricula){
    for(int j = 0; j < i; j++){
        if(alunos[j].pessoa.matricula == matricula){
            return j;
        }
    }
    return -1;
}
void imprimirAlunos(){
    if(i == 0){
        printf("\nNenhum aluno cadastrado\n");
        return;
    }

    for(int j = 0; j < i; j++){
        printf("\n--- ALUNO %d ---\n", j+1);
        printf("Matricula: %d\n", alunos[j].pessoa.matricula);
        printf("CPF: %s\n", alunos[j].pessoa.cpf);
        printf("Nome: %s\n", alunos[j].pessoa.nome);
        printf("Sexo: %c\n", alunos[j].pessoa.sexo);
    }
}
void ExcluirAluno(int pos){
    removerAlunoDeTodasDisciplinas(pos);
    for(int j = pos; j < i - 1; j++){
        alunos[j] = alunos[j + 1];
    }
    i--;
}
void AtualizarAluno(){
    int mudanca;
    int matricula;
    int posicao;
    printf("1-Nome | 2-CPF | 3-Sexo | 4-Data | 5- matricula\n");
    scanf("%d", &mudanca);
    printf("Matricula do aluno: ");
    scanf("%d", &matricula);
    posicao = buscarAlunoMatricula(matricula);
    if(posicao == -1){
        printf("Aluno nao encontrado\n");
        return;
    }
    char nome[100];
    char cpf[12];
    char sexo;
    int d,m,a;
    switch(mudanca){
        case 1:
            printf("Novo nome: ");
            scanf(" %[^\n]", nome);
            TrocaString(nome, alunos[posicao].pessoa.nome);
            break;
        case 2:
            printf("Novo CPF: ");
            scanf("%s", cpf);
            if(!validarCPF(cpf)){
                printf("CPF invalido!\n");
                return;
            }
            TrocaString(cpf, alunos[posicao].pessoa.cpf);
            break;
        case 3:
            printf("Novo sexo: ");
            scanf(" %c", &sexo);
            if(sexo != 'M' && sexo != 'F' && sexo != 'm' && sexo != 'f'){
                printf("Sexo invalido\n");
                return;
            }
            else{
                alunos[posicao].pessoa.sexo = sexo;
            }
            break;
        case 4:
            printf("Nova data (dd mm aaaa): ");
            scanf("%d %d %d", &d, &m, &a);
            if(!validarData(d,m,a)){
                printf("Data invalida!\n");
                return;
            }
            alunos[posicao].pessoa.data.dia = d;
            alunos[posicao].pessoa.data.mes = m;
            alunos[posicao].pessoa.data.ano = a;
            break;
        case 5:
            printf("Nova matricula");
            scanf("%i", &matricula);
            if(matriculaAlunoExiste(matricula)){
                printf("essa matricula ja existe");
                return;
            }else{
                alunos[posicao].pessoa.matricula = matricula;
            }
            break;
        default:
            printf("Opcao invalida\n");
    }
}int ListarAlunosPorSexo(char sexoReq){
    int encontrou = 0;
    for(int j = 0; j<i; j++){
        if(alunos[j].pessoa.sexo == sexoReq || alunos[j].pessoa.sexo == sexoReq - 32){
            printf("\n--- ALUNO %d ---\n", j+1);
            printf("Matricula: %d\n", alunos[j].pessoa.matricula);
            printf("CPF: %s\n", alunos[j].pessoa.cpf);
            printf("Nome: %s\n", alunos[j].pessoa.nome);
            printf("Sexo: %c\n", alunos[j].pessoa.sexo);
            encontrou = 1;
        }
    }    
    if(encontrou == 0){
        printf("nenhum aluno desse sexo foi encontrado");
        return -1;
    }
    return encontrou;
}
void AlunosComMenosDe3Disciplinas(){
    int encontrou = 0;
    for(int j = 0; j<i; j++){
        if(alunos[j].qtdDisciplinas<3){
            printf("\n--- ALUNO %d ---\n", j+1);
            printf("Matricula: %d\n", alunos[j].pessoa.matricula);
            printf("CPF: %s\n", alunos[j].pessoa.cpf);
            printf("Nome: %s\n", alunos[j].pessoa.nome);
            printf("Sexo: %c\n", alunos[j].pessoa.sexo);
            encontrou = 1;
        }
    }
    if(encontrou == 0){
        printf("nenhum aluno com menos de 3 disciplina foi encontrado");
    }
}
void ordenarAlunosPorNome() {
    struct Aluno temp;

    for(int j = 0; j < i - 1; j++){
        for(int k = j + 1; k < i; k++){
            if(strcmp(alunos[j].pessoa.nome, alunos[k].pessoa.nome) > 0){
                temp = alunos[j];
                alunos[j] = alunos[k];
                alunos[k] = temp;
            }
        }
    }

    printf("\n--- ALUNOS ORDENADOS POR NOME ---\n");
    imprimirAlunos();
}
void ordenarAlunosPorData() {
    struct Aluno temp;

    for(int j = 0; j < i - 1; j++){
        for(int k = j + 1; k < i; k++){
            if(compararData(alunos[j].pessoa.data, alunos[k].pessoa.data) > 0){
                temp = alunos[j];
                alunos[j] = alunos[k];
                alunos[k] = temp;
            }
        }
    }

    printf("\n--- ALUNOS ORDENADOS POR DATA ---\n");
    imprimirAlunos();
}
// crud e funções da disciplinas
void removerDisciplinaDeTodosAlunos(char codigo[]){
    for(int j = 0; j < i; j++){
        for(int k = 0; k < alunos[j].qtdDisciplinas; k++){
            if(strcmp(alunos[j].codDisciplinas[k], codigo) == 0){

                for(int x = k; x < alunos[j].qtdDisciplinas - 1; x++){
                    TrocaString(
                        alunos[j].codDisciplinas[x + 1],
                        alunos[j].codDisciplinas[x]
                    );
                }

                alunos[j].qtdDisciplinas--;
                k--;
            }
        }
    }
}
void cadastrarDisciplina(){
    if(tamDisciplinas >= LimiteDisciplinas){
        printf("Limite de disciplinas atingido\n");
        return;
    }
    char nome[100];
    char codigo[20];
    int matricula;
    int semestre;
    printf("Nome da disciplina: ");
    scanf(" %[^\n]", nome); 
    printf("Codigo da Disciplina: ");
    scanf("%19s", codigo);
    if(BuscarDisciplinaCod(codigo) != -1){
        printf("Codigo de disciplina ja existe!\n");
        return;
    }
    printf("Matricula do Professor: ");
    scanf("%d", &matricula);
    if(buscarprofessorMatricula(matricula) == -1){
        printf("Professor nao encontrado\n");
        return;
    }
    printf("Semestre (1-12): ");
    scanf("%d", &semestre);
    if(semestre < 1 || semestre > 12){
        printf("Semestre invalido\n");
        return;
    }
    TrocaString(nome, disciplinas[tamDisciplinas].nome);
    TrocaString(codigo, disciplinas[tamDisciplinas].codigo);
    disciplinas[tamDisciplinas].matriculaProf = matricula;
    disciplinas[tamDisciplinas].semestre = semestre;
    disciplinas[tamDisciplinas].qtdAlunos = 0;
    tamDisciplinas++;
    printf("Disciplina cadastrada com sucesso!\n");
}
void excluirDisciplina(char codigo[]){
    int position = -1;
    for(int i = 0; i<tamDisciplinas; i++){
        if(strcmp(disciplinas[i].codigo, codigo) == 0){
            position = i;
            break;
        }
    }
    if(position == -1){
        printf("Disciplina nao encontrada\n");
        return;
    }
    for(int j = position; j < tamDisciplinas - 1; j++){
        disciplinas[j] = disciplinas[j + 1];
    }
    removerDisciplinaDeTodosAlunos(codigo);
    tamDisciplinas--;
}
void cadastrarAlunoNaDisciplina(char codigo[], int matricula){
    int posDisciplina = BuscarDisciplinaCod(codigo);
    int posAluno = buscarAlunoMatricula(matricula);
    if(posDisciplina == -1){
        printf("essa disciplina nao foi encontrada");
        return;
    }
    
    if(posAluno == -1){
        printf("Aluno nao encontrado\n");
        return;
    }
    if(alunos[posAluno].qtdDisciplinas >= LimiteDisciplina){
    printf("Limite de disciplinas atingido\n");
    return;
    }
    
    if(disciplinas[posDisciplina].qtdAlunos >= LimiteAlunos){
        printf("Disciplina cheia\n");
        return;
    }
    for(int i = 0; i < alunos[posAluno].qtdDisciplinas; i++){
        if(strcmp(alunos[posAluno].codDisciplinas[i], codigo) == 0){
            printf("Aluno ja esta na disciplina\n");
            return;
        }
    }

    TrocaString(
        codigo,
        alunos[posAluno].codDisciplinas[alunos[posAluno].qtdDisciplinas]
    );
    alunos[posAluno].qtdDisciplinas++;
    disciplinas[posDisciplina].qtdAlunos++;
    printf("Aluno matriculado na disciplina!\n");
}
void ExcluirAlunoDaDisciplina(int matricula, char codigo[]){
    int posAluno = buscarAlunoMatricula(matricula);
    int posDisciplina = BuscarDisciplinaCod(codigo);

    if(posAluno == -1){
        printf("Aluno nao existe\n");
        return;
    }

    if(posDisciplina == -1){
        printf("Disciplina nao existe\n");
        return;
    }

    int encontrou = 0;

    for(int i = 0; i < alunos[posAluno].qtdDisciplinas; i++){
        if(strcmp(alunos[posAluno].codDisciplinas[i], codigo) == 0){

            for(int j = i; j < alunos[posAluno].qtdDisciplinas - 1; j++){
                TrocaString(
                    alunos[posAluno].codDisciplinas[j + 1],
                    alunos[posAluno].codDisciplinas[j]
                );
            }

            alunos[posAluno].qtdDisciplinas--;
            disciplinas[posDisciplina].qtdAlunos--;
            encontrou = 1;
            break;
        }
    }

    if(!encontrou){
        printf("Aluno nao esta nessa disciplina\n");
        return;
    }

    printf("Aluno removido com sucesso!\n");}
void ListarDisciplinas(){
    if(tamDisciplinas == 0){
        printf("\nNenhuma disciplina cadastrada\n");
        return;
    }
    for(int j = 0; j < tamDisciplinas; j++){
        printf("\n--- disciplina %d ---\n", j+1);
        printf("nome: %s\n", disciplinas[j].nome);
        printf("quantidade de alunos: %d\n", disciplinas[j].qtdAlunos);
        printf("semestre %i", disciplinas[j].semestre);
        for(int l = 0; l<tamProfessor; l++){
            if(disciplinas[j].matriculaProf == professores[l].pessoa.matricula){
                printf("\n--- professor %d ---\n", j+1);
                printf("Matricula: %d\n", professores[l].pessoa.matricula);
                printf("CPF: %s\n", professores[l].pessoa.cpf);
                printf("Nome: %s\n", professores[l].pessoa.nome);
                printf("Sexo: %c\n", professores[l].pessoa.sexo);
                break;

            };
        }
        printf("codigo: %s\n", disciplinas[j].codigo);
    }
}
void ListarDisciplina(char codigo[]){
    int posicaoDis = BuscarDisciplinaCod(codigo);
    if(posicaoDis == -1){
        printf("Disciplina nao encontrada\n");
        return;
    }
    printf("\n--- disciplina---\n");
    printf("nome: %s\n", disciplinas[posicaoDis].nome);
    printf("quantidade de alunos: %d\n", disciplinas[posicaoDis].qtdAlunos);
    printf("semestre da disciplina: %d\n", disciplinas[posicaoDis].semestre);
        for(int l = 0; l<tamProfessor; l++){
            if(disciplinas[posicaoDis].matriculaProf == professores[l].pessoa.matricula){
                printf("\n--- professor %d ---\n", l+1);
                printf("Matricula: %d\n", professores[l].pessoa.matricula);
                printf("CPF: %s\n", professores[l].pessoa.cpf);
                printf("Nome: %s\n", professores[l].pessoa.nome);
                printf("Sexo: %c\n", professores[l].pessoa.sexo);
                break;
            };
        }
    printf("codigo: %s\n", disciplinas[posicaoDis].codigo);
    for(int j = 0; j<i; j++){
        for(int l = 0; l<alunos[j].qtdDisciplinas; l++){
            if(strcmp(disciplinas[posicaoDis].codigo, alunos[j].codDisciplinas[l]) == 0){
                printf("\n--- aluno  ---\n");
                printf("Matricula: %d\n", alunos[j].pessoa.matricula);
                printf("CPF: %s\n", alunos[j].pessoa.cpf);
                printf("Nome: %s\n", alunos[j].pessoa.nome);
                printf("Sexo: %c\n", alunos[j].pessoa.sexo);
            };
        }
    }
}    
void exibirComMaisdeXnumero(int NumLimite){
    printf("disciplinas com mais de %i alunos", NumLimite);
    for(int i = 0; i<tamDisciplinas; i++){
        if(disciplinas[i].qtdAlunos >= NumLimite){
            printf("nome: %s\n", disciplinas[i].nome);
            printf("quantidade de alunos: %d\n", disciplinas[i].qtdAlunos);
            int pos = buscarprofessorMatricula(disciplinas[i].matriculaProf);
            printf("professor %s", professores[pos].pessoa.nome);
        }
    }
    
}
void AtualizarDisciplina(){
    char codigo[20];
    printf("Codigo da disciplina: ");
    scanf("%s", codigo);
    int pos = BuscarDisciplinaCod(codigo);
    if(pos == -1){
        printf("Disciplina nao encontrada\n");
        return;
    }
    int opcao;
    printf("1-Nome | 2-Professor | 3-Semestre\n");
    scanf("%d", &opcao);
    if(opcao == 1){
        printf("Novo nome: ");
        scanf(" %[^\n]", disciplinas[pos].nome);
    }
    else if(opcao == 2){
        int mat;
        printf("Nova matricula professor: ");
        scanf("%d", &mat);
        if(buscarprofessorMatricula(mat) == -1){
            printf("Professor nao existe\n");
            return;
        }
        disciplinas[pos].matriculaProf = mat;
    }
    else if(opcao == 3){
        int semestre;
        scanf("%d", &semestre);
        if(semestre < 1 || semestre > 12){
            printf("Semestre invalido\n");
            return;
        }
        disciplinas[pos].semestre = semestre;
    }
}
//Relatorios Gerais
void AniversariantesDoMes(int mes){
    printf("alunos aniversariantes do mes");
    for(int l = 0; l<i; l++){
        if(alunos[l].pessoa.data.mes == mes){
            printf("%s, %s, %i\n", alunos[l].pessoa.nome, alunos[l].pessoa.cpf, alunos[l].pessoa.matricula);
        }    
    }
    printf("Professores aniversariantes do mes");
    for(int l = 0; l<tamProfessor; l++){
        if(professores[l].pessoa.data.mes == mes){
            printf("%s, %s, %i", professores[l].pessoa.nome, professores[l].pessoa.cpf, professores[l].pessoa.matricula);
        }    
    }
    
    
    
}
void StringBusca(char pesq[]){
    if(strlen(pesq) < 3){
        printf("Digite pelo menos 3 letras\n");
        return;
    }
    for(int j = 0; j<i; j++){
        int encontrou;
        for(int l = 0; alunos[j].pessoa.nome[l]!='\0'; l++){
            encontrou = 1;
            for(int m = 0; pesq[m]!='\0'; m++){
                if(alunos[j].pessoa.nome[l+m] == '\0' || alunos[j].pessoa.nome[l+m] != pesq[m]){
                    encontrou = 0;
                    break;
                }
            }
            if(encontrou){
                printf("%s\n", alunos[j].pessoa.nome);
                break;
            }
        }
    }
    for(int j = 0; j<tamProfessor; j++){
        int encontrou = 0;
        for(int l = 0; professores[j].pessoa.nome[l]!='\0'; l++){
            encontrou = 1;
            for(int m = 0; pesq[m]!='\0'; m++){
                if(professores[j].pessoa.nome[l+m] == '\0' || professores[j].pessoa.nome[l+m] != pesq[m]){
                    encontrou = 0;
                    break;
                }
            }
            if(encontrou){
                printf("%s\n", professores[j].pessoa.nome);
                break;
            }
        }
    }
}
//programa rodando aqui
int main(){
    int opcaoPrincipal, opcaoSub;
    int rodando = 1;

    while(rodando){
        printf("\n===== SISTEMA ACADEMICO =====\n");
        printf("1 - Alunos\n");
        printf("2 - Professores\n");
        printf("3 - Disciplinas\n");
        printf("4 - Relatorios\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcaoPrincipal);

        switch(opcaoPrincipal){
        case 1:
            printf("\n--- MENU ALUNOS ---\n");
            printf("1 - Cadastrar aluno\n");
            printf("2 - Listar alunos\n");
            printf("3 - Excluir aluno\n");
            printf("4 - Atualizar aluno\n");
            printf("5 - Listar por sexo\n");
            printf("6 - Alunos com menos de 3 disciplinas\n");
            printf("7 - Ordenar por nome\n");
            printf("8 - Ordenar por data\n");
            printf("Escolha: ");
            scanf("%d", &opcaoSub);

            if(opcaoSub == 1){
                cadastrarAluno();
            }
            else if(opcaoSub == 2){
                imprimirAlunos();
            }
            else if(opcaoSub == 3){
                int mat;
                printf("Matricula: ");
                scanf("%d", &mat);
                int pos = buscarAlunoMatricula(mat);
                if(pos != -1){
                    ExcluirAluno(pos);
                } else {
                    printf("Aluno nao encontrado\n");
                }
            }
            else if(opcaoSub == 4){
                AtualizarAluno();
            }
            else if(opcaoSub == 5){
                char sexo;
                printf("Sexo (M/F): ");
                scanf(" %c", &sexo);
                ListarAlunosPorSexo(sexo);
            }
            else if(opcaoSub == 6){
                AlunosComMenosDe3Disciplinas();
            }
            else if(opcaoSub == 7){
                ordenarAlunosPorNome();
            }
            else if(opcaoSub == 8){
                ordenarAlunosPorData();
            }
            break;
        case 2:
            printf("\n--- MENU PROFESSORES ---\n");
            printf("1 - Cadastrar professor\n");
            printf("2 - Listar professores\n");
            printf("3 - Excluir professor\n");
            printf("4 - Atualizar professor\n");
            printf("5 - Listar por sexo\n");
            printf("6 - Ordenar por nome\n");
            printf("7 - Ordenar por data\n");
            printf("Escolha: ");
            scanf("%d", &opcaoSub);

            if(opcaoSub == 1){
                cadastrarProfessor();
            }
            else if(opcaoSub == 2){
                imprimirProfessores();
            }
            else if(opcaoSub == 3){
                int mat;
                printf("Matricula: ");
                scanf("%d", &mat);
                int pos = buscarprofessorMatricula(mat);
                if(pos != -1){
                    ExcluirProfessor(pos);
                } else {
                    printf("Professor nao encontrado\n");
                }
            }
            else if(opcaoSub == 4){
                AtualizarProfessor();
            }
            else if(opcaoSub == 5){
                char sexo;
                printf("Sexo (M/F): ");
                scanf(" %c", &sexo);
                listarProfessoresPorSexo(sexo);
            }
            else if(opcaoSub == 6){
                ordenarProfessoresPorNome();
            }
            else if(opcaoSub == 7){
                ordenarProfessoresPorData();
            }
            break;
        case 3:
            printf("\n--- MENU DISCIPLINAS ---\n");
            printf("1 - Cadastrar disciplina\n");
            printf("2 - Listar disciplinas\n");
            printf("3 - Excluir disciplina\n");
            printf("4 - Matricular aluno\n");
            printf("5 - Remover aluno\n");
            printf("6 - Buscar disciplina\n");
            printf("Escolha: ");
            scanf("%d", &opcaoSub);

            if(opcaoSub == 1){
                cadastrarDisciplina();
            }
            else if(opcaoSub == 2){
                ListarDisciplinas();
            }
            else if(opcaoSub == 3){
                char codigo[20];
                printf("Codigo: ");
                scanf("%s", codigo);
                excluirDisciplina(codigo);
            }
            else if(opcaoSub == 4){
                char codigo[20];
                int mat;
                printf("Codigo da disciplina: ");
                scanf("%s", codigo);
                printf("Matricula do aluno: ");
                scanf("%d", &mat);
                cadastrarAlunoNaDisciplina(codigo, mat);
            }
            else if(opcaoSub == 5){
                char codigo[20];
                int mat;
                printf("Codigo da disciplina: ");
                scanf("%s", codigo);
                printf("Matricula do aluno: ");
                scanf("%d", &mat);
                ExcluirAlunoDaDisciplina(mat, codigo);
            }
            else if(opcaoSub == 6){
                char codigo[20];
                printf("Codigo: ");
                scanf("%s", codigo);
                ListarDisciplina(codigo);
            }
            break;
        case 4:
            printf("\n--- RELATORIOS ---\n");
            printf("1 - Aniversariantes do mes\n");
            printf("2 - Buscar pessoa por nome\n");
            printf("3 - Disciplinas com X alunos\n");
            printf("Escolha: ");
            scanf("%d", &opcaoSub);

            if(opcaoSub == 1){
                int mes;
                printf("Mes (1-12): ");
                scanf("%d", &mes);
                AniversariantesDoMes(mes);
            }
            else if(opcaoSub == 2){
                char busca[100];
                printf("Digite nome: ");
                scanf(" %[^\n]", busca);
                StringBusca(busca);
            }
            else if(opcaoSub == 3){
                int x;
                printf("Numero minimo: ");
                scanf("%d", &x);
                exibirComMaisdeXnumero(x);
            }
            break;

        case 0:
            rodando = 0;
            break;

        default:
            printf("Opcao invalida\n");
        }
    }

    return 0;
}