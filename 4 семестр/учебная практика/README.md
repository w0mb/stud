тут работа на 5, но лучше сдавать main3.py(тк там проще защитить будет, хз как хотите)

установка под wsl:

sudo apt-get install python  (в терминал wsl vs code)
sudo apt install python3-pip  (в терминал wsl vs code)
pip3 install requests  (в терминал wsl vs code)
pip3 install bs4  (в терминал wsl vs code)
pip3 install silenium (в терминал wsl vs code)

запуск  (пишем в терминал wsl):

python3 main.py






установка под винду:

https://www.python.org/downloads/
устанавливаем расширение питона под vs code
pip3 install bs4  (в терминал powershell vs code)
pip3 install requests  (в терминал powershell vs code)
pip3 install silenium (в терминал powershell vs code)

код ранером запускаем






ввод
f - читать из файла 
w - читать с веб страницы

если читаем из файла - в конце предложит поиск по названию крипты


если парсим веб - будет от 4 до 6 хуйовых запросов, скорее всего это зависит от скорости работы гугла и интернета
бтв парсинг работает только с гугла 
после вывода будет предложен поиск. если ниче не вводим код снова пойдет парсить(поэтому придется подождать)

код работает только на винде из-за специфики путей проводника( типа "\\" на винде и "/" на линуксах) - если ставим на линукс меняем open(path.join(path.dirname(file), FILE_NAME), 'r') as file эту строку.