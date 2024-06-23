wifi.setmode(wifi.STATION)
wifi.sta.config {ssid="NOME_DO_SEU_WI-FI", pwd="SENHA_DO_WI-FI"}

tmr.alarm(0, 1000, 1, function() --Aguarda o esp conectar na rede
    if wifi.sta.getip() == nil then
        print("Conectando à rede...\n")
    else
        ip=wifi.sta.getip()
        print("IP: ",ip)
        tmr.stop(0)
    end
end)

srv=net.createServer(net.TCP)
srv:listen(80, function(conn)
    conn:on("receive",function(client,payload)
        print(payload)

        client:send("<head><meta http-equiv='refresh' content='1'></head>") --Atualiza a página a cada 1s
        client:send("<h1>Recebendo dados da porta analógica</h1>")
        client:send("<p>Valor da porta analógica:</p>")
        client:send(adc.read(0)) --Envia o valor do sensor
        client:send("<p>A página é atualizada sozinha</p>")

        client:on("sent", function(conn) conn:close() end) --Finaliza a conexão
    end)
end)