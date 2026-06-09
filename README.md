# 🔏 APIRest

> Servidor REST para serviços de criptografia.

## 📋 Tabela de Conteúdos
- [Sobre](#-sobre)
- [Funcionalidades](#-funcionalidades)
- [Pré-requisitos gerais](#%EF%B8%8F-pr%C3%A9-requisitos-gerais)
- [Instalação](#-instalação)
    - [Pacote](#-Pacote)
    - [CMake](#-cmake)
    - [Conan](#-conan)
        - [Pré-requisitos](#%EF%B8%8F-pr%C3%A9-requisitos)
        - [Passos para a compilação](#-passos-para-a-compilação)
- [Pipeline](#-pipeline)
- [Configuração](#-configuração)
    - [Chaves-de-configuração](#-chaves-de-configuração)
        - [Passos-para-gerar-arquivo-pkcs12](#-passos-para-gerar-arquivo-pkcs12)
- [Como Usar](#-como-usar)

## 📖 Sobre

Servidor REST que expõe duas rotas para serviços de criptografia. Uma rota tem o objetivo de assinar um arquivo e retornar a assinatura em base 64. Outra rota tem como objetivo fazer a verificação rigorosa da assinatura de um arquivo e retornar alguns dados dessa assinatura.

## ✨ Funcionalidades

- [x] Assinar arquivo e retornar a assinatura em base 64
- [x] Fazer verificação rigorosa de assinatura de um arquivo
- [x] Retornar nomes dos signatários
- [x] Retornar datas de assinatura
- [x] Retornar o hash do conteúdo assinado
- [x] Retornar nomes de algoritmos de sumário de mensagens utilizados na assinatura

## 🛠️ Pré-requisitos gerais

* C++17 ou superior.

## 🚀 Instalação

### 📦 Pacote
1. Baixar o pacote:

    ```bash
    wget https://github.com/marvsc/APIRest/releases/download/v<versão>/apirest-v<versão>.tgz
    ```

2. Descompactar:

    ```bash
    tar zxvf apirest-v<versão>.tgz -C <diretório a descompactar>
    ```

### 📜 CMake

1. Clonar o projeto:

    ```bash
    git clone git@github.com:marvsc/APIRest.git
    ```

2. Criar o diretório build:

    ```bash
    mkdir build
    ```

3. Instalar os geradores:

    ```bash
    conan install . --build=missing
    ```

4. Gerar Makefile:

    ```bash
    cmake -DCMAKE_TOOLCHAIN_FILE=build/Release/generators/conan_toolchain.cmake -S . -B build
    ```

5. Compilar projeto:

    ```bash
    make -C build/
    ```

> [!NOTE]
> O comando acima irá compilar o projeto e gerar o artefato build/apirest

### 💪🏻 Conan

#### 🛠️ Pré-requisitos

* Conan na versão 2.25.2

#### 👣 Passos para a compilação

1. Clonar o projeto:

    ```bash
    git clone git@github.com:marvsc/APIRest.git
    ```

2. Definir a senha de acesso ao arquivo PKCS 12 na variável de ambiente PKCS12_ENVVAR_PASSWORD:

    2.1. Converter a chave e o vetor de inicialização em formato hexadecimal

    ```bash
    echo -n "<chave>" | xxd -p -c 256
    echo -n "<iv> | xxd -p -c 256
    ```

    2.2. Encriptar a senha passando a chave e o vetor de inicialização em hexadecimal

    ```bash
    echo -n "<senha>" | openssl enc -aes-256-cbc -e -base64 -K <chave_hex> -iv <iv_hex>
    ```

    2.3. Definir a variável de ambiente PKCS12_ENVVAR_PASSWORD com a senha encriptada:

    ```bash
    export PKCS12_ENVVAR_PASSWORD=<senha_enc>
    ```

> [!IMPORTANT]
> A chave e o vetor de inicialização podem ser obtidos no arquivo test_package/src/UnitTests/include/APIRestServerTestMacros.h

3. Criar o projeto utilizando conan:

    ```bash
    conan create . --build=missing
    ```

> [!NOTE]
> O comando acima vai baixar e compilar todas as dependencias, compilar o projeto e executar os testes que é composto de 1 executáveil que faz os testes unitários.

## 🤞 Pipeline
Ao criar uma tag, duas pipelines são disparadas via github para gerar a release automaticamente e para publicar o pacote no repositório do conan (cloudsmith).

## 🔩 Configuração

O arquivo de configuração é gerado durante a compilação no diretório conf/APIRest.properties e é composto por algumas chaves que definem o comportamento do servidor REST.

### 🔑 Chaves de configuração

As configurações de log utilizam a especificação da [libpoco](https://docs.pocoproject.org/current/Poco.Util.LoggingConfigurator.html). As configurações específicas da APIRest seguem abaixo:

O diretório onde os arquivos recebidos pelo servidor serão salvos deve ser definido na seguinte chave:

```
apirest.upload.dir = /tmp/apirest/uploads
```

As seguintes chaves correspondem ao caminho para o arquivo PKCS12 utilizado pelo servidor para fazer uma verificação rigorosa da conexão e a senha para acesso ao conteúdo desse arquivo:

```
apirest.pkcs12.path = 
apirest.pkcs12.password.aes.256.cbc.base64 = 
```

A senha deve ser criptografada conforme a seção 2 dos [Passos para a compilação](#-passos-para-a-compilação).
O arquivo PKCS 12 deve ser gerado seguindo os passos a seguir:

#### 👣 Passos para gerar arquivo PKCS12

1. Gerar chave privada da autoridade certificadora:

```bash
openssl genrsa -out <nome da chave>.pem 4096
```

> [!IMPORTANT] Esse arquivo deve ser gerado na máquina que será utilizada como autoridade certificadora.

2. Gerar certificado da autoridade certificadora:

```bash
openssl req -new -x509 -keyout <nome da chave>.pem -out <nome do certificado>.pem -subj "/CN=<nome da máquina>" -addext "basicConstraints=critical,CA:TRUE" -addext "keyUsage=critical,keyCertSign,cRLSign" -addext "subjectAltName=DNS:minha-ca.com.br,IP:192.168.1.1"
```

> [!IMPORTANT] O certificado da autoridade certificadora deve ser gerado com common name e subject alternative name definidos além de basic constraints critical e CA e keyusage critival, key cert sign e crl sign para não passar na verificação rigorosa. O common name deve ser o nome da máquina obtido com o comando hostname e o subject alternative name deve ter dns como o nome da máquina também e ip sendo o ip da máquina.

3. Gerar chave privada do servidor:

```bash
openssl genrsa -out <nome da chave>.pem 4096
```

> [!IMPORTANT] A chave privada do servidor deve ser gerada na máquina que será usada como servidor.

4. Gerar requisição de assinatura do servidor:

```bash
openssl req -new -keyout <nome da chave>.pem -out <nome da requisição>.csr -subj "/CN=servidor.minha-ca.com.br" -addext "subjectAltName=DNS:servidor.minha-ca.com.br,IP:192.168.1.100" -addext "keyUsage=critical,digitalSignature,keyEncipherment" -addext "extendedKeyUsage=serverAuth"
```

> [!IMPORTANT] A requsiição de assinatura do servidor deve ser criada com o common name sendo o nome do servidor, subject alternative name sendo o nome do servidor como dns e o ip do servidor como ip além de key usage critical, digital signature e key encipherment e extended key usage server auth.

5. Assinar certificado do servidor com a autoridade certificadora:

```bash
openssl x509 -req -in <nome da requisição>.csr -CA <certificado da autoridade certificadora>.pem -CAkey <chave da autoridade certificadora>.pem -CAcreateserial -out <nome do certificado>.pem -sha256 -extfile <(echo "subjectAltName=DNS:servidor.minha-ca.com.br,IP:192.168.1.100")
```

> [!IMPORTANT] O certificado do servidor deve ser gerado a partir de uma requisição de assinatura utilizando o certificado e chave da autoridade certificadora para assinar esse certificado. Além disso, ja deve ser passado o subject alternative name sendo o nome do servidor como dns e o ip do servidor como ip.

O mesmo processo do servidor deve ser feito para o cliente.

## ✅ Como usar

Executar o apirest passando o arquivo de configuração como parâmetro:

```bash
./apirest -c conf/APIRest.properties
```

