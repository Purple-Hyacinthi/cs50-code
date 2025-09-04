SELECT title, year FROM movies
WHERE title LIKE 'Harry Potter%'
--%不留空隙的原因是Harry Potter: A History of Magic这个电影在Harry Potter后直接加“:” 空了就查不到了
ORDER BY year ASC;--记得时间排序
