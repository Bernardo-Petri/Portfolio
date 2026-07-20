import 'dart:io';

main(){
    // o programa recebe do usuário o valor em dólar
    double n;
    String texto;
    print("Digite o valor do real em dólares: ");
    // a entrada retorna uma string
    texto = stdin.readLineSync()!;
    // será necessário converter a string em um couble
    n = double.parse(texto);
    print("1US é igual a $n reais.");
}