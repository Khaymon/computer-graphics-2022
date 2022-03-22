# Домашние работы компьютерной графике ФПМИ МФТИ
<p float="left" align="center">
  <img src="https://github.com/Khaymon/mipt-2022-computer-graphics/blob/camera_movement/homework1/camera_movement/Triangles.gif" width="250" height="250" />
  <img src="https://github.com/Khaymon/mipt-2022-computer-graphics/blob/master/homework1/instead_of_cube/T.gif" width="250" height="250" />
</p>  

## Ссылки
- [Сайт с туториалами](http://www.opengl-tutorial.org/ru/)
## Домашняя работа 1
1. Запустить код уроков, проверить, что все работает, научиться создавать исполняемые файлы
2. Используя два разных шейдера, нарисовать 2 пересекающихся треугольника разных цветов с альфа-каналом (полупрозрачных), вершины которых не находятся на краях экрана
3. Добавить камеру в сцену, поиграться с функцией LookAt. Важно! После этого создать простой аналог анимационного фильма, где камера кружится вокруг тех двух треугольников, захардкодить её движение (не использовать ввод с мыши и клавиатуры)  (на ваше усмотрение, по какой траектории движется камера, какая задержка между кадрами, сколько кадров и т.п.)
4. Вместо куба из 4 урока, отрисовать любую другую объемную закрытую фигуру. Постараться настроить цвета вершин так, чтобы это было эстетично (но так как у всех понятия красоты отличаются, это не оценивается) и реализовать движение камеры вокруг.
### Оценивание домашней работы 1
На сдаче задания напротив фамилии каждого в [табличке](https://docs.google.com/spreadsheets/d/189_4597-jgIL-3nmXVoaYK-P0_RrbIyHWBmGnprwCsw/edit) будет 6 галочек:
- (1,2) Сдано задание (это значит, что я удостоверился, что у студента выполнены все пункты, описанные в части «задание») Необходимые части: исполняемый файл (.exe со всеми необходимыми для работы библиотеками внутри или в директории) и код (.сpp + файлы шейдеров). Обязательно иметь возможность показать код, описать все части приложения. Задание сдано если код работает, условия соблюдены, то же самое не было показано другим человеком ранее.
- (3) Наличие исполняемого файла для обоих заданий.
- (4,5) Сданы задачи, которые скину в выходные. Т.е. есть записанное решение задачи, объяснен ход решения, дан верный ответ в читаемом виде + дан ответ на вопрос по теории с лекций.
- (6) Доп. Балл за оригинальность / дополнительную фичу...  
Вес каждого пункта рассчитаем позже. Вес всего задания 2 балла не считая допов. Напоминаю, что для допуска на экзамен, нужно набрать не менее 1 балла.
### TODO
- [X] Треугольники
- [X] Движение камеры
- [X] Что-то вместо куба
- [ ] Задачи по лекциям
