import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

class Main{
    public static String TratarVaziosEVirgulas(String linha){
        int cont = 1;
        String result = "";
        //for para tratar valor totalmente vazios dentro do programa
        for(int i = 0; i < linha.length(); i++){
            if(linha.charAt(i) == ','){
                //tratar os valores vazios
                if(cont != 7){
                    if(linha.charAt(i+1) == ','){
                        result += linha.charAt(i);
                        result += "nao informado";
                    }else if(linha.charAt(i+1) == 'n' && linha.charAt(i+2) == 'a' && linha.charAt(i+3) == 'n'){
                        result += linha.charAt(i);
                        result += "nao informado";
                        i+=3;
                    }else{
                        result += linha.charAt(i);
                    }
                }else{
                    if(i == (linha.length()-1)){
                        result += linha.charAt(i);
                        result += "nao informado";
                    }else{
                        result += linha.charAt(i);
                    }
                }
                cont++;
            }else{
                result += linha.charAt(i);
            }
        }
        linha = result;
        result = "";
        return linha;
    }
    public static boolean isFim(String s){
        return (s.length() == 3 && s.charAt(0) == 'F' && s.charAt(1) == 'I' && s.charAt(2) == 'M');
    }
    //Funçao q verifica se o nome digitado contem no segundo vetor criado
    public static boolean nomeIgual(Jogador[]vet, String nome, int y){
        for(int i = 0; i < y; i++){
            Jogador.comp++;
            if(nome.equals(vet[i].getNome()))
                return true;
        }
        return false;
    }
    //Funcao q ira ler o arquivo e retornar um vet do tipo Jogador preenchido com as informaçoes
    public static Jogador[] lerArquivo(){
        Arq.openRead("/tmp/players.csv");
        Jogador vet[] = new Jogador[5000];
        String linha = Arq.readLine();
        linha = Arq.readLine();
        int i = 0;
        while(Arq.hasNext()){
            vet[i] = new Jogador();
            Jogador.ler(linha, vet[i]);
            linha = Arq.readLine();
            i++;
        }
        vet[i] = new Jogador();
        Jogador.ler(linha, vet[i]);
        Arq.close();
        return vet;
    }

    public static void main(String[]args){
        double start = System.currentTimeMillis();
        //vetor onde sera guardado todos os jogadores
        Jogador [] vetJogadores = new Jogador[5000];
        Jogador [] vetJogadores2 = new Jogador[5000];
        vetJogadores = lerArquivo();
        

        String num = MyIO.readString();
        int i = 0;
        do{
            int num1 = Integer.parseInt(num);
            //funçao clonar q pega as informações do jogador pedido, e as clona para um outro vetor
            vetJogadores2[i] = Jogador.clonar(vetJogadores, num1);
            num = MyIO.readString();
            i++;
        }while(isFim(num) == false);

        vetJogadores2 = Jogador.OrdenarPorNomeSelecao(vetJogadores2, i);

        for(int y = 0; y < i; y++){
            Jogador.imprimir(y, vetJogadores2);
        }

        Arq.openWriteClose("matricula_selecao.txt", "561170\t"+Jogador.comp+"\t"+Jogador.mov+"\t"+((System.currentTimeMillis()-start)/1000));

    }
}

class Jogador{
    public static int nextId = 0;
    public static int comp = 0;
    public static int mov = 0;

    private int id;
    private int altura;
    private int peso;

    private String nome;
    private String universidade;
    private int anoNascimento;
    private String cidadeNascimento;
    private String estadoNascimento;

    Jogador(){
        this.altura = 0;
        this.peso = 0;
    }
    Jogador(int x, int y){
        this.altura = x;
        this.peso = y;
    }
    public static Jogador[] OrdenarPorNomeSelecao(Jogador[]vet, int tam){
        int min;
        for(int i =0; i < (tam-1); i++){
            min = i;
            for (int j = (i+1); j < tam; j++){
                if(vet[j].getNome().compareTo(vet[min].getNome()) < 0){
                    Jogador.comp++;
                    min = j;
                }
            }
            vet = swap(vet, i, min);
        }
        return vet;
    }
    //funçao que troca os valores dentro de um vetor e retorna o mesmo
    public static Jogador[] swap(Jogador[]vet, int i, int min){
        Jogador aux = Jogador.clonar(vet, i);
        vet[i] = vet[min];
        vet[min] = aux;
        Jogador.mov += 3;
        return vet;
    }
    public static Jogador clonar(Jogador[]vet, int origem){
        Jogador j1 = new Jogador();
        j1.setId(vet[origem].getId());
        j1.setNome(vet[origem].getNome());
        j1.setAltura(vet[origem].getAltura());
        j1.setPeso(vet[origem].getpeso());
        j1.setCidade(vet[origem].getCidade());
        j1.setEstado(vet[origem].getEstado());
        j1.setUniversidade(vet[origem].getUniversidade());
        j1.setNascimento(vet[origem].getNascimento());
        return j1;
    }
    public static void ler(String linha, Jogador j1){
        linha = Main.TratarVaziosEVirgulas(linha);
        String[] infos = linha.split(",");

        j1.setEstado(infos[infos.length-1]);
        j1.setCidade(infos[infos.length-2]);
        j1.setNascimento(Integer.parseInt(infos[infos.length-3]));
        j1.setUniversidade(infos[infos.length-4]);
        //transformar string em int
        j1.setPeso(Integer.parseInt(infos[infos.length-5]));
        j1.setAltura(Integer.parseInt(infos[infos.length-6]));
        j1.setNome(infos[infos.length-7]);
        j1.setId(nextId++);
    }
    public static void imprimir(int i, Jogador vetJogadores[]){
        MyIO.println("["+ vetJogadores[i].getId() +" ## "+vetJogadores[i].getNome()+" ## "+vetJogadores[i].getAltura()+" ## "+vetJogadores[i].getpeso()+" ## "+vetJogadores[i].getNascimento()+" ## "+vetJogadores[i].getUniversidade()+" ## "+vetJogadores[i].getCidade()+" ## "+vetJogadores[i].getEstado()+"]");
    }
    public void setId(int x){
        this.id = x;
    }
    public int getId(){
        return this.id;
    }
    public void setAltura(int x){
        this.altura = x;
    }
    public int getAltura(){
        return this.altura;
    }
    public void setPeso(int x){
        this.peso = x;
    }
    public int getpeso(){
        return this.peso;
    }
    public void setNome(String x){
        this.nome = x;
    }
    public String getNome(){
        return this.nome;
    }
    public void setUniversidade(String x){
        String result = "";
        for(int i = 0; i < x.length(); i++){
            if(x.charAt(i) != '"'){
                result += x.charAt(i);
            }
        }
        x = result;
        this.universidade = x;
    }
    public String getUniversidade(){
        return this.universidade;
    }
    public void setNascimento(int x){
        this.anoNascimento = x;
    }
    public int getNascimento(){
        return this.anoNascimento;
    }
    public void setCidade(String x){
        this.cidadeNascimento = x;
    }
    public String getCidade(){
        return this.cidadeNascimento;
    }
    public void setEstado(String x){
        this.estadoNascimento = x;
    }
    public String getEstado(){
        return this.estadoNascimento;
    }
}
