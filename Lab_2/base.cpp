#include "base.h"
#include "listmedal.h"
#include "aes.h"
#include <QDebug>
#include <QString>
#include <QFile>
#include <QJsonParseError>
#include <QJsonObject>
#include <QCryptographicHash>
#include <QtWidgets/QApplication>
#include <QtGui/QClipboard>
#include <QDesktopServices>
#include <QJsonArray>
#include <QSaveFile>

//Конструктор класса
base::base(QObject *QMLObject) : viewer(QMLObject)
{
    modal = new listModal();
}

//Расшифровываем первый слой шифрования
bool base::parsing(QString pin, QString searchSubstring){ //Парсинг файла
    QFile file(":/asserts/file.txt");
    if( file.open( QIODevice::ReadOnly ) )
    {
        QByteArray bytes = file.readAll(); //Достаем все содержимое файла
        file.close();

        QAESEncryption encryption(QAESEncryption::AES_256, QAESEncryption::CBC); // Шифровальщик и алгоритм шифрования
        QString pincode(pin); // Ключ
        QString inicialize_vector(pin); // Инициализирующий вектор
        QByteArray hash_pincode = QCryptographicHash::hash(pincode.toLocal8Bit(), QCryptographicHash::Sha256); // Хэш ключа (алгоритм вычисления хэша)
        QByteArray hash_inicialize_vector = QCryptographicHash::hash(inicialize_vector.toLocal8Bit(), QCryptographicHash::Md5); // Хэш иниц вектора (алгоритм вычесления хэша)
        QByteArray decoding = encryption.decode(bytes, hash_pincode, hash_inicialize_vector); // Расшифровка содержимого файла
        QByteArray string = encryption.removePadding(decoding);// Удаление мусора после шифрования
        qDebug() << decoding;
        bytes = string;





        QJsonParseError Error;
        QJsonDocument document = QJsonDocument::fromJson( bytes, &Error );
        if( Error.error != QJsonParseError::NoError ) // Не удачный парсинг
        {
            qDebug() << Error.errorString();
            return false;
        }
        else if(document.isObject()) // удачный парсинг
        {
            QJsonObject object = document.object();
            QJsonValue record = object.value("records"); // Берем рекордс из файла
            QJsonArray array = record.toArray(); // Преобразуем его в массив
            if (modal->rowCount() > 0) { // Если массив пустой = возврат пустой массив
                modal->clear();
            }
            for(int i = 0; i < array.count(); i++){ // Если массив не пустой перебираме каждый его элемент
                QJsonObject List = array.at(i).toObject(); // берем объекит и поля (ниже)
                QString picture = List.value("img").toString();
                QString url = List.value("url").toString();
                QString login = List.value("login").toString();
                QString password = List.value("password").toString();

                //                QUrl photo = list.value("password").toString();
                //                qDebug() << photo;
                if (url.contains(searchSubstring))
                    modal->addItem(list(picture, url, login, password)); // Создаем запись с параметрами из файла и дабавляем ее в массив записей
            }
        }
    }
    return true;
}




// Расшифровываем второй слой шифрования
void base::cryptCopy(int index, QString parametr, QString pin){ //Param содержит входной параметр для расшифровки (логин или пароль)
    QString data = modal->get(index).take(parametr).toString(); //Достаем из модели объект (record) в котором нужное нам поле для расшифровки (логин и пароль)

    // тоже самое что и в первой функции
    QAESEncryption encryption(QAESEncryption::AES_256, QAESEncryption::CBC);
    QString pincode(pin);
    QString inicialize_vector(pin);
    QByteArray hash_pincode = QCryptographicHash::hash(pincode.toLocal8Bit(), QCryptographicHash::Sha256);
    QByteArray hash_inicialize_vector = QCryptographicHash::hash(inicialize_vector.toLocal8Bit(), QCryptographicHash::Md5);



//  QByteArray encodeText = encryption.encode(data, hashKey, hashIV);
    QByteArray decoding = encryption.decode(data.toLocal8Bit(), hash_pincode, hash_inicialize_vector);// Расшифровка логина или пароля
    QString string = QString(encryption.removePadding(decoding)); // Удаление мусора после расшифровки

    QApplication::clipboard()->setText(string); //Коперууем расшифрованный логин или пароль


// Функция создания зашифрованного изначального файла


//    QFile file1(":/asserts/test_file.txt");
//    file1.open(QIODevice::ReadOnly);
//    QByteArray bytes = file1.readAll();
//    file1.close();

//    QByteArray encodeText = encryption.encode(bytes, hashKey, hashIV);
//    QByteArray decodeText = encryption.decode(encodeText, hashKey, hashIV);
//    QString decodedString = QString(encryption.removePadding(decodeText));
//    QFile file("C:\\file.txt");
//    file.open(QIODevice::WriteOnly);
//    file.write(encodeText);
//    file.close();
}


