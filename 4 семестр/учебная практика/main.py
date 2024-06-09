import csv
import time
from os import path
from selenium import webdriver
from selenium.common.exceptions import WebDriverException
from bs4 import BeautifulSoup

FILE_NAME = "currencies24.csv"
URL = "https://coinmarketcap.com/"
SCROLL_PAUSE_TIME = 2
RECORD_LIMIT = 10

S_BOLD = "\033[1m"
S_RESET = "\033[0m"

C_RED = "\033[31m"
C_GREEN = "\033[32m"
C_YELLOW = "\033[33m"
C_CYAN = "\033[36m"

def get_element_details(element):
    return {
        "name": element.select('td')[2].select('.hide-ranking-number > p')[0].text.strip() or '',
        "symbol": element.select('td')[2].select('.coin-item-symbol')[0].text.strip() or '',
        "price": element.select('td')[3].text.strip() or '',
        "capital": element.select('td')[7].select('span')[1].text.strip() or ''
    }

def parse_web_data(driver):
    parsed_data = []
    for page_number in range(1, 2):
        i = 1
        screen_height = driver.execute_script("return window.screen.height;")
        driver.get(f"https://coinmarketcap.com/?page={page_number}")
        time.sleep(10)

        while True:
            driver.execute_script(f"window.scrollTo(0, {screen_height * i});")
            i += 1
            time.sleep(SCROLL_PAUSE_TIME)

            scroll_height = driver.execute_script("return document.body.scrollHeight;")
            if screen_height * i > scroll_height or i > RECORD_LIMIT:
                break

        html = BeautifulSoup(driver.page_source, "html.parser")

        for element in html.select('.cmc-table > tbody > tr')[:RECORD_LIMIT]:
            item = get_element_details(element)
            parsed_data.append(item)

    return parsed_data

def parse_file_data():
    data = []
    try:
        with open(path.join(path.dirname(__file__), FILE_NAME), 'r') as file:
            reader = csv.reader(file, delimiter=',')

            for row in reader:
                if len(row) == 4:
                    item = {
                        "name": row[0],
                        "symbol": row[1],
                        "price": row[2],
                        "capital": row[3]
                    }
                    data.append(item)
                else:
                    print(C_RED + S_BOLD + "Ошибка! Некорректная структура строки в файле CSV.")
                    print("Строка должна содержать имя, символ, цену и рыночную капитализацию.")
                    print(S_RESET)
                    exit()

    except FileNotFoundError:
        print(C_RED + S_BOLD + f"Ошибка! Файл \'{FILE_NAME}\' не обнаружен!")
        print(S_RESET)
        exit()

    return data

def find_by_name(data, search_string):
    items = []
    for item in data:
        if item.get("name", "").upper().startswith(search_string.upper()):
            items.append(item)
    return items

def print_data(data):
    print(S_BOLD + C_GREEN)
    print(f"{'Название':35}  {'Символ':>25}    {'Цена':>15}     {'Рын.Кап':>25}")
    print(C_CYAN)
    for item in data:
        print(f"{item['name']:35}  {item['symbol']:>25}    {item['price']:>15}  {item['capital']:>25}")
    print(C_YELLOW)
    print("Кол-во элементов: ", len(data))
    print(S_RESET)

def main():
    data = []

    print("Считать данные из...")
    while True:
        choice = input("[F]ile|[W]eb: ").upper()
        if choice not in ['F', 'W']:
            print(C_RED + "Ошибка! Некорректный ввод!" + S_RESET)
        else:
            break

    if choice == 'F':
        data = parse_file_data()
        print_data(data)
    elif choice == 'W':
        try:
            driver = webdriver.Chrome()
        except WebDriverException as e:
            print(C_RED + S_BOLD + "Ошибка при создании драйвера Chrome:", e)
            print(S_RESET)
            exit()

        data = parse_web_data(driver)
        print_data(data)

    while True:
        search_string = input("Введите строку для поиска криптовалюты: ")
        found = find_by_name(data, search_string)
        if found:
            print_data(found)
        else:
            print(C_RED + "Криптовалюты не найдены!" + S_RESET)

        print("\n\nПовторить поиск?")
        while True:
            choice = input("[Y]es|[N]o: ").upper()
            if choice not in ['Y', 'N']:
                print(C_RED + "Ошибка! Некорректный ввод!" + S_RESET)
            else:
                break

        if choice == 'N':
            break

if __name__ == '__main__':
    main()
