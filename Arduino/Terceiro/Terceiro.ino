#include <ESP8266WiFi.h> //INCLUSÃO DA BIBLIOTECA NECESSÁRIA PARA FUNCIONAMENTO DO CÓDIGO

wifi.setmode(wifi.STATION)
wifi.sta.config({ssid="ALGAR_Torres2023", pwd="t0rres!001"})

tmr.alarm(0, 1000, 1, function() --Aguarda o esp conectar na rede
   if wifi.sta.getip() == nil then
      print("Conectando à rede...\n")
   else
      ip=wifi.sta.getip()
      print("IP: ",ip)
      tmr.stop(0)
   end
end)


srv = net.createServer(net.TCP)

srv:listen(80,function(conn)
    conn:on("receive", function(client, payload)

        local _line       --Variavel para leitura das linhas
        if file.open("index.html","r") then --Se abrir o arquivo corretamente
        repeat
            _line = file.readline() --Lê a linha
            if (_line~=nil) then  --Se não for nula, envia os dados
               client:send(string.sub(_line,1,-2))  --ignora o pulador de linha
            end
        until _line==nil --Repete até a ultima linha do arquivo
        file.close() --Termina a leitura do arquivo
        end
       
        client:on("sent", function(conn) conn:close() end)
    end)
end)