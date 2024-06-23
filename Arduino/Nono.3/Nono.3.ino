////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Arquivo:   Nono.3.ino
//Tipo:      Codigo-fonte para utilizar no NodeMCU atraves da IDE do Arduino
//Autor:     Pedro Otávio Sampaio Torres
//Descricao: Projeto integrador 
////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <ESP8266WiFi.h>

const char* ssid = "ALGAR_Torres2023"; //VARIÁVEL QUE ARMAZENA O NOME DA REDE SEM FIO EM QUE VAI CONECTAR
const char* password = "t0rres!001"; //VARIÁVEL QUE ARMAZENA A SENHA DA REDE SEM FIO EM QUE VAI CONECTAR

//IP do ESP (para voce acessar pelo browser - voce TEM que mudar este IP tambem)
IPAddress ip(192, 168, 10, 50);

IPAddress gateway(192, 168, 10, 114);//IP do roteador da sua rede wifi

//Mascara de rede da sua rede wifi
IPAddress subnet(255, 255, 255, 0);

WiFiServer server(80); //Criando o servidor web na porta 80

const int pinb = 0; //Pino do NodeMCU que estara conectado ao LED
const int pina = 2; //Pino do NodeMCU que estara conectado ao LED

void setup() {
  //Preparando o pino, que esta lidago ao rele
  pinMode(pinb, OUTPUT);
  digitalWrite(pinb, HIGH);
  pinMode(pina, OUTPUT);
  digitalWrite(pina, HIGH);

  Serial.begin(115200); //INICIALIZA A SERIAL
  delay(10); //INTERVALO DE 10 MILISEGUNDOS

  Serial.println(""); //PULA UMA LINHA NA JANELA SERIAL
  Serial.println(""); //PULA UMA LINHA NA JANELA SERIAL
  Serial.print("Conectando a "); //ESCREVE O TEXTO NA SERIAL
  Serial.print(ssid); //ESCREVE O NOME DA REDE NA SERIAL

  //Conectando a rede Wifi
  WiFi.config(ip, gateway, subnet);
  WiFi.begin(ssid, password); //PASSA OS PARÂMETROS PARA A FUNÇÃO QUE VAI FAZER A CONEXÃO COM A REDE SEM FIO

  //Verificando se esta conectado,
  //caso contrario, espera um pouco e verifica de novo imprime um  ponto.
  while (WiFi.status() != WL_CONNECTED) { //ENQUANTO STATUS FOR DIFERENTE DE CONECTADO
    delay(500); //INTERVALO DE 500 MILISEGUNDOS
    Serial.print("."); //ESCREVE O CARACTER NA SERIAL
  }
  
  Serial.println(""); //PULA UMA LINHA NA JANELA SERIAL
  Serial.print("Conectado a rede sem fio "); //ESCREVE O TEXTO NA SERIAL
  Serial.println(ssid); //ESCREVE O NOME DA REDE NA SERIAL
  server.begin(); //INICIA O SERVIDOR WEB PARA RECEBER DADOS NA PORTA DEFINIDA EM "WiFiServer server(porta);"
  Serial.println("Servidor iniciado"); //ESCREVE O TEXTO NA SERIAL

  Serial.print("IP para se conectar ao NodeMCU: "); //ESCREVE O TEXTO NA SERIAL
  Serial.print("http://192, 168, 10, 50"); //ESCREVE O TEXTO NA SERIAL
  //Serial.println(WiFi.localIP()); //ESCREVE NA SERIAL O IP RECEBIDO DENTRO DA REDE SEM FIO (O IP NESSA PRÁTICA É RECEBIDO DE FORMA AUTOMÁTICA)
}
 
 

//Funcao que sera executada indefinidamente enquanto o NodeMCU estiver ligado.
void loop() {
  //Verificando se o servidor esta pronto.
  WiFiClient client = server.available(); //VERIFICA SE ALGUM CLIENTE ESTÁ
  if (!client) { //SE NÃO EXISTIR CLIENTE CONECTADO, FAZ
    return; //REEXECUTA O PROCESSO ATÉ QUE ALGUM CLIENTE SE CONECTE AO
  }
  
  Serial.println("Novo cliente se conectou!"); //ESCREVE O TEXTO NA SERIAL

  //Verificando se o servidor recebeu alguma requisicao
  while (!client.available()) {
    delay(1);
  }

  //Obtendo a requisicao vinda do browser
  String req = client.readStringUntil('\r');
  
  //Sugestao dada por Enrico Orlando
  if(req == "GET /favicon.ico HTTP/1.1"){
      req = client.readStringUntil('\r');
  }
  Serial.println(req); //ESCREVE A REQUISIÇÃO NA SERIAL
  client.flush(); //AGUARDA ATÉ QUE TODOS OS DADOS DE SAÍDA SEJAM ENVIADOS

  //Iniciando o buffer que ira conter a pagina HTML que sera enviada para o browser.
  String buf = "";

  buf += "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\n";
  buf += "<head> ";
 
  buf += "<meta charset='UTF-8'> ";
  buf += "<meta http-equiv='cache-control' content='max-age=0' /> ";
  buf += "<meta http-equiv='cache-control' content='no-cache' /> ";
  buf += "<meta http-equiv='expires' content='0' /> ";
  buf += "<meta http-equiv='expires' content='Tue, 01 Jan 1980 1:00:00 GMT' /> ";
  buf += "<meta http-equiv='pragma' content='no-cache' /> ";
  
  buf += "<title>Projeto Integrador</title> ";
 
buf += "<style> ";
  buf += "body{font-family:Open Sans; color:#555555;} ";
  buf += "h1{font-size:24px; font-weight:normal; margin:0.4em 0;} ";
  buf += ".container { width: 100%; margin: 0 auto; } ";
  buf += ".container .row { float: left; clear: both; width: 100%; } ";
  buf += ".container .col { float: left; margin: 0 0 1.2em; padding-right: 1.2em; padding-left: 1.2em; } ";
  buf += ".container .col.four, .container .col.twelve { width: 100%; } ";
  buf += "@media screen and (min-width: 767px) { ";
  buf += ".container{width: 100%; max-width: 1080px; margin: 0 auto;} ";
  buf += ".container .row{width:100%; float:left; clear:both;} ";
  buf += ".container .col{float: left; margin: 0 0 1em; padding-right: .5em; padding-left: .5em;} ";
  buf += ".container .col.four { width: 50%; } ";
  buf += ".container .col.tweleve { width: 100%; } ";
  buf += "} ";
  buf += "* {-moz-box-sizing: border-box; -webkit-box-sizing: border-box; box-sizing: border-box;} ";
  buf += "a{text-decoration:none;} ";
  buf += ".btn {font-size: 18px; white-space:nowrap; width:100%; padding:.8em 1.5em; font-family: Open Sans, Helvetica,Arial,sans-serif; ";
  buf += "line-height:18px; display: inline-block;zoom: 1; color: #fff; text-align: center; position:relative; ";
  buf += "-webkit-transition: border .25s linear, color .25s linear, background-color .25s linear; ";
  buf += "transition: border .25s linear, color .25s linear, background-color .25s linear;} ";
  buf += ".btn.btn-sea{background-color: #08bc9a; border-color: #08bc9a; -webkit-box-shadow: 0 3px 0 #088d74; box-shadow: 0 3px 0 #088d74;} ";
  buf += ".btn.btn-sea:hover{background-color:#01a183;} ";
  buf += ".btn.btn-sea:active{ top: 3px; outline: none; -webkit-box-shadow: none; box-shadow: none;} ";
  buf += "</style> ";
 
  buf += "</head> ";
  buf += "<body> ";
 
  buf += "<div class='container'> ";
  
  buf += "<div class='row'> ";
  buf += "<div class='col twelve'> ";
  buf += "<p align='center'><font size='10'>Controle do Sistema</font></p> ";
  buf += "</div> ";
  buf += "</div> ";
  
  buf += "<div class='row'> ";
  
  buf += "<div class='col four'> ";
  buf += "<a href='?f=onb' class='btn btn-sea'>Ligar Bomba</a> ";
  buf += "</div> ";
  
  buf += "<div class='col four'> ";
  buf += "<a href='?f=offb' class='btn btn-sea'>Desligar Bomba</a> ";
  buf += "</div> ";
  buf += "</div> ";
 
  buf += "<div class='row'> "; //INCLUI DAQUI
  
  buf += "<div class='col four'> ";
  buf += "<a href='?f=ona' class='btn btn-sea'>Ligar Aquecedor</a> ";
  buf += "</div> ";
  
  buf += "<div class='col four'> ";
  buf += "<a href='?f=offa' class='btn btn-sea'>Desligar Aquecedor</a> ";
  buf += "</div> ";
  buf += "</div> ";  //ATÉ AQUI
  
  buf += "<div class='col twelve'> ";
  buf += "<p align='center'><font size='5'>Controlando pelo WIFI</font></p> ";
  buf += "</div> ";
  buf += "</div> ";
  buf += "</body> ";
  buf += "</html> ";

  //Enviando para o browser a 'pagina' criada.
  client.print(buf);
  client.flush();

  //Analisando a requisicao recebida para decidir se liga ou desliga a lampada
  if (req.indexOf("offb") != -1)
  {
    digitalWrite(pinb, LOW);
  }
  else if (req.indexOf("onb") != -1)
  {
    digitalWrite(pinb, HIGH);
  }
  else if (req.indexOf("ona") != -1) // DAQUI
  {
    digitalWrite(pina, HIGH);
  }
  else if (req.indexOf("offa") != -1)
  {
    digitalWrite(pina, LOW);
  } //AQUI
  
  else
  {
    //Requisicao invalida!
    client.stop();
  }
}
