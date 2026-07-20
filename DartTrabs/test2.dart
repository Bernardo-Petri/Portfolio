import 'dart:io';

main() {
    // o programa a seguir testa se o usuario ira acertar a senha
    String texto;
    print("Digite a senha ");
    // o usuario digita a senha 
    texto = stdin.readLineSync()!;
    // os condicionais testam se o usuario acertou
    if(texto == "1234"){
        print("Senha correta");
    }
    else{
        print("Senha incorreta");
    }
}