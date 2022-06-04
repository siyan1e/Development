#include "listmedal.h"
#include <QMap>
#include <QDebug>


list::list(const QString &getPicture, const QString &getUrl, const QString &getLogin, const QString &getPassword)
    :   p_picture(getPicture),
        p_url(getUrl),
        p_login(getLogin),
        p_password(getPassword)
{
 //
}

listModal::listModal(QObject *parent) : QAbstractListModel(parent)
{
    //пусто
}

QString list::getPicture() const{ // функция для получения имени друга
    return p_picture;
}

QString list::getUrl() const{ // функция для получения фамилии друга
    return p_url;
}

QString list::getLogin() const{ // функция для получения фото друга
    return p_login;
}

QString list::getPassword() const{ // функция для получения id друга
    return p_password;
}

void listModal::addItem(const list & newItem){
    // не изменяется
  // благодаря beginInsertRows() и endInsertRows() QML реагирует на изменения модели
    //ЧАСТЬ сигнальной системы уведомлений qml об изменениях модели и переде  в qml на какую позицию и сколько элементов вставляется
    beginInsertRows(QModelIndex(), //по умолчанию
                    rowCount(), //номер строки вставки
                    rowCount());// номер строки концу вставляемого участка
    p_items << newItem;// вставка нового элемента данных
    // сообзает listview о том что изменение модели закончено и можно обновить
    endInsertRows();
}

int listModal::rowCount(const QModelIndex &parent) const
{
    // не изменяется
   // метод используется ListView в QML для определения числа элементов
    Q_UNUSED(parent); // макрос который скрыввает сообзение qt о тоом что параметр не использется
    return p_items.count(); //возвращает кол во элементов в списке
}

QVariant listModal::data(const QModelIndex & index,
                                int role) const
{
     // метод используется в QML для получения значения одного поля под обозначением role одного элемента модели index
    //проверка на поппадание в список
    if (index.row() < 0 || (index.row() >= p_items.count()))
        return QVariant();//обертка

  //получение ссылки на обьект с нужным индексом
    const list&itemToReturn = p_items[index.row()];
    //получение значения нужного поля выбранного обьекта
    if (role == Picture)
    return itemToReturn.getPicture(); //при любом return этой функции значение преобразуется в QVariant
    else if (role == URL)
    return itemToReturn.getUrl();
    else if (role == Login)
    return itemToReturn.getLogin();
    else if (role == Password)
    return itemToReturn.getPassword();

    return QVariant();
}

QHash<int, QByteArray> listModal::roleNames() const
{
    // метод используется в QML для сопоставления полей данных со строковыми названиями
     // TODO сопоставить полям данных строковые имена
    //метод отвечает за конвертацию за заполнение словаря "стрококвое_имя":роль
    QHash<int, QByteArray> roles;//обьяляется хэш таблица

    roles[Picture] = "picture"; // строка будет в таком виде выхываться в qml
    roles[URL] = "url";
    roles[Login] = "login";//
    roles[Password] = "password";//
    return roles;
}

QVariantMap listModal::get(int idx) const
{
    // не изменяется
   // метод используется ListView в QML для получения значений полей idx-го элемента модели
    //формирует выгрузку всех полей элемента списка под номером idx
    //QVariantMap {"роль":"значение"}
    QVariantMap map; //словарь
    foreach(int k, roleNames().keys())
    {
        map[roleNames().value(k)] = data(index(idx, 0), k);//выгружаются данные  слвать
    }
    return map;//
}

void listModal::clear()
{
    beginRemoveRows(QModelIndex(), 0, rowCount()-1);//аналагичнов в additem
    p_items.clear();//сообственно удаление элементов списка
    endRemoveRows();
}









