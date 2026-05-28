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

### 🛆 CMake

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

> [!NOTE]
> A chave e o vetor de inicialização podem ser obtidos no arquivo test_package/src/UnitTests/include/APIRestServerTestMacros.h

3. Criar o projeto utilizando conan:

    ```bash
    conan create . --build=missing
    ```

> [!NOTE]
> O comando acima vai baixar e compilar todas as dependencias, compilar o projeto e executar os testes que é composto de 1 executáveil que faz os testes unitários.

## 🔩 Pipeline
Ao criar uma tag, duas pipelines são disparadas via github para gerar a release automaticamente e para publicar o pacote no repositório do conan (cloudsmith).

## Configuração

O arquivo de configuração é gerado durante a compilação no diretório conf/APIRest.properties e é composto por algumas chaves que definem o comportamento do servidor REST.

### Chaves de configuração

O nível de log pode ser definido com os valores none, fatal, critical, error, warning, notice, information, debug, trace através da seguinte configuração:

```
logging.loggers.root.level = debug
```

Sendo que none desativa o log e trace é a informação mais detalhada possível.

O canal de log é definido através da seguinte chave de configuração:

```
logging.loggers.root.channel = splitter
```

As seguintes chaves correspondem a definição do tipo de formatter e o padrão utilizado pelo formatter:

```
logging.formatters.patternformatter.class = PatternFormatter
logging.formatters.patternformatter.pattern = %Y-%m-%d %H:%M:%S.%i [%p] - %s - %t
```

Para definir e configurar os canais os canais de log, é necessário utilizar as chaves correspondentes a seguinte:

```
logging.channels.<nome do canal>.*
```

Deve ser definido o tipo e suas configurações. O canal definido deve ser associado ao log principal.

O diretório onde os arquivos recebidos pelo servidor serão salvos deve ser definido na seguinte chave:

```
apirest.upload.dir = /tmp/apirest/uploads
```

As seguintes chaves correspondem ao caminho para o arquivo PKCS12 utilizado pelo servidor para fazer uma verificação rigorosa da conexão e a senha para acesso ao conteúdo desse arquivo:

```
apirest.pkcs12.path = 
apirest.pkcs12.password.aes.256.cbc.base64 = 
```

A senha deve ser criptografada a seção 2 dos [Passos para a compilação](#-passos-para-a-compilação).
O arquivo PKCS 12 deve ser gerado seguindo os passos a seguir:

### Gerar arquivo PKCS12

Gerar chave privada da autoridade certificadora:

```bash
openssl genrsa -out ca-key.pem 4096
```

Gerar certificado da autoridade certificadora:

```bash
openssl req -new -x509 -days 3650 -keyout ca-key.pem -out ca-cert.pem -subj "/C=BR/ST=Sao Paulo/L=Sao Paulo/O=Minha Organizacao/CN=minha-ca.com.br" -addext "basicConstraints=critical,CA:TRUE" -addext "keyUsage=critical,keyCertSign,cRLSign" -addext "subjectAltName=DNS:minha-ca.com.br,IP:192.168.1.1"
```

Gerar chave privada do servidor:

```bash
openssl genrsa -out server-key.pem 4096
```

Gerar requisição de assinatura do servidor:

```bash
openssl req -new -keyout server-key.pem -out server.csr -subj "/C=BR/ST=Sao Paulo/L=Sao Paulo/O=Minha Organizacao/CN=servidor.minha-ca.com.br" -addext "subjectAltName=DNS:servidor.minha-ca.com.br,IP:192.168.1.100" -addext "keyUsage=critical,digitalSignature,keyEncipherment" -addext "extendedKeyUsage=serverAuth"
```

Assinar certificado do servidor com a autoridade certificadora:

```bash
openssl x509 -req -in server.csr -CA ca-cert.pem -CAkey ca-key.pem -CAcreateserial -out server-cert.pem -days 365 -sha256 -extfile <(echo "subjectAltName=DNS:servidor.minha-ca.com.br,IP:192.168.1.100")
```

O mesmo processo do servidor deve ser feito para o cliente.

## ✅ Como usar

Executar o apirest passando o arquivo de configuração como parâmetro:

```bash
./apirest -c conf/APIRest.properties
```

