# Отчет по лабораторной работе "Генерация последовательностей"

### Лисовский Олег Романович, М8О-308Б-17
Номер в группе: 10, Вариант: 4 ((остаток от деления (XX-1) на 6)+1)

### Цель работы

В данной лабораторной работе вам предстоит научиться генерировать последовательности с помощью рекуррентных нейронных сетей. 

### Используемые входные данные

В качестве входных данных использовались несколько англоязычных книг: Tresure Island
Были так же попытки добавить English Fairy Tales, Grimm's fairy Stories, но мощностей моего компьтера не хватило. 

### Предварительная обработка входных данных

Загружаем все файлы с расширением .txt и создаём из них список. Создаём из них два словаря. Далее вычисляем
паттерны и нормализуем их.

### Эксперимент 1: RNN

#### Архитектура сети

Главное отличие рекуррентных нейронных сетей от других - наличие обратных связей. Иначе говоря создаются копии слоя
и в них поступают результаты работы этого же слоя. Благодаря этому они способны запоминать контекст, что необходимо для
работы с текстами. Чтобы лучше понять принцип работы RNN, перечитайте этот абзац.

#### Результат

![График](epoch_loss_SimpleRNN.svg)

" dangerous nor did it greatly gall me when i used my arm then i looked around me and as the ship was now in a sense my own i began to think of clearing it from its last passenger the dead man o'brien he had pitched as i have said against the bulwarks where he lay like some horrible ungainly "

interior the puppet the the the the ” ” are the ” unfort'nate ” ” said ” said ” ” cried the ” said ” ” said ” ” ” ” said ” ” said ” ” ” ” ” ” ” said ” replied the ” ” ” ” said ” ” cried the ” said ” ” said ” said ” ” said ” ” said ” ” ” ” ” said ” said ” ” said ” ” said ” said ” ” ” ” ” said ” ” said ” ” said ” said ” ”

#### Вывод по данному эксперименту

Сеть оказалась достаточно эффективной для составления текста, который даже по началу достаточно читаемый, но
под конец сеть "заело", и она начала выводить вперемешку одно единственное, по всей видимости достаточно часто используемое,
слово и кавычки

### Эксперимент 2: Однослойная LSTM

#### Архитектура сети

Является достаточно мощной модификацией рекуррентных сетей. Внутрь слоя добавляется 3 так называемых вентиля (забвения,
входной и выходной), которые сильно влияют на состояние ячейки, благодаря которому осуществляются операции с информацией и
как она будет выглядеть на выходе из ячейки. 

#### Результат

![График](epoch_loss.svg)

" the wind's eye but i'll tell you i was sober i was on'y dog tired and if i'd awoke a second sooner i'd a caught you at the act i would he wasn't dead when i got round to him not he ” “well ” says captain smollett as cool as can be all that silver said was a riddle "

the the the the the the the the the the the ” ” ” ” ” ” ” ” ” ” ” ” ” ” ” ” ” ” ” ” ” ” ” ” ” ” ” ” ” ” ” ” ” ” ” ” ” ” ” ” ” ” ” ” ” ” ” ” ” ” ” ” ” ” ” ” ” ” ” ” ” ” ” ” ” ” ” ” ” ” ” ” ” ” ” ” ” ” ” ” ” ” ” ” ” ” ” ” ”

#### Вывод по данному эксперименту

Она показала более лучший старт чем, RNN сеть, но в середине она обучалась чуть хуже, но полностью компенсировала
это под конец, сильно уменьшая ошибки. Первое предложение оказалось чуть лучше, чем у RNN. Во втором предложении
имелось только слово the и кавычки, не вперемешку, что наверное лучше чем у RNN.

### Эксперимент 3: Двухслойная LSTM

#### Архитектура сети

Является по сути той же самой LSTM сетью, но со вторым слоем.

#### Результат

![График](loss_LSTM2.svg)

" rules i do i won't hurt a depytation ” thus encouraged the buccaneer stepped forth more briskly and having passed something to silver from hand to hand slipped yet more smartly back again to his companions the sea cook looked at what had been given him “the black spot i thought so ” he observed “where might you have got "

” ” ” said ” said ” said ” said ” captain the captain ” he the captain ” he the captain ” he the captain ” he the captain ” he the captain ” he the captain ” he the captain ” he the ” ” ” said ” said ” said ” said ” said ” said ” said ” said ” said ” said ” said ” said ” said ” said ” said ” said ” said ” said ” said ” said ” said ” said ” said ” said ” said ” said ”

#### Вывод по данному эксперименту

Она показала чуть более лучший старт чем, однослойная сеть, но её "плато" оказалось выражено гораздо лучше, что
не помешало ей показать меньший результат ошибок чем у однослойной сети. В плане построения первого предложения
то виден прогресс - сеть научилась строить прямую реч. Второе предложение теперь лишь наполовину заполнено повторяющимся
словом, впрочем кавычки всё так же занимают значительную его часть.

### Эксперимент 4: GRU

#### Архитектура сети

Является модификацией LSTM, соответственно являясь ещё более технологичной модификацией RNN. Главное отличие от
LSTM сети заключается в том, что вентили забвения и входа объединяются в единый вентиль обновления.

#### Результат

![График](epoch_loss_GRU.svg)

" stay here a bit ” he continued “i'm a plain man rum and bacon and eggs is what i want and that head up there for to watch ships off what you mought call me you mought call me captain oh i see what you're at there” and he threw down three or four gold pieces on the threshold “you "

the ” the the ” says the doctor the ” the the “would the the doctor the the the the the the the the the the the the the the the the the the the the the the the the the the the the the the the the the the the the the the the forever “they're fourth the sp'iling blabbing forever amen you'd retorted you is the i the i the i the the the the feelings the the the the the the the the the the the the the the the the the the the the the the

#### Вывод по данному эксперименту

Старт оказался чуть менее впечатляющим чем в предыдущие разы, но самая низкая ошибка показала, что GRU может составлять
лучшие предложения из всех сетей. Это особо хорошо подтверждает первое предложение - оно самое осмысленное и
грамматически правильное. Во втором предложении кавычки практически не наблюдаются и постоянный повтор слова the
разбавляется небольшими осмысленными фразами и слово сочетаниями.

### Выводы

Все эксперименты проводились при 25 эпохах и 256 батчах

Самой быстрой оказалась RNN, в тоже самое время она показала худший результат из всех. Однослойная LSTM оказалась чуть
более эффективной, но затребовала больше времени. Дольше всех работала двухслойная LSTM, при этом её результат не так
сильно отличается от однослойной сети. Наиболее эффективной оазалась GRU сеть - работала примерно столько же, сколько
однослойная LSTM, но ошибки оказались самыми маленькими, вдобавок предложения, построенные данной сетью оказались самыми
осмысленными и богатыми на лексикон.

Но при этом количество эпох достаточно мало, как и объём текста (с большими текстами мой компьютер просто отказывался
работать, а при большем количестве эпох работал непростительно долго). Поэтому истинную мощь данных сетей можно познать
только при работе с полноценными библиотеками и при большом количестве эпох (200 - 500). 
