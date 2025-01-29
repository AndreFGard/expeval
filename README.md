# expeval
*<center>An expression evaluator.</center>*

## Como executar
### Compilação
Este projeto requer acesso a um compilador compatível com o padrão de 2017, devido ao uso de ``std::string_view`` e de `std::variant`.

```bash 
g++ arith_expr.cpp tokenizer.cpp logic_expr.cpp main.cpp operator.cpp parser.cpp -std=c++17 -o expeval
./expeval
```

Opcionalmente, a flag de compilação -DDBG pode ser usada para que o programa leia a entrada até o EOF.

## Explicações

#### string_view
O uso de string_view no tokenizador reduz a cópia desnecessária strings do método substr.

#### estrutura das classes de expressão
Com uma certa inspiração no CRTP, a classe abstrata LitExp (expressão literal) usa templates para facilitar o overloading dos seus métodos, em especial o ``getVal``, cujo tipo de retorno muda dependendo da classe filha. Além disso, a LitExp herda da classe Expression, que facilita o upcasting das classes filhas ArithExp e LogicExp, facilitando o aproveitamento do Parser dos métodos virtuais. Dessa forma, o código dele fica mais simples, abstraindo a complexidade de garantir a compatibilidade entre os tipos literais (bool ou aritmético) das subexpressões e a passando para métodos como o apply_operator ou os próprios métodos relativos a cada operador da linguagem, que usam o dynamic_cast para isso.

#### Uso de friend
Usado apenas para fazer overload do operator <<.


GPL-3