
# Задание

## Запуск
После того, как произведен ```build```, выполнить:
```bash
display_server.exe <display_port>
data_processor.exe "<display_ip>" <processor_port> <display_port>
client.exe "<server_ip>" <processor_port>
```

Например:
```bash
display_server.exe 54002
data_processor.exe "127.0.0.1" 54001 54002
client.exe "127.0.0.1" 54001
```


## Запуск тестов
```bash
DataProcessorTests.exe
```
