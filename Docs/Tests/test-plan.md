# План тестирования

### Введение

Данный план описывает тестирование клиентского приложения "VK Desk" для социальной сети «ВКонтакте» под ОС Windows.

Требования, предъявляемые к тестировщику:

* умение пользоваться устройством под управлением операционной системы Windows(далее компьютер).

### Объекты тестирования

* Приложение для операционной системы Windows для социальной сети «ВКонтакте».

Атрибуты качества приложения по ISO 25010:

* функциональность
  * функциональная полнота: приложение должно выполнять все возложенные на нее функции
  * функциональная корректность: приложение должно выполнять все возложенные на нее функции корректно
* производительность
  * временная характеристика: приложение должно открываться не медленнее чем за 30 секунд
* практичность
  * защита от ошибок пользователей: приложение должно выводить сообщения об ошибках если пользователь произвел некорректное действие
* надежность
  * доступность: приложение должно работать при автономной работе компьютера не менее 24 часов
* приложение должно работать при наличии интернет-соединения

### Риски

При высокой частоте запросов приложения к API ВКонтакте возможно некорректное отображение данных или исключение «Too many requests per second» отображаемое в отдельном окне. При возникновении исключения рекомендуется перезапустить приложение. 
При низкой скорости интернета низкая производительность приложения.

### Аспекты тестирования

* авторизация;
* отображение друзей текущего пользователя с возможностью перехода на их страницы; 
* отображение друзей онлайн текущего пользователя с возможностью
перехода на их страницы;
* получение и отправка сообщений в режиме реального времени;
* отображение диалога с пользователем;
* отображение времени отправки сообщений;
* отображение записей на стене пользователя, а именно:
	- текст;
	- фотографии;
* отображение записей на стене, содержащих репост, а именно:
	- текст;
	- фотографии;
* отображение времени создания записи на стене;
* отображение общей и контактной информации о пользователях;
* отображение статусов пользователей;
* отображение состояния пользователей – онлайн/последняя активность;
* отображение основных фотографий пользователей;
* быстрый переход на домашнюю страницу;
* оповещение о получении новых сообщений;

### Подходы к тестированию

Для тестирования необходим компьютер под управлением операционной системы Windows версии 8.0 и выше.

### Представление результатов

Предоставление результатов требуется описать в следующем виде:

1. Идентификатор
2. Назначение / название
3. Сценарий
4. Ожидаемый результат
5. Фактический результат (заполняется на этапе тестирования)
6. Оценка (заполняется на этапе тестирования)

Тестовые сценарии:

#### Авторизация

1. 001

2. Возможность авторизации

3. Произведите следующие шаги:

   1. Запустите приложение.

   2. Нажмите на кнопку "Войти".

   3. Введите Телефон или email и пароль.

   4. Нажмите на кнопку «Войти».

4. Приложение произведет авторизацию в соцсети «ВКонтакте» и отобразит домашнюю страницу текущего пользователя.

#### Отображения друзей текущего пользователя с возможностью перехода на их страницы

1. 002
2. Проверка отображения друзей текущего пользователя с возможностью перехода на их страницы
3. Произведите следующие шаги:

   1. Запустите приложение и авторизуйтесь (т.с. 001).

   2. Слева отобразится список друзей текущего пользователя.

   3. Выберите контакт в списке друзей и нажмите левой клавишей мыши.

4. Отобразится страница выбранного пользователя.

####  Отображение друзей онлайн текущего пользователя с возможностью перехода на их страницы

1. 003
2. Проверка отображения друзей онлайн текущего пользователя с возможностью
перехода на их страницы
3. Произведите следующие шаги:

   1. Запустите приложение и авторизуйтесь (т.с. 001).

   2. Слева отобразится список друзей текущего пользователя. Друзья онлайн будут отмечены зеленым цветом.

   3. Выберите контакт в списке друзей и нажмите левой клавишей мыши.
4. Отобразится страница выбранного пользователя.

#### Получение и отправка сообщений в режиме реального времени

1. 004
2. Проверка получения и отправки сообщений в режиме реального времени
3. Произведите следующие шаги:

   1. Запустите приложение, авторизуйтесь (т.с. 001) и перейдите на страницу нужного пользователя (т.с. 002).

   2. Нажмите на кнопку "К диалогу".

   3. В появившемся окне, отображающем историю переписки, введите сообщение в поле ввода.

   4. Нажмите кнопку отправить или клавишу Enter.

   5. Отправленное сообщение отобразится в истории переписки.

   6. При получении сообщения оно отобразится в истории переписки.

4. Отправленные или полученные сообщения должны отображаться в истории переписки в хронологическом порядке.

#### Отображение диалога с пользователем;

1. 005
2. Проверка отображения диалога с пользователем;
3. Произведите следующие шаги:

   1. Запустите приложение, авторизуйтесь (т.с. 001), перейдите на страницу необходимого пользователя (т.с. 002).

   2. Нажмите на кнопку "К диалогу".

4. Отобразится окно, отображающее диалог с пользователем.

#### Отображение времени отправки сообщений

1. 006
2. Проверка отображения времени отправки сообщений.
3. Произведите следующие шаги:

   1. Запустите приложение, авторизуйтесь (т.с. 001), перейдите на страницу необходимого пользователя (т.с. 002).

   2. Нажмите на кнопку "К диалогу".

4. Отобразится список сообщений, отображающий диалог с пользователем. Под каждым сообщением диалога отобразится время отправки сообщения.

#### Отображение записей на стене пользователя

1. 007
2. Проверка отображения записей на стене пользователя

3. Произведите следующие шаги:

   1. Запустите приложение, авторизуйтесь (т.с. 001) и перейдите на страницу необходимого пользователя (т.с. 002).

   2. Нажмите на кнопку "К стене".

4. На экране должен отобразиться список записей на стене пользователя.

#### Отображение времени создания записи на стене

1. 008
2. Проверка отображения времени создания записи на стене.
3. Произведите следующие шаги:

   1. Запустите приложение, авторизуйтесь (т.с. 001) и перейдите на страницу необходимого пользователя (т.с. 002).

   2. Нажмите на кнопку "К стене".

4. На экране должен отобразиться список записей на стене пользователя. В шапке каждой записи указано время создания записи.

#### Отображение общей и контактной информации о пользователях

1. 009
2. Проверка отображения общей и контактной информации о пользователях.
3. Произведите следующие шаги:

   1. Запустите приложение, авторизуйтесь (т.с. 001) и перейдите на страницу необходимого пользователя (т.с. 002).

4. Отобразится профиль выбранного пользователя. В правой части экрана отобразится общая и контактная информация о пользователе.

#### Отображение статусов пользователей

1. 010
2. Проверка отображения статусов пользователей
3. Произведите следующие шаги:

   1. Запустите приложение, авторизуйтесь (т.с. 001) и перейдите на страницу необходимого пользователя (т.с. 002).

4. Отобразится профиль выбранного пользователя. В правой части экрана, вверху, отобразится статус пользователя.

#### Возможность отображения основных фотографий пользователей

1. 011
2. Проверка отображения основных фотографий пользователей
3. Произведите следующие шаги:

   1. Запустите приложение, авторизуйтесь (т.с. 001) и перейдите на страницу необходимого пользователя (т.с. 002).

   2. Нажмите на кнопку «К стене».

   3. Нажмите на кнопку «Домой».
   
   4. Нажмите на кнопку «К стене».

4. После выполнения первого пункта отобразится основная фотография выбранного пользователя (если отсутствует – отобразится стандартное изображение отсутствия фотографии); после выполнения второго пункта отобразятся записи на стене выбранного пользователя, включая записи содержащие фотографии пользователя (если они есть); после выполнения третьего пункта отобразится основная фотография текущего пользователя (если отсутствует – отобразится стандартное изображение отсутствия фотографии); после выполнения четвертого пункта отобразятся записи на стене текущего пользователя, включая записи содержащие фотографии пользователя (если они есть).

#### Отображение состояния пользователей: онлайн/последняя активность

1. 012
2. Проверка отображения состояния пользователей: онлайн/последняя активность.
3. Произведите следующие шаги:
   
   1. Запустите приложение, авторизуйтесь (т.с. 001).
   
   2. Нажмите на кнопку «К стене».

   3. Перейдите на страницу необходимого пользователя (т.с. 002).

   4. Нажмите на кнопку «К стене».
   
   5. Нажмите на кнопку «К диалогу».

4. После выполнения п.1 и п.2 в шапке страницы будет отображено состояние текущего пользователя, после выполнения остальных пунктов – выбранного пользователя.

#### Быстрый переход на домашнюю страницу

1. 013
2. Возможность быстрого перехода на домашнюю страницу
3. Произведите следующие шаги:

   1. Запустите приложение, авторизуйтесь (т.с. 001).

   2. Перейдите к любому окну приложения (согласно описанных выше т.с.).

   3. Нажмите на кнопку «Домой».

4. Должен произойти переход на домашнюю страницу – профиль текущего пользователя.

#### Оповещение о получении новых сообщений

1. 014
2. Работа оповещения о получении новых сообщений
3. Произведите следующие шаги:

   1. Запустите приложение, авторизуйтесь (т.с. 001).

   2. Перейдите к любому окну приложения (согласно описанных выше т.с.).

4. Если текущему пользователю пришло новое сообщение, в шапке страницы, справа должно отобразиться оповещение.

#### Скорость работы запросов и процент ошибок

1. 015
2. Проверка скорости работы запросов и количества ошибочных запросов
3. Произведите следующие шаги:

   1. Запустите приложение, авторизуйтесь (т.с. 001).

   2. Перейдите к любому окну приложения (согласно описанных выше т.с.). Сделайте это несколько раз. Резльтат работы методов отобразится в статистике.

Для отображения статистики работы запросов используется специальный метод API ВКонтакте. Результаты работы запросов отображаются в кабинете приложения на сайте vk.com. Доступ к кабинету имеет только разработчик. Далее приведена статистика:

![](https://github.com/nikita9matveev/VK_Desk/blob/master/Docs/Tests/Stats/all.png)
![](https://github.com/nikita9matveev/VK_Desk/blob/master/Docs/Tests/Stats/errors.png)
 
4. Процент ошибок должен стремиться к нулю (показания около 4% являются нормальными) и среднее время работы запросов должно быть в пределах 0,5 секунды.

| Функциональные требования                | ID теста |
| ---------------------------------------- | :------: |
| авторизация |    001    |
| отображение друзей текущего пользователя с возможностью перехода на их страницы |    002    |
| отображение друзей онлайн текущего пользователя с возможностью перехода на их страницы |    003    |
| получение и отправка сообщений в режиме реального времени |   004    |
| отображение диалога с пользователем |    005    |
| отображение времени отправки сообщений |    006    |
| отображение записей на стене пользователя (в т.ч. вкл. репост)|    007    |
| отображение времени создания записи на стене |    008    |
| отображение общей и контактной информации о пользователях |    009    |
| отображение статусов пользователей |    010    |
| отображение состояния пользователей – онлайн/последняя активность |    012    |
| отображение основных фотографий пользователей |   011    |
| быстрый переход на домашнюю страницу |    013    |
| оповещение о получении новых сообщений |    014    |
| Скорость работы запросов и процент ошибок |    015    |
