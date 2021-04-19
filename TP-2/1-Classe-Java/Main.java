import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

class Main{
    public static String TratarVaziosEVirgulas(String linha){
        int cont = 1;
        String result = "";
        //tratar os casos com virgula no meio de aspas
        for(int i = 0; i < linha.length(); i++){
            if(linha.charAt(i) == '"'){
                do{
                    i++;
                    if(linha.charAt(i) == ';'){
                        result += ' ';
                        result += '-';
                    }else{
                        result += linha.charAt(i);
                    }
                }while(linha.charAt(i) != '"');
            }else{
                result += linha.charAt(i);
            }
        }
        linha = result;
        result = "";
        //for para tratar valor totalmente vazios dentro do programa
        for(int i = 0; i < linha.length(); i++){
            if(linha.charAt(i) == ';'){
                //tratar os valores vazios
                if(cont != 7){
                    if(linha.charAt(i+1) == ';'){
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

    public static void main(String[]args){
        String csv = "/tmp/players.csv";
        BufferedReader br = null;
        String linha = "";
        //vetor onde sera guardado todos os jogadores
        Jogador [] vetJogadores = new Jogador[5000];
        int i = 0;

        try {
            br = new BufferedReader(new FileReader(csv));
            linha = br.readLine();
            linha = "";
            while ((linha = br.readLine()) != null) {
                if(i != 0 && i != 223){
                    vetJogadores[i] = new Jogador();
                    String result = "";
                    linha = linha.replace(',', ';');
                    linha = TratarVaziosEVirgulas(linha);
                    //colocar cada informação dentro de um espaço dentro do array de string
                    Jogador.ler(linha, i, vetJogadores[i]);
                    i++;
                }else{
                    i++;
                }
        }

        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            if (br != null) {
                try {
                    br.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
        String num = MyIO.readString();
        do{
            int num1 = Integer.parseInt(num);
            Jogador.imprimir(num1, vetJogadores);
            num = MyIO.readString();
        }while(isFim(num) == false);
    }
}

class Jogador{
    private int id;
    private int altura;
    private int peso;
    private int anoNascimento;

    private String nome;
    private String universidade;
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

    public static void ler(String linha, int i, Jogador j1){
        linha = linha.replace(',', ';');
        linha = Main.TratarVaziosEVirgulas(linha);
        String[] jogadores = linha.split(";");

        j1.setEstado(jogadores[jogadores.length-1]);
        j1.setCidade(jogadores[jogadores.length-2]);
        j1.setNascimento(Integer.parseInt(jogadores[jogadores.length-3]));
        j1.setUniversidade(jogadores[jogadores.length-4]);
        //transformar string em int
        j1.setPeso(Integer.parseInt(jogadores[jogadores.length-5]));
        j1.setAltura(Integer.parseInt(jogadores[jogadores.length-6]));
        j1.setNome(jogadores[jogadores.length-7]);
        j1.setId(i);
    }

    public static void imprimir(int i, Jogador vetJogadores[]){
        MyIO.println("["+ i +" ## "+vetJogadores[i].getNome()+" ## "+vetJogadores[i].getAltura()+" ## "+vetJogadores[i].getpeso()+" ## "+vetJogadores[i].getNascimento()+" ## "+vetJogadores[i].getUniversidade()+" ## "+vetJogadores[i].getCidade()+" ## "+vetJogadores[i].getEstado()+"]");
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