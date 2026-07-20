import 'dart:io';

main() {
    // o programa testa se o número digitado pelo usuário é um múltiplo de 3 ou não
    int n;
    String texto;
    print("Digite um número: ");
    // a entrada retorna uma string
    texto = stdin.readLineSync()!;
    // será necessário converter a string em um inteiro
    n = int.parse(texto);
    if(n%3==0){
        print("O número digitado é múltiplo de 3.");
    }
    else{
        print("O número digitado não é múltiplo de 3.");
    }
}