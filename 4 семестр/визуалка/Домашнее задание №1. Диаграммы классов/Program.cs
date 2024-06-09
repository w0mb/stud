using System;
using System.Collections.Generic;
//интерфейс для уведомлений
public interface INotifyer
{
    void Notify(decimal balance);
}

//класс уведомления по SMS при низком балансе
public class SMSLowBalanceNotifyer : INotifyer
{
    private string _phone;
    private decimal _LowBalanceValue;

    public SMSLowBalanceNotifyer(string phone, decimal lowBalanceValue)// конструктор принимает телефон и порог низкого баланса
    {                                                                  // инициализируя класс соответствующими параметрами
        _phone = phone;
        _LowBalanceValue = lowBalanceValue;
    }

    public void Notify(decimal balance)
    {
        if (balance <= _LowBalanceValue)
        {
            Console.WriteLine($"SMSLowBalanceNotifyer: уведомляю пользователя с телефоном {_phone}. низкий уровень деняг: {balance}\n");
        }
    }
}

//уведомления по электронной почте при изменении баланса
public class EMailBalanceChangedNotifyer : INotifyer
{
    private string _email;

    public EMailBalanceChangedNotifyer(string email)
    {
        _email = email;
    }

    public void Notify(decimal balance)
    {
        Console.WriteLine($"EMailBalanceChangedNotifyer: уведомляю пользователя с емайлом {_email}. новый баланс: {balance} \n");
    }
}

//аккаунта пользователя
public class Account
{
    private decimal _balance; //баланс прайват, собственно и лист нотифаеров тоже прайват
    private List<INotifyer> _notifyers; //лист нотифаеров

    public Account() //конструктор с балансом 0(все равно он не дефолтный)
    {
        _balance = 0;
        _notifyers = new List<INotifyer>();
    }

    public Account(decimal initialBalance)//конструктор с переданным балансом
    {
        _balance = initialBalance;
        _notifyers = new List<INotifyer>();
    }

    public void AddNotifyer(INotifyer notifyer)//в лист уведомов добавляем уведом, типа INotifyer
    {
        _notifyers.Add(notifyer);
    }

    public void ChangeBalance(decimal value) //метод изменния баланса, нечего сказать больше, разве что вызываем доступный
    {                                        //только в этом классе метод Notification
        if (value != _balance)
        {
            _balance = value;
            Notification();
        }
    }

    public decimal Balance
    {
        get
        {
            return _balance;
        }
    }

    private void Notification()
    {
        for (int i = 0; i < _notifyers.Count(); i++)
        {
            _notifyers[i].Notify(_balance); //выражение агрегации, т.е. лист уведомов юзает метод из других классов,
        }                                   //которые являются наследниками нужного нам класса по диаграмме (INotifyer)
    }
}

class Program
{
    static void Main()
    {
        decimal lowBalance = 0.1M;
        decimal newBalance = 3;
        Account userAccount = new Account(newBalance); //касарь на балансе
                                                       // а ЕЩЁ создается лист типа акаунт, а акаунт в свою очередь -> decimal


        SMSLowBalanceNotifyer smsNotifyer = new SMSLowBalanceNotifyer("89231686797", lowBalance);
        EMailBalanceChangedNotifyer emailNotifyer = new EMailBalanceChangedNotifyer("danil-kovalev-04@mail.ru");

        //таким образом можем сделать еще всякие уведомы, главное чтобы они имели тип INotifyer

        userAccount.AddNotifyer(emailNotifyer);
        userAccount.AddNotifyer(smsNotifyer);
        //userAccount.AddNotifyer(domophoneNotifyer) можно? НУЖНО!

        Console.WriteLine("привет, ты подписан на 2 уведомления: емайл и по номеру телефона \n");

        Console.WriteLine($"привет, твой текущий баланс: {newBalance} \n");

        Console.WriteLine("привет, за подписку на яндекс музыку у тебя снялось 2.9р \n");

        userAccount.ChangeBalance(0.1M);

        Console.WriteLine("привет, пришло зп \n");

        userAccount.ChangeBalance(20);
    }
}
